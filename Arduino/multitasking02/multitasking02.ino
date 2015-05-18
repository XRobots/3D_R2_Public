#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Soundboard.h>
#include <SoftwareSerial.h>

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x42);


#define PIN            7
#define NUMPIXELS      52

#define SFX_TX 5
#define SFX_RX 6
#define SFX_RST 4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

#define CLOSED_00  50  //ut arms
#define OPEN_00  950
#define CLOSED_01  50
#define OPEN_01  950
#define CLOSED_02  300 // holo
#define OPEN_02  520 // holo
int pulselen;
int pixel = 0;

int R = 50;
int G = 0;
int B = 0;

int ch5;
int ch6;
int ch5sound = 0;

unsigned long previousMillis1 = 0; 
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousLEDMillis = 0;
unsigned long previousPixelMillis = 0;
unsigned long previousCascadeMillis = 0;
long pixelTime = 50;
long cascadeTime = 300;
long LEDTime = 500;
long onTime1 = 3000;
long onTime2 = 3000;
long onTime3 = 1500;
int LEDState = 0;
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag40 = 0;

void setup() {

pwm1.begin();  
pwm1.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
pwm2.begin();  
pwm2.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
pixels.begin();

ss.begin(9600);

Serial.begin(115200);

servoboard1(0, 0, OPEN_00, CLOSED_00); // ut arm
servoboard1(1, 1, OPEN_01, CLOSED_01); // ut arm
servoboard2(0, 1, OPEN_02, CLOSED_02); // holo
  
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
  
    ch5 = pulseIn(2, HIGH, 25000); // Read the pulse width of 
    ch6 = pulseIn(4, HIGH, 25000); // each channel
    
    //Serial.print(ch5);
    //Serial.print(" , ");
    //Serial.println(ch6);
    
    if (ch5 > 1060 || ch6 > 1060) {          // dirty hack to allow PWM/analog voltage to stabalise111111111111111111111111111111111111111111111111111111111111111111111111111111111  11  1  1    11      11``  1    qqqq  
      delay(100);
      ch5 = pulseIn(2, HIGH, 25000); // Read the pulse width of 
      ch6 = pulseIn(4, HIGH, 25000); // each channel
    }
      
  
    if (ch5 > 1185 && ch5 < 1200 && flag40 == 0) {  // 70 open utility arms
      flag40 = 1;  
    }
    else if (ch5 > 1215 && ch5 < 1235 && flag3 == 0) {  // 80 activate holo
      flag3 = 1;  
    } 
    
    if (ch5 > 1305 && ch5 < 1325)  // 100
    {
    sfx.stop();
    }
    if (ch5 > 1255 && ch5 < 1270)  // 90
    {
    ch5sound = ch5sound + 1;  // up track
        if (ch5sound == 1) { sfx.playTrack("T20     OGG"); }
        if (ch5sound == 2) { sfx.playTrack("T21     OGG"); }
        if (ch5sound == 3) { sfx.playTrack("T22     OGG"); }
        if (ch5sound == 4) { sfx.playTrack("T23     OGG"); }
        if (ch5sound == 5) { sfx.playTrack("T24     OGG"); }
        if (ch5sound == 6) { sfx.playTrack("T25     OGG"); }
        if (ch5sound == 7) { sfx.playTrack("T26     OGG"); }
        if (ch5sound == 8) { sfx.playTrack("T27     OGG"); }
        if (ch5sound == 9) { sfx.playTrack("T28     OGG"); }
        if (ch5sound == 10) { sfx.playTrack("T29     OGG"); }
        if (ch5sound == 11) 
        { 
        sfx.playTrack("T30     OGG"); 
        ch5sound = 0;
        }     
    }   
 
    if (ch6 > 1505 && ch6 < 1525)  // 130
    {
    sfx.playTrack("T00     OGG");     
    }
    else if (ch6 > 1595 && ch6 < 1615)  // 140
    {
    sfx.playTrack("T01     OGG");    
    }
    else if (ch6 > 1660 && ch6 < 1685)  //150
    {
    sfx.playTrack("T02     OGG");   
    }
    else if (ch6 > 1715 && ch6 < 1740)  //160
    {
    sfx.playTrack("T03     OGG");     
    }    
  
  if (currentMillis - previousPixelMillis >= pixelTime) {
    pixels.setPixelColor(pixel, pixels.Color(R,G,B));
    pixels.setPixelColor((pixel-3), pixels.Color(R,G,B));
    pixels.setPixelColor((pixel-9), pixels.Color(50,50,50));
    pixels.setPixelColor((pixel-15), pixels.Color(R,G,B));
    pixels.setPixelColor(((pixel-2)), pixels.Color(0,0,0));
    pixels.setPixelColor(((pixel-12)), pixels.Color(0,0,0));

    pixels.show(); // This sends the updated pixel color to the hardware.
    pixel=pixel+1;
    
    if (flag1 == 1 || flag2 == 2){
      R = 30;
      B = 0;
      G = 0;
    }
    else if (flag3 == 1 || flag3 == 2 || flag3 == 4) {
      B = 30;
      R = 0;
      G = 0;
    }
    else {    
      R = 40;
      G = 30;
      B = 0;
  }    
    if (pixel==36) {
       pixel = 0;
     }
  previousPixelMillis = currentMillis;
} 

 
  if (flag40 == 1 && (currentMillis - previousCascadeMillis >= cascadeTime)) {
    flag1 = 1;
    flag40 = 2;   
    previousCascadeMillis = currentMillis;
  }
    else if (flag40 == 2 && (currentMillis - previousCascadeMillis >= cascadeTime)) {
    flag2 = 1;
    flag40 = 0;   
    previousCascadeMillis = currentMillis;
  }
  
  
  if (flag1 == 1) {
    servoboard1(0, 1, OPEN_00, CLOSED_00);
    flag1 = 2;
    previousMillis1 = currentMillis;
  }
  else if (flag1 == 2 && (currentMillis - previousMillis1 >= onTime1)) {
    servoboard1(0, 0, OPEN_00, CLOSED_00);
    flag1 = 0;
    previousMillis1 = currentMillis;
  }  
  
  
  if (flag2 == 1) {
    servoboard1(1, 0, OPEN_01, CLOSED_01);
    flag2 = 2;
    previousMillis2 = currentMillis;
  }
  else if (flag2 == 2 && (currentMillis - previousMillis2 >= onTime2)) {
    servoboard1(1, 1, OPEN_01, CLOSED_01);
    flag2 = 0;
    previousMillis2 = currentMillis;
  }
  
  
   if (flag3 == 1) {
         pixels.setPixelColor(36, pixels.Color(255,255,255));
         pixels.setPixelColor(37, pixels.Color(255,255,255));
         pixels.setPixelColor(38, pixels.Color(255,255,255));
         pixels.setPixelColor(39, pixels.Color(255,255,255));
         pixels.setPixelColor(40, pixels.Color(255,255,255));
         pixels.setPixelColor(41, pixels.Color(255,255,255));
         pixels.setPixelColor(42, pixels.Color(255,255,255));
         pixels.setPixelColor(43, pixels.Color(255,255,255));
         pixels.setPixelColor(44, pixels.Color(255,255,255));
         pixels.setPixelColor(45, pixels.Color(255,255,255));
         pixels.setPixelColor(46, pixels.Color(255,255,255));
         pixels.setPixelColor(47, pixels.Color(255,255,255));
         pixels.setPixelColor(48, pixels.Color(255,255,255));
         pixels.setPixelColor(49, pixels.Color(255,255,255));
         pixels.setPixelColor(50, pixels.Color(255,255,255));
         pixels.setPixelColor(51, pixels.Color(255,255,255));
    pixels.show();     
    flag3 = 2;
    previousMillis3 = currentMillis;
  }
  
  else if (flag3 == 2 && (currentMillis - previousMillis3 >= onTime3)) {
    servoboard2(0, 0, OPEN_02, CLOSED_02);
    flag3 = 3;
    previousMillis3 = currentMillis;
  }
  
  else if (flag3 == 3 && (currentMillis - previousMillis3 >= onTime3)) {
    servoboard2(0, 1, OPEN_02, CLOSED_02);
    flag3 = 4;
    previousMillis3 = currentMillis;
  }
  
  else if (flag3 == 4 && (currentMillis - previousMillis3 >= onTime3)) {
         pixels.setPixelColor(36, pixels.Color(0,0,0));
         pixels.setPixelColor(37, pixels.Color(0,0,0));
         pixels.setPixelColor(38, pixels.Color(0,0,0));
         pixels.setPixelColor(39, pixels.Color(0,0,0));
         pixels.setPixelColor(40, pixels.Color(0,0,0));
         pixels.setPixelColor(41, pixels.Color(0,0,0));
         pixels.setPixelColor(42, pixels.Color(0,0,0));
         pixels.setPixelColor(43, pixels.Color(0,0,0));
         pixels.setPixelColor(44, pixels.Color(0,0,0));
         pixels.setPixelColor(45, pixels.Color(0,0,0));
         pixels.setPixelColor(46, pixels.Color(0,0,0));
         pixels.setPixelColor(47, pixels.Color(0,0,0));
         pixels.setPixelColor(48, pixels.Color(0,0,0));
         pixels.setPixelColor(49, pixels.Color(0,0,0));
         pixels.setPixelColor(50, pixels.Color(0,0,0));
         pixels.setPixelColor(51, pixels.Color(0,0,0));    
    pixels.show(); 
    flag3 = 0;
    previousMillis3 = currentMillis;
    }
 
}


