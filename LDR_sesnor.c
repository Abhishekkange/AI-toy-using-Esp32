#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // No reset pin
#define ldrpin 27      // NO semicolon here!

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA, SCL for ESP32

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED init failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int lightValue = analogRead(ldrpin);

  String status = (lightValue > 2000) ? "Daytime" : "Night";

  Serial.print("Light: ");
  Serial.print(lightValue);
  Serial.print(" - ");
  Serial.println(status);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Light: ");
  display.println(lightValue);
  display.print("Status: ");
  display.println(status);
  display.display();
  delay(100);


}
