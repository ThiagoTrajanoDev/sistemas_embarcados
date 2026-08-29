#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED1_PIN GPIO_NUM_41
#define LED2_PIN GPIO_NUM_42
#define LED3_PIN GPIO_NUM_2
#define LED4_PIN GPIO_NUM_1

const gpio_num_t leds[4] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN};

void leds_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED1_PIN) | (1ULL << LED2_PIN) | 
                        (1ULL << LED3_PIN) | (1ULL << LED4_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

void set_led(gpio_num_t pin, uint8_t state) {
    gpio_set_level(pin, state ? 1 : 0);
}


void turn_off_all_leds(void) {
    for (int i = 0; i < 4; i++) {
        set_led(leds[i], 0);
    }
}

void fase_contador_binario(void) {
    for (int count = 0; count <= 15; count++) {
        for (int bit = 0; bit < 4; bit++) {
            uint8_t state = (count >> bit) & 0x01;
            set_led(leds[bit], state);
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void fase_varredura(void) {

    for (int i = 0; i < 4; i++) {
        turn_off_all_leds();
        set_led(leds[i], 1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    for (int i = 3; i >= 0; i--) {
        turn_off_all_leds();
        set_led(leds[i], 1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    turn_off_all_leds();
}

void app_main(void) {
    leds_init();

    while (1) {
        fase_contador_binario();
        vTaskDelay(pdMS_TO_TICKS(500)); 
        
        fase_varredura();
        vTaskDelay(pdMS_TO_TICKS(500)); 
    }
}