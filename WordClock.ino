#include <FastLED.h>
#define NUM_LEDS 10
#define DATA_PIN 4

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  for(int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Blue;
    FastLED.show();
    delay(10);
    leds[dot] = CRGB::Black;
    delay(30);
  }

}
