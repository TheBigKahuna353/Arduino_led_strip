#include "FastLED.h"
#define NUM_LEDS 300
#define brightness 250
CRGB leds[NUM_LEDS];


void on_start() { 
  FastLED.addLeds<NEOPIXEL, 0>(leds, NUM_LEDS); FastLED.setBrightness(brightness);
  Serial.begin(9600);
  }
void func2() {

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green; FastLED.show();
    delay(5);
  }
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red; FastLED.show();
    delay(5);
  }
  delay(500);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(254); } }

int num = 0;

int hue = 0;
bool dir = true;
int i = 0;

void func4() {
  delay(6);
  for (int j = 0; j < 300; j++) {
    leds[j] = CRGB(255, 255, 255);
    leds[j].maximizeBrightness(i);
  }
  if (dir) {
    i++;
  } else {
    i--;
  }
  if (i == 0 | i == 150) {
    dir = !dir;
  }
  FastLED.show();
}

void func5() {
  fill_solid(leds, 300, CHSV(hue, 255, 255));
  if (hue == 255) {
    hue = 0;
  }
  hue++;
  delay(50);
  FastLED.show();
}

void on_clap() {
  if (num > 0) {
    leds[0] = CHSV(random(255), 255, 255);
    num--;
  }
  else {
    leds[0] = CRGB(0, 0, 0);
  }
  for (int j = 299; j > 0; j--) {
    leds[j] = leds[j-1];
  }
  FastLED.show();
}

void func3() {
  delay(500);
  if (i == 0) {
    fill_solid(leds, 300, CRGB(255, 0, 0));
  } else if (i == 1) {
    fill_solid(leds, 300, CRGB(0, 255, 0));
  } else if (i == 2) {
    fill_solid(leds, 300, CRGB(0, 0, 255));
  }
  if (i >= 2){
    i = -1;
  }
  i++;
  FastLED.show();
}

void black() {
  fill_solid(leds, 300, CRGB(0, 0, 0));
  FastLED.show();
}

int solid[3];

void fill(int r, int g, int b) {
  fill_solid(leds, 300, CRGB(r, g, b));
  FastLED.show();
}

void func1() {
  if (i == 0) {
    dir = true;
  }
  if (i == NUM_LEDS) {
    dir = false;
  }
  if (dir) {
    i++;
  }
  else {
    i--;
  }
  if (hue == 255) {
    hue = 0;
  }
  hue++;
  leds[i] = CHSV(hue, 255, 255);
  fadeall();
  FastLED.show();
}
