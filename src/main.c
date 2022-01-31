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
///  @file  main.c
///
///  @brief  Provides the entry point for the optophaser app
///
///  @author  Tim Rheinfels
///
///  @date  2022-01-22
///

#include <hal.h>

#include <cfg/phaser.h>
#include <drivers/adc.h>
#include <drivers/led.h>
#include <drivers/timer.h>
#include <synthesizer.h>

///
///  @brief  Callback updating the LED by sampling the LFO synthesizer
///
static void callback(void)
{
    static uint16_t phase = 0u;

    uint16_t freq = adc_get_value(ADC_DEVICE_FREQ);
    uint16_t wvf = adc_get_value(ADC_DEVICE_WVF);

    phase += (freq >> 8u) + 1u;

    led_set_value( synthesizer_get_sample(phase, wvf) );
}

///
///  @brief  Program entry point
///
///  @returns  Does not return
///
int main(void)
{
    // Initialize hardware
    halInit();

    // Initialize drivers
    adc_init();
    led_init();
    timer_init();

    // Enable interrupts
    osalSysEnable();
    timer_start(&callback);

    // Sleep inbetween interrupts
    SCB->SCR |= SCB_SCR_SLEEPONEXIT;
    __WFI();

    // Should never be reached
    while (true);
}
