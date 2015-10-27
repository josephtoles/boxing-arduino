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

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

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


int box_count = 0;
  
void bluefruit_loop() {

  Serial.println("Begin send message");
  ble.print("AT+BLEUARTTX=");ble.println("data");
  if (! ble.waitForOK() ) {
     Serial.println(F("Failed to send check-in?"));
  }
  delay(50);

  Serial.println("End send message");
  
  /*
  if (total_acceleration > MAX_CUTOFF) {
    box_count += 1;
  } else {
    if (box_count) {
      if (box_count >= 1000 && box_count <= 9999) {
        Serial.println(box_count);
        ble.print("AT+BLEUARTTX=");ble.print(box_count);ble.println("            ");
        delay(50);
        if (! ble.waitForOK() ) {
           Serial.println(F("Failed to send x?"));
        }
      }
      box_count = 0;
    }
  }
  */
}

