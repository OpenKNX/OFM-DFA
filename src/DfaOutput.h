// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2025 Cornelius Koepp

#pragma once
#include "OpenKNX.h"



// TODO check best place to define constants
#define DFA_DEF_STATES_COUNT 16
#define DFA_DEF_INPUTS_COUNT 8
#define DFA_DEF_OUTPUTS_COUNT 4

// TODO check best place to define constants
#define DFA_STATE_UNDEFINED 0xff
// #define DFA_STATE_VALUE_UNDEFINED 0x00
#define DFA_STATE_TIMEOUT_RESET 0x7f



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


struct DfaTimeout
{
    uint32_t delay_ms;
    uint32_t begin_ms;
};

// TODO check inheritance from Base?
class DfaOutput
{
  private:
    // same as in Base; required for Param-Macros
    uint8_t _channelIndex = 0;

    // note: uint8_t is to small
    static const uint16_t _outputIntervalPRI[DFA_DEF_OUTPUTS_COUNT];
    static const uint16_t _outputSendPRI[DFA_DEF_STATES_COUNT][DFA_DEF_OUTPUTS_COUNT];
    static const uint16_t _outputValuePRI[DFA_DEF_STATES_COUNT][DFA_DEF_OUTPUTS_COUNT];

    /** the 0-based output-number */
    uint8_t i;

    uint8_t _state = DFA_STATE_UNDEFINED;

    /*bool*/ void outputUpdateKO(const KNXValue &value, const Dpt &type, const bool send, const bool forceSend /*= false*/);

    // TODO replace by setting new state only!
    uint8_t getCurrentStateSendConfig();

    // TODO reduce visibility
    // TOOD replace with "has value"?
    uint8_t outputGetDpt();
    // replaced: DfaTimeout _outputsTimeout[DFA_DEF_OUTPUTS_COUNT] = {};
    DfaTimeout _timeout = {};

    /**
     * Update the output based on current state
     * @param _state TODO replace
     * @param send - true will send changed value, false will update GO only
     * @param forceSend - true will always send; independent of value
     */
    void outputUpdate(const bool send, const bool forceSend /*= false*/);

  public:
    DfaOutput(uint8_t channelIndex, uint8_t outputIndex);
    void loop();
    void stateUpdate(const uint8_t newState, const bool _restoreOutputs);

};