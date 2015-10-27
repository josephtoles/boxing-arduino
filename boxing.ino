/*********************************************************************
 This is an example for our nRF51822 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

/***************************
 * Bluefruit configuration *
 ***************************/

#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
  #include <SoftwareSerial.h>
#endif

#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BluefruitLE_UART.h>

// Create the bluefruit object, either software serial...uncomment these lines

#include "bluefruit.h"
#include "adxl335.h"


/**************************************************************************/
/*!
    @brief  Sets up the HW an the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
void setup(void)
{
  pinMode(READY_PIN, OUTPUT);
  digitalWrite(READY_PIN, LOW);

  while (!Serial);  // required for Flora & Micro
  delay(500);

  Serial.begin(9600);

  adxl335_setup();
  if (BLUETOOTH_ENABLED) {
    bluefruit_setup();
  }
}

/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
void loop(void)
{
  adxl335_loop();
  if (BLUETOOTH_ENABLED) {
    bluefruit_loop();    
  }
}


