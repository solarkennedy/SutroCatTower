void fillPlatform1With(CRGB color, int b) {
  for (int i = 0; i < NUM_PLATFORM_1_LEDS * 3; i++)
  {
    leds[platform_1_leds[i]] = color;
    leds[platform_1_leds[i]].fadeToBlackBy(255 - b);
  }
}

void fillPlatform2With(CRGB color, int b) {
  for (int i = 0; i < NUM_PLATFORM_2_LEDS * 3; i++)
  {
    leds[platform_2_leds[i]] = color;
    leds[platform_2_leds[i]].fadeToBlackBy(255 - b);
  }
}

void fillPlatform3With(CRGB color, int b) {
  for (int i = 0; i < NUM_PLATFORM_3_LEDS * 3; i++)
  {
    leds[platform_3_leds[i]] = color;
    leds[platform_3_leds[i]].fadeToBlackBy(255 - b);

  }
}

void fillPlatform4With(CRGB color, int b) {
  for (int i = 0; i < NUM_PLATFORM_4_LEDS * 3; i++)
  {
    leds[platform_4_leds[i]] = color;
    leds[platform_4_leds[i]].fadeToBlackBy(255 - b);

  }
}

void fillSpotsWith(CRGB color, int b) {
  for (int i = 0; i < NUM_SPOT_LEDS * 3; i++)
  {
    leds[spot_leds[i]] = color;
    leds[spot_leds[i]].fadeToBlackBy(255 - b);

  }
}

void fillAntennasWith(CRGB color, int b) {
  for (int i = 0; i < NUM_ANTENNA_LEDS * 3; i++)
  {
    leds[antenna_leds[i]] = color;
    leds[antenna_leds[i]].fadeToBlackBy(255 - b);
  }
}

void blackOut() {
  for (int i = 0 ; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}
