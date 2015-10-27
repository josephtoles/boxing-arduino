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


// Scales a number to f(minus)=-100, f(plus)=100
long scale(long number, long minus, long plus) {
  double a = 200 * 1.0 / (plus - minus);
  double b = 100 - a * plus;
  long output = (long) (a * number + b);
  /*
  Serial.println("begin calculation");
  Serial.print("b=");Serial.println(b);
  Serial.print("precasted");Serial.println(a * number + b);
  Serial.print("a=");Serial.println(a);
  Serial.print("output=");Serial.println(output);
  */
  return output;
}


void adxl335_loop() {
  long x = analogRead(1);
  long y = analogRead(2);
  long z = analogRead(3);

  // X_PLUS is the value of X shen accelerating upward
  // X_MINUX is the value of X shen accelerating downward
  
  long X_PLUS = 397;
  long X_MINUS = 264;
  long Y_PLUS = 399;
  long Y_MINUS = 264;
  long Z_PLUS = 145;
  long Z_MINUS = 15;

  x = scale(x, X_MINUS, X_PLUS);
  y = scale(y, Y_MINUS, Y_PLUS);
  z = scale(z, Z_MINUS, Z_PLUS);
  long squared_norm = x*x + y*y + z*z;

  print_to_size(x);Serial.print("=x");
  print_to_size(y);Serial.print("=y");
  print_to_size(z);Serial.print("=z");
  Serial.println("");

  /*
  Serial.print(x);Serial.print("=x, ");
  Serial.print(y);Serial.print("=y, ");
  Serial.print(z);Serial.print("=z\n");
  */
  
  //long total_acceleration = (long) sqrt(x*x + y*y + z*z);
  //Serial.println(total_acceleration);

}

