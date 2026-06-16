#include <avr/pgmspace.h>
#include <Crypto.h>
#include <SHA256.h>

struct PQCArtifact {
  const byte* data;
  uint16_t size;
  const char* name;
};

const byte MLKEM_PK[800] PROGMEM = {1};
const byte MLKEM_SK[1632] PROGMEM = {2};
const byte MLDSA_SIG[2420] PROGMEM = {3};

PQCArtifact artifacts[] = {
  {MLKEM_PK, 800, "ML-KEM Public Key"},
  {MLKEM_SK, 1632, "ML-KEM Secret Key"},
  {MLDSA_SIG, 2420, "ML-DSA Signature"}
};

const int NUM_ARTIFACTS =
  sizeof(artifacts) / sizeof(artifacts[0]);

void printArtifactInfo(PQCArtifact &a) {

  Serial.println();

  Serial.print("Name: ");
  Serial.println(a.name);

  Serial.print("Size: ");
  Serial.print(a.size);
  Serial.println(" bytes");
}

void hashArtifact(PQCArtifact &a) {

  SHA256 sha256;

  const int CHUNK_SIZE = 32;

  byte buffer[CHUNK_SIZE];

  sha256.reset();

  unsigned long startTime = micros();

  for (int offset = 0; offset < a.size; offset += CHUNK_SIZE) {

    int bytesToRead = CHUNK_SIZE;

    if (offset + bytesToRead > a.size)
      bytesToRead = a.size - offset;

    for (int i = 0; i < bytesToRead; i++) {
      buffer[i] =
        pgm_read_byte(a.data + offset + i);
    }

    sha256.update(buffer, bytesToRead);
  }

  byte hash[32];

  sha256.finalize(hash, sizeof(hash));

  unsigned long endTime = micros();

  Serial.print("Hash: ");

  for (int i = 0; i < 32; i++) {

    if (hash[i] < 16)
      Serial.print("0");

    Serial.print(hash[i], HEX);
  }

  Serial.println();

  Serial.print("Time (us): ");
  Serial.println(endTime - startTime);
}

void setup() {

  Serial.begin(9600);

  for (int i = 0; i < NUM_ARTIFACTS; i++) {

    printArtifactInfo(artifacts[i]);

    hashArtifact(artifacts[i]);
  }
}

void loop() {
}
