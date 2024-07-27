// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2023 Brian Starkey <stark3y@gmail.com>

#include <stdio.h>
#include <string.h>
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "motor_driver.h"
#include "bt_hid.h"

static int clamp(int val, int min, int max)
{
	if( val > max )
	{
		return max;
	}
	if( val < min )
	{
		return min;
	}
	return val;
}

static void update_motor_driver_from_control_input( struct bt_hid_state* state )
{

	// printf("buttons: %04x, l: %d,%d, r: %d,%d, l2,r2: %d,%d hat: %d\n",
	// 			state->buttons, state->lx, state->ly, state->rx, state->ry,
	// 			state->l2, state->r2, state->hat);

	// Motor Mixer
	int forward_speed = (256 - state->ly) - 128; // 128 is full forward, 0 is stop, -128 is backwards
	int swerve_right_rate = (state->rx - 128); // 128 is max right swerve rate, 0 is no swerve, -128 is max left swerve
	
	int left_output = forward_speed;
	int right_output = forward_speed;
	if( forward_speed > 0 )
	{
		if( swerve_right_rate > 0 )
		{
			right_output -= swerve_right_rate / 2;
			right_output = clamp(right_output, 0, 128);
		}
		else if( swerve_right_rate < 0 )
		{
			left_output -= swerve_right_rate / 2;
			left_output = clamp(left_output, 0, 128);
		}
	}
	else if( forward_speed < 0 )
	{
		if( swerve_right_rate > 0 )
		{
			right_output += swerve_right_rate / 2;
			right_output = clamp(right_output, -127, 0);
		}
		else if( swerve_right_rate < 0 )
		{
			left_output += swerve_right_rate / 2;
			left_output = clamp(left_output, -127, 0);
		}
	}
	else
	{
		if( swerve_right_rate != 0 )
		{
			// rotate in place
			// This handles both rotate left and right as left will be negative and right positive
			left_output = swerve_right_rate / 2;
			right_output = -1*swerve_right_rate / 2;
		}
		// otherwise no rotation
	}

	left_output = clamp(left_output, -127, 128);
	right_output = clamp(right_output, -127, 128);

	// Set motor driver
	motor_driver_set_left( left_output );
	motor_driver_set_right( right_output );
}

enum SystemStates
{
	SystemState_DISCONNECTED,
	SystemState_CONNECTED,
	// Add additional state here...
};

void main(void) 
{
	// Variables used to control the main state machine
	enum SystemStates next_system_state = SystemState_DISCONNECTED;
	enum SystemStates system_state = SystemState_DISCONNECTED;
	enum SystemStates prev_system_state = SystemState_DISCONNECTED;
	// Structure used to hold the Bluetooth controller data
	struct bt_hid_state controller_state = {0};

	stdio_init_all();
	multicore_launch_core1(bt_main);
	// Wait for init 
	sleep_ms(1000);
	motor_driver_setup();

	while ( 1 ) 
	{
		const bool system_state_entered = ( system_state != prev_system_state );
		bt_hid_get_latest(&controller_state);
		switch( system_state )
		{
			case 	SystemState_DISCONNECTED:
				// Disconnected state
				if( system_state_entered )
				{
					// When entering the state run these functions 1 time.
					// Set the motors to a safe state.
					motor_driver_stop();
				}
				// Run the following continuously while in the disconnected mode.
				// Check to see if we are connected.
				if( bt_hid_is_connected() )
				{
					// Transition to the Connected system state
					next_system_state = SystemState_CONNECTED;
				}
				break;
			case	SystemState_CONNECTED:
				// Connected state
				if( system_state_entered )
				{
					// When entering the state run these functions 1 time.
					printf("SystemState_CONNECTED\n");
				}
				// Check to see if we are connected.
				// Handle the latest controller input.
				if( bt_hid_is_connected() )
				{
					// handle commands and update the motor.
					update_motor_driver_from_control_input(&controller_state);
				}
				else
				{
					// The system is not connected.
					// Transition to the Disconnected system state
					next_system_state = SystemState_DISCONNECTED;
				}
				break;
			default:
				break;
		}
		prev_system_state = system_state;
		system_state = next_system_state;

		// regulate the update rate to ~100 Hz
		sleep_ms(10);
	}
}
