ESP32 FreeRTOS Queues
====================

Code description: 
- Task 1: generates a random number every SENDER_PERIOD [miliseconds] and sends it to the queue
- Task 2: receives the numbers from the queue every RECEIVER_PERIOD [miliseconds]
- Each task should print the sent/received numbers to serial!
