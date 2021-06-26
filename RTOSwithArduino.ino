// Queue struct

typedef enum {
  eSender1,
  eSender2
} DataSource_t;

/* Define the structure type that will be passed on the queue. */
typedef struct {
  uint8_t ucValue;
  DataSource_t eDataSource;
} Data_t;

/* Declare two variables of type Data_t that will be passed on the queue. */
static const Data_t xStructsToSend[2] = {
  { 100, eSender1 }, // Used by Sender1
  { 200, eSender2 }  // Used by Sender2
};

/* handle of Queue */
QueueHandle_t xQueue;

static void vSenderTask(void *pvParameters) {
  BaseType_t xStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(500UL);

  for(;;) {
    xStatus = xQueueSendToBack(xQueue, pvParameters, xTicksToWait);
    
    if(xStatus == pdPASS) {
      printf("Success send to the queue.\n");
    }
    else {
      printf("Could not send to the queue.\n");
    }
  }
}

void setup() {
  printf("Hello world!\n");

  /* Create Queue */
  xQueue = xQueueCreate(3, sizeof(Data_t));

  if(xQueue != NULL) {  // 큐 생성이 성공한 경우
    /* Create the Task */
    xTaskCreate(vSenderTask, "Sender1", 1024, (void *)&xStructsToSend[0], 2, NULL);
    xTaskCreate(vSenderTask, "Sender2", 1024, (void *)&xStructsToSend[1], 2, NULL);
  }
  else {                // 큐 생성이 실패한 경우
    printf("Creation of Queue is failed\n\n");
  }

}

void loop() {
  static Data_t xReceivedStructure;
  static BaseType_t xStatus;

  if(uxQueueMessagesWaiting(xQueue) != 3) {
    printf("Queue should have been full!\n\n");
  }

  xStatus = xQueueReceive(xQueue, &xReceivedStructure, 0);
  if(xStatus == pdPASS) {  // Data was successfully received
    if(xReceivedStructure.eDataSource == eSender1) {
      printf("From Sender 1 = %d\n\n", xReceivedStructure.ucValue);
    }
    else {
      printf("From Sender 2 = %d\n\n", xReceivedStructure.ucValue);
    }
  }
  else {
    printf("Could not receive from the queue.\n\n");
  }
}