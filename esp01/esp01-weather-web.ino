// Install: DHT sensor library by Adafruit

// components
// ESP-01
// ESP-01S DHT11 Temperature Humidity Sensor module

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);

// AP credentials
const char* ap_ssid = "ESP01_Weather";
const char* ap_password = "12345678";

void handleRoot() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float hi = dht.computeHeatIndex(t, h, false);

  String html = R"(
    <!DOCTYPE html><html>
    <head>
      <meta charset='UTF-8'>
      <meta http-equiv='refresh' content='5'>
      <meta name='viewport' content='width=device-width, initial-scale=1'>
      <title>ESP-01S Weather</title>
      <style>
        body { font-family: Arial; text-align: center; background: #1a1a2e; color: white; }
        .card { display: inline-block; background: #16213e; border-radius: 20px;
                padding: 30px; margin: 10px; width: 150px; }
        .val { font-size: 2.5em; font-weight: bold; color: #00d4ff; }
        .lbl { font-size: 0.9em; color: #aaa; margin-top: 5px; }
      </style>
    </head>
    <body>
      <h2>🌡️ ESP-01S Weather Station</h2>
      <div class='card'><div class='val'>)" + String(t,1) + R"(°C</div><div class='lbl'>Temperature</div></div>
      <div class='card'><div class='val'>)" + String(h,1) + R"(%</div><div class='lbl'>Humidity</div></div>
      <div class='card'><div class='val'>)" + String(hi,1) + R"(°C</div><div class='lbl'>Heat Index</div></div>
      <p style='color:#555'>Auto-refresh every 5 seconds</p>
    </body></html>
  )";

  server.send(200, "text/html", html);
}

void handleJSON() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  String json = "{\"temp\":" + String(t) + ",\"humidity\":" + String(h) + "}";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Start Access Point
  WiFi.softAP(ap_ssid, ap_password);

  Serial.println("AP Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());  // Usually 192.168.4.1

  server.on("/", handleRoot);
  server.on("/json", handleJSON);
  server.begin();
}

void loop() {
  server.handleClient();
}