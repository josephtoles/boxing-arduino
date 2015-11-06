#include <Arduino.h>

#include "bluefruit.h"
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BluefruitLE_UART.h>

/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);


// A small helper (Bluefruit)
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}


void bluefruit_setup() {
  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  /* Perform a factory reset to make sure everything is in a known state */
  Serial.println(F("Performing a factory reset: "));
  if (! ble.factoryReset() ){
       error(F("Couldn't factory reset"));
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  //Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  //ble.info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in UART mode"));
  Serial.println();

  ble.verbose(false);  // debug info is a little annoying after this point!

  digitalWrite(READY_PIN, HIGH);

  /* Wait for connection */
  while (! ble.isConnected()) {
      delay(500);
  }

  Serial.println(F("*****************"));
}


/**************************************************************************/
/*!
    @brief  Checks for user input (via the Serial Monitor)
*/
/**************************************************************************/
/*
bool getUserInput(char buffer[], uint8_t maxSize)
{
  // timeout in 100 milliseconds
  TimeoutTimer timeout(100);

  memset(buffer, 0, maxSize);
  while( (Serial.peek() < 0) && !timeout.expired() ) {}

  if ( timeout.expired() ) return false;

  delay(2);
  uint8_t count=0;
  do
  {
    count += Serial.readBytes(buffer+count, maxSize);
    delay(2);
  } while( (count < maxSize) && !(Serial.peek() < 0) );

  return true;
}
*/

void bluefruit_loop() {
  /*
  extern int n_ext;
  if (n_ext) {
    Serial.println(n_ext);
    n_ext = 0;
  }
  */
  extern int n_ext;
  //Serial.println(n_ext);

  if (n_ext) {
    Serial.println(n_ext);

    if (n_ext > 200) {
      //Serial.println("Begin send message");
      ble.print("AT+BLEUARTTX=");ble.println(n_ext);
      if (! ble.waitForOK() ) {
         Serial.println(F("Failed to send check-in?"));
      }
      delay(50);
    }
    
    n_ext = 0;
  } else {
    //Serial.println("n_ext is zero");
  }

  //Serial.println("End send message");
  
}

