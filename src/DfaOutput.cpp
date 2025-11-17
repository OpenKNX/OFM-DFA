// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2025 Cornelius Koepp

#include "DfaOutput.h"
#include "DfaOutputConfigHelper.h"


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

void DfaOutput::stateUpdate(const uint8_t newState, const bool restoreOutputs)
{
    const bool stateChanged = (_state != newState);
    _state = newState;

    // TODO extract to DfaOutput::setState

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
#if defined(OPENKNX_TRACE1) || defined(OPENKNX_TRACE2) || defined(OPENKNX_TRACE3) || defined(OPENKNX_TRACE4) || defined(OPENKNX_TRACE5)
    // TODO check duplicate decision within called method
    const bool updateKo =            (outputStateSend > 0);
#endif
    const bool sendOnRestore =       (outputStateSend & 0b1000) == 0;
    const uint8_t outputStateSend3 = (outputStateSend & 0b0111);
    const bool sendOnChangedValue =  (outputStateSend3 >= 2);
    const bool sendOnChangedState =  (outputStateSend3 >= 4);
    const bool sendAlways =          (outputStateSend3 >= 6);
    const bool repeatedSending =     (outputStateSend3 >= 2) && (outputStateSend3 & 0b001);

    // TODO check removal of `(outputGetDpt(i) != 0)`
    const bool cyclicSending = (outputGetDpt() != 0) && repeatedSending;
    _timeout.delay_ms = cyclicSending ? paramDelay(knx.paramWord(DFA_ParamCalcIndex(_outputIntervalPRI[i]))) : 0;

    logTraceP("Output<%d>: ko=%i on~Val=%i on~State=%i all=%i ; cyclic=%i",
                i + 1, updateKo, sendOnChangedValue, sendOnChangedState, sendAlways, repeatedSending);

    const bool forceSend = sendAlways || (sendOnChangedState && stateChanged);
    const bool allowSend = !restoreOutputs || sendOnRestore;
    outputUpdate(allowSend && sendOnChangedValue, allowSend && forceSend);
}

uint8_t DfaOutput::outputGetDpt()
{
    // return knx.paramByte(DFA_ParamCalcIndex(_outputDptPRI[i]));
    return ParamDFA_aOutput_I_Dpt(i);
}

uint8_t DfaOutput::getCurrentStateSendConfig()
{
    return knx.paramByte(DFA_ParamCalcIndex(_outputSendPRI[_state][i]));
}

/*bool*/ void DfaOutput::outputUpdateKO(const KNXValue &value, const Dpt &type, const bool send /* = false */, const bool forceSend /* = false */)
{
    bool hasSend = false;

    GroupObject *ko = &KoDFA_KOaOutput_N_(i);
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
                    // TODO check Using paramBit
                    // producer:   (knx.paramByte(DFA_ParamCalcIndex(DFA_az01o1Dpt1)))
                    outputUpdateKO((knx.paramByte(pIdxValue) != 0), DPT_Switch, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT2:
                    // TODO check using mask!
                    // producer:  (knx.paramByte(DFA_ParamCalcIndex(DFA_az01o1Dpt2)))
                    outputUpdateKO(knx.paramByte(pIdxValue), DPT_Switch_Control, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT5:
                    // producer:  (knx.paramByte(DFA_ParamCalcIndex(DFA_az01o1Dpt5)))
                    outputUpdateKO(knx.paramByte(pIdxValue), DPT_DecimalFactor, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT5001:
                    // producer:  (knx.paramByte(DFA_ParamCalcIndex(DFA_az01o1Dpt5001)))
                    outputUpdateKO(knx.paramByte(pIdxValue), DPT_Scaling, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT6:
                    // producer:
                    //    ((int8_t)knx.paramByte(DFA_ParamCalcIndex(DFA_az01o1Dpt6)))
                    outputUpdateKO(knx.paramSignedByte(pIdxValue), DPT_Value_1_Count, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT7:
                    // producer:  (knx.paramWord(DFA_ParamCalcIndex(DFA_az01o1Dpt7)))
                    outputUpdateKO(knx.paramWord(pIdxValue), DPT_Value_2_Ucount, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT8:
                    // producer:  ((int16_t)knx.paramWord(DFA_ParamCalcIndex(DFA_az01o1Dpt8)))
                    outputUpdateKO((int16_t)knx.paramWord(pIdxValue), DPT_Value_2_Count, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT9:
                    // producer:  (knx.paramFloat(DFA_ParamCalcIndex(DFA_az01o1Dpt9),
                    //                                          Float_Enc_IEEE754Single))
                    // Important: Do NOT use a DPT which is cropped. Must be Supported by dptconvert
                    // outputUpdateKO(knx.paramFloat(pIdxValue, Float_Enc_DPT9), DPT_Value_Tempd, send, forceSend);

                    // direct sending of the stored 16 bit value, without conversion
                    outputUpdateKO(knx.paramWord(pIdxValue), DPT_Value_2_Ucount, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT12:
                    // producer:  (knx.paramInt(DFA_ParamCalcIndex(DFA_az01o1Dpt12)))
                    outputUpdateKO(knx.paramInt(pIdxValue), DPT_Value_4_Ucount, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT13:
                    // producer:   (int32_t)knx.paramInt(DFA_ParamCalcIndex(DFA_az01o1Dpt13)))
                    outputUpdateKO((int32_t)knx.paramInt(pIdxValue), DPT_Value_4_Count, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT14:
                    // producer:  (knx.paramFloat(DFA_ParamCalcIndex(DFA_az01o1Dpt14),
                    //                                          Float_Enc_IEEE754Single))
                    // outputUpdateKO(knx.paramFloat(pIdxValue, Float_Enc_IEEE754Single), DPT_Value_Absolute_Temperature, send, forceSend);

                    // direct sending of the stored 32 bit value, without conversion
                    outputUpdateKO(knx.paramInt(pIdxValue), DPT_Value_4_Ucount, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT16:
                    outputUpdateKO((char *)knx.paramData(pIdxValue), DPT_String_8859_1, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT17:
                    // producer:  (knx.paramByte(DFA_ParamCalcIndex(DFA_az01o1Dpt17)))
                    outputUpdateKO(knx.paramByte(pIdxValue), DPT_SceneNumber, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT232:
                    // get value as defined in ParamDFA_az01o1Dpt232
                    // TODO Ensure same values for DFA_az{$state}o{$output}Dpt232Mask and DFA_az{$state}o{$output}Dpt232Shift
                    //  producer:  ((knx.paramInt(DFA_ParamCalcIndex(DFA_az01o1Dpt232))
                    //                                         & DFA_az01o1Dpt232Mask) >> DFA_az01o1Dpt232Shift)
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

