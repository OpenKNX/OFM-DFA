// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023 Cornelius Koepp

#include "DfaModule.h"

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
        _channels[i]->loop();
    }
}

void DfaModule::processInputKo(GroupObject &ko)
{
    for (uint8_t i = 0; i < DFA_ChannelCount; i++)
    {
        _channels[i]->processInputKo(ko);
    }
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
    }
    return false;
}