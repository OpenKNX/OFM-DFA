// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023 Cornelius Koepp

#pragma once
#include "DfaChannel.h"
#include "OpenKNX.h"

class DfaModule : public OpenKNX::Module
{
  private:
    DfaChannel *_channels[DFA_ChannelCount];

  public:
    DfaModule();
    const std::string name() override;

    // configured only
    void setup() override;
    void loop() override;

    void processInputKo(GroupObject &ko) override;
};