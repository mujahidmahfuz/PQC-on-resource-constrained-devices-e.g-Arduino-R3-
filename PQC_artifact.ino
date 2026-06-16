#include <avr/pgmspace.h>

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

void readChunk(
    PQCArtifact &a,
    int offset,
    byte* buffer,
    int chunkSize)
{
  for (int i = 0; i < chunkSize; i++) {

    if (offset + i >= a.size)
      return;

    buffer[i] =
      pgm_read_byte(a.data + offset + i);
  }
}

void setup() {

  Serial.begin(9600);

  for (int i = 0; i < NUM_ARTIFACTS; i++) {

    printArtifactInfo(artifacts[i]);
  }
}

void loop() {}

