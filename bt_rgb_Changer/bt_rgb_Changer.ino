#include <SoftwareSerial.h>
#include <FastLED.h>
#include <ArduinoJson.h>

SoftwareSerial btSerial(0,1);
// How many leds in your strip?
#define NUM_LEDS 24

#define DATA_PIN 8
#define CLOCK_PIN 7

// Define the array of leds
CRGB rgbLeds[NUM_LEDS];

int r = 56;
int b = 100;
int g = 56;
int br = 75;

String myString = "";
int pinGND = 4;
int pinVCC = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("RGB program started");
  btSerial.begin(9600);

  pinMode(pinGND, OUTPUT);
  pinMode(pinVCC, OUTPUT);
  digitalWrite(pinGND, LOW);
  digitalWrite(pinVCC, HIGH);
  
  //Setup the LEDS
  FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(rgbLeds, NUM_LEDS);
  rgbLeds[0] = CRGB(r, g, b);
  FastLED.show(); 
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(btSerial.available()){
    myString = btSerial.readString();
    delay(500);
    Serial.print("Received Len ");
    Serial.println(myString.length());
    char ch[52];
    myString.toCharArray(ch, 52);
    DynamicJsonBuffer  jsonBuffer(320);
    JsonObject& root = jsonBuffer.parseObject(ch);
    Serial.println(ch);
    
    r = root["red"];
    b = root["blue"];
    g = root["green"];
    br = root["brightness"];

    Serial.println(r);Serial.println(b); Serial.println(g);

    rgbLeds[0].setRGB(r, g, b);
    FastLED.setBrightness(br);
    FastLED.show();
  }
}
