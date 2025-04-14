#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 1
#define CS_PIN 10

#define AOUT_PIN1 A0 // Arduino pin that connects to AOUT pin of moisture sensor
#define AOUT_PIN2 A1
#define AOUT_PIN3 A2

#define THRESHOLD 890 // CHANGE YOUR THRESHOLD HERE

MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  Serial.begin(9600);
 
  Display.begin();
  
  Display.setIntensity(0);
  Display.displayClear();
}

void loop() {
  Display.print("1");
  int value[3] = {analogRead(AOUT_PIN1), analogRead(AOUT_PIN2), analogRead(AOUT_PIN3)};
  String text[3];

  for (int i=0; i<sizeof(text)/sizeof(text[0]); i++){
    if (value[i] > THRESHOLD) {
      text[i] = i+1; //The soil of 1 is DRY
    }
  }
  
  Display.setTextAlignment(PA_CENTER);
  for (int i=0; i<sizeof(text)/sizeof(text[0]); i++){
    Display.print(text[i]);
    delay(1000);
  }
  
  for (int i=0; i<sizeof(text)/sizeof(text[0]); i++){
    text[i] = "";
  }
}
