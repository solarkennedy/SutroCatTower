#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "secrets.h"

bool isKodiPlaying(bool previous)
{
  Serial.println("Querying Kodi..");
  HTTPClient http;
  http.setTimeout(500);
  http.begin(KODI_HOST, 8080, "/jsonrpc");
  http.addHeader("Content-Type", "application/json");
  uint16_t httpResponseCode;

  httpResponseCode = http.POST("{\"jsonrpc\": \"2.0\",\"method\": \"Player.GetActivePlayers\",\"id\": 1}");
  if (httpResponseCode > 0) {
    String response = http.getString();
    http.end();
    if (httpResponseCode == 65535) {
      return false;
    } else if (response == "{\"id\":1,\"jsonrpc\":\"2.0\",\"result\":[{\"playerid\":1,\"playertype\":\"internal\",\"type\":\"video\"}]}") {
      return true;
    } else if ( response == "{\"id\":1,\"jsonrpc\":\"2.0\",\"result\":[]}") {
      return false;
    } else {
      Serial.println("Not sure what this response is from Kodi:");
      Serial.println(httpResponseCode);
      Serial.println(response);
      return previous;
    }
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
    http.end();
    return previous;
  }

}
