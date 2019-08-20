/**********************************
 * @author      Arka Maity
 * License:     MIT
 *
 **********************************/
#ifndef __THPOOL2_DEF_H_
#define __THPOOL2_DEF_H_

#include <pthread.h>
#include <stdbool.h>

/* Binary semaphore */
typedef struct __bsem {
	pthread_mutex_t mutex;
	pthread_cond_t   cond;
	int v;
} bsem_t;

/* Job */
typedef struct __job{
	struct __job*  prev;                 /* pointer to previous job   */
	void   (*function)(void* arg);       /* function pointer          */
	void   *arg;                         /* function's argument       */
} job_t;

/* Job queue */
typedef struct __jobqueue {
	pthread_mutex_t rwmutex;             /* used for queue r/w access */
	job_t  *front;                       /* pointer to front of queue */
	job_t  *rear;                        /* pointer to rear  of queue */
	bsem_t *has_jobs;                    /* flag as binary semaphore  */
	int   len;                           /* number of jobs in queue   */
} jobqueue_t;

int   jobqueue_init(jobqueue_t* jobqueue_p);
void  jobqueue_clear(jobqueue_t* jobqueue_p);
void  jobqueue_push(jobqueue_t* jobqueue_p,job_t* newjob_p);
job_t* jobqueue_pull(jobqueue_t* jobqueue_p);
void  jobqueue_destroy(jobqueue_t* jobqueue_p);

void  bsem_init(bsem_t *bsem_p, int value);
void  bsem_reset(bsem_t *bsem_p);
void  bsem_post(bsem_t  *bsem_p);
void  bsem_post_all(bsem_t  *bsem_p);
void  bsem_wait(bsem_t *bsem_p);

#endif /*__THPOOL2_DEF_H_ */