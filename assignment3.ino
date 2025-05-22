// Pin definitions
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int tempPin = A0;
const int ldrPin = A1;
unsigned long lastSwitch = 0;
bool showTemp = true;

// Custom character definitions
byte thermometer[8] = {
  0b00100,
  0b01010,
  0b01010,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b01110
};

byte lightbulb[8] = {
  0b00100,
  0b01110,
  0b01110,
  0b00100,
  0b00100,
  0b00000,
  0b00100,
  0b00000
};

// Basic LCD commands
void lcdCommand(uint8_t value) {
  digitalWrite(rs, LOW);
  lcdWrite4bits(value >> 4);
  lcdWrite4bits(value);
}

void lcdWrite(uint8_t value) {
  digitalWrite(rs, HIGH);
  lcdWrite4bits(value >> 4);
  lcdWrite4bits(value);
}

void lcdWrite4bits(uint8_t value) {
  digitalWrite(d4, (value & 0x01));
  digitalWrite(d5, (value & 0x02));
  digitalWrite(d6, (value & 0x04));
  digitalWrite(d7, (value & 0x08));

  // Enable pulse
  digitalWrite(en, LOW);
  delayMicroseconds(1);
  digitalWrite(en, HIGH);
  delayMicroseconds(1);
  digitalWrite(en, LOW);
  delayMicroseconds(100);
}

void lcdClear() {
  lcdCommand(0x01);
  delay(2);
}

void lcdHome() {
  lcdCommand(0x02);
  delay(2);
}

void lcdSetCursor(uint8_t col, uint8_t row) {
  const int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  lcdCommand(0x80 | (col + row_offsets[row]));
}

void lcdInit() {
  pinMode(rs, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);

  delay(50); // Wait for LCD to power up

  digitalWrite(rs, LOW);
  digitalWrite(en, LOW);

  // LCD initialization sequence
  lcdWrite4bits(0x03);
  delay(5);
  lcdWrite4bits(0x03);
  delayMicroseconds(150);
  lcdWrite4bits(0x03);
  lcdWrite4bits(0x02);

  lcdCommand(0x28); // 4-bit, 2 lines, 5x8 font
  lcdCommand(0x0C); // Display on, cursor off
  lcdCommand(0x06); // Increment mode
  lcdClear();
}

void lcdCreateChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x7;
  lcdCommand(0x40 | (location << 3));
  for (int i = 0; i < 8; i++) {
    lcdWrite(charmap[i]);
  }
}

void lcdPrint(const char* str) {
  while (*str) {
    lcdWrite(*str++);
  }
}

void lcdPrintFloat(float value, int decimal) {
  char buffer[10];
  int intPart = (int)value;
  int decPart = (int)(value * pow(10, decimal)) % (int)pow(10, decimal);

  lcdPrint(itoa(intPart, buffer, 10));

  if (decimal > 0) {
    lcdWrite('.');
    char decBuffer[8];
    itoa(decPart, decBuffer, 10);
    int leadingZeros = decimal - strlen(decBuffer);
    for (int i = 0; i < leadingZeros; i++) {
      lcdWrite('0');
    }
    lcdPrint(decBuffer);
  }
}

void lcdPrintInt(int value) {
  char buffer[8];
  lcdPrint(itoa(value, buffer, 10));
}

void setup() {
  lcdInit();
  lcdCreateChar(0, thermometer);
  lcdCreateChar(1, lightbulb);
  pinMode(tempPin, INPUT);
  pinMode(ldrPin, INPUT);

  lcdSetCursor(0, 0);
  // lcdPrint("Abdalhameed Maree"); // Optional welcome message
  delay(1000);
  lcdClear();
}

void loop() {
  if (millis() - lastSwitch >= 2000) {
    lcdClear();

    if (showTemp) {
      int reading = analogRead(tempPin);
      float voltage = reading * (5.0 / 1023.0);
      float tempC = voltage / 0.01;


      lcdSetCursor(0, 0);
      lcdWrite(0); // Thermometer icon
      lcdPrint(" Temp: ");
      lcdPrintFloat(tempC, 1);
      lcdPrint(" C");
   } else {
      int lightLevel = analogRead(ldrPin);
      int lightPercent = map(lightLevel, 0, 1023, 0, 100); // Or 100 to 0 if inverse

      lcdSetCursor(0, 0);
      lcdWrite(1); // Lightbulb icon
      lcdPrint(" Light: ");
      lcdPrintInt(lightPercent);
      lcdPrint(" %");
    }

    showTemp = !showTemp;
    lastSwitch = millis();
  }

}














