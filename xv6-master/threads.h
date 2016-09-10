#ifndef _THREADS_H_
#define _THREADS_H_

struct user_thread_x {
    int pid;
    void * ustack;
    int used;
};

typedef struct __lock_t {
   volatile uint flag;
} lock_t;

typedef struct anderson_lock
{
  volatile uint flag[64];
} anderson;

static volatile uint num_of_passes;

int thread_create(void (*start_routine)(void*), void *arg);
int thread_join(void);
void lock_acquire(lock_t*);
void lock_release(lock_t*);
void lock_init(lock_t*);
int compare_pass(volatile uint *);

//int thread_create(void (*start_routine)(void*), void *arg);

#endif