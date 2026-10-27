#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
const int seven_seg_pins[7] = {GPIO_NUM_23, GPIO_NUM_22,GPIO_NUM_1,GPIO_NUM_3, GPIO_NUM_21, GPIO_NUM_19, GPIO_NUM_18};
void setup(void)
{
    for(int i=0;i<7;i++)
    {
        gpio_reset_pin(seven_seg_pins[i]);
        gpio_set_direction(seven_seg_pins[i], GPIO_MODE_OUTPUT);
    }
    gpio_reset_pin(5);
    gpio_set_direction(5, GPIO_MODE_OUTPUT);
    
    gpio_reset_pin(17);
    gpio_set_direction(17, GPIO_MODE_OUTPUT);
}

void display(int status, int delay)
{
    for(int i=0;i<7;i++)
    {
        gpio_set_level((gpio_num_t)seven_seg_pins[i], status);
    }
    vTaskDelay(delay);
}

void display_num(int num, int delay){
    const int numbers[10][7] = {
        {0,0,0,0,0,0,1},
        {1,0,0,1,1,1,1},
        {0,0,1,0,0,1,0},
        {0,0,0,0,1,1,0},
        {1,0,0,1,1,0,0},
        {0,1,0,0,1,0,0},
        {0,1,0,0,0,0,0},
        {0,0,0,1,1,1,1},
        {0,0,0,0,0,0,0},
        {0,0,0,1,1,0,0}
    };
    for(int i=0;i<7;i++){
        gpio_set_level(seven_seg_pins[i], !numbers[num][i]);
    }
    vTaskDelay(delay);
}

void digit(int digit, int status){
    gpio_set_level(digit, status);
}
void display2num(int data, int _digit, int status, int delay){
    digit(_digit, status);
    display_num(data, delay);
    digit(_digit, 0);
}
void _display2num(int data){
    digit(5, 1);
    digit(17, 0);
    display_num(data % 10, 500/ portTICK_PERIOD_MS);
    digit(5, 0);
    digit(17, 1);
    display(data / 10, 500 portTICK_PERIOD_MS);
}

void app_main(void)
{
    setup();
    while(1){
        for(int i=0;i<100;i++)
        {
            _display2num(1);
        }
    }
}
