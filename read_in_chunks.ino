#include <avr/pgmspace.h>

const byte signature[2420] PROGMEM = {
  1,2,3,4,5,6,7,8
};

const int CHUNK_SIZE = 32;

void setup() {

  Serial.begin(9600);

  byte buffer[CHUNK_SIZE];

  unsigned long total = 0;

  for (int offset = 0; offset < 2420; offset += CHUNK_SIZE) {

    int bytesToRead = CHUNK_SIZE;

    if (offset + bytesToRead > 2420)
      bytesToRead = 2420 - offset;

    for (int i = 0; i < bytesToRead; i++) {
      buffer[i] = pgm_read_byte(&signature[offset + i]);
      total += buffer[i];
    }
  }

  Serial.print("Processed bytes: ");
  Serial.println(2420);

  Serial.print("Checksum: ");
  Serial.println(total);
}

void loop() {
}