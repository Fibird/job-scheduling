#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "JCB.h"
#include "schedule.h"

int main()
{
    pthread_t dis_thread;
    void *dis_result;
    int i;
    int num;
    //declare the cycle time and cycle time with weight
    int turnaround_time, completion_time, start_time;
    double wturnaround_time;

    printf("Please enter the number of the jobs: ");
    scanf("%d", &num);
    job_info = (JOB*)malloc(num * sizeof(JOB));
    input(num);
    //clear screen
    system("CLS");
    //create another thread to display info of jobs in real time
    pthread_create(&dis_thread, NULL, display, NULL);
    //use FCFS to schedule jobs
    //FCFS_schedule();
    PSA_schedule();
    pthread_join(dis_thread, &dis_result);
    printf("All jobs has finished.\n");
    printf("*************The info of these jobs after running*************\n");
    printf("job name\tstart time\tcompletion time\tturnaround time\twturnaround time\n");
    for (i = 0; i < num; i++)
    {
        //compute turnaround time, turnaround time with weight and completion time
        start_time = job_info[i].arrtime + job_info[i].waitime;
        completion_time = job_info[i].arrtime + job_info[i].waitime + job_info[i].runtime;
        turnaround_time = job_info[i].waitime + job_info[i].runtime;
        wturnaround_time = (double)turnaround_time / (double)job_info[i].runtime;
        printf("%-8s\t%-10d\t%-15d\t%-16d\t%lf\n", job_info[i].name, start_time, completion_time, turnaround_time, wturnaround_time);
    }
    return 0;
}
