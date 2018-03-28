#include "FastLED.h"

#define NUM_LEDS 10

#define DATA_PIN 7
#define BRIGHTNESS_PIN 0
#define SPEED_PIN 1
#define MIN_BRIGHTNESS 32
#define MAX_BRIGHTNESS 255
#define PERIOD 150

CRGB leds[NUM_LEDS];

int index;
int index2;
int count;
int color;
int color2;
int brightness;

void fade(){
    for(int i=0; i<NUM_LEDS; i++){
         leds[i].fadeToBlackBy( 1 );
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

void loop() {
    fade();
    arc_compliments();
    FastLED.show();
    count++;
    delay(10);
}

void arc_compliments() {
    if(count%PERIOD==0) {
        index = index2;
        index2 = random(NUM_LEDS);
        if (index2 == index) index2 = (index2+NUM_LEDS/2)%NUM_LEDS;
        color = color2;
        color2 = (color2+10)%255;
    }
    leds[index]+=CHSV(color,255,25);
    if(count%7 < 2) {
        leds[index2]+=CHSV(color2,(count%PERIOD)*(255/PERIOD),(125+random8()/6)-count%(PERIOD/7));
    } else {
        leds[index2].fadeToBlackBy( 45 );
    }
}
