/*
* http://www.airspayce.com/mikem/arduino/RadioHead/
* https://lastminuteengineers.com/433mhz-rf-wireless-arduino-tutorial/
RH_ASK::RH_ASK  ( uint16_t  speed = 2000,
uint8_t   rxPin = 11,
uint8_t   txPin = 12,
uint8_t   pttPin = 10,
bool  pttInverted = false 
)  
*/


// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
 
void setup()
{
    // Initialize ASK Object
    rf_driver.init();
}
 
void loop()
{
    const char *msg = "Hello World";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(1000);
}
