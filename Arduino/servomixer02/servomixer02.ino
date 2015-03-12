#include <Servo.h>
Servo servo1;
Servo servo2;
 
int channel1; // Forward & Backwards input variable
int channel2; // Left & Right input variable
int channel3; // Head turning input variable
int houtput1; //Head turning output1
int houtput2; //Head turning output2
int output1; // Output first wheel variable
int output2; // Output second wheel variable
int diff; // Difference when steering

void setup() {
  
  servo1.attach(10);  // servo output on pin 10
  servo2.attach(11);  // servo output on pin 11
  
  pinMode(5, OUTPUT); // Head PWM
  pinMode(6, OUTPUT); // Head PWM
  
  pinMode(2, INPUT); // Wire to actual channel 2 for throttle
  pinMode(4, INPUT); // Wire to actual channel 1 for steering
  pinMode(8, INPUT); // Wire to actual channel 4 for head turning 
}
  
void loop() {

  channel1 = pulseIn(2, HIGH, 25000); // Read throttle
  channel2 = pulseIn(4, HIGH, 25000); // Read steering
  channel3 = pulseIn(8, HIGH, 25000); // Read head turning

  channel1 = map(channel1, 1100, 1900, 20, 130); // Scale throttle
  channel2 = map(channel2, 1100, 1900, 0, 200); // Scale steering
  channel3 = map(channel3, 1100, 1900, 0, 510); // Scale head turning
  
  channel1 = constrain(channel1,10,190); // Limit throttle
  channel2 = constrain(channel2,10,190); // Limit steering
  channel3 = constrain(channel3,0,510); // Limit head turning

  diff = channel2 - 100;  // Work out steering difference from centre point
  diff = map(diff, 0, 100, 0 , 65); // Scale steering value
  
  output1 = channel1 + diff;  // First wheel output value
  output2 = channel1 - diff;  // Second wheel output value
  
  if(channel3 > 280)
  {
    houtput1 = channel3-255;
    houtput2 = 0;
  }
  else if(channel3 < 230)
  {
    houtput1 = 0;
    houtput2 = 255-channel3;
  }
  else
  {
  houtput1 = 0;
  houtput2 = 0;
  }
  
  servo1.write(output1);
  servo2.write(output2);
  
  analogWrite(5,houtput1);
  analogWrite(6,houtput2);  
  
}
