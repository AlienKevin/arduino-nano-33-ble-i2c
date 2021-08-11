#include <Wire.h>

int n_squared = 0;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(100);
}

void requestEvent() {
  char data[32];
  sprintf(data, "%031d", n_squared);
  Serial.println(data);
  Wire.write(data);
}

void receiveEvent(int num_bytes) {
  int n = 0;
  while (num_bytes > 0) {
    int digit = Wire.read() - '0'; // receive a digit
    n += digit * pow10(num_bytes - 1);
    --num_bytes;
  }

  n_squared = square(n);
  
  Serial.print(n);
  Serial.print("^2 = ");
  Serial.println(n_squared);
}

int square(int n) {
  return n * n;
}

int pow10(int n) {
  int result = 1;
  for (int i = 0; i < n; ++i) {
    result *= 10;
  }
  return result;
}
