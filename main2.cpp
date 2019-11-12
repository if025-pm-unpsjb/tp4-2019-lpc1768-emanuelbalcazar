#include "mbed.h"
#include<string.h>

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

Serial pc(USBTX, USBRX); // tx, rx

DigitalOut leds[] = { led1, led2, led3, led4 };

int i;
int led;
int length;

int main() {

	while (1) {
		if (pc.readable()) {
			led = (int) pc.getc() - 48;
			printf("Led encendido: %d\n\r", led);
		}

		leds[led - 1] = 1;
		wait(0.25);
		leds[led - 1] = 0;
		wait(0.25);
	}
}
