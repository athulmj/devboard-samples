#include <WiFi.h>
#include <HTTPClient.h>
#include <esp_wifi.h>

// Replace with your network credentials
const char* ssid = "ssid";
const char* password = "password";

// Target endpoint (Public test API returning a mock JSON object)
const char* url = "http://typicode.com";

void setup() {
  // ESP32-C3 Super Mini requires a small delay for the USB CDC Serial to initialize
  Serial.begin(115200);
  delay(2000); 
  
  Serial.println("\n--- ESP32-C3 Wi-Fi Test ---");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  esp_wifi_set_max_tx_power(40); 

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check Wi-Fi connection status before making a request
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    Serial.println("\nFetching data from internet...");
    http.begin(url); // Initialize connection

    int httpResponseCode = http.GET(); // Send the request
    
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      
      String payload = http.getString(); // Retrieve online data
      Serial.println("Online Data Received:");
      Serial.println(payload);
    } 
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    
    http.end(); // Free resources
  } else {
    Serial.println("Wi-Fi Disconnected");
  }

  // Fetch data every 10 seconds
  delay(10000);
}
