#include <Adafruit_NeoPixel.h>
#include <string.h>
#include "neopixelHelper.h"
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;



int displayTime = 2; 

String incomming;

long r, g, b;
bool received = false;
bool timeoutTimer = false;
bool longTimeout = false;
bool offtime = false;

//volatile int timeoutTime = 10; //Minutes
volatile int longTimeoutCount = 2; //How many times does the timer runs to be long timeouted?




using namespace std;

  



void setup() {
  // put your setup code here, to run once:
  pinMode(activityInterupt, INPUT_PULLUP);
  pinMode(timerInterupt, INPUT_PULLUP);
 strip.setBrightness(maxBrightness);
 strip.begin();
 strip.show();  //Clear Strip

 Serial.begin(9600);
}

void serialEvent()
{
   
    incomming = Serial.readString();
    if (incomming.startsWith("#"))
    {
       if (incomming.length() == 7 ){ 
         // Get rid of '#' and convert it to integer
         long number = (long) strtol( &incomming[1], NULL, 16);

         // Split them up into r, g, b values
        r = number >> 16;
        g = number >> 8 & 0xFF;
        b = number & 0xFF;
        setStripColor(r,g,b);            //Set Color for whole Strip
        strip.show();
       }
       else if(incomming.length() == 3)
        {
         long number = (long) strtol( &incomming[1], NULL, 16);
         r = setStripBrightness(r, number);
         g = setStripBrightness(g, number);
         b = setStripBrightness(b, number);

         setStripColor(r, g, b);
         strip.show();
        }
         received = true;

      
        Serial.println(incomming);

        incomming = "";
    
    
     }
}
void loop() {      
    int hour = rtc.now().hour();
    int minute = rtc.now().minute();

    Serial.println(rtc.now().hour(), DEC);
    Serial.println(rtc.now().minute(), DEC);
    if(hour == 3)
    {
      Serial.println("blub");
      if(minute > 14)
      {
      Serial.println("blab");
      setStripColor(00,00,00);
      offtime = true;
      
      }
    }

        
    if(received == true)
      {

        delay(100);
   //     received = false;
      setStripColor(r, g, b);
      }
    
     else if(offtime == true)
     {
       delay(1000);
     }
     else
       CylonBounce(0xff, 0, 0, 4, 50, 50);
     
}


