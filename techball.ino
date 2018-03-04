#include "FastLED.h"

#define NUM_LEDS 6

#define DATA_PIN 7
#define BRIGHTNESS_PIN 0
#define SPEED_PIN 1
#define MIN_BRIGHTNESS 32
#define MAX_BRIGHTNESS 255

CRGB leds[NUM_LEDS];

int index;
int count;
int cur_color;
int brightness;

void fade(){
    for(int i=0; i<NUM_LEDS; i++){ 
         leds[i].fadeToBlackBy( 20 );
    }
}

void blackout(){
    for(int i=0; i<NUM_LEDS; i++){ 
         leds[i]=CRGB::Black;
    }
}

void fade_out_by(int b){
    if(brightness > 0) {
        brightness -= b;
        FastLED.setBrightness(brightness);
    }
}

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB::Black;  
    }
    FastLED.show();
    count=0;
    randomSeed(analogRead(A0)); 
}

void march() {
    leds[count%NUM_LEDS] = CRGB::White;
}

void strobe() {
    if(count%2==0) {
        leds[index] = CRGB::White;
    } else {
        leds[index] = CRGB::Black;
    }
    if(count%10==0) {
        index = random(NUM_LEDS);
    }
}

void warm() {
    int which = random(NUM_LEDS);
    leds[which] += CHSV(255,255,255);
}

void loop() {
    int val = analogRead(BRIGHTNESS_PIN);
    //Serial.println(val);
    blackout();
    strobe();

    //fade();
    FastLED.show();
    count++;
    delay(1024-val);
}