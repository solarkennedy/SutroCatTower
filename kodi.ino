#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

bool isKodiPlaying()
{
    Serial.println("Querying Kodi..");
    HTTPClient http;
    http.begin("10.0.2.10", 8080, "/jsonrpc");
    http.addHeader("Content-Type", "application/json");
    uint16_t httpResponseCode;

    httpResponseCode = http.POST("{\"jsonrpc\": \"2.0\",\"method\": \"Player.GetActivePlayers\",\"id\": 1}");
    if (httpResponseCode > 0)
    {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
    }
    else
    {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }
    http.end();

    //{"id":1,"jsonrpc":"2.0","result":[{"playerid":1,"playertype":"internal","type":"video"}]}
    //{"id":1,"jsonrpc":"2.0","result":[]}
}