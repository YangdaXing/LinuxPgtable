/************************************************************ 
 *File Name: getitem.c
 *Author: YangDaxing
 *Version: 1.0
 *Date: 2019年10月18日 星期五 13时51分49秒
 ------------------------------------------------------------
 *Description: 

 ***********************************************************/
#include <hduos.h>

pid32 getfirst(
               qid16 q
              )
{
    pid32 head;
    if(isempty(q)){
        return EMPTY;
    }

    head = queuehead(q);
    return getitem(queuetab[head].qnext);
}

pid32 getlast(
              qid16 q
             )
{
    pid32 tail;
    if(isempty(q)){
        return EMPTY;
    }

    tail = queuetail(q);
    return getitem(queuetab[tail].qprev);
}

pid32 getitem(
              pid32 pid
             )
{
    pid32 prev,next;

    next = queuetab[pid].qnext;
    prev = queuetab[pid].qnext;
    queuetab[prev].next = next;
    queuetab[next].qprev = prev;

    return pid;
}
