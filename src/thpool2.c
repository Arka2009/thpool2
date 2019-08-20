#include "thpool2.h"
#include <ecotools/errordefs.h>

/* Init semaphore to 1 or 0 */
void  bsem_init(bsem_t *bsem_p, int value) {
	if (value < 0 || value > 1) {
		PRINTERROR("Binary semaphore can take only values 1 or 0");
	}
	pthread_mutex_init(&(bsem_p->mutex), NULL);
	pthread_cond_init(&(bsem_p->cond), NULL);
	bsem_p->v = value;
}

/* Initialize job queue */
int jobqueue_init(jobqueue_t* jobqueue_p) {
	jobqueue_p->len = 0;
	jobqueue_p->front = NULL;
	jobqueue_p->rear  = NULL;

	jobqueue_p->has_jobs = (bsem_t*)malloc(sizeof(bsem_t));
	if (jobqueue_p->has_jobs == NULL){
		return -1;
	}

	pthread_mutex_init(&(jobqueue_p->rwmutex), NULL);
	bsem_init(jobqueue_p->has_jobs, 0);

	return 0;
}