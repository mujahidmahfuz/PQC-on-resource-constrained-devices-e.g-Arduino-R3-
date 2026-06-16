const int DATA_SIZE = 1000;

void setup() {

  Serial.begin(9600);

  randomSeed(analogRead(A0));

  int compressedSize = 0;

  byte currentValue = random(256);
  byte count = 1;

  for (int i = 1; i < DATA_SIZE; i++) {

    byte value = random(256);

    if (value == currentValue && count < 255) {
      count++;
    }
    else {

      compressedSize += 2;

      currentValue = value;
      count = 1;
    }
  }

  compressedSize += 2;

  Serial.print("Original Size: ");
  Serial.println(DATA_SIZE);

  Serial.print("Compressed Size: ");
  Serial.println(compressedSize);
}

void loop() {
}