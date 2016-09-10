#include "types.h"
#include "stat.h"
#include "user.h"
//#include "fs.h"
//#include "fcntl.h"
//#include "syscall.h"
//#include "traps.h"
//#include "defs.h"
#include "threads.h"

lock_t lock;
void print537(void * arg){
	while(num_of_passes > 0) {
		lock_acquire(&lock);
		if(num_of_passes > 0) {
			printf(1, "Running thread %d with token %d\n", getpid(), num_of_passes);
			num_of_passes--;
		}
		lock_release(&lock);
	} 	
    exit();
}

int
main(int argc, char *argv[])
{
 int num_of_threads = atoi(argv[1]);
 char * num = argv[2];
 num_of_passes = atoi(num);
 int i;

 lock_init(&lock);
 for(i=0; i<num_of_threads; i++){
 	int pid = thread_create((void *)&print537, num);
 	//printf(1, "created thread with pid %d\n", pid);
 	if(pid == 0)
 		break;
 	
 }
 
 for(i=0; i<num_of_threads; i++) {
 	thread_join();
 }
 printf(1, "Done passing the frisbee\n");
 printf(1, "\nExiting main now\n");
 exit();
 return 0;
}
