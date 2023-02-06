/*
Copyright 2020-2021 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H
#include "hardware_variants.h"

/* HARDWARE DEFINITION*/
/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

/* key matrix pins */
#define MATRIX_ROW_PINS {20, 17, 31, 6}
#define MATRIX_COL_PINS {29, 38, 2, 36, 47, 11, 45, 32, 43, 24, 10, 22, 9}
#define UNUSED_PINS {}

/* RGB */
#define WS2812B_LED_PIN 8
#define WS2812B_LED_COUNT 1
#define WS2812B_LED_ON 1

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* BATTERY */
#define BATTERY_TYPE BATT_VDDH
#define  STATUS_BLE_LED_PIN  15  //blue = 0.15
#define  STATUS_KB_LED_PIN 17  //red = 0.17
#define VCC_PIN 13
#define VCC_POLARITY_ON 0

/*    #define D3      6  //
      #define D2      8   //
      #define D1      17  //sda
      #define D0      20  //scl
      #define D4      22
      #define C6      24
      #define D7      32
      #define E6      11
      #define B4      36
      #define B5      38

      #define F4      31
      #define F5      29
      #define F6      2
      #define F7      47
      #define B1      45  //sck
      #define B3      43  //miso
      #define B2      10  //mosi
      #define B6      9
      #define NC      33 */
    
#endif /* HARDWARE_CONFIG_H */