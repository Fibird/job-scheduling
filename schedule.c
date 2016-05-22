#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#include "schedule.h"
#include "JCB.h"

static JCB *head;
int time_count = 0;

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

void FCFS_schedule()
{
    int i;
    while (head != NULL)
    {
        head->state = 1;
        JCB *p = head;
        while (1)
        {
            Sleep(1000);
            p->jjcb.runtime++;
            wait_time();
            if (p->jjcb.runtime == p->jjcb.reqtime)
            {
                i = p->jjcb.arrtime - 1;
                job_info[i] = p->jjcb;
                //job_info[i].arrtime = p->jjcb.arrtime;
                //job_info[i].name = p->jjcb.name;
                //job_info[i].reqtime = p->jjcb.reqtime;
                //job_info[i].resource = p->jjcb.resource;
                destory(p);
                //p->state = FINISH;
                break;
            }
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
    //printf("Please enter the number of the process: ");
    //scanf("%d", &num);
    //static JOB job_info[num];
    JCB *ptr;

    for (i = 0; i < num; i++)
    {
        printf("the ID of job:No.%d\n", i);
        ptr = getpch(JCB);
        printf("Please enter the name of the job: ");
        scanf("%s", ptr->jjcb.name);
        ptr->priority = num - i;
        ptr->jjcb.waitime = 0;
        printf("Please enter the time of the job need: ");
        scanf("%d", &ptr->jjcb.reqtime);
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
    p = NULL;
    free(p);
}
void *display(void *arg)
{
    JCB *p = NULL;
    while (head != NULL)
    {
        p = head;
        printf("**********************PROCESSES INFO***********************\n");
        printf("job name\tarrive time\tpriority\twait time\n");
        while (p != NULL)
        {
            if (p->state == 1)
            {
                printf("******job %s is running, its running time is %d sec******\n",
                       p->jjcb.name,
                       p->jjcb.runtime);
            }
            else if (p->state == 0)
            {
                get_info(p);
            }
            p = p->link;
        }
        Sleep(1000);
        //ÇåÆÁ²Ù×÷
        system("CLS");
    }
    pthread_exit(0);
    return NULL;
}

void get_info(JCB *job)
{
    printf("%s\t%d\t%d\t%d\n", job->jjcb.name, job->jjcb.arrtime,
           job->priority, job->jjcb.waitime);
}
