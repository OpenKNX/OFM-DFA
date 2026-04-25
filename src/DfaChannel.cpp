// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2026 Cornelius Koepp

#include "DfaChannelConfigHelper.h"
#include "DfaChannel.h"
#ifdef OPENKNX_DEBUG
    #include "DfaOutputConfigHelper.h"
#endif

#pragma region "DFA_CHANNEL_BASE"

DfaChannel::DfaChannel(uint8_t index)
{
    _channelIndex = index;
    for (uint8_t i = 0; i < DFA_DEF_OUTPUTS_COUNT; i++)
    {
        _outputs[i] = new DfaOutput(_channelIndex, i);
    }
}

const std::string DfaChannel::name()
{
    return "DFA-Channel";
}

#pragma endregion "DFA_CHANNEL_BASE"

void DfaChannel::setup()
{
    _channelActive = (ParamDFA_aActive == 0b01);
    if (_channelActive)
    {
        logDebugP("setup(delay=%ds run=%d)", _channelActive, ParamDFA_aStartupDelayTimeMS / 1000, ParamDFA_aStartPause != 2);
        logIndentUp();

        initInputConfig();

        // TODO QS: check first state handling, especially sending
        _firstState = ParamDFA_az0 - 1;
        // _firstStateTimeoutDelay_ms = getStateTimeoutDelay_ms(_firstState);

        // could be overwritten in restore
        _firstRunning = (ParamDFA_aStartPause != 2);

        // actual starting in processAfterStartupDelay() ...
        logIndentDown();
    }
}

#pragma region "DFA_CHANNEL_INPUT_INIT"

uint16_t DfaChannel::getLogicOutputKoNumber(const uint8_t /* intended overlapping name for usage in macro! */ _channelIndex)
{
    return LOG_KoCalcNumber(LOG_KoKOfO);
}

uint16_t DfaChannel::getInputKoNumber(const uint8_t input)
{
    if (input < DFA_DEF_INPUTS_WITH_T_COUNT)
    {
        const uint8_t inputConf = _ParamDFA_aSymbol___Input(input);
        // logDebugP("  get ko for input=%i -> conf=%i", input, inputConf);
        switch (inputConf)
        {
            case 1: // Own KO
                return _KoDFA_KOaInput___(input);
            case 3: // Logic-Output (KO)
                {
                    const u_int16_t logicNumber = _ParamDFA_aSymbol___LogicNumber(input);
                    if (logicNumber > LOG_ChannelCount || logicNumber > 99)
                    {
                        logErrorP("Invalid LOG-channel %u for input %u", logicNumber, input);
                        return 0;
                    }
                    return getLogicOutputKoNumber(logicNumber - 1);
                }
            case 2: // Existing KO
                return _ParamDFA_aSymbol___KoNumber(input);
        }
    }
    // default, including case 0 (disabled)
    return 0;
}

void DfaChannel::initNonPairedInput(const uint8_t i)
{
    const uint16_t koNumber = getInputKoNumber(i);
    _inputs[i].koNumber = koNumber;
    _inputs[i].trigger = (koNumber > 0) ? static_cast<DfaInputTrigger>(_ParamDFA_aSymbol___Trigger(i)) : DfaInputTrigger::disabled;
    if (koNumber != 0 || _inputs[i].trigger != DfaInputTrigger::disabled)
    {
        logDebugP("separate: %d ko=%-4i trigger=%c%c", i, koNumber, (static_cast<uint8_t>(_inputs[i].trigger) & 0b10) ? '1' : '_', (static_cast<uint8_t>(_inputs[i].trigger) & 0b01) ? '0' : '_');
    }
}

void DfaChannel::initInputConfig()
{
    // inputs for symbols A..H (can be defined in pairs A/B, C/D, E/F, G/H)
    const bool combined[DFA_DEF_INPUTS_COUNT / 2] = {ParamDFA_aSymbolPairAB, ParamDFA_aSymbolPairCD, ParamDFA_aSymbolPairEF, ParamDFA_aSymbolPairGH};
    for (uint8_t iPair = 0; iPair < DFA_DEF_INPUTS_COUNT / 2; iPair++)
    {
        const uint8_t iFirst = iPair * 2;
        const uint8_t iSecond = iFirst + 1;
        logDebugP("input-pair %d, first=%d, second=%d; ispair=%d", iPair, iFirst, iSecond, combined[iPair]);
        if (combined[iPair])
        {
            // one shared input for 2 symbols
            const uint16_t koNumber = getInputKoNumber(iFirst);

            _inputs[iFirst].koNumber = koNumber;
            _inputs[iFirst].trigger = (koNumber > 0) ? DfaInputTrigger::only1 : DfaInputTrigger::disabled;
            _inputs[iSecond].koNumber = koNumber;
            _inputs[iSecond].trigger = (koNumber > 0) ? DfaInputTrigger::only0 : DfaInputTrigger::disabled;
        }
        else
        {
            // separate input for 2 symbols
            initNonPairedInput(iFirst);
            initNonPairedInput(iSecond);
        }
    }

    // input for symbol T (not part of a pair)
    initNonPairedInput(DFA_INPUT_SYMBOL_T);

#ifdef OPENKNX_DEBUG
    for (size_t i = 0; i < DFA_DEF_INPUTS_WITH_T_COUNT; i++)
    {
        if (_inputs[i].koNumber != 0 || _inputs[i].trigger != DfaInputTrigger::disabled)
        {
            logDebugP("input[%d]: ko=%-4d trigger=%c%c", i, _inputs[i].koNumber, (static_cast<uint8_t>(_inputs[i].trigger) & 0b10) ? '1' : '_', (static_cast<uint8_t>(_inputs[i].trigger) & 0b01) ? '0' : '_');
        }
    }
#endif
}

#pragma endregion "DFA_CHANNEL_INPUT_INIT"

void DfaChannel::processAfterStartupDelay()
{
    // start after device global delay
    if (_channelActive)
    {
        logDebugP("processAfterStartupDelay");
        _processStartup = true;
        _startupDelayBegin_ms = millis();
    }
}

void DfaChannel::loop()
{
    // !_channelActive will result in _running=false, so no need for checking
    if (_running)
    {
        if (_stateTimeoutDelay_ms > 0 && delayCheckMillis(_stateTimeoutBegin_ms, _stateTimeoutDelay_ms))
        {
            // prio 1: timeout of state => transfer to following state

            // logDebugP("timeout reached (@%d+%dms >=%d)", _stateTimeoutBegin_ms, _stateTimeoutDelay_ms, millis());
            transfer(DFA_INPUT_SYMBOL_T);
        }
        else
        {
            // prio 2: cyclic sending of outputs
            for (uint8_t i = 0; i < DFA_DEF_OUTPUTS_COUNT; i++)
            {
                _outputs[i]->loop();
            }
        }
    }
    else if (_processStartup && delayCheckMillis(_startupDelayBegin_ms, ParamDFA_aStartupDelayTimeMS))
    {
        _processStartup = false;

        // set to running. This includes setting the start state
        setRunning(_firstRunning, true);
    }
}

void DfaChannel::processInputKo(GroupObject &ko)
{
    if (!_channelActive)
        return; // ignore inactive channel

    // TODO optimize check of ko-Number

    const uint16_t koNumber = ko.asap();

    // TODO define behaviour within startup delay!
    if (koNumber == DFA_KoCalcNumber(DFA_KoKOaRunSet))
    {
        logDebugP("processInputKo set running");
        setRunning(ko.value(DPT_Start));
    }
    // TODO define expected behaviour when changed before; will be relevant for inputs by KO-Index
    if (_running)
    {
        if (koNumber == DFA_KoCalcNumber(DFA_KoKOaStateI))
        {
            // input only for visible KO, so no need to check:
            // .. && ParamDFA_aStateSetting==0b01
            logDebugP("processInputKo set state (separate); StateSetting=%d, ..Same=%d", ParamDFA_aStateSetting, ParamDFA_aStateSettingSame);
            transfer((uint8_t)ko.value(DPT_SceneNumber) | 0x80); // setting the same state is handled based on parameters
        }
        else if (koNumber == DFA_KoCalcNumber(DFA_KoKOaState) && ParamDFA_aStateSetting == 0b10)
        {
            logDebugP("processInputKo set state (combined); StateSetting=%d, ..Same=%d", ParamDFA_aStateSetting, ParamDFA_aStateSettingSame);

            const uint8_t nextState = ko.value(DPT_SceneNumber);
            if (_state != nextState) // ignore same state to prevent processing the result of own sending to shared KO
            {
                transfer(nextState | 0x80);
            }

            // ensure KO has the value of current state!
            // TODO restore KO value for invalid state only
            ko.valueNoSend(_state, DPT_SceneNumber);
        }
        else if (ko.valueSize() == 1) // TODO check if adequate, or add support for other input types
        {
            const bool value = ko.value(DPT_Switch);

            // check (new or existing) inputs based on ko-numbers
            for (size_t i = 0; i < DFA_DEF_INPUTS_WITH_T_COUNT; i++)
            {
                if (koNumber == _inputs[i].koNumber)
                {
                    const bool triggered = static_cast<uint8_t>(_inputs[i].trigger) & (1 << value);
                    logDebugP("processInputKo input=%d (ko=%d; triggered=%d)", i + 1, koNumber, triggered);
                    if (triggered)
                    {
                        transfer(i);
                        break; // only one! (Same input should NOT generate multiple symbols)
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
            transfer(DFA_INPUT_SYMBOL_START); // set the start-state

            logDebugP("restore: _stateTimeoutDelay_ms=%d ParamDFA_aStateRestore=%d _firstStateTimeoutDelay_ms=%d ParamDFA_aChannelDelayTimeMS=%d", _stateTimeoutDelay_ms, ParamDFA_aStateRestore, _firstStateTimeoutDelay_ms, ParamDFA_aStartupDelayTimeMS);
            // TODO check usage of _firstStateTimeoutDelay_ms, this is the remaining delay and should be renamed
            // _stateTimeoutDelay_ms is set to current's state timeout in setState(..)
            if (_stateTimeoutDelay_ms > 0 && (ParamDFA_aStateRestore & 0b10) && _firstStateTimeoutDelay_ms > 0)
            {
                // remaining timeout starts with device;
                // this will already add an unknown delay caused by downtime of unknown length,
                // which should be solved by (re)store the absolute timeout end
                if (_firstStateTimeoutDelay_ms > _stateTimeoutBegin_ms)
                {
                    logDebugP("restore with shortened delay");
                    // TODO check/define behaviour when timeout configuration was changed, and is shorter than saved remaining time
                    _stateTimeoutDelay_ms = _firstStateTimeoutDelay_ms - _stateTimeoutBegin_ms;
                }
                else
                {
                    // TODO check direct restore of timeout-state, to reduce sending
                    logDebugP("restore with ended delay");
                    _stateTimeoutDelay_ms = 1;
                }
            }
            // all following state-updates are not part of restore => no special handling
            _restoreOutputs = false;
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

    if (send && (ParamDFA_aStartPause != 0))
        KoDFA_KOaRunning.value(_running, DPT_State);
}

uint32_t DfaChannel::getStateTimeoutDelay_ms(const uint8_t state)
{
    return (state < DFA_DEF_STATES_COUNT) ? _ParamDFA_ad___TTimeMS(state) : 0;
}

bool DfaChannel::isValidState(const uint8_t state)
{
    return state < DFA_DEF_STATES_COUNT;
}

void DfaChannel::setState(const uint8_t nextState, const DfaDirectSetSame sameStateBehaviour /*= DfaDirectSetSame::timeout_restart*/)
{
    if (isValidState(nextState))
    {
        const bool stateChanged = (_state != nextState);
        if (!stateChanged && sameStateBehaviour == DfaDirectSetSame::ignore)
            return;

        _state = nextState;
        if (stateChanged || sameStateBehaviour == DfaDirectSetSame::timeout_restart)
        {
            // reset timeout
            _stateTimeoutDelay_ms = getStateTimeoutDelay_ms(nextState);
            resetTimeout();
        }

        // send state
        GroupObject *ko = &KoDFA_KOaState;
        if (ko->valueNoSendCompare(_state, DPT_SceneNumber))
            ko->objectWritten();

        // if (_stateTimeoutDelay_ms > 0)
        //     logDebugP("  with timeout state %d after %dms", getTimeoutState(nextState), _stateTimeoutDelay_ms);

        for (uint8_t i = 0; i < DFA_DEF_OUTPUTS_COUNT; i++)
        {
            _outputs[i]->stateUpdate(_state, _restoreOutputs);
        }
    }
}

#pragma region "DFA_CHANNEL_TRANSFER"

/**
 * @brief Transfer the DFA to the next state based on the current state and input symbol.
 * @param input
 *  SYMBOL      : VALUE                                       > RESULT
 *  'A'..'H'    : (       0..7 )                             \
 *  'T'         : (       8    )   (DFA_INPUT_SYMBOL_T)       > (depends on defined following state or choice)
 *  '<'         : (       9    )   (possible extension)      /
 *  1..16       : (0x80 | 0..15) = 128..143                  \  set state 0..15
 *   ..32       : (0x80 |  ..31) =    ..159                   >            ..31
 *   ..64       : (0x80 |  ..63) =    ..191                  /             ..63
 *  'a'..'p'    : (0xC0 | 0..15) = 192..207                  -> (when defined and evaluated with result) set state 0..15
 *  'START'     : (0x00 | 249  )   (DFA_INPUT_SYMBOL_START)  -> set state 0..15
 */
void DfaChannel::transfer(const uint8_t input)
{
    // 1) get the next state + 2) evaluate conditional states
    uint8_t nextState = DFA_STATE_UNDEFINED;
    if (input == DFA_INPUT_SYMBOL_START) // check first, otherwise 2') could result in unexpected behaviour
    {
        logDebugP("State<z%u>: transfer(START)->int:%u", _state + 1, _firstState);
        logIndentUp();
        nextState = transferEvaluateChoiceLoop(_firstState);
        // 2') use fallback for start, when using choice evaluation without resulting state
        if (nextState == DFA_STATE_UNDEFINED)
        {
            nextState = ParamDFA_az0Fallback - 1;
            logDebugP("Start-Fallback: selected z%u", nextState + 1);
        }
    }
    else if (isValidState(_state))
    {
        nextState = transferGetNextForInput(input);
        logIndentUp();
        nextState = transferEvaluateChoiceLoop(nextState);
    }
    else
    {
        logIndentUp();
        logDebugP("State<z%u>: transfer(int:%u)->IGNORE (invalid state & no startup)", _state + 1, _state);
    }

    // 3) set the next state
    transferProcessNext(nextState);

    addHistory(input, _state); // write history with resulting state after processing
    logIndentDown();
}

uint8_t DfaChannel::transferGetNextForInput(const uint8_t input)
{
    if (input < DFA_DEF_INPUTS_WITH_T_COUNT)
    {
        // 1a) regular symbols (X_z)
        // 1b) timeout symbols (X_t) // TODO check inclusion of '<'

        // Expected Values: ETS-Param => Converted by -1
        // 0 - no following state    => 255
        // 1-16/1-32/1-64 next state => 0-15/1-31/1-63
        // 65-80 choice states a..p  => 64-79
        // 127 timeout reset         => 126

        // must be uint8_t to ensure conversion from ETS-param to required state (0x00 -> 0xff)
        const uint8_t nextState = _ParamDFA_ad___(_state, input) - 1;

        logDebugP("State<z%u>: transfer(%c)->%u", _state + 1, input == DFA_INPUT_SYMBOL_T ? 'T' : ('A' + input), nextState);
        return nextState;
    }
    else if (input & 0x80)
    {
        // 1c) special case: direct setting state (X_z) and direct setting choice-states
        const uint8_t directState = (input & 0x7F);
        if (directState < DFA_DEF_STATES_COUNT)
        {
            // direct state
            if (directState == _state && (static_cast<DfaDirectSetSame>(ParamDFA_aStateSettingSame) == DfaDirectSetSame::ignore))
            {
                logDebugP("State<z%u>: transfer(%u)->IGNORE (same state)", _state + 1, directState);
                return DFA_STATE_UNDEFINED;
            }

            logDebugP("State<z%u>: transfer(%u)->%u", _state + 1, directState, directState);
            return directState;
        }
        else if (64 <= directState && directState < 64 + DFA_DEF_CHOICESTATES_COUNT)
        {
            // direct choice-state
            logDebugP("State<z%u>: transfer(%c)->CHOICE", _state + 1, 'a' + directState - 64);
            return directState;
        }
        // NOT direct state and NOT choice state
    }
    return DFA_STATE_UNDEFINED;
}

uint8_t DfaChannel::transferEvaluateChoiceLoop(uint8_t nextState)
{
    for (uint8_t i = 0; (64 <= nextState && nextState < 64 + DFA_DEF_CHOICESTATES_COUNT); i++)
    {
        if (i >= DFA_DEF_CHOICESTATES_COUNT)
        {
            // this should NEVER happen,
            // as transferEvaluateChoice is only allowed to produce monotonic increasing choicestates
            // but failing this condition would result in infinite loop
            logErrorP("ChoiceState<?>: Too many iterations!");
            return DFA_STATE_UNDEFINED;
        }

        nextState = transferEvaluateChoice(nextState);
        // 2i) repeat until non-choice-state is reached
    }
    return nextState;
}

uint8_t DfaChannel::transferEvaluateChoice(const uint8_t nextState)
{
    // 2a) => is choice-state
    const uint8_t choiceState = nextState - 64;
    // TODO ensure allowed!
    if (choiceState >= DFA_DEF_CHOICESTATES_COUNT)
    {
        logErrorP("ChoiceState<?>: Wrong int:%u!", nextState);
        return DFA_STATE_UNDEFINED;
    }

    // 2b) get choice-state config
    // TODO ensure expected memory layout!
    const uint8_t choiceStateLogChannel = knx.paramByte(DFA_ParamCalcIndex(DFA_aCaLOG + choiceState * (DFA_aCbLOG - DFA_aCaLOG)));

    // 2c) check choice enabled
    if (choiceStateLogChannel == 0)
    {
        logInfoP("ChoiceState<%c>: Inactive!", 'a' + choiceState);
        return DFA_STATE_UNDEFINED;
    }

    // 2d) get assigned logic-channel
    const uint16_t logOutputKoNumber = getLogicOutputKoNumber(choiceStateLogChannel - 1);
    GroupObject *logOutputKo = &knx.getGroupObject(logOutputKoNumber);
    if (logOutputKo == nullptr)
    {
        logErrorP("ChoiceState<%c>: Undefined LOG[%u](KO %u)", 'a' + choiceState, choiceStateLogChannel, logOutputKoNumber);
        return DFA_STATE_UNDEFINED;
    }
    // const bool isLogicChannelEnabled = ... (Parameter calculated?)

    // 2e) check logic-channel result present
    if (logOutputKo->valueSize() != 1)
    {
        // TODO exclude all KOs of length 2 to 8 bits!
        logInfoP("ChoiceState<%c>: Invalid LOG[%u](KO %u) size %u", 'a' + choiceState, choiceStateLogChannel, logOutputKoNumber, logOutputKo->valueSize());
        return DFA_STATE_UNDEFINED;
    }
    uint8_t selectedNext;
    if (!logOutputKo->initialized())
    {
        logInfoP("ChoiceState<%c>: Uninitialized LOG[%u](KO %u)", 'a' + choiceState, choiceStateLogChannel, logOutputKoNumber);
        // 2g) get the following state
        // TODO ensure expected memory layout!
        selectedNext = knx.paramByte(DFA_ParamCalcIndex(DFA_aCaU + choiceState * (DFA_aCbU - DFA_aCaU)));
    }
    else
    {
        // 2f) get logic-channel result
        const bool choice = logOutputKo->value(DPT_Switch);
        logDebugP("ChoiceState<%c>: LOG[%u](KO %u)=%d", 'a' + choiceState, choiceStateLogChannel, logOutputKoNumber, choice);
        // 2g) get the following state
        // TODO ensure expected memory layout!
        selectedNext = choice
                           ? knx.paramByte(DFA_ParamCalcIndex(DFA_aCaT + choiceState * (DFA_aCbT - DFA_aCaT)))
                           : knx.paramByte(DFA_ParamCalcIndex(DFA_aCaF + choiceState * (DFA_aCbF - DFA_aCaF)));
    }

    const uint8_t selectedNextState = selectedNext - 1;
    if (isValidState(selectedNextState))
    {
        logDebugP("ChoiceState<%c>: -> selected next state z%u", 'a' + choiceState, selectedNextState + 1);
        return selectedNextState;
    }
    else if (selectedNextState == DFA_STATE_CHOICE_ELSE)
    {
        if (nextState + 1 < 64 + DFA_DEF_CHOICESTATES_COUNT)
        {
            logDebugP("ChoiceState<%c>: -> ELSE", 'a' + choiceState);
            return nextState + 1;
            // => start evaluating the chain until last choice-state
        }
        else
        {
            logErrorP("ChoiceState<%c>: Invalid ELSE for last Choice-State", 'a' + choiceState);
            return DFA_STATE_UNDEFINED;
        }
    }
    else
    {
        // 2h) ignore empty following
        // exclude arbitrary following choice-states (could result in endless loop!) or reset-pseudo-state
        logDebugP("ChoiceState<%c>: selected NO next state", 'a' + choiceState);
        // all next definitions not a state, or not explicitly else
        return DFA_STATE_UNDEFINED;
    }
}

void DfaChannel::transferProcessNext(const uint8_t nextState)
{
    if (isValidState(nextState))
    {
        // 3a) set state
        logDebugP("=> set state z%u", nextState + 1);
        setState(nextState);
    }
    else if (nextState == DFA_STATE_TIMEOUT_RESET)
    {
        // 3b) special case: timeout reset (without setting the state)
        logDebugP("=> timeout restart");

        // handling of timeout reset as defined by "<<", do not trigger any other reaction
        resetTimeout();
    }
    else if (nextState == DFA_STATE_UNDEFINED)
    {
        logDebugP("=> no following state");
    }
    else
    {
        logErrorP("=> UNEXPECTED int:%u", nextState);
    }
}

#pragma endregion "DFA_CHANNEL_TRANSFER"

#pragma region "DFA_CHANNEL_STATE_TIMEOUT"

void DfaChannel::endTimeout()
{
    if (_stateTimeoutDelay_ms > 0)
    {
        logDebugP("change timeout %d -> 1ms", _stateTimeoutDelay_ms);

        // set to shortest possible valid timeout of 1ms; might result in up to 1ms delay until end, when executed directly after state change
        _stateTimeoutDelay_ms = 1;
    }
}

void DfaChannel::resetTimeout()
{
    // do NOT check: if (_stateTimeoutDelay_ms > 0)
    _stateTimeoutBegin_ms = millis();
}

// calculate the remaining timeout, or 0 for no timeout defined for current state
uint32_t DfaChannel::timeoutRemaining_ms()
{
    if (_stateTimeoutDelay_ms == 0)
    {
        return 0; // no timeout defined in current state
    }

    // important: use same time for all comparisons and calculations
    const unsigned long now = millis();

    // note: the following condition is used to check time-out-end in loop:
    // (_stateTimeoutDelay_ms > 0 && delayCheckMillis(_stateTimeoutBegin_ms, _stateTimeoutDelay_ms))
    if (_stateTimeoutDelay_ms > 0 && (now - _stateTimeoutBegin_ms >= _stateTimeoutDelay_ms))
    {
        return 1; // timeout reached
    }

    //          remaining_ms = _stateTimeoutBegin_ms + _stateTimeoutDelay_ms - millis();
    //          remaining_ms = (_stateTimeoutBegin_ms - millis()) + _stateTimeoutDelay_ms;
    //          remaining_ms   = _stateTimeoutDelay_ms - (millis() - _stateTimeoutBegin_ms)
    const uint32_t remaining_ms = _stateTimeoutDelay_ms - (now - _stateTimeoutBegin_ms);
    // note: prevent 0, as indicator for no timeout
    return (remaining_ms > 0) ? remaining_ms : 1;
}

#pragma endregion "DFA_CHANNEL_STATE_TIMEOUT"

#pragma region "DFA_CHANNEL_PERSISTANCE"

void DfaChannel::save()
{
    // 0x AR00_00PP
    const uint8_t conf = _channelActive << 7 | _running << 6 | ParamDFA_aStateRestore;
    openknx.flash.writeByte(conf);
    openknx.flash.writeByte(_state);

    const uint32_t futureDelay = timeoutRemaining_ms();
    openknx.flash.writeInt(futureDelay);

    // TODO write absolute time

    logDebugP("saved c=%2x s=%2x t=%u b=%u f=%u", conf, _state, _stateTimeoutDelay_ms, _stateTimeoutBegin_ms, futureDelay);
}

void DfaChannel::restore()
{
    // 0x AR00_00PP
    const uint8_t conf = openknx.flash.readByte();
    const uint8_t state = openknx.flash.readByte();
    const uint32_t timeout = openknx.flash.readInt();
    logDebugP("restored conf=0x%02x state=%3u(raw) timeout=%u", conf, state, timeout);

    // do not restore inactive channels, but must always read all bytes!
    if ((conf & (1 << 7)) == 0)
        return;

    //  <ParameterType Id="%AID%_PT-StatePersistance" Name="StatePersistance">
    //  <TypeRestriction Base="Value" SizeInBit="2">
    //      <Enumeration Id="%ENID%" Value="0" Text="nicht speichern (immer Startzustand nutzen)"  /><!-- 0b00 -->
    //      <Enumeration Id="%ENID%" Value="1" Text="gespeicherten Zustand neu starten"            /><!-- 0b01 -->
    //      <Enumeration Id="%ENID%" Value="2" Text="gespeicherten Zustand fortsetzen"             /><!-- 0b10 -->
    //      <!--
    //      <Enumeration Id="%ENID%" Value="3" Text="letzten Zustand mit absolutem Timeout-Ende"   /> --><!-- 0b11 -->
    //  </TypeRestriction>
    //  </ParameterType>

    if (ParamDFA_aStateRestore && (conf & 0b11))
    {
        // restore last running state
        if (ParamDFA_aStartPause > 0)
        {
            bool savedRunning = conf & (1 << 6);
            _firstRunning = savedRunning;
        }

        // restore only, if a state was reached; otherwise use z0
        if (isValidState(state))
        {
            _firstState = state;
            _firstStateTimeoutDelay_ms = timeout;

            _restoreOutputs = true;
        }
    }
}

#pragma endregion "DFA_CHANNEL_PERSISTANCE"

bool DfaChannel::isActive()
{
    return _channelActive;
}

#pragma region "DFA_CHANNEL_COMMANDS"

bool DfaChannel::processCommandDfa(bool diagnoseKo)
{
    logDebugP("status and remaining delay");

    if (!_channelActive)
    {
        logInfoP("NOT_ACTIVE");
        if (diagnoseKo)
            openknx.console.writeDiagnoseKo("NOT_ACTIVE");
        return true;
    }

    if (_processStartup)
    {
        logInfoP("STARTUP");
        if (diagnoseKo)
            openknx.console.writeDiagnoseKo("STARTUP");
        return true;
    }

    const uint8_t state = _state + 1;
    const char mode = _running ? '<' : ']';
    if (state > 99)
    {
        // exclude states with > 2 characters; should never happen
    }
    else if (_stateTimeoutDelay_ms > 0)
    {
        uint32_t remaining = timeoutRemaining_ms();
        logDebugP("T@%d", remaining);
        const uint16_t timeoutMillis = remaining % 1000;
        remaining = remaining / 1000;
        const uint16_t timeoutSeconds = remaining % 60;
        remaining = remaining / 60;
        const uint16_t timeoutMinutes = remaining % 60;
        remaining = remaining / 60;
        const uint16_t timeoutHours = remaining;

        logInfoP((timeoutHours < 10) ? "%02d%c%d:%02d:%02d.%03d" : "%02d%c%5d:%02d:%02d", state, mode, timeoutHours, timeoutMinutes, timeoutSeconds, timeoutMillis);
        if (diagnoseKo)
            openknx.console.writeDiagnoseKo((timeoutHours < 10) ? "%02d%c%d:%02d:%02d.%03d" : "%02d%c%5d:%02d:%02d", state, mode, timeoutHours, timeoutMinutes, timeoutSeconds, timeoutMillis);
    }
    else
    {
        logInfoP("%02d%cNO_TIMEOUT", state, mode);
        if (diagnoseKo)
            openknx.console.writeDiagnoseKo("%02d%c NO_TIMEOUT", state, mode);
    }
    return true;
}

bool DfaChannel::processCommandDfaTimeout(bool diagnoseKo)
{
    logInfoP("timeout end now!");
    // TODO define behaviour when disabled
    endTimeout();
    return true;
}

bool DfaChannel::processCommandDfaStateSet(const uint8_t stateStarting1, bool diagnoseKo)
{
    const uint8_t state = stateStarting1 - 1;
    transfer(state | 0x80); // TODO check using a return-value
    return isValidState(state);
}

bool DfaChannel::processCommandDfaSymbolInsert(const uint8_t inputSymbolNumber, bool diagnoseKo)
{
    transfer(inputSymbolNumber);
    return true;
}

bool DfaChannel::processCommandDfaChoice(const uint8_t inputChoiceNumber, bool diagnoseKo)
{
    transfer(0xC0 | inputChoiceNumber);
    return true;
}

bool DfaChannel::processCommandDfaHistory(bool diagnoseKo)
{
    std::string historyStr = _history.getCompactHistoryString();
    logInfoP("History: %s", historyStr.c_str());
    if (diagnoseKo)
        openknx.console.writeDiagnoseKo(historyStr.c_str());
    return true;
}

#ifdef OPENKNX_DEBUG
bool DfaChannel::processCommandDfaTesting()
{
    uint8_t next[256];
    uint8_t eval[256];
    bool isState[256];
    bool isConditional[256];
    char type[256];
    logDebugP("TEST Collect:");
    logIndentUp();
    for (uint16_t i = 0x00; i <= 0xff; i++)
    {
        next[i] = transferGetNextForInput(i);
        eval[i] = transferEvaluateChoice(i);
        isState[i] = isValidState(i);
        isConditional[i] = (64 <= i && i < 64 + DFA_DEF_CHOICESTATES_COUNT);
        if (i < 8)
            type[i] = 'A' + i;
        else if (i == 8)
            type[i] = 'T';
        else if (128 <= i && i < 128 + DFA_DEF_STATES_COUNT)
            type[i] = '=';
        else if (128 + 64 <= i && i < 128 + 64 + DFA_DEF_CHOICESTATES_COUNT)
            type[i] = 'a' + (i - 128 - 64);
        else
            type[i] = '_';
    }
    logIndentDown();
    logDebugP("TEST[nnn]: T transf   S C choice");
    for (uint16_t i = 0x00; i <= 0xff; i++)
    {
        const uint16_t iFirst = i;
        logDebugP("TEST[%3u]: %c %3u|x%02x  %u %3u|x%02x", i, type[i], next[i], next[i], isState[i], isConditional[i], eval[i], eval[i]);
        while (i+1  <= 0xff && next[i+1] == next[i] && eval[i+1] == eval[i] && isState[i+1] == isState[i] && isConditional[i+1] == isConditional[i] && type[i+1] == type[i])
            i++;
        if (i > iFirst)
            logDebugP("... %ux ...", i - iFirst);
    }
    return true;
}

bool DfaChannel::processCommandDfaParams()
{
    logDebugP("PARAM Collect:");
    for (uint8_t i = 0; i <= 8; i++)
    {
        // _DFA_KoKOaInput___(i)
        // _KoDFA_KOaInput___(i)

        logDebugP("Input[%u]: %u {LOG=%u KO=%u} trigger=%u", i,
            _ParamDFA_aSymbol___Input(i),        // _DFA_aSymbol___Input(i)
            _ParamDFA_aSymbol___LogicNumber(i),  // _DFA_aSymbol___LogicNumber(i)
            _ParamDFA_aSymbol___KoNumber(i),     // _DFA_aSymbol___KoNumber(i)
            _ParamDFA_aSymbol___Trigger(i)       // _DFA_aSymbol___Trigger(i)
        );
    }

    //       ("State z%02u: %3u %3u %3u %3u %3u %3u %3u %3u | %3u @ %10ums (%u)", z + 1);
    logDebugP("[Address]    A   B   C   D   E   F   G   H     T     Timeout | Send/Dpt1 for 4 outputs");
    for (uint8_t z = 0; z < DFA_DEF_STATES_COUNT; z++)
    {
        logDebugP("State z%02u: %3u %3u %3u %3u %3u %3u %3u %3u | %3u @ %3u | %03u %03u %03u %03u %03u %03u %03u %03u", z + 1,
            _DFA_ad___(z, 0), _DFA_ad___(z, 1), _DFA_ad___(z, 2), _DFA_ad___(z, 3),
            _DFA_ad___(z, 4), _DFA_ad___(z, 5), _DFA_ad___(z, 6), _DFA_ad___(z, 7),
            _DFA_ad___(z, 8), _DFA_ad___TTime(z),
            _DFA_az___o___Send(z, 0), _DFA_az___o___Dpt1(z, 0),
            _DFA_az___o___Send(z, 1), _DFA_az___o___Dpt1(z, 1),
            _DFA_az___o___Send(z, 2), _DFA_az___o___Dpt1(z, 2),
            _DFA_az___o___Send(z, 3), _DFA_az___o___Dpt1(z, 3)
        );
    }
    logDebugP("[Values]     A   B   C   D   E   F   G   H     T     Timeout   | Send/Spt for 4 outputs");
    for (uint8_t z = 0; z < DFA_DEF_STATES_COUNT; z++)
    {
        logDebugP("State z%02u: %3u %3u %3u %3u %3u %3u %3u %3u | %3u @ %10ums | %2x %08x %2x %08x %2x %08x %2x %08x", z + 1,
            _ParamDFA_ad___(z, 0), _ParamDFA_ad___(z, 1), _ParamDFA_ad___(z, 2), _ParamDFA_ad___(z, 3),
            _ParamDFA_ad___(z, 4), _ParamDFA_ad___(z, 5), _ParamDFA_ad___(z, 6), _ParamDFA_ad___(z, 7),
            _ParamDFA_ad___(z, 8), _ParamDFA_ad___TTimeMS(z),
            _ParamDFA_az___o___Send(z, 0), knx.paramInt(DFA_ParamCalcIndex(_DFA_az___o___Dpt1(z, 0))),
            _ParamDFA_az___o___Send(z, 1), knx.paramInt(DFA_ParamCalcIndex(_DFA_az___o___Dpt1(z, 1))),
            _ParamDFA_az___o___Send(z, 2), knx.paramInt(DFA_ParamCalcIndex(_DFA_az___o___Dpt1(z, 2))),
            _ParamDFA_az___o___Send(z, 3), knx.paramInt(DFA_ParamCalcIndex(_DFA_az___o___Dpt1(z, 3)))
        );
    }

    return true;
}
#endif

#pragma endregion "DFA_CHANNEL_COMMANDS"

void DfaChannel::addHistory(uint8_t input, uint8_t state)
{
    _history.addHistory(input, state);
    logDebugP("addHistory(input=int:%u, state=int:%u) [DONE]", input, state);
    logHexDebugP(_history.getHistoryBuffer(), _history.getHistoryBufferSize());
}
