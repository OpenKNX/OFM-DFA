// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2024 Cornelius Koepp

#include "DfaChannel.h"

#pragma region "DFA_CHANNEL_ADDR"

const uint8_t DfaChannel::_inputKo[DFA_DEF_INPUTS_COUNT] = {
    DFA_KoKOaInput1,
    DFA_KoKOaInput2,
    DFA_KoKOaInput3,
    DFA_KoKOaInput4,
    DFA_KoKOaInput5,
    DFA_KoKOaInput6,
    DFA_KoKOaInput7,
    DFA_KoKOaInput8,
};
// Value of DFA_KoKOaInput[1-8] by 0-based index
#define DFA_KoKOaInput__N__(IDX) DFA_KoKOaInput1 + IDX * (DFA_KoKOaInput2 - DFA_KoKOaInput1)
// Value of DFA_KoCalcNumber(DFA_KoKOaInput[1-8]) by 0-based index
#define DFA_Channel_Input_KO(IDX) DFA_KoCalcNumber(DFA_KoKOaInput__N__(IDX))

// TODO calculate index; expected distance should be protected by compile error
const uint16_t DfaChannel::_inputConfPRI[DFA_DEF_INPUTS_COUNT] = {
    DFA_aInputSymbol1Ko,
    DFA_aInputSymbol2Ko,
    DFA_aInputSymbol3Ko,
    DFA_aInputSymbol4Ko,
    DFA_aInputSymbol5Ko,
    DFA_aInputSymbol6Ko,
    DFA_aInputSymbol7Ko,
    DFA_aInputSymbol8Ko,
};
// Value of DFA_aInputSymbol[1-8]Ko by 0-based index
#define DFA_aInputSymbol__N__Ko(IDX) DFA_aInputSymbol1Ko + IDX * (DFA_aInputSymbol2Ko - DFA_aInputSymbol1Ko)
//     const uint8_t inputConf = ((knx.paramByte(DFA_ParamCalcIndex(_inputConfPRI[input])) & DFA_aInputSymbol1KoMask) >> DFA_aInputSymbol1KoShift);
#define DFA_Channel_Input_Config(IDX) ((knx.paramByte(DFA_aInputSymbol__N__Ko(input)) & DFA_aInputSymbol1KoMask) >> DFA_aInputSymbol1KoShift)


#if DFA_aInputSymbol1LogicNumber != DFA_aInputSymbol1KoNumber
    #error "DFA_aInputSymbol1LogicNumber != DFA_aInputSymbol1KoNumber"
#endif
const uint16_t DfaChannel::_inputConfNumberPRI[DFA_DEF_INPUTS_COUNT] = {
    DFA_aInputSymbol1KoNumber,
    DFA_aInputSymbol2KoNumber,
    DFA_aInputSymbol3KoNumber,
    DFA_aInputSymbol4KoNumber,
    DFA_aInputSymbol5KoNumber,
    DFA_aInputSymbol6KoNumber,
    DFA_aInputSymbol7KoNumber,
    DFA_aInputSymbol8KoNumber,
};
const uint16_t DfaChannel::_inputTriggerPRI[DFA_DEF_INPUTS_COUNT] = {
    DFA_aInputSymbol1Value,
    DFA_aInputSymbol2Value,
    DFA_aInputSymbol3Value,
    DFA_aInputSymbol4Value,
    DFA_aInputSymbol5Value,
    DFA_aInputSymbol6Value,
    DFA_aInputSymbol7Value,
    DFA_aInputSymbol8Value,
};

// TODO calculate index; expected distance should be protected by compile error
// TODO special handling of indices for >32 DFA required
// Define (relative) parameter address-index for next state by current state and input
const uint16_t DfaChannel::_outputKoPRI[DFA_DEF_OUTPUTS_COUNT] = {
    DFA_KoKOaOutput1,
    DFA_KoKOaOutput2,
    DFA_KoKOaOutput3,
    DFA_KoKOaOutput4,
};
const uint16_t DfaChannel::_outputDptPRI[DFA_DEF_OUTPUTS_COUNT] = {
    DFA_aOutput1Dpt,
    DFA_aOutput2Dpt,
    DFA_aOutput3Dpt,
    DFA_aOutput4Dpt,
};
const uint16_t DfaChannel::_outputSendPRI[DFA_DEF_STATES_COUNT][DFA_DEF_OUTPUTS_COUNT] = {
    // TODO ensure same position of all Outputs
    { DFA_aState01Output1Conf, DFA_aState01Output2Conf, DFA_aState01Output3Conf, DFA_aState01Output4Conf, },
    { DFA_aState02Output1Conf, DFA_aState02Output2Conf, DFA_aState02Output3Conf, DFA_aState02Output4Conf, },
    { DFA_aState03Output1Conf, DFA_aState03Output2Conf, DFA_aState03Output3Conf, DFA_aState03Output4Conf, },
    { DFA_aState04Output1Conf, DFA_aState04Output2Conf, DFA_aState04Output3Conf, DFA_aState04Output4Conf, },
    { DFA_aState05Output1Conf, DFA_aState05Output2Conf, DFA_aState05Output3Conf, DFA_aState05Output4Conf, },
    { DFA_aState06Output1Conf, DFA_aState06Output2Conf, DFA_aState06Output3Conf, DFA_aState06Output4Conf, },
    { DFA_aState07Output1Conf, DFA_aState07Output2Conf, DFA_aState07Output3Conf, DFA_aState07Output4Conf, },
    { DFA_aState08Output1Conf, DFA_aState08Output2Conf, DFA_aState08Output3Conf, DFA_aState08Output4Conf, },
    { DFA_aState09Output1Conf, DFA_aState09Output2Conf, DFA_aState09Output3Conf, DFA_aState09Output4Conf, },
    { DFA_aState10Output1Conf, DFA_aState10Output2Conf, DFA_aState10Output3Conf, DFA_aState10Output4Conf, },
    { DFA_aState11Output1Conf, DFA_aState11Output2Conf, DFA_aState11Output3Conf, DFA_aState11Output4Conf, },
    { DFA_aState12Output1Conf, DFA_aState12Output2Conf, DFA_aState12Output3Conf, DFA_aState12Output4Conf, },
    { DFA_aState13Output1Conf, DFA_aState13Output2Conf, DFA_aState13Output3Conf, DFA_aState13Output4Conf, },
    { DFA_aState14Output1Conf, DFA_aState14Output2Conf, DFA_aState14Output3Conf, DFA_aState14Output4Conf, },
    { DFA_aState15Output1Conf, DFA_aState15Output2Conf, DFA_aState15Output3Conf, DFA_aState15Output4Conf, },
    { DFA_aState16Output1Conf, DFA_aState16Output2Conf, DFA_aState16Output3Conf, DFA_aState16Output4Conf, },
    { DFA_aState17Output1Conf, DFA_aState17Output2Conf, DFA_aState17Output3Conf, DFA_aState17Output4Conf, },
    { DFA_aState18Output1Conf, DFA_aState18Output2Conf, DFA_aState18Output3Conf, DFA_aState18Output4Conf, },
    { DFA_aState19Output1Conf, DFA_aState19Output2Conf, DFA_aState19Output3Conf, DFA_aState19Output4Conf, },
    { DFA_aState20Output1Conf, DFA_aState20Output2Conf, DFA_aState20Output3Conf, DFA_aState20Output4Conf, },
    { DFA_aState21Output1Conf, DFA_aState21Output2Conf, DFA_aState21Output3Conf, DFA_aState21Output4Conf, },
    { DFA_aState22Output1Conf, DFA_aState22Output2Conf, DFA_aState22Output3Conf, DFA_aState22Output4Conf, },
    { DFA_aState23Output1Conf, DFA_aState23Output2Conf, DFA_aState23Output3Conf, DFA_aState23Output4Conf, },
    { DFA_aState24Output1Conf, DFA_aState24Output2Conf, DFA_aState24Output3Conf, DFA_aState24Output4Conf, },
    { DFA_aState25Output1Conf, DFA_aState25Output2Conf, DFA_aState25Output3Conf, DFA_aState25Output4Conf, },
    { DFA_aState26Output1Conf, DFA_aState26Output2Conf, DFA_aState26Output3Conf, DFA_aState26Output4Conf, },
    { DFA_aState27Output1Conf, DFA_aState27Output2Conf, DFA_aState27Output3Conf, DFA_aState27Output4Conf, },
    { DFA_aState28Output1Conf, DFA_aState28Output2Conf, DFA_aState28Output3Conf, DFA_aState28Output4Conf, },
    { DFA_aState29Output1Conf, DFA_aState29Output2Conf, DFA_aState29Output3Conf, DFA_aState29Output4Conf, },
    { DFA_aState30Output1Conf, DFA_aState30Output2Conf, DFA_aState30Output3Conf, DFA_aState30Output4Conf, },
    { DFA_aState31Output1Conf, DFA_aState31Output2Conf, DFA_aState31Output3Conf, DFA_aState31Output4Conf, },
    { DFA_aState32Output1Conf, DFA_aState32Output2Conf, DFA_aState32Output3Conf, DFA_aState32Output4Conf, },
    /*
    { DFA_aState33Output1Conf, DFA_aState33Output2Conf, DFA_aState33Output3Conf, DFA_aState33Output4Conf, },
    { DFA_aState34Output1Conf, DFA_aState34Output2Conf, DFA_aState34Output3Conf, DFA_aState34Output4Conf, },
    { DFA_aState35Output1Conf, DFA_aState35Output2Conf, DFA_aState35Output3Conf, DFA_aState35Output4Conf, },
    { DFA_aState36Output1Conf, DFA_aState36Output2Conf, DFA_aState36Output3Conf, DFA_aState36Output4Conf, },
    { DFA_aState37Output1Conf, DFA_aState37Output2Conf, DFA_aState37Output3Conf, DFA_aState37Output4Conf, },
    { DFA_aState38Output1Conf, DFA_aState38Output2Conf, DFA_aState38Output3Conf, DFA_aState38Output4Conf, },
    { DFA_aState39Output1Conf, DFA_aState39Output2Conf, DFA_aState39Output3Conf, DFA_aState39Output4Conf, },
    { DFA_aState40Output1Conf, DFA_aState40Output2Conf, DFA_aState40Output3Conf, DFA_aState40Output4Conf, },
    { DFA_aState41Output1Conf, DFA_aState41Output2Conf, DFA_aState41Output3Conf, DFA_aState41Output4Conf, },
    { DFA_aState42Output1Conf, DFA_aState42Output2Conf, DFA_aState42Output3Conf, DFA_aState42Output4Conf, },
    { DFA_aState43Output1Conf, DFA_aState43Output2Conf, DFA_aState43Output3Conf, DFA_aState43Output4Conf, },
    { DFA_aState44Output1Conf, DFA_aState44Output2Conf, DFA_aState44Output3Conf, DFA_aState44Output4Conf, },
    { DFA_aState45Output1Conf, DFA_aState45Output2Conf, DFA_aState45Output3Conf, DFA_aState45Output4Conf, },
    { DFA_aState46Output1Conf, DFA_aState46Output2Conf, DFA_aState46Output3Conf, DFA_aState46Output4Conf, },
    { DFA_aState47Output1Conf, DFA_aState47Output2Conf, DFA_aState47Output3Conf, DFA_aState47Output4Conf, },
    { DFA_aState48Output1Conf, DFA_aState48Output2Conf, DFA_aState48Output3Conf, DFA_aState48Output4Conf, },
    { DFA_aState49Output1Conf, DFA_aState49Output2Conf, DFA_aState49Output3Conf, DFA_aState49Output4Conf, },
    { DFA_aState50Output1Conf, DFA_aState50Output2Conf, DFA_aState50Output3Conf, DFA_aState50Output4Conf, },
    { DFA_aState51Output1Conf, DFA_aState51Output2Conf, DFA_aState51Output3Conf, DFA_aState51Output4Conf, },
    { DFA_aState52Output1Conf, DFA_aState52Output2Conf, DFA_aState52Output3Conf, DFA_aState52Output4Conf, },
    { DFA_aState53Output1Conf, DFA_aState53Output2Conf, DFA_aState53Output3Conf, DFA_aState53Output4Conf, },
    { DFA_aState54Output1Conf, DFA_aState54Output2Conf, DFA_aState54Output3Conf, DFA_aState54Output4Conf, },
    { DFA_aState55Output1Conf, DFA_aState55Output2Conf, DFA_aState55Output3Conf, DFA_aState55Output4Conf, },
    { DFA_aState56Output1Conf, DFA_aState56Output2Conf, DFA_aState56Output3Conf, DFA_aState56Output4Conf, },
    { DFA_aState57Output1Conf, DFA_aState57Output2Conf, DFA_aState57Output3Conf, DFA_aState57Output4Conf, },
    { DFA_aState58Output1Conf, DFA_aState58Output2Conf, DFA_aState58Output3Conf, DFA_aState58Output4Conf, },
    { DFA_aState59Output1Conf, DFA_aState59Output2Conf, DFA_aState59Output3Conf, DFA_aState59Output4Conf, },
    { DFA_aState60Output1Conf, DFA_aState60Output2Conf, DFA_aState60Output3Conf, DFA_aState60Output4Conf, },
    { DFA_aState61Output1Conf, DFA_aState61Output2Conf, DFA_aState61Output3Conf, DFA_aState61Output4Conf, },
    { DFA_aState62Output1Conf, DFA_aState62Output2Conf, DFA_aState62Output3Conf, DFA_aState62Output4Conf, },
    { DFA_aState63Output1Conf, DFA_aState63Output2Conf, DFA_aState63Output3Conf, DFA_aState63Output4Conf, },
    { DFA_aState64Output1Conf, DFA_aState64Output2Conf, DFA_aState64Output3Conf, DFA_aState64Output4Conf, },
    */
};
const uint16_t DfaChannel::_outputValuePRI[DFA_DEF_STATES_COUNT][DFA_DEF_OUTPUTS_COUNT] = {
    // TODO ensure same position of all Outputs
    { DFA_aState01Output1TypeDpt1, DFA_aState01Output2TypeDpt1, DFA_aState01Output3TypeDpt1, DFA_aState01Output4TypeDpt1, },
    { DFA_aState02Output1TypeDpt1, DFA_aState02Output2TypeDpt1, DFA_aState02Output3TypeDpt1, DFA_aState02Output4TypeDpt1, },
    { DFA_aState03Output1TypeDpt1, DFA_aState03Output2TypeDpt1, DFA_aState03Output3TypeDpt1, DFA_aState03Output4TypeDpt1, },
    { DFA_aState04Output1TypeDpt1, DFA_aState04Output2TypeDpt1, DFA_aState04Output3TypeDpt1, DFA_aState04Output4TypeDpt1, },
    { DFA_aState05Output1TypeDpt1, DFA_aState05Output2TypeDpt1, DFA_aState05Output3TypeDpt1, DFA_aState05Output4TypeDpt1, },
    { DFA_aState06Output1TypeDpt1, DFA_aState06Output2TypeDpt1, DFA_aState06Output3TypeDpt1, DFA_aState06Output4TypeDpt1, },
    { DFA_aState07Output1TypeDpt1, DFA_aState07Output2TypeDpt1, DFA_aState07Output3TypeDpt1, DFA_aState07Output4TypeDpt1, },
    { DFA_aState08Output1TypeDpt1, DFA_aState08Output2TypeDpt1, DFA_aState08Output3TypeDpt1, DFA_aState08Output4TypeDpt1, },
    { DFA_aState09Output1TypeDpt1, DFA_aState09Output2TypeDpt1, DFA_aState09Output3TypeDpt1, DFA_aState09Output4TypeDpt1, },
    { DFA_aState10Output1TypeDpt1, DFA_aState10Output2TypeDpt1, DFA_aState10Output3TypeDpt1, DFA_aState10Output4TypeDpt1, },
    { DFA_aState11Output1TypeDpt1, DFA_aState11Output2TypeDpt1, DFA_aState11Output3TypeDpt1, DFA_aState11Output4TypeDpt1, },
    { DFA_aState12Output1TypeDpt1, DFA_aState12Output2TypeDpt1, DFA_aState12Output3TypeDpt1, DFA_aState12Output4TypeDpt1, },
    { DFA_aState13Output1TypeDpt1, DFA_aState13Output2TypeDpt1, DFA_aState13Output3TypeDpt1, DFA_aState13Output4TypeDpt1, },
    { DFA_aState14Output1TypeDpt1, DFA_aState14Output2TypeDpt1, DFA_aState14Output3TypeDpt1, DFA_aState14Output4TypeDpt1, },
    { DFA_aState15Output1TypeDpt1, DFA_aState15Output2TypeDpt1, DFA_aState15Output3TypeDpt1, DFA_aState15Output4TypeDpt1, },
    { DFA_aState16Output1TypeDpt1, DFA_aState16Output2TypeDpt1, DFA_aState16Output3TypeDpt1, DFA_aState16Output4TypeDpt1, },
    { DFA_aState17Output1TypeDpt1, DFA_aState17Output2TypeDpt1, DFA_aState17Output3TypeDpt1, DFA_aState17Output4TypeDpt1, },
    { DFA_aState18Output1TypeDpt1, DFA_aState18Output2TypeDpt1, DFA_aState18Output3TypeDpt1, DFA_aState18Output4TypeDpt1, },
    { DFA_aState19Output1TypeDpt1, DFA_aState19Output2TypeDpt1, DFA_aState19Output3TypeDpt1, DFA_aState19Output4TypeDpt1, },
    { DFA_aState20Output1TypeDpt1, DFA_aState20Output2TypeDpt1, DFA_aState20Output3TypeDpt1, DFA_aState20Output4TypeDpt1, },
    { DFA_aState21Output1TypeDpt1, DFA_aState21Output2TypeDpt1, DFA_aState21Output3TypeDpt1, DFA_aState21Output4TypeDpt1, },
    { DFA_aState22Output1TypeDpt1, DFA_aState22Output2TypeDpt1, DFA_aState22Output3TypeDpt1, DFA_aState22Output4TypeDpt1, },
    { DFA_aState23Output1TypeDpt1, DFA_aState23Output2TypeDpt1, DFA_aState23Output3TypeDpt1, DFA_aState23Output4TypeDpt1, },
    { DFA_aState24Output1TypeDpt1, DFA_aState24Output2TypeDpt1, DFA_aState24Output3TypeDpt1, DFA_aState24Output4TypeDpt1, },
    { DFA_aState25Output1TypeDpt1, DFA_aState25Output2TypeDpt1, DFA_aState25Output3TypeDpt1, DFA_aState25Output4TypeDpt1, },
    { DFA_aState26Output1TypeDpt1, DFA_aState26Output2TypeDpt1, DFA_aState26Output3TypeDpt1, DFA_aState26Output4TypeDpt1, },
    { DFA_aState27Output1TypeDpt1, DFA_aState27Output2TypeDpt1, DFA_aState27Output3TypeDpt1, DFA_aState27Output4TypeDpt1, },
    { DFA_aState28Output1TypeDpt1, DFA_aState28Output2TypeDpt1, DFA_aState28Output3TypeDpt1, DFA_aState28Output4TypeDpt1, },
    { DFA_aState29Output1TypeDpt1, DFA_aState29Output2TypeDpt1, DFA_aState29Output3TypeDpt1, DFA_aState29Output4TypeDpt1, },
    { DFA_aState30Output1TypeDpt1, DFA_aState30Output2TypeDpt1, DFA_aState30Output3TypeDpt1, DFA_aState30Output4TypeDpt1, },
    { DFA_aState31Output1TypeDpt1, DFA_aState31Output2TypeDpt1, DFA_aState31Output3TypeDpt1, DFA_aState31Output4TypeDpt1, },
    { DFA_aState32Output1TypeDpt1, DFA_aState32Output2TypeDpt1, DFA_aState32Output3TypeDpt1, DFA_aState32Output4TypeDpt1, },
    /*
    { DFA_aState33Output1TypeDpt1, DFA_aState33Output2TypeDpt1, DFA_aState33Output3TypeDpt1, DFA_aState33Output4TypeDpt1, },
    { DFA_aState34Output1TypeDpt1, DFA_aState34Output2TypeDpt1, DFA_aState34Output3TypeDpt1, DFA_aState34Output4TypeDpt1, },
    { DFA_aState35Output1TypeDpt1, DFA_aState35Output2TypeDpt1, DFA_aState35Output3TypeDpt1, DFA_aState35Output4TypeDpt1, },
    { DFA_aState36Output1TypeDpt1, DFA_aState36Output2TypeDpt1, DFA_aState36Output3TypeDpt1, DFA_aState36Output4TypeDpt1, },
    { DFA_aState37Output1TypeDpt1, DFA_aState37Output2TypeDpt1, DFA_aState37Output3TypeDpt1, DFA_aState37Output4TypeDpt1, },
    { DFA_aState38Output1TypeDpt1, DFA_aState38Output2TypeDpt1, DFA_aState38Output3TypeDpt1, DFA_aState38Output4TypeDpt1, },
    { DFA_aState39Output1TypeDpt1, DFA_aState39Output2TypeDpt1, DFA_aState39Output3TypeDpt1, DFA_aState39Output4TypeDpt1, },
    { DFA_aState40Output1TypeDpt1, DFA_aState40Output2TypeDpt1, DFA_aState40Output3TypeDpt1, DFA_aState40Output4TypeDpt1, },
    { DFA_aState41Output1TypeDpt1, DFA_aState41Output2TypeDpt1, DFA_aState41Output3TypeDpt1, DFA_aState41Output4TypeDpt1, },
    { DFA_aState42Output1TypeDpt1, DFA_aState42Output2TypeDpt1, DFA_aState42Output3TypeDpt1, DFA_aState42Output4TypeDpt1, },
    { DFA_aState43Output1TypeDpt1, DFA_aState43Output2TypeDpt1, DFA_aState43Output3TypeDpt1, DFA_aState43Output4TypeDpt1, },
    { DFA_aState44Output1TypeDpt1, DFA_aState44Output2TypeDpt1, DFA_aState44Output3TypeDpt1, DFA_aState44Output4TypeDpt1, },
    { DFA_aState45Output1TypeDpt1, DFA_aState45Output2TypeDpt1, DFA_aState45Output3TypeDpt1, DFA_aState45Output4TypeDpt1, },
    { DFA_aState46Output1TypeDpt1, DFA_aState46Output2TypeDpt1, DFA_aState46Output3TypeDpt1, DFA_aState46Output4TypeDpt1, },
    { DFA_aState47Output1TypeDpt1, DFA_aState47Output2TypeDpt1, DFA_aState47Output3TypeDpt1, DFA_aState47Output4TypeDpt1, },
    { DFA_aState48Output1TypeDpt1, DFA_aState48Output2TypeDpt1, DFA_aState48Output3TypeDpt1, DFA_aState48Output4TypeDpt1, },
    { DFA_aState49Output1TypeDpt1, DFA_aState49Output2TypeDpt1, DFA_aState49Output3TypeDpt1, DFA_aState49Output4TypeDpt1, },
    { DFA_aState50Output1TypeDpt1, DFA_aState50Output2TypeDpt1, DFA_aState50Output3TypeDpt1, DFA_aState50Output4TypeDpt1, },
    { DFA_aState51Output1TypeDpt1, DFA_aState51Output2TypeDpt1, DFA_aState51Output3TypeDpt1, DFA_aState51Output4TypeDpt1, },
    { DFA_aState52Output1TypeDpt1, DFA_aState52Output2TypeDpt1, DFA_aState52Output3TypeDpt1, DFA_aState52Output4TypeDpt1, },
    { DFA_aState53Output1TypeDpt1, DFA_aState53Output2TypeDpt1, DFA_aState53Output3TypeDpt1, DFA_aState53Output4TypeDpt1, },
    { DFA_aState54Output1TypeDpt1, DFA_aState54Output2TypeDpt1, DFA_aState54Output3TypeDpt1, DFA_aState54Output4TypeDpt1, },
    { DFA_aState55Output1TypeDpt1, DFA_aState55Output2TypeDpt1, DFA_aState55Output3TypeDpt1, DFA_aState55Output4TypeDpt1, },
    { DFA_aState56Output1TypeDpt1, DFA_aState56Output2TypeDpt1, DFA_aState56Output3TypeDpt1, DFA_aState56Output4TypeDpt1, },
    { DFA_aState57Output1TypeDpt1, DFA_aState57Output2TypeDpt1, DFA_aState57Output3TypeDpt1, DFA_aState57Output4TypeDpt1, },
    { DFA_aState58Output1TypeDpt1, DFA_aState58Output2TypeDpt1, DFA_aState58Output3TypeDpt1, DFA_aState58Output4TypeDpt1, },
    { DFA_aState59Output1TypeDpt1, DFA_aState59Output2TypeDpt1, DFA_aState59Output3TypeDpt1, DFA_aState59Output4TypeDpt1, },
    { DFA_aState60Output1TypeDpt1, DFA_aState60Output2TypeDpt1, DFA_aState60Output3TypeDpt1, DFA_aState60Output4TypeDpt1, },
    { DFA_aState61Output1TypeDpt1, DFA_aState61Output2TypeDpt1, DFA_aState61Output3TypeDpt1, DFA_aState61Output4TypeDpt1, },
    { DFA_aState62Output1TypeDpt1, DFA_aState62Output2TypeDpt1, DFA_aState62Output3TypeDpt1, DFA_aState62Output4TypeDpt1, },
    { DFA_aState63Output1TypeDpt1, DFA_aState63Output2TypeDpt1, DFA_aState63Output3TypeDpt1, DFA_aState63Output4TypeDpt1, },
    { DFA_aState64Output1TypeDpt1, DFA_aState64Output2TypeDpt1, DFA_aState64Output3TypeDpt1, DFA_aState64Output4TypeDpt1, },
    */
};

// TODO calculate index; expected distance should be protected by compile error
// Define (relative) parameter address-index for next state by current state and input

// Value of DFA_KoKOaInput[1-8] by 0-based index
#define DFA_aTransState__N__Input__M__(N, M) DFA_aTransState01Input1 + N * (DFA_aTransState02Input1 - DFA_aTransState01Input1) + M * (DFA_aTransState01Input2 - DFA_aTransState01Input1)
// Value of DFA_KoCalcNumber(DFA_KoKOaInput[1-8]) by 0-based index
#define DFA_Channel_TransferByStateInput(STATE_IDX,IN_IDX) DFA_KoCalcNumber(DFA_aTransState__N__Input__M__(STATE_IDX, IN_IDX))


const uint16_t DfaChannel::_transPRI[DFA_DEF_STATES_COUNT][DFA_DEF_INPUTS_COUNT] = {
    {DFA_aTransState01Input1, DFA_aTransState01Input2, DFA_aTransState01Input3, DFA_aTransState01Input4, DFA_aTransState01Input5, DFA_aTransState01Input6, DFA_aTransState01Input7, DFA_aTransState01Input8},
    {DFA_aTransState02Input1, DFA_aTransState02Input2, DFA_aTransState02Input3, DFA_aTransState02Input4, DFA_aTransState02Input5, DFA_aTransState02Input6, DFA_aTransState02Input7, DFA_aTransState02Input8},
    {DFA_aTransState03Input1, DFA_aTransState03Input2, DFA_aTransState03Input3, DFA_aTransState03Input4, DFA_aTransState03Input5, DFA_aTransState03Input6, DFA_aTransState03Input7, DFA_aTransState03Input8},
    {DFA_aTransState04Input1, DFA_aTransState04Input2, DFA_aTransState04Input3, DFA_aTransState04Input4, DFA_aTransState04Input5, DFA_aTransState04Input6, DFA_aTransState04Input7, DFA_aTransState04Input8},
    {DFA_aTransState05Input1, DFA_aTransState05Input2, DFA_aTransState05Input3, DFA_aTransState05Input4, DFA_aTransState05Input5, DFA_aTransState05Input6, DFA_aTransState05Input7, DFA_aTransState05Input8},
    {DFA_aTransState06Input1, DFA_aTransState06Input2, DFA_aTransState06Input3, DFA_aTransState06Input4, DFA_aTransState06Input5, DFA_aTransState06Input6, DFA_aTransState06Input7, DFA_aTransState06Input8},
    {DFA_aTransState07Input1, DFA_aTransState07Input2, DFA_aTransState07Input3, DFA_aTransState07Input4, DFA_aTransState07Input5, DFA_aTransState07Input6, DFA_aTransState07Input7, DFA_aTransState07Input8},
    {DFA_aTransState08Input1, DFA_aTransState08Input2, DFA_aTransState08Input3, DFA_aTransState08Input4, DFA_aTransState08Input5, DFA_aTransState08Input6, DFA_aTransState08Input7, DFA_aTransState08Input8},
    {DFA_aTransState09Input1, DFA_aTransState09Input2, DFA_aTransState09Input3, DFA_aTransState09Input4, DFA_aTransState09Input5, DFA_aTransState09Input6, DFA_aTransState09Input7, DFA_aTransState09Input8},
    {DFA_aTransState10Input1, DFA_aTransState10Input2, DFA_aTransState10Input3, DFA_aTransState10Input4, DFA_aTransState10Input5, DFA_aTransState10Input6, DFA_aTransState10Input7, DFA_aTransState10Input8},
    {DFA_aTransState11Input1, DFA_aTransState11Input2, DFA_aTransState11Input3, DFA_aTransState11Input4, DFA_aTransState11Input5, DFA_aTransState11Input6, DFA_aTransState11Input7, DFA_aTransState11Input8},
    {DFA_aTransState12Input1, DFA_aTransState12Input2, DFA_aTransState12Input3, DFA_aTransState12Input4, DFA_aTransState12Input5, DFA_aTransState12Input6, DFA_aTransState12Input7, DFA_aTransState12Input8},
    {DFA_aTransState13Input1, DFA_aTransState13Input2, DFA_aTransState13Input3, DFA_aTransState13Input4, DFA_aTransState13Input5, DFA_aTransState13Input6, DFA_aTransState13Input7, DFA_aTransState13Input8},
    {DFA_aTransState14Input1, DFA_aTransState14Input2, DFA_aTransState14Input3, DFA_aTransState14Input4, DFA_aTransState14Input5, DFA_aTransState14Input6, DFA_aTransState14Input7, DFA_aTransState14Input8},
    {DFA_aTransState15Input1, DFA_aTransState15Input2, DFA_aTransState15Input3, DFA_aTransState15Input4, DFA_aTransState15Input5, DFA_aTransState15Input6, DFA_aTransState15Input7, DFA_aTransState15Input8},
    {DFA_aTransState16Input1, DFA_aTransState16Input2, DFA_aTransState16Input3, DFA_aTransState16Input4, DFA_aTransState16Input5, DFA_aTransState16Input6, DFA_aTransState16Input7, DFA_aTransState16Input8},
    {DFA_aTransState17Input1, DFA_aTransState17Input2, DFA_aTransState17Input3, DFA_aTransState17Input4, DFA_aTransState17Input5, DFA_aTransState17Input6, DFA_aTransState17Input7, DFA_aTransState17Input8},
    {DFA_aTransState18Input1, DFA_aTransState18Input2, DFA_aTransState18Input3, DFA_aTransState18Input4, DFA_aTransState18Input5, DFA_aTransState18Input6, DFA_aTransState18Input7, DFA_aTransState18Input8},
    {DFA_aTransState19Input1, DFA_aTransState19Input2, DFA_aTransState19Input3, DFA_aTransState19Input4, DFA_aTransState19Input5, DFA_aTransState19Input6, DFA_aTransState19Input7, DFA_aTransState19Input8},
    {DFA_aTransState20Input1, DFA_aTransState20Input2, DFA_aTransState20Input3, DFA_aTransState20Input4, DFA_aTransState20Input5, DFA_aTransState20Input6, DFA_aTransState20Input7, DFA_aTransState20Input8},
    {DFA_aTransState21Input1, DFA_aTransState21Input2, DFA_aTransState21Input3, DFA_aTransState21Input4, DFA_aTransState21Input5, DFA_aTransState21Input6, DFA_aTransState21Input7, DFA_aTransState21Input8},
    {DFA_aTransState22Input1, DFA_aTransState22Input2, DFA_aTransState22Input3, DFA_aTransState22Input4, DFA_aTransState22Input5, DFA_aTransState22Input6, DFA_aTransState22Input7, DFA_aTransState22Input8},
    {DFA_aTransState23Input1, DFA_aTransState23Input2, DFA_aTransState23Input3, DFA_aTransState23Input4, DFA_aTransState23Input5, DFA_aTransState23Input6, DFA_aTransState23Input7, DFA_aTransState23Input8},
    {DFA_aTransState24Input1, DFA_aTransState24Input2, DFA_aTransState24Input3, DFA_aTransState24Input4, DFA_aTransState24Input5, DFA_aTransState24Input6, DFA_aTransState24Input7, DFA_aTransState24Input8},
    {DFA_aTransState25Input1, DFA_aTransState25Input2, DFA_aTransState25Input3, DFA_aTransState25Input4, DFA_aTransState25Input5, DFA_aTransState25Input6, DFA_aTransState25Input7, DFA_aTransState25Input8},
    {DFA_aTransState26Input1, DFA_aTransState26Input2, DFA_aTransState26Input3, DFA_aTransState26Input4, DFA_aTransState26Input5, DFA_aTransState26Input6, DFA_aTransState26Input7, DFA_aTransState26Input8},
    {DFA_aTransState27Input1, DFA_aTransState27Input2, DFA_aTransState27Input3, DFA_aTransState27Input4, DFA_aTransState27Input5, DFA_aTransState27Input6, DFA_aTransState27Input7, DFA_aTransState27Input8},
    {DFA_aTransState28Input1, DFA_aTransState28Input2, DFA_aTransState28Input3, DFA_aTransState28Input4, DFA_aTransState28Input5, DFA_aTransState28Input6, DFA_aTransState28Input7, DFA_aTransState28Input8},
    {DFA_aTransState29Input1, DFA_aTransState29Input2, DFA_aTransState29Input3, DFA_aTransState29Input4, DFA_aTransState29Input5, DFA_aTransState29Input6, DFA_aTransState29Input7, DFA_aTransState29Input8},
    {DFA_aTransState30Input1, DFA_aTransState30Input2, DFA_aTransState30Input3, DFA_aTransState30Input4, DFA_aTransState30Input5, DFA_aTransState30Input6, DFA_aTransState30Input7, DFA_aTransState30Input8},
    {DFA_aTransState31Input1, DFA_aTransState31Input2, DFA_aTransState31Input3, DFA_aTransState31Input4, DFA_aTransState31Input5, DFA_aTransState31Input6, DFA_aTransState31Input7, DFA_aTransState31Input8},
    {DFA_aTransState32Input1, DFA_aTransState32Input2, DFA_aTransState32Input3, DFA_aTransState32Input4, DFA_aTransState32Input5, DFA_aTransState32Input6, DFA_aTransState32Input7, DFA_aTransState32Input8},
    /*
    {DFA_aTransState33Input1, DFA_aTransState33Input2, DFA_aTransState33Input3, DFA_aTransState33Input4, DFA_aTransState33Input5, DFA_aTransState33Input6, DFA_aTransState33Input7, DFA_aTransState33Input8},
    {DFA_aTransState34Input1, DFA_aTransState34Input2, DFA_aTransState34Input3, DFA_aTransState34Input4, DFA_aTransState34Input5, DFA_aTransState34Input6, DFA_aTransState34Input7, DFA_aTransState34Input8},
    {DFA_aTransState35Input1, DFA_aTransState35Input2, DFA_aTransState35Input3, DFA_aTransState35Input4, DFA_aTransState35Input5, DFA_aTransState35Input6, DFA_aTransState35Input7, DFA_aTransState35Input8},
    {DFA_aTransState36Input1, DFA_aTransState36Input2, DFA_aTransState36Input3, DFA_aTransState36Input4, DFA_aTransState36Input5, DFA_aTransState36Input6, DFA_aTransState36Input7, DFA_aTransState36Input8},
    {DFA_aTransState37Input1, DFA_aTransState37Input2, DFA_aTransState37Input3, DFA_aTransState37Input4, DFA_aTransState37Input5, DFA_aTransState37Input6, DFA_aTransState37Input7, DFA_aTransState37Input8},
    {DFA_aTransState38Input1, DFA_aTransState38Input2, DFA_aTransState38Input3, DFA_aTransState38Input4, DFA_aTransState38Input5, DFA_aTransState38Input6, DFA_aTransState38Input7, DFA_aTransState38Input8},
    {DFA_aTransState39Input1, DFA_aTransState39Input2, DFA_aTransState39Input3, DFA_aTransState39Input4, DFA_aTransState39Input5, DFA_aTransState39Input6, DFA_aTransState39Input7, DFA_aTransState39Input8},
    {DFA_aTransState40Input1, DFA_aTransState40Input2, DFA_aTransState40Input3, DFA_aTransState40Input4, DFA_aTransState40Input5, DFA_aTransState40Input6, DFA_aTransState40Input7, DFA_aTransState40Input8},
    {DFA_aTransState41Input1, DFA_aTransState41Input2, DFA_aTransState41Input3, DFA_aTransState41Input4, DFA_aTransState41Input5, DFA_aTransState41Input6, DFA_aTransState41Input7, DFA_aTransState41Input8},
    {DFA_aTransState42Input1, DFA_aTransState42Input2, DFA_aTransState42Input3, DFA_aTransState42Input4, DFA_aTransState42Input5, DFA_aTransState42Input6, DFA_aTransState42Input7, DFA_aTransState42Input8},
    {DFA_aTransState43Input1, DFA_aTransState43Input2, DFA_aTransState43Input3, DFA_aTransState43Input4, DFA_aTransState43Input5, DFA_aTransState43Input6, DFA_aTransState43Input7, DFA_aTransState43Input8},
    {DFA_aTransState44Input1, DFA_aTransState44Input2, DFA_aTransState44Input3, DFA_aTransState44Input4, DFA_aTransState44Input5, DFA_aTransState44Input6, DFA_aTransState44Input7, DFA_aTransState44Input8},
    {DFA_aTransState45Input1, DFA_aTransState45Input2, DFA_aTransState45Input3, DFA_aTransState45Input4, DFA_aTransState45Input5, DFA_aTransState45Input6, DFA_aTransState45Input7, DFA_aTransState45Input8},
    {DFA_aTransState46Input1, DFA_aTransState46Input2, DFA_aTransState46Input3, DFA_aTransState46Input4, DFA_aTransState46Input5, DFA_aTransState46Input6, DFA_aTransState46Input7, DFA_aTransState46Input8},
    {DFA_aTransState47Input1, DFA_aTransState47Input2, DFA_aTransState47Input3, DFA_aTransState47Input4, DFA_aTransState47Input5, DFA_aTransState47Input6, DFA_aTransState47Input7, DFA_aTransState47Input8},
    {DFA_aTransState48Input1, DFA_aTransState48Input2, DFA_aTransState48Input3, DFA_aTransState48Input4, DFA_aTransState48Input5, DFA_aTransState48Input6, DFA_aTransState48Input7, DFA_aTransState48Input8},
    {DFA_aTransState49Input1, DFA_aTransState49Input2, DFA_aTransState49Input3, DFA_aTransState49Input4, DFA_aTransState49Input5, DFA_aTransState49Input6, DFA_aTransState49Input7, DFA_aTransState49Input8},
    {DFA_aTransState50Input1, DFA_aTransState50Input2, DFA_aTransState50Input3, DFA_aTransState50Input4, DFA_aTransState50Input5, DFA_aTransState50Input6, DFA_aTransState50Input7, DFA_aTransState50Input8},
    {DFA_aTransState51Input1, DFA_aTransState51Input2, DFA_aTransState51Input3, DFA_aTransState51Input4, DFA_aTransState51Input5, DFA_aTransState51Input6, DFA_aTransState51Input7, DFA_aTransState51Input8},
    {DFA_aTransState52Input1, DFA_aTransState52Input2, DFA_aTransState52Input3, DFA_aTransState52Input4, DFA_aTransState52Input5, DFA_aTransState52Input6, DFA_aTransState52Input7, DFA_aTransState52Input8},
    {DFA_aTransState53Input1, DFA_aTransState53Input2, DFA_aTransState53Input3, DFA_aTransState53Input4, DFA_aTransState53Input5, DFA_aTransState53Input6, DFA_aTransState53Input7, DFA_aTransState53Input8},
    {DFA_aTransState54Input1, DFA_aTransState54Input2, DFA_aTransState54Input3, DFA_aTransState54Input4, DFA_aTransState54Input5, DFA_aTransState54Input6, DFA_aTransState54Input7, DFA_aTransState54Input8},
    {DFA_aTransState55Input1, DFA_aTransState55Input2, DFA_aTransState55Input3, DFA_aTransState55Input4, DFA_aTransState55Input5, DFA_aTransState55Input6, DFA_aTransState55Input7, DFA_aTransState55Input8},
    {DFA_aTransState56Input1, DFA_aTransState56Input2, DFA_aTransState56Input3, DFA_aTransState56Input4, DFA_aTransState56Input5, DFA_aTransState56Input6, DFA_aTransState56Input7, DFA_aTransState56Input8},
    {DFA_aTransState57Input1, DFA_aTransState57Input2, DFA_aTransState57Input3, DFA_aTransState57Input4, DFA_aTransState57Input5, DFA_aTransState57Input6, DFA_aTransState57Input7, DFA_aTransState57Input8},
    {DFA_aTransState58Input1, DFA_aTransState58Input2, DFA_aTransState58Input3, DFA_aTransState58Input4, DFA_aTransState58Input5, DFA_aTransState58Input6, DFA_aTransState58Input7, DFA_aTransState58Input8},
    {DFA_aTransState59Input1, DFA_aTransState59Input2, DFA_aTransState59Input3, DFA_aTransState59Input4, DFA_aTransState59Input5, DFA_aTransState59Input6, DFA_aTransState59Input7, DFA_aTransState59Input8},
    {DFA_aTransState60Input1, DFA_aTransState60Input2, DFA_aTransState60Input3, DFA_aTransState60Input4, DFA_aTransState60Input5, DFA_aTransState60Input6, DFA_aTransState60Input7, DFA_aTransState60Input8},
    {DFA_aTransState61Input1, DFA_aTransState61Input2, DFA_aTransState61Input3, DFA_aTransState61Input4, DFA_aTransState61Input5, DFA_aTransState61Input6, DFA_aTransState61Input7, DFA_aTransState61Input8},
    {DFA_aTransState62Input1, DFA_aTransState62Input2, DFA_aTransState62Input3, DFA_aTransState62Input4, DFA_aTransState62Input5, DFA_aTransState62Input6, DFA_aTransState62Input7, DFA_aTransState62Input8},
    {DFA_aTransState63Input1, DFA_aTransState63Input2, DFA_aTransState63Input3, DFA_aTransState63Input4, DFA_aTransState63Input5, DFA_aTransState63Input6, DFA_aTransState63Input7, DFA_aTransState63Input8},
    {DFA_aTransState64Input1, DFA_aTransState64Input2, DFA_aTransState64Input3, DFA_aTransState64Input4, DFA_aTransState64Input5, DFA_aTransState64Input6, DFA_aTransState64Input7, DFA_aTransState64Input8},
    */
};

// TODO calculate index; expected distance should be protected by compile error
// Define (relative) parameter address-index for timeout duration and timeout state
const DfaStateTimeoutParamRelIdx DfaChannel::_timeoutPRI[DFA_DEF_STATES_COUNT] = {
    {DFA_aState01TimeoutTime, DFA_aTransState01Timeout},
    {DFA_aState02TimeoutTime, DFA_aTransState02Timeout},
    {DFA_aState03TimeoutTime, DFA_aTransState03Timeout},
    {DFA_aState04TimeoutTime, DFA_aTransState04Timeout},
    {DFA_aState05TimeoutTime, DFA_aTransState05Timeout},
    {DFA_aState06TimeoutTime, DFA_aTransState06Timeout},
    {DFA_aState07TimeoutTime, DFA_aTransState07Timeout},
    {DFA_aState08TimeoutTime, DFA_aTransState08Timeout},
    {DFA_aState09TimeoutTime, DFA_aTransState09Timeout},
    {DFA_aState10TimeoutTime, DFA_aTransState10Timeout},
    {DFA_aState11TimeoutTime, DFA_aTransState11Timeout},
    {DFA_aState12TimeoutTime, DFA_aTransState12Timeout},
    {DFA_aState13TimeoutTime, DFA_aTransState13Timeout},
    {DFA_aState14TimeoutTime, DFA_aTransState14Timeout},
    {DFA_aState15TimeoutTime, DFA_aTransState15Timeout},
    {DFA_aState16TimeoutTime, DFA_aTransState16Timeout},
    {DFA_aState17TimeoutTime, DFA_aTransState17Timeout},
    {DFA_aState18TimeoutTime, DFA_aTransState18Timeout},
    {DFA_aState19TimeoutTime, DFA_aTransState19Timeout},
    {DFA_aState20TimeoutTime, DFA_aTransState20Timeout},
    {DFA_aState21TimeoutTime, DFA_aTransState21Timeout},
    {DFA_aState22TimeoutTime, DFA_aTransState22Timeout},
    {DFA_aState23TimeoutTime, DFA_aTransState23Timeout},
    {DFA_aState24TimeoutTime, DFA_aTransState24Timeout},
    {DFA_aState25TimeoutTime, DFA_aTransState25Timeout},
    {DFA_aState26TimeoutTime, DFA_aTransState26Timeout},
    {DFA_aState27TimeoutTime, DFA_aTransState27Timeout},
    {DFA_aState28TimeoutTime, DFA_aTransState28Timeout},
    {DFA_aState29TimeoutTime, DFA_aTransState29Timeout},
    {DFA_aState30TimeoutTime, DFA_aTransState30Timeout},
    {DFA_aState31TimeoutTime, DFA_aTransState31Timeout},
    {DFA_aState32TimeoutTime, DFA_aTransState32Timeout},
    /*
    {DFA_aState33TimeoutTime, DFA_aTransState33Timeout},
    {DFA_aState34TimeoutTime, DFA_aTransState34Timeout},
    {DFA_aState35TimeoutTime, DFA_aTransState35Timeout},
    {DFA_aState36TimeoutTime, DFA_aTransState36Timeout},
    {DFA_aState37TimeoutTime, DFA_aTransState37Timeout},
    {DFA_aState38TimeoutTime, DFA_aTransState38Timeout},
    {DFA_aState39TimeoutTime, DFA_aTransState39Timeout},
    {DFA_aState40TimeoutTime, DFA_aTransState40Timeout},
    {DFA_aState41TimeoutTime, DFA_aTransState41Timeout},
    {DFA_aState42TimeoutTime, DFA_aTransState42Timeout},
    {DFA_aState43TimeoutTime, DFA_aTransState43Timeout},
    {DFA_aState44TimeoutTime, DFA_aTransState44Timeout},
    {DFA_aState45TimeoutTime, DFA_aTransState45Timeout},
    {DFA_aState46TimeoutTime, DFA_aTransState46Timeout},
    {DFA_aState47TimeoutTime, DFA_aTransState47Timeout},
    {DFA_aState48TimeoutTime, DFA_aTransState48Timeout},
    {DFA_aState49TimeoutTime, DFA_aTransState49Timeout},
    {DFA_aState50TimeoutTime, DFA_aTransState50Timeout},
    {DFA_aState51TimeoutTime, DFA_aTransState51Timeout},
    {DFA_aState52TimeoutTime, DFA_aTransState52Timeout},
    {DFA_aState53TimeoutTime, DFA_aTransState53Timeout},
    {DFA_aState54TimeoutTime, DFA_aTransState54Timeout},
    {DFA_aState55TimeoutTime, DFA_aTransState55Timeout},
    {DFA_aState56TimeoutTime, DFA_aTransState56Timeout},
    {DFA_aState57TimeoutTime, DFA_aTransState57Timeout},
    {DFA_aState58TimeoutTime, DFA_aTransState58Timeout},
    {DFA_aState59TimeoutTime, DFA_aTransState59Timeout},
    {DFA_aState60TimeoutTime, DFA_aTransState60Timeout},
    {DFA_aState61TimeoutTime, DFA_aTransState61Timeout},
    {DFA_aState62TimeoutTime, DFA_aTransState62Timeout},
    {DFA_aState63TimeoutTime, DFA_aTransState63Timeout},
    {DFA_aState64TimeoutTime, DFA_aTransState64Timeout},
    */
};

#pragma endregion "DFA_CHANNEL_ADDR"

#pragma region "DFA_CHANNEL_BASE"

DfaChannel::DfaChannel(uint8_t index)
{
    _channelIndex = index;
}

const std::string DfaChannel::name()
{
    return "DFA-Channel";
}

#pragma endregion "DFA_CHANNEL_BASE"

void DfaChannel::setup()
{
    _channelActive = (ParamDFA_aActive == 0b01);
    logDebugP("setup (act=%d dly=%ds run=%d)", _channelActive, ParamDFA_aStartupDelayTimeMS / 1000, ParamDFA_aStartPause != 0b00);

    if (_channelActive)
    {
        initInputConfig();

        _firstState = DFA_STATE_PARAM_XOR ^ ParamDFA_aStateStart;
        // _firstStateTimeoutDelay_ms = getStateTimeoutDelay_ms(_firstState);

        // starting in processAfterStartupDelay() ...
        // TODO check/fix calculation of remaining delay 
    }
}

#pragma region "DFA_CHANNEL_INPUT_INIT"

uint16_t DfaChannel::getInputKo(const uint8_t input)
{
    // TODO check shift and mark for all
    const uint8_t inputConf = ((knx.paramByte(DFA_ParamCalcIndex(_inputConfPRI[input])) & DFA_aInputSymbol1KoMask) >> DFA_aInputSymbol1KoShift);
    // logDebugP("  get ko for input=%i -> conf=%i", input, inputConf);
    switch (inputConf)
    {
        case 1: // Own KO
            return DFA_KoCalcNumber(_inputKo[input]);
        case 3: // Logic-Output (KO)
            {
                // TODO optimize/use API for this
                // overlay for _channelIndex!
                const u_int16_t logicNumber = knx.paramWord(DFA_ParamCalcIndex(_inputConfNumberPRI[input]));
                const u_int16_t _channelIndex = logicNumber - 1;
                return LOG_KoCalcNumber(LOG_KoKOfO);
            }
        case 2: // Existing KO
            return knx.paramWord(DFA_ParamCalcIndex(_inputConfNumberPRI[input]));
    }
    // default, including case 0 (disabled)
    return 0;
}

void DfaChannel::initInputConfig()
{
    const bool combined[DFA_DEF_INPUTS_COUNT / 2] = {ParamDFA_aInputCombinedAB, ParamDFA_aInputCombinedCD, ParamDFA_aInputCombinedEF, ParamDFA_aInputCombinedGH};
    for (uint8_t iPair = 0; iPair < DFA_DEF_INPUTS_COUNT / 2; iPair++)
    {
        // logDebugP("input-pair %d", iPair);
        // logDebugP("input[%d]: ko=%d trigger=%d", i, _inputs[i].koNumber, _inputs[i].trigger);
        const uint8_t iFirst = iPair * 2;
        const uint8_t iSecond = iFirst + 1;
        logDebugP("input-pair %d, first=%d, second=%d; ispair=%d", iPair, iFirst, iSecond, combined[iPair]);
        if (combined[iPair])
        {
            // single input for 2 symbols
            const uint16_t koNumber = getInputKo(iFirst);

            _inputs[iFirst].koNumber = koNumber;
            _inputs[iFirst].trigger = (koNumber > 0) ? INPUT_TRIGGER_1 : INPUT_TRIGGER_DISABLED;
            _inputs[iSecond].koNumber = koNumber;
            _inputs[iSecond].trigger = (koNumber > 0) ? INPUT_TRIGGER_0 : INPUT_TRIGGER_DISABLED;
        }
        else
        {
            // separate input for 2 symbols
            for (uint8_t i = iFirst; i <= iSecond; i++)
            {
                const uint16_t koNumber = getInputKo(i);
                _inputs[i].koNumber = koNumber;
                if (koNumber > 0)
                {
                    // TODO define ParamDFA_aInputSymbolNUMBERValue
                    _inputs[i].trigger = ((knx.paramByte(DFA_ParamCalcIndex(_inputTriggerPRI[i])) & DFA_aInputSymbol1ValueMask) >> DFA_aInputSymbol1ValueShift);
                }
                else
                {
                    _inputs[i].trigger = INPUT_TRIGGER_DISABLED;
                }
                logDebugP("  separate: %d ko=%i trigger=%i", i, koNumber, _inputs[i].trigger);
            }
        }
    }
    for (size_t i = 0; i < DFA_DEF_INPUTS_COUNT; i++)
    {
        logDebugP("input[%d]: ko=%d trigger=%d", i, _inputs[i].koNumber, _inputs[i].trigger);
    }
}

#pragma endregion "DFA_CHANNEL_INPUT_INIT"

void DfaChannel::processAfterStartupDelay()
{
    // start after device global delay
    if (_channelActive)
    {
        logDebugP("processAfterStartupDelay");
        _processStartupDelay = true;
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
            // timeout of state

            // logDebugP("timeout reached (@%d+%dms >=%d)", _stateTimeoutBegin_ms, _stateTimeoutDelay_ms, millis());
            // TODO check creation of method transferTimeout()
            setState(getTimeoutState(_state));
        }
        else
        {
            // cyclic sending
            for (uint8_t i = 0; i < DFA_DEF_OUTPUTS_COUNT; i++)
                outputLoop(i); // TODO check using break on actual sending, to limit sending to 1 per loop
        }
    }
    else if (_processStartupDelay && delayCheckMillis(_startupDelayBegin_ms, ParamDFA_aStartupDelayTimeMS))
    {
        _processStartupDelay = false;

        // set to running. This includes setting the start state
        setRunning(ParamDFA_aStartPause != 0b00, true);
    }
}

void DfaChannel::outputLoop(const uint8_t i)
{
    if (_outputsTimeout[i].delay_ms > 0 && delayCheckMillis(_outputsTimeout[i].begin_ms, _outputsTimeout[i].delay_ms))
    {
        // force send for cyclic sending
        outputUpdate(i, true, true);
        _outputsTimeout[i].begin_ms = millis(); // TODO check remove, as this should be updated on actual sending only
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
            logDebugP("processInputKo set state (separate)");
            setState(ko.value(DPT_SceneNumber));
        }
        else if (koNumber == DFA_KoCalcNumber(DFA_KoKOaState) && ParamDFA_aStateSetting == 0b10)
        {
            // TODO ensure not processing when result of own sending!
            logDebugP("processInputKo set state (combined)");
            setState(ko.value(DPT_SceneNumber));
        }
        else if (ko.valueSize() == 1) // TODO check if adequate, or add support for other input types
        {
            const bool value = ko.value(DPT_Switch);

            // check (new or existing) inputs based on ko-numbers
            for (size_t i = 0; i < DFA_DEF_INPUTS_COUNT; i++)
            {
                if (koNumber == _inputs[i].koNumber)
                {
                    const bool triggered = _inputs[i].trigger & (1 << value);
                    logDebugP("processInputKo input=%d (ko=%d; triggered=%d)", i + 1, koNumber, triggered);
                    if (triggered)
                    {
                        transfer(i);
                        break; // only one! // TODO check
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
            logDebugP("restore: ParamDFA_aStateRestore=%d _firstStateTimeoutDelay_ms=%d ParamDFA_aChannelDelayTimeMS=%d", ParamDFA_aStateRestore, _firstStateTimeoutDelay_ms, ParamDFA_aStartupDelayTimeMS);
            if (ParamDFA_aStateRestore & 0b10 && _firstStateTimeoutDelay_ms > 0)
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

    if (send && (ParamDFA_aStartPause < 0b10))
        KoDFA_KOaRunning.value(_running, DPT_State);
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
    if (isValidState(nextState))
    {
        const bool stateChanged = (_state != nextState);

        _state = nextState;
        // reset timeout
        _stateTimeoutDelay_ms = getStateTimeoutDelay_ms(nextState);
        resetTimeout();

        // send state
        GroupObject *ko = &KoDFA_KOaState;
        if (ko->valueNoSendCompare(_state, DPT_SceneNumber))
            ko->objectWritten();

        // if (_stateTimeoutDelay_ms > 0)
        //     logDebugP("  with timeout state %d after %dms", getTimeoutState(nextState), _stateTimeoutDelay_ms);

        // send output values
        // TODO extract
        const uint32_t outputDelays[DFA_DEF_OUTPUTS_COUNT] = {
            ParamDFA_aOutput1DelayTimeMS,
            ParamDFA_aOutput2DelayTimeMS,
            ParamDFA_aOutput3DelayTimeMS,
            ParamDFA_aOutput4DelayTimeMS,
        };
        for (uint8_t i = 0; i < DFA_DEF_OUTPUTS_COUNT; i++)
        {
            const uint8_t outputStateSend = outputGetCurrentStateSendConfig(i);

            const bool updateKo = (outputStateSend & OUTPUT_UPDATE_KO);
            const bool sendOnChangedValue = (outputStateSend & OUTPUT_SEND_ON_VALUE_CHANGE);
            const bool sendOnChangedState = (outputStateSend & OUTPUT_SEND_ON_STATE_CHANGE);
            const bool sendAlways = (outputStateSend & OUTPUT_SEND_ALWAYS);
            const bool repeatedSending = (outputStateSend & OUTPUT_REPEATED_SEND);

            const bool cyclicSending = (outputGetDpt(i) != 0) && repeatedSending;
            _outputsTimeout[i].delay_ms = cyclicSending ? outputDelays[i] : 0;

            logDebugP("Output<%d>: ko=%i on~Val=%i on~State=%i all=%i ; cyclic=%i",
                      i + 1, updateKo, sendOnChangedValue, sendOnChangedState, sendAlways, repeatedSending);

            const bool forceSend = sendAlways || (sendOnChangedState && stateChanged);
            outputUpdate(i, sendOnChangedValue, forceSend);
        }
    }
}

#pragma region "DFA_CHANNEL_OUTPUT_SEND"

uint8_t DfaChannel::outputGetDpt(const uint8_t i)
{
    return knx.paramByte(DFA_ParamCalcIndex(_outputDptPRI[i]));
}

uint8_t DfaChannel::outputGetCurrentStateSendConfig(const uint8_t i)
{
    return knx.paramByte(DFA_ParamCalcIndex(_outputSendPRI[_state][i]));
}

/*bool*/ void DfaChannel::outputUpdateKO(const uint8_t i, const KNXValue &value, const Dpt &type, const bool send /* = false */, const bool forceSend /* = false */)
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
        _outputsTimeout[i].begin_ms = millis();
    }
    // return hasSend;
}

void DfaChannel::outputUpdate(const uint8_t i, const bool send, const bool forceSend /* = false */)
{
    const uint8_t outputType = outputGetDpt(i);
    // output is active?
    if (outputType != 0)
    {
        const uint8_t outputStateSend = outputGetCurrentStateSendConfig(i);
        logDebugP("Output<%d>: update (type=%3i); begin=%6ims, dur=%6ims, outputStateSend=%d", i + 1, outputType, _outputsTimeout[i].begin_ms, _outputsTimeout[i].delay_ms, outputStateSend);
        
        // output has value for state?
        if (outputStateSend != 0)
        {
            const uint32_t pIdxValue = DFA_ParamCalcIndex(_outputValuePRI[_state][i]);
            // logDebugP("         -> paramIndex=%i", pIdxValue);

            // set value based on dpt
            switch (outputType)
            {
                case OUTPUT_TYPE_DPT1:
                    // works, as long as using same location as other dpt values
                    outputUpdateKO(i, (knx.paramByte(pIdxValue) != 0), DPT_Switch, send, forceSend);
                    break;
                case OUTPUT_TYPE_DPT2:
                    // TODO check using mask!
                    outputUpdateKO(i, knx.paramByte(pIdxValue), DPT_Switch_Control, send, forceSend);
                    break;
                case OUTPUT_TYPE_DPT5:
                    outputUpdateKO(i, knx.paramByte(pIdxValue), DPT_DecimalFactor, send, forceSend);
                    break;
                case OUTPUT_TYPE_DPT5001:
                    outputUpdateKO(i, knx.paramByte(pIdxValue), DPT_Scaling, send, forceSend);
                    break;                                                
                case OUTPUT_TYPE_DPT6:
                    outputUpdateKO(i, knx.paramSignedByte(pIdxValue), DPT_Value_1_Count, send, forceSend);
                    break;
                case OUTPUT_TYPE_DPT7:
                    outputUpdateKO(i, knx.paramWord(pIdxValue), DPT_Value_2_Ucount, send, forceSend);
                    break;
                case OUTPUT_TYPE_DPT8:
                    outputUpdateKO(i, knx.paramWord(pIdxValue), DPT_Value_2_Count, send, forceSend);
                    break;
                case OUTPUT_TYPE_DPT9:
                    outputUpdateKO(i, knx.paramFloat(pIdxValue, Float_Enc_DPT9), DPT_Value_Temp, send, forceSend);
                    break;
                case OUTPUT_TYPE_DPT12:
                    outputUpdateKO(i, knx.paramInt(pIdxValue), DPT_Value_4_Ucount, send, forceSend);
                    break;
                case OUTPUT_TYPE_DPT13:
                    outputUpdateKO(i, knx.paramInt(pIdxValue), DPT_Value_4_Count, send, forceSend);
                    break;
                case OUTPUT_TYPE_DPT14:
                    outputUpdateKO(i, knx.paramFloat(pIdxValue, Float_Enc_IEEE754Double), DPT_Value_Absolute_Temperature, send, forceSend);
                    break;
                case OUTPUT_TYPE_DPT16:
                    outputUpdateKO(i, (char *)knx.paramData(pIdxValue), DPT_String_8859_1, send, forceSend);
                    break;
                case OUTPUT_TYPE_DPT17:
                    outputUpdateKO(i, knx.paramByte(pIdxValue), DPT_SceneNumber, send, forceSend);
                    break;
                case OUTPUT_TYPE_DPT232:
                    // TODO FIXME Mask
                    outputUpdateKO(i, knx.paramInt(pIdxValue) >> 8, DPT_Colour_RGB, send, forceSend);
                    break;
                default:
                    // TODO check handling undefined cases
                    break;
            }
        }
    }    
}

#pragma endregion "DFA_CHANNEL_OUTPUT_SEND"

void DfaChannel::transfer(const uint8_t input)
{
    if (_state < DFA_DEF_STATES_COUNT && input < DFA_DEF_INPUTS_COUNT)
    {
        const uint16_t nextStateParamIdx = DFA_ParamCalcIndex(_transPRI[_state][input]);
        const uint8_t nextState = DFA_STATE_PARAM_XOR ^ knx.paramByte(nextStateParamIdx);

        logDebugP("transfer(%d,%d)->%d", _state, input, nextState);
        if (isValidState(nextState))
        {
            setState(nextState);
        }
        else if (nextState == DFA_STATE_TIMEOUT_RESET)
        {
            // handling of timeout reset as defined by "<<", do not trigger any other reaction
            resetTimeout();
        }

        // ignore undefined transition
    }
}

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

// TODO check definition of behaviour for non-timeout
uint32_t DfaChannel::timeoutRemaining_ms()
{
    // futureDelay = _stateTimeoutBegin_ms + _stateTimeoutDelay_ms - millis();
    // futureDelay = (_stateTimeoutBegin_ms - millis()) + _stateTimeoutDelay_ms;
    // futureDelay = _stateTimeoutDelay_ms - (millis() - _stateTimeoutBegin_ms)
    // TODO check for correct handling of overflow
    return _stateTimeoutDelay_ms - (millis() - _stateTimeoutBegin_ms);
}

#pragma endregion "DFA_CHANNEL_STATE_TIMEOUT"

#pragma region "DFA_CHANNEL_PERSISTANCE"

void DfaChannel::save()
{
    const uint8_t conf = _channelActive << 7 | _running << 6 | ParamDFA_aStateRestore;
    openknx.flash.writeByte(conf);
    openknx.flash.writeByte(_state);

    const uint32_t futureDelay = timeoutRemaining_ms();
    openknx.flash.writeInt(futureDelay);

    logDebugP("saved c=%2x s=%2x t=%u b=%u f=%u", conf, _state, _stateTimeoutDelay_ms, _stateTimeoutBegin_ms, futureDelay);
}

void DfaChannel::restore()
{
    const uint8_t conf = openknx.flash.readByte();
    const uint8_t state = openknx.flash.readByte();
    const uint32_t timeout = openknx.flash.readInt();
    logDebugP("restored conf=%d state=%d timeout=%d", conf, state, timeout);

    if (ParamDFA_aStateRestore && (conf & 0b11))
    {
        _firstState = state;
        _firstStateTimeoutDelay_ms = timeout;
    }
}

#pragma endregion "DFA_CHANNEL_PERSISTANCE"

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
        else if (cmd.length() == 5)
        {
            // TODO check handling of unexpected inputs!
            uint16_t channelIdx = std::stoi(cmd.substr(3, 2)) - 1;
            if (channelIdx == _channelIndex)
            {
                logDebugP("status and remaining delay");
                const uint8_t state = _state + 1;
                if (_stateTimeoutDelay_ms > 0)
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

                    // TODO FIXME ensure state<100
                    if (timeoutHours < 10)
                    {
                        logDebugP("%02d<%d:%02d:%02d.%03d", state, timeoutHours, timeoutMinutes, timeoutSeconds, timeoutMillis);
                        openknx.console.writeDiagenoseKo("%02d<%d:%02d:%02d.%03d", state, timeoutHours, timeoutMinutes, timeoutSeconds, timeoutMillis);
                    }
                    else
                    {
                        logDebugP("%02d<%5d:%02d:%02d", state, timeoutHours, timeoutMinutes, timeoutSeconds);
                        openknx.console.writeDiagenoseKo("%02d<%5d:%02d:%02d", state, timeoutHours, timeoutMinutes, timeoutSeconds);
                    }
                }
                else
                {
                    logDebugP("%02d<NO_TIMEOUT", state);
                    openknx.console.writeDiagenoseKo("%02d<NO_TIMEOUT", state);
                }
                return true;
            }
        }
    }
    return false;
}
