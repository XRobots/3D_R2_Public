// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            7

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      52


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

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop()

{
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
