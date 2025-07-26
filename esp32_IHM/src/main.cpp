#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

const char* ssid = "ESP_Gateway";
const char* password = "12345678";

WiFiServer server(8888);  // Port TCP

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Gateway IP : ");
  Serial.println(IP);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connecté !");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\n');
        Serial.print("Reçu : ");
        Serial.println(data);

        // (Optionnel) Réponse
        // client.println("ACK: " + data);
      }
    }
    client.stop();
    Serial.println("Client déconnecté");
  }
}