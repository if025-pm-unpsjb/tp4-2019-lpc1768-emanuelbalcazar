#include "mbed.h"
#include<string.h>

DigitalOut leds[] = { LED1, LED2, LED3, LED4 };
Serial pc(USBTX, USBRX); // tx, rx

char readed;
int number = 0;
float numberAnt = 1000;

void prenderSiguiente(int i) {
	leds[i] = 0;
	if (leds[i + 1] == 1) {
		prenderSiguiente(i + 1);
	} else {
		leds[i + 1] = 1;
	}
}

void aumentar() {
	for (int i = 0; i < 4; i++) {
		if (leds[i] == 0) {
			leds[i] = 1;
			break;
		} else if (i != 3) {
			prenderSiguiente(i);
			break;
		}
	}
}

bool lleno() {
	for (int i = 0; i < 4; i++) {
		if (leds[i] == 0) {
			return false;
		}
	}

	return true;
}

void vaciar() {
	for (int i = 0; i < 4; i++) {
		leds[i] = 0;
	}
}

int main() {
	// specify period first, then everything else
	while (1) {
		if (pc.readable()) {
			readed = pc.getc();

			if (readed == '.') {
				numberAnt = number;
				number = 0;
			} else {
				number = readed - '0' + number * 10;
			}
		} else {
			if (lleno()) {
				vaciar();
			}

			aumentar();
			wait(numberAnt / 1000);
		}
	}
}
