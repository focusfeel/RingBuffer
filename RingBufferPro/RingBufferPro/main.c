/*
 * Time: 
 * 		Jun. 18, 2016
 * Author: 
 * 			
 * Description: 
 * 		This file is used to test ring buffer.
 *
 */

#include <stdio.h>
#include "ring.h"

int main(void)
{
	TsRingBuffer_t testRingBuffer;
	char data_to_write[] = "This string is used to test ring buffer !";
	char data_to_read[RING_BUFFER_BLOCK_SIZE] = "0";

	ringBufferCreate(&testRingBuffer, RING_BUFFER_BLOCK_NUM);

	if (ringBufferWrite(&testRingBuffer, data_to_write))
	{
		printf("Buffer write failed !\n");
	}
	else
	{
		if (ringBufferRead(&testRingBuffer, data_to_read))
		{
			printf("Buffer read failed !\n");
		}
		else
		{
			printf("%s\n", data_to_read);
		}
	}

	while (1)
	{}

	return 0;
}
