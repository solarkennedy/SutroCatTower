void selfTestPattern() {

  fillPlatform1With(CRGB::Blue);
  FastLED.delay(1000);
  blackOut();

  fillPlatform2With(CRGB::Yellow);
  FastLED.delay(1000);
  blackOut();

  fillPlatform3With(CRGB::Green);
  FastLED.delay(1000);
  blackOut();

  fillPlatform4With(CRGB::Orange);
  FastLED.delay(1000);
  blackOut();

  fillSpotsWith(CRGB::White);
  FastLED.delay(1000);
  blackOut();

  fillAntennasWith(CRGB::Green);
  FastLED.delay(1000);
  blackOut();

}
