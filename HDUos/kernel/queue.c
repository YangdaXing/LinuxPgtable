/************************************************************ 
 *File Name: queue.c
 *Author: YangDaxing
 *Version: 1.0
 *Date: 2019年10月18日 星期五 14时06分12秒
 ------------------------------------------------------------
 *Description:enqueue() dequeue() 

 ***********************************************************/
#include <hduos.h>


struct qentry queuetab[NQENT];

/*
 *insert a node from the tail  
 */
pid32 enqueue(
              pid32 pid;
              qid16 q;
             )
{
    qid16 tail , prev;

    if(isbadqid(q) || isbadpid(pid)){
        return SYSERR;
    }

    tail = queuetail(q);
    prev = queuetab[tail].qprev;

    queuetab[pid].qnext = tail;
    queuetab[pid].qprev = prev;
    queuetab[prev].qnext = pid;
    queuetab[tail].qprev = pid;
    return pid;
}

/*
 *remove a node from the head 
 */
pid32 dequeue(
              qid16 q
             )
{
    pid32 pid;

    if(isbadqid(q)){
        return SYSERR;
    }else if (isempty(q)){
        return EMPTY;
    }

    pid = getfirst(q);
    
    queuetab[pid].qprev = EMPTY;
    queuetab[pid].qnext = EMPTY;

    return pid;
}
