// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2026 Cornelius Koepp

#pragma once

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