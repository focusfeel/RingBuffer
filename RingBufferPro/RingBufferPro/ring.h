/*
 * Time: 
 * 		Jun. 17, 2016
 * Author: 
 * 			
 * Description: 
 * 		This file is used to define some macros and functions to realize ring buffer.
 *
 */
 
#ifndef _RING_BUFFER_
#define _RING_BUFFER_

/* Some macros for data type. */

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long int64_t;
typedef unsigned long uint64_t;

/* Ring printf define */
#define __RING_PRINTF__

#ifdef __RING_PRINTF__
#define RING_PRINTF(format, ...)		printf(format, ##__VA_ARGS__)
#else
#define RING_PRINTF(format, ...)
#endif

#define RING_BUFFER_BLOCK_NUM		8
#define RING_BUFFER_BLOCK_SIZE		512

typedef enum ringNodeFlag{
	RING_NODE_FLAG_NONE,
	RING_NODE_FLAG_READ,
	RING_NODE_FLAG_WRITE,
} TeRingNodeFlag_t;

typedef enum ringBufferFlag{
	RING_BUFFER_FLAG_NONE,
	RING_BUFFER_FLAG_EMPTY,
	RING_BUFFER_FLAG_FULL,
} TeRingBufferFlag_t;

typedef struct ringNode{
	uint8_t flag;
	uint32_t index;
	uint32_t data_size;
	uint32_t data[RING_BUFFER_BLOCK_SIZE];
	struct ringNode *next;
} TsRingNode_t;

typedef struct ringBuffer{
	uint8_t flag;
	uint32_t rbBlockNum;
	TsRingNode_t *rbRead;
	TsRingNode_t *rbWrite;
	TsRingNode_t *rbHead;
	TsRingNode_t *rbTail;
} TsRingBuffer_t;

uint32_t ringBufferCreate(TsRingBuffer_t *ringBuffer, uint32_t bufferBlockNum);
void ringBufferDestroy(TsRingBuffer_t *ringBuffer);
uint32_t ringBufferRead(TsRingBuffer_t *ringBuffer, uint8_t *data);
uint32_t ringBufferWrite(TsRingBuffer_t *ringBuffer, uint8_t *data);
uint32_t ringBufferTest(TsRingBuffer_t *ringBuffer);

#endif	/* End of #ifndef _RING_BUFFER_ */