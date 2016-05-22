#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED
#include "JCB.h"
#define getpch(type) (type*)malloc(sizeof(type))

#define WAIT 0
#define READY 1
#define FINISH -1

extern int time_count;
JOB *job_info;
//append new job in the queue
void join(JCB *);
//acquire the information of the job
void get_info(JCB* job);
//sort the job by arriving time
void FCFS_schedule();
void wait_time();
void *display(void *arg);
void input(int);
//delete the job if it is finished
void destory(JCB *p);
#endif // SCHEDULE_H_INCLUDED
