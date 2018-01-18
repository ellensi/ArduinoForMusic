#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

#define NUM_LEDS 94
#define ledStripPin 2
#define sensorSignalPin 4
#define sensorVcc 5
#define sensorGnd 6

CRGB ledStripData[NUM_LEDS];
int previousTimeKey = 0;
bool previousReading = false;
bool hasBeenSet = false;
int i = 0;

void setup() {
  pinMode(sensorSignalPin, INPUT);
  pinMode(ledStripPin, OUTPUT);

  pinMode(sensorVcc, OUTPUT); digitalWrite(sensorVcc, HIGH);
  pinMode(sensorGnd, OUTPUT); digitalWrite(sensorGnd, LOW);

  FastLED.addLeds<WS2811, ledStripPin, GRB>(ledStripData, NUM_LEDS);
  FastLED.setBrightness(64);
}

void loop() {

  bool currentReading = digitalRead(sensorSignalPin);
  int currentTimer = millis() - previousTimeKey;

  if (!hasBeenSet || (currentReading != previousReading)) {
    hasBeenSet = true;
    previousReading = currentReading;
    previousTimeKey = millis();
  }

  if (currentReading) {
    fill_rainbow(ledStripData, NUM_LEDS, -millis() / 12 + 128, 1);
  } else {
    fill_rainbow(ledStripData, NUM_LEDS, -millis() / 12, 1);
  }
  FastLED.show();
}

