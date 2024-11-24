// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2024 Cornelius Koepp

#pragma once
#include "OpenKNX.h"

#define DFA_DEF_STATES_COUNT 32
#define DFA_DEF_INPUTS_COUNT 8
#define DFA_DEF_OUTPUTS_COUNT 4

#define DFA_STATE_UNDEFINED 0xff
// #define DFA_STATE_VALUE_UNDEFINED 0x00
#define DFA_STATE_TIMEOUT_RESET 0x7f

// #define DFA_INPUT_TRIGGER_DISABLED 0b00
// #define DFA_INPUT_TRIGGER_0        0b01
// #define DFA_INPUT_TRIGGER_1        0b10
// #define DFA_INPUT_TRIGGER_BOTH     0b11
enum class DfaInputTrigger
{
  disabled = 0b00,
  only0    = 0b01,
  only1    = 0b10,
  both     = 0b11,
};

enum class DfaDirectSetSame {
  ignore              = 0b00,
  timeout_restart     = 0b01,
  // timeout_continue = 0b10,
  // timeout_add      = 0b11,
};

#define DFA_OUTPUT_TYPE_DPT1    10
#define DFA_OUTPUT_TYPE_DPT2    20
#define DFA_OUTPUT_TYPE_DPT5    50
#define DFA_OUTPUT_TYPE_DPT5001 51
#define DFA_OUTPUT_TYPE_DPT6    61
#define DFA_OUTPUT_TYPE_DPT7    70
#define DFA_OUTPUT_TYPE_DPT8    80
#define DFA_OUTPUT_TYPE_DPT9    90
#define DFA_OUTPUT_TYPE_DPT12   120
#define DFA_OUTPUT_TYPE_DPT13   130
#define DFA_OUTPUT_TYPE_DPT14   140
#define DFA_OUTPUT_TYPE_DPT16   161
#define DFA_OUTPUT_TYPE_DPT17   171
#define DFA_OUTPUT_TYPE_DPT232  232

// #if (DFA_ParamBlockSize > 0xff)
//  #error Relativ channel parameter index > uint8_t => need uint16_t for DfaStateTimeoutParamRelIdx.state and _transitionParamsRelIdx
// #endif

struct DfaInputs
{
  DfaInputTrigger trigger;
  uint16_t koNumber;
};

struct DfaStateTimeoutParamRelIdx
{
  uint16_t delay;
  uint16_t state; // note: uint8_t is to small
};

struct DfaTimeout
{
  uint32_t delay_ms;
  uint32_t begin_ms;
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
    bool _channelActive = false;

    DfaInputs _inputs[DFA_DEF_INPUTS_COUNT] = {};
    DfaTimeout _outputsTimeout[DFA_DEF_OUTPUTS_COUNT] = {};

    // wait while startup is delayed
    bool _processStartupDelay = false;
    uint32_t _startupDelayBegin_ms = 0;

    // is not paused (startup is ETS, later updated by KO)
    bool _running = false;
    uint32_t _pauseBegin = 0;

    // will be set to defined start-state or restored state
    uint8_t _firstState = DFA_STATE_UNDEFINED;
    uint32_t _firstStateTimeoutDelay_ms = 0;

    uint8_t _state = DFA_STATE_UNDEFINED;
    uint32_t _stateTimeoutDelay_ms = 0;
    uint32_t _stateTimeoutBegin_ms = 0;

    uint16_t getInputKoNumber(const uint8_t input);
    void initInputConfig();

    uint32_t getStateTimeoutDelay_ms(const uint8_t state);
    uint8_t getTimeoutState(const uint8_t state);
    inline bool isValidState(const uint8_t state);
    void setState(const uint8_t nextState, const DfaDirectSetSame sameStateBehaviour = DfaDirectSetSame::timeout_restart);
    void transfer(const uint8_t input);

    void endTimeout();
    void resetTimeout();
    uint32_t timeoutRemaining_ms();

    void setRunning(const bool requestRun, const bool first = false);

    uint8_t outputGetDpt(const uint8_t i);
    uint8_t outputGetCurrentStateSendConfig(const uint8_t i);
    void outputLoop(const uint8_t i);
    void outputUpdate(const uint8_t i, const bool send, const bool forceSend /*= false*/);
    /*bool*/ void outputUpdateKO(const uint8_t i, const KNXValue &value, const Dpt &type, const bool send, const bool forceSend /*= false*/);

  public:
    explicit DfaChannel(uint8_t index);
    const std::string name() override;
    void setup() override;
    void loop() override;
    void processAfterStartupDelay();
    void processInputKo(GroupObject &ko) override;

    void save();
    void restore();

    bool processCommandDfa();
    bool processCommandDfaTimeout();
    bool processCommandDfaStateSet(const uint8_t stateStarting1);
    bool processCommandDfaSymbolInsert(const uint8_t inputSymbolNumber);
};