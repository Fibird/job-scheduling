#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#include "schedule.h"
#include "JCB.h"

static JCB *ready;
static int time_count = 0;

void join(JCB *ptr)
{
    JCB *p = NULL;

    if (ready == NULL)
    {
        ready = ptr;
    }
    else
    {
        p = ready;
        while (p->link != NULL)
        {
            p = p->link;
        }
        p->link = ptr;
    }
    ptr->time.arrtime = time_count + 1;
}

void FCFS_schedule()
{
    while (ready != NULL)
    {
        ready->state = 1;
        JCB *p = ready;
        while (1)
        {
            p->time.runtime++;
            Sleep(1000);
            if (p->time.runtime == p->time.reqtime)
            {
                destory(p);
                break;
            }
        }
    }
}

void destory(JCB *p)
{
    JCB *pre, *cur;
    pre = cur = ready;
    if (p == ready)
    {
        ready = p->link;
    }
    while (!(cur->name == p->name || cur == NULL))
    {
        pre = cur;
        cur = cur->link;
    }
    if (cur != NULL)
    {
        pre->link = cur->link;
    }
    else
    {
        pre->link = NULL;
    }
    p = NULL;
    free(p);
}

void get_info(JCB *job)
{
    printf("time\tjobs\tpriority\tstate\truntime\treqtime");
    //printf("%d\t", )
}
