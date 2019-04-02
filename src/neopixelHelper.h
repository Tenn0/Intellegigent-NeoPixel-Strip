#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "settings.h"
#include <Wire.h>
#include <RTClib.h>
 



Adafruit_NeoPixel strip = Adafruit_NeoPixel(numberLED, stripPin, NEO_GRB + NEO_KHZ800);

int setStripBrightness(int color, int dimVal) //Dim color to dimVal in percent
{
  color = color / 100 * dimVal;
  if(color < 0)
  {
    color = 0;
  }
   else if(color > 255)
   {
     color = 255;
   }
  return color;
}

void setStripColor(int redValue, int greenValue, int blueValue)  //Set Color for whole strip
{
   for(int i = 0; i  < numberLED; i++ ){
         strip.setPixelColor(i, redValue,greenValue,blueValue);
         
         
      }
}

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){



  for(int i = 0; i < numberLED-EyeSize-2; i++) {

    setStripColor(0,0,0);

    strip.setPixelColor(i, red/10, green/10, blue/10);

    for(int j = 1; j <= EyeSize; j++) {

      strip.setPixelColor(i+j, red, green, blue); 

    }

    strip.setPixelColor(i+EyeSize+1, red/10, green/10, blue/10);

    strip.show();

    delay(SpeedDelay);

  }



  delay(ReturnDelay);



  for(int i = numberLED-EyeSize-2; i > 0; i--) {

    setStripColor(0,0,0);

    strip.setPixelColor(i, red/10, green/10, blue/10);

    for(int j = 1; j <= EyeSize; j++) {

      strip.setPixelColor(i+j, red, green, blue); 

    }

    strip.setPixelColor(i+EyeSize+1, red/10, green/10, blue/10);

    strip.show();

    delay(SpeedDelay);

  }

  

  delay(ReturnDelay);

}






