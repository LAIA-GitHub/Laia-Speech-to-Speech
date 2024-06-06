#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN        6  // Change to the correct pin
#define NUMPIXELS 60 // Adjust based on your LED strip

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command.startsWith("loading")) {
      int state = command.charAt(8) - '0';  // Extract the state number
      updateLEDs(state);
    } else if (command == "reset") {
      pixels.clear();
      pixels.show();
    }
  }
}

void updateLEDs(int state) {
  // Clear previous state
  pixels.clear();

  // Calculate how many LEDs to light up based on the state
  int ledsToLight = state * (NUMPIXELS / 4);  // Example: Divide strip into 4 segments

  for(int i = 0; i < ledsToLight; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 0, 0));  // Example: Set to green
  }
  pixels.show();
}
