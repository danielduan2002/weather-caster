#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
 
const char* ssid = "Alanda";
const char* password =  "12345678";
 
const String endpoint = "https://api.openweathermap.org/data/2.5/weather?id=5327684&units=imperial&appid=";
const String key = "eb473f77c86ef6f4d94c3605fec1dd3b";

WiFiClientSecure client;
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  client.setInsecure();
 
}
 
void loop() {
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
      
    // Your Domain name with URL path or IP address with path
    http.begin(client, endpoint + key);
    
    // Send HTTP POST request
    int httpResponseCode = http.GET();
    
    String payload = "{}"; 
    
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      payload = http.getString();
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  
    Serial.println(payload);

    JSONVar responseObject = JSON.parse(payload);

    if (JSON.typeof(responseObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
    }

    // get the rain data and temperature data hell yea!
    // ["weather"][0]["main"] -> "Rainy"
    // ["main"]["feels_like"] -> temperature
  }
 
}
