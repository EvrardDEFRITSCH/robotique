#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "ESP_Gateway";      // Nom du Wi-Fi créé par le Gateway
const char* password = "12345678";

const char* host = "192.168.4.1";      // IP fixe du SoftAP ESP32 Gateway
const uint16_t port = 8888;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connexion au WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connecté !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());

  Serial.print("Connexion au serveur ");
  Serial.print(host);
  Serial.print(":");
  Serial.println(port);

  if (!client.connect(host, port)) {
    Serial.println("Échec de connexion au serveur");
    return;
  }

  Serial.println("Connecté au serveur !");
}

void loop() {
  if (client.connected()) {
    client.println("Hello from client");
    Serial.println("Message envoyé !");
  } else {
    Serial.println("Déconnecté du serveur. Tentative de reconnexion...");
    if (client.connect(host, port)) {
      Serial.println("Reconnecté !");
    } else {
      Serial.println("Échec de reconnexion");
    }
  }

  delay(2000);
}