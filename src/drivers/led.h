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
///  @file  drivers/led.h
///
///  @brief  Provides a shim layer for accessing the LED
///
///  @author  Tim Rheinfels
///
///  @date  2022-01-23
///

#ifndef DRIVERS_LED_H
#define DRIVERS_LED_H

#include <stdint.h>

#include <cfg/phaser.h>

#if PHASER_LED_USE_DAC

#include <drivers/dac.h>

///
///  @brief  Initializes the led driver
///
#define led_init() dac_init()

///
///  @brief  Sets the LED brightness value to @p value
///
///  @param[in]  value  Value to output
///
#define led_set_value(x) dac_set_value(x)

#else
#error "LED via PWM not yet implemented"
#endif

#endif // DRIVERS_ADC_H
