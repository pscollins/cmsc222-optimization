#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#include "worker_pool.h"

/* note: add in error handling later in life */

typedef struct {
	sem_t mutex;
	int count;
} worker_pool;

worker_pool* initialize_pool(int pool_size) 
{
	/* add error handling */
	worker_pool *ret = malloc(sizeof(worker_pool));
	
	/* need to check this return value */
	/* initialize the lock with a value of 1 as local to the process */
	sem_init(&ret->mutex, 0, 1);
	ret->count = pool_size;

	return ret;
}

bool request_worker(worker_pool *pool)
{
	assert(pool);

	bool ret;
	/* acquire a lock so we can safely check the number of free workers */
	sem_wait(&pool->mutex);

	
	if(pool->count){
		--pool->count;
		ret = true;
	} else {
		ret = false;
	}
	
	/* the check is done, release the lock */
	sem_post(&pool->mutex);
	
	return ret;
}

void return_worker(worker_pool *pool)
{
	assert(pool);

	sem_wait(&pool->mutex);
	pool->count++;
	sem_post(&pool->mutex);
}
	

/* unit tests */
int main(int argc, char* argv[])
{
	return;
}
