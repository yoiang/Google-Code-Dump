#include "HashTable.h"

#include <string.h>

Node::Node(FTPSite *pValue)
{
	m_pValue = pValue ;
	m_pHashNext = NULL ;
	m_pHashPrevious = NULL ;

	m_pListNext = NULL ;
	m_pListPrevious = NULL ;
}

Node::~Node()
{
	if (m_pHashNext != NULL) m_pHashNext->m_pHashPrevious = m_pHashPrevious ;
	if (m_pHashPrevious != NULL) m_pHashPrevious->m_pHashNext = m_pHashNext ;

	if (m_pListNext != NULL) m_pListNext->m_pListPrevious = m_pListPrevious ;
	if (m_pListPrevious != NULL) m_pListPrevious->m_pListNext = m_pListNext ;

	if (m_pValue != NULL) delete m_pValue ;
}

HashTable::HashTable(int iSize) 
{
	m_iSize = iSize ;
	m_pHashTable = new Node*[iSize] ;
	for (int iTrav = 0 ; iTrav < m_iSize ; iTrav ++)
		m_pHashTable[iTrav] = NULL ;

	m_pPollingTable = new Node*[POLL_NUM_TYPES-1] ;
	for (iTrav = 0 ; iTrav < POLL_NUM_TYPES-1 ; iTrav ++)
		m_pPollingTable[iTrav] = NULL ;

	m_iPollingLengths = new int[POLL_NUM_TYPES-1] ;
	for (iTrav = 0 ; iTrav < POLL_NUM_TYPES-1 ; iTrav ++)
		m_iPollingLengths[iTrav] = 0 ;
}

HashTable::~HashTable()
{
	for (int iTrav = 0 ; iTrav < m_iSize ; iTrav ++)
	{
		while (m_pHashTable[iTrav] != NULL && m_pHashTable[iTrav]->m_pHashNext != NULL)
			delete m_pHashTable[iTrav]->m_pHashNext ;
		if (m_pHashTable[iTrav] != NULL) delete m_pHashTable[iTrav] ;
	}
	delete [] m_pHashTable ;

	delete [] m_pPollingTable ;

	delete [] m_iPollingLengths ;
}

int HashTable::GetKey(CString cstrName)
{
	int iKey = 0 ;

	for (int iTrav = 0 ; cstrName.GetLength() > iTrav ; iTrav ++)
		iKey += cstrName[iTrav] ;

	return iKey % m_iSize ;
}


bool HashTable::AddToHash(FTPSite *pAdd, Node *&pAdded, int &iOriginalPolling)
{
	int iKey = GetKey(pAdd->GetName()) ;

	Node *pNewNode = new Node(pAdd) ;
	Node *pTempNode ;
	if (m_pHashTable[iKey] == NULL)
	{
		m_pHashTable[iKey] = pNewNode ;
	} else
	{
		pTempNode = m_pHashTable[iKey] ;
		while (pTempNode->m_pHashNext != NULL) 
		{
			if (strcmp(pTempNode->m_pValue->GetName(), pNewNode->m_pValue->GetName()) == 0)
			{
				iOriginalPolling = pTempNode->m_pValue->GetPolling() ;
				delete pTempNode->m_pValue ;
				pTempNode->m_pValue = pNewNode->m_pValue ;
				pNewNode->m_pValue = NULL ;
				delete pNewNode ;

				pAdded = pTempNode ;
				return false ;
			}
			pTempNode = pTempNode->m_pHashNext ;
		}

		if (strcmp(pTempNode->m_pValue->GetName(), pNewNode->m_pValue->GetName()) == 0)
		{
			iOriginalPolling = pTempNode->m_pValue->GetPolling() ;
			delete pTempNode->m_pValue ;
			pTempNode->m_pValue = pNewNode->m_pValue ;
			pNewNode->m_pValue = NULL ;
			delete pNewNode ;

			pAdded = pTempNode ;
			return false ;
		}

		pTempNode->m_pHashNext = pNewNode ;
		pNewNode->m_pHashPrevious = pTempNode ;
	}
	pAdded = pNewNode ;
	iOriginalPolling = 0 ;
	return true ;
}

void HashTable::AddToList(Node *pAdd)
{
	int iCurrentPolling = pAdd->m_pValue->GetPolling() ; 

	if (iCurrentPolling > 0 && iCurrentPolling < POLL_NUM_TYPES)
	{

		if (m_pPollingTable[iCurrentPolling-1] == NULL)
		{
			m_pPollingTable[iCurrentPolling-1] = pAdd ;
		} else
		{
			pAdd->m_pListNext = m_pPollingTable[iCurrentPolling-1] ;
			m_pPollingTable[iCurrentPolling-1]->m_pListPrevious = pAdd ;
			pAdd->m_pListNext = m_pPollingTable[iCurrentPolling-1] ;
			m_pPollingTable[iCurrentPolling-1] = pAdd ;
		}

		m_iPollingLengths[iCurrentPolling-1] ++ ;
	}
}

bool HashTable::Add(FTPSite *pAdd) 
{
	Node *pNodeAdded ;
	int iOriginalPolling ;
	bool bNew = AddToHash(pAdd, pNodeAdded, iOriginalPolling) ;

	if (iOriginalPolling != pNodeAdded->m_pValue->GetPolling()) 
	{
		RemoveFromList(pNodeAdded, iOriginalPolling) ;
	
		AddToList(pNodeAdded) ;
	}

	return bNew ;
}

void HashTable::RemoveFromList(Node *pRemove, int iPolling)
{
	if (iPolling > 0 && iPolling < POLL_NUM_TYPES)
	{
		if (m_pPollingTable[iPolling-1] == pRemove)
		{
			m_pPollingTable[iPolling-1] = pRemove->m_pListNext ;
			if (pRemove->m_pListNext != NULL) pRemove->m_pListNext->m_pListPrevious = NULL ;
			pRemove->m_pListNext = NULL ;
		} else
		{
			if (pRemove->m_pListNext != NULL) pRemove->m_pListNext->m_pListPrevious = pRemove->m_pListPrevious ;
			if (pRemove->m_pListPrevious != NULL) pRemove->m_pListPrevious->m_pListNext = pRemove->m_pListNext ;
			pRemove->m_pListNext = NULL ;
			pRemove->m_pListPrevious = NULL ;
		}

		m_iPollingLengths[iPolling-1] -- ;
	}
}

void HashTable::Remove(char *szName)
{
	int iKey = GetKey(szName) ;

	Node *pTempNode = m_pHashTable[iKey] ;
	while (pTempNode != NULL)
	{
		if (strcmp(pTempNode->m_pValue->GetName(), szName) == 0) 
		{
			if (pTempNode == m_pHashTable[iKey]) m_pHashTable[iKey] = pTempNode->m_pHashNext ;

			RemoveFromList(pTempNode, pTempNode->m_pValue->GetPolling()) ;

			delete pTempNode ;
			return ;
		}
		pTempNode = pTempNode->m_pHashNext ;
	}
}

FTPSite *HashTable::Get(char *szName)
{
	int iKey = GetKey(szName) ;

	Node *pTempNode = m_pHashTable[iKey] ;
	while (pTempNode != NULL)
	{
		if (strcmp(pTempNode->m_pValue->GetName(), szName) == 0) return pTempNode->m_pValue ;
		pTempNode = pTempNode->m_pHashNext ;
	}
	return NULL ;
}

void HashTable::CallPolling(UINT nTimerID) 
{
	Node *pHourlyNodes ;
	for (int iTrav = 0 ; iTrav < POLL_NUM_TYPES - 1 ; iTrav ++)
	{
		pHourlyNodes = m_pPollingTable[iTrav] ; 
		while (pHourlyNodes != NULL)
		{
			if (pHourlyNodes->m_pValue->GetTimerID() == nTimerID)
			{
				pHourlyNodes->m_pValue->DoTask() ;
				return ;
			}
			pHourlyNodes = pHourlyNodes->m_pListNext ;
		}
	}
}