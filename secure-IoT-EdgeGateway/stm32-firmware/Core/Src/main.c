#include "main.h"
#include <stdio.h>
#include <string.h>

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart3;

static void sensor_init(void)
{
    // ADXL345 initialization will be implemented here
}

static void sensor_read(int16_t *x, int16_t *y, int16_t *z)
{
    // Placeholder values for initial firmware skeleton
    *x = 100;
    *y = 200;
    *z = 300;
}

static void uart_send(const char *msg)
{
    HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 100);
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART3_UART_Init();

    sensor_init();

    int16_t x, y, z;
    char buffer[128];

    while (1)
    {
        sensor_read(&x, &y, &z);

        snprintf(buffer, sizeof(buffer),
                 "{\"x\":%d,\"y\":%d,\"z\":%d}\n",
                 x, y, z);

        uart_send(buffer);
        HAL_Delay(500);
    }
}