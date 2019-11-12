#include "mbed.h"
#include<string.h>

PwmOut led(LED1);
DigitalOut led4(LED4);

Serial pc(USBTX, USBRX); // tx, rx

float offset = 0.0;
float limit = 0.50;
float increment = 0.005;

int main() {
	// specify period first, then everything else
	while (1) {
		if (offset <= limit) {
			offset = offset + increment;
			led.write(offset);
			led4 = 0;
		} else {
			offset = 0.0;
			led4 = 1;
			wait(0.05);
		}

		wait(0.05);
	}
}
