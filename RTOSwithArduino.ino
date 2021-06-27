// Queue overwrite, peek

typedef struct xExampleStructure {
  TickType_t xTimeStamp;
  uint32_t ulValue;
} Example_t;

/* handle fo queue */
static QueueHandle_t xMailbox;

static void vUpdateData(void *pvParameters) {
  Example_t xData;
  uint32_t value = 0;
  const TickType_t xBlockTime = pdMS_TO_TICKS(500);

  for(;;) {
    xData.ulValue = value++;
    xData.xTimeStamp = xTaskGetTickCount();

    xQueueOverwrite(xMailbox, &xData);
    vTaskDelay(xBlockTime);
  }
}

Example_t xData;

void setup() {
  printf("Hello world!\n");

  /* Create Queue */
  xMailbox = xQueueCreate(1, sizeof(Example_t));

  /* Create the Tasks that send to the queues. */
    xTaskCreate(vUpdateData, "Update", 1024, NULL, 1, NULL); 

    memset(&xData, 0, sizeof(Example_t));
}

void loop() {
  static TickType_t xPrevTimeStamp;
  const TickType_t xBlockTime = pdMS_TO_TICKS(100);

  xPrevTimeStamp = xData.xTimeStamp;
  xQueuePeek(xMailbox, &xData, portMAX_DELAY);

  if(xData.xTimeStamp > xPrevTimeStamp) {
    printf("value : %d\n\n", xData.ulValue);
  }
  else {
    printf("Not receive Mailbox\n\n");
  }
  vTaskDelay(xBlockTime);
}