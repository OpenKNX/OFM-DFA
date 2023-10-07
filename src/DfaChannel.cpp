// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023 Cornelius Koepp

#include "DfaChannel.h"

// TODO calculate index; expected distance should be protected by compile error
// Define (relative) parameter address-index for next state by current state and input
const uint8_t DfaChannel::_transPRI[DFA_DEF_STATES_COUNT][DFA_DEF_INPUTS_COUNT] = {
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
    logDebugP("setup (act=%d run=%d)", _channelActive, ParamDFA_fSwitchByKo != 0b00);
    if (!_channelActive)
        return; // ignore inactive channel

    // TODO define expected timing behaviour for first state with timeout
    // TODO add state restore

    // set to running. This includes setting the start state
    setRunning(ParamDFA_fSwitchByKo != 0b00, true);
}

void DfaChannel::loop()
{
    // !_channelActive will result in _running=false, so no need for checking
    if (_running && _stateTimeoutDelay_ms > 0 && delayCheckMillis(_stateTimeoutBegin_ms, _stateTimeoutDelay_ms))
    {
        // logDebugP("timeout reached (@%d+%dms >=%d)", _stateTimeoutBegin_ms, _stateTimeoutDelay_ms, millis());
        setState(getTimeoutState(_state));
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
            logDebugP("processInputKo set state");
            // TODO add conditions / depend on configuration
            setState(ko.value(DPT_SceneNumber));
        }
        else if (koNumber == DFA_KoCalcNumber(DFA_KoKOfInput1))
        {
            logDebugP("processInputKo input1");
            transfer(ko.value(DPT_Bool) ? 0 : 1);
        }
        else if (koNumber == DFA_KoCalcNumber(DFA_KoKOfInput2))
        {
            logDebugP("processInputKo input2");
            transfer(ko.value(DPT_Bool) ? 2 : 3);
        }
        else if (koNumber == DFA_KoCalcNumber(DFA_KoKOfInput3))
        {
            logDebugP("processInputKo input3");
            transfer(ko.value(DPT_Bool) ? 4 : 5);
        }
        else if (koNumber == DFA_KoCalcNumber(DFA_KoKOfInput4))
        {
            logDebugP("processInputKo input4");
            transfer(ko.value(DPT_Bool) ? 6 : 7);
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
            setState(ParamDFA_fStateStart);
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
    return knx.paramByte(DFA_ParamCalcIndex(_timeoutPRI[state].state));
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
    }
}

void DfaChannel::transfer(const uint8_t input)
{
    if (_state < DFA_DEF_STATES_COUNT && input < DFA_DEF_INPUTS_COUNT)
    {
        const uint16_t nextStateParamIdx = DFA_ParamCalcIndex(_transPRI[_state][input]);
        const uint8_t nextState = knx.paramByte(nextStateParamIdx);

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
