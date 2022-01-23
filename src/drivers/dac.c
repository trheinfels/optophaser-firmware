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
///  @file  drivers/dac.c
///
///  @brief  Provides the implementation of the DAC driver
///
///  @author  Tim Rheinfels
///
///  @date  2022-01-23
///

#include "dac.h"

#include <stdint.h>
#include <string.h>

#include <hal.h>


// ===== Local =====

///
///  @brief  TSEL1 mask in CR used to trigger on TIM2_TRGO signal
///
#define CR_TSEL  (DAC_CR_TSEL1_2)

///
///  @brief  TEN1 mask in CR used to convert on trigger
///
#define CR_TEN  (DAC_CR_TEN1)

///
///  @brief  DAC configuration
///
static const DACConfig dac_config =
{
    .cr = CR_TSEL | CR_TEN
};


// ===== Global =====
void dac_init(void)
{
    // Check for correct datatype
    osalDbgAssert(sizeof(dacsample_t) == sizeof(uint16_t), "invalid datatype");

    // Start DAC
    dacStart(&PHASER_DAC_DRIVER, &dac_config);
}

void dac_set_value(uint16_t value)
{
    dacPutChannelX(&PHASER_DAC_DRIVER, 0u, value >> 4u);
}
