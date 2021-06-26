// Queue set

/* handle of Queue */
QueueHandle_t xQueue1 = NULL, xQueue2 = NULL;
/* handle of Queue set */
QueueSetHandle_t xQueueSet = NULL;

static void vSenderTask1(void *pvParameters) {
  const TickType_t xBlockTime = pdMS_TO_TICKS(200UL);
  const char* const pcMessage ="Message for vSenderTask1\n\n"; 

  for(;;) {
    /* Block for 200ms */
    vTaskDelay(xBlockTime);

    /* Send this task's string to xQueue1. */ 
    xQueueSend(xQueue1, &pcMessage, 0);
  }
}

static void vSenderTask2(void *pvParameters) {
  const TickType_t xBlockTime = pdMS_TO_TICKS(400UL);
  const char* const pcMessage ="Message for vSenderTask2\n\n"; 

  for(;;) {
    /* Block for 400ms */
    vTaskDelay(xBlockTime);

    /* Send this task's string to xQueue1. */ 
    xQueueSend(xQueue2, &pcMessage, 0);
  }
}

void setup() {
  printf("Hello world!\n");

  /* Create Queue */
  xQueue1 = xQueueCreate(1, sizeof(char *));
  xQueue2 = xQueueCreate(1, sizeof(char *));

  /* Creat Queue-set */
  xQueueSet = xQueueCreateSet(2);

  /* Add the two Queues to the set. */
  xQueueAddToSet(xQueue1, xQueueSet);
  xQueueAddToSet(xQueue2, xQueueSet);

  /* Create the Tasks that send to the queues. */
    xTaskCreate(vSenderTask1, "Sender1", 1024, NULL, 1, NULL);
    xTaskCreate(vSenderTask2, "Sender2", 1024, NULL, 1, NULL);
}

void loop() {
  static QueueHandle_t xQueueThatContainsData;
  static char *pcReceivedString;

  /* Block on the queue set to wait for one of the queue int the set to contain data. */
  xQueueThatContainsData = (QueueHandle_t)xQueueSelectFromSet(xQueueSet, portMAX_DELAY);

  xQueueReceive(xQueueThatContainsData, &pcReceivedString, 0);
  printf(pcReceivedString);
}