#include <Wire.h>
#include <Servo.h>
#include "Adafruit_TCS34725.h"



// Color Sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
int r;
int g;
int b;
String userColor;
String inputColor;

// Servomotoro Pin
int SM = 3;
// Servomotor angle (default 45 deg)
int servoAngle = 90;
// Create Servo Object
Servo servo;



void setup() {
  // Baud Rate
  Serial.begin(9600);

  // delay
  delay(2000);

  // Setup: Color Sensor
  if (tcs.begin()) {
    Serial.println("Found sensor.");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Setup: Claw Servomotor
  servo.attach(SM);
  servo.write(servoAngle);
}


void loop() {
  // Prompt User for Input (package color)
  Serial.println("Enter Address Color.");
  while (Serial.available() == 0 ) {
    // Wait for User to Input Data
  }
  userColor = Serial.readString();
  Serial.println("User wants " + userColor);

  // initialize Sensor Color
  Serial.println("Initializing sensor.");
  readColor();

  // Continue to execute until user input & sensor inputs match
  matchColor();

  // Activate claw when user input & sensor inputs match
  pickup();
}



void matchColor() { 
  // Move until colors match
    // Serial.print(userColor);
    // Serial.print(inputColor); // has an 'new line'
    while ( userColor != inputColor + '\n' ) {
      Serial.println("User input does NOT match sensor input.");
      Serial.println();
  
      // do NOT activate servo (default angle)
      servo.write(servoAngle);
      
      // move to different location on Grid
      
      // Sensor reads 3 times and tells user color
      readColor();
    }
}



void pickup() {
    Serial.println("User input matches sensor input.");
    Serial.println("Close the claw and fly away");
    Serial.println();
  
    // Activate: Claw
    servo.write(0);
}



void readColor() {
  // color variable settings
  uint16_t r, g, b, c, colorTemp, lux;

  // obtain color data (1)
  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  // colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  // lux = tcs.calculateLux(r, g, b);

  // Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  // Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  // Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
  delay(2000);
  
  // obtain color data (2), after 2 sec delay
  tcs.getRawData(&r, &g, &b, &c);

  // Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  // Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  // Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
  delay(2000);

  // obtain color data (3), after 2 sec delay
  tcs.getRawData(&r, &g, &b, &c);

  // Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  // Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  // Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println();
  delay(2000);
  
  if ( r < 30000 ) {
    inputColor = "GREEN";
  }
  else if ( 50000 > r  > 40000 ) {
    inputColor = "YELLOW";
  }
  else if ( r > 60000 && g > 20000 ) {
    inputColor = "ORANGE";
  }
  else if ( r > 60000 && g < 20000 && b < 20000 ) {
    inputColor = "RED";
  }
  else if ( 60000 > r > 60000 && 20000 > b > 15000 ) {
    inputColor = "PINK";
  }
  Serial.println("Sensor reads " + inputColor);
}



// serial print variable type
void types(String a) { Serial.println("it's a String"); }
void types(int a) { Serial.println("it's an int"); }
void types(char *a) { Serial.println("it's a char*"); }
void types(float a) { Serial.println("it's a float"); }
void types(bool a) { Serial.println("it's a bool"); }
