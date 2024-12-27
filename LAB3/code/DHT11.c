#include "DHT11.h"
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void start_signal(void){
	gpio_set_mode(DHT_11_Pin, Output);
	// Set the DHT LOW for 20ms to ensure DHT’s detection of MCU's signal
	gpio_set(DHT_11_Pin, 0);							
	delay_ms(20);	
	
	// Set the DHT HIGH and wait 30us (20-40us) for DHT’s response
	gpio_set(DHT_11_Pin, 1);							
	delay_us(30);															
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Once DHT detects the start signal, it will send out a low-voltage-level response signal, which
lasts 80us. Then the programme of DHT sets Data Single-bus voltage level from low to high and
keeps it for 80us for DHT’s preparation for sending data.
*/

uint8_t check_response(void){
	// keep the time that we are waiting for something to happen //
	uint8_t time = 0;
	// Set the DHT Pin as an Input //
	gpio_set_mode(DHT_11_Pin, Input);
	
	while (gpio_get(DHT_11_Pin) && (time < 100)){  
		time++;
		// sampling of the state of the DHT with 1us 
		delay_us(1);
	}	

	/*
	While ends in the following cases : 1) DHT LOW or 2) time >= 100 
	  
	  1) DHT on LOW and time < 100   // time = time that DHT starts the response 
    2) time >= 100 and DHT on HIGH // never got response from the sensor
		
	*/
	if(time >= 100)
		// 2) error case 
		return 1;													
	else 
		// 1) // correct case 
	  // we go the time to zero to measure the width of the response in time to check if it is correct ( 80us )
		time = 0;
	
  while(!gpio_get(DHT_11_Pin) && time < 100){
		time++;
		// sampling of the state of the DHT with 1us 
		delay_us(1);
	}
		/*
		While ends in the following cases : 1) DHT HIGH or 2) time >= 100 
		1) DHT on HIGH and time < 100      // time = time that DHT ends the response cause it becomes HIGH
    2) time >= 100 and DHT on LOW      // never ends the respose ( must end in at 80us in normal conditions )
	  */
	if(time >= 100)		
		 // 2) error case 
		return 1;
	else
		// 1) works fine
		return 0; //  			
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	When DHT is sending data to MCU, EVERY bit of data begins with the 50us low-voltage-level signal
	The Length in time of the following HIGH Level Signal determines if it is 0 or 1.
	1 = ( 70us on HIGH )
	0 = ( 26 - 28 us on HIGH)
*/
uint8_t readBit(void){															
	
	while(gpio_get(DHT_11_Pin))
	{
		// sampling of the state of the DHT with 1us 
		delay_us(1);
	}
	/*
		While ends when becomes LOW 
	*/
	// Here started the 50us low-voltage-level signal (something like start bit)
	while(!gpio_get(DHT_11_Pin))
	{
		// sampling of the state of the DHT with 1us 
		delay_us(1);
	}
	/*
		While ends when becomes HIGH ( the 50us came to its end so we can start to read )
	*/
	
	// Reading Technique // 
	
	// wait 40us and then read the DHT // 
	
	delay_us(40); 

	// if it is still HIGH after 40us we are in the range of (40 - 70us ), so the bit is 1
	// else if it is not HIGH, that means that the DHT has started the next 50us low-voltage-level pulse, so the bit is 0
	
	if(gpio_get(DHT_11_Pin))					
		return 1;
	else 
	  return 0;	

	// Reading Technique // 	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t readByte(void){
	uint8_t byte = 0x0;							
	// A loop to read 8 bit continuously
	for(int i = 0; i < 8; i++){				
		// The sensor sends higher data bit first, so we left shift the bits each time
		byte <<= 1; 
	  byte |= readBit();
		
		
		// BITWISE OR 
		// cases :
		// 1) 0bxxxxxxx0 | 0b00000000 = 0bxxxxxxx0 
		// 2) 0bxxxxxxx0 | 0b00000001 = 0bxxxxxxx1 
		// we have two cases because each time we perform left shifting
	}
	return byte;												
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t * get_packet(void){
	
	// static to retain its memory after the execution of the function and to be processed in the main
	static uint8_t sensor_data[5];
	// read 5 bytes that form a complete packet 

	for(uint8_t i = 0; i < 5; i++)
		sensor_data[i] = readByte();
	
	// sensor_data[0] = integral RH 
	// sensor_data[1] = decimal RH data 
	// sensor_data[2] = integral T data
	// sensor_data[3] = decimal T
	// sensor_data[4] = check sum
	
	return sensor_data;
}

///////////////////////////////////////////////////////////

uint8_t check_sum(uint8_t *packet)
{
	if(packet[0] + packet[1] + packet[2] + packet[3] == packet[4])
		return OK;
	else
		return ERROR;
}






