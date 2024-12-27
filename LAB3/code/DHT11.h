#include <stdint.h>
#include <delay.h>
#include <gpio.h>

#define DHT_11_Pin PA_0

#define OK 0
#define ERROR 1

/*!
 *  @brief  // starts the start signal process of the sensor to actually communicate with it in order to read its data // 
 */
void start_signal(void);


/*!
 *  @brief Checks if the sensor responds appropriatelly 
 *seconds.
 *  
 *	@return 1 if we have error
 */
 
uint8_t check_response(void);

/*!
 *  @brief reads the waveform of the signal and determines if it 1 or 0
 *  
 *	@return 	1 = ( 70us on HIGH ), 0 = ( 26 - 28 us on HIGH)
	
 */
uint8_t readBit(void);

/*!
 *  @brief reads 8 bits continiously and stores them into a byte
 *  
 *	@return byte
	
 */
uint8_t readByte(void);

/*!
 *  @brief reads 5 bytes (one complete packet of the DHT) continiously and stores them I
 *  
 *	@return an array 
	
 */
uint8_t * get_packet(void);


// if(packet[0] + packet[1] + packet[2] + packet[3] == packet[4]) then its OK
uint8_t check_sum(uint8_t *packet);