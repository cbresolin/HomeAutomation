/*****************************************
* name:LM35 Temperature Sensor
* function:
* LM35 output voltage has a linear relation with the Celsius temperature, output of 0 v when 0 ℃, 
* every increase 1 ℃, the output voltage increase 10 mv
*****************************************/
/****************************************/
#include <Wire.h>
#include <SoftwareSerial.h>

#define ML35PIN A0 
#define REDPIN 4
#define GREENPIN 5
#define BLUEPIN 6
#define COLD 18
#define HOT 22

#define SERIALBAUDRATE 9600
#define BTRX 2
#define BTTX 3

SoftwareSerial btserial(BTRX, BTTX);

float temp = 0;
float lmVal = 0;

void setup()
{
  // initialize serial communication
  Serial.begin(SERIALBAUDRATE);
  
  // initialize BT serial communication
  btserial.begin(SERIALBAUDRATE);

  // Set RGB LED pin modes
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  // improve measure precision by reducing measure range to 1.1V instead of 5V
  analogReference(INTERNAL);

  switchoff_led();
}

void set_led_red()
{
  analogWrite(REDPIN, 255);
  analogWrite(BLUEPIN, 0);
  analogWrite(GREENPIN, 0);
}

void set_led_blue()
{
  analogWrite(REDPIN, 0);
  analogWrite(BLUEPIN, 255);
  analogWrite(GREENPIN, 0);
}

void set_led_green()
{
  analogWrite(REDPIN, 0);
  analogWrite(BLUEPIN, 0);
  analogWrite(GREENPIN, 255);
}

void switchoff_led()
{
  analogWrite(REDPIN, 0);
  analogWrite(BLUEPIN, 0);
  analogWrite(GREENPIN, 0);
}

void loop()
{
  lmVal = analogRead(ML35PIN);
  temp = (lmVal * (1.1 / 1023.0) * 100.0) - 1;
  
  btserial.print("Temperature: ");
  btserial.print(temp);
  btserial.println(" C");

  if (temp < COLD)
      set_led_blue();
  else if (temp >= COLD && temp < HOT)
      set_led_green();
  else if (temp >= HOT)
      set_led_red();
  
  delay(100);
}
