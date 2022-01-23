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
///  @file  drivers/adc.h
///
///  @brief  Provides the interface for the ADC driver
///
///  @author  Tim Rheinfels
///
///  @date  2022-01-23
///

#ifndef DRIVERS_ADC_H
#define DRIVERS_ADC_H

#include <stdint.h>

#include <cfg/phaser.h>

///
///  @brief  Enumeration of the devices connected to the ADC
///
typedef enum
{
    ADC_DEVICE_CV,    ///<  Control voltage / expression pedal input
    ADC_DEVICE_FREQ,  ///<  Frequency potentiometer
#if PHASER_HAS_WVF
    ADC_DEVICE_WVF,   ///<  Waveform potentiometer
#endif
} adc_device_t;

///
///  @brief  Initializes the ADC driver
///
void adc_init(void);

///
///  @brief  Queries the current value of @p device
///
///  @param[in]  device  Device to query
///
///  @returns  ADC value for @p device
///
uint16_t adc_get_value(adc_device_t device);

#endif // DRIVERS_ADC_H
