#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BUTTON_1 GPIO_NUM_18
#define BUTTON_2 GPIO_NUM_19
#define BUTTON_3 GPIO_NUM_5     // Hazard switch

#define LED_1 GPIO_NUM_21
#define LED_2 GPIO_NUM_22

static volatile int button_1_value = 1;
static volatile int button_2_value = 1;
static volatile int button_3_value = 1;

/* ISR handlers */
static void IRAM_ATTR isr_func_1(void *arg)
{
    button_1_value = gpio_get_level(BUTTON_1);
}

static void IRAM_ATTR isr_func_2(void *arg)
{
    button_2_value = gpio_get_level(BUTTON_2);
}

static void IRAM_ATTR isr_func_3(void *arg)
{
    button_3_value = gpio_get_level(BUTTON_3);
}

void app_main(void)
{
    gpio_reset_pin(LED_1);
    gpio_reset_pin(LED_2);
    gpio_reset_pin(BUTTON_1);
    gpio_reset_pin(BUTTON_2);
    gpio_reset_pin(BUTTON_3);

    /* Button config */
    gpio_config_t btn_conf = {
        .pin_bit_mask = (1ULL << BUTTON_1) |
                        (1ULL << BUTTON_2) |
                        (1ULL << BUTTON_3),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_ANYEDGE
    };
    gpio_config(&btn_conf);

    /* LED config */
    gpio_set_direction(LED_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_2, GPIO_MODE_OUTPUT);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_1, isr_func_1, NULL);
    gpio_isr_handler_add(BUTTON_2, isr_func_2, NULL);
    gpio_isr_handler_add(BUTTON_3, isr_func_3, NULL);

    while (1)
    {
        /* HAZARD OVERRIDE */
        if (button_3_value == 0)
        {
            gpio_set_level(LED_1, 1);
            gpio_set_level(LED_2, 1);
            vTaskDelay(pdMS_TO_TICKS(200));

            gpio_set_level(LED_1, 0);
            gpio_set_level(LED_2, 0);
            vTaskDelay(pdMS_TO_TICKS(200));
        }
        else
        {
            /* LEFT */
            if (button_1_value == 0)
            {
                gpio_set_level(LED_1, 1);
                vTaskDelay(pdMS_TO_TICKS(200));
                gpio_set_level(LED_1, 0);
                vTaskDelay(pdMS_TO_TICKS(200));
            }
            else
            {
                gpio_set_level(LED_1, 0);
            }

            /* RIGHT */
            if (button_2_value == 0)
            {
                gpio_set_level(LED_2, 1);
                vTaskDelay(pdMS_TO_TICKS(200));
                gpio_set_level(LED_2, 0);
                vTaskDelay(pdMS_TO_TICKS(200));
            }
            else
            {
                gpio_set_level(LED_2, 0);
            }
        }
    }
}
