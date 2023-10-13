// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023 Cornelius Koepp

#pragma once
#include "DfaChannel.h"
#include "OpenKNX.h"
// always include for RUNTIME_MEASURE_{BEGIN,END}
#include "OpenKNX/Stat/RuntimeStat.h"

class DfaModule : public OpenKNX::Module
{
  private:
    DfaChannel *_channels[DFA_ChannelCount];
#ifdef OPENKNX_RUNTIME_STAT
    OpenKNX::Stat::RuntimeStat _channelLoopRuntimes[DFA_ChannelCount];
    OpenKNX::Stat::RuntimeStat _channelInputRuntimes[DFA_ChannelCount];
#endif

  public:
    DfaModule();
    const std::string name() override;
    const std::string version() override;

    // configured only
    void setup() override;
    void loop() override;

    void processInputKo(GroupObject &ko) override;

    void showHelp() override;
    bool processCommand(const std::string cmd, bool diagnoseKo);
};