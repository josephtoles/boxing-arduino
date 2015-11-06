#include <Arduino.h>
#include "bluefruit.h"  //just for serial setup TODO find a better way to do this
#include "adxl335.h"

const int X_PLUS = 397;
const int X_MINUS = 264;
const int Y_PLUS = 399;
const int Y_MINUS = 264;
const int Z_PLUS = 404;  // Requires slightly finer calibration
const int Z_MINUS = 269;  // Requires slightly finer calibration

// Variables for counting zeroes
bool counting_zeroes;
int count_since_first_zero;
int count_since_last_zero;
int n_ext;  // Variable to send data to bluefruit.cpp for output
int n;  // May not have to be here

void adxl335_setup() {
  bool counting_zeroes = false;
  n_ext = 0;
}


// Scales a number to f(minus)=-100, f(plus)=100
int scale(int number, int minus, int plus) {
  double a = 200 * 1.0 / (plus - minus);
  double b = 100 - a * plus;
  int output = (int) (a * number + b);
  return output;
}


void adxl335_loop() {

  int x = analogRead(1);
  int y = analogRead(2);
  int z = analogRead(3);

  int xs = scale(x, X_MINUS, X_PLUS);
  int ys = scale(y, Y_MINUS, Y_PLUS);
  int zs = scale(z, Z_MINUS, Z_PLUS);

  n = (int) (sqrt((xs * xs) + (ys * ys) + (zs * zs)));

  //Counting zeroes
  if (counting_zeroes) {
    ++count_since_first_zero;
    if (n==0) {
      count_since_last_zero = 0;
    } else {
      ++count_since_last_zero;
      if (count_since_last_zero > 100) {
        //Serial.println(count_since_first_zero);
        n_ext = count_since_first_zero;
        //Serial.println(n_ext);
        counting_zeroes = false;
      }
    }
  } else {
    if (n==0) {
      counting_zeroes = true;
      count_since_first_zero = 0;
      count_since_last_zero = 0;
    }
  }

  // TODO
  // Ignore any numbers less than 250. They're not punches.
  // Calculate proper timing
}

