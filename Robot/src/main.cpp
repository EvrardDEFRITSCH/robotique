#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

float X, Y, Z; // Variables pour stocker les valeurs d'accélération

float alpha = 0.05;  // Plus petit = plus lent (~1 Hz visuel)
float ax_filtered = 0;
float ay_filtered = 0;
float az_filtered = 0;


void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // Attente du port série

  if (!mpu.begin()) {
    Serial.println("Échec de détection du MPU6050");
    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 détecté !");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  X=g.gyro.x; // Initialisation des variables
  Y=g.gyro.y;
 
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);


  Serial.print("Accel X: ");
  Serial.print(alpha*g.gyro.x+0-(alpha*X));
  Serial.print(", Y: ");
  Serial.println(alpha*g.gyro.y+0-(alpha*Y));
  //Serial.print(", Z: ");
  //Serial.println(a.acceleration.z-Z);
  delay(200);
}