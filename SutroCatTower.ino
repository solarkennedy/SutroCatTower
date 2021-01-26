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
#define NUM_LOWER_LEDS (NUM_PLATFORM_1_LEDS + NUM_PLATFORM_2_LEDS + NUM_PLATFORM_3_LEDS) * 3
CRGB leds[NUM_LEDS];
int platform_1_leds[NUM_PLATFORM_1_LEDS * 3];
int platform_2_leds[NUM_PLATFORM_2_LEDS * 3];
int platform_3_leds[NUM_PLATFORM_3_LEDS * 3];
int platform_4_leds[NUM_PLATFORM_4_LEDS * 3];
int spot_leds[NUM_SPOT_LEDS * 3];
int antenna_leds[NUM_ANTENNA_LEDS * 3];

CRGBPalette16 platform_1_currentPalette;
CRGBPalette16 platform_1_targetPalette;
CRGBPalette16 platform_2_currentPalette;
CRGBPalette16 platform_2_targetPalette;
CRGBPalette16 platform_3_currentPalette;
CRGBPalette16 platform_3_targetPalette;

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
  Serial.println("Platform 1");
  plasma(platform_1_leds, NUM_PLATFORM_1_LEDS * 3, platform_1_currentPalette, platform_1_targetPalette);
  Serial.println("Platform 2");
  plasma(platform_2_leds, NUM_PLATFORM_2_LEDS * 3, platform_2_currentPalette, platform_2_targetPalette);
  Serial.println("Platform 3");
  plasma(platform_3_leds, NUM_PLATFORM_3_LEDS * 3, platform_3_currentPalette, platform_3_targetPalette);

  // for (int i = 0; i < NUM_PLATFORM_4_LEDS * 3; i++)
  // {
  //   leds[platform_4_leds[i]] = CRGB::DarkRed;
  // }
  // for (int i = 0; i < NUM_SPOT_LEDS * 3; i++)
  // {
  //   leds[spot_leds[i]] = CRGB::Purple;
  // }
  // for (int i = 0; i < NUM_ANTENNA_LEDS * 3; i++)
  // {
  //   leds[antenna_leds[i]] = CRGB::Orange;
  // }
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

void setupPlatform1LEDs()
{
  int index = 0;
  int offset = 0;
  int segment_end = NUM_PLATFORM_1_LEDS * 3;
  for (int i = offset; i < segment_end; i++)
  {
    platform_1_leds[index] = i;
    index++;
  }
}

void setupPlatform2LEDS()
{
  int index = 0;
  int offset = NUM_PLATFORM_1_LEDS * 3;
  int segment_end = offset + (NUM_PLATFORM_2_LEDS * 3);
  for (int i = offset; i < segment_end; i++)
  {
    platform_2_leds[index] = i;
    index++;
  }
}

void setupPlatform3LEDS()
{
  int index = 0;
  int offset = (NUM_PLATFORM_1_LEDS * 3) + (NUM_PLATFORM_2_LEDS * 3);
  int segment_end = offset + (NUM_PLATFORM_3_LEDS * 3);
  for (int i = offset; i < segment_end; i++)
  {
    platform_3_leds[index] = i;
    index++;
  }
}

void setupPlatform4LEDS()
{
  int index = 0;
  int offset = NUM_LOWER_LEDS + (NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
  int segment_end = offset + (NUM_PLATFORM_4_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    platform_4_leds[index] = i;
    index++;
  }
  offset = NUM_LOWER_LEDS + (NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
  segment_end = offset + (NUM_PLATFORM_4_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    platform_4_leds[index] = i;
    index++;
  }
  offset = NUM_LOWER_LEDS + (NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) * 2;
  segment_end = offset + (NUM_PLATFORM_4_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    platform_4_leds[index] = i;
    index++;
  }
}

void setupSpotLEDS()
{
  int index = 0;
  int offset = NUM_LOWER_LEDS + (NUM_ANTENNA_LEDS);
  int segment_end = offset + (NUM_SPOT_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    spot_leds[index] = i;
    index++;
  }
  offset = NUM_LOWER_LEDS + (NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
  segment_end = offset + (NUM_SPOT_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    spot_leds[index] = i;
    index++;
  }
  offset = NUM_LOWER_LEDS + (NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) * 2;
  segment_end = offset + (NUM_SPOT_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    spot_leds[index] = i;
    index++;
  }
}

void setupAntennaLEDS()
{
  // Antenna
  int index = 0;
  int offset = NUM_LOWER_LEDS;
  int segment_end = offset + (NUM_ANTENNA_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    antenna_leds[index] = i;
    index++;
  }
  offset = NUM_LOWER_LEDS + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
  segment_end = offset + (NUM_ANTENNA_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    antenna_leds[index] = i;
    index++;
  }
  offset = NUM_LOWER_LEDS + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) * 2;
  segment_end = offset + (NUM_ANTENNA_LEDS);
  for (int i = offset; i < segment_end; i++)
  {
    antenna_leds[index] = i;
    index++;
  }
}

void setupStrip()
{
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
      .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  // Emperically this results in 50 watts from the wall
  set_max_power_in_milliwatts(57000);

  setupPlatform1LEDs();
  setupPlatform2LEDS();
  setupPlatform3LEDS();
  setupPlatform4LEDS();
  setupSpotLEDS();
  setupAntennaLEDS();
}
