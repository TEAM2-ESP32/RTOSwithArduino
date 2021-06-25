// Queue creat, wtite, read

const TickType_t xTicksToWait = pdMS_TO_TICKS(500UL);

/* handle of Queue */
QueueHandle_t xQueue;

static void vSenderTask(void *pvParameters) {
  int32_t lValueToSend;
  BaseType_t xStatus;

  lValueToSend = (int32_t)pvParameters;

  for(;;) {
    xStatus = xQueueSendToBack(xQueue, &lValueToSend, 0);
    
    if(xStatus == pdPASS) {
      printf("Success send to the queue.\n");
    }
    else {
      printf("Could not send to the queue.\n");
    }
    vTaskDelay(300/ portTICK_PERIOD_MS);
  }
}

void setup() {
  printf("Hello world!\n");

  /* Create Queue */
  xQueue = xQueueCreate(5, sizeof(int32_t));

  if(xQueue != NULL) {  // 큐 생성이 성공한 경우
    /* Create the Task */
    xTaskCreate(vSenderTask, "Sender1", 1024, (void *)100, 1, NULL);
  }
  else {                // 큐 생성이 실패한 경우
    printf("Creation of Queue is failed\n\n");
  }

}

void loop() {
  static int32_t lReceivedValue;
  static BaseType_t xStatus;

  if(uxQueueMessagesWaiting(xQueue) != 0) {
    printf("Queue should have been empty!\n\n");
  }

  xStatus = xQueueReceive(xQueue, &lReceivedValue, xTicksToWait);
  if(xStatus == pdPASS) {  // Data was successfully received
    printf("Received = %d\n\n", lReceivedValue);
  }
  else {
    printf("Could not receive from the queue.\n\n");
  }
}