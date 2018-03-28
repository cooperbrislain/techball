#include "FastLED.h"

#define NUM_LEDS 12

#define DATA_PIN 7
#define BRIGHTNESS_PIN 0
#define SPEED_PIN 1
#define MIN_BRIGHTNESS 32
#define MAX_BRIGHTNESS 255

CRGB leds[NUM_LEDS];

int index;
int index2;
int count;
int color;
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

void setup() {
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

void flare() {
    if(count%20==0) {
        index = random(NUM_LEDS);
        color = random8();
    }
    leds[index]+=CHSV(color,255,55);
}

void flare_compliments() {
    if(count%20==0) {
        index = random(NUM_LEDS);
        index2 = random(NUM_LEDS);
        if (index2 == index) index2 = (index2+NUM_LEDS/2)%NUM_LEDS;
        color = random8();
    }
    leds[index]+=CHSV(color,255,55);
    leds[index2]+=CHSV((color+128)%255,255,55);
}

void warm() {
    int which = random(NUM_LEDS);
    leds[which] += CHSV(255,255,255);
}

void loop() {
    flare_compliments();
    fade();
    FastLED.show();
    count++;
    delay(90);
}
