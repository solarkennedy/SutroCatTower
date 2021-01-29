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

void figureOutWhatToShow()
{
  int b = beatsin8(4);
  fillSpotsWith(CRGB::Red, b);
  fillAntennasWith(CRGB::Green, b);
  int c = beatsin8(3);
  fillPlatform4With(CRGB::Purple, c);
  int d = beatsin8(5);
  fillPlatform3With(CRGB::Blue, d);
  int e = beatsin8(6);
  fillPlatform2With(CRGB::Green, e);
  int f = beatsin8(4.5);
  fillPlatform1With(CRGB::White, f);
}


void reactToKodi() {
  EVERY_N_SECONDS(10)
  {
    KodiIsPlaying = isKodiPlaying(KodiIsPlaying);
  }

  if (KodiIsPlaying == true) {
    faderate = -20;
  } else {
    faderate = 10;
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
  FastLED.show();
  brightness = calculateBrightness(brightness, faderate);
  FastLED.setBrightness(brightness);
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
}
