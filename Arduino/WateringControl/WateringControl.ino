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

// Create aREST instance
aREST rest = aREST();

void setup()
{
  // initialize serial communication
  Serial.begin(SERIALBAUDRATE);

  // Expose functions to REST API

  // Give name and ID to device
  rest.set_id(DEVICEID);
  rest.set_name(DEVICENAME);
}

void loop()
{
  // Handle REST calls
  rest.handle(Serial);
}
