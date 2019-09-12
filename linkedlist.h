#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H
/* Contains implementation of linked list for maintaining list of jobs */

//create job struct
struct jobNode *createJobNode(int pid, char *name);

//add job to end of linked list
void addJobNode(struct jobNode *job);

//delete job with given PID from linked list
void deleteJobNode(int pid);

//return head of linked list
struct jobNode *getHead();


#endif