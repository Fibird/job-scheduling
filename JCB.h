#ifndef JCB_H_INCLUDED
#define JCB_H_INCLUDED

typedef struct job
{
    char name[10];
    int reqtime;
    int runtime;
    int arrtime;
    int waitime;
    int resource;
    struct job* link;
}JOB;

typedef struct jcb
{
    JOB* jjcb;
    int state;
    int priority;
    struct jcb* link;
}JCB;

#endif // JCB_H_INCLUDED
