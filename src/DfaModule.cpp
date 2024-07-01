// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2024 Cornelius Koepp

#include "DfaModule.h"

// TODO replace x!
const uint8_t DfaModule::_magicWord[DFA_FLASH_MAGIC_WORD_LEN] = {
    'x',
    'D',
    'f',
    'a',
};

DfaModule::DfaModule()
{
    for (uint8_t i = 0; i < DFA_ChannelCount; i++)
    {
        _channels[i] = new DfaChannel(i);
    }
}

const std::string DfaModule::name()
{
    return "DFA";
}

const std::string DfaModule::version()
{
    return MODULE_DFA_Version;
}

void DfaModule::setup()
{
    logDebugP("setup");
    logIndentUp();
    for (uint8_t i = 0; i < DFA_ChannelCount; i++)
    {
        _channels[i]->setup();
    }
    logIndentDown();
}

void DfaModule::processAfterStartupDelay()
{
    logDebugP("processAfterStartupDelay");
    logIndentUp();
    for (uint8_t i = 0; i < DFA_ChannelCount; i++)
    {
        _channels[i]->processAfterStartupDelay();
    }
    logIndentDown();    
}

void DfaModule::loop()
{
    // loop all channels, as handling is fast
    for (uint8_t i = 0; i < DFA_ChannelCount; i++)
    {
        RUNTIME_MEASURE_BEGIN(_channelLoopRuntimes[i]);
        _channels[i]->loop();
        RUNTIME_MEASURE_END(_channelLoopRuntimes[i]);
    }
}

void DfaModule::processInputKo(GroupObject &ko)
{
    for (uint8_t i = 0; i < DFA_ChannelCount; i++)
    {
        RUNTIME_MEASURE_BEGIN(_channelInputRuntimes[i]);
        _channels[i]->processInputKo(ko);
        RUNTIME_MEASURE_END(_channelInputRuntimes[i]);
    }
}

uint16_t DfaModule::flashSize()
{
    // [4] MAGIG_WORD ('CDfa')
    // [1] VERSION
    // per Channel:
    //   [1] CH_CONF
    //   [1] CH_STATE
    //   [4] CH_TIMEOUT
    return 4 + 1 + DFA_ChannelCount * (1 + 1 + 4);
}

void DfaModule::writeFlash()
{
    logDebugP("writing");

    // magic word
    for (size_t i = 0; i < DFA_FLASH_MAGIC_WORD_LEN; i++)
        openknx.flash.writeByte(_magicWord[i]);

    // version
    openknx.flash.writeByte(1);

    for (uint8_t i = 0; i < DFA_ChannelCount; i++)
    {
        _channels[i]->save();
    }
    logDebugP("write [done]");
}

void DfaModule::readFlash(const uint8_t *buf, const uint16_t size)
{
    if (size < 4 + 1) // no channels present
    {
        logDebugP("Flash data short!");
        return;
    }

    for (size_t i = 0; i < DFA_FLASH_MAGIC_WORD_LEN; i++)
    {
        if (openknx.flash.readByte() != _magicWord[i])
        {
            logDebugP("Wrong magic-word!");
            return;
        }
    }

    const uint8_t version = openknx.flash.readByte();
    if (version != 1) // version unknown
    {
        logDebugP("Wrong version (%d)", version);
        return;
    }

    const uint8_t chDataMaxCount = (size - 4 - 1) / (1 + 1 + 4);
    logDebugP("Found %d of %d channels", chDataMaxCount, DFA_ChannelCount);
    const uint8_t n = MIN(chDataMaxCount, DFA_ChannelCount);
    for (uint8_t i = 0; i < n; i++)
    {
        _channels[i]->restore();
    }
    logDebugP("read [done]");
}

void DfaModule::showHelp()
{
    // TODO Check and refine command definitions after first tests and extension!
    openknx.console.printHelpLine("dfaNN",          "Show current state and timeout remain");
    if (DFA_DiagnoseAccess == 1) // writing to DFAs is allowed
    {
        openknx.console.printHelpLine("dfaNN timeout!", "Let timeout of channel NN end now!");
        openknx.console.printHelpLine("dfaNN state=SS", "Change state to SS");
        openknx.console.printHelpLine("dfaNN symbol=X", "Input the symbol X");
    }
}

bool DfaModule::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (cmd.substr(0, 3) == "dfa")
    {
        if (cmd.length() >= 5) 
        {
            if (!std::isdigit(cmd[3]) || !std::isdigit(cmd[4]))
            {
                logErrorP("=> invalid channel-number '%s'!", cmd.substr(3, 2).c_str());
                return false;
            }

            const uint16_t channelIdx = std::stoi(cmd.substr(3, 2)) - 1;
            if (channelIdx < DFA_ChannelCount)
            {
                if (cmd.length() == 5)
                {
                    logDebugP("=> DFA-Channel<%u> overview!", (channelIdx + 1));
                    return _channels[channelIdx]->processCommandDfa();
                }
                else if (ParamDFA_DiagnoseAccess == 1) // writing to DFAs is allowed
                {
                    if (cmd.length() == 14) // all current commands have the same length
                    {
                        if (cmd.substr(5, 9) == " timeout!")
                        {
                            logDebugP("=> DFA-Channel<%u> timeout end now!", (channelIdx + 1));
                            return _channels[channelIdx]->processCommandDfaTimeout();
                        }
                        else if (cmd.substr(5, 7) == " state=" && std::isdigit(cmd[12]) && std::isdigit(cmd[13]))
                        {
                            const uint8_t newState = std::stoi(cmd.substr(12, 2));

                            logDebugP("=> DFA-Channel<%u> set state=%u!", (channelIdx + 1), newState);
                            return _channels[channelIdx]->processCommandDfaStateSet(newState);
                        }
                        else if (cmd.substr(5, 8) == " symbol=" && ('A' <= cmd[13] && cmd[13] <= 'H'))
                        {
                            const uint8_t inputSymbolNumber = cmd[13] - 'A';

                            logDebugP("=> DFA-Channel<%u> input Symbol=%c (%u)!", (channelIdx + 1), ('A' + inputSymbolNumber), inputSymbolNumber);
                            return _channels[channelIdx]->processCommandDfaSymbolInsert(inputSymbolNumber);
                        }
                    }
                }
            }
            else
            {
                logInfoP("=> unused channel-number %u!", channelIdx + 1);
            }
        }
#ifdef OPENKNX_RUNTIME_STAT
        else if (cmd == "dfa runtime")
        {
            logInfoP("DFA Runtime Statistics: (Uptime=%dms)", millis());
            logIndentUp();
            OpenKNX::Stat::RuntimeStat::showStatHeader();
            char labelLoop[8 + 1] = "Ch00Loop";
            char labelInput[8 + 1] = "Ch00Inpt";
            for (uint8_t i = 0; i < DFA_ChannelCount; i++)
            {
                labelLoop[2] = labelInput[2] = '0' + i / 10;
                labelLoop[3] = labelInput[3] = '0' + i % 10;
                _channelLoopRuntimes[i].showStat(labelLoop, 0, true, true);
                _channelInputRuntimes[i].showStat(labelInput, 0, true, true);
            }
            logIndentDown();
        }
#endif
    }
    return false;
}

DfaModule openknxDfaModule;