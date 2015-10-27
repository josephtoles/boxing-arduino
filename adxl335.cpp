#include <Arduino.h>
#include "bluefruit.h"  //just for serial setup TODO find a better way to do this
#include "adxl335.h"

void adxl335_setup() {
  
}


void print_to_size(int number) {
  char buffer[6] = "";
  sprintf(buffer, "%6d", number);
  Serial.print(buffer);
}


void adxl335_loop() {

  int MIN_CUTOFF = 460;
  int MAX_CUTOFF = 550;

  long x = analogRead(1);
  long y = analogRead(2);
  long z = analogRead(3);

  print_to_size(x);Serial.print("=x");
  print_to_size(y);Serial.print("=y");
  print_to_size(z);Serial.print("=z");
  Serial.println("");
  
  long total_acceleration = (long) sqrt(x*x + y*y + z*z);
  //Serial.println(total_acceleration);

}

