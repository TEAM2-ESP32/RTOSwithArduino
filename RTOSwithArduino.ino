void vTask1(void *pvParameters) {
  for(;;) {
    printf("vTask1\n");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  printf("Hello world!\n");
  
  xTaskCreate(vTask1, "Task1", 1024, NULL, 3, NULL);
}

void loop() {
  static int i = 0;

  printf("Restarting in %d seconds...\n", i);
  i++;
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
