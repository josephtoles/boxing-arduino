#include <Arduino.h>
#include "bluefruit.h"  //just for serial setup TODO find a better way to do this
#include "adxl335.h"

void adxl335_setup() {
  
}


void adxl335_loop() {

  int MIN_CUTOFF = 460;
  int MAX_CUTOFF = 550;

  long x = analogRead(1);
  long y = analogRead(2);
  long z = analogRead(3);

  /*
  Serial.print("x=");Serial.print(x);
  Serial.print("y=");Serial.print(y);
  Serial.print("z=");Serial.print(z);
  */
  
  long total_acceleration = (long) sqrt(x*x + y*y + z*z);
  //Serial.println(total_acceleration);

}

