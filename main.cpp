#include "FreeRTOS.h"
#include "task.h"
#include "mbed.h"
#include "LPC17xx.h"

DigitalOut led1(LED1);

void thread1 (void* params)
{
	// to use some heap memory
	uint8_t * buf = ( uint8_t * ) pvPortMalloc( sizeof( uint8_t ) * 1024 );
	buf[0] = 0;

    while(1)
    {
        led1 = 0;
        vTaskDelay(500);
        led1 = 1;
        vTaskDelay(500);
    }
}

int main()
{
	// Initializes the trace recorder, but does not start the tracing.
	vTraceEnable( TRC_INIT );

	xTaskCreate(thread1, "t1", 128, NULL, configMAX_PRIORITIES - 1, NULL);

	// Starts the tracing.
	vTraceEnable( TRC_START );

	vTaskStartScheduler();

	for( ;; );
}

/**
 * See: http://www.freertos.org/rtos-run-time-stats.html
 */
void vConfigureTimerForRunTimeStats( void )
{
    const unsigned long TCR_COUNT_RESET = 2,
                        CTCR_CTM_TIMER = 0x00,
                        TCR_COUNT_ENABLE = 0x01;

    /* Power up and feed the timer with a clock. */
    LPC_SC->PCONP |= 0x02UL;
    LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 & (~(0x3<<2))) | (0x01 << 2);

    /* Reset Timer 0 */
    LPC_TIM0->TCR = TCR_COUNT_RESET;

    /* Just count up. */
    LPC_TIM0->CTCR = CTCR_CTM_TIMER;

    /* Prescale to a frequency that is good enough to get a decent resolution,
    but not too fast so as to overflow all the time. */
    LPC_TIM0->PR =  ( configCPU_CLOCK_HZ / 10000UL ) - 1UL;

    /* Start the counter. */
    LPC_TIM0->TCR = TCR_COUNT_ENABLE;
}
