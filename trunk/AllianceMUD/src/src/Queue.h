/*

  Queue.h
  Version 0.004.000

*/

#ifndef __QUEUE_H__
#define __QUEUE_H__

template <class QueueNodeType>
struct QueueNode
{
 QueueNodeType *Data ;

 QueueNode<QueueNodeType> *pNext ;
} ;

template <class QueueType>
class Queue
{
private:
 int nNumQueues ;
 QueueNode<QueueType> *QueueHead ;
 QueueNode<QueueType> *QueueTail ;

public:
 Queue() ;
 ~Queue() ;

 int Push (QueueType *pPushData) ;
 int Pop (QueueType *&pPopData) ;
 int NumQueues () ;
} ;

#endif // __QUEUE_H__