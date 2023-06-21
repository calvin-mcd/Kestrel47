/*
Copyright 2018-2021 <Pierre Constantineau>

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

#ifndef FIRMWARE_CONFIG_H
#define FIRMWARE_CONFIG_H
#include "hardware_variants.h"
#include "keyboard_config.h"
#include "datastructures.h"

// THIS FILE USES THE USER KEYBOARD DEFINITION FILES TO CONFIGURE THE REST OF THE OPTIONS
// NOTE THAT OPTIONS NOT DEFINED BY THE USER WILL BE SET TO THEIR DEFAULTS IN THIS FILE

#define MATRIX_SCAN 1
#define SEND_KEYS 1

#if KEYBOARD_SIDE == LEFT
#define BLE_HID 1
#define BLE_CENTRAL 1
#define CENTRAL_COUNT 1
#define PERIPHERAL_COUNT 1 //1  
#define BLE_PERIPHERAL 0
#define DEVICE_NAME DEVICE_NAME_L // override name
#elif KEYBOARD_SIDE == RIGHT
#define BLE_HID 0
#define BLE_CENTRAL 0
#define CENTRAL_COUNT 0
#define PERIPHERAL_COUNT 1 //1  
#define BLE_PERIPHERAL 1
#define DEVICE_NAME DEVICE_NAME_R // override name
#elif KEYBOARD_SIDE == SINGLE
#define BLE_HID 1
#define BLE_CENTRAL 0
#define CENTRAL_COUNT 0
#define PERIPHERAL_COUNT 1 //1  
#define BLE_PERIPHERAL 0
#ifndef DEVICE_NAME 
#define DEVICE_NAME DEVICE_NAME_M
#endif
#elif KEYBOARD_SIDE == TEST
#define BLE_CENTRAL 0  /// 
#define BLE_PERIPHERAL 0 /// 
#define BLE_PAIRS 0  /// NOT SURE WHAT THIS ACTIVATES
#define BLE_HID 1 //1 //  
#define PERIPHERAL_COUNT 1 //1  
#define CENTRAL_COUNT 0
#ifndef DEVICE_NAME 
#define DEVICE_NAME DEVICE_NAME_M
#endif
#endif


#ifndef DEBOUNCETIME 
#define DEBOUNCETIME 3   // changing this to 1 and you will have problems with the debounce logic - repeated keys perhaps...
#endif

#ifndef HIDREPORTINGINTERVAL
#define HIDREPORTINGINTERVAL 8
#endif
#ifndef LOWPRIORITYLOOPINTERVAL
#define LOWPRIORITYLOOPINTERVAL 128
#endif


// Battery Service definitions.

#ifndef BATTERY_TYPE
#define BATTERY_TYPE BATT_UNKNOWN
#endif

#ifndef VBAT_PIN
#define VBAT_PIN  31       // make sure we have a default analog pin to do something with...
#endif

#ifndef BATTERYINTERVAL
#define BATTERYINTERVAL 30000
#endif

#define SLEEPING_DELAY 30000              // when it's not connected, 30 seconds is good.
#define SLEEPING_DELAY_CONNECTED 600000   // 2 minutes is way too fast and really ennoying. making it 10 minutes
#define SLEEP_ACTIVE 1                    // 1 = it will go to sleep. 0 = sleep will not be activated.

#ifndef DEFAULT_PWM_MAX_VALUE 
#define DEFAULT_PWM_MAX_VALUE 0x7FFF      // PWM max intensity
#endif

#ifndef DEFAULT_PWM_VALUE 
#define DEFAULT_PWM_VALUE 0x7FFF          // PWM default intensity
#endif

#ifndef BACKLIGHT_LED_PIN
  #define BACKLIGHT_LED_PIN 0 
  #ifndef BACKLIGHT_PWM_ON
   #define BACKLIGHT_PWM_ON 0          
  #endif  
#else
  #ifndef BACKLIGHT_PWM_ON
  #define BACKLIGHT_PWM_ON 1          
  #endif      
#endif

#ifndef WS2812B_LED_PIN
  #define WS2812B_LED_PIN 0 
  #ifndef WS2812B_LED_COUNT
    #define WS2812B_LED_COUNT 0          
  #endif
  #ifndef WS2812B_LED_ON
    #define WS2812B_LED_ON 0          
  #endif        
#endif

  #ifndef WS2812B_LED_ON  // it would have been created if a LED_PIN did not exist
  #define WS2812B_LED_ON 1          
  #endif 

  #ifndef WS2812B_LED_COUNT  // it would have been created if a LED_PIN did not exist
  #define WS2812B_LED_COUNT 1          
  #endif


#ifndef STATUS_BLE_LED_PIN                // setup default value if not set
  #define STATUS_BLE_LED_PIN LED_BLUE 
  #ifndef BLE_LED_ACTIVE                    // setup default value if not set
    #define BLE_LED_ACTIVE 0     
  #endif 
  #ifndef BLE_LED_POLARITY                    // setup default value if not set
    #define BLE_LED_POLARITY 1     
  #endif 
#else
  #ifndef BLE_LED_ACTIVE                    // setup default value if not set
    #define BLE_LED_ACTIVE 1     
  #endif
  #ifndef BLE_LED_POLARITY                    // setup default value if not set
    #define BLE_LED_POLARITY 1     
  #endif 
#endif

#ifndef STATUS_KB_LED_PIN                 // setup default value if not set
  #define STATUS_KB_LED_PIN LED_RED 
  #ifndef STATUS_KB_LED_ACTIVE                   // setup default value if not set
    #define STATUS_KB_LED_ACTIVE 0       
  #endif
  #ifndef STATUS_KB_LED_POLARITY                    // setup default value if not set
    #define STATUS_KB_LED_POLARITY 1     
  #endif 
#else
  #ifndef STATUS_KB_LED_ACTIVE                   // setup default value if not set
    #define STATUS_KB_LED_ACTIVE 1       
  #endif 
  #ifndef STATUS_KB_LED_POLARITY                    // setup default value if not set
    #define STATUS_KB_LED_POLARITY 1     
  #endif       
#endif

#define PWM_TOUCH_INTERVAL 1000           // detection time since last keypress.
#ifndef VBAT_PIN
   #define VBAT_PIN          (A7)
#endif

#define VBAT_MV_PER_LSB   (0.73242188F)   // 3.0V ADC range and 12-bit ADC resolution = 3000mV/4096
#ifdef ARDUINO_NRF52840_FEATHER           // these settings are specific to the NRF52840_FEATHER not the NRF52840 Chip.
  #define VBAT_DIVIDER      (0.5F)          // 150K + 150K voltage divider on VBAT
  #define VBAT_DIVIDER_COMP (2.0F)          // Compensation factor for the VBAT divider
#else
  #define VBAT_DIVIDER      (0.71275837F)   // 2M + 0.806M voltage divider on VBAT = (2M / (0.806M + 2M))
  #define VBAT_DIVIDER_COMP (1.403F)        // Compensation factor for the VBAT divider
#endif

#define VDDHDIV5DIV2SCALE (6000)
#define VDDHDIV5DIV2RANGE (1023)

#ifdef VCC_PIN
  #define VCC_ENABLE_GPIO 1
    #ifndef VCC_POLARITY_ON
      #define VCC_POLARITY_ON 1
    #endif
    #ifndef VCC_DEFAULT_ON
      #define VCC_DEFAULT_ON 1
    #endif
  #else
  #define VCC_ENABLE_GPIO 0
#endif

#ifndef VCC_DEFAULT_ON
  #define VCC_DEFAULT_ON 0
#endif

 

#ifdef CHARGER_PIN
  #define VCC_ENABLE_CHARGER 1
    #ifndef CHARGER_POLARITY_ON
      #define CHARGER_POLARITY_ON 1
    #endif
  #else
  #define VCC_ENABLE_CHARGER 0
#endif

#ifndef SERIAL_DEBUG_CLI_DEFAULT_ON
  #define SERIAL_DEBUG_CLI_DEFAULT_ON 1
#endif

// OLED DISPLAY CONFIG
#ifdef ARDUINO_NRF52_ADAFRUIT
            // do nothing since the Adafruit BSP doesn't have U8g2lib included
#endif
#ifdef ARDUINO_NRF52_COMMUNITY
    #ifdef DISPLAY_U8G2_CONSTRUCTOR
        #ifdef I2C_SDA_PIN
            #ifdef I2C_SCK_PIN   // everything needed is defined!
                #define BLUEMICRO_CONFIGURED_DISPLAY 1
                #ifndef DISPLAY_U8G2_ROTATION  // check for overriding default rotation
                    #define DISPLAY_U8G2_ROTATION U8G2_R1 // options are here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#rotation
                #endif               
            #endif
        #endif
    #endif
#endif

#endif /* FIRMWARE_CONFIG_H */
