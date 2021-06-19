const char *pcTextTask1 = "vTask1";
const char *pcTextTask2 = "vTask2";

void vTask1(void *pvParameters) {
  char *pcTaskName;
  pcTaskName = (char *)pvParameters;

  for(;;) {
    printf("%s\n", pcTaskName);
    printf("This task priority is %d.\n\n", uxTaskPriorityGet(NULL));
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  printf("Hello world!\n");

  xTaskCreate(vTask1, "Task 1", 2048, (void *)pcTextTask1, 3, NULL);  // 1024 stack overflow -> 2048
  xTaskCreate(vTask1, "Task 2", 2048, (void *)pcTextTask2, 4, NULL);  // 1024 stack overflow -> 2048
}

void loop() {
  static int i = 0;

  printf("Restarting in %d seconds...\n", i);
  printf("This task priority is %d.\n\n", uxTaskPriorityGet(NULL));
  i++; 
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}