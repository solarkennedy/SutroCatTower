#include <FastLED.h>

#define DATA_PIN D4
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define LAMP_HOUR_BEGIN 18
#define LAMP_HOUR_END 22
#define BEACON_HOUR_BEGIN 22
#define BEACON_HOUR_END 6

#define NUM_ANTENNA_LEDS 1
#define NUM_SPOT_LEDS 12
#define NUM_PLATFORM_4_LEDS 40
#define NUM_PLATFORM_3_LEDS 14
#define NUM_PLATFORM_2_LEDS 34
#define NUM_PLATFORM_1_LEDS 22
#define NUM_LEDS (NUM_PLATFORM_1_LEDS + NUM_PLATFORM_2_LEDS + NUM_PLATFORM_3_LEDS + NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) * 3
CRGB leds[NUM_LEDS];

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  setupSerial();
  setupStrip();
  setupWifi();
  syncTimeFromWifi();
  sendPushNotification();
  digitalWrite(LED_BUILTIN, HIGH);
}

void figureOutWhatToShow()
{
  int offset, segment_end;

  offset = 0;
  segment_end = NUM_PLATFORM_1_LEDS * 3;
  for (int i = offset; i < segment_end; i++)
  {
    leds[i] = CRGB::Khaki;
  }

  offset = NUM_PLATFORM_1_LEDS * 3;
  segment_end = offset + (NUM_PLATFORM_2_LEDS * 3);
  for (int i = offset; i < segment_end; i++)
  {
    leds[i] = CRGB::Red;
  }

  offset = (NUM_PLATFORM_1_LEDS * 3) + (NUM_PLATFORM_2_LEDS * 3);
  segment_end = offset + (NUM_PLATFORM_3_LEDS * 3);
  for (int i = offset; i < segment_end; i++)
  {
    leds[i] = CRGB::Blue;
  }

  // platform 4
  offset = (NUM_PLATFORM_1_LEDS * 3) + (NUM_PLATFORM_2_LEDS * 3) + (NUM_PLATFORM_3_LEDS * 3) + (NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
  segment_end = offset + (NUM_PLATFORM_4_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    leds[i] = CRGB::Green;
  }
  offset = (NUM_PLATFORM_1_LEDS * 3) + (NUM_PLATFORM_2_LEDS * 3) + (NUM_PLATFORM_3_LEDS * 3) + (NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
  segment_end = offset + (NUM_PLATFORM_4_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    leds[i] = CRGB::Green;
  }
  offset = (NUM_PLATFORM_1_LEDS * 3) + (NUM_PLATFORM_2_LEDS * 3) + (NUM_PLATFORM_3_LEDS * 3) + (NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
  segment_end = offset + (NUM_PLATFORM_4_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    leds[i] = CRGB::Green;
  }

  // Spots
  offset = (NUM_PLATFORM_1_LEDS * 3) + (NUM_PLATFORM_2_LEDS * 3) + (NUM_PLATFORM_3_LEDS * 3) + (NUM_ANTENNA_LEDS);
  segment_end = offset + (NUM_SPOT_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    leds[i] = CRGB::White;
  }
  offset = (NUM_PLATFORM_1_LEDS * 3) + (NUM_PLATFORM_2_LEDS * 3) + (NUM_PLATFORM_3_LEDS * 3) + (NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
  segment_end = offset + (NUM_SPOT_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    leds[i] = CRGB::White;
  }
  offset = (NUM_PLATFORM_1_LEDS * 3) + (NUM_PLATFORM_2_LEDS * 3) + (NUM_PLATFORM_3_LEDS * 3) + (NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
  segment_end = offset + (NUM_SPOT_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    leds[i] = CRGB::White;
  }

  // Antenna
  offset = (NUM_PLATFORM_1_LEDS * 3) + (NUM_PLATFORM_2_LEDS * 3) + (NUM_PLATFORM_3_LEDS * 3);
  segment_end = offset + (NUM_ANTENNA_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    leds[i] = CRGB::Green;
  }
  offset = (NUM_PLATFORM_1_LEDS * 3) + (NUM_PLATFORM_2_LEDS * 3) + (NUM_PLATFORM_3_LEDS * 3) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
  segment_end = offset + (NUM_ANTENNA_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    leds[i] = CRGB::Green;
  }
  offset = (NUM_PLATFORM_1_LEDS * 3) + (NUM_PLATFORM_2_LEDS * 3) + (NUM_PLATFORM_3_LEDS * 3) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
  segment_end = offset + (NUM_ANTENNA_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    leds[i] = CRGB::Green;
  }

  /*
    if (h >= LAMP_HOUR_BEGIN && h < LAMP_HOUR_END) {
      setLampBrightness(255);
    } else {
      setLampBrightness(0);
    }

    if (h >= BEACON_HOUR_BEGIN && h <= 24) {
      setBeaconBrightness(255);
    } else if (h < BEACON_HOUR_END) {
      setBeaconBrightness(255);
    } else {
      setBeaconBrightness(0);
    }
  */
}

void loop()
{
  figureOutWhatToShow();
  FastLED.show();
  wifiEvents();
  EVERY_N_SECONDS(3600)
  {
    syncTimeFromWifi();
  }
}

void setupSerial()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println();
  Serial.println();
  const char compile_date[] = __DATE__ " " __TIME__;
  Serial.printf("ESP8266 Chip id = %08X\n", ESP.getChipId());
  Serial.printf("Sketch compiled %s\n", compile_date);
}

void setupStrip()
{
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
      .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  // Emperically this results in 50 watts from the wall
  set_max_power_in_milliwatts(57000);
}
