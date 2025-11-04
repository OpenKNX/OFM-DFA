// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2025 Cornelius Koepp

#pragma once

// TODO check best place to define constants
#define DFA_DEF_STATES_COUNT 16
#define DFA_DEF_CHOICESTATES_COUNT 16
#define DFA_DEF_INPUTS_COUNT 8
#define DFA_DEF_OUTPUTS_COUNT 4
// extension for timeout input symbol T:
#define DFA_DEF_INPUTS_WITH_T_COUNT (DFA_DEF_INPUTS_COUNT + 1)
/*
#define DFA_INPUT_SYMBOL_A 0
#define DFA_INPUT_SYMBOL_B 1
#define DFA_INPUT_SYMBOL_C 2
#define DFA_INPUT_SYMBOL_D 3
#define DFA_INPUT_SYMBOL_E 4
#define DFA_INPUT_SYMBOL_F 5
#define DFA_INPUT_SYMBOL_G 6
#define DFA_INPUT_SYMBOL_H 7
*/
// TODO ensure `(DFA_DEF_INPUTS_COUNT==8)`
#define DFA_INPUT_SYMBOL_T 8

// TODO ensure not overlapping
#define DFA_INPUT_SYMBOL_START 249

// TODO check best place to define constants
// ETS-Param 0 =(-1)=> 255
#define DFA_STATE_UNDEFINED 0xff
// ETS-Param 127 =(-1)=> 126
#define DFA_STATE_TIMEOUT_RESET 0x7e
// ETS-Param 126 =(-1)=> 125
#define DFA_STATE_CHOICE_ELSE 0x7d