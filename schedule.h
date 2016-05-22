#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED
#include "JCB.h"
#define getpch(type) (type*)malloc(sizeof(type))

#define WAIT 0
#define READY 1
#define FINISH -1

//array to save the information of jobs after it is finished
JOB *job_info;
//append new job in the queue
void join(JCB *);
//acquire the information of the job
void get_info(JCB* job);
//schedule jobs by FCFS
void FCFS_schedule();
//update wait time of every job
void wait_time();
//display information in real time in another thread
void *display(void *arg);
//input the information of jobs
void input(int);
//delete the job if it is finished
void destory(JCB *p);
#endif // SCHEDULE_H_INCLUDED
