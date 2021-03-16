#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <Adafruit_SSD1306.h>
#include <splash.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 Mydisp(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int echoPin = 3;
const int triggerPin = 2;

unsigned long duration; // variable for duration
volatile unsigned long timeIn = 0; // echoPin: time RISE
volatile unsigned long timeOut = 0; // echoPin: time FALL

void measureIn() {
  timeIn = micros();
}

void measureOut() {
  timeOut = micros();
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // initialize with the I2C addr 0x3C (for the 128x64)
  Mydisp.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Mydisp.setTextColor(WHITE);

  // pinModes
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Send pulse for 0.01 
  digitalWrite(triggerPin,HIGH);
  delay(0.01);
  digitalWrite(triggerPin,LOW);

  // duration
  duration = pulseIn(echoPin,HIGH);
  Serial.println(duration);

  // interrupt
//  attachInterrupt(digitalPinToInterrupt(echoPin),measureIn,HIGH);
//  attachInterrupt(digitalPinToInterrupt(echoPin),measureOut,LOW);
//  duration = timeOut - timeIn;
//  Serial.print("timeIn = ");Serial.println(timeIn);
//  Serial.print("timeOut = ");Serial.println(timeOut);
  
  // display set up
  Mydisp.setTextSize(1,2); // integer x 10 (pixels)
    // what does 2nd variables in setTextSize(A,B) mean?

  Mydisp.clearDisplay();
  Mydisp.setCursor(10,0);
  Mydisp.print((float) duration/58); Mydisp.print(" cm");

  Mydisp.setCursor(10,20);
  Mydisp.print((float) duration/148); Mydisp.print(" in");

  Mydisp.display();
}
