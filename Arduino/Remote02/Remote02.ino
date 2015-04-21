// include the library code:
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

//Variables for menu
int column = 0;
int function = 0;
int buttonValue = 0;
int button2 = 1;
int button3 = 1;
int button4 = 1;
int button7 = 1;
int button8 = 1;
int button9 = 1;
int button10 = 1;
int button11 = 1;
int button12 = 1;
int button13 = 1;

void setup() {
  lcd.begin(16, 2);
  lcd.setBacklight(YELLOW);
  lcd.setCursor(0,0);
  lcd.print("R6 Droid Control");
  delay(2000);
  lcd.clear();
  lcd.print("Actions         ");
  lcd.setBacklight(GREEN);
  
  pinMode(5, OUTPUT); // channel 5
  pinMode(6, OUTPUT); // channel 6
  pinMode(2, INPUT_PULLUP); // button inputs
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
}

uint8_t i=0;
void loop() {
  
  buttonValue = 0;
  
  button2 = digitalRead(2);
  button3 = digitalRead(3);
  button4 = digitalRead(4);
  button7 = digitalRead(7);
  button8 = digitalRead(8);
  button9 = digitalRead(9);
  button10 = digitalRead(10);
  button11 = digitalRead(11);
  button12 = digitalRead(12);
  button13 = digitalRead(13);
  
  if (button2 == LOW) {     
    buttonValue = 10;    
  } 
  if (button3 == LOW) {
    buttonValue = 20;
  }
  if (button4 == LOW) {
    buttonValue = 30;
  }
  if (button7 == LOW) {
    buttonValue = 40;
  }
  if (button8 == LOW) {
    buttonValue = 50;
  }
  if (button9 == LOW) {
    buttonValue = 60;
  }
  if (button10 == LOW) {
    buttonValue = 70;
  }
  if (button11 == LOW) {
    buttonValue = 80;
  }
  if (button12 == LOW) {
    buttonValue = 90;
  }
  if (button13 == LOW) {
    buttonValue = 100;
  }
  
  analogWrite(6, buttonValue);
  lcd.setCursor(13,0);
  lcd.print(buttonValue);
  lcd.print("   ");
     
  uint8_t buttons = lcd.readButtons();

  if (buttons) {
    if (buttons & BUTTON_LEFT) {
      lcd.setCursor(0,0);
      lcd.print("Actions         ");
      lcd.setBacklight(GREEN);
      column = column - 130;
      column = constrain(column,0,130);
      
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.setCursor(0,0);
      lcd.print("Sounds           ");
      lcd.setBacklight(RED);
      column = column + 130;
      column = constrain(column,0,130);
    }
    if (buttons & BUTTON_UP) {
      function = function - 10;
      function = constrain(function,0,120);
      lcd.setCursor(0,1);
      lcd.print(function);
      lcd.print("              ");
      delay(200);
    }
    if (buttons & BUTTON_DOWN) {
      function = function + 10;
      function = constrain(function,0,120);
      lcd.setCursor(0,1);
      lcd.print(function);
      lcd.print("              ");
      delay(200);
    }
    if (buttons & BUTTON_SELECT) {
      //lcd.setBacklight(VIOLET);
      lcd.setCursor(4,1);
      lcd.print("         ");
      lcd.print(column+function);
      lcd.print("   ");
      analogWrite(5, column+function);
      
    }
  }
  
  
}
