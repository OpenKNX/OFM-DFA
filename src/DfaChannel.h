// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023 Cornelius Koepp

#pragma once
#include "OpenKNX.h"

#define DFA_DEF_STATES_COUNT 16
#define DFA_DEF_INPUTS_COUNT 8

#define DFA_STATE_UNDEFINED 0xff
#define DFA_STATE_VALUE_UNDEFINED 0x40

#if (DFA_ParamBlockSize > 0xff)
  #error Relativ channel parameter index > uint8_t => need uint16_t for DfaStateTimeoutParamRelIdx.state and _transitionParamsRelIdx
#endif

struct DfaStateTimeoutParamRelIdx {
    uint8_t delay;
    uint8_t state; // note: relative param index <= uint8_t is ensured at compile-time
};

class DfaChannel : public OpenKNX::Channel
{
  private:
    static const uint8_t _magicWord[4];

    // note: relative param index <= uint8_t is ensured at compile-time
    static const uint8_t _valuePRI[DFA_DEF_STATES_COUNT];
    static const uint8_t _transPRI[DFA_DEF_STATES_COUNT][DFA_DEF_INPUTS_COUNT];
    static const DfaStateTimeoutParamRelIdx _timeoutPRI[DFA_DEF_STATES_COUNT];

    // is enabled in ETS?
    bool _channelActive = true;

    // wait while startup is delayed
    bool _processStartupDelay = false;
    uint32_t _startupDelayBegin_ms = 0;

    // is not paused (startup is ETS, later updated by KO)
    bool _running = false;
    uint32_t _pauseBegin = 0;

    uint8_t _firstState = DFA_STATE_UNDEFINED;
    uint32_t _firstStateTimeoutDelay_ms = 0;

    uint8_t _state = DFA_STATE_UNDEFINED;
    uint32_t _stateTimeoutDelay_ms = 0;
    uint32_t _stateTimeoutBegin_ms = 0;
    uint8_t _stateValue = DFA_STATE_VALUE_UNDEFINED;

    uint32_t getStateTimeoutDelay_ms(const uint8_t state);
    uint8_t getTimeoutState(const uint8_t state);
    inline bool isValidState(const uint8_t state);
    void setState(const uint8_t nextState);
    void transfer(const uint8_t input);

    void endTimeout();

    void setRunning(const bool requestRun, const bool first = false);

  public:
    explicit DfaChannel(uint8_t index);
    const std::string name() override;
    void setup() override;
    void loop() override;
    void processInputKo(GroupObject &ko) override;

    void save();
    void restore();

    bool processCommand(const std::string cmd, bool diagnoseKo);
};