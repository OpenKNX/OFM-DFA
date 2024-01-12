// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2024 Cornelius Koepp

#pragma once
#include "DfaChannel.h"
#include "OpenKNX.h"
// always include for RUNTIME_MEASURE_{BEGIN,END}
#include "OpenKNX/Stat/RuntimeStat.h"

#define DFA_FLASH_MAGIC_WORD_LEN 4

class DfaModule : public OpenKNX::Module
{
  private:
    static const uint8_t _magicWord[DFA_FLASH_MAGIC_WORD_LEN];

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
    void processAfterStartupDelay() override;
    void loop() override;

    void processInputKo(GroupObject &ko) override;

    // persistance handling
    uint16_t flashSize() override;    
    void writeFlash() override;
    void readFlash(const uint8_t *iBuffer, const uint16_t iSize) override;

    void showHelp() override;
    bool processCommand(const std::string cmd, bool diagnoseKo);
};

extern DfaModule openknxDfaModule;