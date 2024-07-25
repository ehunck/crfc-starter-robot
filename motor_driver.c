// motor_driver.h
// Eddie Hunckler 2024
//

#include "motor_driver.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

// #define motor_driver_printf( x )
#define motor_driver_printf( x )    printf( x )

void motor_driver_setup(void)
{
    motor_driver_printf("motor driver setup\n");
    // TODO
}

void motor_driver_enable(void)
{
    motor_driver_printf("motor driver enable\n");
    // TODO
}

void motor_driver_disable(void)
{
    motor_driver_printf("motor driver disable\n");
    // TODO
}

void motor_driver_set_speed( float val )
{
    // TODO

}

void motor_driver_set_direction( bool forward )
{
    // TODO
}
