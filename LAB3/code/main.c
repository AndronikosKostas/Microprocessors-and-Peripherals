#include <platform.h>
#include <uart.h>
#include <gpio.h>
#include <timer.h>
#include "DHT11.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define USER_LED PA_5
#define BUTTON PC_13


static uint8_t packet[5];
static uint8_t check_sum_var = OK;
static char _temp_[2];
static uint8_t temperature = 0;

static uint8_t button_pressed = 0;						
static uint8_t AEM[5];		
static uint8_t AEM_SUM = 0;
static uint8_t aem_index = 0;

// The counter for the temperature measurement

static uint8_t temperature_timing_counter = 0;	
static uint8_t print_timing_counter = 0;
static uint8_t PRINT_FREQUENCY = 0;
static char refresh_rate[2];											

// ISR to process the user's AEM
void AEM_ISR(uint8_t uart_byte);
// ISR to process the temperature
void timer_ISR(void);
// LED ISRs
// called when temperature > 25
void led_on(void); 
// called when temperature < 20
void led_off(void); 
// called when temperature  = [20, 25]
void toggle_led(void);
// Init the USER Button
void BUTTON_INIT(void);
// Called when the button is pressed
void BUTTON_ISR(void);




int main(void)
{
	// UART Init
	uart_init(115200);
	uart_enable();
	
	// Set the uart callback function
	uart_set_rx_callback(AEM_ISR);				
	uart_print("Give me your AEM \n");
	
	// Timer Init //
	// Set up the timer to interrupt the CPU with a rate of 1sec
	timer_init(1000000);			
	// Enable the timer	
	timer_enable();													  
	// Set the timer callback ( called every second )
	timer_set_callback(timer_ISR);
	
	// LED init
	
	gpio_set_mode(USER_LED, Output);
	gpio_set(USER_LED,0);
	
	// Button Init 
	BUTTON_INIT();
	
	PRINT_FREQUENCY = 2;

	
	// Enable the interrupts
  __enable_irq();													
	
	while(1)
	{
			__WFI();
	}
}

// ISR to process the user's AEM
void AEM_ISR(uint8_t uart_byte){
	// Save the AEM until the enter character was recognized
	if(uart_byte != 10 && (uart_byte >= 48 && uart_byte <= 57)){
		AEM[aem_index] = uart_byte;										
		aem_index++;																				
	}
	else if(uart_byte == 10){ // which is the "enter"{
		aem_index--;
		AEM_SUM = (AEM[aem_index] - 48) + (AEM[aem_index-1] - 48);				// Add the two last digits of the AEM
		aem_index = 0;																					  			  // Reset the index array
	}
	else{
		uart_print("Wrong AEM. Type Again\n");
		AEM_SUM = 0;
	}
}


void timer_ISR(void)
{
	temperature_timing_counter++;
	print_timing_counter++;
	if(temperature_timing_counter == 2)
	{
		temperature_timing_counter = 0;
		start_signal();
		// check_response() returns 0 when its ok to read the sensor //
		 if(!check_response()){
			 uint8_t *p;
			 p = get_packet();
			 for(uint8_t i = 0 ; i < 5; i++)
					packet[i] = *(p + i);
				 // Control the LED based on the temp value
				  if(check_sum(packet) == OK)
					{
						
						if(temperature > 25 )
							led_on();
						else if(temperature < 20)
							led_off();
						else
							toggle_led();		
					}
		}
	}
	
	if(print_timing_counter == PRINT_FREQUENCY && check_sum(packet) == OK)
	{
		print_timing_counter = 0;
		check_sum_var = OK;
	  uart_print("Temperature = ");
		temperature = packet[2];
		sprintf(_temp_, "%d", temperature);
		uart_print(_temp_);
		uart_print("\n");			
	}
}


void led_on(void)
{
	gpio_set(USER_LED, 1);
}


void led_off(void)
{
	gpio_set(USER_LED, 0);
}


void toggle_led(void)
{
	gpio_toggle(USER_LED);
}


void BUTTON_INIT(void)
{
	gpio_set_mode(BUTTON, PullUp);
	gpio_set_trigger(BUTTON, Rising);
	gpio_set_callback(BUTTON,(void *)BUTTON_ISR);
}
		
void BUTTON_ISR(void){
	button_pressed ++;							 		
	print_timing_counter = 0 ;
	
	if(button_pressed == 1){						
		PRINT_FREQUENCY = AEM_SUM;			
	}
	else{																					
		if(button_pressed % 2 == 0){			
			PRINT_FREQUENCY = 4;
		}
		else{																				
			PRINT_FREQUENCY = 3;
		}
	}
	uart_print("\nRefresh rate: ");
	sprintf(refresh_rate, "%d", PRINT_FREQUENCY);
	uart_print(refresh_rate);
	uart_print(" sec");
	uart_print("\n");
}








