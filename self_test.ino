void selfTestPattern() {

  fillPlatform1With(CRGB::Blue, 255);
  FastLED.delay(1000);
  blackOut();

  fillPlatform2With(CRGB::Yellow, 255);
  FastLED.delay(1000);
  blackOut();

  fillPlatform3With(CRGB::Green, 255);
  FastLED.delay(1000);
  blackOut();

  fillPlatform4With(CRGB::Purple, 255);
  FastLED.delay(1000);
  blackOut();

  fillSpotsWith(CRGB::White, 255);
  FastLED.delay(1000);
  blackOut();

  fillAntennasWith(CRGB::Green, 255);
  FastLED.delay(1000);
  blackOut();

  FastLED.delay(1000);
}
