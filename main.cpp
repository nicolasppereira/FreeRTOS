#include <../../Ex04/lib/src/Arduino_FreeRTOS.h>
#include <Arduino.h>

#define LED2 2
#define LED3 3
#define LED4 4

/*Variáveis para armazenamento do handle das tasks*/

TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;
TaskHandle_t task3Handle = NULL;
TaskHandle_t task4Handle = NULL;

/*Protótipos das Tasks*/

void vTask1 (void *pvParameters);
void vTask2 (void *pvParameters);
void vTask3 (void *pvParameters);
void vTask4 (void *pvParameters);

/* função setup */

void setup(){
  Serial.begin(9600);

  while(!Serial){
    ;
  }

  xTaskCreate(vTask1,"TASK1",configMINIMAL_STACK_SIZE,(void*)LED2,2,&task1Handle);
  xTaskCreate(vTask2,"TASK2",configMINIMAL_STACK_SIZE,NULL,1,&task2Handle);
  xTaskCreate(vTask3,"TASK3",configMINIMAL_STACK_SIZE,(void*)LED3,2,&task3Handle);
  xTaskCreate(vTask4,"TASK4",configMINIMAL_STACK_SIZE,(void*)LED4,2,&task4Handle);
}

void loop(){

}

void vTask1(void *pvParameters)
{
     int pin = (int)pvParameters;
    pinMode(pin,OUTPUT);

    while (1)
    {
      digitalWrite(pin,HIGH);
      vTaskDelay(pdMS_TO_TICKS(500));
    }
}


/*
vTask2 
imprime valor de contagem a cada 1 seg
*/
void vTask2(void *pvParameters)
{
  int cont = 0;

  while (1)
  {
    Serial.println("Task 2: " + String(cont++));
    vTaskDelay(pdMS_TO_TICKS(1000));

    if(cont <= 1){
    vTaskResume(task1Handle);
    vTaskSuspend(task3Handle);
    digitalWrite(LED3,LOW);
    vTaskSuspend(task4Handle);
    digitalWrite(LED4,LOW);
  }

  if (cont == 6){
    vTaskSuspend(task1Handle);
    digitalWrite(LED2,LOW);
    vTaskResume(task4Handle);
    vTaskDelay(pdMS_TO_TICKS(5000));
    
  }
  if (cont == 8){
    vTaskSuspend(task4Handle);
    digitalWrite(LED4,LOW);
    vTaskResume(task3Handle);
    vTaskDelay(pdMS_TO_TICKS(2000));
    cont = 0;
  }
  }

  
  
}

void vTask3(void *pvParameters)
{
    int pin = (int)pvParameters;
    pinMode(pin,OUTPUT);

    while (1)
    {
      digitalWrite(pin,HIGH);
      vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vTask4(void *pvParameters)
{
    int pin = (int)pvParameters;
    pinMode(pin,OUTPUT);

    while (1)
    {
      digitalWrite(pin,HIGH);
      vTaskDelay(pdMS_TO_TICKS(500));
    }
}

