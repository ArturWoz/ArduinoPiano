#include <Keypad.h>
#include <Wire.h>
#include "rgb_lcd.h"

const int freq[4][12] = { //Frequencies
    { 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247 },
    { 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494 },
    { 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988 },
    { 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976 }
};

//LCD
rgb_lcd lcd;

//Keypad
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', '9'+1, '9'+2, '9'+3},
  {'D', 'E', 'F', 'G'}
};
byte rowPins[ROWS] = {7,6,5,4}; 
byte colPins[COLS] = {8,9,10,11}; 
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//buzzer pin
const int buzzer = 2;

byte octave = 0;
int len = 300;

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);

  lcd.print("Octave: ");
  lcd.setCursor(0, 1);
  lcd.print(octave);
}
  
void loop(){
  char customKey = keypad.getKey();

  switch(customKey)
  {
    case 0:
      break;
    case 'D':
      if(octave>0) octave--;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Octave: ");
      lcd.setCursor(0, 1);
      lcd.print(octave);
      break;
    
    case 'E':
      if(octave<3) octave++;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Octave: ");
      lcd.setCursor(0, 1);
      lcd.print(octave);
      break;
    
    case 'F':
      if(len>100) len=len/2;
      break;
    
    case 'G':
      if(len<1000) len=len*2;
      break;

    default:
      int note = freq[octave][customKey-'0'];
      Serial.println(len);
      tone(buzzer,note);
      delay(len);
      noTone(buzzer);
      break;
  }
}