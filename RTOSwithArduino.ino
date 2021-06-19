const char *pcTextTask1 = "vTask1";
const char *pcTextTask2 = "vTask2";

void vTask1(void *pvParameters) {
  char *pcTaskName;
  pcTaskName = (char *)pvParameters;

  for(;;) {
    printf("%s\n", pcTaskName);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  printf("Hello world!\n");

  xTaskCreate(vTask1, "Task 1", 1024, (void *)pcTextTask1, 3, NULL);
  xTaskCreate(vTask1, "Task 2", 1024, (void *)pcTextTask2, 3, NULL);
}

void loop() {
  static int i = 0;

  printf("Restarting in %d seconds...\n", i);
  i++; 
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}