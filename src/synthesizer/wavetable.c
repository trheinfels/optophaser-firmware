// This file is part of the optophaser firmware.
// Copyright (C) 2021-2023  Tim Rheinfels  <13381391+trheinfels@users.noreply.github.com>
// See https://github.com/trheinfels/optophaser-firmware
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

///
///  @file  synthesizer/wavetable.c
///
///  @brief  Provides the implementation the wavetable synthesizer
///
///  @author  Tim Rheinfels
///
///  @date  2022-01-23
///

#include "wavetable.h"

#include <stddef.h>


// ===== Local =====

#define WAVETABLE_COUNT_BITS   2u                       ///<  Bit count for the wavetable count
#define WAVETABLE_COUNT (1u << WAVETABLE_COUNT_BITS)    ///<  Number of wavetables
#define WAVETABLE_LENGTH_BITS  10u                      ///<  Bit count for the wavetable length
#define WAVETABLE_LENGTH (1u << WAVETABLE_LENGTH_BITS)  ///<  Number of entries in a wavetable

///
///  @brief  Wavetable data
///
static uint16_t wavetables[WAVETABLE_COUNT][WAVETABLE_LENGTH] =
{
    // Hacky but works well...
    {
        #include "wavetables/sine.csv"
    },
    {
        #include "wavetables/square.csv"
    },
    {
        #include "wavetables/triangle.csv"
    },
    {
        #include "wavetables/sawtooth.csv"
    },
};

///
///  @brief  Linear interpolates between @p a and @p b given a @p numerator and @p denominator
///
///  @param[in]  a            First value
///  @param[in]  b            Second value
///  @param[in]  numerator    Fraction numerator
///  @param[in]  denominator  Fraction denominator
///
///  @returns  Linear interpolant between @p a and @p b evaluated at the ratio @p numerator / @p denominator
///
static inline uint16_t lerp(uint16_t a, uint16_t b, uint16_t numerator, uint16_t denominator)
{
    return ((denominator - numerator) * (uint32_t) a + numerator * (uint32_t) b) / denominator;
}

// ===== Global =====
uint16_t wavetable_get_sample(uint16_t phase, uint16_t mix)
{
    // Get wavetable indices and fractional part
    size_t wt_idx_a = mix >> (16u - WAVETABLE_COUNT_BITS);
    size_t wt_idx_b = (wt_idx_a + 1u) % WAVETABLE_COUNT;
    uint16_t wt_frac = mix % ((1u << (16u - WAVETABLE_COUNT_BITS)) - 1u);

    // Get sample indices and fractional part
    size_t sam_idx_1 = phase >> (16u - WAVETABLE_LENGTH_BITS);
    size_t sam_idx_2 = (sam_idx_1 + 1u) % WAVETABLE_LENGTH;
    uint16_t sam_frac = phase % ((1u << (16u - WAVETABLE_LENGTH_BITS)) - 1u);

    // Get values from wavetables
    uint16_t sample_a1 = wavetables[wt_idx_a][sam_idx_1];
    uint16_t sample_a2 = wavetables[wt_idx_a][sam_idx_2];
    uint16_t sample_b1 = wavetables[wt_idx_b][sam_idx_1];
    uint16_t sample_b2 = wavetables[wt_idx_b][sam_idx_2];

    // Compute and return sample as bilinear interpolant
    uint16_t sample_a = lerp(sample_a1, sample_a2, sam_frac, ((1u << (16u - WAVETABLE_COUNT_BITS)) - 1u));
    uint16_t sample_b = lerp(sample_b1, sample_b2, sam_frac, ((1u << (16u - WAVETABLE_LENGTH_BITS)) - 1u));
    return lerp(sample_a, sample_b, wt_frac, ((1u << (16u - WAVETABLE_COUNT_BITS)) - 1u));

}
