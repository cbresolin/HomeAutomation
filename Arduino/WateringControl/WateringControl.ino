/*****************************************
* name: Watering Control
* function:
* Controls a switch to enable or disable watering according
* to environment (% humidity, temperature, seasons...)
*****************************************/

// Libraries
#include <Wire.h>
#include <aREST.h>

// Defines
#define SERIALBAUDRATE 9600
#define DEVICENAME "Watering Control"
#define DEVICEID "02"

#define VBUSLANE1 22
#define VBUSLANE2 28
#define VBUSLANE3 29

#define POWERLANE1 40
#define POWERLANE2 38
#define POWERLANE3 50

#define SWITCHLANE1 36
#define SWITCHLANE2 34
#define SWITCHLANE3 52

// Create aREST instance
aREST rest = aREST();

void setup()
{
  // initialize serial communication
  Serial.begin(SERIALBAUDRATE);

  // Give name and ID to device
  rest.set_id(DEVICEID);
  rest.set_name(DEVICENAME);

  // Set pin modes
  pinMode(VBUSLANE1, OUTPUT);
  pinMode(VBUSLANE2, OUTPUT);
  pinMode(VBUSLANE3, OUTPUT);

  pinMode(POWERLANE1, OUTPUT);
  pinMode(POWERLANE2, OUTPUT);
  pinMode(POWERLANE3, OUTPUT);

  pinMode(SWITCHLANE1, OUTPUT);
  pinMode(SWITCHLANE2, OUTPUT);
  pinMode(SWITCHLANE3, OUTPUT);
}

void loop()
{
  // Handle REST calls
  rest.handle(Serial);
}
