#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#include <stdbool.h>

void motor_driver_setup(void);
void motor_driver_stop(void);
void motor_driver_set_left( int val );
void motor_driver_set_right( int val );

#endif // _MOTOR_DRIVER_H_