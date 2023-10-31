// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023 Cornelius Koepp

#include "DfaChannel.h"

const uint8_t DfaChannel::_inputKo[DFA_DEF_INPUTS_COUNT] = {
    DFA_KoKOfInput1,
    DFA_KoKOfInput2,
    DFA_KoKOfInput3,
    DFA_KoKOfInput4,
    DFA_KoKOfInput5,
    DFA_KoKOfInput6,
    DFA_KoKOfInput7,
    DFA_KoKOfInput8,
};

// TODO calculate index; expected distance should be protected by compile error
const uint16_t DfaChannel::_inputConfPRI[DFA_DEF_INPUTS_COUNT] = {
    DFA_fInputSymbol1Ko,
    DFA_fInputSymbol2Ko,
    DFA_fInputSymbol3Ko,
    DFA_fInputSymbol4Ko,
    DFA_fInputSymbol5Ko,
    DFA_fInputSymbol6Ko,
    DFA_fInputSymbol7Ko,
    DFA_fInputSymbol8Ko,
};
const uint16_t DfaChannel::_inputConfNumberPRI[DFA_DEF_INPUTS_COUNT] = {
    DFA_fInputSymbol1KoNumber,
    DFA_fInputSymbol2KoNumber,
    DFA_fInputSymbol3KoNumber,
    DFA_fInputSymbol4KoNumber,
    DFA_fInputSymbol5KoNumber,
    DFA_fInputSymbol6KoNumber,
    DFA_fInputSymbol7KoNumber,
    DFA_fInputSymbol8KoNumber,
};
const uint16_t DfaChannel::_inputTriggerPRI[DFA_DEF_INPUTS_COUNT] = {
    DFA_fInputSymbol1Value,
    DFA_fInputSymbol2Value,
    DFA_fInputSymbol3Value,
    DFA_fInputSymbol4Value,
    DFA_fInputSymbol5Value,
    DFA_fInputSymbol6Value,
    DFA_fInputSymbol7Value,
    DFA_fInputSymbol8Value,
};

// TODO calculate index; expected distance should be protected by compile error
// TODO special handling of indices for >32 DFA required
// Define (relative) parameter address-index for next state by current state and input
const uint16_t DfaChannel::_outputKoPRI[DFA_DEF_OUTPUTS_COUNT] = {
    DFA_KoKOfOutput1,
    DFA_KoKOfOutput2,
    DFA_KoKOfOutput3,
    DFA_KoKOfOutput4,
};
const uint16_t DfaChannel::_outputDptPRI[DFA_DEF_OUTPUTS_COUNT] = {
    DFA_fOutput1Dpt,
    DFA_fOutput2Dpt,
    DFA_fOutput3Dpt,
    DFA_fOutput4Dpt,
};
const uint16_t DfaChannel::_outputSendPRI[DFA_DEF_STATES_COUNT][DFA_DEF_OUTPUTS_COUNT] = {
    // TODO ensure same position of all Outputs
    { DFA_fState01Output1Conf, DFA_fState01Output2Conf, DFA_fState01Output3Conf, DFA_fState01Output4Conf, },
    { DFA_fState02Output1Conf, DFA_fState02Output2Conf, DFA_fState02Output3Conf, DFA_fState02Output4Conf, },
    { DFA_fState03Output1Conf, DFA_fState03Output2Conf, DFA_fState03Output3Conf, DFA_fState03Output4Conf, },
    { DFA_fState04Output1Conf, DFA_fState04Output2Conf, DFA_fState04Output3Conf, DFA_fState04Output4Conf, },
    { DFA_fState05Output1Conf, DFA_fState05Output2Conf, DFA_fState05Output3Conf, DFA_fState05Output4Conf, },
    { DFA_fState06Output1Conf, DFA_fState06Output2Conf, DFA_fState06Output3Conf, DFA_fState06Output4Conf, },
    { DFA_fState07Output1Conf, DFA_fState07Output2Conf, DFA_fState07Output3Conf, DFA_fState07Output4Conf, },
    { DFA_fState08Output1Conf, DFA_fState08Output2Conf, DFA_fState08Output3Conf, DFA_fState08Output4Conf, },
    { DFA_fState09Output1Conf, DFA_fState09Output2Conf, DFA_fState09Output3Conf, DFA_fState09Output4Conf, },
    { DFA_fState10Output1Conf, DFA_fState10Output2Conf, DFA_fState10Output3Conf, DFA_fState10Output4Conf, },
    { DFA_fState11Output1Conf, DFA_fState11Output2Conf, DFA_fState11Output3Conf, DFA_fState11Output4Conf, },
    { DFA_fState12Output1Conf, DFA_fState12Output2Conf, DFA_fState12Output3Conf, DFA_fState12Output4Conf, },
    { DFA_fState13Output1Conf, DFA_fState13Output2Conf, DFA_fState13Output3Conf, DFA_fState13Output4Conf, },
    { DFA_fState14Output1Conf, DFA_fState14Output2Conf, DFA_fState14Output3Conf, DFA_fState14Output4Conf, },
    { DFA_fState15Output1Conf, DFA_fState15Output2Conf, DFA_fState15Output3Conf, DFA_fState15Output4Conf, },
    { DFA_fState16Output1Conf, DFA_fState16Output2Conf, DFA_fState16Output3Conf, DFA_fState16Output4Conf, },
    // parameter index index will not fit in one memory block for 64 DFAs
};
const uint16_t DfaChannel::_outputValuePRI[DFA_DEF_STATES_COUNT][DFA_DEF_OUTPUTS_COUNT] = {
    // TODO ensure same position of all Outputs
    { DFA_fState01Output1TypeDpt1, DFA_fState01Output2TypeDpt1, DFA_fState01Output3TypeDpt1, DFA_fState01Output4TypeDpt1, },
    { DFA_fState02Output1TypeDpt1, DFA_fState02Output2TypeDpt1, DFA_fState02Output3TypeDpt1, DFA_fState02Output4TypeDpt1, },
    { DFA_fState03Output1TypeDpt1, DFA_fState03Output2TypeDpt1, DFA_fState03Output3TypeDpt1, DFA_fState03Output4TypeDpt1, },
    { DFA_fState04Output1TypeDpt1, DFA_fState04Output2TypeDpt1, DFA_fState04Output3TypeDpt1, DFA_fState04Output4TypeDpt1, },
    { DFA_fState05Output1TypeDpt1, DFA_fState05Output2TypeDpt1, DFA_fState05Output3TypeDpt1, DFA_fState05Output4TypeDpt1, },
    { DFA_fState06Output1TypeDpt1, DFA_fState06Output2TypeDpt1, DFA_fState06Output3TypeDpt1, DFA_fState06Output4TypeDpt1, },
    { DFA_fState07Output1TypeDpt1, DFA_fState07Output2TypeDpt1, DFA_fState07Output3TypeDpt1, DFA_fState07Output4TypeDpt1, },
    { DFA_fState08Output1TypeDpt1, DFA_fState08Output2TypeDpt1, DFA_fState08Output3TypeDpt1, DFA_fState08Output4TypeDpt1, },
    { DFA_fState09Output1TypeDpt1, DFA_fState09Output2TypeDpt1, DFA_fState09Output3TypeDpt1, DFA_fState09Output4TypeDpt1, },
    { DFA_fState10Output1TypeDpt1, DFA_fState10Output2TypeDpt1, DFA_fState10Output3TypeDpt1, DFA_fState10Output4TypeDpt1, },
    { DFA_fState11Output1TypeDpt1, DFA_fState11Output2TypeDpt1, DFA_fState11Output3TypeDpt1, DFA_fState11Output4TypeDpt1, },
    { DFA_fState12Output1TypeDpt1, DFA_fState12Output2TypeDpt1, DFA_fState12Output3TypeDpt1, DFA_fState12Output4TypeDpt1, },
    { DFA_fState13Output1TypeDpt1, DFA_fState13Output2TypeDpt1, DFA_fState13Output3TypeDpt1, DFA_fState13Output4TypeDpt1, },
    { DFA_fState14Output1TypeDpt1, DFA_fState14Output2TypeDpt1, DFA_fState14Output3TypeDpt1, DFA_fState14Output4TypeDpt1, },
    { DFA_fState15Output1TypeDpt1, DFA_fState15Output2TypeDpt1, DFA_fState15Output3TypeDpt1, DFA_fState15Output4TypeDpt1, },
    { DFA_fState16Output1TypeDpt1, DFA_fState16Output2TypeDpt1, DFA_fState16Output3TypeDpt1, DFA_fState16Output4TypeDpt1, },
    // parameter index index will not fit in one memory block for 64 DFAs
};

// TODO calculate index; expected distance should be protected by compile error
// Define (relative) parameter address-index for next state by current state and input
const uint16_t DfaChannel::_transPRI[DFA_DEF_STATES_COUNT][DFA_DEF_INPUTS_COUNT] = {
    {DFA_fTransState01Input1, DFA_fTransState01Input2, DFA_fTransState01Input3, DFA_fTransState01Input4, DFA_fTransState01Input5, DFA_fTransState01Input6, DFA_fTransState01Input7, DFA_fTransState01Input8},
    {DFA_fTransState02Input1, DFA_fTransState02Input2, DFA_fTransState02Input3, DFA_fTransState02Input4, DFA_fTransState02Input5, DFA_fTransState02Input6, DFA_fTransState02Input7, DFA_fTransState02Input8},
    {DFA_fTransState03Input1, DFA_fTransState03Input2, DFA_fTransState03Input3, DFA_fTransState03Input4, DFA_fTransState03Input5, DFA_fTransState03Input6, DFA_fTransState03Input7, DFA_fTransState03Input8},
    {DFA_fTransState04Input1, DFA_fTransState04Input2, DFA_fTransState04Input3, DFA_fTransState04Input4, DFA_fTransState04Input5, DFA_fTransState04Input6, DFA_fTransState04Input7, DFA_fTransState04Input8},
    {DFA_fTransState05Input1, DFA_fTransState05Input2, DFA_fTransState05Input3, DFA_fTransState05Input4, DFA_fTransState05Input5, DFA_fTransState05Input6, DFA_fTransState05Input7, DFA_fTransState05Input8},
    {DFA_fTransState06Input1, DFA_fTransState06Input2, DFA_fTransState06Input3, DFA_fTransState06Input4, DFA_fTransState06Input5, DFA_fTransState06Input6, DFA_fTransState06Input7, DFA_fTransState06Input8},
    {DFA_fTransState07Input1, DFA_fTransState07Input2, DFA_fTransState07Input3, DFA_fTransState07Input4, DFA_fTransState07Input5, DFA_fTransState07Input6, DFA_fTransState07Input7, DFA_fTransState07Input8},
    {DFA_fTransState08Input1, DFA_fTransState08Input2, DFA_fTransState08Input3, DFA_fTransState08Input4, DFA_fTransState08Input5, DFA_fTransState08Input6, DFA_fTransState08Input7, DFA_fTransState08Input8},
    {DFA_fTransState09Input1, DFA_fTransState09Input2, DFA_fTransState09Input3, DFA_fTransState09Input4, DFA_fTransState09Input5, DFA_fTransState09Input6, DFA_fTransState09Input7, DFA_fTransState09Input8},
    {DFA_fTransState10Input1, DFA_fTransState10Input2, DFA_fTransState10Input3, DFA_fTransState10Input4, DFA_fTransState10Input5, DFA_fTransState10Input6, DFA_fTransState10Input7, DFA_fTransState10Input8},
    {DFA_fTransState11Input1, DFA_fTransState11Input2, DFA_fTransState11Input3, DFA_fTransState11Input4, DFA_fTransState11Input5, DFA_fTransState11Input6, DFA_fTransState11Input7, DFA_fTransState11Input8},
    {DFA_fTransState12Input1, DFA_fTransState12Input2, DFA_fTransState12Input3, DFA_fTransState12Input4, DFA_fTransState12Input5, DFA_fTransState12Input6, DFA_fTransState12Input7, DFA_fTransState12Input8},
    {DFA_fTransState13Input1, DFA_fTransState13Input2, DFA_fTransState13Input3, DFA_fTransState13Input4, DFA_fTransState13Input5, DFA_fTransState13Input6, DFA_fTransState13Input7, DFA_fTransState13Input8},
    {DFA_fTransState14Input1, DFA_fTransState14Input2, DFA_fTransState14Input3, DFA_fTransState14Input4, DFA_fTransState14Input5, DFA_fTransState14Input6, DFA_fTransState14Input7, DFA_fTransState14Input8},
    {DFA_fTransState15Input1, DFA_fTransState15Input2, DFA_fTransState15Input3, DFA_fTransState15Input4, DFA_fTransState15Input5, DFA_fTransState15Input6, DFA_fTransState15Input7, DFA_fTransState15Input8},
    {DFA_fTransState16Input1, DFA_fTransState16Input2, DFA_fTransState16Input3, DFA_fTransState16Input4, DFA_fTransState16Input5, DFA_fTransState16Input6, DFA_fTransState16Input7, DFA_fTransState16Input8},
};

// TODO calculate index; expected distance should be protected by compile error
// Define (relative) parameter address-index for timeout duration and timeout state
const DfaStateTimeoutParamRelIdx DfaChannel::_timeoutPRI[DFA_DEF_STATES_COUNT] = {
    {DFA_fState01TimeoutTime, DFA_fTransState01Timeout},
    {DFA_fState02TimeoutTime, DFA_fTransState02Timeout},
    {DFA_fState03TimeoutTime, DFA_fTransState03Timeout},
    {DFA_fState04TimeoutTime, DFA_fTransState04Timeout},
    {DFA_fState05TimeoutTime, DFA_fTransState05Timeout},
    {DFA_fState06TimeoutTime, DFA_fTransState06Timeout},
    {DFA_fState07TimeoutTime, DFA_fTransState07Timeout},
    {DFA_fState08TimeoutTime, DFA_fTransState08Timeout},
    {DFA_fState09TimeoutTime, DFA_fTransState09Timeout},
    {DFA_fState10TimeoutTime, DFA_fTransState10Timeout},
    {DFA_fState11TimeoutTime, DFA_fTransState11Timeout},
    {DFA_fState12TimeoutTime, DFA_fTransState12Timeout},
    {DFA_fState13TimeoutTime, DFA_fTransState13Timeout},
    {DFA_fState14TimeoutTime, DFA_fTransState14Timeout},
    {DFA_fState15TimeoutTime, DFA_fTransState15Timeout},
    {DFA_fState16TimeoutTime, DFA_fTransState16Timeout},
};

DfaChannel::DfaChannel(uint8_t index)
{
    _channelIndex = index;
}

const std::string DfaChannel::name()
{
    return "DFA-Channel";
}

void DfaChannel::setup()
{
    _channelActive = (ParamDFA_fSwitchMaster == 0b01);
    logDebugP("setup (act=%d dly=%ds run=%d)", _channelActive, ParamDFA_fChannelDelayTimeMS / 1000, ParamDFA_fSwitchByKo != 0b00);

    if (_channelActive)
    {
        initInputConfig();

        // TODO add state restore

        _processStartupDelay = true;
        _startupDelayBegin_ms = millis();

        _firstState = DFA_STATE_PARAM_XOR ^ ParamDFA_fStateStart;
        // _firstStateTimeoutDelay_ms = getStateTimeoutDelay_ms(_firstState);
    }
}

void DfaChannel::initInputConfig()
{
    // TODO check moving
    for (size_t i = 0; i < DFA_DEF_INPUTS_COUNT; i++)
    {
        // TODO check shift and mark for all
        const uint8_t inputConf = ((knx.paramByte(DFA_ParamCalcIndex(_inputConfPRI[i])) & DFA_fInputSymbol1KoMask) >> DFA_fInputSymbol1KoShift);
        if (inputConf == 0)
        {
            _inputs[i].trigger = 0b00;
            _inputs[i].koNumber = 0;
        }
        else
        {
            _inputs[i].trigger = ((knx.paramByte(DFA_ParamCalcIndex(_inputTriggerPRI[i])) & DFA_fInputSymbol1Value) >> DFA_fInputSymbol1ValueShift);
            switch (inputConf)
            {
                case 1: // Eigenes KO
                    _inputs[i].koNumber = DFA_KoCalcNumber(_inputKo[i]);
                    break;
                case 3: // Logik-Ausgang
                    {
                        // const u_int16_t logicOutputNumber = knx.paramWord(DFA_ParamCalcIndex(_inputConfNumberPRI[i]));

                        // overlay for _channelIndex!
                        const u_int16_t _channelIndex = knx.paramWord(DFA_ParamCalcIndex(_inputConfNumberPRI[i]));
                        _inputs[i].koNumber = LOG_ParamCalcIndex(LOG_KoKOfO);
                    }
                    break;
                case 2: // Bestehendes KO
                    _inputs[i].koNumber = knx.paramWord(DFA_ParamCalcIndex(_inputConfNumberPRI[i]));
                    break;
                default:
                    // TODO check
                    break;
            }
        }
        /* code */
    }
}

void DfaChannel::loop()
{
    // !_channelActive will result in _running=false, so no need for checking
    if (_running)
    {
        if (_stateTimeoutDelay_ms > 0 && delayCheckMillis(_stateTimeoutBegin_ms, _stateTimeoutDelay_ms))
        {
            // logDebugP("timeout reached (@%d+%dms >=%d)", _stateTimeoutBegin_ms, _stateTimeoutDelay_ms, millis());

            // TODO check creation of method transferTimeout()
            setState(getTimeoutState(_state));
        }
    }
    else if (_processStartupDelay && delayCheckMillis(_startupDelayBegin_ms, ParamDFA_fChannelDelayTimeMS))
    {
        _processStartupDelay = false;

        // set to running. This includes setting the start state
        setRunning(ParamDFA_fSwitchByKo != 0b00, true);
    }
}

void DfaChannel::processInputKo(GroupObject &ko)
{
    if (!_channelActive)
        return; // ignore inactive channel

    // TODO optimize check of ko-Number
    // TODO add inputs of other ko-Number

    const uint16_t koNumber = ko.asap();

    if (koNumber == DFA_KoCalcNumber(DFA_KoKOfRunSet))
    {
        logDebugP("processInputKo set running");
        setRunning(ko.value(DPT_Start));
    }

    // TODO define expected behaviour when changed before; will be relevant for inputs by KO-Index
    if (_running)
    {
        if (koNumber == DFA_KoCalcNumber(DFA_KoKOfStateI))
        {
            // input only for visible KO, so no need to check:
            // .. && ParamDFA_fStateSetting==0b01
            logDebugP("processInputKo set state (separate)");
            setState(ko.value(DPT_SceneNumber));
        }
        else if (koNumber == DFA_KoCalcNumber(DFA_KoKOfState) && ParamDFA_fStateSetting == 0b10)
        {
            // TODO ensure not processing when result of own sending!
            logDebugP("processInputKo set state (combined)");
            setState(ko.value(DPT_SceneNumber));
        }
        else if (ko.valueSize() == 1) // TODO check if adequate
        {
            // const KNXValue value = ko.value(DPT_Switch);
            const bool value = ko.value(DPT_Switch);

            // check regular inputs
            for (size_t i = 0; i < DFA_DEF_INPUTS_COUNT; i++)
            {
                if (koNumber == _inputs[i].koNumber)
                {
                    const bool triggered = _inputs[i].trigger & (1 << value);
                    if (triggered)
                    {
                        logDebugP("triggered input%d", i);
                        transfer(i);

                        // only one!
                        break;
                    }
                }
            }
        }
    }
}

void DfaChannel::setRunning(const bool requestRun, const bool first /*= false*/)
{
    bool send = first;
    if (_running != requestRun)
    {
        if (!requestRun)
        {
            // suspend
            logDebugP("suspend");
            _pauseBegin = millis();
        }
        else if (_state == DFA_STATE_UNDEFINED)
        {
            // first activation
            logDebugP("first activation");
            setState(_firstState);
            if (ParamDFA_fStateRestore & 0b10 && _firstStateTimeoutDelay_ms > 0)
            {
                // TODO check refactoring!
                if (_firstStateTimeoutDelay_ms > ParamDFA_fChannelDelayTimeMS)
                {
                    logDebugP("restore with shortened delay");
                    _stateTimeoutDelay_ms = _firstStateTimeoutDelay_ms - ParamDFA_fChannelDelayTimeMS;
                }
                else
                {
                    logDebugP("restore with ended delay");
                    _stateTimeoutDelay_ms = 1;
                }
            }
        }
        else
        {
            // resume & increase delay by pause time
            logDebugP("resume after sleeping %dms", (millis() - _pauseBegin));
            _stateTimeoutBegin_ms += (millis() - _pauseBegin);
        }
        _running = requestRun;
        send = true;
    }

    if (send && (ParamDFA_fSwitchByKo < 0b10))
        KoDFA_KOfRunning.value(_running, DPT_State);
}

uint32_t DfaChannel::getStateTimeoutDelay_ms(const uint8_t state)
{
    // TODO ensure returning 0 for undefined timeout state
    return paramDelay(knx.paramWord(DFA_ParamCalcIndex(_timeoutPRI[state].delay)));
}

uint8_t DfaChannel::getTimeoutState(const uint8_t state)
{
    return DFA_STATE_PARAM_XOR ^ knx.paramByte(DFA_ParamCalcIndex(_timeoutPRI[state].state));
}

bool DfaChannel::isValidState(const uint8_t state)
{
    return state < DFA_DEF_STATES_COUNT;
}

void DfaChannel::setState(const uint8_t nextState)
{
    // logDebugP("setState %d->%d", _state, nextState);
    if (nextState < DFA_DEF_STATES_COUNT)
    {
        _state = nextState;
        // reset timeout
        _stateTimeoutDelay_ms = getStateTimeoutDelay_ms(nextState);
        _stateTimeoutBegin_ms = millis();

        // send state
        KoDFA_KOfState.value(_state, DPT_SceneNumber);

        // if (_stateTimeoutDelay_ms > 0)
        //     logDebugP("  with timeout state %d after %dms", getTimeoutState(nextState), _stateTimeoutDelay_ms);

        // send output values
        sendValues();
    }
}

void DfaChannel::sendOutput(const uint8_t outputIndex, const KNXValue &value, const Dpt &type, const uint8_t outputStateSend)
{
    GroupObject ko = knx.getGroupObject(DFA_KoCalcNumber(_outputKoPRI[outputIndex]));
    if (outputStateSend == OUTPUT_SEND_ALWAYS)
    {
        ko.value(value, type);
    }
    else if (ko.valueNoSendCompare(value, type))
    {
        // write changed value only; given: /* outputStateSend == OUTPUT_SEND_CHANGE && */ 
        ko.objectWritten();
    }
}

void DfaChannel::sendValues()
{
    for (uint8_t i = 0; i < DFA_DEF_OUTPUTS_COUNT; i++)
    {
        const uint8_t outputType = knx.paramByte(DFA_ParamCalcIndex(_outputDptPRI[i]));
        // output is active?
        if (outputType != 0)
        {
            const uint8_t outputStateSend = knx.paramByte(DFA_ParamCalcIndex(_outputSendPRI[_state][i])) >> 6;
            // output has value for state?
            if (outputStateSend)
            {
                const uint32_t pIdxValue = DFA_ParamCalcIndex(_outputValuePRI[_state][i]);

                // set value based on dpt
                switch (outputType)
                {
                    case OUTPUT_TYPE_DPT1:
                        {
                            // TODO FIXME Mask
                            // const KNXValue value = ((bool)(knx.paramByte(pIdxValue) & LOG_DFA_f1State01Output1TypeDpt1Mask));

                            // works, as long as using same location as other dpt values
                            sendOutput(i, (knx.paramByte(pIdxValue) != 0), DPT_Switch, outputStateSend);
                        }
                        break;
                    case OUTPUT_TYPE_DPT2:
                        // TODO check using mask!
                        sendOutput(i, knx.paramByte(pIdxValue), DPT_Switch_Control, outputStateSend);
                        break;
                    case OUTPUT_TYPE_DPT5:
                        sendOutput(i, knx.paramByte(pIdxValue), DPT_DecimalFactor, outputStateSend);
                        break;
                    case OUTPUT_TYPE_DPT5001:
                        sendOutput(i, knx.paramByte(pIdxValue), DPT_Scaling, outputStateSend);
                        break;                                                
                    case OUTPUT_TYPE_DPT6:
                        sendOutput(i, knx.paramSignedByte(pIdxValue), DPT_Value_1_Count, outputStateSend);
                        break;
                    case OUTPUT_TYPE_DPT7:
                        sendOutput(i, knx.paramWord(pIdxValue), DPT_Value_2_Ucount, outputStateSend);
                        break;
                    case OUTPUT_TYPE_DPT8:
                        sendOutput(i, knx.paramWord(pIdxValue), DPT_Value_2_Count, outputStateSend);
                        break;
                    case OUTPUT_TYPE_DPT9:
                        sendOutput(i, knx.paramFloat(pIdxValue, Float_Enc_DPT9), DPT_Value_Temp, outputStateSend);
                        break;
                    case OUTPUT_TYPE_DPT12:
                        sendOutput(i, knx.paramInt(pIdxValue), DPT_Value_4_Ucount, outputStateSend);
                        break;
                    case OUTPUT_TYPE_DPT13:
                        sendOutput(i, knx.paramInt(pIdxValue), DPT_Value_4_Count, outputStateSend);
                        break;
                    case OUTPUT_TYPE_DPT14:
                        sendOutput(i, knx.paramFloat(pIdxValue, Float_Enc_IEEE754Double), DPT_Value_Absolute_Temperature, outputStateSend);
                        break;
                    case OUTPUT_TYPE_DPT16:
                        sendOutput(i, (char *)knx.paramData(pIdxValue), DPT_String_8859_1, outputStateSend);
                        break;
                    case OUTPUT_TYPE_DPT17:
                        sendOutput(i, knx.paramByte(pIdxValue), DPT_SceneNumber, outputStateSend);
                        break;
                    case OUTPUT_TYPE_DPT232:
                        // TODO FIXME Mask
                        sendOutput(i, knx.paramInt(pIdxValue) >> 8, DPT_Colour_RGB, outputStateSend);
                        break;
                    default:
                        // TODO check handling undefined cases
                        break;
                }
            }
        }
    }
}

void DfaChannel::transfer(const uint8_t input)
{
    if (_state < DFA_DEF_STATES_COUNT && input < DFA_DEF_INPUTS_COUNT)
    {
        const uint16_t nextStateParamIdx = DFA_ParamCalcIndex(_transPRI[_state][input]);
        const uint8_t nextState = DFA_STATE_PARAM_XOR ^ knx.paramByte(nextStateParamIdx);

        logDebugP("transfer(%d,%d)->%d", _state, input, nextState);
        if (isValidState(nextState))
            setState(nextState);
        // ignore undefined transition
    }
}

void DfaChannel::endTimeout()
{
    if (_stateTimeoutDelay_ms > 0)
    {
        logDebugP("change timeout %d -> 1ms", _stateTimeoutDelay_ms);

        // set to shortest possible valid timeout of 1ms; might result in up to 1ms delay until end, when executed directly after state change
        _stateTimeoutDelay_ms = 1;
    }
}

void DfaChannel::save()
{
    const uint8_t conf = _channelActive << 7 | _running << 6 | ParamDFA_fStateRestore;
    openknx.flash.writeByte(conf);
    openknx.flash.writeByte(_state);

    // futureDelay = _stateTimeoutBegin_ms + _stateTimeoutDelay_ms - millis();
    // futureDelay = (_stateTimeoutBegin_ms - millis()) + _stateTimeoutDelay_ms;
    // futureDelay = _stateTimeoutDelay_ms - (millis() - _stateTimeoutBegin_ms)
    // TODO check for correct handling of overflow
    const uint32_t futureDelay = _stateTimeoutDelay_ms - (millis() - _stateTimeoutBegin_ms);
    openknx.flash.writeInt(futureDelay);

    logDebugP("saved c=%2x s=%2x t=%u b=%u f=%u", conf, _state, _stateTimeoutDelay_ms, _stateTimeoutBegin_ms, futureDelay);
}

void DfaChannel::restore()
{
    const uint8_t conf = openknx.flash.readByte();
    const uint8_t state = openknx.flash.readByte();
    const uint8_t timeout = openknx.flash.readInt();
    logDebugP("restored conf=%d state=%d timeout=%d", conf, state, timeout);

    if (ParamDFA_fStateRestore && (conf & 0b11))
    {
        _firstState = state;
        _firstStateTimeoutDelay_ms = timeout;
    }
}

bool DfaChannel::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (cmd.substr(0, 3) == "dfa")
    {
        // TODO Check and refine command definitions after first tests and extension!
        if (cmd.length() == 14 && cmd.substr(5, 9) == " timeout!")
        {
            uint16_t channelIdx = std::stoi(cmd.substr(3, 2)) - 1;
            if (channelIdx == _channelIndex)
            {
                logDebugP("timeout end now!");
                // TODO define behaviour when disabled
                endTimeout();
                return true;
            }
        }
    }
    return false;
}
