// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2025 Cornelius Koepp

#include "DfaOutput.h"


// TODO calculate index; expected distance should be protected by compile error
// TODO special handling of indices for >32 DFA required
// Define (relative) parameter address-index for next state by current state and input
const uint16_t DfaOutput::_outputKoPRI[DFA_DEF_OUTPUTS_COUNT] = {
    DFA_KoKOaOutput1,
    DFA_KoKOaOutput2,
    DFA_KoKOaOutput3,
    DFA_KoKOaOutput4,
};
const uint16_t DfaOutput::_outputDptPRI[DFA_DEF_OUTPUTS_COUNT] = {
    DFA_aOutput1Dpt,
    DFA_aOutput2Dpt,
    DFA_aOutput3Dpt,
    DFA_aOutput4Dpt,
};
const uint16_t DfaOutput::_outputSendPRI[DFA_DEF_STATES_COUNT][DFA_DEF_OUTPUTS_COUNT] = {
    // TODO ensure same position of all Outputs
    { DFA_az01o1Send, DFA_az01o2Send, DFA_az01o3Send, DFA_az01o4Send, },
    { DFA_az02o1Send, DFA_az02o2Send, DFA_az02o3Send, DFA_az02o4Send, },
    { DFA_az03o1Send, DFA_az03o2Send, DFA_az03o3Send, DFA_az03o4Send, },
    { DFA_az04o1Send, DFA_az04o2Send, DFA_az04o3Send, DFA_az04o4Send, },
    { DFA_az05o1Send, DFA_az05o2Send, DFA_az05o3Send, DFA_az05o4Send, },
    { DFA_az06o1Send, DFA_az06o2Send, DFA_az06o3Send, DFA_az06o4Send, },
    { DFA_az07o1Send, DFA_az07o2Send, DFA_az07o3Send, DFA_az07o4Send, },
    { DFA_az08o1Send, DFA_az08o2Send, DFA_az08o3Send, DFA_az08o4Send, },
    { DFA_az09o1Send, DFA_az09o2Send, DFA_az09o3Send, DFA_az09o4Send, },
    { DFA_az10o1Send, DFA_az10o2Send, DFA_az10o3Send, DFA_az10o4Send, },
    { DFA_az11o1Send, DFA_az11o2Send, DFA_az11o3Send, DFA_az11o4Send, },
    { DFA_az12o1Send, DFA_az12o2Send, DFA_az12o3Send, DFA_az12o4Send, },
    { DFA_az13o1Send, DFA_az13o2Send, DFA_az13o3Send, DFA_az13o4Send, },
    { DFA_az14o1Send, DFA_az14o2Send, DFA_az14o3Send, DFA_az14o4Send, },
    { DFA_az15o1Send, DFA_az15o2Send, DFA_az15o3Send, DFA_az15o4Send, },
    { DFA_az16o1Send, DFA_az16o2Send, DFA_az16o3Send, DFA_az16o4Send, },
#if DFA_DEF_STATES_COUNT > 16
    { DFA_az17o1Send, DFA_az17o2Send, DFA_az17o3Send, DFA_az17o4Send, },
    { DFA_az18o1Send, DFA_az18o2Send, DFA_az18o3Send, DFA_az18o4Send, },
    { DFA_az19o1Send, DFA_az19o2Send, DFA_az19o3Send, DFA_az19o4Send, },
    { DFA_az20o1Send, DFA_az20o2Send, DFA_az20o3Send, DFA_az20o4Send, },
    { DFA_az21o1Send, DFA_az21o2Send, DFA_az21o3Send, DFA_az21o4Send, },
    { DFA_az22o1Send, DFA_az22o2Send, DFA_az22o3Send, DFA_az22o4Send, },
    { DFA_az23o1Send, DFA_az23o2Send, DFA_az23o3Send, DFA_az23o4Send, },
    { DFA_az24o1Send, DFA_az24o2Send, DFA_az24o3Send, DFA_az24o4Send, },
    { DFA_az25o1Send, DFA_az25o2Send, DFA_az25o3Send, DFA_az25o4Send, },
    { DFA_az26o1Send, DFA_az26o2Send, DFA_az26o3Send, DFA_az26o4Send, },
    { DFA_az27o1Send, DFA_az27o2Send, DFA_az27o3Send, DFA_az27o4Send, },
    { DFA_az28o1Send, DFA_az28o2Send, DFA_az28o3Send, DFA_az28o4Send, },
    { DFA_az29o1Send, DFA_az29o2Send, DFA_az29o3Send, DFA_az29o4Send, },
    { DFA_az30o1Send, DFA_az30o2Send, DFA_az30o3Send, DFA_az30o4Send, },
    { DFA_az31o1Send, DFA_az31o2Send, DFA_az31o3Send, DFA_az31o4Send, },
    { DFA_az32o1Send, DFA_az32o2Send, DFA_az32o3Send, DFA_az32o4Send, },
#endif
#if DFA_DEF_STATES_COUNT > 32
    { DFA_az33o1Send, DFA_az33o2Send, DFA_az33o3Send, DFA_az33o4Send, },
    { DFA_az34o1Send, DFA_az34o2Send, DFA_az34o3Send, DFA_az34o4Send, },
    { DFA_az35o1Send, DFA_az35o2Send, DFA_az35o3Send, DFA_az35o4Send, },
    { DFA_az36o1Send, DFA_az36o2Send, DFA_az36o3Send, DFA_az36o4Send, },
    { DFA_az37o1Send, DFA_az37o2Send, DFA_az37o3Send, DFA_az37o4Send, },
    { DFA_az38o1Send, DFA_az38o2Send, DFA_az38o3Send, DFA_az38o4Send, },
    { DFA_az39o1Send, DFA_az39o2Send, DFA_az39o3Send, DFA_az39o4Send, },
    { DFA_az40o1Send, DFA_az40o2Send, DFA_az40o3Send, DFA_az40o4Send, },
    { DFA_az41o1Send, DFA_az41o2Send, DFA_az41o3Send, DFA_az41o4Send, },
    { DFA_az42o1Send, DFA_az42o2Send, DFA_az42o3Send, DFA_az42o4Send, },
    { DFA_az43o1Send, DFA_az43o2Send, DFA_az43o3Send, DFA_az43o4Send, },
    { DFA_az44o1Send, DFA_az44o2Send, DFA_az44o3Send, DFA_az44o4Send, },
    { DFA_az45o1Send, DFA_az45o2Send, DFA_az45o3Send, DFA_az45o4Send, },
    { DFA_az46o1Send, DFA_az46o2Send, DFA_az46o3Send, DFA_az46o4Send, },
    { DFA_az47o1Send, DFA_az47o2Send, DFA_az47o3Send, DFA_az47o4Send, },
    { DFA_az48o1Send, DFA_az48o2Send, DFA_az48o3Send, DFA_az48o4Send, },
    { DFA_az49o1Send, DFA_az49o2Send, DFA_az49o3Send, DFA_az49o4Send, },
    { DFA_az50o1Send, DFA_az50o2Send, DFA_az50o3Send, DFA_az50o4Send, },
    { DFA_az51o1Send, DFA_az51o2Send, DFA_az51o3Send, DFA_az51o4Send, },
    { DFA_az52o1Send, DFA_az52o2Send, DFA_az52o3Send, DFA_az52o4Send, },
    { DFA_az53o1Send, DFA_az53o2Send, DFA_az53o3Send, DFA_az53o4Send, },
    { DFA_az54o1Send, DFA_az54o2Send, DFA_az54o3Send, DFA_az54o4Send, },
    { DFA_az55o1Send, DFA_az55o2Send, DFA_az55o3Send, DFA_az55o4Send, },
    { DFA_az56o1Send, DFA_az56o2Send, DFA_az56o3Send, DFA_az56o4Send, },
    { DFA_az57o1Send, DFA_az57o2Send, DFA_az57o3Send, DFA_az57o4Send, },
    { DFA_az58o1Send, DFA_az58o2Send, DFA_az58o3Send, DFA_az58o4Send, },
    { DFA_az59o1Send, DFA_az59o2Send, DFA_az59o3Send, DFA_az59o4Send, },
    { DFA_az60o1Send, DFA_az60o2Send, DFA_az60o3Send, DFA_az60o4Send, },
    { DFA_az61o1Send, DFA_az61o2Send, DFA_az61o3Send, DFA_az61o4Send, },
    { DFA_az62o1Send, DFA_az62o2Send, DFA_az62o3Send, DFA_az62o4Send, },
    { DFA_az63o1Send, DFA_az63o2Send, DFA_az63o3Send, DFA_az63o4Send, },
    { DFA_az64o1Send, DFA_az64o2Send, DFA_az64o3Send, DFA_az64o4Send, },
#endif    
};
const uint16_t DfaOutput::_outputValuePRI[DFA_DEF_STATES_COUNT][DFA_DEF_OUTPUTS_COUNT] = {
    // TODO ensure same position of all Outputs
    { DFA_az01o1Dpt1, DFA_az01o2Dpt1, DFA_az01o3Dpt1, DFA_az01o4Dpt1, },
    { DFA_az02o1Dpt1, DFA_az02o2Dpt1, DFA_az02o3Dpt1, DFA_az02o4Dpt1, },
    { DFA_az03o1Dpt1, DFA_az03o2Dpt1, DFA_az03o3Dpt1, DFA_az03o4Dpt1, },
    { DFA_az04o1Dpt1, DFA_az04o2Dpt1, DFA_az04o3Dpt1, DFA_az04o4Dpt1, },
    { DFA_az05o1Dpt1, DFA_az05o2Dpt1, DFA_az05o3Dpt1, DFA_az05o4Dpt1, },
    { DFA_az06o1Dpt1, DFA_az06o2Dpt1, DFA_az06o3Dpt1, DFA_az06o4Dpt1, },
    { DFA_az07o1Dpt1, DFA_az07o2Dpt1, DFA_az07o3Dpt1, DFA_az07o4Dpt1, },
    { DFA_az08o1Dpt1, DFA_az08o2Dpt1, DFA_az08o3Dpt1, DFA_az08o4Dpt1, },
    { DFA_az09o1Dpt1, DFA_az09o2Dpt1, DFA_az09o3Dpt1, DFA_az09o4Dpt1, },
    { DFA_az10o1Dpt1, DFA_az10o2Dpt1, DFA_az10o3Dpt1, DFA_az10o4Dpt1, },
    { DFA_az11o1Dpt1, DFA_az11o2Dpt1, DFA_az11o3Dpt1, DFA_az11o4Dpt1, },
    { DFA_az12o1Dpt1, DFA_az12o2Dpt1, DFA_az12o3Dpt1, DFA_az12o4Dpt1, },
    { DFA_az13o1Dpt1, DFA_az13o2Dpt1, DFA_az13o3Dpt1, DFA_az13o4Dpt1, },
    { DFA_az14o1Dpt1, DFA_az14o2Dpt1, DFA_az14o3Dpt1, DFA_az14o4Dpt1, },
    { DFA_az15o1Dpt1, DFA_az15o2Dpt1, DFA_az15o3Dpt1, DFA_az15o4Dpt1, },
    { DFA_az16o1Dpt1, DFA_az16o2Dpt1, DFA_az16o3Dpt1, DFA_az16o4Dpt1, },
#if DFA_DEF_STATES_COUNT > 16
    { DFA_az17o1Dpt1, DFA_az17o2Dpt1, DFA_az17o3Dpt1, DFA_az17o4Dpt1, },
    { DFA_az18o1Dpt1, DFA_az18o2Dpt1, DFA_az18o3Dpt1, DFA_az18o4Dpt1, },
    { DFA_az19o1Dpt1, DFA_az19o2Dpt1, DFA_az19o3Dpt1, DFA_az19o4Dpt1, },
    { DFA_az20o1Dpt1, DFA_az20o2Dpt1, DFA_az20o3Dpt1, DFA_az20o4Dpt1, },
    { DFA_az21o1Dpt1, DFA_az21o2Dpt1, DFA_az21o3Dpt1, DFA_az21o4Dpt1, },
    { DFA_az22o1Dpt1, DFA_az22o2Dpt1, DFA_az22o3Dpt1, DFA_az22o4Dpt1, },
    { DFA_az23o1Dpt1, DFA_az23o2Dpt1, DFA_az23o3Dpt1, DFA_az23o4Dpt1, },
    { DFA_az24o1Dpt1, DFA_az24o2Dpt1, DFA_az24o3Dpt1, DFA_az24o4Dpt1, },
    { DFA_az25o1Dpt1, DFA_az25o2Dpt1, DFA_az25o3Dpt1, DFA_az25o4Dpt1, },
    { DFA_az26o1Dpt1, DFA_az26o2Dpt1, DFA_az26o3Dpt1, DFA_az26o4Dpt1, },
    { DFA_az27o1Dpt1, DFA_az27o2Dpt1, DFA_az27o3Dpt1, DFA_az27o4Dpt1, },
    { DFA_az28o1Dpt1, DFA_az28o2Dpt1, DFA_az28o3Dpt1, DFA_az28o4Dpt1, },
    { DFA_az29o1Dpt1, DFA_az29o2Dpt1, DFA_az29o3Dpt1, DFA_az29o4Dpt1, },
    { DFA_az30o1Dpt1, DFA_az30o2Dpt1, DFA_az30o3Dpt1, DFA_az30o4Dpt1, },
    { DFA_az31o1Dpt1, DFA_az31o2Dpt1, DFA_az31o3Dpt1, DFA_az31o4Dpt1, },
    { DFA_az32o1Dpt1, DFA_az32o2Dpt1, DFA_az32o3Dpt1, DFA_az32o4Dpt1, },
#endif
#if DFA_DEF_STATES_COUNT > 32
    { DFA_az33o1Dpt1, DFA_az33o2Dpt1, DFA_az33o3Dpt1, DFA_az33o4Dpt1, },
    { DFA_az34o1Dpt1, DFA_az34o2Dpt1, DFA_az34o3Dpt1, DFA_az34o4Dpt1, },
    { DFA_az35o1Dpt1, DFA_az35o2Dpt1, DFA_az35o3Dpt1, DFA_az35o4Dpt1, },
    { DFA_az36o1Dpt1, DFA_az36o2Dpt1, DFA_az36o3Dpt1, DFA_az36o4Dpt1, },
    { DFA_az37o1Dpt1, DFA_az37o2Dpt1, DFA_az37o3Dpt1, DFA_az37o4Dpt1, },
    { DFA_az38o1Dpt1, DFA_az38o2Dpt1, DFA_az38o3Dpt1, DFA_az38o4Dpt1, },
    { DFA_az39o1Dpt1, DFA_az39o2Dpt1, DFA_az39o3Dpt1, DFA_az39o4Dpt1, },
    { DFA_az40o1Dpt1, DFA_az40o2Dpt1, DFA_az40o3Dpt1, DFA_az40o4Dpt1, },
    { DFA_az41o1Dpt1, DFA_az41o2Dpt1, DFA_az41o3Dpt1, DFA_az41o4Dpt1, },
    { DFA_az42o1Dpt1, DFA_az42o2Dpt1, DFA_az42o3Dpt1, DFA_az42o4Dpt1, },
    { DFA_az43o1Dpt1, DFA_az43o2Dpt1, DFA_az43o3Dpt1, DFA_az43o4Dpt1, },
    { DFA_az44o1Dpt1, DFA_az44o2Dpt1, DFA_az44o3Dpt1, DFA_az44o4Dpt1, },
    { DFA_az45o1Dpt1, DFA_az45o2Dpt1, DFA_az45o3Dpt1, DFA_az45o4Dpt1, },
    { DFA_az46o1Dpt1, DFA_az46o2Dpt1, DFA_az46o3Dpt1, DFA_az46o4Dpt1, },
    { DFA_az47o1Dpt1, DFA_az47o2Dpt1, DFA_az47o3Dpt1, DFA_az47o4Dpt1, },
    { DFA_az48o1Dpt1, DFA_az48o2Dpt1, DFA_az48o3Dpt1, DFA_az48o4Dpt1, },
    { DFA_az49o1Dpt1, DFA_az49o2Dpt1, DFA_az49o3Dpt1, DFA_az49o4Dpt1, },
    { DFA_az50o1Dpt1, DFA_az50o2Dpt1, DFA_az50o3Dpt1, DFA_az50o4Dpt1, },
    { DFA_az51o1Dpt1, DFA_az51o2Dpt1, DFA_az51o3Dpt1, DFA_az51o4Dpt1, },
    { DFA_az52o1Dpt1, DFA_az52o2Dpt1, DFA_az52o3Dpt1, DFA_az52o4Dpt1, },
    { DFA_az53o1Dpt1, DFA_az53o2Dpt1, DFA_az53o3Dpt1, DFA_az53o4Dpt1, },
    { DFA_az54o1Dpt1, DFA_az54o2Dpt1, DFA_az54o3Dpt1, DFA_az54o4Dpt1, },
    { DFA_az55o1Dpt1, DFA_az55o2Dpt1, DFA_az55o3Dpt1, DFA_az55o4Dpt1, },
    { DFA_az56o1Dpt1, DFA_az56o2Dpt1, DFA_az56o3Dpt1, DFA_az56o4Dpt1, },
    { DFA_az57o1Dpt1, DFA_az57o2Dpt1, DFA_az57o3Dpt1, DFA_az57o4Dpt1, },
    { DFA_az58o1Dpt1, DFA_az58o2Dpt1, DFA_az58o3Dpt1, DFA_az58o4Dpt1, },
    { DFA_az59o1Dpt1, DFA_az59o2Dpt1, DFA_az59o3Dpt1, DFA_az59o4Dpt1, },
    { DFA_az60o1Dpt1, DFA_az60o2Dpt1, DFA_az60o3Dpt1, DFA_az60o4Dpt1, },
    { DFA_az61o1Dpt1, DFA_az61o2Dpt1, DFA_az61o3Dpt1, DFA_az61o4Dpt1, },
    { DFA_az62o1Dpt1, DFA_az62o2Dpt1, DFA_az62o3Dpt1, DFA_az62o4Dpt1, },
    { DFA_az63o1Dpt1, DFA_az63o2Dpt1, DFA_az63o3Dpt1, DFA_az63o4Dpt1, },
    { DFA_az64o1Dpt1, DFA_az64o2Dpt1, DFA_az64o3Dpt1, DFA_az64o4Dpt1, },
#endif
};


DfaOutput::DfaOutput(uint8_t channelIndex, uint8_t outputIndex)
{
    _channelIndex = channelIndex;
    i = outputIndex;
}

void DfaOutput::loop()
{
    if (_timeout.delay_ms > 0 && delayCheckMillis(_timeout.begin_ms, _timeout.delay_ms))
    {
        // force send for cyclic sending
        outputUpdate(true, true);
        _timeout.begin_ms = millis(); // TODO check remove, as this should be updated on actual sending only
    }
}


#pragma region "DFA_CHANNEL_OUTPUT_SEND"

void DfaOutput::stateUpdate(const uint8_t newState, const bool _restoreOutputs)
{
    const bool stateChanged = (_state != newState);
    _state = newState;

    // TODO extract to DfaOutput::setState

    // send output values
    // TODO extract
    // TODO replace with `(paramDelay(knx.paramWord(DFA_ParamCalcIndex(DFA_aOutput1IntervalTime))))`
    const uint32_t outputDelays[DFA_DEF_OUTPUTS_COUNT] = {
        ParamDFA_aOutput1IntervalTimeMS,
        ParamDFA_aOutput2IntervalTimeMS,
        ParamDFA_aOutput3IntervalTimeMS,
        ParamDFA_aOutput4IntervalTimeMS,
    };

    const uint8_t outputStateSend = getCurrentStateSendConfig();

    //  <ParameterType Id="%AID%_PT-DfaOutputConf" Name="DfaOutputConf">
    //    <TypeRestriction Base="Value" SizeInBit="8">
    //      <Enumeration Text="-"                                              Value="0" Id="%ENID%" />
    //      <Enumeration Text="kein Senden, nur KO setzen"                     Value="1" Id="%ENID%" />
    //      <Enumeration Text="Wert-Änderung, nicht nach Rekonstruktion"      Value="10" Id="%ENID%" />
    //      <Enumeration Text="Wert-Änderung"                                  Value="2" Id="%ENID%" />
    //      <Enumeration Text="Wert-Änderung                  + zyklisch"      Value="3" Id="%ENID%" />
    //      <Enumeration Text="Zustands-Änderung, nicht nach Rekonstruktion"  Value="12" Id="%ENID%" />
    //      <Enumeration Text="Zustands-Änderung"                              Value="4" Id="%ENID%" />
    //      <Enumeration Text="Zustands-Änderung           + zyklisch"         Value="5" Id="%ENID%" />
    //      <Enumeration Text="jeder Zustands-Aufruf"                          Value="6" Id="%ENID%" />
    //      <Enumeration Text="jeder Zustands-Aufruf        + zyklisch"        Value="7" Id="%ENID%" />
    //    </TypeRestriction>
    //  </ParameterType>
    const bool updateKo =            (outputStateSend > 0);
    const bool sendOnRestore =       (outputStateSend & 0b1000) == 0;
    const uint8_t outputStateSend3 = (outputStateSend & 0b0111);
    const bool sendOnChangedValue =  (outputStateSend3 >= 2);
    const bool sendOnChangedState =  (outputStateSend3 >= 4);
    const bool sendAlways =          (outputStateSend3 >= 6);
    const bool repeatedSending =     (outputStateSend3 >= 2) && (outputStateSend3 & 0b001);

    // TODO check removal of `(outputGetDpt(i) != 0)`
    const bool cyclicSending = (outputGetDpt() != 0) && repeatedSending;
    _timeout.delay_ms = cyclicSending ? outputDelays[i] : 0;

    logTraceP("Output<%d>: ko=%i on~Val=%i on~State=%i all=%i ; cyclic=%i",
                i + 1, updateKo, sendOnChangedValue, sendOnChangedState, sendAlways, repeatedSending);

    const bool forceSend = sendAlways || (sendOnChangedState && stateChanged);
    const bool allowSend = !_restoreOutputs || sendOnRestore;
    outputUpdate(allowSend && sendOnChangedValue, allowSend && forceSend);
}

uint8_t DfaOutput::outputGetDpt()
{
    return knx.paramByte(DFA_ParamCalcIndex(_outputDptPRI[i]));
}

uint8_t DfaOutput::getCurrentStateSendConfig()
{
    return knx.paramByte(DFA_ParamCalcIndex(_outputSendPRI[_state][i]));
}

/*bool*/ void DfaOutput::outputUpdateKO(const KNXValue &value, const Dpt &type, const bool send /* = false */, const bool forceSend /* = false */)
{
    bool hasSend = false;
    const uint16_t goNumber = DFA_KoCalcNumber(_outputKoPRI[i]);
    GroupObject *ko = &knx.getGroupObject(goNumber);
    if (forceSend)
    {
        ko->value(value, type);
        hasSend = true;
    }
    else if (!send)
    {
        ko->valueNoSend(value, type);
    }
    else if (ko->valueNoSendCompare(value, type))
    {
        ko->objectWritten();
        hasSend = true;
    }

    if (hasSend)
    {
        // keep time of writing value to bus
        _timeout.begin_ms = millis();
    }
    // return hasSend;
}

void DfaOutput::outputUpdate(const bool send, const bool forceSend /* = false */)
{
    const uint8_t outputType = outputGetDpt();
    // output is active?
    if (outputType != 0)
    {
        const uint8_t outputStateSend = getCurrentStateSendConfig();
        logTraceP("Output<%d>: update (type=%3i); begin=%6ims, dur=%6ims, outputStateSend=%d", i + 1, outputType, _outputsTimeout[i].begin_ms, _outputsTimeout[i].delay_ms, outputStateSend);

        // output has value for state?
        if (outputStateSend != 0)
        {
            const uint32_t pIdxValue = DFA_ParamCalcIndex(_outputValuePRI[_state][i]);
            // logDebugP("         -> paramIndex=%i", pIdxValue);

            // set value based on dpt
            switch (outputType)
            {
                case DFA_OUTPUT_TYPE_DPT1:
                    // works, as long as using same location as other dpt values
                    outputUpdateKO((knx.paramByte(pIdxValue) != 0), DPT_Switch, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT2:
                    // TODO check using mask!
                    outputUpdateKO(knx.paramByte(pIdxValue), DPT_Switch_Control, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT5:
                    outputUpdateKO(knx.paramByte(pIdxValue), DPT_DecimalFactor, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT5001:
                    outputUpdateKO(knx.paramByte(pIdxValue), DPT_Scaling, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT6:
                    outputUpdateKO(knx.paramSignedByte(pIdxValue), DPT_Value_1_Count, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT7:
                    outputUpdateKO(knx.paramWord(pIdxValue), DPT_Value_2_Ucount, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT8:
                    outputUpdateKO(knx.paramWord(pIdxValue), DPT_Value_2_Count, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT9:
                    outputUpdateKO(knx.paramFloat(pIdxValue, Float_Enc_DPT9), DPT_Value_Temp, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT12:
                    outputUpdateKO(knx.paramInt(pIdxValue), DPT_Value_4_Ucount, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT13:
                    outputUpdateKO(knx.paramInt(pIdxValue), DPT_Value_4_Count, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT14:
                    outputUpdateKO(knx.paramFloat(pIdxValue, Float_Enc_IEEE754Double), DPT_Value_Absolute_Temperature, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT16:
                    outputUpdateKO((char *)knx.paramData(pIdxValue), DPT_String_8859_1, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT17:
                    outputUpdateKO(knx.paramByte(pIdxValue), DPT_SceneNumber, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT232:
                    // get value as defined in ParamDFA_az01o1Dpt232
                    // TODO Ensure same values for DFA_az{$state}o{$output}Dpt232Mask and DFA_az{$state}o{$output}Dpt232Shift
                    outputUpdateKO((knx.paramInt(pIdxValue) & DFA_az01o1Dpt232Mask) >> DFA_az01o1Dpt232Shift, DPT_Colour_RGB, send, forceSend);
                    break;
                default:
                    // TODO check handling undefined cases
                    break;
            }
        }
    }
}

#pragma endregion "DFA_CHANNEL_OUTPUT_SEND"

