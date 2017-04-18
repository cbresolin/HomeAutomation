// Libraries
#include <Wire.h>
#include <aREST.h>

// Defines
#define ML35PIN A0 
#define REDPIN 4
#define GREENPIN 5
#define BLUEPIN 6
#define SERIALBAUDRATE 9600
#define DEVICENAME "BT Weather Station"
#define DEVICEID "01"

// Create aREST instance
aREST rest = aREST();

// Variables to be exposed to the API
float temperature;

void setup()
{
  // initialize serial communication
  Serial.begin(SERIALBAUDRATE);

  // Expose variables to REST API
  rest.variable("temperature",&temperature);

  // Expose functions to REST API
  rest.function("red",set_led_red);
  rest.function("green",set_led_green);
  rest.function("blue",set_led_blue);
  rest.function("off",switchoff_led);

  // Give name and ID to device
  rest.set_id(DEVICEID);
  rest.set_name(DEVICENAME);

  // Set RGB LED pin modes
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  // improve temperature measure precision
  // by reducing measure range to 1.1V instead of 5V
  analogReference(INTERNAL);

  switchoff_led();
}

int set_led_red()
{
  analogWrite(REDPIN, 255);
  analogWrite(BLUEPIN, 0);
  analogWrite(GREENPIN, 0);
  return 0;
}

int set_led_blue()
{
  analogWrite(REDPIN, 0);
  analogWrite(BLUEPIN, 255);
  analogWrite(GREENPIN, 0);
  return 0;
}

int set_led_green()
{
  analogWrite(REDPIN, 0);
  analogWrite(BLUEPIN, 0);
  analogWrite(GREENPIN, 255);
  return 0;
}

int switchoff_led()
{
  analogWrite(REDPIN, 0);
  analogWrite(BLUEPIN, 0);
  analogWrite(GREENPIN, 0);
  return 0;
}

void loop()
{
  temperature = (analogRead(ML35PIN) * (1.1 / 1023.0) * 100.0) - 1;

  // Handle REST calls
  rest.handle(Serial);
}
