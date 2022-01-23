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
///  @file  drivers/dac.h
///
///  @brief  Provides the interface for the DAC driver
///
///  @author  Tim Rheinfels
///
///  @date  2022-01-23
///

#ifndef DRIVERS_DAC_H
#define DRIVERS_DAC_H

#include <stdint.h>

#include <cfg/phaser.h>

///
///  @brief  Initializes the DAC driver
///
void dac_init(void);

///
///  @brief  Sets the DAC output to @p value
///
///  @param[in]  value  Value to output
///
void dac_set_value(uint16_t value);

#endif // DRIVERS_ADC_H
