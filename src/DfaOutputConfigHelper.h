// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2026 Cornelius Koepp

#include "DfaOutput.h"

// TODO special handling of indices for >32 DFA required
// Define (relative) parameter address-index for next state by current state and input

// calc local GO-Number for Wertausgang
#define _DFA_KoKOaOutput___(IDX)       (DFA_KoKOaOutput1 + IDX)
static_assert(_DFA_KoKOaOutput___(0) == DFA_KoKOaOutput1);
static_assert(_DFA_KoKOaOutput___(1) == DFA_KoKOaOutput2);
static_assert(_DFA_KoKOaOutput___(2) == DFA_KoKOaOutput3);
static_assert(_DFA_KoKOaOutput___(3) == DFA_KoKOaOutput4);
// Wertausgang i (0-based)
#define _KoDFA_KOaOutput___(IDX)  (knx.getGroupObject(DFA_KoCalcNumber(_DFA_KoKOaOutput___(IDX))))

// calc local Param-Offset for Ausgangs-Datentyp
#define index_ParamDFA_aOutput_I_Dpt(i)                (DFA_aOutput1Dpt + i * (DFA_aOutput2Dpt-DFA_aOutput1Dpt))
    static_assert(DFA_aOutput1Dpt == index_ParamDFA_aOutput_I_Dpt(0), "Wrong index_ParamDFA_aOutput_I_Dpt(0)");
    static_assert(DFA_aOutput2Dpt == index_ParamDFA_aOutput_I_Dpt(1), "Wrong index_ParamDFA_aOutput_I_Dpt(1)");
    static_assert(DFA_aOutput3Dpt == index_ParamDFA_aOutput_I_Dpt(2), "Wrong index_ParamDFA_aOutput_I_Dpt(2)");
    static_assert(DFA_aOutput4Dpt == index_ParamDFA_aOutput_I_Dpt(3), "Wrong index_ParamDFA_aOutput_I_Dpt(3)");
// Datentyp Ausgabe i (0-based)
#define ParamDFA_aOutput_I_Dpt(i)                      (knx.paramByte(DFA_ParamCalcIndex(index_ParamDFA_aOutput_I_Dpt(i))))

const uint16_t DfaOutput::_outputIntervalPRI[DFA_DEF_OUTPUTS_COUNT] = {
    DFA_aOutput1IntervalTime,
    DFA_aOutput2IntervalTime,
    DFA_aOutput3IntervalTime,
    DFA_aOutput4IntervalTime,
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
