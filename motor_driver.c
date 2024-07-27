// motor_driver.h
// Eddie Hunckler 2024
//

#include <stdio.h>
#include "motor_driver.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include "pin_definitions.h"

void motor_driver_setup(void)
{
    printf("motor driver setup\n");

    // Left motor driver initialization
    gpio_init(PIN_LEFT_MOTOR_INA);
    gpio_init(PIN_LEFT_MOTOR_INB);
    gpio_set_dir(PIN_LEFT_MOTOR_INA, GPIO_OUT);
    gpio_set_dir(PIN_LEFT_MOTOR_INB, GPIO_OUT);
    gpio_put(PIN_LEFT_MOTOR_INA, 0);
    gpio_put(PIN_LEFT_MOTOR_INB, 0);

    // Right motor driver initialization
    gpio_init(PIN_RIGHT_MOTOR_INA);
    gpio_init(PIN_RIGHT_MOTOR_INB);
    gpio_set_dir(PIN_RIGHT_MOTOR_INA, GPIO_OUT);
    gpio_set_dir(PIN_RIGHT_MOTOR_INB, GPIO_OUT);
    gpio_put(PIN_RIGHT_MOTOR_INA, 0);
    gpio_put(PIN_RIGHT_MOTOR_INB, 0);
}

void motor_driver_stop(void)
{
    printf("motor driver stop\n");
    gpio_put(PIN_LEFT_MOTOR_INA, 0);
    gpio_put(PIN_LEFT_MOTOR_INB, 0);
    gpio_put(PIN_RIGHT_MOTOR_INA, 0);
    gpio_put(PIN_RIGHT_MOTOR_INB, 0);
}

void motor_driver_set_left( int val )
{
    if( val > 0 )
    {
        // clockwise
        gpio_put(PIN_LEFT_MOTOR_INA, 0); // 1);
        gpio_put(PIN_LEFT_MOTOR_INB, 1); // 0);
        // TODO Set PWM
    }
    else if( val < 0 )
    {
        // counter closkwise
        gpio_put(PIN_LEFT_MOTOR_INA, 1); // 0);
        gpio_put(PIN_LEFT_MOTOR_INB, 0); // 1);
        // TODO Set PWM
    }
    else
    {
        // stop
        gpio_put(PIN_LEFT_MOTOR_INA, 0);
        gpio_put(PIN_LEFT_MOTOR_INB, 0);
    }
}

void motor_driver_set_right( int val )
{
    if( val > 0 )
    {
        // counter clockwise
        gpio_put(PIN_RIGHT_MOTOR_INA, 0);
        gpio_put(PIN_RIGHT_MOTOR_INB, 1);
        // TODO Set PWM
    }
    else if( val < 0 )
    {
        // clockwise
        gpio_put(PIN_RIGHT_MOTOR_INA, 1);
        gpio_put(PIN_RIGHT_MOTOR_INB, 0);
        // TODO Set PWM
    }
    else
    {
        // stop
        gpio_put(PIN_RIGHT_MOTOR_INA, 0);
        gpio_put(PIN_RIGHT_MOTOR_INB, 0);
    }
}