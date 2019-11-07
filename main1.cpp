#include "mbed.h"
#include<string.h>

DigitalOut led1(LED1);
Serial pc(USBTX, USBRX); // tx, rx

int main() {

	while (1) {
		if (pc.readable()) {
			if ('h' == pc.getc()) {
				printf("¡hola!\n\r");
			} else {
			    printf("%c\n\r", pc.getc());
			}
		}
	}
}
