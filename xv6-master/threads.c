#include "types.h"
/*#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"*/
#include "user.h"
/*#include "syscall.h"
#include "traps.h"*/
#include "x86.h"
#include "threads.h"
#include "param.h"

struct user_thread_x threads[NPROC]; //thread table
volatile uint flags[NPROC];
int queuelast = 0;
int current = 0;

// add thread to thread table
void add_thread(int * pid, void * ustack){
    int c;
    for(c = 0; c < NPROC; c++){
        if(threads[c].used == 0){
            threads[c].pid = *pid;
            threads[c].ustack = ustack;
            threads[c].used = 1;
        }
    }
}

void remove_thread(int * pid){
    int c;
    void * ustack; 
    for(c = 0; c < NPROC; c++){
        if(threads[c].used && threads[c].pid == *pid){
            ustack = threads[c].ustack;
            free(ustack);
            threads[c].pid = 0;
            threads[c].ustack = 0;
            threads[c].used = 0;
            break;
        } 
    }
}

int thread_create(void (*start_routine)(void*), void *arg){
    // If first time running any threads, initialize thread table with zeros
    int c;
    for(c = 0; c < NPROC; c++){
        threads[c].pid = 0;
        threads[c].ustack = 0;
        threads[c].used = 0;
    }
    int pid;
    void * new_stack = malloc(KSTACKSIZE); // allocate one page for user stack 
    pid = clone((void *) start_routine, (void *) arg, (void *) new_stack); // system call for kernel thread
    if(pid == 0) {
        //  call start_routine
    }

    //printf(1, "pid created : %d", pid);
    add_thread(&pid, new_stack); // save new thread to thread table
    return pid; 
}

int thread_join(void){
    int c, p;
    for(c = 0; c < NPROC; c++){ 
        if(threads[c].used == 1){
            p = join(&threads[c].ustack);

            if(p > 0){
                remove_thread(&p); 
                break;
            }
        }
    }
    return p;
}


void lock_acquire(lock_t * lock){
    volatile uint zero = (uint) 0;
    int my_place = queuelast;
    queuelast++;
    while(xchg(&flags[my_place % NPROC], zero)  == zero)
      ;
    current = my_place;
};

void lock_release(lock_t * lock){
    flags[current % NPROC] = 0; 
    //printf(1, "thread %d releasing lock\n", current);
    flags[(current+1) % NPROC] = 1;
}

void lock_init(lock_t * lock){
   // 0 means lock is available 1 means lock is taken
   lock->flag = 0;
   int i;
   for(i=0; i < NPROC; i++){
     flags[i] = 0;
   }
   flags[0] = 1;
}

int compare_pass(volatile uint * pass) {
    volatile uint zero = 0;
    if(xchg(pass, zero)  == zero)
        return 0;
    return 1;
}