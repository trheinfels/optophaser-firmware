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
///  @file  synthesizer.h
///
///  @brief  Provides the the synthesizer shim layer
///
///  @author  Tim Rheinfels
///
///  @date  2022-01-23
///

#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <stdint.h>

#include <cfg/phaser.h>

#if PHASER_SYNTHESIZER_USE_WAVETABLE

#include <synthesizer/wavetable.h>

///
///  @brief  Returns the sample value associated with the given @p phase and @p mix
///
///  @param[in]  phase  Phase to sample the wavetables at
///  @param[in]  mix    Mix blending the wavetables
///
///  @returns  Sample for the given @p phase and @p mix
///
#define synthesizer_get_sample(phase, mix) wavetable_get_sample(phase, mix)

#else
#error "Only wavetable symthesizer implemented yet"
#endif

#endif // SYNTHESIZER_H
