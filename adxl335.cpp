#include <Arduino.h>
#include "bluefruit.h"  //just for serial setup TODO find a better way to do this
#include "adxl335.h"

const int X_PLUS = 397;
const int X_MINUS = 264;
const int Y_PLUS = 399;
const int Y_MINUS = 264;
const int Z_PLUS = 404;  // Requires slightly finer calibration
const int Z_MINUS = 269;  // Requires slightly finer calibration

// Variables for export
int n_1;
int n_2;
int n_3;
int n_4;

// Variables for remembering time
int time_since_punch_start;
bool punch_confirmed;

void adxl335_setup() {
  time_since_punch_start = 0;
  punch_confirmed = false;
}


void print_to_size(int number) {
  Serial.print("");Serial.print(number);
  // You [Joseph] are an idiot.
  
  //char buffer[5] = "";
  //sprintf(buffer, "%5d", number);
  //Serial.print(buffer);
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

  /*
  print_to_size(x);Serial.print(F("=ax"));
  print_to_size(y);Serial.print(F("=ay"));
  print_to_size(z);Serial.print(F("=az"));
  Serial.println("");

  // X_PLUS is the value of X shen accelerating upward
  // X_MINUX is the value of X shen accelerating downward

  Serial.print(" |");

  print_to_size(xs);Serial.print(F("=xs"));
  print_to_size(ys);Serial.print(F("=ys"));
  print_to_size(zs);Serial.print(F("=zs"));
  //Serial.println("");

  Serial.print(" |");
  */

  int n = (int) (sqrt((xs * xs) + (ys * ys) + (zs * zs)));
  if (false) {
    print_to_size(n);Serial.print(F(""));
    Serial.println("");
  }

  //Trying integration
  if (n > 100) {
    if (n > 145) {
      punch_confirmed = true;
    }
    time_since_punch_start += n - 100;
  } else {
    if (punch_confirmed && (time_since_punch_start > 3000)) {
      Serial.println(time_since_punch_start);
      delay(1000);
    }
    time_since_punch_start = 0;
    punch_confirmed = false;
  }

  // Trying hard cutoffs
  /*
  time_since_punch_start += 1;
  if (punch_confirmed) {
    if (n < 100) {
      //Serial.println(time_since_punch_start);
      time_since_punch_start = 0;
      punch_confirmed = false;
    }
  } else {
    if (n < 100) {
      punch_confirmed = false;
      time_since_punch_start = 0;
    } else if (n > 145) {
      punch_confirmed = true;
    }
  }
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

