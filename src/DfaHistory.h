// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2025 Cornelius Koepp

#pragma once
#include "DfaConstants.h"
#include "OpenKNX.h"

// History constants
#define DFA_HISTORY_INIT_VALUE 250
#define DFA_HISTORY_MAX_LENGTH 14

/**
 * @brief History tracking class for DFA (Deterministic Finite Automaton) channels
 *
 * This class maintains a circular buffer of input events and resulting states,
 * providing compact string representation for debugging and diagnostics.
 */
class DfaHistory
{
  private:
    // Ring buffer for storing input-state pairs
    uint8_t _history[DFA_HISTORY_MAX_LENGTH] = {
        DFA_STATE_UNDEFINED,
        DFA_HISTORY_INIT_VALUE,
        DFA_HISTORY_INIT_VALUE,
        DFA_HISTORY_INIT_VALUE,
        DFA_HISTORY_INIT_VALUE,
        DFA_HISTORY_INIT_VALUE,
        DFA_HISTORY_INIT_VALUE,
        DFA_HISTORY_INIT_VALUE,
        DFA_HISTORY_INIT_VALUE,
        DFA_HISTORY_INIT_VALUE,
        DFA_HISTORY_INIT_VALUE,
        DFA_HISTORY_INIT_VALUE,
        DFA_HISTORY_INIT_VALUE,
        DFA_HISTORY_INIT_VALUE,
    };

    // Ring-buffer index for next write position
    uint8_t _historyIndex = 0;

  public:
    /**
     * @brief Add an input-state pair to the history
     * @param input The input symbol that triggered the transition
     * @param state The resulting state after the transition
     */
    void addHistory(uint8_t input, uint8_t state);

    /**
     * @brief Generate compact history string (max 14 chars)
     * @return Compact string representation of the history
     */
    std::string getCompactHistoryString() const;

    /**
     * @brief Get read-only access to history buffer for debugging
     * @return Pointer to the history buffer
     */
    const uint8_t* getHistoryBuffer() const { return _history; }

    /**
     * @brief Get size of history buffer for debugging
     * @return Size of the history buffer
     */
    static constexpr size_t getHistoryBufferSize() { return DFA_HISTORY_MAX_LENGTH; }
};