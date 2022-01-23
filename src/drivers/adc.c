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
///  @file  drivers/adc.c
///
///  @brief  Provides the implementation of the ADC driver
///
///  @author  Tim Rheinfels
///
///  @date  2022-01-23
///

#include "adc.h"

#include <stdint.h>
#include <string.h>

#include <hal.h>


// ===== Local =====
#if PHASER_HAS_WVF
static adcsample_t samples[6u];                      ///<  Double buffered ADC samples
#else
static adcsample_t samples[4u];                      ///<  Double buffered ADC samples
#endif
static adcsample_t volatile *samples_out = samples;  ///<  Output buffer

// Forward declaration
static void adc_callback(ADCDriver *);

///
///  @brief  EXTEN mask in CR2 used to trigger on the rising edge
///
#define CR2_EXTEN  (ADC_CR2_EXTEN_1)

///
///  @brief  EXTSEL mask in CR2 used to trigger on TIM2_TRGO signal
///
#define CR2_EXTSEL (ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_2)

///
///  @brief  ADC conversion group
///
static const ADCConversionGroup adc_conversion_group =
{
    .circular = true,
    .end_cb = &adc_callback,
    .error_cb = NULL,
    .cr2 = ADC_CR2_ALIGN | CR2_EXTEN | CR2_EXTSEL, // Left-aligned, start conversion upon TIM2_TRGO event
#if PHASER_HAS_WVF
    .num_channels = 3u,
    .sqr1 = (2u << 20u), // Channel count
    .sqr5 =   ADC_SQR5_SQ1_N(PHASER_CV_ADC_CHANNEL)
            | ADC_SQR5_SQ2_N(PHASER_FREQ_ADC_CHANNEL)
            | ADC_SQR5_SQ3_N(PHASER_WVF_ADC_CHANNEL),
#else
    .num_channels = 2u,
    .sqr1 = (1u << 20u), // Channel count
    .sqr5 =   ADC_SQR5_SQ1_N(PHASER_CV_ADC_CHANNEL)
            | ADC_SQR5_SQ2_N(PHASER_FREQ_ADC_CHANNEL),
#endif
};

///
///  @brief  ADC conversion callback
///
///  @param[in]  adc  ADCDriver instance
///
static void adc_callback(ADCDriver *adc)
{
    osalSysLockFromISR();
    if(adcIsBufferComplete(adc))
    {
        samples_out = samples + 3u;
    }
    else
    {
        samples_out = samples;
    }
    osalSysUnlockFromISR();
}


// ===== Global =====
void adc_init(void)
{
    // Check for correct datatype
    osalDbgAssert(sizeof(adcsample_t) == sizeof(uint16_t), "invalid datatype");

    // Start ADC and circular conversion
    adcStart(&PHASER_ADC_DRIVER, NULL);
    adcStartConversion(&PHASER_ADC_DRIVER, &adc_conversion_group, samples, 2u);
}

uint16_t adc_get_value(adc_device_t device)
{
    osalDbgAssert(device < sizeof(samples) / (2u * sizeof(samples[0u])), "invalid adc device");
    osalSysLockFromISR();
    uint16_t result = samples_out[device];
    osalSysUnlockFromISR();
    return result;
}
