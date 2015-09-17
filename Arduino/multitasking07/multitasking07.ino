#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Soundboard.h>
#include <SoftwareSerial.h>

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x42);

#define PIN            7
#define NUMPIXELS      54

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
int pixel2 = 0;

int R = 50;
int G = 0;
int B = 0;

int interlock = 0;

int ch5;
int ch6;
int ch5sound = 0;

unsigned long previousMillis1 = 0; 
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousLEDMillis = 0;
unsigned long previousPixelMillis = 0;
unsigned long previousCascadeMillis = 0;
unsigned long previousPeriMillis = 0;
unsigned long previousSawMillis = 0;
unsigned long previousProbeMillis = 0;
unsigned long previousScannerMillis = 0;
long pixelTime = 50;
long cascadeTime = 300;
long LEDTime = 500;
long onTime1 = 3000;
long onTime2 = 3000;
long onTime3 = 1500;
long periTime = 1600;
long sawTime = 500;
long probeTime = 500;
long scannerTime = 3000;
int LEDState = 0;
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
int flag5 = 0;
int flag6 = 0;
int flag7 = 0;
int flag40 = 0;


void setup() {
  
pinMode(10, OUTPUT);  // To 3 Leg mode
pinMode(11, OUTPUT);  // To 2 leg mode
pinMode(12, OUTPUT);  // Centre foot up
pinMode(13, OUTPUT);  // Centre foot down

digitalWrite (10, LOW);
digitalWrite (11, LOW);
digitalWrite (12, LOW);
digitalWrite (13, LOW);

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
pwm2.setPWM(2, 0, 320); // peri
pwm1.setPWM(2, 0, 130); // saw arm
pwm1.setPWM(3, 0, 130); // saw tool
pwm1.setPWM(4, 0, 525); // probe arm
pwm1.setPWM(5, 0, 405); // probe tool
pwm2.setPWM(3, 0, 109); // life form scanner
pwm2.setPWM(4, 0, 130); // life form scanner top

}

int setall(int R, int G, int B) {  /// set all logics to one RGB colour
     for (pixel2 = 0; pixel2 <= 35; pixel2++) {
     pixels.setPixelColor(pixel2, pixels.Color(R,G,B));
     pixels.show();
     }
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
    
   
    if (ch5 > 1060 || ch6 > 1060) {          // dirty hack to allow PWM/analog voltage to stabalise 
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
    else if (ch5 > 1155 && ch5 < 1168 && flag4 == 0) {  // 60 activate Periscope
      flag4 = 1;
    }
    else if (ch5 > 1093 && ch5 < 1100 && flag5 == 0) {  // 30 activate saw
      flag5 = 1;
    }
    else if (ch5 > 1112 && ch5 < 1122 && flag6 == 0) {  // 40 activate probe
      flag6 = 1;
    }    
    else if (ch5 > 1132 && ch5 < 1147 && flag7 == 0) {  // 50 activate LF Scanner
      flag7 = 1;
    }
    
    if (ch5 > 1305 && ch5 < 1325)  // 100
    {
    sfx.stop();
    }
    if (ch5 > 1062 && ch5 < 1067) // 1 
    {
    sfx.volDown();    
    }
    if (ch5 > 1077 && ch5 < 1083) // 2 
    {
    sfx.volUp();    
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
    
    // -------------------start 2-3-2 mode stuff------------
    
    else if (ch6 > 1060 && ch6 < 1068) {  // 2-3-2 interlock
    interlock = 1;
    setall(80,0,0);
    while (interlock != 0) {
        delay(300); // wait for button press to end
        ch6 = pulseIn(4, HIGH, 25000); // read channel      
        if (ch5 > 1060 || ch6 > 1060) {         // dirty hack to allow PWM/analog voltage to stabalise 
          delay(100);
          ch6 = pulseIn(4, HIGH, 25000);        // read channel / decide what to do
          }
          if (ch6 > 1060 && ch6 < 1068) {
            digitalWrite(10,LOW);               // make sure all 2-3-2 functions are diabled in case a switch fails while driving
            digitalWrite(11,LOW);
            digitalWrite(12,LOW);
            digitalWrite(13,LOW);
            delay(200);
            interlock = 0;  // break out of interlock
            }
          else if (ch6 > 1070 && ch6 < 1082) {  // start putting foot down
            digitalWrite(13,HIGH);              // put foot down
            interlock = 2;                      // set interlock to 3 leg mode lock
            }                                   // end putting foot down
            
          else if (ch6 > 1090 && ch6 < 1099 && interlock == 2) { // start shoulder conversion to 3 legs
            digitalWrite(10,HIGH);
          }                                                      // end shoulder conversion to 3 legs

          else if (ch6 > 1108 && ch6 < 1119) { // start conversion to 2 legs
            digitalWrite(11, HIGH);
            interlock = 3;                      // set interlock to 2 leg lock
          }

          else if (ch6 > 1130 && ch6 < 1142 && interlock == 3) {  // start putting foot up
            digitalWrite(12,HIGH);  
          }                                     // end putting foot up          
    }
    }    
          
 
     // -------------------end 2-3-2 mode stuff------------   
       
  
  if (currentMillis - previousPixelMillis >= pixelTime) {  // logic Neopixels
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
    else if (flag4 != 0) {
      R = 0;
      G = 30;
      B = 0;
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
         pixels.setPixelColor(52, pixels.Color(255,255,255));
         pixels.setPixelColor(53, pixels.Color(255,255,255));
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
         pixels.setPixelColor(52, pixels.Color(0,0,0));
         pixels.setPixelColor(53, pixels.Color(0,0,0));    
    pixels.show(); 
    flag3 = 0;
    previousMillis3 = currentMillis;
    }
    
    // periscope from here down

    else if (flag4 == 1) {
       pwm2.setPWM(1, 0, 360);
       pwm2.setPWM(2, 0, 320);
       flag4 = 2;
       previousPeriMillis = currentMillis;
    }
    else if (flag4 == 2 && currentMillis - previousPeriMillis >= periTime) {
         pixels.setPixelColor(36, pixels.Color(80,80,255));
         pixels.setPixelColor(37, pixels.Color(80,80,255));
         pixels.show();
         flag4 = 3;
         previousPeriMillis = currentMillis; 
    }
    
    else if (flag4 == 3 && currentMillis - previousPeriMillis >= periTime) {
         pwm2.setPWM(2, 0, 120);
         flag4 = 4;
         previousPeriMillis = currentMillis; 
    }
    else if (flag4 == 4 && currentMillis - previousPeriMillis >= periTime) {
         pwm2.setPWM(2, 0, 800);
         flag4 = 5;
         previousPeriMillis = currentMillis; 
    }
    else if (flag4 == 5 && currentMillis - previousPeriMillis >= periTime) {
         pwm2.setPWM(2, 0, 120);
         flag4 = 6;
         previousPeriMillis = currentMillis; 
    }
    else if (flag4 == 6 && currentMillis - previousPeriMillis >= periTime) {
         pwm2.setPWM(2, 0, 800);
         flag4 = 7;
         previousPeriMillis = currentMillis; 
    }
    else if (flag4 == 7 && currentMillis - previousPeriMillis >= periTime) {
         pwm2.setPWM(2, 0, 120);
         flag4 = 8;
         previousPeriMillis = currentMillis; 
    }
    else if (flag4 == 8 && currentMillis - previousPeriMillis >= periTime) {
         pwm2.setPWM(2, 0, 320);
         flag4 = 9;
         previousPeriMillis = currentMillis; 
    }
    else if (flag4 == 9 && currentMillis - previousPeriMillis >= periTime) {
         pixels.setPixelColor(36, pixels.Color(0,0,0));
         pixels.setPixelColor(37, pixels.Color(0,0,0));
         flag4 = 10;
         previousPeriMillis = currentMillis; 
    }
    else if (flag4 == 10 && currentMillis - previousPeriMillis >= periTime) {
         pwm2.setPWM(1, 0, 110);
         flag4 = 0;
         previousPeriMillis = currentMillis; 
    }
    
    //Saw arm from here down
    
    else if (flag5 == 1) {
      pwm1.setPWM(2, 0, 600);
      flag5 = 2;
      previousSawMillis = currentMillis;
    }
    else if (flag5 == 2 && currentMillis - previousSawMillis >= sawTime) {
      pwm1.setPWM(3, 0, 550);
      flag5 = 3;
      previousSawMillis = currentMillis;
    }
    else if (flag5 == 3 && currentMillis - previousSawMillis >= sawTime) {
      pwm1.setPWM(3, 0, 130);
      flag5 = 4;
      previousSawMillis = currentMillis;
    }
    else if (flag5 == 4 && currentMillis - previousSawMillis >= sawTime) {
      pwm1.setPWM(3, 0, 550);
      flag5 = 5;
      previousSawMillis = currentMillis;
    }
    else if (flag5 == 5 && currentMillis - previousSawMillis >= sawTime) {
      pwm1.setPWM(3, 0, 130);
      flag5 = 6;
      previousSawMillis = currentMillis;
    }
    else if (flag5 == 6 && currentMillis - previousSawMillis >= sawTime) {
      pwm1.setPWM(3, 0, 550);
      flag5 = 7;
      previousSawMillis = currentMillis;
    }
      else if (flag5 == 7 && currentMillis - previousSawMillis >= sawTime) {
      pwm1.setPWM(3, 0, 130);
      flag5 = 8;
      previousSawMillis = currentMillis;
    }
    else if (flag5 == 8 && currentMillis - previousSawMillis >= sawTime) {
      pwm1.setPWM(3, 0, 550);
      flag5 = 9;
      previousSawMillis = currentMillis;
    }
    else if (flag5 == 9 && currentMillis - previousSawMillis >= sawTime) {
      pwm1.setPWM(2, 0, 130);
      flag5 = 0;
      previousSawMillis = currentMillis;
    }
    
    //Probe arm from here down
    
    
    else if (flag6 == 1) {
      pwm1.setPWM(4, 0, 110);
      flag6 = 2;
      previousProbeMillis = currentMillis;
    }
    else if (flag6 == 2 && currentMillis - previousProbeMillis >= probeTime) {
      pwm1.setPWM(5, 0, 300);
      flag6 = 3;
      previousProbeMillis = currentMillis;
    }
      else if (flag6 == 3 && currentMillis - previousProbeMillis >= probeTime) {
      pwm1.setPWM(5, 0, 450);
      flag6 = 4;
      previousProbeMillis = currentMillis;
    }
      else if (flag6 == 4 && currentMillis - previousProbeMillis >= probeTime) {
      pwm1.setPWM(5, 0, 200);
      flag6 = 5;
      previousProbeMillis = currentMillis;
    }
      else if (flag6 == 5 && currentMillis - previousProbeMillis >= probeTime) {
      pwm1.setPWM(5, 0, 450);
      flag6 = 6;
      previousProbeMillis = currentMillis;
    }
      else if (flag6 == 6 && currentMillis - previousProbeMillis >= probeTime) {
      pwm1.setPWM(5, 0, 300);
      flag6 = 7;
      previousProbeMillis = currentMillis;
    }
      else if (flag6 == 7 && currentMillis - previousProbeMillis >= probeTime) {
      pwm1.setPWM(5, 0, 450);
      flag6 = 8;
      previousProbeMillis = currentMillis;
    }
      else if (flag6 == 8 && currentMillis - previousProbeMillis >= probeTime) {
      pwm1.setPWM(5, 0, 200);
      flag6 = 9;
      previousProbeMillis = currentMillis;
    }
      else if (flag6 == 9 && currentMillis - previousProbeMillis >= probeTime) {
      pwm1.setPWM(5, 0, 405);
      pwm1.setPWM(4, 0, 530);
      flag6 = 0;
      previousProbeMillis = currentMillis;
    }
    
    //Life Form Scanner from here down
    
    
     else if (flag7 == 1) {
      pwm2.setPWM(3, 0, 137);
      flag7 = 2;
      previousScannerMillis = currentMillis;
    }    
     else if (flag7 == 2 && currentMillis - previousScannerMillis >= scannerTime) {
      pwm2.setPWM(4, 0, 550);
      flag7 = 3;
      previousScannerMillis = currentMillis;
    }
     else if (flag7 == 3 && currentMillis - previousScannerMillis >= scannerTime) {
      pwm2.setPWM(4, 0, 130);
      flag7 = 4;
      previousScannerMillis = currentMillis;
    }
     else if (flag7 == 4 && currentMillis - previousScannerMillis >= scannerTime) {
      pwm2.setPWM(4, 0, 550);
      flag7 = 5;
      previousScannerMillis = currentMillis;
    }
     else if (flag7 == 5 && currentMillis - previousScannerMillis >= scannerTime) {
      pwm2.setPWM(4, 0, 130);
      flag7 = 6;
      previousScannerMillis = currentMillis;
    }
     else if (flag7 == 6 && currentMillis - previousScannerMillis >= scannerTime) {
      pwm2.setPWM(3, 0, 109);
      flag7 = 0;
      previousScannerMillis = currentMillis;
    }
    
}


