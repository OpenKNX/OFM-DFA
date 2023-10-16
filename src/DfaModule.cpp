// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023 Cornelius Koepp

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
    openknx.console.printHelpLine("dfaNN timeout!", "(WIP/may change) Let timeout of channel NN end now!");
}

bool DfaModule::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (cmd.substr(0, 3) == "dfa")
    {
        // TODO Check and refine command definitions after first tests and extension!
        if (cmd.length() == 14 && cmd.substr(5, 9) == " timeout!")
        {
            uint16_t channelIdx = std::stoi(cmd.substr(3, 2)) - 1;

            if (channelIdx < DFA_ChannelCount)
            {
                logDebugP("=> DFA-Channel<%d> timeout end now!", (channelIdx + 1));
                return _channels[channelIdx]->processCommand(cmd, diagnoseKo);
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