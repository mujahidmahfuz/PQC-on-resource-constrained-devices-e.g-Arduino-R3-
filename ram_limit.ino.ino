byte publicKey[1632];

void setup() {
  Serial.begin(9600);

  unsigned long sum = 0;

  for (int i = 0; i < 1632; i++) {
    publicKey[i] = i & 0xFF;
  }

  for (int i = 0; i < 1632; i++) {
    sum += publicKey[i];
  }

  Serial.print("Size = ");
  Serial.println(sizeof(publicKey));

  Serial.print("Sum = ");
  Serial.println(sum);
}

void loop() {
}