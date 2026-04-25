// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2026 Cornelius Koepp

#include "DfaChannel.h"

static_assert(DFA_DEF_STATES_COUNT == 16 || DFA_DEF_STATES_COUNT == 32, "illegal DFA_DEF_STATES_COUNT");

#pragma region "DFA_CHANNEL_ADDR"

// Value of DFA_KoKOaInput{1..8,T} by 0-based index
#define _DFA_KoKOaInput___(IDX) (DFA_KoKOaInput1 + IDX * (DFA_KoKOaInput2 - DFA_KoKOaInput1))
static_assert(_DFA_KoKOaInput___(0) == DFA_KoKOaInput1);
static_assert(_DFA_KoKOaInput___(1) == DFA_KoKOaInput2);
static_assert(_DFA_KoKOaInput___(2) == DFA_KoKOaInput3);
static_assert(_DFA_KoKOaInput___(3) == DFA_KoKOaInput4);
static_assert(_DFA_KoKOaInput___(4) == DFA_KoKOaInput5);
static_assert(_DFA_KoKOaInput___(5) == DFA_KoKOaInput6);
static_assert(_DFA_KoKOaInput___(6) == DFA_KoKOaInput7);
static_assert(_DFA_KoKOaInput___(7) == DFA_KoKOaInput8);
static_assert(_DFA_KoKOaInput___(8) == DFA_KoKOaInputT);
#define _KoDFA_KOaInput___(IDX) (DFA_KoCalcNumber(_DFA_KoKOaInput___(IDX)))

// Value of DFA_aInputSymbol{1..8,T}Ko by 0-based index
#define _DFA_aSymbol___Input(IDX) (DFA_aSymbolAInput + IDX * (DFA_aSymbolBInput - DFA_aSymbolAInput))
static_assert(_DFA_aSymbol___Input(0) == DFA_aSymbolAInput);
static_assert(_DFA_aSymbol___Input(1) == DFA_aSymbolBInput);
static_assert(_DFA_aSymbol___Input(2) == DFA_aSymbolCInput);
static_assert(_DFA_aSymbol___Input(3) == DFA_aSymbolDInput);
static_assert(_DFA_aSymbol___Input(4) == DFA_aSymbolEInput);
static_assert(_DFA_aSymbol___Input(5) == DFA_aSymbolFInput);
static_assert(_DFA_aSymbol___Input(6) == DFA_aSymbolGInput);
static_assert(_DFA_aSymbol___Input(7) == DFA_aSymbolHInput);
static_assert(_DFA_aSymbol___Input(8) == DFA_aSymbolTInput);
#define _DFA_aSymbol___InputMask (DFA_aSymbolAInputMask)
#define _DFA_aSymbol___InputShift (DFA_aSymbolAInputShift)
static_assert(DFA_aSymbolAInputMask == _DFA_aSymbol___InputMask); static_assert(DFA_aSymbolAInputShift == _DFA_aSymbol___InputShift);
static_assert(DFA_aSymbolBInputMask == _DFA_aSymbol___InputMask); static_assert(DFA_aSymbolBInputShift == _DFA_aSymbol___InputShift);
static_assert(DFA_aSymbolCInputMask == _DFA_aSymbol___InputMask); static_assert(DFA_aSymbolCInputShift == _DFA_aSymbol___InputShift);
static_assert(DFA_aSymbolDInputMask == _DFA_aSymbol___InputMask); static_assert(DFA_aSymbolDInputShift == _DFA_aSymbol___InputShift);
static_assert(DFA_aSymbolEInputMask == _DFA_aSymbol___InputMask); static_assert(DFA_aSymbolEInputShift == _DFA_aSymbol___InputShift);
static_assert(DFA_aSymbolFInputMask == _DFA_aSymbol___InputMask); static_assert(DFA_aSymbolFInputShift == _DFA_aSymbol___InputShift);
static_assert(DFA_aSymbolGInputMask == _DFA_aSymbol___InputMask); static_assert(DFA_aSymbolGInputShift == _DFA_aSymbol___InputShift);
static_assert(DFA_aSymbolHInputMask == _DFA_aSymbol___InputMask); static_assert(DFA_aSymbolHInputShift == _DFA_aSymbol___InputShift);
static_assert(DFA_aSymbolTInputMask == _DFA_aSymbol___InputMask); static_assert(DFA_aSymbolTInputShift == _DFA_aSymbol___InputShift);
//                                    ((knx.paramByte(DFA_ParamCalcIndex(DFA_aSymbol{?}Input))     & DFA_aSymbolAInputMask) >> DFA_aSymbolAInputShift);
#define _ParamDFA_aSymbol___Input(IDX) ((knx.paramByte(DFA_ParamCalcIndex(_DFA_aSymbol___Input(IDX))) & _DFA_aSymbol___InputMask) >> _DFA_aSymbol___InputShift)


#define _DFA_aSymbol___LogicNumber(IDX) (DFA_aSymbolALogicNumber + IDX * (DFA_aSymbolBLogicNumber - DFA_aSymbolALogicNumber))
static_assert(_DFA_aSymbol___LogicNumber(0) == DFA_aSymbolALogicNumber);
static_assert(_DFA_aSymbol___LogicNumber(1) == DFA_aSymbolBLogicNumber);
static_assert(_DFA_aSymbol___LogicNumber(2) == DFA_aSymbolCLogicNumber);
static_assert(_DFA_aSymbol___LogicNumber(3) == DFA_aSymbolDLogicNumber);
static_assert(_DFA_aSymbol___LogicNumber(4) == DFA_aSymbolELogicNumber);
static_assert(_DFA_aSymbol___LogicNumber(5) == DFA_aSymbolFLogicNumber);
static_assert(_DFA_aSymbol___LogicNumber(6) == DFA_aSymbolGLogicNumber);
static_assert(_DFA_aSymbol___LogicNumber(7) == DFA_aSymbolHLogicNumber);
static_assert(_DFA_aSymbol___LogicNumber(8) == DFA_aSymbolTLogicNumber);
#ifdef DFA_aSymbolALogicNumberMask
    #error "DFA_aSymbolALogicNumber not expected to have Mask!"
#endif
#ifdef DFA_aSymbolALogicNumberShift
    #error "DFA_aSymbolALogicNumber not expected to have Shift!"
#endif
#define _ParamDFA_aSymbol___LogicNumber(IDX) (knx.paramWord(DFA_ParamCalcIndex(_DFA_aSymbol___LogicNumber(IDX))))

// return ((knx.paramWord(DFA_ParamCalcIndex(
//                                  DFA_aSymbolAKoNumber + input * (DFA_aSymbolBKoNumber - DFA_aSymbolAKoNumber))) & DFA_aSymbolAKoNumberMask) >> DFA_aSymbolAKoNumberShift);
#define _DFA_aSymbol___KoNumber(IDX) (DFA_aSymbolAKoNumber + IDX * (DFA_aSymbolBKoNumber - DFA_aSymbolAKoNumber))
static_assert(_DFA_aSymbol___KoNumber(0) == DFA_aSymbolAKoNumber);
static_assert(_DFA_aSymbol___KoNumber(1) == DFA_aSymbolBKoNumber);
static_assert(_DFA_aSymbol___KoNumber(2) == DFA_aSymbolCKoNumber);
static_assert(_DFA_aSymbol___KoNumber(3) == DFA_aSymbolDKoNumber);
static_assert(_DFA_aSymbol___KoNumber(4) == DFA_aSymbolEKoNumber);
static_assert(_DFA_aSymbol___KoNumber(5) == DFA_aSymbolFKoNumber);
static_assert(_DFA_aSymbol___KoNumber(6) == DFA_aSymbolGKoNumber);
static_assert(_DFA_aSymbol___KoNumber(7) == DFA_aSymbolHKoNumber);
static_assert(_DFA_aSymbol___KoNumber(8) == DFA_aSymbolTKoNumber);
#define _DFA_aSymbol___KoNumberMask (DFA_aSymbolAKoNumberMask)
#define _DFA_aSymbol___KoNumberShift (DFA_aSymbolAKoNumberShift)
static_assert(DFA_aSymbolAKoNumberMask == _DFA_aSymbol___KoNumberMask); static_assert(DFA_aSymbolAKoNumberShift == _DFA_aSymbol___KoNumberShift);
static_assert(DFA_aSymbolBKoNumberMask == _DFA_aSymbol___KoNumberMask); static_assert(DFA_aSymbolBKoNumberShift == _DFA_aSymbol___KoNumberShift);
static_assert(DFA_aSymbolCKoNumberMask == _DFA_aSymbol___KoNumberMask); static_assert(DFA_aSymbolCKoNumberShift == _DFA_aSymbol___KoNumberShift);
static_assert(DFA_aSymbolDKoNumberMask == _DFA_aSymbol___KoNumberMask); static_assert(DFA_aSymbolDKoNumberShift == _DFA_aSymbol___KoNumberShift);
static_assert(DFA_aSymbolEKoNumberMask == _DFA_aSymbol___KoNumberMask); static_assert(DFA_aSymbolEKoNumberShift == _DFA_aSymbol___KoNumberShift);
static_assert(DFA_aSymbolFKoNumberMask == _DFA_aSymbol___KoNumberMask); static_assert(DFA_aSymbolFKoNumberShift == _DFA_aSymbol___KoNumberShift);
static_assert(DFA_aSymbolGKoNumberMask == _DFA_aSymbol___KoNumberMask); static_assert(DFA_aSymbolGKoNumberShift == _DFA_aSymbol___KoNumberShift);
static_assert(DFA_aSymbolHKoNumberMask == _DFA_aSymbol___KoNumberMask); static_assert(DFA_aSymbolHKoNumberShift == _DFA_aSymbol___KoNumberShift);
static_assert(DFA_aSymbolTKoNumberMask == _DFA_aSymbol___KoNumberMask); static_assert(DFA_aSymbolTKoNumberShift == _DFA_aSymbol___KoNumberShift);
#define _ParamDFA_aSymbol___KoNumber(IDX) ((knx.paramWord(DFA_ParamCalcIndex(_DFA_aSymbol___KoNumber(IDX))) & _DFA_aSymbol___KoNumberMask) >> _DFA_aSymbol___KoNumberShift)

#define _DFA_aSymbol___Trigger(IDX) (DFA_aSymbolATrigger + IDX * (DFA_aSymbolBTrigger - DFA_aSymbolATrigger))
static_assert(_DFA_aSymbol___Trigger(0) == DFA_aSymbolATrigger);
static_assert(_DFA_aSymbol___Trigger(1) == DFA_aSymbolBTrigger);
static_assert(_DFA_aSymbol___Trigger(2) == DFA_aSymbolCTrigger);
static_assert(_DFA_aSymbol___Trigger(3) == DFA_aSymbolDTrigger);
static_assert(_DFA_aSymbol___Trigger(4) == DFA_aSymbolETrigger);
static_assert(_DFA_aSymbol___Trigger(5) == DFA_aSymbolFTrigger);
static_assert(_DFA_aSymbol___Trigger(6) == DFA_aSymbolGTrigger);
static_assert(_DFA_aSymbol___Trigger(7) == DFA_aSymbolHTrigger);
static_assert(_DFA_aSymbol___Trigger(8) == DFA_aSymbolTTrigger);
#define _DFA_aSymbol___TriggerMask (DFA_aSymbolATriggerMask)
#define _DFA_aSymbol___TriggerShift (DFA_aSymbolATriggerShift)
static_assert(DFA_aSymbolATriggerMask == _DFA_aSymbol___TriggerMask); static_assert(DFA_aSymbolATriggerShift == _DFA_aSymbol___TriggerShift);
static_assert(DFA_aSymbolBTriggerMask == _DFA_aSymbol___TriggerMask); static_assert(DFA_aSymbolBTriggerShift == _DFA_aSymbol___TriggerShift);
static_assert(DFA_aSymbolCTriggerMask == _DFA_aSymbol___TriggerMask); static_assert(DFA_aSymbolCTriggerShift == _DFA_aSymbol___TriggerShift);
static_assert(DFA_aSymbolDTriggerMask == _DFA_aSymbol___TriggerMask); static_assert(DFA_aSymbolDTriggerShift == _DFA_aSymbol___TriggerShift);
static_assert(DFA_aSymbolETriggerMask == _DFA_aSymbol___TriggerMask); static_assert(DFA_aSymbolETriggerShift == _DFA_aSymbol___TriggerShift);
static_assert(DFA_aSymbolFTriggerMask == _DFA_aSymbol___TriggerMask); static_assert(DFA_aSymbolFTriggerShift == _DFA_aSymbol___TriggerShift);
static_assert(DFA_aSymbolGTriggerMask == _DFA_aSymbol___TriggerMask); static_assert(DFA_aSymbolGTriggerShift == _DFA_aSymbol___TriggerShift);
static_assert(DFA_aSymbolHTriggerMask == _DFA_aSymbol___TriggerMask); static_assert(DFA_aSymbolHTriggerShift == _DFA_aSymbol___TriggerShift);
static_assert(DFA_aSymbolTTriggerMask == _DFA_aSymbol___TriggerMask); static_assert(DFA_aSymbolTTriggerShift == _DFA_aSymbol___TriggerShift);
// old usage:                              (knx.paramByte(DFA_ParamCalcIndex(DFA_aSymbol___Trigger( i ))) & DFA_aSymbol___TriggerMask) >> DFA_aSymbol___TriggerShift;
#define _ParamDFA_aSymbol___Trigger(IDX) ((knx.paramByte(DFA_ParamCalcIndex(_DFA_aSymbol___Trigger(IDX))) & _DFA_aSymbol___TriggerMask) >> _DFA_aSymbol___TriggerShift)


// Define (relative) parameter address-index for next state by current state and input

// #define DFA_aTransfer_State__N__Input__M__(N, M) (DFA_ad01A + N * (DFA_ad02A - DFA_ad01A) + M * (DFA_ad01B - DFA_ad01A))
#define _DFA_ad___(STATE_IDX, SYMBOL_IDX) (DFA_ad01A + STATE_IDX * (DFA_ad02A - DFA_ad01A) + SYMBOL_IDX * (DFA_ad01B - DFA_ad01A))
// Value of DFA_KoCalcNumber(DFA_KoKOaInput[1-8]) by 0-based index
static_assert(_DFA_ad___( 0, 0) == DFA_ad01A); static_assert(_DFA_ad___( 0, 1) == DFA_ad01B); static_assert(_DFA_ad___( 0, 2) == DFA_ad01C); static_assert(_DFA_ad___( 0, 3) == DFA_ad01D); static_assert(_DFA_ad___( 0, 4) == DFA_ad01E); static_assert(_DFA_ad___( 0, 5) == DFA_ad01F); static_assert(_DFA_ad___( 0, 6) == DFA_ad01G); static_assert(_DFA_ad___( 0, 7) == DFA_ad01H); static_assert(_DFA_ad___( 0, 8) == DFA_ad01T);
static_assert(_DFA_ad___( 1, 0) == DFA_ad02A); static_assert(_DFA_ad___( 1, 1) == DFA_ad02B); static_assert(_DFA_ad___( 1, 2) == DFA_ad02C); static_assert(_DFA_ad___( 1, 3) == DFA_ad02D); static_assert(_DFA_ad___( 1, 4) == DFA_ad02E); static_assert(_DFA_ad___( 1, 5) == DFA_ad02F); static_assert(_DFA_ad___( 1, 6) == DFA_ad02G); static_assert(_DFA_ad___( 1, 7) == DFA_ad02H); static_assert(_DFA_ad___( 1, 8) == DFA_ad02T);
static_assert(_DFA_ad___( 2, 0) == DFA_ad03A); static_assert(_DFA_ad___( 2, 1) == DFA_ad03B); static_assert(_DFA_ad___( 2, 2) == DFA_ad03C); static_assert(_DFA_ad___( 2, 3) == DFA_ad03D); static_assert(_DFA_ad___( 2, 4) == DFA_ad03E); static_assert(_DFA_ad___( 2, 5) == DFA_ad03F); static_assert(_DFA_ad___( 2, 6) == DFA_ad03G); static_assert(_DFA_ad___( 2, 7) == DFA_ad03H); static_assert(_DFA_ad___( 2, 8) == DFA_ad03T);
static_assert(_DFA_ad___( 3, 0) == DFA_ad04A); static_assert(_DFA_ad___( 3, 1) == DFA_ad04B); static_assert(_DFA_ad___( 3, 2) == DFA_ad04C); static_assert(_DFA_ad___( 3, 3) == DFA_ad04D); static_assert(_DFA_ad___( 3, 4) == DFA_ad04E); static_assert(_DFA_ad___( 3, 5) == DFA_ad04F); static_assert(_DFA_ad___( 3, 6) == DFA_ad04G); static_assert(_DFA_ad___( 3, 7) == DFA_ad04H); static_assert(_DFA_ad___( 3, 8) == DFA_ad04T);
static_assert(_DFA_ad___( 4, 0) == DFA_ad05A); static_assert(_DFA_ad___( 4, 1) == DFA_ad05B); static_assert(_DFA_ad___( 4, 2) == DFA_ad05C); static_assert(_DFA_ad___( 4, 3) == DFA_ad05D); static_assert(_DFA_ad___( 4, 4) == DFA_ad05E); static_assert(_DFA_ad___( 4, 5) == DFA_ad05F); static_assert(_DFA_ad___( 4, 6) == DFA_ad05G); static_assert(_DFA_ad___( 4, 7) == DFA_ad05H); static_assert(_DFA_ad___( 4, 8) == DFA_ad05T);
static_assert(_DFA_ad___( 5, 0) == DFA_ad06A); static_assert(_DFA_ad___( 5, 1) == DFA_ad06B); static_assert(_DFA_ad___( 5, 2) == DFA_ad06C); static_assert(_DFA_ad___( 5, 3) == DFA_ad06D); static_assert(_DFA_ad___( 5, 4) == DFA_ad06E); static_assert(_DFA_ad___( 5, 5) == DFA_ad06F); static_assert(_DFA_ad___( 5, 6) == DFA_ad06G); static_assert(_DFA_ad___( 5, 7) == DFA_ad06H); static_assert(_DFA_ad___( 5, 8) == DFA_ad06T);
static_assert(_DFA_ad___( 6, 0) == DFA_ad07A); static_assert(_DFA_ad___( 6, 1) == DFA_ad07B); static_assert(_DFA_ad___( 6, 2) == DFA_ad07C); static_assert(_DFA_ad___( 6, 3) == DFA_ad07D); static_assert(_DFA_ad___( 6, 4) == DFA_ad07E); static_assert(_DFA_ad___( 6, 5) == DFA_ad07F); static_assert(_DFA_ad___( 6, 6) == DFA_ad07G); static_assert(_DFA_ad___( 6, 7) == DFA_ad07H); static_assert(_DFA_ad___( 6, 8) == DFA_ad07T);
static_assert(_DFA_ad___( 7, 0) == DFA_ad08A); static_assert(_DFA_ad___( 7, 1) == DFA_ad08B); static_assert(_DFA_ad___( 7, 2) == DFA_ad08C); static_assert(_DFA_ad___( 7, 3) == DFA_ad08D); static_assert(_DFA_ad___( 7, 4) == DFA_ad08E); static_assert(_DFA_ad___( 7, 5) == DFA_ad08F); static_assert(_DFA_ad___( 7, 6) == DFA_ad08G); static_assert(_DFA_ad___( 7, 7) == DFA_ad08H); static_assert(_DFA_ad___( 7, 8) == DFA_ad08T);
static_assert(_DFA_ad___( 8, 0) == DFA_ad09A); static_assert(_DFA_ad___( 8, 1) == DFA_ad09B); static_assert(_DFA_ad___( 8, 2) == DFA_ad09C); static_assert(_DFA_ad___( 8, 3) == DFA_ad09D); static_assert(_DFA_ad___( 8, 4) == DFA_ad09E); static_assert(_DFA_ad___( 8, 5) == DFA_ad09F); static_assert(_DFA_ad___( 8, 6) == DFA_ad09G); static_assert(_DFA_ad___( 8, 7) == DFA_ad09H); static_assert(_DFA_ad___( 8, 8) == DFA_ad09T);
static_assert(_DFA_ad___( 9, 0) == DFA_ad10A); static_assert(_DFA_ad___( 9, 1) == DFA_ad10B); static_assert(_DFA_ad___( 9, 2) == DFA_ad10C); static_assert(_DFA_ad___( 9, 3) == DFA_ad10D); static_assert(_DFA_ad___( 9, 4) == DFA_ad10E); static_assert(_DFA_ad___( 9, 5) == DFA_ad10F); static_assert(_DFA_ad___( 9, 6) == DFA_ad10G); static_assert(_DFA_ad___( 9, 7) == DFA_ad10H); static_assert(_DFA_ad___( 9, 8) == DFA_ad10T);
static_assert(_DFA_ad___(10, 0) == DFA_ad11A); static_assert(_DFA_ad___(10, 1) == DFA_ad11B); static_assert(_DFA_ad___(10, 2) == DFA_ad11C); static_assert(_DFA_ad___(10, 3) == DFA_ad11D); static_assert(_DFA_ad___(10, 4) == DFA_ad11E); static_assert(_DFA_ad___(10, 5) == DFA_ad11F); static_assert(_DFA_ad___(10, 6) == DFA_ad11G); static_assert(_DFA_ad___(10, 7) == DFA_ad11H); static_assert(_DFA_ad___(10, 8) == DFA_ad11T);
static_assert(_DFA_ad___(11, 0) == DFA_ad12A); static_assert(_DFA_ad___(11, 1) == DFA_ad12B); static_assert(_DFA_ad___(11, 2) == DFA_ad12C); static_assert(_DFA_ad___(11, 3) == DFA_ad12D); static_assert(_DFA_ad___(11, 4) == DFA_ad12E); static_assert(_DFA_ad___(11, 5) == DFA_ad12F); static_assert(_DFA_ad___(11, 6) == DFA_ad12G); static_assert(_DFA_ad___(11, 7) == DFA_ad12H); static_assert(_DFA_ad___(11, 8) == DFA_ad12T);
static_assert(_DFA_ad___(12, 0) == DFA_ad13A); static_assert(_DFA_ad___(12, 1) == DFA_ad13B); static_assert(_DFA_ad___(12, 2) == DFA_ad13C); static_assert(_DFA_ad___(12, 3) == DFA_ad13D); static_assert(_DFA_ad___(12, 4) == DFA_ad13E); static_assert(_DFA_ad___(12, 5) == DFA_ad13F); static_assert(_DFA_ad___(12, 6) == DFA_ad13G); static_assert(_DFA_ad___(12, 7) == DFA_ad13H); static_assert(_DFA_ad___(12, 8) == DFA_ad13T);
static_assert(_DFA_ad___(13, 0) == DFA_ad14A); static_assert(_DFA_ad___(13, 1) == DFA_ad14B); static_assert(_DFA_ad___(13, 2) == DFA_ad14C); static_assert(_DFA_ad___(13, 3) == DFA_ad14D); static_assert(_DFA_ad___(13, 4) == DFA_ad14E); static_assert(_DFA_ad___(13, 5) == DFA_ad14F); static_assert(_DFA_ad___(13, 6) == DFA_ad14G); static_assert(_DFA_ad___(13, 7) == DFA_ad14H); static_assert(_DFA_ad___(13, 8) == DFA_ad14T);
static_assert(_DFA_ad___(14, 0) == DFA_ad15A); static_assert(_DFA_ad___(14, 1) == DFA_ad15B); static_assert(_DFA_ad___(14, 2) == DFA_ad15C); static_assert(_DFA_ad___(14, 3) == DFA_ad15D); static_assert(_DFA_ad___(14, 4) == DFA_ad15E); static_assert(_DFA_ad___(14, 5) == DFA_ad15F); static_assert(_DFA_ad___(14, 6) == DFA_ad15G); static_assert(_DFA_ad___(14, 7) == DFA_ad15H); static_assert(_DFA_ad___(14, 8) == DFA_ad15T);
static_assert(_DFA_ad___(15, 0) == DFA_ad16A); static_assert(_DFA_ad___(15, 1) == DFA_ad16B); static_assert(_DFA_ad___(15, 2) == DFA_ad16C); static_assert(_DFA_ad___(15, 3) == DFA_ad16D); static_assert(_DFA_ad___(15, 4) == DFA_ad16E); static_assert(_DFA_ad___(15, 5) == DFA_ad16F); static_assert(_DFA_ad___(15, 6) == DFA_ad16G); static_assert(_DFA_ad___(15, 7) == DFA_ad16H); static_assert(_DFA_ad___(15, 8) == DFA_ad16T);
#if DFA_DEF_STATES_COUNT > 16
static_assert(_DFA_ad___(16, 0) == DFA_ad17A); static_assert(_DFA_ad___(16, 1) == DFA_ad17B); static_assert(_DFA_ad___(16, 2) == DFA_ad17C); static_assert(_DFA_ad___(16, 3) == DFA_ad17D); static_assert(_DFA_ad___(16, 4) == DFA_ad17E); static_assert(_DFA_ad___(16, 5) == DFA_ad17F); static_assert(_DFA_ad___(16, 6) == DFA_ad17G); static_assert(_DFA_ad___(16, 7) == DFA_ad17H); static_assert(_DFA_ad___(16, 8) == DFA_ad17T);
static_assert(_DFA_ad___(17, 0) == DFA_ad18A); static_assert(_DFA_ad___(17, 1) == DFA_ad18B); static_assert(_DFA_ad___(17, 2) == DFA_ad18C); static_assert(_DFA_ad___(17, 3) == DFA_ad18D); static_assert(_DFA_ad___(17, 4) == DFA_ad18E); static_assert(_DFA_ad___(17, 5) == DFA_ad18F); static_assert(_DFA_ad___(17, 6) == DFA_ad18G); static_assert(_DFA_ad___(17, 7) == DFA_ad18H); static_assert(_DFA_ad___(17, 8) == DFA_ad18T);
static_assert(_DFA_ad___(18, 0) == DFA_ad19A); static_assert(_DFA_ad___(18, 1) == DFA_ad19B); static_assert(_DFA_ad___(18, 2) == DFA_ad19C); static_assert(_DFA_ad___(18, 3) == DFA_ad19D); static_assert(_DFA_ad___(18, 4) == DFA_ad19E); static_assert(_DFA_ad___(18, 5) == DFA_ad19F); static_assert(_DFA_ad___(18, 6) == DFA_ad19G); static_assert(_DFA_ad___(18, 7) == DFA_ad19H); static_assert(_DFA_ad___(18, 8) == DFA_ad19T);
static_assert(_DFA_ad___(19, 0) == DFA_ad20A); static_assert(_DFA_ad___(19, 1) == DFA_ad20B); static_assert(_DFA_ad___(19, 2) == DFA_ad20C); static_assert(_DFA_ad___(19, 3) == DFA_ad20D); static_assert(_DFA_ad___(19, 4) == DFA_ad20E); static_assert(_DFA_ad___(19, 5) == DFA_ad20F); static_assert(_DFA_ad___(19, 6) == DFA_ad20G); static_assert(_DFA_ad___(19, 7) == DFA_ad20H); static_assert(_DFA_ad___(19, 8) == DFA_ad20T);
static_assert(_DFA_ad___(20, 0) == DFA_ad21A); static_assert(_DFA_ad___(20, 1) == DFA_ad21B); static_assert(_DFA_ad___(20, 2) == DFA_ad21C); static_assert(_DFA_ad___(20, 3) == DFA_ad21D); static_assert(_DFA_ad___(20, 4) == DFA_ad21E); static_assert(_DFA_ad___(20, 5) == DFA_ad21F); static_assert(_DFA_ad___(20, 6) == DFA_ad21G); static_assert(_DFA_ad___(20, 7) == DFA_ad21H); static_assert(_DFA_ad___(20, 8) == DFA_ad21T);
static_assert(_DFA_ad___(21, 0) == DFA_ad22A); static_assert(_DFA_ad___(21, 1) == DFA_ad22B); static_assert(_DFA_ad___(21, 2) == DFA_ad22C); static_assert(_DFA_ad___(21, 3) == DFA_ad22D); static_assert(_DFA_ad___(21, 4) == DFA_ad22E); static_assert(_DFA_ad___(21, 5) == DFA_ad22F); static_assert(_DFA_ad___(21, 6) == DFA_ad22G); static_assert(_DFA_ad___(21, 7) == DFA_ad22H); static_assert(_DFA_ad___(21, 8) == DFA_ad22T);
static_assert(_DFA_ad___(22, 0) == DFA_ad23A); static_assert(_DFA_ad___(22, 1) == DFA_ad23B); static_assert(_DFA_ad___(22, 2) == DFA_ad23C); static_assert(_DFA_ad___(22, 3) == DFA_ad23D); static_assert(_DFA_ad___(22, 4) == DFA_ad23E); static_assert(_DFA_ad___(22, 5) == DFA_ad23F); static_assert(_DFA_ad___(22, 6) == DFA_ad23G); static_assert(_DFA_ad___(22, 7) == DFA_ad23H); static_assert(_DFA_ad___(22, 8) == DFA_ad23T);
static_assert(_DFA_ad___(23, 0) == DFA_ad24A); static_assert(_DFA_ad___(23, 1) == DFA_ad24B); static_assert(_DFA_ad___(23, 2) == DFA_ad24C); static_assert(_DFA_ad___(23, 3) == DFA_ad24D); static_assert(_DFA_ad___(23, 4) == DFA_ad24E); static_assert(_DFA_ad___(23, 5) == DFA_ad24F); static_assert(_DFA_ad___(23, 6) == DFA_ad24G); static_assert(_DFA_ad___(23, 7) == DFA_ad24H); static_assert(_DFA_ad___(23, 8) == DFA_ad24T);
static_assert(_DFA_ad___(24, 0) == DFA_ad25A); static_assert(_DFA_ad___(24, 1) == DFA_ad25B); static_assert(_DFA_ad___(24, 2) == DFA_ad25C); static_assert(_DFA_ad___(24, 3) == DFA_ad25D); static_assert(_DFA_ad___(24, 4) == DFA_ad25E); static_assert(_DFA_ad___(24, 5) == DFA_ad25F); static_assert(_DFA_ad___(24, 6) == DFA_ad25G); static_assert(_DFA_ad___(24, 7) == DFA_ad25H); static_assert(_DFA_ad___(24, 8) == DFA_ad25T);
static_assert(_DFA_ad___(25, 0) == DFA_ad26A); static_assert(_DFA_ad___(25, 1) == DFA_ad26B); static_assert(_DFA_ad___(25, 2) == DFA_ad26C); static_assert(_DFA_ad___(25, 3) == DFA_ad26D); static_assert(_DFA_ad___(25, 4) == DFA_ad26E); static_assert(_DFA_ad___(25, 5) == DFA_ad26F); static_assert(_DFA_ad___(25, 6) == DFA_ad26G); static_assert(_DFA_ad___(25, 7) == DFA_ad26H); static_assert(_DFA_ad___(25, 8) == DFA_ad26T);
static_assert(_DFA_ad___(26, 0) == DFA_ad27A); static_assert(_DFA_ad___(26, 1) == DFA_ad27B); static_assert(_DFA_ad___(26, 2) == DFA_ad27C); static_assert(_DFA_ad___(26, 3) == DFA_ad27D); static_assert(_DFA_ad___(26, 4) == DFA_ad27E); static_assert(_DFA_ad___(26, 5) == DFA_ad27F); static_assert(_DFA_ad___(26, 6) == DFA_ad27G); static_assert(_DFA_ad___(26, 7) == DFA_ad27H); static_assert(_DFA_ad___(26, 8) == DFA_ad27T);
static_assert(_DFA_ad___(27, 0) == DFA_ad28A); static_assert(_DFA_ad___(27, 1) == DFA_ad28B); static_assert(_DFA_ad___(27, 2) == DFA_ad28C); static_assert(_DFA_ad___(27, 3) == DFA_ad28D); static_assert(_DFA_ad___(27, 4) == DFA_ad28E); static_assert(_DFA_ad___(27, 5) == DFA_ad28F); static_assert(_DFA_ad___(27, 6) == DFA_ad28G); static_assert(_DFA_ad___(27, 7) == DFA_ad28H); static_assert(_DFA_ad___(27, 8) == DFA_ad28T);
static_assert(_DFA_ad___(28, 0) == DFA_ad29A); static_assert(_DFA_ad___(28, 1) == DFA_ad29B); static_assert(_DFA_ad___(28, 2) == DFA_ad29C); static_assert(_DFA_ad___(28, 3) == DFA_ad29D); static_assert(_DFA_ad___(28, 4) == DFA_ad29E); static_assert(_DFA_ad___(28, 5) == DFA_ad29F); static_assert(_DFA_ad___(28, 6) == DFA_ad29G); static_assert(_DFA_ad___(28, 7) == DFA_ad29H); static_assert(_DFA_ad___(28, 8) == DFA_ad29T);
static_assert(_DFA_ad___(29, 0) == DFA_ad30A); static_assert(_DFA_ad___(29, 1) == DFA_ad30B); static_assert(_DFA_ad___(29, 2) == DFA_ad30C); static_assert(_DFA_ad___(29, 3) == DFA_ad30D); static_assert(_DFA_ad___(29, 4) == DFA_ad30E); static_assert(_DFA_ad___(29, 5) == DFA_ad30F); static_assert(_DFA_ad___(29, 6) == DFA_ad30G); static_assert(_DFA_ad___(29, 7) == DFA_ad30H); static_assert(_DFA_ad___(29, 8) == DFA_ad30T);
static_assert(_DFA_ad___(30, 0) == DFA_ad31A); static_assert(_DFA_ad___(30, 1) == DFA_ad31B); static_assert(_DFA_ad___(30, 2) == DFA_ad31C); static_assert(_DFA_ad___(30, 3) == DFA_ad31D); static_assert(_DFA_ad___(30, 4) == DFA_ad31E); static_assert(_DFA_ad___(30, 5) == DFA_ad31F); static_assert(_DFA_ad___(30, 6) == DFA_ad31G); static_assert(_DFA_ad___(30, 7) == DFA_ad31H); static_assert(_DFA_ad___(30, 8) == DFA_ad31T);
static_assert(_DFA_ad___(31, 0) == DFA_ad32A); static_assert(_DFA_ad___(31, 1) == DFA_ad32B); static_assert(_DFA_ad___(31, 2) == DFA_ad32C); static_assert(_DFA_ad___(31, 3) == DFA_ad32D); static_assert(_DFA_ad___(31, 4) == DFA_ad32E); static_assert(_DFA_ad___(31, 5) == DFA_ad32F); static_assert(_DFA_ad___(31, 6) == DFA_ad32G); static_assert(_DFA_ad___(31, 7) == DFA_ad32H); static_assert(_DFA_ad___(31, 8) == DFA_ad32T);
#endif
#if DFA_DEF_STATES_COUNT > 32
static_assert(_DFA_ad___(32, 0) == DFA_ad33A); static_assert(_DFA_ad___(32, 1) == DFA_ad33B); static_assert(_DFA_ad___(32, 2) == DFA_ad33C); static_assert(_DFA_ad___(32, 3) == DFA_ad33D); static_assert(_DFA_ad___(32, 4) == DFA_ad33E); static_assert(_DFA_ad___(32, 5) == DFA_ad33F); static_assert(_DFA_ad___(32, 6) == DFA_ad33G); static_assert(_DFA_ad___(32, 7) == DFA_ad33H); static_assert(_DFA_ad___(32, 8) == DFA_ad33T);
static_assert(_DFA_ad___(33, 0) == DFA_ad34A); static_assert(_DFA_ad___(33, 1) == DFA_ad34B); static_assert(_DFA_ad___(33, 2) == DFA_ad34C); static_assert(_DFA_ad___(33, 3) == DFA_ad34D); static_assert(_DFA_ad___(33, 4) == DFA_ad34E); static_assert(_DFA_ad___(33, 5) == DFA_ad34F); static_assert(_DFA_ad___(33, 6) == DFA_ad34G); static_assert(_DFA_ad___(33, 7) == DFA_ad34H); static_assert(_DFA_ad___(33, 8) == DFA_ad34T);
static_assert(_DFA_ad___(34, 0) == DFA_ad35A); static_assert(_DFA_ad___(34, 1) == DFA_ad35B); static_assert(_DFA_ad___(34, 2) == DFA_ad35C); static_assert(_DFA_ad___(34, 3) == DFA_ad35D); static_assert(_DFA_ad___(34, 4) == DFA_ad35E); static_assert(_DFA_ad___(34, 5) == DFA_ad35F); static_assert(_DFA_ad___(34, 6) == DFA_ad35G); static_assert(_DFA_ad___(34, 7) == DFA_ad35H); static_assert(_DFA_ad___(34, 8) == DFA_ad35T);
static_assert(_DFA_ad___(35, 0) == DFA_ad36A); static_assert(_DFA_ad___(35, 1) == DFA_ad36B); static_assert(_DFA_ad___(35, 2) == DFA_ad36C); static_assert(_DFA_ad___(35, 3) == DFA_ad36D); static_assert(_DFA_ad___(35, 4) == DFA_ad36E); static_assert(_DFA_ad___(35, 5) == DFA_ad36F); static_assert(_DFA_ad___(35, 6) == DFA_ad36G); static_assert(_DFA_ad___(35, 7) == DFA_ad36H); static_assert(_DFA_ad___(35, 8) == DFA_ad36T);
static_assert(_DFA_ad___(36, 0) == DFA_ad37A); static_assert(_DFA_ad___(36, 1) == DFA_ad37B); static_assert(_DFA_ad___(36, 2) == DFA_ad37C); static_assert(_DFA_ad___(36, 3) == DFA_ad37D); static_assert(_DFA_ad___(36, 4) == DFA_ad37E); static_assert(_DFA_ad___(36, 5) == DFA_ad37F); static_assert(_DFA_ad___(36, 6) == DFA_ad37G); static_assert(_DFA_ad___(36, 7) == DFA_ad37H); static_assert(_DFA_ad___(36, 8) == DFA_ad37T);
static_assert(_DFA_ad___(37, 0) == DFA_ad38A); static_assert(_DFA_ad___(37, 1) == DFA_ad38B); static_assert(_DFA_ad___(37, 2) == DFA_ad38C); static_assert(_DFA_ad___(37, 3) == DFA_ad38D); static_assert(_DFA_ad___(37, 4) == DFA_ad38E); static_assert(_DFA_ad___(37, 5) == DFA_ad38F); static_assert(_DFA_ad___(37, 6) == DFA_ad38G); static_assert(_DFA_ad___(37, 7) == DFA_ad38H); static_assert(_DFA_ad___(37, 8) == DFA_ad38T);
static_assert(_DFA_ad___(38, 0) == DFA_ad39A); static_assert(_DFA_ad___(38, 1) == DFA_ad39B); static_assert(_DFA_ad___(38, 2) == DFA_ad39C); static_assert(_DFA_ad___(38, 3) == DFA_ad39D); static_assert(_DFA_ad___(38, 4) == DFA_ad39E); static_assert(_DFA_ad___(38, 5) == DFA_ad39F); static_assert(_DFA_ad___(38, 6) == DFA_ad39G); static_assert(_DFA_ad___(38, 7) == DFA_ad39H); static_assert(_DFA_ad___(38, 8) == DFA_ad39T);
static_assert(_DFA_ad___(39, 0) == DFA_ad40A); static_assert(_DFA_ad___(39, 1) == DFA_ad40B); static_assert(_DFA_ad___(39, 2) == DFA_ad40C); static_assert(_DFA_ad___(39, 3) == DFA_ad40D); static_assert(_DFA_ad___(39, 4) == DFA_ad40E); static_assert(_DFA_ad___(39, 5) == DFA_ad40F); static_assert(_DFA_ad___(39, 6) == DFA_ad40G); static_assert(_DFA_ad___(39, 7) == DFA_ad40H); static_assert(_DFA_ad___(39, 8) == DFA_ad40T);
static_assert(_DFA_ad___(40, 0) == DFA_ad41A); static_assert(_DFA_ad___(40, 1) == DFA_ad41B); static_assert(_DFA_ad___(40, 2) == DFA_ad41C); static_assert(_DFA_ad___(40, 3) == DFA_ad41D); static_assert(_DFA_ad___(40, 4) == DFA_ad41E); static_assert(_DFA_ad___(40, 5) == DFA_ad41F); static_assert(_DFA_ad___(40, 6) == DFA_ad41G); static_assert(_DFA_ad___(40, 7) == DFA_ad41H); static_assert(_DFA_ad___(40, 8) == DFA_ad41T);
static_assert(_DFA_ad___(41, 0) == DFA_ad42A); static_assert(_DFA_ad___(41, 1) == DFA_ad42B); static_assert(_DFA_ad___(41, 2) == DFA_ad42C); static_assert(_DFA_ad___(41, 3) == DFA_ad42D); static_assert(_DFA_ad___(41, 4) == DFA_ad42E); static_assert(_DFA_ad___(41, 5) == DFA_ad42F); static_assert(_DFA_ad___(41, 6) == DFA_ad42G); static_assert(_DFA_ad___(41, 7) == DFA_ad42H); static_assert(_DFA_ad___(41, 8) == DFA_ad42T);
static_assert(_DFA_ad___(42, 0) == DFA_ad43A); static_assert(_DFA_ad___(42, 1) == DFA_ad43B); static_assert(_DFA_ad___(42, 2) == DFA_ad43C); static_assert(_DFA_ad___(42, 3) == DFA_ad43D); static_assert(_DFA_ad___(42, 4) == DFA_ad43E); static_assert(_DFA_ad___(42, 5) == DFA_ad43F); static_assert(_DFA_ad___(42, 6) == DFA_ad43G); static_assert(_DFA_ad___(42, 7) == DFA_ad43H); static_assert(_DFA_ad___(42, 8) == DFA_ad43T);
static_assert(_DFA_ad___(43, 0) == DFA_ad44A); static_assert(_DFA_ad___(43, 1) == DFA_ad44B); static_assert(_DFA_ad___(43, 2) == DFA_ad44C); static_assert(_DFA_ad___(43, 3) == DFA_ad44D); static_assert(_DFA_ad___(43, 4) == DFA_ad44E); static_assert(_DFA_ad___(43, 5) == DFA_ad44F); static_assert(_DFA_ad___(43, 6) == DFA_ad44G); static_assert(_DFA_ad___(43, 7) == DFA_ad44H); static_assert(_DFA_ad___(43, 8) == DFA_ad44T);
static_assert(_DFA_ad___(44, 0) == DFA_ad45A); static_assert(_DFA_ad___(44, 1) == DFA_ad45B); static_assert(_DFA_ad___(44, 2) == DFA_ad45C); static_assert(_DFA_ad___(44, 3) == DFA_ad45D); static_assert(_DFA_ad___(44, 4) == DFA_ad45E); static_assert(_DFA_ad___(44, 5) == DFA_ad45F); static_assert(_DFA_ad___(44, 6) == DFA_ad45G); static_assert(_DFA_ad___(44, 7) == DFA_ad45H); static_assert(_DFA_ad___(44, 8) == DFA_ad45T);
static_assert(_DFA_ad___(45, 0) == DFA_ad46A); static_assert(_DFA_ad___(45, 1) == DFA_ad46B); static_assert(_DFA_ad___(45, 2) == DFA_ad46C); static_assert(_DFA_ad___(45, 3) == DFA_ad46D); static_assert(_DFA_ad___(45, 4) == DFA_ad46E); static_assert(_DFA_ad___(45, 5) == DFA_ad46F); static_assert(_DFA_ad___(45, 6) == DFA_ad46G); static_assert(_DFA_ad___(45, 7) == DFA_ad46H); static_assert(_DFA_ad___(45, 8) == DFA_ad46T);
static_assert(_DFA_ad___(46, 0) == DFA_ad47A); static_assert(_DFA_ad___(46, 1) == DFA_ad47B); static_assert(_DFA_ad___(46, 2) == DFA_ad47C); static_assert(_DFA_ad___(46, 3) == DFA_ad47D); static_assert(_DFA_ad___(46, 4) == DFA_ad47E); static_assert(_DFA_ad___(46, 5) == DFA_ad47F); static_assert(_DFA_ad___(46, 6) == DFA_ad47G); static_assert(_DFA_ad___(46, 7) == DFA_ad47H); static_assert(_DFA_ad___(46, 8) == DFA_ad47T);
static_assert(_DFA_ad___(47, 0) == DFA_ad48A); static_assert(_DFA_ad___(47, 1) == DFA_ad48B); static_assert(_DFA_ad___(47, 2) == DFA_ad48C); static_assert(_DFA_ad___(47, 3) == DFA_ad48D); static_assert(_DFA_ad___(47, 4) == DFA_ad48E); static_assert(_DFA_ad___(47, 5) == DFA_ad48F); static_assert(_DFA_ad___(47, 6) == DFA_ad48G); static_assert(_DFA_ad___(47, 7) == DFA_ad48H); static_assert(_DFA_ad___(47, 8) == DFA_ad48T);
static_assert(_DFA_ad___(48, 0) == DFA_ad49A); static_assert(_DFA_ad___(48, 1) == DFA_ad49B); static_assert(_DFA_ad___(48, 2) == DFA_ad49C); static_assert(_DFA_ad___(48, 3) == DFA_ad49D); static_assert(_DFA_ad___(48, 4) == DFA_ad49E); static_assert(_DFA_ad___(48, 5) == DFA_ad49F); static_assert(_DFA_ad___(48, 6) == DFA_ad49G); static_assert(_DFA_ad___(48, 7) == DFA_ad49H); static_assert(_DFA_ad___(48, 8) == DFA_ad49T);
static_assert(_DFA_ad___(49, 0) == DFA_ad50A); static_assert(_DFA_ad___(49, 1) == DFA_ad50B); static_assert(_DFA_ad___(49, 2) == DFA_ad50C); static_assert(_DFA_ad___(49, 3) == DFA_ad50D); static_assert(_DFA_ad___(49, 4) == DFA_ad50E); static_assert(_DFA_ad___(49, 5) == DFA_ad50F); static_assert(_DFA_ad___(49, 6) == DFA_ad50G); static_assert(_DFA_ad___(49, 7) == DFA_ad50H); static_assert(_DFA_ad___(49, 8) == DFA_ad50T);
static_assert(_DFA_ad___(50, 0) == DFA_ad51A); static_assert(_DFA_ad___(50, 1) == DFA_ad51B); static_assert(_DFA_ad___(50, 2) == DFA_ad51C); static_assert(_DFA_ad___(50, 3) == DFA_ad51D); static_assert(_DFA_ad___(50, 4) == DFA_ad51E); static_assert(_DFA_ad___(50, 5) == DFA_ad51F); static_assert(_DFA_ad___(50, 6) == DFA_ad51G); static_assert(_DFA_ad___(50, 7) == DFA_ad51H); static_assert(_DFA_ad___(50, 8) == DFA_ad51T);
static_assert(_DFA_ad___(51, 0) == DFA_ad52A); static_assert(_DFA_ad___(51, 1) == DFA_ad52B); static_assert(_DFA_ad___(51, 2) == DFA_ad52C); static_assert(_DFA_ad___(51, 3) == DFA_ad52D); static_assert(_DFA_ad___(51, 4) == DFA_ad52E); static_assert(_DFA_ad___(51, 5) == DFA_ad52F); static_assert(_DFA_ad___(51, 6) == DFA_ad52G); static_assert(_DFA_ad___(51, 7) == DFA_ad52H); static_assert(_DFA_ad___(51, 8) == DFA_ad52T);
static_assert(_DFA_ad___(52, 0) == DFA_ad53A); static_assert(_DFA_ad___(52, 1) == DFA_ad53B); static_assert(_DFA_ad___(52, 2) == DFA_ad53C); static_assert(_DFA_ad___(52, 3) == DFA_ad53D); static_assert(_DFA_ad___(52, 4) == DFA_ad53E); static_assert(_DFA_ad___(52, 5) == DFA_ad53F); static_assert(_DFA_ad___(52, 6) == DFA_ad53G); static_assert(_DFA_ad___(52, 7) == DFA_ad53H); static_assert(_DFA_ad___(52, 8) == DFA_ad53T);
static_assert(_DFA_ad___(53, 0) == DFA_ad54A); static_assert(_DFA_ad___(53, 1) == DFA_ad54B); static_assert(_DFA_ad___(53, 2) == DFA_ad54C); static_assert(_DFA_ad___(53, 3) == DFA_ad54D); static_assert(_DFA_ad___(53, 4) == DFA_ad54E); static_assert(_DFA_ad___(53, 5) == DFA_ad54F); static_assert(_DFA_ad___(53, 6) == DFA_ad54G); static_assert(_DFA_ad___(53, 7) == DFA_ad54H); static_assert(_DFA_ad___(53, 8) == DFA_ad54T);
static_assert(_DFA_ad___(54, 0) == DFA_ad55A); static_assert(_DFA_ad___(54, 1) == DFA_ad55B); static_assert(_DFA_ad___(54, 2) == DFA_ad55C); static_assert(_DFA_ad___(54, 3) == DFA_ad55D); static_assert(_DFA_ad___(54, 4) == DFA_ad55E); static_assert(_DFA_ad___(54, 5) == DFA_ad55F); static_assert(_DFA_ad___(54, 6) == DFA_ad55G); static_assert(_DFA_ad___(54, 7) == DFA_ad55H); static_assert(_DFA_ad___(54, 8) == DFA_ad55T);
static_assert(_DFA_ad___(55, 0) == DFA_ad56A); static_assert(_DFA_ad___(55, 1) == DFA_ad56B); static_assert(_DFA_ad___(55, 2) == DFA_ad56C); static_assert(_DFA_ad___(55, 3) == DFA_ad56D); static_assert(_DFA_ad___(55, 4) == DFA_ad56E); static_assert(_DFA_ad___(55, 5) == DFA_ad56F); static_assert(_DFA_ad___(55, 6) == DFA_ad56G); static_assert(_DFA_ad___(55, 7) == DFA_ad56H); static_assert(_DFA_ad___(55, 8) == DFA_ad56T);
static_assert(_DFA_ad___(56, 0) == DFA_ad57A); static_assert(_DFA_ad___(56, 1) == DFA_ad57B); static_assert(_DFA_ad___(56, 2) == DFA_ad57C); static_assert(_DFA_ad___(56, 3) == DFA_ad57D); static_assert(_DFA_ad___(56, 4) == DFA_ad57E); static_assert(_DFA_ad___(56, 5) == DFA_ad57F); static_assert(_DFA_ad___(56, 6) == DFA_ad57G); static_assert(_DFA_ad___(56, 7) == DFA_ad57H); static_assert(_DFA_ad___(56, 8) == DFA_ad57T);
static_assert(_DFA_ad___(57, 0) == DFA_ad58A); static_assert(_DFA_ad___(57, 1) == DFA_ad58B); static_assert(_DFA_ad___(57, 2) == DFA_ad58C); static_assert(_DFA_ad___(57, 3) == DFA_ad58D); static_assert(_DFA_ad___(57, 4) == DFA_ad58E); static_assert(_DFA_ad___(57, 5) == DFA_ad58F); static_assert(_DFA_ad___(57, 6) == DFA_ad58G); static_assert(_DFA_ad___(57, 7) == DFA_ad58H); static_assert(_DFA_ad___(57, 8) == DFA_ad58T);
static_assert(_DFA_ad___(58, 0) == DFA_ad59A); static_assert(_DFA_ad___(58, 1) == DFA_ad59B); static_assert(_DFA_ad___(58, 2) == DFA_ad59C); static_assert(_DFA_ad___(58, 3) == DFA_ad59D); static_assert(_DFA_ad___(58, 4) == DFA_ad59E); static_assert(_DFA_ad___(58, 5) == DFA_ad59F); static_assert(_DFA_ad___(58, 6) == DFA_ad59G); static_assert(_DFA_ad___(58, 7) == DFA_ad59H); static_assert(_DFA_ad___(58, 8) == DFA_ad59T);
static_assert(_DFA_ad___(59, 0) == DFA_ad60A); static_assert(_DFA_ad___(59, 1) == DFA_ad60B); static_assert(_DFA_ad___(59, 2) == DFA_ad60C); static_assert(_DFA_ad___(59, 3) == DFA_ad60D); static_assert(_DFA_ad___(59, 4) == DFA_ad60E); static_assert(_DFA_ad___(59, 5) == DFA_ad60F); static_assert(_DFA_ad___(59, 6) == DFA_ad60G); static_assert(_DFA_ad___(59, 7) == DFA_ad60H); static_assert(_DFA_ad___(59, 8) == DFA_ad60T);
static_assert(_DFA_ad___(60, 0) == DFA_ad61A); static_assert(_DFA_ad___(60, 1) == DFA_ad61B); static_assert(_DFA_ad___(60, 2) == DFA_ad61C); static_assert(_DFA_ad___(60, 3) == DFA_ad61D); static_assert(_DFA_ad___(60, 4) == DFA_ad61E); static_assert(_DFA_ad___(60, 5) == DFA_ad61F); static_assert(_DFA_ad___(60, 6) == DFA_ad61G); static_assert(_DFA_ad___(60, 7) == DFA_ad61H); static_assert(_DFA_ad___(60, 8) == DFA_ad61T);
static_assert(_DFA_ad___(61, 0) == DFA_ad62A); static_assert(_DFA_ad___(61, 1) == DFA_ad62B); static_assert(_DFA_ad___(61, 2) == DFA_ad62C); static_assert(_DFA_ad___(61, 3) == DFA_ad62D); static_assert(_DFA_ad___(61, 4) == DFA_ad62E); static_assert(_DFA_ad___(61, 5) == DFA_ad62F); static_assert(_DFA_ad___(61, 6) == DFA_ad62G); static_assert(_DFA_ad___(61, 7) == DFA_ad62H); static_assert(_DFA_ad___(61, 8) == DFA_ad62T);
static_assert(_DFA_ad___(62, 0) == DFA_ad63A); static_assert(_DFA_ad___(62, 1) == DFA_ad63B); static_assert(_DFA_ad___(62, 2) == DFA_ad63C); static_assert(_DFA_ad___(62, 3) == DFA_ad63D); static_assert(_DFA_ad___(62, 4) == DFA_ad63E); static_assert(_DFA_ad___(62, 5) == DFA_ad63F); static_assert(_DFA_ad___(62, 6) == DFA_ad63G); static_assert(_DFA_ad___(62, 7) == DFA_ad63H); static_assert(_DFA_ad___(62, 8) == DFA_ad63T);
static_assert(_DFA_ad___(63, 0) == DFA_ad64A); static_assert(_DFA_ad___(63, 1) == DFA_ad64B); static_assert(_DFA_ad___(63, 2) == DFA_ad64C); static_assert(_DFA_ad___(63, 3) == DFA_ad64D); static_assert(_DFA_ad___(63, 4) == DFA_ad64E); static_assert(_DFA_ad___(63, 5) == DFA_ad64F); static_assert(_DFA_ad___(63, 6) == DFA_ad64G); static_assert(_DFA_ad___(63, 7) == DFA_ad64H); static_assert(_DFA_ad___(63, 8) == DFA_ad64T);
#endif
//                                              knx.paramByte(DFA_ParamCalcIndex(_DFA_ad___(_state, input)))
#define _ParamDFA_ad___(STATE_IDX, SYMBOL_IDX) (knx.paramByte(DFA_ParamCalcIndex(_DFA_ad___(STATE_IDX, SYMBOL_IDX))))

// Define (relative) parameter address-index for timeout duration and timeout state
#define _DFA_ad___TTime(IDX) (DFA_ad01TTime + IDX * (DFA_ad02TTime - DFA_ad01TTime))
static_assert(_DFA_ad___TTime( 0) == DFA_ad01TTime);
static_assert(_DFA_ad___TTime( 1) == DFA_ad02TTime);
static_assert(_DFA_ad___TTime( 2) == DFA_ad03TTime);
static_assert(_DFA_ad___TTime( 3) == DFA_ad04TTime);
static_assert(_DFA_ad___TTime( 4) == DFA_ad05TTime);
static_assert(_DFA_ad___TTime( 5) == DFA_ad06TTime);
static_assert(_DFA_ad___TTime( 6) == DFA_ad07TTime);
static_assert(_DFA_ad___TTime( 7) == DFA_ad08TTime);
static_assert(_DFA_ad___TTime( 8) == DFA_ad09TTime);
static_assert(_DFA_ad___TTime( 9) == DFA_ad10TTime);
static_assert(_DFA_ad___TTime(10) == DFA_ad11TTime);
static_assert(_DFA_ad___TTime(11) == DFA_ad12TTime);
static_assert(_DFA_ad___TTime(12) == DFA_ad13TTime);
static_assert(_DFA_ad___TTime(13) == DFA_ad14TTime);
static_assert(_DFA_ad___TTime(14) == DFA_ad15TTime);
static_assert(_DFA_ad___TTime(15) == DFA_ad16TTime);
#if DFA_DEF_STATES_COUNT > 16
static_assert(_DFA_ad___TTime(16) == DFA_ad17TTime);
static_assert(_DFA_ad___TTime(17) == DFA_ad18TTime);
static_assert(_DFA_ad___TTime(18) == DFA_ad19TTime);
static_assert(_DFA_ad___TTime(19) == DFA_ad20TTime);
static_assert(_DFA_ad___TTime(20) == DFA_ad21TTime);
static_assert(_DFA_ad___TTime(21) == DFA_ad22TTime);
static_assert(_DFA_ad___TTime(22) == DFA_ad23TTime);
static_assert(_DFA_ad___TTime(23) == DFA_ad24TTime);
static_assert(_DFA_ad___TTime(24) == DFA_ad25TTime);
static_assert(_DFA_ad___TTime(25) == DFA_ad26TTime);
static_assert(_DFA_ad___TTime(26) == DFA_ad27TTime);
static_assert(_DFA_ad___TTime(27) == DFA_ad28TTime);
static_assert(_DFA_ad___TTime(28) == DFA_ad29TTime);
static_assert(_DFA_ad___TTime(29) == DFA_ad30TTime);
static_assert(_DFA_ad___TTime(30) == DFA_ad31TTime);
static_assert(_DFA_ad___TTime(31) == DFA_ad32TTime);
#endif
#if DFA_DEF_STATES_COUNT > 32
static_assert(_DFA_ad___TTime(32) == DFA_ad33TTime);
static_assert(_DFA_ad___TTime(33) == DFA_ad34TTime);
static_assert(_DFA_ad___TTime(34) == DFA_ad35TTime);
static_assert(_DFA_ad___TTime(35) == DFA_ad36TTime);
static_assert(_DFA_ad___TTime(36) == DFA_ad37TTime);
static_assert(_DFA_ad___TTime(37) == DFA_ad38TTime);
static_assert(_DFA_ad___TTime(38) == DFA_ad39TTime);
static_assert(_DFA_ad___TTime(39) == DFA_ad40TTime);
static_assert(_DFA_ad___TTime(40) == DFA_ad41TTime);
static_assert(_DFA_ad___TTime(41) == DFA_ad42TTime);
static_assert(_DFA_ad___TTime(42) == DFA_ad43TTime);
static_assert(_DFA_ad___TTime(43) == DFA_ad44TTime);
static_assert(_DFA_ad___TTime(44) == DFA_ad45TTime);
static_assert(_DFA_ad___TTime(45) == DFA_ad46TTime);
static_assert(_DFA_ad___TTime(46) == DFA_ad47TTime);
static_assert(_DFA_ad___TTime(47) == DFA_ad48TTime);
static_assert(_DFA_ad___TTime(48) == DFA_ad49TTime);
static_assert(_DFA_ad___TTime(49) == DFA_ad50TTime);
static_assert(_DFA_ad___TTime(50) == DFA_ad51TTime);
static_assert(_DFA_ad___TTime(51) == DFA_ad52TTime);
static_assert(_DFA_ad___TTime(52) == DFA_ad53TTime);
static_assert(_DFA_ad___TTime(53) == DFA_ad54TTime);
static_assert(_DFA_ad___TTime(54) == DFA_ad55TTime);
static_assert(_DFA_ad___TTime(55) == DFA_ad56TTime);
static_assert(_DFA_ad___TTime(56) == DFA_ad57TTime);
static_assert(_DFA_ad___TTime(57) == DFA_ad58TTime);
static_assert(_DFA_ad___TTime(58) == DFA_ad59TTime);
static_assert(_DFA_ad___TTime(59) == DFA_ad60TTime);
static_assert(_DFA_ad___TTime(60) == DFA_ad61TTime);
static_assert(_DFA_ad___TTime(61) == DFA_ad62TTime);
static_assert(_DFA_ad___TTime(62) == DFA_ad63TTime);
static_assert(_DFA_ad___TTime(63) == DFA_ad64TTime);
#endif
#define _ParamDFA_ad___TTimeMS(IDX) (paramDelay(knx.paramWord(DFA_ParamCalcIndex(_DFA_ad___TTime(IDX)))))

#pragma endregion "DFA_CHANNEL_ADDR"

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
    // TODO ensure returning 0 for undefined timeout state
    return _ParamDFA_ad___TTimeMS(state);
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
#endif

#pragma endregion "DFA_CHANNEL_COMMANDS"

void DfaChannel::addHistory(uint8_t input, uint8_t state)
{
    _history.addHistory(input, state);
    logDebugP("addHistory(input=int:%u, state=int:%u) [DONE]", input, state);
    logHexDebugP(_history.getHistoryBuffer(), _history.getHistoryBufferSize());
}
