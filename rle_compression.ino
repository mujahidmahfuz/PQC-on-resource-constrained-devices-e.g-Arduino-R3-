const int DATA_SIZE = 1000;

byte original[DATA_SIZE];
byte compressed[DATA_SIZE * 2];

void setup() {
  Serial.begin(9600);

  // Highly compressible test data
  for (int i = 0; i < DATA_SIZE; i++) {
    original[i] = (i / 100) % 5;
  }

  int compressedSize = compressRLE(original, DATA_SIZE, compressed);

  Serial.println("=== Compression Test ===");

  Serial.print("Original Size: ");
  Serial.println(DATA_SIZE);

  Serial.print("Compressed Size: ");
  Serial.println(compressedSize);

  float ratio = (100.0 * compressedSize) / DATA_SIZE;

  Serial.print("Compression Ratio (%): ");
  Serial.println(ratio);
}

int compressRLE(byte* input, int length, byte* output) {

  int outIndex = 0;

  for (int i = 0; i < length; ) {

    byte value = input[i];
    byte count = 1;

    while ((i + count < length) &&
           (input[i + count] == value) &&
           (count < 255)) {
      count++;
    }

    output[outIndex++] = value;
    output[outIndex++] = count;

    i += count;
  }

  return outIndex;
}

void loop() {
}