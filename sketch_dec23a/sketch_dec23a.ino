#include "Adafruit_NeoPixel.h"

#define PIN 10
#define NUMPIXELS 5
#define BUTTON_PIN 9
#define POT_PIN A0
#define DEBOUNCE_DELAY 50

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t colors[] = {
  strip.Color(255, 0, 0),
  strip.Color(0, 255, 0),
  strip.Color(0, 0, 255),
  strip.Color(255, 0, 255),
  strip.Color(255, 255, 0),
};
const int numColors = sizeof(colors) / sizeof(colors[0]);
int currentColorIndex = 0;

int buttonState = LOW;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
int brightness = 150;


void setup() {
  strip.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);
}


void loop() {
  // Чтение значения потенциометра и установка яркости
  brightness = map(analogRead(POT_PIN), 0, 1023, 0, 255);
  strip.setBrightness(brightness);

  // Чтение кнопки
  int reading = digitalRead(BUTTON_PIN);

  // Фильтр дребезга
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        currentColorIndex = (currentColorIndex + 1) % numColors;
       
        for (int i = 0; i < NUMPIXELS; i++) {
          strip.setPixelColor(i, colors[currentColorIndex]);
        }
        strip.show();
      }
    }
  }

  lastButtonState = reading;
}