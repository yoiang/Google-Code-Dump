#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "FTPSite.h"
#include <afxcmn.h>

class Node
{
public:
	Node *m_pHashNext ;
	Node *m_pHashPrevious ;

	Node *m_pListNext ;
	Node *m_pListPrevious ;

	FTPSite *m_pValue ;
	Node(FTPSite *pValue) ;
	~Node() ;
} ;

class HashTable
{
private:
	Node **m_pHashTable ;

	Node **m_pPollingTable ;
	int *m_iPollingLengths ;

	int m_iSize ;

	int GetKey(CString cstrName) ;
	bool AddToHash(FTPSite *pAdd, Node *&pAdded, int &iOriginalPolling) ;
	void AddToList(Node *pAdd) ;

	void RemoveFromList(Node *pRemove, int iPolling) ;

public:
	HashTable(int iSize) ;
	~HashTable() ;

	void CallPolling(UINT nTimerID) ;
	bool Add(FTPSite *pAdd) ;
	void Remove(char *szName) ;
	FTPSite *Get(char *szName) ;
} ;

#endif 