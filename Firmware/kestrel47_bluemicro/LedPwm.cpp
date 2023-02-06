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
#include "LedPwm.h"

//extern PersistentState keyboardconfig;
int16_t pwmval = DEFAULT_PWM_VALUE;


uint16_t pwmstepsize = 128;
uint16_t pwmmaxvalue = DEFAULT_PWM_MAX_VALUE;
bool breathingincreasing = true;

uint8_t PWMMode = 1;
/**************************************************************************************************************************/
void setPWMMode(int mode)
{
  PWMMode = mode;
}

void incPWMStepSize(){
if (pwmstepsize < (1024 - pwmstepsize)) {pwmstepsize = pwmstepsize+8 ;} else {pwmstepsize = 1024 ;}

}
void decPWMStepSize(){

if (pwmstepsize > 8) {pwmstepsize = pwmstepsize-8 ;} else {pwmstepsize = 8 ;}
}

void incPWMMaxVal(){
  if (pwmmaxvalue < (DEFAULT_PWM_MAX_VALUE - pwmstepsize*4)) {pwmmaxvalue = pwmmaxvalue+pwmstepsize*4 ;} else {pwmmaxvalue = DEFAULT_PWM_MAX_VALUE ;}
}
void decPWMMaxVal(){
  if (pwmmaxvalue > pwmstepsize*4) {pwmmaxvalue = pwmmaxvalue-pwmstepsize*4 ;} else {pwmmaxvalue = 0 ;}
}
void PWMSetMaxVal()
{
  pwmmaxvalue = DEFAULT_PWM_MAX_VALUE ;
}

void stepPWMMode()
{
  PWMMode++;
  if (PWMMode > 3){PWMMode=0;}
}


/**************************************************************************************************************************/
void updatePWM(unsigned long timesincelastkeypress)
{
updatePWM(PWMMode, timesincelastkeypress);
}
void updatePWM(int mode, unsigned long timesincelastkeypress)
{

  switch (mode)
  {
  case 0: // OFF.
      sendPWM(0);
    break;

  case 1: // Bright when typing, dim when not typing
        if (timesincelastkeypress<PWM_TOUCH_INTERVAL)
        {
            pwmval = pwmmaxvalue;

        }else
        {
          if (pwmval > pwmstepsize) {pwmval = pwmval-pwmstepsize ;} else {pwmval = 0 ;}
        }
          sendPWM(cie_lightness(pwmval));
          if (pwmval<pwmstepsize)
          {
            sendPWM(0);
          }
    break;
        
case 2: // Breathing
        if (breathingincreasing)
        {
            if (pwmval < (pwmmaxvalue - pwmstepsize)) {pwmval = pwmval+pwmstepsize ;} else {pwmval = pwmmaxvalue ; breathingincreasing = false;}

        }else
        {
          if (pwmval > pwmstepsize) {pwmval = pwmval-pwmstepsize ;} else {pwmval = 0 ;breathingincreasing = true;}
        }
          sendPWM(cie_lightness(pwmval));
          if (pwmval<pwmstepsize)
          {
            sendPWM(0);
          }

 break;
    case 3: // on all the time...

          sendPWM(cie_lightness(pwmval));
    break;
  default:
    // unknown mode.  switch to mode 0
    setPWMMode(0);
    break;
  }
}
/**************************************************************************************************************************/
// See http://jared.geek.nz/2013/feb/linear-led-pwm
/*
 CIE Lightness to PWM conversion
 L* = 116(Y/Yn)^1/3 - 16, Y/Yn > 0.008856
L* = 903.3(Y/Yn),         Y/Yn <= 0.008856 // L <= 8
// L  0-100
// Y/Yn = 0-1
// fitted by part to span 0-32767 = 15 bits
*/
uint16_t cie_lightness(uint16_t v) {
  if (v <= 2621) // if below 8% of max 0.08*0x7FFF=2621.26
    return v / 9; // same as dividing by 900%
  else {
    if (v <= 5243)
       return (v*3/20-107);
    else {
      if (v <= 7864)
        return (v/4-623);
            else {
          if (v <= 10485)
          return (v*3/8-1590);
              else {
            if (v <= 13107)
              return (v*26/50-3138);
                  else {
                    if (v <= 16383)
                    return (v*18/25-5708);
                    else {
                     if (v <= 19660)
                    return (v-9864);
                    else {
                        if (v <= 22937)
                        return (v*5/4-15608);
                        else {
                           if (v <= 26214)
                            return (v*8/5-23190);
                            else {
                             if (v <= 30044)
                       return (v*49/25-32864);
                        else {
                        return (v*59/25-44880); 
                    }                             
                  }    
                }                            
              }                      
            }                     
          }       
        } 
      }  
    }
  }
}
