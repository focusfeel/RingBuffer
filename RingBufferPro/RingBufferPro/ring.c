/*
 * Time: 
 * 		Jun. 17, 2016
 * Author: 
 * 			
 * Description: 
 * 		This file is used to realize ring buffer.
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ring.h"
 
uint32_t ringBufferCreate(TsRingBuffer_t *ringBuffer, uint32_t bufferBlockNum)
{
	uint32_t i;

	if (bufferBlockNum <= 1)
	{
		RING_PRINTF("(File: %s, Line: %d) Ring buffer block number is invalid !\n", __FILE__, __LINE__);

		return -1;
	}

	ringBuffer->flag = RING_BUFFER_FLAG_EMPTY;
    ringBuffer->rbBlockNum = bufferBlockNum;
    ringBuffer->rbHead = malloc(sizeof(TsRingNode_t));
    ringBuffer->rbHead->index = 0;
	ringBuffer->rbHead->data_size = 0;
	ringBuffer->rbRead = ringBuffer->rbHead;
	ringBuffer->rbWrite = ringBuffer->rbHead;
    ringBuffer->rbTail = ringBuffer->rbHead;

	for (i = 1; i < bufferBlockNum; i++)
	{
		ringBuffer->rbTail->next = malloc(sizeof(TsRingNode_t));
        ringBuffer->rbTail->next->index = i;
		ringBuffer->rbTail->next->data_size = 0;
        ringBuffer->rbTail = ringBuffer->rbTail->next;      
	}

    ringBuffer->rbTail->next = ringBuffer->rbHead;

	return 0;
}

void ringBufferDestroy(TsRingBuffer_t *ringBuffer)
{
    TsRingNode_t *freeNode, *freeNext;

	freeNext = ringBuffer->rbHead;
    for (freeNode = ringBuffer->rbHead; freeNode != ringBuffer->rbTail; )
    {
        freeNext = freeNode->next;
		free(freeNode);
		freeNode = freeNext;
    }
	free(freeNode);
}

uint32_t ringBufferRead(TsRingBuffer_t *ringBuffer, uint8_t *data)
{
	uint32_t i;

	if (ringBuffer->flag == RING_BUFFER_FLAG_EMPTY)
	{
		RING_PRINTF("(File: %s, Line: %d) Ring buffer is empty !\n", __FILE__, __LINE__);

		return -1;
	}
	else
	{
		for (i = 0; i < ringBuffer->rbRead->data_size; i++)
		{
			data[i] = ringBuffer->rbRead->data[i];
		}
		ringBuffer->rbRead = ringBuffer->rbRead->next;

		if (ringBuffer->rbRead == ringBuffer->rbWrite)
		{
			ringBuffer->flag = RING_BUFFER_FLAG_EMPTY;
		}
		else
		{
			ringBuffer->flag = RING_BUFFER_FLAG_NONE;
		}
	}

	return 0;
}
uint32_t ringBufferWrite(TsRingBuffer_t *ringBuffer, uint8_t *data)
{
	uint32_t i;

	if (ringBuffer->flag == RING_BUFFER_FLAG_FULL)
	{
		RING_PRINTF("(File: %s, Line: %d) Ring buffer is full !\n", __FILE__, __LINE__);

		return -1;
	}
	else
	{
		for (i = 0; i < strlen(data); i++)
		{
			ringBuffer->rbWrite->data[i] = data[i];
			ringBuffer->rbWrite->data_size++;
		}
		ringBuffer->rbWrite = ringBuffer->rbWrite->next;

		if (ringBuffer->rbWrite == ringBuffer->rbRead)
		{
			ringBuffer->flag = RING_BUFFER_FLAG_FULL;
		}
		else
		{
			ringBuffer->flag = RING_BUFFER_FLAG_NONE;
		}
	}

	return 0;
}
uint32_t ringBufferTest(TsRingBuffer_t *ringBuffer)
{
	
	return 0;
}