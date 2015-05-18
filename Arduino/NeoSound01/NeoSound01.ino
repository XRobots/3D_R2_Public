// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            7

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      52

// Choose any two pins that can be used with SoftwareSerial to RX & TX
#define SFX_TX 5
#define SFX_RX 6
// Connect to the RST pin on the Sound Board
#define SFX_RST 4

// we'll be using software serial
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);

// pass the software serial to Adafruit_soundboard, the second
// argument is the debug port (not used really) and the third 
// arg is the reset pin
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 150; // delay for half a second
int R = 0;  
int G = 0;
int B = 0;
int i = 0;
long randNumber;

int ch5;
int ch6;

int ch5sound = 0;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  ss.begin(9600);
}

void loop()

{
    ch5 = pulseIn(2, HIGH, 25000); // Read the pulse width of 
    ch6 = pulseIn(4, HIGH, 25000); // each channel
  
    if (ch5 > 1300 && ch5 < 1325)  // 100
    {
    sfx.stop();
    }
    if (ch5 > 1260 && ch5 < 1270)  // 90
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
  
    if (ch6 > 1500 && ch6 < 1530)  // 130
    {
    sfx.playTrack("T00     OGG");     
    }
    else if (ch6 > 1590 && ch6 < 1620)  // 140
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
  
  
    pixels.setPixelColor(i, pixels.Color(R,G,B));
    pixels.setPixelColor((i-3), pixels.Color(R,G,B));
    pixels.setPixelColor((i+3), pixels.Color(R,G,B));
    pixels.setPixelColor((i-9), pixels.Color(R,G,B));
    pixels.setPixelColor((i+9), pixels.Color(R,G,B));
    pixels.setPixelColor((i-15), pixels.Color(R,G,B));
    pixels.setPixelColor((i+15), pixels.Color(R,G,B));
    pixels.setPixelColor((i-21), pixels.Color(R,G,B));
    pixels.setPixelColor((i+21), pixels.Color(R,G,B));
    pixels.setPixelColor(((i+4)/3), pixels.Color(0,0,0));
    pixels.setPixelColor(((i-2))*2, pixels.Color(0,0,0));
    pixels.setPixelColor(((i-6))*2, pixels.Color(0,0,0));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
    i=i+1;
    randNumber=random(10,50);
    R = (randNumber);
    randNumber=random(10,50);
    G = (randNumber);
    randNumber=random(10,50);
    B = (randNumber);
    
        if (i==51)
        {
          i = 0;
        }

}
