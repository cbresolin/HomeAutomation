/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 
#include <IRremote.h>
 
#define PanasonicAddress      0x4004     // Panasonic address (Pre data) 
#define PanasonicPower        0x100BCBD  // Panasonic Power button

#define JVCPower              0xC5E8

IRsend irsend;

void setup()
{
}

void loop() {
  irsend.sendPanasonic(PanasonicAddress,PanasonicPower); // This should turn your TV on and off
  
  irsend.sendJVC(JVCPower, 16,0); // hex value, 16 bits, no repeat
  delayMicroseconds(50); //
  irsend.sendJVC(JVCPower, 16,1); // hex value, 16 bits, repeat
  delayMicroseconds(50);
}
