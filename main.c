#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "JCB.h"
#include "schedule.h"

int main()
{
    pthread_t dis_thread;
    void *dis_result;
    //JOB *job_info;
    int i;
    int num;
    printf("Please enter the number of the process: ");
    scanf("%d", &num);
    job_info = (JOB*)malloc(num * sizeof(JOB));

    input(num);
    system("CLS");
    pthread_create(&dis_thread, NULL, display, NULL);
    FCFS_schedule();
    pthread_join(dis_thread, &dis_result);
    printf("All jobs has finished.\n");
    printf("The info of these jobs is blew:\n");
    for (i = 0; i < num; i++)
    {
        printf("%s\t%d\t&d\t%d\n", job_info[i].name, job_info[i].arrtime, job_info[i].runtime, job_info[i].waitime);
    }
    return 0;
}
