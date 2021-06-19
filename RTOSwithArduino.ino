/* handle of Task */
TaskHandle_t xTask1Handle;

void vTask1(void *pvParameters) {
  printf("Task1 is running and deleted.\n\n");
  vTaskDelete(xTask1Handle);  // loop 코드가 없는 경우에 필요
  //vTaskDelete(NULL);
}

void setup() {
  printf("Hello world!\n");

}

void loop() {
  printf("Task1 is started\n");
  xTaskCreate(vTask1, "Task 1", 1024, NULL, 3, &xTask1Handle);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}