/*
 * IO pins:
 *     analog sensor:	PA_0
 *     fireworks:		PA_5
 *     neon:			PB_6
 *
 * Assumptions:
 *     - The fireworks go off when their input (our pin PA_5) goes from (logical) 0 to 1.
*/

#include <platform.h>
#include <gpio.h>
#include <stdint.h>
#include <adc.h>
#include <timer.h>

/* Pins */
#define P_DIST_SENSOR	PA_5
#define P_FIREWORKS		PA_5
#define P_NEON			PA_6

/* Constants */
#define VREF (3.3)
#define PERIOD (1000)
#define NUM_STEPS (100)

/* Functions definition */

void init(void);
int map(int x, int in_min, int in_max, int out_min, int out_max);

void handle_dist_long(void);
void handle_dist_medium(void);
void handle_dist_short(void);
void set_neon_pwm(int percentage);
void timer_callback_isr(void);

/* Globals */
int duty_cycle = 0;
int step = 0;

void main(void)
{
	init();

	while(1) {
		volatile int distance;
		volatile int res = (int)adc_read(P_ADC) / ADC_MASK;
		
		if (res == 0) // Special case for <30cm distance
		{
			handle_dist_short();
		} else
		{
			// Scale the adc result to a distance in cm, according to map:
			// MIN    MAX
			// VREF -> 0     IN
			//  30  -> 300   OUT
			distance = map(res , VREF, 0, 30, 300);

			if (distance <= 200 && distance > 100)
			{
				handle_dist_long();
			}
			else if (distance <= 100 && distance > 30)
			{
				handle_dist_medium();
				// Fireworks went off! Terminate the program.
				break;
			}
		}
	}
}

void init(void)
{
	__enable_irq();
	adc_init(P_ADC);
	gpio_set_mode(P_FIREWORKS, Output);
	gpio_set(P_FIREWORKS, 0);
}


int map(int x, int in_min, int in_max, int out_min, int out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void handle_dist_long(void)
{
	set_neon_pwm(50);
}

void handle_dist_medium(void)
{
	set_neon_pwm(80);
}

void handle_dist_short(void)
{
	set_neon_pwm(100);
	gpio_set(P_FIREWORKS, 1);
}

void set_neon_pwm(int percentage)
{
	timer_disable();
	duty_cycle = percentage;

	if (duty_cycle < NUM_STEPS) {
		timer_init(PERIOD/NUM_STEPS);
		timer_enable();
	} else { // Duty cycle 100% = always on
		gpio_set(P_NEON, 1);
	}
}

void timer_callback_isr(void) {
	if (step > duty_cycle) {
		gpio_set(P_NEON, 0);
	} else {
		gpio_set(P_NEON, 1);
	}

	step = ++step % NUM_STEPS;
}
