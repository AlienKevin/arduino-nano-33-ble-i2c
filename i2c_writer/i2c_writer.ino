#include <Wire.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin(); // join i2c bus (address optional for writer)
}

void loop() {
  Serial.print("Enter a number to square: ");
  char ledVal[0];
  readSerial(ledVal);
  Serial.println(ledVal);
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(ledVal);        // sends the given value
  Wire.endTransmission();    // stop transmitting

  delay(100);
  
  Wire.requestFrom(8, 31);
  int n_squared = 0;
  while (Wire.available()) {
    char d = Wire.read();
    int digit = d - '0'; // receive a digit
//    Serial.print(d);
//    Serial.print(",");
    n_squared *= 10;
    n_squared += digit;
  }

  Serial.print(ledVal);
  Serial.print("^2 = ");
  Serial.println(n_squared);
  
  delay(500);
}

/* Read input serial */
int readSerial(char result[]) {
  int i = 0;
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}
