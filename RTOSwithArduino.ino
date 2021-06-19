/* handle of Task */
TaskHandle_t xTask2Handle;

void vTask1(void *pvParameters) {
  UBaseType_t uxPriority;
  uxPriority = uxTaskPriorityGet(NULL);

  for(;;) {
    printf("Task1 is running.\n");
    printf("Priority of Task2 is %d.\n", uxTaskPriorityGet(xTask2Handle));

    /* Setting the Task2 priority */
    printf("About to raise the Task2 priority\n\n");
    vTaskPrioritySet(xTask2Handle, uxPriority + 1);
  }
}

void vTask2(void *pvParameters) {
  UBaseType_t uxPriority;
  uxPriority = uxTaskPriorityGet(NULL);

  for(;;) {
    printf("Task2 is running.\n");
    printf("Priority of Task2 is %d.\n", uxTaskPriorityGet(NULL));

    /* Setting the Task2 priority */
    printf("About to lower the Task2 priority\n\n");
    vTaskPrioritySet(NULL, uxPriority - 1);
  }
}

void setup() {
  printf("Hello world!\n");

  xTaskCreate(vTask1, "Task 1", 2048, NULL, 4, NULL);
  xTaskCreate(vTask2, "Task 2", 2048, NULL, 3, &xTask2Handle);
}

void loop() {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}