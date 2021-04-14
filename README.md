ESP32 FreeRTOS Queues
====================

Code description: 
- Task 1: generates a random number every SENDER_PERIOD [miliseconds] and sends it to the queue
- Task 2: receives the numbers from the queue every RECEIVER_PERIOD [miliseconds]
- Each task should print the sent/received numbers to serial!

Instructions:
1. Install required componentes from https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html
2. Go to the root of the repository
```bash
$ cd <REPO_PATH>

```
3. Build, flash and monitor (works with either 'make' or 'idf.py' command):

```bash
$ make build flash monitor
```
If it fails, try with the following `flash` options
- Baudrate: 
```bash
-b 115200
```

- Port example (Linux): 
```bash
-p /dev/ttyUSB0
```
