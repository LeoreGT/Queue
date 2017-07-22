#include "mu_test.h"
#include "gen_queue.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>  /* size_t */

typedef struct Person
{
  char* m_name;
  size_t m_age;
} Person_t;

typedef void(*DestroyFunc_t)(void*);

/*Destroy function*/
void DestroyPerson(Person_t* _Person)
{
  free(_Person);
}

UNIT(create_empty)
  DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPerson;
  Queue* queue = NULL;
  queue = QueueCreate(100);
  ASSERT_THAT(queue != NULL);
  QueueDestroy(queue, destroyFunc);
END_UNIT

UNIT(create_zero_size)
  DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPerson;
  Queue* queue = NULL;
  queue = QueueCreate(0);
  ASSERT_THAT(queue != NULL);
  QueueDestroy(queue, destroyFunc);
END_UNIT

UNIT(create_and_destroy)
  DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPerson;
  Queue* queue = NULL;
  queue = QueueCreate(100);
  QueueDestroy(queue, destroyFunc);
  ASSERT_THAT(queue == NULL);
END_UNIT

UNIT(double_destruction)
  DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPerson;
  Queue* queue = NULL;
  queue = QueueCreate(100);
  QueueDestroy(queue, destroyFunc);
  QueueDestroy(queue, destroyFunc);
  ASSERT_THAT(queue == NULL); /* Why doesn't work == NULL but works != NULL */
END_UNIT

UNIT(append_one)
  DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPerson;
  Queue* queue = NULL;
  Person_t* p = (Person_t*) malloc(sizeof(Person_t));
  queue = QueueCreate(100);
  QueueInsert(queue, p);
  ASSERT_THAT(QueueIsEmpty(queue) == 0);
  QueueDestroy(queue, destroyFunc);
END_UNIT

UNIT(append_few)
  DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPerson;
  Queue* queue = NULL;
  int i;
  Person_t* p;
  queue = QueueCreate(100);
  for(i = 0; i < 15; ++i)
  {
    p = (Person_t*) malloc(sizeof(Person_t));
    QueueInsert(queue, p);
  }
  ASSERT_THAT(QueueIsEmpty(queue) == 0);
  QueueDestroy(queue, destroyFunc);
END_UNIT

UNIT(append_many)
  DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPerson;
  Queue* queue = NULL;
  int i;
  Person_t* p;
  queue = QueueCreate(100);
  for(i = 0; i < 300; ++i)
  {
    p = (Person_t*) malloc(sizeof(Person_t));
    QueueInsert(queue, p);
  }
  ASSERT_THAT(QueueIsEmpty(queue) == 0);
  QueueDestroy(queue, destroyFunc);
END_UNIT

TEST_SUITE(Generic Vector Tests)
  TEST(create_empty)
  TEST(create_zero_size)
  TEST(create_and_destroy)
  TEST(double_destruction)
  TEST(append_one)
  TEST(append_few)
  TEST(append_many)
END_SUITE

/*===============================TEST IMPLEMENTATION============================================*/
