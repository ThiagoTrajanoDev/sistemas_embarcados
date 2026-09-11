#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    printf("Nome: Thiago Trajano\n Matricula: 202221250002\n");


    int cont = 0;

    while (1)
    {
        printf("Tempo decorrido: %d segundos\n", cont);

        cont += 2;

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}