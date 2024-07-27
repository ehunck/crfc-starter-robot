// motor_driver.h
// Eddie Hunckler 2024
//

#include <stdio.h>
#include <stdlib.h>
#include "motor_driver.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include "pin_definitions.h"

static int left_pwm_slice_num = 0;
static int right_pwm_slice_num = 0;

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
    
    // PWM Left 
    gpio_set_function(PIN_LEFT_MOTOR_PWM, GPIO_FUNC_PWM);
    left_pwm_slice_num = pwm_gpio_to_slice_num(PIN_LEFT_MOTOR_PWM);
    pwm_set_wrap(left_pwm_slice_num, 128);
    pwm_set_gpio_level(PIN_LEFT_MOTOR_PWM, 0);
    pwm_set_enabled(left_pwm_slice_num, true);

    // PWM Right
    gpio_set_function(PIN_RIGHT_MOTOR_PWM, GPIO_FUNC_PWM);
    right_pwm_slice_num = pwm_gpio_to_slice_num(PIN_RIGHT_MOTOR_PWM);
    pwm_set_wrap(right_pwm_slice_num, 128);
    pwm_set_gpio_level(PIN_RIGHT_MOTOR_PWM, 0);
    pwm_set_enabled(right_pwm_slice_num, true);
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
        pwm_set_gpio_level(PIN_LEFT_MOTOR_PWM, abs(val));
    }
    else if( val < 0 )
    {
        // counter closkwise
        gpio_put(PIN_LEFT_MOTOR_INA, 1); // 0);
        gpio_put(PIN_LEFT_MOTOR_INB, 0); // 1);
        pwm_set_gpio_level(PIN_LEFT_MOTOR_PWM, abs(val));
    }
    else
    {
        // stop
        gpio_put(PIN_LEFT_MOTOR_INA, 0);
        gpio_put(PIN_LEFT_MOTOR_INB, 0);
        pwm_set_gpio_level(PIN_LEFT_MOTOR_PWM, 0);
    }
}

void motor_driver_set_right( int val )
{
    if( val > 0 )
    {
        // counter clockwise
        gpio_put(PIN_RIGHT_MOTOR_INA, 0);
        gpio_put(PIN_RIGHT_MOTOR_INB, 1);
        pwm_set_gpio_level(PIN_RIGHT_MOTOR_PWM, abs(val));
    }
    else if( val < 0 )
    {
        // clockwise
        gpio_put(PIN_RIGHT_MOTOR_INA, 1);
        gpio_put(PIN_RIGHT_MOTOR_INB, 0);
        pwm_set_gpio_level(PIN_RIGHT_MOTOR_PWM, abs(val));
    }
    else
    {
        // stop
        gpio_put(PIN_RIGHT_MOTOR_INA, 0);
        gpio_put(PIN_RIGHT_MOTOR_INB, 0);
        pwm_set_gpio_level(PIN_RIGHT_MOTOR_PWM, 0);
    }
}