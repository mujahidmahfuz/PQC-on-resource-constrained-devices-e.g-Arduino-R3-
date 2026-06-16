#include <Crypto.h>
#include <SHA256.h>
#include <avr/pgmspace.h>

SHA256 sha256;

//const byte signature[2420] PROGMEM = {
//  1,2,3,4,5,6,7,8
//};

const byte signature[2420] PROGMEM = { };  // chunk size will produce the same hash

const int CHUNK_SIZE = 128;  // try 16, 32, 64, 128 for optimizing time and memory

void setup() {

  Serial.begin(9600);

  sha256.reset();

  unsigned long startTime = micros();

  byte buffer[CHUNK_SIZE];

  for (int offset = 0; offset < 2420; offset += CHUNK_SIZE) {

    int bytesToRead = CHUNK_SIZE;

    if (offset + bytesToRead > 2420)
      bytesToRead = 2420 - offset;

    for (int i = 0; i < bytesToRead; i++) {
      buffer[i] = pgm_read_byte(&signature[offset + i]);
    }

    sha256.update(buffer, bytesToRead);
  }

  byte hash[32];

  sha256.finalize(hash, sizeof(hash));

  unsigned long endTime = micros();

  Serial.println("SHA-256:");

  for (int i = 0; i < 32; i++) {

    if (hash[i] < 16)
      Serial.print("0");

    Serial.print(hash[i], HEX);
  }

  Serial.println();

  Serial.print("Time (us): ");
  Serial.println(endTime - startTime);
}

void loop() {
}