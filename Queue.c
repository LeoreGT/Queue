#include "ADTDefs.h"
#include "vector.h"
#include "gen_queue.h"
#include <stdlib.h>
#include <stddef.h>  /* size_t */

#define ALIVE      0xbeefbeef
#define DEAD       0xdeadbeef
#define QUEUE_SIZE 128

#define CHECK(input, inputAgainst, output) if(inputAgainst == input) \
															{ \
															return output; \
															}
struct Queue
{
  size_t m_size;
  int m_head;
  int m_tail;
  size_t m_nItems;
  size_t m_magicNumber;
  Vector*  m_vector;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static ADTErr VectorErrToQueueErr(Vector_Result _err) /* Error conversions learned from Anton */
{
	ADTErr queueRes = ERR_GENERAL;
	switch(_err)
	{
		case VECTOR_SUCCESS:
			queueRes = ERR_OK;
			break;
		case VECTOR_UNITIALIZED_ERROR:
			queueRes = ERR_GENERAL;
			break;
		case VECTOR_ALLOCATION_ERROR:
			queueRes = ERR_ALLOCATION_FAILED;
			break;
    case VECTOR_INDEX_OUT_OF_BOUNDS_ERROR:
      queueRes = ERR_INVALID_DATA;
			break;
	}
	return queueRes;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Queue* QueueCreate(size_t _size)
{
	Queue* newQueue;

	newQueue = (Queue*) malloc(sizeof(Queue));
	CHECK(newQueue, NULL, NULL);

	newQueue->m_vector = Vector_Create(10, 10);
	if(NULL == newQueue->m_vector)
	{
		free(newQueue);
		return NULL;
	}

	newQueue->m_magicNumber = ALIVE;

	return newQueue;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void QueueDestroy(Queue* _queue, void(*_destroyElement)(void*))
{
	if(NULL != _queue && ALIVE == _queue->m_magicNumber)
	{
		Vector_Destroy(&(_queue->m_vector), _destroyElement);
		_queue->m_magicNumber = DEAD;
		free(_queue);
	}
  _queue = NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ADTErr QueueInsert(Queue* _queue, void* _item)
{
	Vector_Result res = Vector_Append(_queue->m_vector, _item);
	return VectorErrToQueueErr(res);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ADTErr QueueRemove(Queue* _queue, void** _item)
{
	Vector_Result res = Vector_Remove(_queue->m_vector, _item);
	return VectorErrToQueueErr(res);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int QueueIsEmpty(Queue* _queue)
{
	CHECK(_queue, NULL , 1)
	return (Vector_Size(_queue->m_vector) == 0 ? 1 : 0);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
size_t QueueForEach(Queue* _queue, KeyValueActionFunction _action, void* _context)
{
  CHECK(_queue, NULL , 1)
  Vector_ForEeach()
  return iterations;
}*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
