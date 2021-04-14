#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* TODO
 * Task 1: generates a random number every 200ms and stores it in the queue
 * Task 2: receives the numbers from the queue every 500ms
 * ALERT: each task should print the sent/received numbers to serial!
 * 
 */

#define STACK_SIZE 2000

// task functions
void senderFunction(){
	int i = 0;
	for( ; ; ){
		printf("Sender Task: %d\n", i);
		vTaskDelay(200 / portTICK_PERIOD_MS);
	}
}

void receiverFunction(){
	int i = 0;
	for( ; ; ){
		printf("Receiver Task: %d\n", i);
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}


// task handlers
TaskHandle_t xSenderTask_h = NULL;
TaskHandle_t xReceiverTask_h = NULL;

/* Buffers that the tasks being created will use as its stack.  Note this is
 an array of StackType_t variables.  The size of StackType_t is dependent on
the RTOS port.*/
// StackType_t xSenderStack[ STACK_SIZE ];
// StackType_t xReceiverStack[ STACK_SIZE ];

// Structure that will hold the TCB of the task being created.
// StaticTask_t xSenderBuffer;
// StaticTask_t xReceiverBuffer;

// This must exist for the life time of the task (docs)
static uint8_t ucParameterSender;
static uint8_t ucParameterReceiver;

void app_main(void)
{
	xTaskCreate(&senderFunction, "Sender", STACK_SIZE, &ucParameterSender, tskIDLE_PRIORITY, xSenderTask_h);
	
	xTaskCreate(&receiverFunction, "Receiver", STACK_SIZE, &ucParameterReceiver, tskIDLE_PRIORITY, xReceiverTask_h);
	
// 	configASSERT(xSenderTask_h);
// 	configASSERT(xReceiverTask_h);
	
	
	
	// continues to infinite loop in main task
    int i = 0;
    while (1) {
        printf("[%d] Hello world!\n", i);
        i++;
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
