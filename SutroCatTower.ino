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

bool KodiIsPlaying = false;
bool RemoteToggle = true;
int brightness = 0;
int faderate = 5;

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
  selfTestPattern();
}

int calculateBrightness(int b, int rate) {
  EVERY_N_MILLISECONDS(200) {
    b += rate;
  }
  if (b < 0) {
    b = 0;
  } else if (b > 255) {
    b = 255;
  }
  return b;
}

int getWhiteScaleForHour() {
  uint8 h = getHour();
  uint8 wakeup_hour = 8;
  uint8 night_wakeup_hour = 18;

  if (h >= 0 && h < wakeup_hour) {
    return 0;
  } else if (h >= wakeup_hour && h < wakeup_hour + 1) {
    return map(getMinuteOfTheHour() * 60 + getSecond(), 0, 3600, 0, 255);
  } else if (h >= wakeup_hour + 1 && h < wakeup_hour + 2) {
    return 255;
  } else if (h >= wakeup_hour + 2 && h < wakeup_hour + 3) {
    return map(getMinuteOfTheHour() * 60 + getSecond(), 0, 3600, 255, 0);
  } else if (h >= wakeup_hour + 3 && h < night_wakeup_hour) {
    return 0;
  } else if (h >= night_wakeup_hour && h < night_wakeup_hour + 1) {
    return map(getMinuteOfTheHour() * 60 + getSecond(), 0, 3600, 0, 255);
  } else if (h >= night_wakeup_hour + 1 && h < night_wakeup_hour + 3) {
    return 255;
  } else if (h >= night_wakeup_hour + 3 && h < night_wakeup_hour + 4) {
    return map(getMinuteOfTheHour() * 60 + getSecond(), 0, 3600, 255, 0);
  } else {
    return 0;
  }
}

void figureOutWhatToShow()
{
  int b = beatsin8(4);
  fillAntennasWith(CRGB::Green, b);
  fillSpotsWith(CRGB::Red, b);

  int white_scale = getWhiteScaleForHour();
  fillPlatform3With(CRGB::FairyLight, white_scale / 2);
  fillPlatform2With(CRGB::FairyLight, white_scale / 4);
  fillPlatform1With(CRGB::FairyLight, white_scale / 2);
}


void reactToKodi() {
  EVERY_N_SECONDS(10)
  {
    KodiIsPlaying = isKodiPlaying(KodiIsPlaying);
  }

  if (KodiIsPlaying == true || RemoteToggle == false) {
    faderate = -15;
  } else {
    faderate = 8;
  }
}

void wifiMaintenance() {
  EVERY_N_SECONDS(3600)
  {
    syncTimeFromWifi();
  }
  wifiEvents();
}

void loop()
{
  reactToKodi();
  wifiMaintenance();
  figureOutWhatToShow();
  brightness = calculateBrightness(brightness, faderate);
  FastLED.setBrightness(brightness);
  FastLED.show();
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

  setupPlatform1LEDs();
  setupPlatform2LEDS();
  setupPlatform3LEDS();
  setupPlatform4LEDS();
  setupSpotLEDS();
  setupAntennaLEDS();
  brightness = 0;
}
