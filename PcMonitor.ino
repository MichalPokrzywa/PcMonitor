#include <UTFTGLUE.h>              //use GLUE class and constructor
#include <string.h>
#include <FastLED.h>
#define DATA_PIN 19
#define NUM_LEDS 8
#define LED_TYPE WS2812B
CRGB leds[NUM_LEDS];
UTFTGLUE myGLCD(0,A2,A1,A3,A4,A0);//initiate screen
void setup()
{
  FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  randomSeed(analogRead(0));
  for(int i=0;i<NUM_LEDS;i++)
  {
    leds[i] = CRGB(0,0,0);
    FastLED.setBrightness(6);
    FastLED.show();
  }
  Serial.begin(9600);
  Serial.setTimeout(1);
  //Print the basic layout of the Display
  myGLCD.InitLCD(0);
  myGLCD.setFont(BigFont);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(0, 0, 319, 479);
  
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
  
  myGLCD.print("CPU TEMP: ", LEFT+15, 50);
  myGLCD.print("C ",290, 50);

  myGLCD.print("CPU LOAD: ", LEFT+15, 50+70);
  myGLCD.print("%", 290, 50+70);

  myGLCD.print("CPU POWER: ", LEFT+15, 50+70*2);
  myGLCD.print("W", 290, 50+70*2);
  
  myGLCD.print("GPU TEMP: ", LEFT+15, 50+70*3);
  myGLCD.print("C", 290, 50+70*3);
  
  myGLCD.print("GPU LOAD: ", LEFT+15, 50+70*4);
  myGLCD.print("%", 290, 50+70*4);

  myGLCD.print("GPU POWER: ", LEFT+15, 50+70*5);
  myGLCD.print("W", 290, 50+70*5);

 // myGLCD.print("USED SPACE: ", LEFT, 20+60*6);
 // myGLCD.print("%", 300, 20+60*6);
 // 
 // myGLCD.print("RAM USED: ", LEFT, 20+60*7);
 // myGLCD.print("%", 300, 20+60*7);

  myGLCD.setFont(SevenSegNumFont);

  myGLCD.setBrightness(0);
}

void loop()
{

  String str="";
  char k[31];
  char *token;
  int aux[6];
 long int t1 = millis();

while (!Serial.available()); //Get data from the PC
  str = Serial.readString();
  str.toCharArray(k,31);
  token = strtok(k, ","); //Conversions to split the string and get the data of each field.
  int i=0;
  while( token != NULL ) {
  aux[i]=atoi(token);
  i++;
  if(i>5)
    break;
  token = strtok(NULL, ",");
  }

for (int i = 0; i < (sizeof(aux)/sizeof(aux[0])); i++)
{
  myGLCD.printNumI(aux[i], 180, 45+70*i-10,3);

}
FastLED.clear();
  if(aux[0]<50)
  {
    
    leds[0] = CRGB(255,0,0);
    FastLED.setBrightness(6);
    FastLED.show();
  }
  if(aux[0]>=50&&aux[0]<60)
  {
    leds[0] = CRGB(255,0,0);
    leds[1] = CRGB(255,111,0);
    FastLED.setBrightness(6);
    FastLED.show();
  }
  if(aux[0]>=60&&aux[0]<80)
  {
    leds[0] = CRGB(255,0,0);
    leds[1] = CRGB(255,111,0);
    leds[2] = CRGB(255,255,0);
    FastLED.setBrightness(6);
    FastLED.show();
  }
  if(aux[0]>=80)
  {
    leds[0] = CRGB(255,0,0);
    leds[1] = CRGB(255,111,0);
    leds[2] = CRGB(255,255,0);
    leds[3] = CRGB(0,255,0);
    FastLED.setBrightness(6);
    FastLED.show();
  }

  if(aux[3]<50)
  {
    leds[4] = CRGB(255,0,0);
    FastLED.setBrightness(6);
    FastLED.show();
  }
  if(aux[3]>=50&&aux[3]<60)
  {
    leds[4] = CRGB(255,0,0);
    leds[5] = CRGB(255,111,0);
    FastLED.setBrightness(6);
    FastLED.show();
  }
  if(aux[3]>=60&&aux[3]<80)
  {
    leds[4] = CRGB(255,0,0);
    leds[5] = CRGB(255,111,0);
    leds[6] = CRGB(255,255,0);
    FastLED.setBrightness(6);
    FastLED.show();
  }
  if(aux[3]>=80)
  {
    leds[4] = CRGB(255,0,0);
    leds[5] = CRGB(255,111,0);
    leds[6] = CRGB(255,255,0);
    leds[7] = CRGB(0,255,0);
    FastLED.setBrightness(6);
    FastLED.show();
  }
  long int t2 = millis();
  //Serial.print("Time taken by the task: "); Serial.print(t2-t1); Serial.println(" milliseconds");
  //myGLCD.printNumI(t2-t1, 150, 15+60*7-10,4);
  delay (2500);
  
}