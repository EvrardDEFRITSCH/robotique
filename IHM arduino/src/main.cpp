#include <Arduino.h>
#include <Ultrasonic.h>

Ultrasonic ultrasonic(9, 10);  // Trig = 9, Echo = 10


void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);

}
void testFonction(){
  
      char cmd = Serial.read();
    if (cmd == '1') {
      digitalWrite(13, HIGH); // Allume la LED
    } else if (cmd == '0') {
      digitalWrite(13, LOW);  // Éteint la LED
    } else if (cmd== '3'){
      digitalWrite(13, HIGH); // Allume la LED
      delay(500);
      digitalWrite(13, LOW);  // Éteint la LED
      delay(500);
    }
}
void loop() {
  float distance = ultrasonic.read(); // en cm
  Serial.println(distance);

  delay(500);
  testFonction();
  
}

