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
///  @file  drivers/timer.c
///
///  @brief  Provides the implementation of the timer driver
///
///  @author  Tim Rheinfels
///
///  @date  2022-01-23
///

#include "timer.h"

#include <stdint.h>
#include <string.h>

#include <hal.h>

#include <cfg/phaser.h>


// ===== Local =====

///
///  @brief  Function called at phaser base frequency
///
timer_callback_t timer_callback = NULL;

///
///  @brief  Base timer callback
///
///  @param[in]  gpt  GPTDriver instance
///
static void gpt_callback(GPTDriver *gpt)
{
    (void) gpt;

    if(timer_callback != NULL)
    {
        timer_callback();
    }
}

///
///  @brief  MMS mask in CR2 used to set trigger signal on update event
///
#define CR2_MMS  (TIM_CR2_MMS_1)

///
///  @brief  Configuration for the base timer
///
static GPTConfig gpt_config =
{
    .frequency = PHASER_BASE_FREQUENCY,
    .callback = &gpt_callback,
    .cr2 = CR2_MMS,
};


// ===== Global =====
void timer_init(void)
{
    gptStart(&PHASER_TIMER_DRIVER, &gpt_config);
}

void timer_start(timer_callback_t callback)
{
    // Check for valid callback
    osalDbgAssert(callback != NULL, "invalid callback");

    // Store callback for later
    timer_callback = callback;

    // Configure timer to run periodically at PHASER_BASE_FREQUENCY
    gptStartContinuous(&PHASER_TIMER_DRIVER, 2u);
}
