# Thread-Implementation-in-XV6
# AUTHOR: Phanikar Subodh Krishna Chereddi
# email: pcher003@ucr.edu, subodhkrishnacp@gmail.com

XV-6 is a operating system used for teaching purpose and it was developed by a MIT group
I changed few systemcall and implemented a new one clone to implement kernel threads

clone systemcall:
It is similar to fork but with a few differences like it will share the addressspace 
insted of creating a new one like in fork systemcall

wait and exit system call are also modified in order to implement threads. 
whenever these two are called it chceks info about if there are any other procs/threads 
running in the same addressspace and proceeds further.
