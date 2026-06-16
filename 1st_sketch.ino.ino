#include <Crypto.h>
#include <SHA256.h>

SHA256 sha256;

void setup() {
  Serial.begin(9600);

  const char* message = "HELLO PQC";

  sha256.reset();
  sha256.update((const uint8_t*)message, strlen(message));

  uint8_t hash[32];
  sha256.finalize(hash, sizeof(hash));

  Serial.println("SHA-256:");

  for (int i = 0; i < 32; i++) {
    if (hash[i] < 16)
      Serial.print("0");

    Serial.print(hash[i], HEX);
  }

  Serial.println();
}

void loop() {
}