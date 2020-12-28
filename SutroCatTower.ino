#include <FastLED.h>

#define DATA_PIN 0
#define NUM_LEDS 100
#define LED_TYPE WS2812B
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

#define LAMP_HOUR_BEGIN 18
#define LAMP_HOUR_END 22
#define BEACON_HOUR_BEGIN 22
#define BEACON_HOUR_END 6

const uint8 BEACON_LEDS[] = {0,1};
const uint8 BEACON_ANTENNA_LEDS[] = {100,101,103};

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  setupSerial();
  setupStrip();
  setupWifi();
  syncTimeFromWifi();
  digitalWrite(LED_BUILTIN, HIGH);
}

void figureOutWhatToShow()
{
  uint8 h = getHour();

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
}

void loop()  {
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
}
