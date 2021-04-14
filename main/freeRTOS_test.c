#include <stdio.h>				// printf
#include <stdlib.h>  			// rand
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

/* Code description: 
 * Task 1: generates a random number every SENDER_PERIOD [miliseconds] and sends it to the queue
 * Task 2: receives the numbers from the queue every RECEIVER_PERIOD [miliseconds]
 * ALERT: each task should print the sent/received numbers to serial!
 */

// definitions
#define STACK_SIZE 2000
#define QUEUE_TIMEOUT 50/portTICK_PERIOD_MS
#define SENDER_PERIOD 100 / portTICK_PERIOD_MS
#define RECEIVER_PERIOD 100 / portTICK_PERIOD_MS

// Prototypes
void senderFunction();
void receiverFunction();

// Declarations
QueueHandle_t xQueue;
TaskHandle_t xSenderTask_h = NULL;
TaskHandle_t xReceiverTask_h = NULL;

// These must exist for the life time of the task (docs)
static uint8_t ucParameterSender;
static uint8_t ucParameterReceiver;





void app_main(void)
{
	xQueue = xQueueCreate(10, sizeof(uint32_t));
	
	xTaskCreate(&senderFunction, "Sender", STACK_SIZE, &ucParameterSender, tskIDLE_PRIORITY, xSenderTask_h);
	
	xTaskCreate(&receiverFunction, "Receiver", STACK_SIZE, &ucParameterReceiver, tskIDLE_PRIORITY, xReceiverTask_h);
	
	// continues to infinite loop in main task
    uint32_t i = 0;
    while (1) {
        printf("[%d] Hello world!\n", i);
		printf("Queue msgs:\t%d\n", uxQueueMessagesWaiting(xQueue));
        i++;
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

// task functions
void senderFunction(){
	uint32_t i;
	for( ; ; ){
		i = rand()%100;
		// TODO: send value to queue
		BaseType_t sndStatus = xQueueSend(xQueue, &i, QUEUE_TIMEOUT);
		if( sndStatus == errQUEUE_FULL ){
			printf("Queue is full. Dropping %d\n", i);
		}
		printf("Sender Task:  \t%d \t @ %d\n", i, xTaskGetTickCount());
		vTaskDelay(SENDER_PERIOD);
	}
}

void receiverFunction(){
	int i;
	for( ; ; ){
// 		i = rand()%100; //TODO: receive value from queue
		BaseType_t rcvStatus = xQueueReceive(xQueue, &i, QUEUE_TIMEOUT);
		if(rcvStatus == pdTRUE){
			printf("Receiver Task:\t%d \t @ %d\n", i, xTaskGetTickCount());
		}
		else{
			printf("Failed to receive message: Queue empty\n");
		}
		vTaskDelay(RECEIVER_PERIOD);
	}
}
