#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#include <stdbool.h>

void motor_driver_setup(void);
void motor_driver_enable(void);
void motor_driver_disable(void);
void motor_driver_set_speed( float val );
void motor_driver_set_direction( bool forward );

#endif // _MOTOR_DRIVER_H_