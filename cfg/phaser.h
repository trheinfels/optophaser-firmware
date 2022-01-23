///
///  @file  cfg/phaser.h
///
///  @brief  Provides the phaser configuration
///
///  @author  Tim Rheinfels
///
///  @date  2022-01-22
///

#ifndef CFG_PHASER_H
#define CFG_PHASER_H

///
///  @brief  GPTDriver instance used
///
#define PHASER_TIMER_DRIVER  GPTD2

///
///  @brief  Phaser base frequency
///
#define PHASER_BASE_FREQUENCY  10000u

///
///  @brief  Wvf potentiometer connected instead of rotary encoder
///
#define PHASER_HAS_WVF  1

///
///  @brief  ADCDriver instance used
///
#define PHASER_ADC_DRIVER  ADCD1

///
///  @brief  ADC Channel to which the control voltage / expression pedal is connected to
///
#define PHASER_CV_ADC_CHANNEL  ADC_CHANNEL_IN5

///
///  @brief  ADC Channel to which the Freq potentiometer is connected to
///
#define PHASER_FREQ_ADC_CHANNEL  ADC_CHANNEL_IN6

#if PHASER_HAS_WVF
///
///  @brief  ADC Channel to which the Wvf potentiometer is connected to
///
#define PHASER_WVF_ADC_CHANNEL  ADC_CHANNEL_IN7
#endif

///
///  @brief  DACDriver instance used
///
#define PHASER_DAC_DRIVER  DACD1

#endif // CFG_PHASER_H
