#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x42);

#define PIN            6
#define NUMPIXELS      24

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define CLOSED_00  50
#define OPEN_00  950
#define CLOSED_01  50
#define OPEN_01  950

int pulselen;
int pixel = 0;

int R = 50;
int G = 0;
int B = 0;

unsigned long previousMillis1 = 0; 
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousLEDMillis = 0;
unsigned long previousPixelMillis = 0;
unsigned long previousCascadeMillis = 0;
long pixelTime = 100;
long cascadeTime = 300;
long LEDTime = 500;
long onTime1 = 3000;
long onTime2 = 3000;
long onTime3 = 3000;
int LEDState = 0;
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag40 = 0;
int trigger1;
int trigger2;
int trigger3;
int trigger40;


void setup() {

pinMode (7, INPUT_PULLUP);
pinMode (8, INPUT_PULLUP);
pinMode (3, INPUT_PULLUP);
pinMode (11, OUTPUT); 
pinMode (12, OUTPUT); 

pwm1.begin();  
pwm1.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
pwm2.begin();  
pwm2.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
pixels.begin();

servoboard1(0, 0, OPEN_00, CLOSED_00);
servoboard1(1, 0, OPEN_00, CLOSED_00);
servoboard2(0, 0, OPEN_00, CLOSED_00);
  
}

int servoboard1(int servo, int state, int opened, int closed) {
  if (state == 1){
        for (pulselen = closed; pulselen < opened; pulselen++) {
    pwm1.setPWM(servo, 0, pulselen);
    }
  }
  if (state == 0){
       for (pulselen = opened; pulselen > closed; pulselen--) {
    pwm1.setPWM(servo, 0, pulselen);
    }
  }
} 

int servoboard2(int servo, int state, int opened, int closed) {
  if (state == 1){
        for (pulselen = closed; pulselen < opened; pulselen++) {
    pwm2.setPWM(servo, 0, pulselen);
    }
  }
  if (state == 0){
       for (pulselen = opened; pulselen > closed; pulselen--) {
    pwm2.setPWM(servo, 0, pulselen);
    }
  }
} 

void loop() {
  unsigned long currentMillis = millis();
  
  if (LEDState == 0 && (currentMillis - previousLEDMillis >= LEDTime)) {
    digitalWrite(11, 0);
    digitalWrite(12, 1);
    LEDState = 1;
    previousLEDMillis = currentMillis;
  }
  else if (LEDState == 1 && (currentMillis - previousLEDMillis >= LEDTime)) {
    digitalWrite(11, 1);
    digitalWrite(12, 0);
    LEDState = 0;
    previousLEDMillis = currentMillis; 
  }
    
  
  if (currentMillis - previousPixelMillis >= pixelTime) {
    pixels.setPixelColor(pixel, pixels.Color(R,G,B));
    pixels.setPixelColor((pixel-3), pixels.Color(R,G,B));
    pixels.setPixelColor((pixel+3), pixels.Color(15,15,15));
    pixels.setPixelColor((pixel-9), pixels.Color(15,15,15));
    pixels.setPixelColor((pixel+9), pixels.Color(R,G,B));
    pixels.setPixelColor((pixel-15), pixels.Color(R,G,B));
    pixels.setPixelColor((pixel+15), pixels.Color(15,15,15));
    pixels.setPixelColor((pixel-21), pixels.Color(15,15,15));
    pixels.setPixelColor((pixel+21), pixels.Color(R,G,B));
    pixels.setPixelColor(((pixel+4)/3), pixels.Color(0,0,0));
    pixels.setPixelColor(((pixel-2))*2, pixels.Color(0,0,0));
    pixels.setPixelColor(((pixel-6))*2, pixels.Color(0,0,0));
    pixels.show(); // This sends the updated pixel color to the hardware.
    pixel=pixel+1;
    
    if (flag1 == 2){
      R = 30;
      B = 0;
      G = 0;
    }
    else if (flag2 == 2) {
      B = 30;
      R = 0;
      G = 0;
    }
    else {    
      R = 40;
      G = 30;
      B = 0;
  }    
    if (pixel==23) {
       pixel = 0;
     }
  previousPixelMillis = currentMillis;
}  
  
  trigger1 = digitalRead(7);
  trigger2 = digitalRead(8);
  trigger40 = digitalRead(3);
 
  if (trigger1 == 0 && flag1 == 0) {
  flag1 = 1;
  }
  if (trigger2 == 0 && flag2 == 0) {
  flag2 = 1;
  }  
  if (trigger40 == 0 && flag40 == 0) {
  flag40 = 1;
  }
  
  if (flag40 == 1 && (currentMillis - previousCascadeMillis >= cascadeTime)) {
    flag1 = 1;
    flag40 = 2;   
    previousCascadeMillis = currentMillis;
  }
    else if (flag40 == 2 && (currentMillis - previousCascadeMillis >= cascadeTime)) {
    flag2 = 1;
    flag40 = 3;   
    previousCascadeMillis = currentMillis;
  }
    else if (flag40 == 3 && (currentMillis - previousCascadeMillis >= cascadeTime)) {
    flag3 = 1;
    flag40 = 0;   
    previousCascadeMillis = currentMillis;
  } 
  
  
  if (flag1 == 1) {
    //digitalWrite(11, HIGH);
    servoboard1(0, 1, OPEN_00, CLOSED_00);
    flag1 = 2;
    previousMillis1 = currentMillis;
  }
  else if (flag1 == 2 && (currentMillis - previousMillis1 >= onTime1)) {
    //digitalWrite(11, LOW);
    servoboard1(0, 0, OPEN_00, CLOSED_00);
    flag1 = 0;
    previousMillis1 = currentMillis;
  }  
  
  
  if (flag2 == 1) {
    //digitalWrite(12, HIGH);
    servoboard1(1, 1, OPEN_00, CLOSED_00);
    flag2 = 2;
    previousMillis2 = currentMillis;
  }
  else if (flag2 == 2 && (currentMillis - previousMillis2 >= onTime2)) {
    //digitalWrite(12, LOW);
    servoboard1(1, 0, OPEN_00, CLOSED_00);
    flag2 = 0;
    previousMillis2 = currentMillis;
  }
  
  
    if (flag3 == 1) {
    //digitalWrite(12, HIGH);
    servoboard2(0, 1, OPEN_00, CLOSED_00);
    flag3 = 2;
    previousMillis3 = currentMillis;
  }
  else if (flag3 == 2 && (currentMillis - previousMillis3 >= onTime3)) {
    //digitalWrite(12, LOW);
    servoboard2(0, 0, OPEN_00, CLOSED_00);
    flag3 = 0;
    previousMillis3 = currentMillis;
  }
 
}


