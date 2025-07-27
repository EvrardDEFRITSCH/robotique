#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ESP32Servo.h>

Adafruit_MPU6050 mpu;
Servo myServo;

float angleX = 90.0; // Position de départ du servo (à plat)
unsigned long lastTime = 0;

void setup() {
  Serial.begin(115200);
  mpu.begin();
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  myServo.attach(18); // PWM pin
  myServo.write(angleX); // Position initiale

  lastTime = millis();
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0; // delta temps en secondes
  lastTime = now;

  // Intégration de la vitesse angulaire autour de X
  angleX += g.gyro.x * dt;

  // Corriger pour garder le capteur horizontal
  float servoAngle = 90 - angleX; // Inversé selon ton montage
  servoAngle = constrain(servoAngle, 0, 180);

  myServo.write(servoAngle);

  Serial.print("Gyro X (°/s): ");
  Serial.print(g.gyro.x);
  Serial.print(" | angle estimé: ");
  Serial.print(angleX);
  Serial.print(" | servo: ");
  Serial.println(servoAngle);

  delay(20);
}
