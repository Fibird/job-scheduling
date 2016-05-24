#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#include "schedule.h"
#include "JCB.h"

static int time_count = 0;
static int RESOURCE = 10;
void join(JCB *ptr)
{
    JCB *p = NULL;

    if (head == NULL)
    {
        head = ptr;
    }
    else
    {
        p = head;
        while (p->link != NULL)
        {
            p = p->link;
        }
        p->link = ptr;
    }
    ptr->jjcb.arrtime = time_count++;
    ptr->link = NULL;
}

void PSA_schedule()
{
    JCB *p;
    JCB *hp, *lp;
    //scan all the jobs and allocate resource to jobs
    JCB *scan;
    int i;
    int remainder = 0;
    int TIME_SLICE = 3;
    //p = head;
    //lp = head->link;
    while (head != NULL)
    {
        scan = head;
        while (scan != NULL)
        {
            hp = head;
            lp = head->link;
            //find the job which has highest priority
            while (lp != NULL)
            {
                if ((hp->priority < lp->priority) && (lp->state != READY))
                {
                    hp = lp;
                }
                lp = lp->link;
            }
            if (hp->jjcb.resource < RESOURCE)
            {
                hp->state = READY;
                RESOURCE -= hp->jjcb.resource;
            }
            else
            {
                //if the job of higher priority
                //don't have enough resource,
                //wait until resource is enough
                break;
            }
            scan = scan->link;
        }
        p = head;
        while (p != NULL)
        {
            if (p->state == READY)
            {
                //进程所需时间对时间片取余
                remainder = p->jjcb.reqtime % TIME_SLICE;
                if ((p->jjcb.reqtime - p->jjcb.runtime) == remainder)
                {
                    p->jjcb.runtime += remainder;
                }
                else
                {
                    p->jjcb.runtime += TIME_SLICE;
                }
                //p->state = 1;
                Sleep(1000 * TIME_SLICE);
                wait_time();
                //p->state = 0;
                if (p->jjcb.runtime == p->jjcb.reqtime)
                {
                    i = p->jjcb.arrtime;
                    job_info[i] = p->jjcb;
                    //it is useless now
                    p->state = FINISH;
                    RESOURCE += p->jjcb.resource;
                    destory(p);
                }
            }
            p = p->link;
        }
    }
}

void wait_time()
{
    JCB *p;
    p = head;

    while (p != NULL)
    {
        if (p->state != 1)
        {
            p->jjcb.waitime++;
        }
        p = p->link;
    }
}
void input(int num)
{
    int i;
    JCB *ptr;

    for (i = 0; i < num; i++)
    {
        printf("the ID of job:No.%d\n", i);
        ptr = getpch(JCB);
        printf("Please enter the name of the job: ");
        scanf("%s", ptr->jjcb.name);
        ptr->jjcb.waitime = 0;
        printf("Please enter the number of resource the job need: ");
        scanf("%d", &ptr->jjcb.resource);
        printf("Please enter the time of the job need: ");
        scanf("%d", &ptr->jjcb.reqtime);
        ptr->priority = 20 - ptr->jjcb.reqtime;
        printf("\n");
        ptr->jjcb.runtime = 0;
        ptr->state = WAIT;
        ptr->link = NULL;
        join(ptr);
    }
}

void destory(JCB *p)
{
    JCB *pre, *cur;
    pre = cur = head;
    if (p == head)
    {
        head = p->link;
    }
    else
    {
        while (!(cur->jjcb.name == p->jjcb.name || cur == NULL))
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
    }
    p = NULL;
    free(p);
}
void *display(void *arg)
{
    JCB *p = NULL;
    while (head != NULL)
    {
        p = head;
        printf("*****************NUM OF RESOURCE:%d**********************\n", RESOURCE);
        printf("************************JOB INFO*************************\n");
        printf("job name\tarrive time\tpriority\twait time\tstate\trun time\n");
        while (p != NULL)
        {
            get_info(p);
            p = p->link;
        }
        Sleep(1000);
        //clear screen
        system("CLS");
    }
    pthread_exit(0);
    return NULL;
}

void get_info(JCB *job)
{
    printf("%-8s\t%-11d\t%-8d\t%-9d\t%d\t%d\n", job->jjcb.name, job->jjcb.arrtime,
           job->priority, job->jjcb.waitime, job->state, job->jjcb.runtime);
}
