/*

  Queue.cpp
  Version 0.004.000

*/

#include "Main.h"

template <class QueueType>
Queue<QueueType>::Queue ()
{
 nNumQueues = 0 ;
 QueueHead = NULL ;
 QueueTail = NULL ;
}

template <class QueueType>
Queue<QueueType>::~Queue ()
{
 QueueNode<QueueType> *pQueueNewHead ;
 while (QueueHead != NULL)
 {
  pQueueNewHead = QueueHead->pNext ;
  pPopData = QueueHead->Data ;
  delete QueueHead ;
  QueueHead = pQueueNewHead ;
 }
}

template <class QueueType>
int Queue<QueueType>::Push (QueueType *pPushData)
{
 if (QueueHead == NULL)
 {
  QueueHead = new QueueNode<QueueType> ;
  QueueTail = QueueHead ;
 } else
 {
  QueueTail->pNext = new QueueNode<QueueType> ;
  QueueTail = QueueTail->pNext ;
 }
 QueueTail->Data = pPushData ;
 QueueTail->Data = NULL ;
 nNumQueues ++ ;
 return nNumQueues ;
}

template <class QueueType>
int Queue<QueueType>::Pop (QueueType *&pPopData)
{
 if (QueueHead == NULL) 
 {
  pPopData = NULL ;
  return 0 ;
 }

 QueueNode<QueueType> *pQueueNewHead = QueueHead->pNext ;
 pPopData = QueueHead->Data ;
 delete QueueHead ;
 QueueHead = pQueueNewHead ;
 nNumQueues -- ;
 return nNumQueues ;
}

template <class QueueType>
int Queue<QueueType>::NumQueues()
{ return nNumQueues ; }