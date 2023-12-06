#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
 
const char* ssid     = "Daniel";
const char* password = "danielduan";

String openWeatherMapApiKey = "ca0d27fd76c78cdf8b0df60b41ccda7b";
String cityID = "5327684";
String serverPath = "https://api.openweathermap.org/data/2.5/weather?id=" + cityID + "&units=imperial" + "&appid=" + openWeatherMapApiKey;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // SETS TO STATION MODE!
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }  
  Serial.print("IP is ");
  Serial.println(WiFi.localIP());

  HTTPClient http;

  // Your Domain name with URL path or IP address with path
  http.begin(serverPath.c_str());
  
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

  JSONVar my_obj = JSON.parse(payload);
  
  if (JSON.typeof(my_obj) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }
  
  Serial.println(my_obj["weather"][0]["main"]);

  float cold = 55;
  float hot = 65;

}

void loop() {
}
