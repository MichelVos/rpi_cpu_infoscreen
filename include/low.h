/*
 * low.h
 *
 *  Created on: Jun 16, 2017
 *      Author: michel
 */

#ifndef BCM8544_LOW_H_
#define BCM8544_LOW_H_


void low_initialise();
void send_data(unsigned char*, int);
void send_command_byte(unsigned char);

#endif /* BCM8544_LOW_H_ */
