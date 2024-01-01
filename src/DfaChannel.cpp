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
#if DFA_fInputSymbol1LogicNumber != DFA_fInputSymbol1KoNumber
    #error "DFA_fInputSymbol1LogicNumber != DFA_fInputSymbol1KoNumber"
#endif
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
    { DFA_fState17Output1Conf, DFA_fState17Output2Conf, DFA_fState17Output3Conf, DFA_fState17Output4Conf, },
    { DFA_fState18Output1Conf, DFA_fState18Output2Conf, DFA_fState18Output3Conf, DFA_fState18Output4Conf, },
    { DFA_fState19Output1Conf, DFA_fState19Output2Conf, DFA_fState19Output3Conf, DFA_fState19Output4Conf, },
    { DFA_fState20Output1Conf, DFA_fState20Output2Conf, DFA_fState20Output3Conf, DFA_fState20Output4Conf, },
    { DFA_fState21Output1Conf, DFA_fState21Output2Conf, DFA_fState21Output3Conf, DFA_fState21Output4Conf, },
    { DFA_fState22Output1Conf, DFA_fState22Output2Conf, DFA_fState22Output3Conf, DFA_fState22Output4Conf, },
    { DFA_fState23Output1Conf, DFA_fState23Output2Conf, DFA_fState23Output3Conf, DFA_fState23Output4Conf, },
    { DFA_fState24Output1Conf, DFA_fState24Output2Conf, DFA_fState24Output3Conf, DFA_fState24Output4Conf, },
    { DFA_fState25Output1Conf, DFA_fState25Output2Conf, DFA_fState25Output3Conf, DFA_fState25Output4Conf, },
    { DFA_fState26Output1Conf, DFA_fState26Output2Conf, DFA_fState26Output3Conf, DFA_fState26Output4Conf, },
    { DFA_fState27Output1Conf, DFA_fState27Output2Conf, DFA_fState27Output3Conf, DFA_fState27Output4Conf, },
    { DFA_fState28Output1Conf, DFA_fState28Output2Conf, DFA_fState28Output3Conf, DFA_fState28Output4Conf, },
    { DFA_fState29Output1Conf, DFA_fState29Output2Conf, DFA_fState29Output3Conf, DFA_fState29Output4Conf, },
    { DFA_fState30Output1Conf, DFA_fState30Output2Conf, DFA_fState30Output3Conf, DFA_fState30Output4Conf, },
    { DFA_fState31Output1Conf, DFA_fState31Output2Conf, DFA_fState31Output3Conf, DFA_fState31Output4Conf, },
    { DFA_fState32Output1Conf, DFA_fState32Output2Conf, DFA_fState32Output3Conf, DFA_fState32Output4Conf, },
    /*
    { DFA_fState33Output1Conf, DFA_fState33Output2Conf, DFA_fState33Output3Conf, DFA_fState33Output4Conf, },
    { DFA_fState34Output1Conf, DFA_fState34Output2Conf, DFA_fState34Output3Conf, DFA_fState34Output4Conf, },
    { DFA_fState35Output1Conf, DFA_fState35Output2Conf, DFA_fState35Output3Conf, DFA_fState35Output4Conf, },
    { DFA_fState36Output1Conf, DFA_fState36Output2Conf, DFA_fState36Output3Conf, DFA_fState36Output4Conf, },
    { DFA_fState37Output1Conf, DFA_fState37Output2Conf, DFA_fState37Output3Conf, DFA_fState37Output4Conf, },
    { DFA_fState38Output1Conf, DFA_fState38Output2Conf, DFA_fState38Output3Conf, DFA_fState38Output4Conf, },
    { DFA_fState39Output1Conf, DFA_fState39Output2Conf, DFA_fState39Output3Conf, DFA_fState39Output4Conf, },
    { DFA_fState40Output1Conf, DFA_fState40Output2Conf, DFA_fState40Output3Conf, DFA_fState40Output4Conf, },
    { DFA_fState41Output1Conf, DFA_fState41Output2Conf, DFA_fState41Output3Conf, DFA_fState41Output4Conf, },
    { DFA_fState42Output1Conf, DFA_fState42Output2Conf, DFA_fState42Output3Conf, DFA_fState42Output4Conf, },
    { DFA_fState43Output1Conf, DFA_fState43Output2Conf, DFA_fState43Output3Conf, DFA_fState43Output4Conf, },
    { DFA_fState44Output1Conf, DFA_fState44Output2Conf, DFA_fState44Output3Conf, DFA_fState44Output4Conf, },
    { DFA_fState45Output1Conf, DFA_fState45Output2Conf, DFA_fState45Output3Conf, DFA_fState45Output4Conf, },
    { DFA_fState46Output1Conf, DFA_fState46Output2Conf, DFA_fState46Output3Conf, DFA_fState46Output4Conf, },
    { DFA_fState47Output1Conf, DFA_fState47Output2Conf, DFA_fState47Output3Conf, DFA_fState47Output4Conf, },
    { DFA_fState48Output1Conf, DFA_fState48Output2Conf, DFA_fState48Output3Conf, DFA_fState48Output4Conf, },
    { DFA_fState49Output1Conf, DFA_fState49Output2Conf, DFA_fState49Output3Conf, DFA_fState49Output4Conf, },
    { DFA_fState50Output1Conf, DFA_fState50Output2Conf, DFA_fState50Output3Conf, DFA_fState50Output4Conf, },
    { DFA_fState51Output1Conf, DFA_fState51Output2Conf, DFA_fState51Output3Conf, DFA_fState51Output4Conf, },
    { DFA_fState52Output1Conf, DFA_fState52Output2Conf, DFA_fState52Output3Conf, DFA_fState52Output4Conf, },
    { DFA_fState53Output1Conf, DFA_fState53Output2Conf, DFA_fState53Output3Conf, DFA_fState53Output4Conf, },
    { DFA_fState54Output1Conf, DFA_fState54Output2Conf, DFA_fState54Output3Conf, DFA_fState54Output4Conf, },
    { DFA_fState55Output1Conf, DFA_fState55Output2Conf, DFA_fState55Output3Conf, DFA_fState55Output4Conf, },
    { DFA_fState56Output1Conf, DFA_fState56Output2Conf, DFA_fState56Output3Conf, DFA_fState56Output4Conf, },
    { DFA_fState57Output1Conf, DFA_fState57Output2Conf, DFA_fState57Output3Conf, DFA_fState57Output4Conf, },
    { DFA_fState58Output1Conf, DFA_fState58Output2Conf, DFA_fState58Output3Conf, DFA_fState58Output4Conf, },
    { DFA_fState59Output1Conf, DFA_fState59Output2Conf, DFA_fState59Output3Conf, DFA_fState59Output4Conf, },
    { DFA_fState60Output1Conf, DFA_fState60Output2Conf, DFA_fState60Output3Conf, DFA_fState60Output4Conf, },
    { DFA_fState61Output1Conf, DFA_fState61Output2Conf, DFA_fState61Output3Conf, DFA_fState61Output4Conf, },
    { DFA_fState62Output1Conf, DFA_fState62Output2Conf, DFA_fState62Output3Conf, DFA_fState62Output4Conf, },
    { DFA_fState63Output1Conf, DFA_fState63Output2Conf, DFA_fState63Output3Conf, DFA_fState63Output4Conf, },
    { DFA_fState64Output1Conf, DFA_fState64Output2Conf, DFA_fState64Output3Conf, DFA_fState64Output4Conf, },
    */
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
    { DFA_fState17Output1TypeDpt1, DFA_fState17Output2TypeDpt1, DFA_fState17Output3TypeDpt1, DFA_fState17Output4TypeDpt1, },
    { DFA_fState18Output1TypeDpt1, DFA_fState18Output2TypeDpt1, DFA_fState18Output3TypeDpt1, DFA_fState18Output4TypeDpt1, },
    { DFA_fState19Output1TypeDpt1, DFA_fState19Output2TypeDpt1, DFA_fState19Output3TypeDpt1, DFA_fState19Output4TypeDpt1, },
    { DFA_fState20Output1TypeDpt1, DFA_fState20Output2TypeDpt1, DFA_fState20Output3TypeDpt1, DFA_fState20Output4TypeDpt1, },
    { DFA_fState21Output1TypeDpt1, DFA_fState21Output2TypeDpt1, DFA_fState21Output3TypeDpt1, DFA_fState21Output4TypeDpt1, },
    { DFA_fState22Output1TypeDpt1, DFA_fState22Output2TypeDpt1, DFA_fState22Output3TypeDpt1, DFA_fState22Output4TypeDpt1, },
    { DFA_fState23Output1TypeDpt1, DFA_fState23Output2TypeDpt1, DFA_fState23Output3TypeDpt1, DFA_fState23Output4TypeDpt1, },
    { DFA_fState24Output1TypeDpt1, DFA_fState24Output2TypeDpt1, DFA_fState24Output3TypeDpt1, DFA_fState24Output4TypeDpt1, },
    { DFA_fState25Output1TypeDpt1, DFA_fState25Output2TypeDpt1, DFA_fState25Output3TypeDpt1, DFA_fState25Output4TypeDpt1, },
    { DFA_fState26Output1TypeDpt1, DFA_fState26Output2TypeDpt1, DFA_fState26Output3TypeDpt1, DFA_fState26Output4TypeDpt1, },
    { DFA_fState27Output1TypeDpt1, DFA_fState27Output2TypeDpt1, DFA_fState27Output3TypeDpt1, DFA_fState27Output4TypeDpt1, },
    { DFA_fState28Output1TypeDpt1, DFA_fState28Output2TypeDpt1, DFA_fState28Output3TypeDpt1, DFA_fState28Output4TypeDpt1, },
    { DFA_fState29Output1TypeDpt1, DFA_fState29Output2TypeDpt1, DFA_fState29Output3TypeDpt1, DFA_fState29Output4TypeDpt1, },
    { DFA_fState30Output1TypeDpt1, DFA_fState30Output2TypeDpt1, DFA_fState30Output3TypeDpt1, DFA_fState30Output4TypeDpt1, },
    { DFA_fState31Output1TypeDpt1, DFA_fState31Output2TypeDpt1, DFA_fState31Output3TypeDpt1, DFA_fState31Output4TypeDpt1, },
    { DFA_fState32Output1TypeDpt1, DFA_fState32Output2TypeDpt1, DFA_fState32Output3TypeDpt1, DFA_fState32Output4TypeDpt1, },
    /*
    { DFA_fState33Output1TypeDpt1, DFA_fState33Output2TypeDpt1, DFA_fState33Output3TypeDpt1, DFA_fState33Output4TypeDpt1, },
    { DFA_fState34Output1TypeDpt1, DFA_fState34Output2TypeDpt1, DFA_fState34Output3TypeDpt1, DFA_fState34Output4TypeDpt1, },
    { DFA_fState35Output1TypeDpt1, DFA_fState35Output2TypeDpt1, DFA_fState35Output3TypeDpt1, DFA_fState35Output4TypeDpt1, },
    { DFA_fState36Output1TypeDpt1, DFA_fState36Output2TypeDpt1, DFA_fState36Output3TypeDpt1, DFA_fState36Output4TypeDpt1, },
    { DFA_fState37Output1TypeDpt1, DFA_fState37Output2TypeDpt1, DFA_fState37Output3TypeDpt1, DFA_fState37Output4TypeDpt1, },
    { DFA_fState38Output1TypeDpt1, DFA_fState38Output2TypeDpt1, DFA_fState38Output3TypeDpt1, DFA_fState38Output4TypeDpt1, },
    { DFA_fState39Output1TypeDpt1, DFA_fState39Output2TypeDpt1, DFA_fState39Output3TypeDpt1, DFA_fState39Output4TypeDpt1, },
    { DFA_fState40Output1TypeDpt1, DFA_fState40Output2TypeDpt1, DFA_fState40Output3TypeDpt1, DFA_fState40Output4TypeDpt1, },
    { DFA_fState41Output1TypeDpt1, DFA_fState41Output2TypeDpt1, DFA_fState41Output3TypeDpt1, DFA_fState41Output4TypeDpt1, },
    { DFA_fState42Output1TypeDpt1, DFA_fState42Output2TypeDpt1, DFA_fState42Output3TypeDpt1, DFA_fState42Output4TypeDpt1, },
    { DFA_fState43Output1TypeDpt1, DFA_fState43Output2TypeDpt1, DFA_fState43Output3TypeDpt1, DFA_fState43Output4TypeDpt1, },
    { DFA_fState44Output1TypeDpt1, DFA_fState44Output2TypeDpt1, DFA_fState44Output3TypeDpt1, DFA_fState44Output4TypeDpt1, },
    { DFA_fState45Output1TypeDpt1, DFA_fState45Output2TypeDpt1, DFA_fState45Output3TypeDpt1, DFA_fState45Output4TypeDpt1, },
    { DFA_fState46Output1TypeDpt1, DFA_fState46Output2TypeDpt1, DFA_fState46Output3TypeDpt1, DFA_fState46Output4TypeDpt1, },
    { DFA_fState47Output1TypeDpt1, DFA_fState47Output2TypeDpt1, DFA_fState47Output3TypeDpt1, DFA_fState47Output4TypeDpt1, },
    { DFA_fState48Output1TypeDpt1, DFA_fState48Output2TypeDpt1, DFA_fState48Output3TypeDpt1, DFA_fState48Output4TypeDpt1, },
    { DFA_fState49Output1TypeDpt1, DFA_fState49Output2TypeDpt1, DFA_fState49Output3TypeDpt1, DFA_fState49Output4TypeDpt1, },
    { DFA_fState50Output1TypeDpt1, DFA_fState50Output2TypeDpt1, DFA_fState50Output3TypeDpt1, DFA_fState50Output4TypeDpt1, },
    { DFA_fState51Output1TypeDpt1, DFA_fState51Output2TypeDpt1, DFA_fState51Output3TypeDpt1, DFA_fState51Output4TypeDpt1, },
    { DFA_fState52Output1TypeDpt1, DFA_fState52Output2TypeDpt1, DFA_fState52Output3TypeDpt1, DFA_fState52Output4TypeDpt1, },
    { DFA_fState53Output1TypeDpt1, DFA_fState53Output2TypeDpt1, DFA_fState53Output3TypeDpt1, DFA_fState53Output4TypeDpt1, },
    { DFA_fState54Output1TypeDpt1, DFA_fState54Output2TypeDpt1, DFA_fState54Output3TypeDpt1, DFA_fState54Output4TypeDpt1, },
    { DFA_fState55Output1TypeDpt1, DFA_fState55Output2TypeDpt1, DFA_fState55Output3TypeDpt1, DFA_fState55Output4TypeDpt1, },
    { DFA_fState56Output1TypeDpt1, DFA_fState56Output2TypeDpt1, DFA_fState56Output3TypeDpt1, DFA_fState56Output4TypeDpt1, },
    { DFA_fState57Output1TypeDpt1, DFA_fState57Output2TypeDpt1, DFA_fState57Output3TypeDpt1, DFA_fState57Output4TypeDpt1, },
    { DFA_fState58Output1TypeDpt1, DFA_fState58Output2TypeDpt1, DFA_fState58Output3TypeDpt1, DFA_fState58Output4TypeDpt1, },
    { DFA_fState59Output1TypeDpt1, DFA_fState59Output2TypeDpt1, DFA_fState59Output3TypeDpt1, DFA_fState59Output4TypeDpt1, },
    { DFA_fState60Output1TypeDpt1, DFA_fState60Output2TypeDpt1, DFA_fState60Output3TypeDpt1, DFA_fState60Output4TypeDpt1, },
    { DFA_fState61Output1TypeDpt1, DFA_fState61Output2TypeDpt1, DFA_fState61Output3TypeDpt1, DFA_fState61Output4TypeDpt1, },
    { DFA_fState62Output1TypeDpt1, DFA_fState62Output2TypeDpt1, DFA_fState62Output3TypeDpt1, DFA_fState62Output4TypeDpt1, },
    { DFA_fState63Output1TypeDpt1, DFA_fState63Output2TypeDpt1, DFA_fState63Output3TypeDpt1, DFA_fState63Output4TypeDpt1, },
    { DFA_fState64Output1TypeDpt1, DFA_fState64Output2TypeDpt1, DFA_fState64Output3TypeDpt1, DFA_fState64Output4TypeDpt1, },
    */
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
    {DFA_fTransState17Input1, DFA_fTransState17Input2, DFA_fTransState17Input3, DFA_fTransState17Input4, DFA_fTransState17Input5, DFA_fTransState17Input6, DFA_fTransState17Input7, DFA_fTransState17Input8},
    {DFA_fTransState18Input1, DFA_fTransState18Input2, DFA_fTransState18Input3, DFA_fTransState18Input4, DFA_fTransState18Input5, DFA_fTransState18Input6, DFA_fTransState18Input7, DFA_fTransState18Input8},
    {DFA_fTransState19Input1, DFA_fTransState19Input2, DFA_fTransState19Input3, DFA_fTransState19Input4, DFA_fTransState19Input5, DFA_fTransState19Input6, DFA_fTransState19Input7, DFA_fTransState19Input8},
    {DFA_fTransState20Input1, DFA_fTransState20Input2, DFA_fTransState20Input3, DFA_fTransState20Input4, DFA_fTransState20Input5, DFA_fTransState20Input6, DFA_fTransState20Input7, DFA_fTransState20Input8},
    {DFA_fTransState21Input1, DFA_fTransState21Input2, DFA_fTransState21Input3, DFA_fTransState21Input4, DFA_fTransState21Input5, DFA_fTransState21Input6, DFA_fTransState21Input7, DFA_fTransState21Input8},
    {DFA_fTransState22Input1, DFA_fTransState22Input2, DFA_fTransState22Input3, DFA_fTransState22Input4, DFA_fTransState22Input5, DFA_fTransState22Input6, DFA_fTransState22Input7, DFA_fTransState22Input8},
    {DFA_fTransState23Input1, DFA_fTransState23Input2, DFA_fTransState23Input3, DFA_fTransState23Input4, DFA_fTransState23Input5, DFA_fTransState23Input6, DFA_fTransState23Input7, DFA_fTransState23Input8},
    {DFA_fTransState24Input1, DFA_fTransState24Input2, DFA_fTransState24Input3, DFA_fTransState24Input4, DFA_fTransState24Input5, DFA_fTransState24Input6, DFA_fTransState24Input7, DFA_fTransState24Input8},
    {DFA_fTransState25Input1, DFA_fTransState25Input2, DFA_fTransState25Input3, DFA_fTransState25Input4, DFA_fTransState25Input5, DFA_fTransState25Input6, DFA_fTransState25Input7, DFA_fTransState25Input8},
    {DFA_fTransState26Input1, DFA_fTransState26Input2, DFA_fTransState26Input3, DFA_fTransState26Input4, DFA_fTransState26Input5, DFA_fTransState26Input6, DFA_fTransState26Input7, DFA_fTransState26Input8},
    {DFA_fTransState27Input1, DFA_fTransState27Input2, DFA_fTransState27Input3, DFA_fTransState27Input4, DFA_fTransState27Input5, DFA_fTransState27Input6, DFA_fTransState27Input7, DFA_fTransState27Input8},
    {DFA_fTransState28Input1, DFA_fTransState28Input2, DFA_fTransState28Input3, DFA_fTransState28Input4, DFA_fTransState28Input5, DFA_fTransState28Input6, DFA_fTransState28Input7, DFA_fTransState28Input8},
    {DFA_fTransState29Input1, DFA_fTransState29Input2, DFA_fTransState29Input3, DFA_fTransState29Input4, DFA_fTransState29Input5, DFA_fTransState29Input6, DFA_fTransState29Input7, DFA_fTransState29Input8},
    {DFA_fTransState30Input1, DFA_fTransState30Input2, DFA_fTransState30Input3, DFA_fTransState30Input4, DFA_fTransState30Input5, DFA_fTransState30Input6, DFA_fTransState30Input7, DFA_fTransState30Input8},
    {DFA_fTransState31Input1, DFA_fTransState31Input2, DFA_fTransState31Input3, DFA_fTransState31Input4, DFA_fTransState31Input5, DFA_fTransState31Input6, DFA_fTransState31Input7, DFA_fTransState31Input8},
    {DFA_fTransState32Input1, DFA_fTransState32Input2, DFA_fTransState32Input3, DFA_fTransState32Input4, DFA_fTransState32Input5, DFA_fTransState32Input6, DFA_fTransState32Input7, DFA_fTransState32Input8},
    /*
    {DFA_fTransState33Input1, DFA_fTransState33Input2, DFA_fTransState33Input3, DFA_fTransState33Input4, DFA_fTransState33Input5, DFA_fTransState33Input6, DFA_fTransState33Input7, DFA_fTransState33Input8},
    {DFA_fTransState34Input1, DFA_fTransState34Input2, DFA_fTransState34Input3, DFA_fTransState34Input4, DFA_fTransState34Input5, DFA_fTransState34Input6, DFA_fTransState34Input7, DFA_fTransState34Input8},
    {DFA_fTransState35Input1, DFA_fTransState35Input2, DFA_fTransState35Input3, DFA_fTransState35Input4, DFA_fTransState35Input5, DFA_fTransState35Input6, DFA_fTransState35Input7, DFA_fTransState35Input8},
    {DFA_fTransState36Input1, DFA_fTransState36Input2, DFA_fTransState36Input3, DFA_fTransState36Input4, DFA_fTransState36Input5, DFA_fTransState36Input6, DFA_fTransState36Input7, DFA_fTransState36Input8},
    {DFA_fTransState37Input1, DFA_fTransState37Input2, DFA_fTransState37Input3, DFA_fTransState37Input4, DFA_fTransState37Input5, DFA_fTransState37Input6, DFA_fTransState37Input7, DFA_fTransState37Input8},
    {DFA_fTransState38Input1, DFA_fTransState38Input2, DFA_fTransState38Input3, DFA_fTransState38Input4, DFA_fTransState38Input5, DFA_fTransState38Input6, DFA_fTransState38Input7, DFA_fTransState38Input8},
    {DFA_fTransState39Input1, DFA_fTransState39Input2, DFA_fTransState39Input3, DFA_fTransState39Input4, DFA_fTransState39Input5, DFA_fTransState39Input6, DFA_fTransState39Input7, DFA_fTransState39Input8},
    {DFA_fTransState40Input1, DFA_fTransState40Input2, DFA_fTransState40Input3, DFA_fTransState40Input4, DFA_fTransState40Input5, DFA_fTransState40Input6, DFA_fTransState40Input7, DFA_fTransState40Input8},
    {DFA_fTransState41Input1, DFA_fTransState41Input2, DFA_fTransState41Input3, DFA_fTransState41Input4, DFA_fTransState41Input5, DFA_fTransState41Input6, DFA_fTransState41Input7, DFA_fTransState41Input8},
    {DFA_fTransState42Input1, DFA_fTransState42Input2, DFA_fTransState42Input3, DFA_fTransState42Input4, DFA_fTransState42Input5, DFA_fTransState42Input6, DFA_fTransState42Input7, DFA_fTransState42Input8},
    {DFA_fTransState43Input1, DFA_fTransState43Input2, DFA_fTransState43Input3, DFA_fTransState43Input4, DFA_fTransState43Input5, DFA_fTransState43Input6, DFA_fTransState43Input7, DFA_fTransState43Input8},
    {DFA_fTransState44Input1, DFA_fTransState44Input2, DFA_fTransState44Input3, DFA_fTransState44Input4, DFA_fTransState44Input5, DFA_fTransState44Input6, DFA_fTransState44Input7, DFA_fTransState44Input8},
    {DFA_fTransState45Input1, DFA_fTransState45Input2, DFA_fTransState45Input3, DFA_fTransState45Input4, DFA_fTransState45Input5, DFA_fTransState45Input6, DFA_fTransState45Input7, DFA_fTransState45Input8},
    {DFA_fTransState46Input1, DFA_fTransState46Input2, DFA_fTransState46Input3, DFA_fTransState46Input4, DFA_fTransState46Input5, DFA_fTransState46Input6, DFA_fTransState46Input7, DFA_fTransState46Input8},
    {DFA_fTransState47Input1, DFA_fTransState47Input2, DFA_fTransState47Input3, DFA_fTransState47Input4, DFA_fTransState47Input5, DFA_fTransState47Input6, DFA_fTransState47Input7, DFA_fTransState47Input8},
    {DFA_fTransState48Input1, DFA_fTransState48Input2, DFA_fTransState48Input3, DFA_fTransState48Input4, DFA_fTransState48Input5, DFA_fTransState48Input6, DFA_fTransState48Input7, DFA_fTransState48Input8},
    {DFA_fTransState49Input1, DFA_fTransState49Input2, DFA_fTransState49Input3, DFA_fTransState49Input4, DFA_fTransState49Input5, DFA_fTransState49Input6, DFA_fTransState49Input7, DFA_fTransState49Input8},
    {DFA_fTransState50Input1, DFA_fTransState50Input2, DFA_fTransState50Input3, DFA_fTransState50Input4, DFA_fTransState50Input5, DFA_fTransState50Input6, DFA_fTransState50Input7, DFA_fTransState50Input8},
    {DFA_fTransState51Input1, DFA_fTransState51Input2, DFA_fTransState51Input3, DFA_fTransState51Input4, DFA_fTransState51Input5, DFA_fTransState51Input6, DFA_fTransState51Input7, DFA_fTransState51Input8},
    {DFA_fTransState52Input1, DFA_fTransState52Input2, DFA_fTransState52Input3, DFA_fTransState52Input4, DFA_fTransState52Input5, DFA_fTransState52Input6, DFA_fTransState52Input7, DFA_fTransState52Input8},
    {DFA_fTransState53Input1, DFA_fTransState53Input2, DFA_fTransState53Input3, DFA_fTransState53Input4, DFA_fTransState53Input5, DFA_fTransState53Input6, DFA_fTransState53Input7, DFA_fTransState53Input8},
    {DFA_fTransState54Input1, DFA_fTransState54Input2, DFA_fTransState54Input3, DFA_fTransState54Input4, DFA_fTransState54Input5, DFA_fTransState54Input6, DFA_fTransState54Input7, DFA_fTransState54Input8},
    {DFA_fTransState55Input1, DFA_fTransState55Input2, DFA_fTransState55Input3, DFA_fTransState55Input4, DFA_fTransState55Input5, DFA_fTransState55Input6, DFA_fTransState55Input7, DFA_fTransState55Input8},
    {DFA_fTransState56Input1, DFA_fTransState56Input2, DFA_fTransState56Input3, DFA_fTransState56Input4, DFA_fTransState56Input5, DFA_fTransState56Input6, DFA_fTransState56Input7, DFA_fTransState56Input8},
    {DFA_fTransState57Input1, DFA_fTransState57Input2, DFA_fTransState57Input3, DFA_fTransState57Input4, DFA_fTransState57Input5, DFA_fTransState57Input6, DFA_fTransState57Input7, DFA_fTransState57Input8},
    {DFA_fTransState58Input1, DFA_fTransState58Input2, DFA_fTransState58Input3, DFA_fTransState58Input4, DFA_fTransState58Input5, DFA_fTransState58Input6, DFA_fTransState58Input7, DFA_fTransState58Input8},
    {DFA_fTransState59Input1, DFA_fTransState59Input2, DFA_fTransState59Input3, DFA_fTransState59Input4, DFA_fTransState59Input5, DFA_fTransState59Input6, DFA_fTransState59Input7, DFA_fTransState59Input8},
    {DFA_fTransState60Input1, DFA_fTransState60Input2, DFA_fTransState60Input3, DFA_fTransState60Input4, DFA_fTransState60Input5, DFA_fTransState60Input6, DFA_fTransState60Input7, DFA_fTransState60Input8},
    {DFA_fTransState61Input1, DFA_fTransState61Input2, DFA_fTransState61Input3, DFA_fTransState61Input4, DFA_fTransState61Input5, DFA_fTransState61Input6, DFA_fTransState61Input7, DFA_fTransState61Input8},
    {DFA_fTransState62Input1, DFA_fTransState62Input2, DFA_fTransState62Input3, DFA_fTransState62Input4, DFA_fTransState62Input5, DFA_fTransState62Input6, DFA_fTransState62Input7, DFA_fTransState62Input8},
    {DFA_fTransState63Input1, DFA_fTransState63Input2, DFA_fTransState63Input3, DFA_fTransState63Input4, DFA_fTransState63Input5, DFA_fTransState63Input6, DFA_fTransState63Input7, DFA_fTransState63Input8},
    {DFA_fTransState64Input1, DFA_fTransState64Input2, DFA_fTransState64Input3, DFA_fTransState64Input4, DFA_fTransState64Input5, DFA_fTransState64Input6, DFA_fTransState64Input7, DFA_fTransState64Input8},
    */
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
    {DFA_fState17TimeoutTime, DFA_fTransState17Timeout},
    {DFA_fState18TimeoutTime, DFA_fTransState18Timeout},
    {DFA_fState19TimeoutTime, DFA_fTransState19Timeout},
    {DFA_fState20TimeoutTime, DFA_fTransState20Timeout},
    {DFA_fState21TimeoutTime, DFA_fTransState21Timeout},
    {DFA_fState22TimeoutTime, DFA_fTransState22Timeout},
    {DFA_fState23TimeoutTime, DFA_fTransState23Timeout},
    {DFA_fState24TimeoutTime, DFA_fTransState24Timeout},
    {DFA_fState25TimeoutTime, DFA_fTransState25Timeout},
    {DFA_fState26TimeoutTime, DFA_fTransState26Timeout},
    {DFA_fState27TimeoutTime, DFA_fTransState27Timeout},
    {DFA_fState28TimeoutTime, DFA_fTransState28Timeout},
    {DFA_fState29TimeoutTime, DFA_fTransState29Timeout},
    {DFA_fState30TimeoutTime, DFA_fTransState30Timeout},
    {DFA_fState31TimeoutTime, DFA_fTransState31Timeout},
    {DFA_fState32TimeoutTime, DFA_fTransState32Timeout},
    /*
    {DFA_fState33TimeoutTime, DFA_fTransState33Timeout},
    {DFA_fState34TimeoutTime, DFA_fTransState34Timeout},
    {DFA_fState35TimeoutTime, DFA_fTransState35Timeout},
    {DFA_fState36TimeoutTime, DFA_fTransState36Timeout},
    {DFA_fState37TimeoutTime, DFA_fTransState37Timeout},
    {DFA_fState38TimeoutTime, DFA_fTransState38Timeout},
    {DFA_fState39TimeoutTime, DFA_fTransState39Timeout},
    {DFA_fState40TimeoutTime, DFA_fTransState40Timeout},
    {DFA_fState41TimeoutTime, DFA_fTransState41Timeout},
    {DFA_fState42TimeoutTime, DFA_fTransState42Timeout},
    {DFA_fState43TimeoutTime, DFA_fTransState43Timeout},
    {DFA_fState44TimeoutTime, DFA_fTransState44Timeout},
    {DFA_fState45TimeoutTime, DFA_fTransState45Timeout},
    {DFA_fState46TimeoutTime, DFA_fTransState46Timeout},
    {DFA_fState47TimeoutTime, DFA_fTransState47Timeout},
    {DFA_fState48TimeoutTime, DFA_fTransState48Timeout},
    {DFA_fState49TimeoutTime, DFA_fTransState49Timeout},
    {DFA_fState50TimeoutTime, DFA_fTransState50Timeout},
    {DFA_fState51TimeoutTime, DFA_fTransState51Timeout},
    {DFA_fState52TimeoutTime, DFA_fTransState52Timeout},
    {DFA_fState53TimeoutTime, DFA_fTransState53Timeout},
    {DFA_fState54TimeoutTime, DFA_fTransState54Timeout},
    {DFA_fState55TimeoutTime, DFA_fTransState55Timeout},
    {DFA_fState56TimeoutTime, DFA_fTransState56Timeout},
    {DFA_fState57TimeoutTime, DFA_fTransState57Timeout},
    {DFA_fState58TimeoutTime, DFA_fTransState58Timeout},
    {DFA_fState59TimeoutTime, DFA_fTransState59Timeout},
    {DFA_fState60TimeoutTime, DFA_fTransState60Timeout},
    {DFA_fState61TimeoutTime, DFA_fTransState61Timeout},
    {DFA_fState62TimeoutTime, DFA_fTransState62Timeout},
    {DFA_fState63TimeoutTime, DFA_fTransState63Timeout},
    {DFA_fState64TimeoutTime, DFA_fTransState64Timeout},
    */
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

uint16_t DfaChannel::getInputKo(const uint8_t input)
{
    // TODO check shift and mark for all
    const uint8_t inputConf = ((knx.paramByte(DFA_ParamCalcIndex(_inputConfPRI[input])) & DFA_fInputSymbol1KoMask) >> DFA_fInputSymbol1KoShift);
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
        case 2: // Bestehendes KO
            return knx.paramWord(DFA_ParamCalcIndex(_inputConfNumberPRI[input]));
    }
    // default, including case 0 (disabled)
    return 0;
}

void DfaChannel::initInputConfig()
{
    const bool combined[DFA_DEF_INPUTS_COUNT / 2] = {ParamDFA_fInputCombinedAB, ParamDFA_fInputCombinedCD, ParamDFA_fInputCombinedEF, ParamDFA_fInputCombinedGH};
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
                    _inputs[i].trigger = ((knx.paramByte(DFA_ParamCalcIndex(_inputTriggerPRI[i])) & DFA_fInputSymbol1ValueMask) >> DFA_fInputSymbol1ValueShift);
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
        else
        {
            // TODO cyclic sending
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

    const uint16_t koNumber = ko.asap();

    // TODO define behaviour within startup delay!
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
        else if (ko.valueSize() == 1) // TODO check if adequate, or add support for other input types
        {
            const bool value = ko.value(DPT_Switch);

            // check (new or existing) inputs based on ko-numbers
            for (size_t i = 0; i < DFA_DEF_INPUTS_COUNT; i++)
            {
                if (koNumber == _inputs[i].koNumber)
                {
                    const bool triggered = _inputs[i].trigger & (1 << value);
                    logDebugP("processInputKo input=%d (ko=%d; triggered=%d)", i+1, koNumber, triggered);
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
        resetTimeout();

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
    const uint16_t goNumber = DFA_KoCalcNumber(_outputKoPRI[outputIndex]);
    // logDebugP(" => sendOutput: index=%i, konr=%i, value=%i, dpt=%i.%03i, send=%i", outputIndex, goNumber, (long)value, type.mainGroup, type.subGroup, outputStateSend);
    GroupObject* ko = &knx.getGroupObject(goNumber);
    if (outputStateSend == OUTPUT_SEND_ALWAYS)
    {
        ko->value(value, type);
    }
    else if (ko->valueNoSendCompare(value, type))
    {
        ko->objectWritten();
    }
}

void DfaChannel::sendValues()
{
    for (uint8_t i = 0; i < DFA_DEF_OUTPUTS_COUNT; i++)
    {
        const uint8_t outputType = knx.paramByte(DFA_ParamCalcIndex(_outputDptPRI[i]));
        logDebugP("Output<%d>: check sending value (type=%i)", i+1, outputType);
        // output is active?
        if (outputType != 0)
        {
            const uint8_t outputStateSend = knx.paramByte(DFA_ParamCalcIndex(_outputSendPRI[_state][i])) >> 6;
            logDebugP(" -> outputStateSend=%d", outputStateSend);
            // output has value for state?
            if (outputStateSend)
            {
                const uint32_t pIdxValue = DFA_ParamCalcIndex(_outputValuePRI[_state][i]);
                logDebugP(" -> paramIndex=%i", pIdxValue);

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

void DfaChannel::save()
{
    const uint8_t conf = _channelActive << 7 | _running << 6 | ParamDFA_fStateRestore;
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
