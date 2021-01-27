void fillPlatform1With(CRGB color) {
  for (int i = 0; i < NUM_PLATFORM_1_LEDS * 3; i++)
  {
    leds[platform_1_leds[i]] = color;
  }
}

void fillPlatform2With(CRGB color) {
  for (int i = 0; i < NUM_PLATFORM_2_LEDS * 3; i++)
  {
    leds[platform_2_leds[i]] = color;
  }
}

void fillPlatform3With(CRGB color) {
  for (int i = 0; i < NUM_PLATFORM_3_LEDS * 3; i++)
  {
    leds[platform_3_leds[i]] = color;
  }
}

void fillPlatform4With(CRGB color) {
  for (int i = 0; i < NUM_PLATFORM_4_LEDS * 3; i++)
  {
    leds[platform_4_leds[i]] = color;
  }
}

void fillSpotsWith(CRGB color) {
  for (int i = 0; i < NUM_SPOT_LEDS * 3; i++)
  {
    leds[spot_leds[i]] = color;
  }
}

void fillAntennasWith(CRGB color) {
  for (int i = 0; i < NUM_ANTENNA_LEDS * 3; i++)
  {
    leds[antenna_leds[i]] = color;
  }
}

void blackOut() {
  for (int i = 0 ; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}
