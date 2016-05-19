#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED
#include "JCB.h"

//append new job in the queue
void join();
//acquire the information of the job
void get_info(JCB* job);
//delete the job if it is finished
void destory(JCB *p);
#endif // SCHEDULE_H_INCLUDED
