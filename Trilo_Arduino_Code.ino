#include "Adafruit_GFX.h"
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif

#define NUMPIXELS 256


#define LED_PIN    11


#define LED_COUNT 300





Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int FSRRED = 0;
int FSRGREEN = 1;
int FSRBLUE = 2;
int PotiPIN = 3;

int FSRREDReading;
int FSRREDReading2;
int FSRGREENReading;
int FSRGREENReading2;
int FSRBLUEReading;
int FSRBLUEReading2;
int wert1 = 0.5;
int wer2 = 0.8;
int PotiVal = 0;


int LEDREDbrightness;
int LEDGREENbrightness;
int LEDBLUEbrightness;

int LEDblau = 3;
int LEDrot = 6;
int LEDgruen = 5;
unsigned long wartezeit = 200;
unsigned long millisAlt = 0;
int brightness1a = 150;
int brightness1b = 100;
int brightness1c = 130;
boolean dunkel = 0;
double daempfung = 1;

float EMA_a_low = 0.05;
float EMA_S_lowRED = 0;
float EMA_S_lowGREEN = 0;
float EMA_S_lowBLUE = 0;

void setup(void) {

    Serial.begin(115200);                     //setup of Serial module, 115200 bits/second
   
  EMA_S_lowRED = analogRead(FSRRED);
  EMA_S_lowGREEN = analogRead(FSRGREEN);
  EMA_S_lowBLUE = analogRead(FSRBLUE);//set EMA S for t=1


  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif


  strip.begin();
  strip.show();
  strip.setBrightness(100);


  pinMode(LEDblau, OUTPUT);
  pinMode(LEDgruen, OUTPUT);
  pinMode(LEDrot, OUTPUT);
}

void loop(void) {

  FSRREDReading = analogRead(FSRRED);
  EMA_S_lowRED = (EMA_a_low*FSRREDReading) + ((1-EMA_a_low)*EMA_S_lowRED);    
  LEDREDbrightness = map(EMA_S_lowRED, 0, 1023, 0, 255);


 FSRGREENReading = analogRead(FSRGREEN);
  EMA_S_lowGREEN = (EMA_a_low*FSRGREENReading) + ((1-EMA_a_low)*EMA_S_lowGREEN);    
  LEDGREENbrightness = map(EMA_S_lowGREEN, 0, 1023, 0, 255);


 FSRBLUEReading = analogRead(FSRBLUE);
  EMA_S_lowBLUE = (EMA_a_low*FSRBLUEReading) + ((1-EMA_a_low)*EMA_S_lowBLUE);    
  LEDBLUEbrightness = map(EMA_S_lowBLUE, 0, 1023, 0, 255);


  for (int zaehler=0; zaehler<255; zaehler = zaehler+1){
  strip.setPixelColor(zaehler, LEDREDbrightness, LEDGREENbrightness, LEDBLUEbrightness);}


  strip.show();

PotiVal = analogRead(PotiPIN);

wartezeit = map(PotiVal,0,1023,100,200);

 Serial.println(wartezeit);

if(millis() - millisAlt >= wartezeit){
  Serial.println("Wartezeit um");
  Serial.println(millis() - millisAlt);
  millisAlt = millis();
  dunkel =! dunkel;
}

if (dunkel == 0){
  brightness1a = 150;
  brightness1b = 100;
  brightness1c = 130;
} else {
  brightness1a = 0;
}

//Serial.println(dunkel);
  analogWrite(LEDblau, brightness1a);
  analogWrite(LEDrot, brightness1a);
  analogWrite(LEDgruen, brightness1a);
}
