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
