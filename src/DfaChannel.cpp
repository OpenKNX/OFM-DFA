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
    DFA_aSymbolAInput,
    DFA_aSymbolBInput,
    DFA_aSymbolCInput,
    DFA_aSymbolDInput,
    DFA_aSymbolEInput,
    DFA_aSymbolFInput,
    DFA_aSymbolGInput,
    DFA_aSymbolHInput,
};
// Value of DFA_aInputSymbol[1-8]Ko by 0-based index
#define DFA_aSymbol__N__Ko(IDX) DFA_aSymbolAInput + IDX * (DFA_aSymbolBInput - DFA_aSymbolAInput)
//     const uint8_t inputConf = ((knx.paramByte(DFA_ParamCalcIndex(_inputConfPRI[input])) & DFA_aSymbolAInputMask) >> DFA_aSymbolAInputShift);
#define DFA_Channel_Input_Config(IDX) ((knx.paramByte(DFA_aSymbol__N__Ko(input)) & DFA_aSymbolAInputMask) >> DFA_aSymbolAInputShift)


#if DFA_aSymbolALogicNumber != DFA_aSymbolAKoNumber
    #error "DFA_aSymbolALogicNumber != DFA_aSymbolAKoNumber"
#endif
const uint16_t DfaChannel::_inputConfNumberPRI[DFA_DEF_INPUTS_COUNT] = {
    DFA_aSymbolAKoNumber,
    DFA_aSymbolBKoNumber,
    DFA_aSymbolCKoNumber,
    DFA_aSymbolDKoNumber,
    DFA_aSymbolEKoNumber,
    DFA_aSymbolFKoNumber,
    DFA_aSymbolGKoNumber,
    DFA_aSymbolHKoNumber,
};
const uint16_t DfaChannel::_inputTriggerPRI[DFA_DEF_INPUTS_COUNT] = {
    DFA_aSymbolATrigger,
    DFA_aSymbolBTrigger,
    DFA_aSymbolCTrigger,
    DFA_aSymbolDTrigger,
    DFA_aSymbolETrigger,
    DFA_aSymbolFTrigger,
    DFA_aSymbolGTrigger,
    DFA_aSymbolHTrigger,
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
    /*
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
    */
};
const uint16_t DfaChannel::_outputValuePRI[DFA_DEF_STATES_COUNT][DFA_DEF_OUTPUTS_COUNT] = {
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
    /*
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
    */
};

// TODO calculate index; expected distance should be protected by compile error
// Define (relative) parameter address-index for next state by current state and input

// Value of DFA_KoKOaInput[1-8] by 0-based index
#define DFA_aTransfer_State__N__Input__M__(N, M) DFA_ad01A + N * (DFA_ad02A - DFA_ad01A) + M * (DFA_ad01B - DFA_ad01A)
// Value of DFA_KoCalcNumber(DFA_KoKOaInput[1-8]) by 0-based index
#define DFA_Channel_TransferByStateInput(STATE_IDX, IN_IDX) DFA_KoCalcNumber(DFA_aTransfer_State__N__Input__M__(STATE_IDX, IN_IDX))


const uint16_t DfaChannel::_transPRI[DFA_DEF_STATES_COUNT][DFA_DEF_INPUTS_COUNT] = {
    {DFA_ad01A, DFA_ad01B, DFA_ad01C, DFA_ad01D, DFA_ad01E, DFA_ad01F, DFA_ad01G, DFA_ad01H},
    {DFA_ad02A, DFA_ad02B, DFA_ad02C, DFA_ad02D, DFA_ad02E, DFA_ad02F, DFA_ad02G, DFA_ad02H},
    {DFA_ad03A, DFA_ad03B, DFA_ad03C, DFA_ad03D, DFA_ad03E, DFA_ad03F, DFA_ad03G, DFA_ad03H},
    {DFA_ad04A, DFA_ad04B, DFA_ad04C, DFA_ad04D, DFA_ad04E, DFA_ad04F, DFA_ad04G, DFA_ad04H},
    {DFA_ad05A, DFA_ad05B, DFA_ad05C, DFA_ad05D, DFA_ad05E, DFA_ad05F, DFA_ad05G, DFA_ad05H},
    {DFA_ad06A, DFA_ad06B, DFA_ad06C, DFA_ad06D, DFA_ad06E, DFA_ad06F, DFA_ad06G, DFA_ad06H},
    {DFA_ad07A, DFA_ad07B, DFA_ad07C, DFA_ad07D, DFA_ad07E, DFA_ad07F, DFA_ad07G, DFA_ad07H},
    {DFA_ad08A, DFA_ad08B, DFA_ad08C, DFA_ad08D, DFA_ad08E, DFA_ad08F, DFA_ad08G, DFA_ad08H},
    {DFA_ad09A, DFA_ad09B, DFA_ad09C, DFA_ad09D, DFA_ad09E, DFA_ad09F, DFA_ad09G, DFA_ad09H},
    {DFA_ad10A, DFA_ad10B, DFA_ad10C, DFA_ad10D, DFA_ad10E, DFA_ad10F, DFA_ad10G, DFA_ad10H},
    {DFA_ad11A, DFA_ad11B, DFA_ad11C, DFA_ad11D, DFA_ad11E, DFA_ad11F, DFA_ad11G, DFA_ad11H},
    {DFA_ad12A, DFA_ad12B, DFA_ad12C, DFA_ad12D, DFA_ad12E, DFA_ad12F, DFA_ad12G, DFA_ad12H},
    {DFA_ad13A, DFA_ad13B, DFA_ad13C, DFA_ad13D, DFA_ad13E, DFA_ad13F, DFA_ad13G, DFA_ad13H},
    {DFA_ad14A, DFA_ad14B, DFA_ad14C, DFA_ad14D, DFA_ad14E, DFA_ad14F, DFA_ad14G, DFA_ad14H},
    {DFA_ad15A, DFA_ad15B, DFA_ad15C, DFA_ad15D, DFA_ad15E, DFA_ad15F, DFA_ad15G, DFA_ad15H},
    {DFA_ad16A, DFA_ad16B, DFA_ad16C, DFA_ad16D, DFA_ad16E, DFA_ad16F, DFA_ad16G, DFA_ad16H},
    {DFA_ad17A, DFA_ad17B, DFA_ad17C, DFA_ad17D, DFA_ad17E, DFA_ad17F, DFA_ad17G, DFA_ad17H},
    {DFA_ad18A, DFA_ad18B, DFA_ad18C, DFA_ad18D, DFA_ad18E, DFA_ad18F, DFA_ad18G, DFA_ad18H},
    {DFA_ad19A, DFA_ad19B, DFA_ad19C, DFA_ad19D, DFA_ad19E, DFA_ad19F, DFA_ad19G, DFA_ad19H},
    {DFA_ad20A, DFA_ad20B, DFA_ad20C, DFA_ad20D, DFA_ad20E, DFA_ad20F, DFA_ad20G, DFA_ad20H},
    {DFA_ad21A, DFA_ad21B, DFA_ad21C, DFA_ad21D, DFA_ad21E, DFA_ad21F, DFA_ad21G, DFA_ad21H},
    {DFA_ad22A, DFA_ad22B, DFA_ad22C, DFA_ad22D, DFA_ad22E, DFA_ad22F, DFA_ad22G, DFA_ad22H},
    {DFA_ad23A, DFA_ad23B, DFA_ad23C, DFA_ad23D, DFA_ad23E, DFA_ad23F, DFA_ad23G, DFA_ad23H},
    {DFA_ad24A, DFA_ad24B, DFA_ad24C, DFA_ad24D, DFA_ad24E, DFA_ad24F, DFA_ad24G, DFA_ad24H},
    {DFA_ad25A, DFA_ad25B, DFA_ad25C, DFA_ad25D, DFA_ad25E, DFA_ad25F, DFA_ad25G, DFA_ad25H},
    {DFA_ad26A, DFA_ad26B, DFA_ad26C, DFA_ad26D, DFA_ad26E, DFA_ad26F, DFA_ad26G, DFA_ad26H},
    {DFA_ad27A, DFA_ad27B, DFA_ad27C, DFA_ad27D, DFA_ad27E, DFA_ad27F, DFA_ad27G, DFA_ad27H},
    {DFA_ad28A, DFA_ad28B, DFA_ad28C, DFA_ad28D, DFA_ad28E, DFA_ad28F, DFA_ad28G, DFA_ad28H},
    {DFA_ad29A, DFA_ad29B, DFA_ad29C, DFA_ad29D, DFA_ad29E, DFA_ad29F, DFA_ad29G, DFA_ad29H},
    {DFA_ad30A, DFA_ad30B, DFA_ad30C, DFA_ad30D, DFA_ad30E, DFA_ad30F, DFA_ad30G, DFA_ad30H},
    {DFA_ad31A, DFA_ad31B, DFA_ad31C, DFA_ad31D, DFA_ad31E, DFA_ad31F, DFA_ad31G, DFA_ad31H},
    {DFA_ad32A, DFA_ad32B, DFA_ad32C, DFA_ad32D, DFA_ad32E, DFA_ad32F, DFA_ad32G, DFA_ad32H},
    /*
    {DFA_ad33A, DFA_ad33B, DFA_ad33C, DFA_ad33D, DFA_ad33E, DFA_ad33F, DFA_ad33G, DFA_ad33H},
    {DFA_ad34A, DFA_ad34B, DFA_ad34C, DFA_ad34D, DFA_ad34E, DFA_ad34F, DFA_ad34G, DFA_ad34H},
    {DFA_ad35A, DFA_ad35B, DFA_ad35C, DFA_ad35D, DFA_ad35E, DFA_ad35F, DFA_ad35G, DFA_ad35H},
    {DFA_ad36A, DFA_ad36B, DFA_ad36C, DFA_ad36D, DFA_ad36E, DFA_ad36F, DFA_ad36G, DFA_ad36H},
    {DFA_ad37A, DFA_ad37B, DFA_ad37C, DFA_ad37D, DFA_ad37E, DFA_ad37F, DFA_ad37G, DFA_ad37H},
    {DFA_ad38A, DFA_ad38B, DFA_ad38C, DFA_ad38D, DFA_ad38E, DFA_ad38F, DFA_ad38G, DFA_ad38H},
    {DFA_ad39A, DFA_ad39B, DFA_ad39C, DFA_ad39D, DFA_ad39E, DFA_ad39F, DFA_ad39G, DFA_ad39H},
    {DFA_ad40A, DFA_ad40B, DFA_ad40C, DFA_ad40D, DFA_ad40E, DFA_ad40F, DFA_ad40G, DFA_ad40H},
    {DFA_ad41A, DFA_ad41B, DFA_ad41C, DFA_ad41D, DFA_ad41E, DFA_ad41F, DFA_ad41G, DFA_ad41H},
    {DFA_ad42A, DFA_ad42B, DFA_ad42C, DFA_ad42D, DFA_ad42E, DFA_ad42F, DFA_ad42G, DFA_ad42H},
    {DFA_ad43A, DFA_ad43B, DFA_ad43C, DFA_ad43D, DFA_ad43E, DFA_ad43F, DFA_ad43G, DFA_ad43H},
    {DFA_ad44A, DFA_ad44B, DFA_ad44C, DFA_ad44D, DFA_ad44E, DFA_ad44F, DFA_ad44G, DFA_ad44H},
    {DFA_ad45A, DFA_ad45B, DFA_ad45C, DFA_ad45D, DFA_ad45E, DFA_ad45F, DFA_ad45G, DFA_ad45H},
    {DFA_ad46A, DFA_ad46B, DFA_ad46C, DFA_ad46D, DFA_ad46E, DFA_ad46F, DFA_ad46G, DFA_ad46H},
    {DFA_ad47A, DFA_ad47B, DFA_ad47C, DFA_ad47D, DFA_ad47E, DFA_ad47F, DFA_ad47G, DFA_ad47H},
    {DFA_ad48A, DFA_ad48B, DFA_ad48C, DFA_ad48D, DFA_ad48E, DFA_ad48F, DFA_ad48G, DFA_ad48H},
    {DFA_ad49A, DFA_ad49B, DFA_ad49C, DFA_ad49D, DFA_ad49E, DFA_ad49F, DFA_ad49G, DFA_ad49H},
    {DFA_ad50A, DFA_ad50B, DFA_ad50C, DFA_ad50D, DFA_ad50E, DFA_ad50F, DFA_ad50G, DFA_ad50H},
    {DFA_ad51A, DFA_ad51B, DFA_ad51C, DFA_ad51D, DFA_ad51E, DFA_ad51F, DFA_ad51G, DFA_ad51H},
    {DFA_ad52A, DFA_ad52B, DFA_ad52C, DFA_ad52D, DFA_ad52E, DFA_ad52F, DFA_ad52G, DFA_ad52H},
    {DFA_ad53A, DFA_ad53B, DFA_ad53C, DFA_ad53D, DFA_ad53E, DFA_ad53F, DFA_ad53G, DFA_ad53H},
    {DFA_ad54A, DFA_ad54B, DFA_ad54C, DFA_ad54D, DFA_ad54E, DFA_ad54F, DFA_ad54G, DFA_ad54H},
    {DFA_ad55A, DFA_ad55B, DFA_ad55C, DFA_ad55D, DFA_ad55E, DFA_ad55F, DFA_ad55G, DFA_ad55H},
    {DFA_ad56A, DFA_ad56B, DFA_ad56C, DFA_ad56D, DFA_ad56E, DFA_ad56F, DFA_ad56G, DFA_ad56H},
    {DFA_ad57A, DFA_ad57B, DFA_ad57C, DFA_ad57D, DFA_ad57E, DFA_ad57F, DFA_ad57G, DFA_ad57H},
    {DFA_ad58A, DFA_ad58B, DFA_ad58C, DFA_ad58D, DFA_ad58E, DFA_ad58F, DFA_ad58G, DFA_ad58H},
    {DFA_ad59A, DFA_ad59B, DFA_ad59C, DFA_ad59D, DFA_ad59E, DFA_ad59F, DFA_ad59G, DFA_ad59H},
    {DFA_ad60A, DFA_ad60B, DFA_ad60C, DFA_ad60D, DFA_ad60E, DFA_ad60F, DFA_ad60G, DFA_ad60H},
    {DFA_ad61A, DFA_ad61B, DFA_ad61C, DFA_ad61D, DFA_ad61E, DFA_ad61F, DFA_ad61G, DFA_ad61H},
    {DFA_ad62A, DFA_ad62B, DFA_ad62C, DFA_ad62D, DFA_ad62E, DFA_ad62F, DFA_ad62G, DFA_ad62H},
    {DFA_ad63A, DFA_ad63B, DFA_ad63C, DFA_ad63D, DFA_ad63E, DFA_ad63F, DFA_ad63G, DFA_ad63H},
    {DFA_ad64A, DFA_ad64B, DFA_ad64C, DFA_ad64D, DFA_ad64E, DFA_ad64F, DFA_ad64G, DFA_ad64H},
    */
};

// TODO calculate index; expected distance should be protected by compile error
// Define (relative) parameter address-index for timeout duration and timeout state
const DfaStateTimeoutParamRelIdx DfaChannel::_timeoutPRI[DFA_DEF_STATES_COUNT] = {
    {DFA_ad01TTime, DFA_ad01T},
    {DFA_ad02TTime, DFA_ad02T},
    {DFA_ad03TTime, DFA_ad03T},
    {DFA_ad04TTime, DFA_ad04T},
    {DFA_ad05TTime, DFA_ad05T},
    {DFA_ad06TTime, DFA_ad06T},
    {DFA_ad07TTime, DFA_ad07T},
    {DFA_ad08TTime, DFA_ad08T},
    {DFA_ad09TTime, DFA_ad09T},
    {DFA_ad10TTime, DFA_ad10T},
    {DFA_ad11TTime, DFA_ad11T},
    {DFA_ad12TTime, DFA_ad12T},
    {DFA_ad13TTime, DFA_ad13T},
    {DFA_ad14TTime, DFA_ad14T},
    {DFA_ad15TTime, DFA_ad15T},
    {DFA_ad16TTime, DFA_ad16T},
    {DFA_ad17TTime, DFA_ad17T},
    {DFA_ad18TTime, DFA_ad18T},
    {DFA_ad19TTime, DFA_ad19T},
    {DFA_ad20TTime, DFA_ad20T},
    {DFA_ad21TTime, DFA_ad21T},
    {DFA_ad22TTime, DFA_ad22T},
    {DFA_ad23TTime, DFA_ad23T},
    {DFA_ad24TTime, DFA_ad24T},
    {DFA_ad25TTime, DFA_ad25T},
    {DFA_ad26TTime, DFA_ad26T},
    {DFA_ad27TTime, DFA_ad27T},
    {DFA_ad28TTime, DFA_ad28T},
    {DFA_ad29TTime, DFA_ad29T},
    {DFA_ad30TTime, DFA_ad30T},
    {DFA_ad31TTime, DFA_ad31T},
    {DFA_ad32TTime, DFA_ad32T},
    /*
    {DFA_ad33TTime, DFA_ad33T},
    {DFA_ad34TTime, DFA_ad34T},
    {DFA_ad35TTime, DFA_ad35T},
    {DFA_ad36TTime, DFA_ad36T},
    {DFA_ad37TTime, DFA_ad37T},
    {DFA_ad38TTime, DFA_ad38T},
    {DFA_ad39TTime, DFA_ad39T},
    {DFA_ad40TTime, DFA_ad40T},
    {DFA_ad41TTime, DFA_ad41T},
    {DFA_ad42TTime, DFA_ad42T},
    {DFA_ad43TTime, DFA_ad43T},
    {DFA_ad44TTime, DFA_ad44T},
    {DFA_ad45TTime, DFA_ad45T},
    {DFA_ad46TTime, DFA_ad46T},
    {DFA_ad47TTime, DFA_ad47T},
    {DFA_ad48TTime, DFA_ad48T},
    {DFA_ad49TTime, DFA_ad49T},
    {DFA_ad50TTime, DFA_ad50T},
    {DFA_ad51TTime, DFA_ad51T},
    {DFA_ad52TTime, DFA_ad52T},
    {DFA_ad53TTime, DFA_ad53T},
    {DFA_ad54TTime, DFA_ad54T},
    {DFA_ad55TTime, DFA_ad55T},
    {DFA_ad56TTime, DFA_ad56T},
    {DFA_ad57TTime, DFA_ad57T},
    {DFA_ad58TTime, DFA_ad58T},
    {DFA_ad59TTime, DFA_ad59T},
    {DFA_ad60TTime, DFA_ad60T},
    {DFA_ad61TTime, DFA_ad61T},
    {DFA_ad62TTime, DFA_ad62T},
    {DFA_ad63TTime, DFA_ad63T},
    {DFA_ad64TTime, DFA_ad64T},
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
    logDebugP("setup (act=%d dly=%ds run=%d)", _channelActive, ParamDFA_aStartupDelayTimeMS / 1000, ParamDFA_aStartPause != 2);

    if (_channelActive)
    {
        initInputConfig();

        // TODO QS: check first state handling, especially sending
        _firstState = ParamDFA_az0 - 1;
        // _firstStateTimeoutDelay_ms = getStateTimeoutDelay_ms(_firstState);

        // actual starting in processAfterStartupDelay() ...
    }
}

#pragma region "DFA_CHANNEL_INPUT_INIT"

#if (DFA_aSymbolBInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolBInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolBTriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolBInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol B and A"
#endif
#if (DFA_aSymbolCInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolCInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolCTriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolCInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol C and A"
#endif
#if (DFA_aSymbolDInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolDInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolDTriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolDInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol D and A"
#endif
#if (DFA_aSymbolEInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolEInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolETriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolEInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol E and A"
#endif
#if (DFA_aSymbolFInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolFInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolFTriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolFInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol F and A"
#endif
#if (DFA_aSymbolGInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolGInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolGTriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolGInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol G and A"
#endif
#if (DFA_aSymbolHInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolHInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolHTriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolHInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol H and A"
#endif
#define DFA_aSymbol___InputMask DFA_aSymbolAInputMask
#define DFA_aSymbol___InputShift DFA_aSymbolAInputShift
#define DFA_aSymbol___TriggerMask DFA_aSymbolATriggerMask
#define DFA_aSymbol___TriggerShift DFA_aSymbolATriggerShift

uint16_t DfaChannel::getInputKoNumber(const uint8_t input)
{
    const uint8_t inputConf = ((knx.paramByte(DFA_ParamCalcIndex(_inputConfPRI[input])) & DFA_aSymbol___InputMask) >> DFA_aSymbol___InputShift);
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
    const bool combined[DFA_DEF_INPUTS_COUNT / 2] = {ParamDFA_aSymbolPairAB, ParamDFA_aSymbolPairCD, ParamDFA_aSymbolPairEF, ParamDFA_aSymbolPairGH};
    for (uint8_t iPair = 0; iPair < DFA_DEF_INPUTS_COUNT / 2; iPair++)
    {
        // logDebugP("input-pair %d", iPair);
        // logDebugP("input[%d]: ko=%d trigger=%d", i, _inputs[i].koNumber, _inputs[i].trigger);
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
            for (uint8_t i = iFirst; i <= iSecond; i++)
            {
                const uint16_t koNumber = getInputKoNumber(i);
                _inputs[i].koNumber = koNumber;
                _inputs[i].trigger = (koNumber > 0) ? static_cast<DfaInputTrigger>((knx.paramByte(DFA_ParamCalcIndex(_inputTriggerPRI[i])) & DFA_aSymbol___TriggerMask) >> DFA_aSymbol___TriggerShift) : DfaInputTrigger::disabled;
                logDebugP("  separate: %d ko=%i trigger=%i", i, koNumber, _inputs[i].trigger);
            }
        }
    }
    #ifdef OPENKNX_DEBUG
        for (size_t i = 0; i < DFA_DEF_INPUTS_COUNT; i++)
        {
            logDebugP("input[%d]: ko=%d trigger=%d", i, _inputs[i].koNumber, _inputs[i].trigger);
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
        setRunning(ParamDFA_aStartPause != 2, true);
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
                    const bool triggered = static_cast<uint8_t>(_inputs[i].trigger) & (1 << value);
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

    if (send && (ParamDFA_aStartPause != 0))
        KoDFA_KOaRunning.value(_running, DPT_State);
}

uint32_t DfaChannel::getStateTimeoutDelay_ms(const uint8_t state)
{
    // TODO ensure returning 0 for undefined timeout state
    return paramDelay(knx.paramWord(DFA_ParamCalcIndex(_timeoutPRI[state].delay)));
}

uint8_t DfaChannel::getTimeoutState(const uint8_t state)
{
    return knx.paramByte(DFA_ParamCalcIndex(_timeoutPRI[state].state)) - 1;
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
            ParamDFA_aOutput1IntervalTimeMS,
            ParamDFA_aOutput2IntervalTimeMS,
            ParamDFA_aOutput3IntervalTimeMS,
            ParamDFA_aOutput4IntervalTimeMS,
        };
        for (uint8_t i = 0; i < DFA_DEF_OUTPUTS_COUNT; i++)
        {
            const uint8_t outputStateSend = outputGetCurrentStateSendConfig(i);

            // see %AID%_PT-DfaOutputConf"
            const bool updateKo =           (outputStateSend > 0);
            const bool sendOnChangedValue = (outputStateSend >= 2);
            const bool sendOnChangedState = (outputStateSend >= 4);
            const bool sendAlways =         (outputStateSend >= 6);
            const bool repeatedSending =    (outputStateSend >= 2) && (outputStateSend & 0b001);

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
                case DFA_OUTPUT_TYPE_DPT1:
                    // works, as long as using same location as other dpt values
                    outputUpdateKO(i, (knx.paramByte(pIdxValue) != 0), DPT_Switch, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT2:
                    // TODO check using mask!
                    outputUpdateKO(i, knx.paramByte(pIdxValue), DPT_Switch_Control, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT5:
                    outputUpdateKO(i, knx.paramByte(pIdxValue), DPT_DecimalFactor, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT5001:
                    outputUpdateKO(i, knx.paramByte(pIdxValue), DPT_Scaling, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT6:
                    outputUpdateKO(i, knx.paramSignedByte(pIdxValue), DPT_Value_1_Count, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT7:
                    outputUpdateKO(i, knx.paramWord(pIdxValue), DPT_Value_2_Ucount, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT8:
                    outputUpdateKO(i, knx.paramWord(pIdxValue), DPT_Value_2_Count, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT9:
                    outputUpdateKO(i, knx.paramFloat(pIdxValue, Float_Enc_DPT9), DPT_Value_Temp, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT12:
                    outputUpdateKO(i, knx.paramInt(pIdxValue), DPT_Value_4_Ucount, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT13:
                    outputUpdateKO(i, knx.paramInt(pIdxValue), DPT_Value_4_Count, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT14:
                    outputUpdateKO(i, knx.paramFloat(pIdxValue, Float_Enc_IEEE754Double), DPT_Value_Absolute_Temperature, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT16:
                    outputUpdateKO(i, (char *)knx.paramData(pIdxValue), DPT_String_8859_1, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT17:
                    outputUpdateKO(i, knx.paramByte(pIdxValue), DPT_SceneNumber, send, forceSend);
                    break;
                case DFA_OUTPUT_TYPE_DPT232:
                    // get value as defined in ParamDFA_az01o1Dpt232
                    // TODO Ensure same values for DFA_az{$state}o{$output}Dpt232Mask and DFA_az{$state}o{$output}Dpt232Shift
                    outputUpdateKO(i, (knx.paramInt(pIdxValue) & DFA_az01o1Dpt232Mask) >> DFA_az01o1Dpt232Shift, DPT_Colour_RGB, send, forceSend);
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
        const uint8_t nextState = knx.paramByte(nextStateParamIdx) - 1;

        logDebugP("transfer(%u,%u)->%u", _state, input, nextState);
        if (isValidState(nextState))
        {
            setState(nextState);
        }
        else if (nextState == DFA_STATE_TIMEOUT_RESET - 1)
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

#pragma region "DFA_CHANNEL_COMMANDS"

bool DfaChannel::processCommandDfa()
{
    logDebugP("status and remaining delay");
    const uint8_t state = _state + 1;
    const char mode = '<';
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
        openknx.console.writeDiagenoseKo((timeoutHours < 10) ? "%02d%c%d:%02d:%02d.%03d" : "%02d%c%5d:%02d:%02d", state, mode, timeoutHours, timeoutMinutes, timeoutSeconds, timeoutMillis);
    }
    else
    {
        logInfoP("%02d%cNO_TIMEOUT", state, mode);
        openknx.console.writeDiagenoseKo("%02d%c NO_TIMEOUT", state, mode);
    }
    return true;
}

bool DfaChannel::processCommandDfaTimeout()
{
    logInfoP("timeout end now!");
    // TODO define behaviour when disabled
    endTimeout();
    return true;
}

bool DfaChannel::processCommandDfaStateSet(const uint8_t state) {
    setState(state);
    return true;
}

bool DfaChannel::processCommandDfaSymbolInsert(const uint8_t inputSymbolNumber) {
    transfer(inputSymbolNumber);
    return true;
}

#pragma endregion "DFA_CHANNEL_COMMANDS"
