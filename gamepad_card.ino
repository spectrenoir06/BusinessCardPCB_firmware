#include <Adafruit_NeoPixel.h>
#include <Joystick.h>

#define PIXEL_NUM	4
#define PIXEL_PIN	A5
#define PIXEL_BRIGH	25

uint8_t buttons_pins[8] = {
	A2,
	A0,
	A3,
	A3,
	3,
	0,
	2,
	1
};

uint8_t leds_pins[8] = {
	30,
	4,
	12,
	6,
	8,
	9,
	10,
	5
};

uint8_t lastButtonState[8] = {1,1,1,1,1,1,1,1};

Joystick_ Joystick;
Adafruit_NeoPixel pixels(PIXEL_NUM, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
uint32_t j=0;

uint32_t Wheel(byte WheelPos) {
	if(WheelPos < 85) {
		return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	} else if(WheelPos < 170) {
		WheelPos -= 85;
		return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	} else {
		WheelPos -= 170;
		return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}


void setup() {
	pixels.begin();
	Joystick.begin();

	for (uint8_t i=0; i<8; i++) {
		pinMode(buttons_pins[i], INPUT);
		digitalWrite(buttons_pins[i], HIGH);
	}

	for (uint8_t i=0; i<8; i++) {
		pinMode(leds_pins[i], OUTPUT);
	}
}

void loop() {

	for (uint8_t i=0; i<8; i++) {
		uint8_t d = digitalRead(buttons_pins[i]);
		if (d != lastButtonState[i]) {
			Joystick.setButton(i, !d);
			lastButtonState[i] = d;
		}
	}

	for (uint8_t i=0; i<8; i++)
		digitalWrite(leds_pins[7-i], (j>>4>>i)&1);

	for (uint8_t i=0;i<4;i++)
		pixels.setPixelColor(i, Wheel((j&0xFF)+i*10));
	j++;

	pixels.setBrightness(PIXEL_BRIGH);
	pixels.show();
	delay(10);
}
