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
#define _DFA_aOutput___Dpt(IDX)       (DFA_aOutput1Dpt + IDX * (DFA_aOutput2Dpt - DFA_aOutput1Dpt))
static_assert(_DFA_aOutput___Dpt(0) == DFA_aOutput1Dpt);
static_assert(_DFA_aOutput___Dpt(1) == DFA_aOutput2Dpt);
static_assert(_DFA_aOutput___Dpt(2) == DFA_aOutput3Dpt);
static_assert(_DFA_aOutput___Dpt(3) == DFA_aOutput4Dpt);
// Datentyp Ausgabe i (0-based)
#define _ParamDFA_aOutput___Dpt(IDX)  (knx.paramByte(DFA_ParamCalcIndex(_DFA_aOutput___Dpt(IDX))))

# define _DFA_aOutput___IntervalTime(IDX)      (DFA_aOutput1IntervalTime + IDX * (DFA_aOutput2IntervalTime - DFA_aOutput1IntervalTime))
static_assert(_DFA_aOutput___IntervalTime(0) == DFA_aOutput1IntervalTime);
static_assert(_DFA_aOutput___IntervalTime(1) == DFA_aOutput2IntervalTime);
static_assert(_DFA_aOutput___IntervalTime(2) == DFA_aOutput3IntervalTime);
static_assert(_DFA_aOutput___IntervalTime(3) == DFA_aOutput4IntervalTime);
#define _ParamDFA_aOutput___IntervalTimeMS(IDX)  (paramDelay(knx.paramWord(DFA_ParamCalcIndex(_DFA_aOutput___IntervalTime(IDX)))))

#define _DFA_az___o___Send(IDX_STATE, IDX_OUTPUT)  (DFA_az01o1Send + IDX_STATE * (DFA_az02o1Send - DFA_az01o1Send) + IDX_OUTPUT * (DFA_az01o2Send - DFA_az01o1Send))
static_assert(_DFA_az___o___Send( 0, 0) == DFA_az01o1Send); static_assert(_DFA_az___o___Send( 0, 1) == DFA_az01o2Send); static_assert(_DFA_az___o___Send( 0, 2) == DFA_az01o3Send); static_assert(_DFA_az___o___Send( 0, 3) == DFA_az01o4Send);
static_assert(_DFA_az___o___Send( 1, 0) == DFA_az02o1Send); static_assert(_DFA_az___o___Send( 1, 1) == DFA_az02o2Send); static_assert(_DFA_az___o___Send( 1, 2) == DFA_az02o3Send); static_assert(_DFA_az___o___Send( 1, 3) == DFA_az02o4Send);
static_assert(_DFA_az___o___Send( 2, 0) == DFA_az03o1Send); static_assert(_DFA_az___o___Send( 2, 1) == DFA_az03o2Send); static_assert(_DFA_az___o___Send( 2, 2) == DFA_az03o3Send); static_assert(_DFA_az___o___Send( 2, 3) == DFA_az03o4Send);
static_assert(_DFA_az___o___Send( 3, 0) == DFA_az04o1Send); static_assert(_DFA_az___o___Send( 3, 1) == DFA_az04o2Send); static_assert(_DFA_az___o___Send( 3, 2) == DFA_az04o3Send); static_assert(_DFA_az___o___Send( 3, 3) == DFA_az04o4Send);
static_assert(_DFA_az___o___Send( 4, 0) == DFA_az05o1Send); static_assert(_DFA_az___o___Send( 4, 1) == DFA_az05o2Send); static_assert(_DFA_az___o___Send( 4, 2) == DFA_az05o3Send); static_assert(_DFA_az___o___Send( 4, 3) == DFA_az05o4Send);
static_assert(_DFA_az___o___Send( 5, 0) == DFA_az06o1Send); static_assert(_DFA_az___o___Send( 5, 1) == DFA_az06o2Send); static_assert(_DFA_az___o___Send( 5, 2) == DFA_az06o3Send); static_assert(_DFA_az___o___Send( 5, 3) == DFA_az06o4Send);
static_assert(_DFA_az___o___Send( 6, 0) == DFA_az07o1Send); static_assert(_DFA_az___o___Send( 6, 1) == DFA_az07o2Send); static_assert(_DFA_az___o___Send( 6, 2) == DFA_az07o3Send); static_assert(_DFA_az___o___Send( 6, 3) == DFA_az07o4Send);
static_assert(_DFA_az___o___Send( 7, 0) == DFA_az08o1Send); static_assert(_DFA_az___o___Send( 7, 1) == DFA_az08o2Send); static_assert(_DFA_az___o___Send( 7, 2) == DFA_az08o3Send); static_assert(_DFA_az___o___Send( 7, 3) == DFA_az08o4Send);
static_assert(_DFA_az___o___Send( 8, 0) == DFA_az09o1Send); static_assert(_DFA_az___o___Send( 8, 1) == DFA_az09o2Send); static_assert(_DFA_az___o___Send( 8, 2) == DFA_az09o3Send); static_assert(_DFA_az___o___Send( 8, 3) == DFA_az09o4Send);
static_assert(_DFA_az___o___Send( 9, 0) == DFA_az10o1Send); static_assert(_DFA_az___o___Send( 9, 1) == DFA_az10o2Send); static_assert(_DFA_az___o___Send( 9, 2) == DFA_az10o3Send); static_assert(_DFA_az___o___Send( 9, 3) == DFA_az10o4Send);
static_assert(_DFA_az___o___Send(10, 0) == DFA_az11o1Send); static_assert(_DFA_az___o___Send(10, 1) == DFA_az11o2Send); static_assert(_DFA_az___o___Send(10, 2) == DFA_az11o3Send); static_assert(_DFA_az___o___Send(10, 3) == DFA_az11o4Send);
static_assert(_DFA_az___o___Send(11, 0) == DFA_az12o1Send); static_assert(_DFA_az___o___Send(11, 1) == DFA_az12o2Send); static_assert(_DFA_az___o___Send(11, 2) == DFA_az12o3Send); static_assert(_DFA_az___o___Send(11, 3) == DFA_az12o4Send);
static_assert(_DFA_az___o___Send(12, 0) == DFA_az13o1Send); static_assert(_DFA_az___o___Send(12, 1) == DFA_az13o2Send); static_assert(_DFA_az___o___Send(12, 2) == DFA_az13o3Send); static_assert(_DFA_az___o___Send(12, 3) == DFA_az13o4Send);
static_assert(_DFA_az___o___Send(13, 0) == DFA_az14o1Send); static_assert(_DFA_az___o___Send(13, 1) == DFA_az14o2Send); static_assert(_DFA_az___o___Send(13, 2) == DFA_az14o3Send); static_assert(_DFA_az___o___Send(13, 3) == DFA_az14o4Send);
static_assert(_DFA_az___o___Send(14, 0) == DFA_az15o1Send); static_assert(_DFA_az___o___Send(14, 1) == DFA_az15o2Send); static_assert(_DFA_az___o___Send(14, 2) == DFA_az15o3Send); static_assert(_DFA_az___o___Send(14, 3) == DFA_az15o4Send);
static_assert(_DFA_az___o___Send(15, 0) == DFA_az16o1Send); static_assert(_DFA_az___o___Send(15, 1) == DFA_az16o2Send); static_assert(_DFA_az___o___Send(15, 2) == DFA_az16o3Send); static_assert(_DFA_az___o___Send(15, 3) == DFA_az16o4Send);
#if DFA_DEF_STATES_COUNT > 16
static_assert(_DFA_az___o___Send(16, 0) == DFA_az17o1Send); static_assert(_DFA_az___o___Send(16, 1) == DFA_az17o2Send); static_assert(_DFA_az___o___Send(16, 2) == DFA_az17o3Send); static_assert(_DFA_az___o___Send(16, 3) == DFA_az17o4Send);
static_assert(_DFA_az___o___Send(17, 0) == DFA_az18o1Send); static_assert(_DFA_az___o___Send(17, 1) == DFA_az18o2Send); static_assert(_DFA_az___o___Send(17, 2) == DFA_az18o3Send); static_assert(_DFA_az___o___Send(17, 3) == DFA_az18o4Send);
static_assert(_DFA_az___o___Send(18, 0) == DFA_az19o1Send); static_assert(_DFA_az___o___Send(18, 1) == DFA_az19o2Send); static_assert(_DFA_az___o___Send(18, 2) == DFA_az19o3Send); static_assert(_DFA_az___o___Send(18, 3) == DFA_az19o4Send);
static_assert(_DFA_az___o___Send(19, 0) == DFA_az20o1Send); static_assert(_DFA_az___o___Send(19, 1) == DFA_az20o2Send); static_assert(_DFA_az___o___Send(19, 2) == DFA_az20o3Send); static_assert(_DFA_az___o___Send(19, 3) == DFA_az20o4Send);
static_assert(_DFA_az___o___Send(20, 0) == DFA_az21o1Send); static_assert(_DFA_az___o___Send(20, 1) == DFA_az21o2Send); static_assert(_DFA_az___o___Send(20, 2) == DFA_az21o3Send); static_assert(_DFA_az___o___Send(20, 3) == DFA_az21o4Send);
static_assert(_DFA_az___o___Send(21, 0) == DFA_az22o1Send); static_assert(_DFA_az___o___Send(21, 1) == DFA_az22o2Send); static_assert(_DFA_az___o___Send(21, 2) == DFA_az22o3Send); static_assert(_DFA_az___o___Send(21, 3) == DFA_az22o4Send);
static_assert(_DFA_az___o___Send(22, 0) == DFA_az23o1Send); static_assert(_DFA_az___o___Send(22, 1) == DFA_az23o2Send); static_assert(_DFA_az___o___Send(22, 2) == DFA_az23o3Send); static_assert(_DFA_az___o___Send(22, 3) == DFA_az23o4Send);
static_assert(_DFA_az___o___Send(23, 0) == DFA_az24o1Send); static_assert(_DFA_az___o___Send(23, 1) == DFA_az24o2Send); static_assert(_DFA_az___o___Send(23, 2) == DFA_az24o3Send); static_assert(_DFA_az___o___Send(23, 3) == DFA_az24o4Send);
static_assert(_DFA_az___o___Send(24, 0) == DFA_az25o1Send); static_assert(_DFA_az___o___Send(24, 1) == DFA_az25o2Send); static_assert(_DFA_az___o___Send(24, 2) == DFA_az25o3Send); static_assert(_DFA_az___o___Send(24, 3) == DFA_az25o4Send);
static_assert(_DFA_az___o___Send(25, 0) == DFA_az26o1Send); static_assert(_DFA_az___o___Send(25, 1) == DFA_az26o2Send); static_assert(_DFA_az___o___Send(25, 2) == DFA_az26o3Send); static_assert(_DFA_az___o___Send(25, 3) == DFA_az26o4Send);
static_assert(_DFA_az___o___Send(26, 0) == DFA_az27o1Send); static_assert(_DFA_az___o___Send(26, 1) == DFA_az27o2Send); static_assert(_DFA_az___o___Send(26, 2) == DFA_az27o3Send); static_assert(_DFA_az___o___Send(26, 3) == DFA_az27o4Send);
static_assert(_DFA_az___o___Send(27, 0) == DFA_az28o1Send); static_assert(_DFA_az___o___Send(27, 1) == DFA_az28o2Send); static_assert(_DFA_az___o___Send(27, 2) == DFA_az28o3Send); static_assert(_DFA_az___o___Send(27, 3) == DFA_az28o4Send);
static_assert(_DFA_az___o___Send(28, 0) == DFA_az29o1Send); static_assert(_DFA_az___o___Send(28, 1) == DFA_az29o2Send); static_assert(_DFA_az___o___Send(28, 2) == DFA_az29o3Send); static_assert(_DFA_az___o___Send(28, 3) == DFA_az29o4Send);
static_assert(_DFA_az___o___Send(29, 0) == DFA_az30o1Send); static_assert(_DFA_az___o___Send(29, 1) == DFA_az30o2Send); static_assert(_DFA_az___o___Send(29, 2) == DFA_az30o3Send); static_assert(_DFA_az___o___Send(29, 3) == DFA_az30o4Send);
static_assert(_DFA_az___o___Send(30, 0) == DFA_az31o1Send); static_assert(_DFA_az___o___Send(30, 1) == DFA_az31o2Send); static_assert(_DFA_az___o___Send(30, 2) == DFA_az31o3Send); static_assert(_DFA_az___o___Send(30, 3) == DFA_az31o4Send);
static_assert(_DFA_az___o___Send(31, 0) == DFA_az32o1Send); static_assert(_DFA_az___o___Send(31, 1) == DFA_az32o2Send); static_assert(_DFA_az___o___Send(31, 2) == DFA_az32o3Send); static_assert(_DFA_az___o___Send(31, 3) == DFA_az32o4Send);
#endif
#if DFA_DEF_STATES_COUNT > 32
static_assert(_DFA_az___o___Send(32, 0) == DFA_az33o1Send); static_assert(_DFA_az___o___Send(32, 1) == DFA_az33o2Send); static_assert(_DFA_az___o___Send(32, 2) == DFA_az33o3Send); static_assert(_DFA_az___o___Send(32, 3) == DFA_az33o4Send);
static_assert(_DFA_az___o___Send(33, 0) == DFA_az34o1Send); static_assert(_DFA_az___o___Send(33, 1) == DFA_az34o2Send); static_assert(_DFA_az___o___Send(33, 2) == DFA_az34o3Send); static_assert(_DFA_az___o___Send(33, 3) == DFA_az34o4Send);
static_assert(_DFA_az___o___Send(34, 0) == DFA_az35o1Send); static_assert(_DFA_az___o___Send(34, 1) == DFA_az35o2Send); static_assert(_DFA_az___o___Send(34, 2) == DFA_az35o3Send); static_assert(_DFA_az___o___Send(34, 3) == DFA_az35o4Send);
static_assert(_DFA_az___o___Send(35, 0) == DFA_az36o1Send); static_assert(_DFA_az___o___Send(35, 1) == DFA_az36o2Send); static_assert(_DFA_az___o___Send(35, 2) == DFA_az36o3Send); static_assert(_DFA_az___o___Send(35, 3) == DFA_az36o4Send);
static_assert(_DFA_az___o___Send(36, 0) == DFA_az37o1Send); static_assert(_DFA_az___o___Send(36, 1) == DFA_az37o2Send); static_assert(_DFA_az___o___Send(36, 2) == DFA_az37o3Send); static_assert(_DFA_az___o___Send(36, 3) == DFA_az37o4Send);
static_assert(_DFA_az___o___Send(37, 0) == DFA_az38o1Send); static_assert(_DFA_az___o___Send(37, 1) == DFA_az38o2Send); static_assert(_DFA_az___o___Send(37, 2) == DFA_az38o3Send); static_assert(_DFA_az___o___Send(37, 3) == DFA_az38o4Send);
static_assert(_DFA_az___o___Send(38, 0) == DFA_az39o1Send); static_assert(_DFA_az___o___Send(38, 1) == DFA_az39o2Send); static_assert(_DFA_az___o___Send(38, 2) == DFA_az39o3Send); static_assert(_DFA_az___o___Send(38, 3) == DFA_az39o4Send);
static_assert(_DFA_az___o___Send(39, 0) == DFA_az40o1Send); static_assert(_DFA_az___o___Send(39, 1) == DFA_az40o2Send); static_assert(_DFA_az___o___Send(39, 2) == DFA_az40o3Send); static_assert(_DFA_az___o___Send(39, 3) == DFA_az40o4Send);
static_assert(_DFA_az___o___Send(40, 0) == DFA_az41o1Send); static_assert(_DFA_az___o___Send(40, 1) == DFA_az41o2Send); static_assert(_DFA_az___o___Send(40, 2) == DFA_az41o3Send); static_assert(_DFA_az___o___Send(40, 3) == DFA_az41o4Send);
static_assert(_DFA_az___o___Send(41, 0) == DFA_az42o1Send); static_assert(_DFA_az___o___Send(41, 1) == DFA_az42o2Send); static_assert(_DFA_az___o___Send(41, 2) == DFA_az42o3Send); static_assert(_DFA_az___o___Send(41, 3) == DFA_az42o4Send);
static_assert(_DFA_az___o___Send(42, 0) == DFA_az43o1Send); static_assert(_DFA_az___o___Send(42, 1) == DFA_az43o2Send); static_assert(_DFA_az___o___Send(42, 2) == DFA_az43o3Send); static_assert(_DFA_az___o___Send(42, 3) == DFA_az43o4Send);
static_assert(_DFA_az___o___Send(43, 0) == DFA_az44o1Send); static_assert(_DFA_az___o___Send(43, 1) == DFA_az44o2Send); static_assert(_DFA_az___o___Send(43, 2) == DFA_az44o3Send); static_assert(_DFA_az___o___Send(43, 3) == DFA_az44o4Send);
static_assert(_DFA_az___o___Send(44, 0) == DFA_az45o1Send); static_assert(_DFA_az___o___Send(44, 1) == DFA_az45o2Send); static_assert(_DFA_az___o___Send(44, 2) == DFA_az45o3Send); static_assert(_DFA_az___o___Send(44, 3) == DFA_az45o4Send);
static_assert(_DFA_az___o___Send(45, 0) == DFA_az46o1Send); static_assert(_DFA_az___o___Send(45, 1) == DFA_az46o2Send); static_assert(_DFA_az___o___Send(45, 2) == DFA_az46o3Send); static_assert(_DFA_az___o___Send(45, 3) == DFA_az46o4Send);
static_assert(_DFA_az___o___Send(46, 0) == DFA_az47o1Send); static_assert(_DFA_az___o___Send(46, 1) == DFA_az47o2Send); static_assert(_DFA_az___o___Send(46, 2) == DFA_az47o3Send); static_assert(_DFA_az___o___Send(46, 3) == DFA_az47o4Send);
static_assert(_DFA_az___o___Send(47, 0) == DFA_az48o1Send); static_assert(_DFA_az___o___Send(47, 1) == DFA_az48o2Send); static_assert(_DFA_az___o___Send(47, 2) == DFA_az48o3Send); static_assert(_DFA_az___o___Send(47, 3) == DFA_az48o4Send);
static_assert(_DFA_az___o___Send(48, 0) == DFA_az49o1Send); static_assert(_DFA_az___o___Send(48, 1) == DFA_az49o2Send); static_assert(_DFA_az___o___Send(48, 2) == DFA_az49o3Send); static_assert(_DFA_az___o___Send(48, 3) == DFA_az49o4Send);
static_assert(_DFA_az___o___Send(49, 0) == DFA_az50o1Send); static_assert(_DFA_az___o___Send(49, 1) == DFA_az50o2Send); static_assert(_DFA_az___o___Send(49, 2) == DFA_az50o3Send); static_assert(_DFA_az___o___Send(49, 3) == DFA_az50o4Send);
static_assert(_DFA_az___o___Send(50, 0) == DFA_az51o1Send); static_assert(_DFA_az___o___Send(50, 1) == DFA_az51o2Send); static_assert(_DFA_az___o___Send(50, 2) == DFA_az51o3Send); static_assert(_DFA_az___o___Send(50, 3) == DFA_az51o4Send);
static_assert(_DFA_az___o___Send(51, 0) == DFA_az52o1Send); static_assert(_DFA_az___o___Send(51, 1) == DFA_az52o2Send); static_assert(_DFA_az___o___Send(51, 2) == DFA_az52o3Send); static_assert(_DFA_az___o___Send(51, 3) == DFA_az52o4Send);
static_assert(_DFA_az___o___Send(52, 0) == DFA_az53o1Send); static_assert(_DFA_az___o___Send(52, 1) == DFA_az53o2Send); static_assert(_DFA_az___o___Send(52, 2) == DFA_az53o3Send); static_assert(_DFA_az___o___Send(52, 3) == DFA_az53o4Send);
static_assert(_DFA_az___o___Send(53, 0) == DFA_az54o1Send); static_assert(_DFA_az___o___Send(53, 1) == DFA_az54o2Send); static_assert(_DFA_az___o___Send(53, 2) == DFA_az54o3Send); static_assert(_DFA_az___o___Send(53, 3) == DFA_az54o4Send);
static_assert(_DFA_az___o___Send(54, 0) == DFA_az55o1Send); static_assert(_DFA_az___o___Send(54, 1) == DFA_az55o2Send); static_assert(_DFA_az___o___Send(54, 2) == DFA_az55o3Send); static_assert(_DFA_az___o___Send(54, 3) == DFA_az55o4Send);
static_assert(_DFA_az___o___Send(55, 0) == DFA_az56o1Send); static_assert(_DFA_az___o___Send(55, 1) == DFA_az56o2Send); static_assert(_DFA_az___o___Send(55, 2) == DFA_az56o3Send); static_assert(_DFA_az___o___Send(55, 3) == DFA_az56o4Send);
static_assert(_DFA_az___o___Send(56, 0) == DFA_az57o1Send); static_assert(_DFA_az___o___Send(56, 1) == DFA_az57o2Send); static_assert(_DFA_az___o___Send(56, 2) == DFA_az57o3Send); static_assert(_DFA_az___o___Send(56, 3) == DFA_az57o4Send);
static_assert(_DFA_az___o___Send(57, 0) == DFA_az58o1Send); static_assert(_DFA_az___o___Send(57, 1) == DFA_az58o2Send); static_assert(_DFA_az___o___Send(57, 2) == DFA_az58o3Send); static_assert(_DFA_az___o___Send(57, 3) == DFA_az58o4Send);
static_assert(_DFA_az___o___Send(58, 0) == DFA_az59o1Send); static_assert(_DFA_az___o___Send(58, 1) == DFA_az59o2Send); static_assert(_DFA_az___o___Send(58, 2) == DFA_az59o3Send); static_assert(_DFA_az___o___Send(58, 3) == DFA_az59o4Send);
static_assert(_DFA_az___o___Send(59, 0) == DFA_az60o1Send); static_assert(_DFA_az___o___Send(59, 1) == DFA_az60o2Send); static_assert(_DFA_az___o___Send(59, 2) == DFA_az60o3Send); static_assert(_DFA_az___o___Send(59, 3) == DFA_az60o4Send);
static_assert(_DFA_az___o___Send(60, 0) == DFA_az61o1Send); static_assert(_DFA_az___o___Send(60, 1) == DFA_az61o2Send); static_assert(_DFA_az___o___Send(60, 2) == DFA_az61o3Send); static_assert(_DFA_az___o___Send(60, 3) == DFA_az61o4Send);
static_assert(_DFA_az___o___Send(61, 0) == DFA_az62o1Send); static_assert(_DFA_az___o___Send(61, 1) == DFA_az62o2Send); static_assert(_DFA_az___o___Send(61, 2) == DFA_az62o3Send); static_assert(_DFA_az___o___Send(61, 3) == DFA_az62o4Send);
static_assert(_DFA_az___o___Send(62, 0) == DFA_az63o1Send); static_assert(_DFA_az___o___Send(62, 1) == DFA_az63o2Send); static_assert(_DFA_az___o___Send(62, 2) == DFA_az63o3Send); static_assert(_DFA_az___o___Send(62, 3) == DFA_az63o4Send);
static_assert(_DFA_az___o___Send(63, 0) == DFA_az64o1Send); static_assert(_DFA_az___o___Send(63, 1) == DFA_az64o2Send); static_assert(_DFA_az___o___Send(63, 2) == DFA_az64o3Send); static_assert(_DFA_az___o___Send(63, 3) == DFA_az64o4Send);
#endif
#define _ParamDFA_az___o___Send(IDX_STATE, IDX_OUTPUT)  (knx.paramByte(DFA_ParamCalcIndex(_DFA_az___o___Send(IDX_STATE, IDX_OUTPUT))))

#define _DFA_az___o___Dpt1(IDX_STATE, IDX_OUTPUT)  (DFA_az01o1Dpt1 + IDX_STATE * (DFA_az02o1Dpt1 - DFA_az01o1Dpt1) + IDX_OUTPUT * (DFA_az01o2Dpt1 - DFA_az01o1Dpt1))
static_assert(_DFA_az___o___Dpt1( 0, 0) == DFA_az01o1Dpt1); static_assert(_DFA_az___o___Dpt1( 0, 1) == DFA_az01o2Dpt1); static_assert(_DFA_az___o___Dpt1( 0, 2) == DFA_az01o3Dpt1); static_assert(_DFA_az___o___Dpt1( 0, 3) == DFA_az01o4Dpt1);
static_assert(_DFA_az___o___Dpt1( 1, 0) == DFA_az02o1Dpt1); static_assert(_DFA_az___o___Dpt1( 1, 1) == DFA_az02o2Dpt1); static_assert(_DFA_az___o___Dpt1( 1, 2) == DFA_az02o3Dpt1); static_assert(_DFA_az___o___Dpt1( 1, 3) == DFA_az02o4Dpt1);
static_assert(_DFA_az___o___Dpt1( 2, 0) == DFA_az03o1Dpt1); static_assert(_DFA_az___o___Dpt1( 2, 1) == DFA_az03o2Dpt1); static_assert(_DFA_az___o___Dpt1( 2, 2) == DFA_az03o3Dpt1); static_assert(_DFA_az___o___Dpt1( 2, 3) == DFA_az03o4Dpt1);
static_assert(_DFA_az___o___Dpt1( 3, 0) == DFA_az04o1Dpt1); static_assert(_DFA_az___o___Dpt1( 3, 1) == DFA_az04o2Dpt1); static_assert(_DFA_az___o___Dpt1( 3, 2) == DFA_az04o3Dpt1); static_assert(_DFA_az___o___Dpt1( 3, 3) == DFA_az04o4Dpt1);
static_assert(_DFA_az___o___Dpt1( 4, 0) == DFA_az05o1Dpt1); static_assert(_DFA_az___o___Dpt1( 4, 1) == DFA_az05o2Dpt1); static_assert(_DFA_az___o___Dpt1( 4, 2) == DFA_az05o3Dpt1); static_assert(_DFA_az___o___Dpt1( 4, 3) == DFA_az05o4Dpt1);
static_assert(_DFA_az___o___Dpt1( 5, 0) == DFA_az06o1Dpt1); static_assert(_DFA_az___o___Dpt1( 5, 1) == DFA_az06o2Dpt1); static_assert(_DFA_az___o___Dpt1( 5, 2) == DFA_az06o3Dpt1); static_assert(_DFA_az___o___Dpt1( 5, 3) == DFA_az06o4Dpt1);
static_assert(_DFA_az___o___Dpt1( 6, 0) == DFA_az07o1Dpt1); static_assert(_DFA_az___o___Dpt1( 6, 1) == DFA_az07o2Dpt1); static_assert(_DFA_az___o___Dpt1( 6, 2) == DFA_az07o3Dpt1); static_assert(_DFA_az___o___Dpt1( 6, 3) == DFA_az07o4Dpt1);
static_assert(_DFA_az___o___Dpt1( 7, 0) == DFA_az08o1Dpt1); static_assert(_DFA_az___o___Dpt1( 7, 1) == DFA_az08o2Dpt1); static_assert(_DFA_az___o___Dpt1( 7, 2) == DFA_az08o3Dpt1); static_assert(_DFA_az___o___Dpt1( 7, 3) == DFA_az08o4Dpt1);
static_assert(_DFA_az___o___Dpt1( 8, 0) == DFA_az09o1Dpt1); static_assert(_DFA_az___o___Dpt1( 8, 1) == DFA_az09o2Dpt1); static_assert(_DFA_az___o___Dpt1( 8, 2) == DFA_az09o3Dpt1); static_assert(_DFA_az___o___Dpt1( 8, 3) == DFA_az09o4Dpt1);
static_assert(_DFA_az___o___Dpt1( 9, 0) == DFA_az10o1Dpt1); static_assert(_DFA_az___o___Dpt1( 9, 1) == DFA_az10o2Dpt1); static_assert(_DFA_az___o___Dpt1( 9, 2) == DFA_az10o3Dpt1); static_assert(_DFA_az___o___Dpt1( 9, 3) == DFA_az10o4Dpt1);
static_assert(_DFA_az___o___Dpt1(10, 0) == DFA_az11o1Dpt1); static_assert(_DFA_az___o___Dpt1(10, 1) == DFA_az11o2Dpt1); static_assert(_DFA_az___o___Dpt1(10, 2) == DFA_az11o3Dpt1); static_assert(_DFA_az___o___Dpt1(10, 3) == DFA_az11o4Dpt1);
static_assert(_DFA_az___o___Dpt1(11, 0) == DFA_az12o1Dpt1); static_assert(_DFA_az___o___Dpt1(11, 1) == DFA_az12o2Dpt1); static_assert(_DFA_az___o___Dpt1(11, 2) == DFA_az12o3Dpt1); static_assert(_DFA_az___o___Dpt1(11, 3) == DFA_az12o4Dpt1);
static_assert(_DFA_az___o___Dpt1(12, 0) == DFA_az13o1Dpt1); static_assert(_DFA_az___o___Dpt1(12, 1) == DFA_az13o2Dpt1); static_assert(_DFA_az___o___Dpt1(12, 2) == DFA_az13o3Dpt1); static_assert(_DFA_az___o___Dpt1(12, 3) == DFA_az13o4Dpt1);
static_assert(_DFA_az___o___Dpt1(13, 0) == DFA_az14o1Dpt1); static_assert(_DFA_az___o___Dpt1(13, 1) == DFA_az14o2Dpt1); static_assert(_DFA_az___o___Dpt1(13, 2) == DFA_az14o3Dpt1); static_assert(_DFA_az___o___Dpt1(13, 3) == DFA_az14o4Dpt1);
static_assert(_DFA_az___o___Dpt1(14, 0) == DFA_az15o1Dpt1); static_assert(_DFA_az___o___Dpt1(14, 1) == DFA_az15o2Dpt1); static_assert(_DFA_az___o___Dpt1(14, 2) == DFA_az15o3Dpt1); static_assert(_DFA_az___o___Dpt1(14, 3) == DFA_az15o4Dpt1);
static_assert(_DFA_az___o___Dpt1(15, 0) == DFA_az16o1Dpt1); static_assert(_DFA_az___o___Dpt1(15, 1) == DFA_az16o2Dpt1); static_assert(_DFA_az___o___Dpt1(15, 2) == DFA_az16o3Dpt1); static_assert(_DFA_az___o___Dpt1(15, 3) == DFA_az16o4Dpt1);
#if DFA_DEF_STATES_COUNT > 16
static_assert(_DFA_az___o___Dpt1(16, 0) == DFA_az17o1Dpt1); static_assert(_DFA_az___o___Dpt1(16, 1) == DFA_az17o2Dpt1); static_assert(_DFA_az___o___Dpt1(16, 2) == DFA_az17o3Dpt1); static_assert(_DFA_az___o___Dpt1(16, 3) == DFA_az17o4Dpt1);
static_assert(_DFA_az___o___Dpt1(17, 0) == DFA_az18o1Dpt1); static_assert(_DFA_az___o___Dpt1(17, 1) == DFA_az18o2Dpt1); static_assert(_DFA_az___o___Dpt1(17, 2) == DFA_az18o3Dpt1); static_assert(_DFA_az___o___Dpt1(17, 3) == DFA_az18o4Dpt1);
static_assert(_DFA_az___o___Dpt1(18, 0) == DFA_az19o1Dpt1); static_assert(_DFA_az___o___Dpt1(18, 1) == DFA_az19o2Dpt1); static_assert(_DFA_az___o___Dpt1(18, 2) == DFA_az19o3Dpt1); static_assert(_DFA_az___o___Dpt1(18, 3) == DFA_az19o4Dpt1);
static_assert(_DFA_az___o___Dpt1(19, 0) == DFA_az20o1Dpt1); static_assert(_DFA_az___o___Dpt1(19, 1) == DFA_az20o2Dpt1); static_assert(_DFA_az___o___Dpt1(19, 2) == DFA_az20o3Dpt1); static_assert(_DFA_az___o___Dpt1(19, 3) == DFA_az20o4Dpt1);
static_assert(_DFA_az___o___Dpt1(20, 0) == DFA_az21o1Dpt1); static_assert(_DFA_az___o___Dpt1(20, 1) == DFA_az21o2Dpt1); static_assert(_DFA_az___o___Dpt1(20, 2) == DFA_az21o3Dpt1); static_assert(_DFA_az___o___Dpt1(20, 3) == DFA_az21o4Dpt1);
static_assert(_DFA_az___o___Dpt1(21, 0) == DFA_az22o1Dpt1); static_assert(_DFA_az___o___Dpt1(21, 1) == DFA_az22o2Dpt1); static_assert(_DFA_az___o___Dpt1(21, 2) == DFA_az22o3Dpt1); static_assert(_DFA_az___o___Dpt1(21, 3) == DFA_az22o4Dpt1);
static_assert(_DFA_az___o___Dpt1(22, 0) == DFA_az23o1Dpt1); static_assert(_DFA_az___o___Dpt1(22, 1) == DFA_az23o2Dpt1); static_assert(_DFA_az___o___Dpt1(22, 2) == DFA_az23o3Dpt1); static_assert(_DFA_az___o___Dpt1(22, 3) == DFA_az23o4Dpt1);
static_assert(_DFA_az___o___Dpt1(23, 0) == DFA_az24o1Dpt1); static_assert(_DFA_az___o___Dpt1(23, 1) == DFA_az24o2Dpt1); static_assert(_DFA_az___o___Dpt1(23, 2) == DFA_az24o3Dpt1); static_assert(_DFA_az___o___Dpt1(23, 3) == DFA_az24o4Dpt1);
static_assert(_DFA_az___o___Dpt1(24, 0) == DFA_az25o1Dpt1); static_assert(_DFA_az___o___Dpt1(24, 1) == DFA_az25o2Dpt1); static_assert(_DFA_az___o___Dpt1(24, 2) == DFA_az25o3Dpt1); static_assert(_DFA_az___o___Dpt1(24, 3) == DFA_az25o4Dpt1);
static_assert(_DFA_az___o___Dpt1(25, 0) == DFA_az26o1Dpt1); static_assert(_DFA_az___o___Dpt1(25, 1) == DFA_az26o2Dpt1); static_assert(_DFA_az___o___Dpt1(25, 2) == DFA_az26o3Dpt1); static_assert(_DFA_az___o___Dpt1(25, 3) == DFA_az26o4Dpt1);
static_assert(_DFA_az___o___Dpt1(26, 0) == DFA_az27o1Dpt1); static_assert(_DFA_az___o___Dpt1(26, 1) == DFA_az27o2Dpt1); static_assert(_DFA_az___o___Dpt1(26, 2) == DFA_az27o3Dpt1); static_assert(_DFA_az___o___Dpt1(26, 3) == DFA_az27o4Dpt1);
static_assert(_DFA_az___o___Dpt1(27, 0) == DFA_az28o1Dpt1); static_assert(_DFA_az___o___Dpt1(27, 1) == DFA_az28o2Dpt1); static_assert(_DFA_az___o___Dpt1(27, 2) == DFA_az28o3Dpt1); static_assert(_DFA_az___o___Dpt1(27, 3) == DFA_az28o4Dpt1);
static_assert(_DFA_az___o___Dpt1(28, 0) == DFA_az29o1Dpt1); static_assert(_DFA_az___o___Dpt1(28, 1) == DFA_az29o2Dpt1); static_assert(_DFA_az___o___Dpt1(28, 2) == DFA_az29o3Dpt1); static_assert(_DFA_az___o___Dpt1(28, 3) == DFA_az29o4Dpt1);
static_assert(_DFA_az___o___Dpt1(29, 0) == DFA_az30o1Dpt1); static_assert(_DFA_az___o___Dpt1(29, 1) == DFA_az30o2Dpt1); static_assert(_DFA_az___o___Dpt1(29, 2) == DFA_az30o3Dpt1); static_assert(_DFA_az___o___Dpt1(29, 3) == DFA_az30o4Dpt1);
static_assert(_DFA_az___o___Dpt1(30, 0) == DFA_az31o1Dpt1); static_assert(_DFA_az___o___Dpt1(30, 1) == DFA_az31o2Dpt1); static_assert(_DFA_az___o___Dpt1(30, 2) == DFA_az31o3Dpt1); static_assert(_DFA_az___o___Dpt1(30, 3) == DFA_az31o4Dpt1);
static_assert(_DFA_az___o___Dpt1(31, 0) == DFA_az32o1Dpt1); static_assert(_DFA_az___o___Dpt1(31, 1) == DFA_az32o2Dpt1); static_assert(_DFA_az___o___Dpt1(31, 2) == DFA_az32o3Dpt1); static_assert(_DFA_az___o___Dpt1(31, 3) == DFA_az32o4Dpt1);
#endif
#if DFA_DEF_STATES_COUNT > 32
static_assert(_DFA_az___o___Dpt1(32, 0) == DFA_az33o1Dpt1); static_assert(_DFA_az___o___Dpt1(32, 1) == DFA_az33o2Dpt1); static_assert(_DFA_az___o___Dpt1(32, 2) == DFA_az33o3Dpt1); static_assert(_DFA_az___o___Dpt1(32, 3) == DFA_az33o4Dpt1);
static_assert(_DFA_az___o___Dpt1(33, 0) == DFA_az34o1Dpt1); static_assert(_DFA_az___o___Dpt1(33, 1) == DFA_az34o2Dpt1); static_assert(_DFA_az___o___Dpt1(33, 2) == DFA_az34o3Dpt1); static_assert(_DFA_az___o___Dpt1(33, 3) == DFA_az34o4Dpt1);
static_assert(_DFA_az___o___Dpt1(34, 0) == DFA_az35o1Dpt1); static_assert(_DFA_az___o___Dpt1(34, 1) == DFA_az35o2Dpt1); static_assert(_DFA_az___o___Dpt1(34, 2) == DFA_az35o3Dpt1); static_assert(_DFA_az___o___Dpt1(34, 3) == DFA_az35o4Dpt1);
static_assert(_DFA_az___o___Dpt1(35, 0) == DFA_az36o1Dpt1); static_assert(_DFA_az___o___Dpt1(35, 1) == DFA_az36o2Dpt1); static_assert(_DFA_az___o___Dpt1(35, 2) == DFA_az36o3Dpt1); static_assert(_DFA_az___o___Dpt1(35, 3) == DFA_az36o4Dpt1);
static_assert(_DFA_az___o___Dpt1(36, 0) == DFA_az37o1Dpt1); static_assert(_DFA_az___o___Dpt1(36, 1) == DFA_az37o2Dpt1); static_assert(_DFA_az___o___Dpt1(36, 2) == DFA_az37o3Dpt1); static_assert(_DFA_az___o___Dpt1(36, 3) == DFA_az37o4Dpt1);
static_assert(_DFA_az___o___Dpt1(37, 0) == DFA_az38o1Dpt1); static_assert(_DFA_az___o___Dpt1(37, 1) == DFA_az38o2Dpt1); static_assert(_DFA_az___o___Dpt1(37, 2) == DFA_az38o3Dpt1); static_assert(_DFA_az___o___Dpt1(37, 3) == DFA_az38o4Dpt1);
static_assert(_DFA_az___o___Dpt1(38, 0) == DFA_az39o1Dpt1); static_assert(_DFA_az___o___Dpt1(38, 1) == DFA_az39o2Dpt1); static_assert(_DFA_az___o___Dpt1(38, 2) == DFA_az39o3Dpt1); static_assert(_DFA_az___o___Dpt1(38, 3) == DFA_az39o4Dpt1);
static_assert(_DFA_az___o___Dpt1(39, 0) == DFA_az40o1Dpt1); static_assert(_DFA_az___o___Dpt1(39, 1) == DFA_az40o2Dpt1); static_assert(_DFA_az___o___Dpt1(39, 2) == DFA_az40o3Dpt1); static_assert(_DFA_az___o___Dpt1(39, 3) == DFA_az40o4Dpt1);
static_assert(_DFA_az___o___Dpt1(40, 0) == DFA_az41o1Dpt1); static_assert(_DFA_az___o___Dpt1(40, 1) == DFA_az41o2Dpt1); static_assert(_DFA_az___o___Dpt1(40, 2) == DFA_az41o3Dpt1); static_assert(_DFA_az___o___Dpt1(40, 3) == DFA_az41o4Dpt1);
static_assert(_DFA_az___o___Dpt1(41, 0) == DFA_az42o1Dpt1); static_assert(_DFA_az___o___Dpt1(41, 1) == DFA_az42o2Dpt1); static_assert(_DFA_az___o___Dpt1(41, 2) == DFA_az42o3Dpt1); static_assert(_DFA_az___o___Dpt1(41, 3) == DFA_az42o4Dpt1);
static_assert(_DFA_az___o___Dpt1(42, 0) == DFA_az43o1Dpt1); static_assert(_DFA_az___o___Dpt1(42, 1) == DFA_az43o2Dpt1); static_assert(_DFA_az___o___Dpt1(42, 2) == DFA_az43o3Dpt1); static_assert(_DFA_az___o___Dpt1(42, 3) == DFA_az43o4Dpt1);
static_assert(_DFA_az___o___Dpt1(43, 0) == DFA_az44o1Dpt1); static_assert(_DFA_az___o___Dpt1(43, 1) == DFA_az44o2Dpt1); static_assert(_DFA_az___o___Dpt1(43, 2) == DFA_az44o3Dpt1); static_assert(_DFA_az___o___Dpt1(43, 3) == DFA_az44o4Dpt1);
static_assert(_DFA_az___o___Dpt1(44, 0) == DFA_az45o1Dpt1); static_assert(_DFA_az___o___Dpt1(44, 1) == DFA_az45o2Dpt1); static_assert(_DFA_az___o___Dpt1(44, 2) == DFA_az45o3Dpt1); static_assert(_DFA_az___o___Dpt1(44, 3) == DFA_az45o4Dpt1);
static_assert(_DFA_az___o___Dpt1(45, 0) == DFA_az46o1Dpt1); static_assert(_DFA_az___o___Dpt1(45, 1) == DFA_az46o2Dpt1); static_assert(_DFA_az___o___Dpt1(45, 2) == DFA_az46o3Dpt1); static_assert(_DFA_az___o___Dpt1(45, 3) == DFA_az46o4Dpt1);
static_assert(_DFA_az___o___Dpt1(46, 0) == DFA_az47o1Dpt1); static_assert(_DFA_az___o___Dpt1(46, 1) == DFA_az47o2Dpt1); static_assert(_DFA_az___o___Dpt1(46, 2) == DFA_az47o3Dpt1); static_assert(_DFA_az___o___Dpt1(46, 3) == DFA_az47o4Dpt1);
static_assert(_DFA_az___o___Dpt1(47, 0) == DFA_az48o1Dpt1); static_assert(_DFA_az___o___Dpt1(47, 1) == DFA_az48o2Dpt1); static_assert(_DFA_az___o___Dpt1(47, 2) == DFA_az48o3Dpt1); static_assert(_DFA_az___o___Dpt1(47, 3) == DFA_az48o4Dpt1);
static_assert(_DFA_az___o___Dpt1(48, 0) == DFA_az49o1Dpt1); static_assert(_DFA_az___o___Dpt1(48, 1) == DFA_az49o2Dpt1); static_assert(_DFA_az___o___Dpt1(48, 2) == DFA_az49o3Dpt1); static_assert(_DFA_az___o___Dpt1(48, 3) == DFA_az49o4Dpt1);
static_assert(_DFA_az___o___Dpt1(49, 0) == DFA_az50o1Dpt1); static_assert(_DFA_az___o___Dpt1(49, 1) == DFA_az50o2Dpt1); static_assert(_DFA_az___o___Dpt1(49, 2) == DFA_az50o3Dpt1); static_assert(_DFA_az___o___Dpt1(49, 3) == DFA_az50o4Dpt1);
static_assert(_DFA_az___o___Dpt1(50, 0) == DFA_az51o1Dpt1); static_assert(_DFA_az___o___Dpt1(50, 1) == DFA_az51o2Dpt1); static_assert(_DFA_az___o___Dpt1(50, 2) == DFA_az51o3Dpt1); static_assert(_DFA_az___o___Dpt1(50, 3) == DFA_az51o4Dpt1);
static_assert(_DFA_az___o___Dpt1(51, 0) == DFA_az52o1Dpt1); static_assert(_DFA_az___o___Dpt1(51, 1) == DFA_az52o2Dpt1); static_assert(_DFA_az___o___Dpt1(51, 2) == DFA_az52o3Dpt1); static_assert(_DFA_az___o___Dpt1(51, 3) == DFA_az52o4Dpt1);
static_assert(_DFA_az___o___Dpt1(52, 0) == DFA_az53o1Dpt1); static_assert(_DFA_az___o___Dpt1(52, 1) == DFA_az53o2Dpt1); static_assert(_DFA_az___o___Dpt1(52, 2) == DFA_az53o3Dpt1); static_assert(_DFA_az___o___Dpt1(52, 3) == DFA_az53o4Dpt1);
static_assert(_DFA_az___o___Dpt1(53, 0) == DFA_az54o1Dpt1); static_assert(_DFA_az___o___Dpt1(53, 1) == DFA_az54o2Dpt1); static_assert(_DFA_az___o___Dpt1(53, 2) == DFA_az54o3Dpt1); static_assert(_DFA_az___o___Dpt1(53, 3) == DFA_az54o4Dpt1);
static_assert(_DFA_az___o___Dpt1(54, 0) == DFA_az55o1Dpt1); static_assert(_DFA_az___o___Dpt1(54, 1) == DFA_az55o2Dpt1); static_assert(_DFA_az___o___Dpt1(54, 2) == DFA_az55o3Dpt1); static_assert(_DFA_az___o___Dpt1(54, 3) == DFA_az55o4Dpt1);
static_assert(_DFA_az___o___Dpt1(55, 0) == DFA_az56o1Dpt1); static_assert(_DFA_az___o___Dpt1(55, 1) == DFA_az56o2Dpt1); static_assert(_DFA_az___o___Dpt1(55, 2) == DFA_az56o3Dpt1); static_assert(_DFA_az___o___Dpt1(55, 3) == DFA_az56o4Dpt1);
static_assert(_DFA_az___o___Dpt1(56, 0) == DFA_az57o1Dpt1); static_assert(_DFA_az___o___Dpt1(56, 1) == DFA_az57o2Dpt1); static_assert(_DFA_az___o___Dpt1(56, 2) == DFA_az57o3Dpt1); static_assert(_DFA_az___o___Dpt1(56, 3) == DFA_az57o4Dpt1);
static_assert(_DFA_az___o___Dpt1(57, 0) == DFA_az58o1Dpt1); static_assert(_DFA_az___o___Dpt1(57, 1) == DFA_az58o2Dpt1); static_assert(_DFA_az___o___Dpt1(57, 2) == DFA_az58o3Dpt1); static_assert(_DFA_az___o___Dpt1(57, 3) == DFA_az58o4Dpt1);
static_assert(_DFA_az___o___Dpt1(58, 0) == DFA_az59o1Dpt1); static_assert(_DFA_az___o___Dpt1(58, 1) == DFA_az59o2Dpt1); static_assert(_DFA_az___o___Dpt1(58, 2) == DFA_az59o3Dpt1); static_assert(_DFA_az___o___Dpt1(58, 3) == DFA_az59o4Dpt1);
static_assert(_DFA_az___o___Dpt1(59, 0) == DFA_az60o1Dpt1); static_assert(_DFA_az___o___Dpt1(59, 1) == DFA_az60o2Dpt1); static_assert(_DFA_az___o___Dpt1(59, 2) == DFA_az60o3Dpt1); static_assert(_DFA_az___o___Dpt1(59, 3) == DFA_az60o4Dpt1);
static_assert(_DFA_az___o___Dpt1(60, 0) == DFA_az61o1Dpt1); static_assert(_DFA_az___o___Dpt1(60, 1) == DFA_az61o2Dpt1); static_assert(_DFA_az___o___Dpt1(60, 2) == DFA_az61o3Dpt1); static_assert(_DFA_az___o___Dpt1(60, 3) == DFA_az61o4Dpt1);
static_assert(_DFA_az___o___Dpt1(61, 0) == DFA_az62o1Dpt1); static_assert(_DFA_az___o___Dpt1(61, 1) == DFA_az62o2Dpt1); static_assert(_DFA_az___o___Dpt1(61, 2) == DFA_az62o3Dpt1); static_assert(_DFA_az___o___Dpt1(61, 3) == DFA_az62o4Dpt1);
static_assert(_DFA_az___o___Dpt1(62, 0) == DFA_az63o1Dpt1); static_assert(_DFA_az___o___Dpt1(62, 1) == DFA_az63o2Dpt1); static_assert(_DFA_az___o___Dpt1(62, 2) == DFA_az63o3Dpt1); static_assert(_DFA_az___o___Dpt1(62, 3) == DFA_az63o4Dpt1);
static_assert(_DFA_az___o___Dpt1(63, 0) == DFA_az64o1Dpt1); static_assert(_DFA_az___o___Dpt1(63, 1) == DFA_az64o2Dpt1); static_assert(_DFA_az___o___Dpt1(63, 2) == DFA_az64o3Dpt1); static_assert(_DFA_az___o___Dpt1(63, 3) == DFA_az64o4Dpt1);
#endif
// #define _ParamDFA_az___o___Dpt1(IDX_STATE, IDX_OUTPUT)  (knx.paramByte(DFA_ParamCalcIndex(_DFA_az___o___Dpt1(IDX_STATE, IDX_OUTPUT))))
