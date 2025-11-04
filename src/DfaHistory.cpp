// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2025 Cornelius Koepp

#include "DfaHistory.h"

void DfaHistory::addHistory(uint8_t input, uint8_t state)
{
    _historyIndex = (_historyIndex + 1) % sizeof(_history);
    _history[_historyIndex] = input;
    _historyIndex = (_historyIndex + 1) % sizeof(_history);
    _history[_historyIndex] = state;
}

std::string DfaHistory::getCompactHistoryString() const
{
    char result[DFA_HISTORY_MAX_LENGTH + 1] = {0}; // +1 for null terminator

    // Format:  12345678901234
    // Example: 01B02C03D04ASS
    // Step:    22222222222211

    const uint8_t currentState = _history[_historyIndex];

    // 1. Set last 2 characters to current state (1-based)
    const uint8_t displayState = (currentState == DFA_STATE_UNDEFINED) ? 0 : currentState + 1;
    result[12 + 0] = '0' + (displayState / 10);
    result[12 + 1] = '0' + (displayState % 10);

    // 2. Fill 12 bytes from right to left
    uint8_t resultingState = currentState;
    for (uint8_t back = 1; back <= 4; back++)
    {
        const uint8_t originState = _history[(_historyIndex - back * 2 + 0 + DFA_HISTORY_MAX_LENGTH) % DFA_HISTORY_MAX_LENGTH];
        const uint8_t input = _history[(_historyIndex - back * 2 + 1 + DFA_HISTORY_MAX_LENGTH) % DFA_HISTORY_MAX_LENGTH];

        if (originState == DFA_HISTORY_INIT_VALUE || input == DFA_HISTORY_INIT_VALUE) // no more valid history
            break;

        char symbol;
        if (input == DFA_INPUT_SYMBOL_T) // timeout symbol
        {
            symbol = 'T';
        }
        else if (input < DFA_DEF_INPUTS_COUNT) // regular input symbols A-H (0-7)
        {
            symbol = 'A' + input;
        }
        else if (input == 9) // symbol '<'
        {
            symbol = '<';
        }
        else if ((input & 0x80) && (input & 0x7F) < 64) // direct state calls (0x80 | 0..63) // TODO use check-function
        {
            const uint8_t targetState = input & 0x7F;
            const bool success = (targetState == resultingState);
            symbol = success ? '=' : '#';
        }
        else if ((input & 0x80) && (input & 0x7F) >= 64 && (input & 0x7F) < 64 + 16) // conditional states a-p (0x80 | 64..79)
        {
            uint8_t choiceState = (input & 0x7F) - 64;
            symbol = 'a' + choiceState;
        }
        else if (input == DFA_INPUT_SYMBOL_START)
        {
            symbol = '*';
        }
        else // unknown symbol
        {
            symbol = '?';
        }

        const uint8_t displayState = (originState == DFA_STATE_UNDEFINED) ? 0 : originState + 1;
        result[12 - back * 3 + 0] = '0' + (displayState / 10);
        result[12 - back * 3 + 1] = '0' + (displayState % 10);
        result[12 - back * 3 + 2] = symbol;

        // Process the input-state pair
        resultingState = originState;
    }

    // Return substring starting from first non-zero character
    for (int i = 0; i < DFA_HISTORY_MAX_LENGTH; i++)
    {
        if (result[i] != 0) // found start of string
            return std::string(&result[i]);
    }
    // Fallback: just return current state
    return std::string(&result[12]);
}