#include <avr/pgmspace.h>

const byte signature[2420] PROGMEM = {
  1,2,3,4,5,6,7,8
};

void setup() {
  Serial.begin(9600);

  byte b = pgm_read_byte(&signature[0]);

  Serial.println(b);
}

void loop() {}