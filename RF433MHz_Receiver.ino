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
    // Setup Serial Monitor
    Serial.begin(9600);
}
 
void loop()
{
    // Set buffer to size of expected message
    uint8_t buf[11];
    uint8_t buflen = sizeof(buf);
    //Serial.println((char*)buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
      
      // Message received with valid checksum
      Serial.print("Message Received: ");
      Serial.println((char*)buf);         
    }
}
