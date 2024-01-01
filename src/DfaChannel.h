// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023 Cornelius Koepp

#pragma once
#include "OpenKNX.h"

#define DFA_DEF_STATES_COUNT 32
#define DFA_DEF_INPUTS_COUNT 8
#define DFA_DEF_OUTPUTS_COUNT 4

#define DFA_STATE_PARAM_XOR 0x40
#define DFA_STATE_UNDEFINED 0xff
#define DFA_STATE_VALUE_UNDEFINED 0x40

#define INPUT_TRIGGER_DISABLED 0b00
#define INPUT_TRIGGER_0        0b01
#define INPUT_TRIGGER_1        0b10
#define INPUT_TRIGGER_BOTH     0b11

#define OUTPUT_TYPE_DPT1    10
#define OUTPUT_TYPE_DPT2    20
#define OUTPUT_TYPE_DPT5    50
#define OUTPUT_TYPE_DPT5001 51
#define OUTPUT_TYPE_DPT6    61
#define OUTPUT_TYPE_DPT7    70
#define OUTPUT_TYPE_DPT8    80
#define OUTPUT_TYPE_DPT9    90
#define OUTPUT_TYPE_DPT12   120
#define OUTPUT_TYPE_DPT13   130
#define OUTPUT_TYPE_DPT14   140
#define OUTPUT_TYPE_DPT16   161
#define OUTPUT_TYPE_DPT17   171
#define OUTPUT_TYPE_DPT232  232

#define OUTPUT_SEND_CHANGE  1
#define OUTPUT_SEND_ALWAYS  2

// #if (DFA_ParamBlockSize > 0xff)
//  #error Relativ channel parameter index > uint8_t => need uint16_t for DfaStateTimeoutParamRelIdx.state and _transitionParamsRelIdx
// #endif

struct DfaInputs {
    uint8_t trigger;
    uint16_t koNumber;
};

struct DfaStateTimeoutParamRelIdx {
    uint16_t delay;
    uint16_t state; // note: uint8_t is to small
};

class DfaChannel : public OpenKNX::Channel
{
  private:
    static const uint8_t _magicWord[4];

    static const uint8_t _inputKo[DFA_DEF_INPUTS_COUNT];
    static const uint16_t _inputConfPRI[DFA_DEF_INPUTS_COUNT];
    static const uint16_t _inputConfNumberPRI[DFA_DEF_INPUTS_COUNT];
    static const uint16_t _inputTriggerPRI[DFA_DEF_INPUTS_COUNT];

    // note: uint8_t is to small
    static const uint16_t _outputKoPRI[DFA_DEF_OUTPUTS_COUNT];
    static const uint16_t _outputDptPRI[DFA_DEF_OUTPUTS_COUNT];
    static const uint16_t _outputSendPRI[DFA_DEF_STATES_COUNT][DFA_DEF_OUTPUTS_COUNT];
    static const uint16_t _outputValuePRI[DFA_DEF_STATES_COUNT][DFA_DEF_OUTPUTS_COUNT];
    static const uint16_t _transPRI[DFA_DEF_STATES_COUNT][DFA_DEF_INPUTS_COUNT];
    static const DfaStateTimeoutParamRelIdx _timeoutPRI[DFA_DEF_STATES_COUNT];

    // is enabled in ETS?
    bool _channelActive = true;

    DfaInputs _inputs[DFA_DEF_INPUTS_COUNT] = {};

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

    uint16_t getInputKo(const uint8_t input);
    void initInputConfig();

    uint32_t getStateTimeoutDelay_ms(const uint8_t state);
    uint8_t getTimeoutState(const uint8_t state);
    inline bool isValidState(const uint8_t state);
    void setState(const uint8_t nextState);
    void sendOutput(const uint8_t outputIndex, const KNXValue &value, const Dpt &type, const uint8_t outputStateSend);
    void sendValues();
    void transfer(const uint8_t input);

    void endTimeout();
    uint32_t timeoutRemaining_ms();

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