#include <NewPing.h>

#define TRIGGER_PIN  3  
#define ECHO_PIN     2  
#define MAX_DISTANCE 200
#define SERIALBAUDRATE 9600

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void setup() {
  Serial.begin(SERIALBAUDRATE); 
}

void loop() {
  delay(500);                     
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println(" cm");
}
