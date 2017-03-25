

/*****************************************
* name:HC-05 BT Module
* function:
*****************************************/
/****************************************/
#include <SoftwareSerial.h>

#define PINRX 2
#define PINTX 3
#define SERIALBAUDRATE 9600

SoftwareSerial btserial(PINRX, PINTX);


void setup()
{
  // initialize serial communication:
  btserial.begin(SERIALBAUDRATE);
  Serial.begin(SERIALBAUDRATE);
}

void loop()
{
  if (btserial.available())
  {
    Serial.write(btserial.read());
  }

  if (Serial.available())
  {
    btserial.write(Serial.read());
  }
}
