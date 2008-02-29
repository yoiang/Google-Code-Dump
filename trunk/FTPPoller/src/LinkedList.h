#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

template <class LLNType>
class LinkedListNode	// linked list node
{
public:
	LLNType *pValue ;
	LinkedListNode *pLast, *pNext ;

	LinkedListNode() ;
	~LinkedListNode() ;
} ;

template <class LLType>
class LinkedList	// linked list class
{
public:
	LinkedListNode<LLType> *pHead, *pTail ;
	LinkedList() ;
	~LinkedList() ;

	void AddFront(LLType *pAdd) ;
	void AddBack(LLType *pAdd) ;
	void Remove(LinkedListNode<LLType> *pRemove, bool bDeleteValue) ;

	void Clear(bool bDeleteValue) ;
} ;

template <class LLNType>
LinkedListNode<LLNType>::LinkedListNode()
{
}

template <class LLNType>
LinkedListNode<LLNType>::~LinkedListNode()
{
}

template <class LLType>
LinkedList<LLType>::LinkedList()
{
	pHead = 0 ;
	pTail = 0 ;
}

template <class LLType>
LinkedList<LLType>::~LinkedList()
{
	Clear(false) ;
}

template <class LLType>
void LinkedList<LLType>::AddFront(LLType *pAdd)	// add to the front of the list
{
	LinkedListNode<LLType> *pNew = new LinkedListNode<LLType> ;
	if (pNew == 0) exit(-1) ;
	pNew->pValue = pAdd ;
	if (pHead == 0)
	{
		pHead = pNew ;
		pTail = pNew ;
		pNew->pNext = 0 ;
		pNew->pLast = 0 ;
	} else
	{
		pHead->pLast = pNew ;
		pNew->pNext = pHead ;
		pNew->pLast = 0 ;
		pHead = pNew ;
	}
}

template <class LLType>
void LinkedList<LLType>::AddBack(LLType *pAdd)	// add to back of list
{
	LinkedListNode<LLType> *pNew = new LinkedListNode<LLType> ;
	if (pNew == 0) exit(-1) ;
	pNew->pValue = pAdd ;
	if (pHead == 0)
	{
		pHead = pNew ;
		pTail = pNew ;
		pNew->pNext = 0 ;
		pNew->pLast = 0 ;
	} else
	{
		pTail->pNext = pNew ;
		pNew->pLast = pTail ;
		pNew->pNext = 0 ;
		pTail = pNew ;
	}
}

template <class LLType>
void LinkedList<LLType>::Remove(LinkedListNode<LLType> *pRemove, bool bDeleteValue) // remove list
{
	if (pRemove == pHead && pRemove == pTail)
	{
		pHead = 0 ;
		pTail = 0 ;
 		if (bDeleteValue) delete pRemove->pValue ;
		delete pRemove ;
	} else if (pRemove == pHead)
	{
		pHead = pHead->pNext ;
		pHead->pLast = 0 ;
		if (bDeleteValue) delete pRemove->pValue ;
		delete pRemove ;
	} else if (pRemove == pTail)
	{
		pTail = pTail->pLast ;
		pTail->pNext = 0 ;
		if (bDeleteValue) delete pRemove->pValue ;
		delete pRemove ;		
	} else
	{
		pRemove->pNext->pLast = pRemove->pLast ;
		pRemove->pLast->pNext = pRemove->pNext ;
		if (bDeleteValue) delete pRemove->pValue ;
		delete pRemove ;
	}
}

template <class LLType>
void LinkedList<LLType>::Clear(bool bDeleteValue) // clear linked list
{
	if (pHead == 0) return ;

	LinkedListNode<LLType> *pTemp ;
	pTemp = pHead ;
	while (pTemp != 0)
	{
		pHead = pHead->pNext ;
		if (bDeleteValue) delete pTemp->pValue ;
		delete pTemp ;
		pTemp = pHead ;
	}
	pTail = 0 ;
}



#endif