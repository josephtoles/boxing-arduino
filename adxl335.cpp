#include <Arduino.h>
#include "bluefruit.h"  //just for serial setup TODO find a better way to do this
#include "adxl335.h"

const int X_PLUS = 397;
const int X_MINUS = 264;
const int Y_PLUS = 399;
const int Y_MINUS = 264;
const int Z_PLUS = 145;
const int Z_MINUS = 15;

// Variables for export
int e_x;
int e_y;
int e_z;

void adxl335_setup() {
  
}


void print_to_size(int number) {
  char buffer[6] = "";
  sprintf(buffer, "%6d", number);
  Serial.print(buffer);
}


// Scales a number to f(minus)=-100, f(plus)=100
int scale(int number, int minus, int plus) {
  double a = 200 * 1.0 / (plus - minus);
  double b = 100 - a * plus;
  return (int) (a * number + b);
}


void adxl335_loop() {
  int x = analogRead(1);
  int y = analogRead(2);
  int z = analogRead(3);

  // X_PLUS is the value of X shen accelerating upward
  // X_MINUX is the value of X shen accelerating downward
  
  x = scale(x, X_MINUS, X_PLUS);
  y = scale(y, Y_MINUS, Y_PLUS);
  z = scale(z, Z_MINUS, Z_PLUS);

  print_to_size(x);Serial.print(F("=x"));
  print_to_size(y);Serial.print(F("=y"));
  print_to_size(z);Serial.print(F("=z"));
  Serial.println("");

  /*
  e_x = x;
  e_y = y;
  e_z = z;
  */

  // This code doesn't function on the Arduino for some reason
  /*
  int norm_squared = x * x + y * y + z * z;
  int TRIGGER_THRESHOLD = 35;
  if (norm_squared < (100 - TRIGGER_THRESHOLD) * (100 - TRIGGER_THRESHOLD) ||
      norm_squared > (100 + TRIGGER_THRESHOLD) * (100 + TRIGGER_THRESHOLD)) {
    Serial.println("punch");
  }
  */
}

