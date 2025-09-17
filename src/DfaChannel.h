// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2025 Cornelius Koepp

#pragma once
#include "OpenKNX.h"

#include "DfaConstants.h"
#include "DfaHistory.h"
#include "DfaOutput.h"

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

enum class DfaDirectSetSame
{
    ignore              = 0b00,
    timeout_restart     = 0b01,
    // timeout_continue = 0b10,
    // timeout_add      = 0b11,
};

// #if (DFA_ParamBlockSize > 0xff)
//  #error Relativ channel parameter index > uint8_t => need uint16_t for DfaStateTimeoutParamRelIdx.state and _transitionParamsRelIdx
// #endif

struct DfaInputs
{
    DfaInputTrigger trigger;
    uint16_t koNumber;
};




class DfaChannel : public OpenKNX::Channel
{
  private:
    static const uint8_t _magicWord[4];

    static const uint8_t _inputKo[DFA_DEF_INPUTS_COUNT];
    static const uint16_t _inputConfPRI[DFA_DEF_INPUTS_COUNT];
    static const uint16_t _inputConfNumberPRI[DFA_DEF_INPUTS_COUNT];
    static const uint16_t _inputTriggerPRI[DFA_DEF_INPUTS_COUNT];

    static const uint16_t _transPRI[DFA_DEF_STATES_COUNT][DFA_DEF_INPUTS_WITH_T_COUNT];
    static const uint16_t _timeoutPRI[DFA_DEF_STATES_COUNT];

    // is enabled in ETS?
    bool _channelActive = false;

    DfaInputs _inputs[DFA_DEF_INPUTS_COUNT] = {};

    DfaOutput* _outputs[DFA_DEF_OUTPUTS_COUNT] = {};

    // wait while startup is delayed
    bool _processStartup = false;
    uint32_t _startupDelayBegin_ms = 0;

    // will be set to defined or restored running state
    bool _firstRunning = true;

    // is not paused (startup is ETS, later updated by KO)
    bool _running = false;
    uint32_t _pauseBegin = 0;

    // will be set to defined start-state or restored state
    uint8_t _firstState = DFA_STATE_UNDEFINED;
    uint32_t _firstStateTimeoutDelay_ms = 0;
    // indicate last state was restored, which should result in special handling of sending
    uint8_t _restoreOutputs = false;

    uint8_t _state = DFA_STATE_UNDEFINED;
    uint32_t _stateTimeoutDelay_ms = 0;
    uint32_t _stateTimeoutBegin_ms = 0;

    DfaHistory _history;

    void addHistory(uint8_t input, uint8_t state);

    uint16_t getLogicOutputKoNumber(const uint8_t /* intended overlapping name for usage in macro! */ _channelIndex);
    uint16_t getInputKoNumber(const uint8_t input);
    void initInputConfig();

    uint32_t getStateTimeoutDelay_ms(const uint8_t state);
    inline bool isValidState(const uint8_t state);
    void setState(const uint8_t nextState, const DfaDirectSetSame sameStateBehaviour = DfaDirectSetSame::timeout_restart);

    void transfer(const uint8_t input);
    uint8_t transferGetNextForInput(const uint8_t input);
    uint8_t transferEvaluateChoice(const uint8_t nextState);
    void transferProcessNext(const uint8_t nextState);

    void endTimeout();
    void resetTimeout();
    uint32_t timeoutRemaining_ms();

    void setRunning(const bool requestRun, const bool first = false);

  public:
    explicit DfaChannel(uint8_t index);
    const std::string name() override;
    void setup() override;
    void loop() override;
    void processAfterStartupDelay();
    void processInputKo(GroupObject &ko) override;

    void save();
    void restore();

    bool processCommandDfa(bool diagnoseKo);
    bool processCommandDfaTimeout(bool diagnoseKo);
    bool processCommandDfaStateSet(const uint8_t stateStarting1, bool diagnoseKo);
    bool processCommandDfaSymbolInsert(const uint8_t inputSymbolNumber, bool diagnoseKo);
    bool processCommandDfaHistory(bool diagnoseKo);
};