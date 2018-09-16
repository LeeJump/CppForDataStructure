// LinkList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#define OK 1
#define ERROR -1
#define INDEX_ERROR -2
#define MALLOC_ERROR -3


//class define
template<class T_ELE>
class LinkedList
{
public:
	LinkedList();
	virtual ~LinkedList();
public:
	bool IsEmpty();
	void Clear();
	DWORD Append(IN T_ELE Ele);
	void Pop();
	DWORD Insert(IN T_ELE Ele,IN DWORD dwIndex);
	DWORD Delete(IN DWORD dwIndex);
	DWORD GetElementByIndex(IN DWORD dwIndex,OUT T_ELE& Ele);
	DWORD GetIndexByElement(IN T_ELE Ele,OUT DWORD& dwIndex);
	DWORD GetLen();
private:
	typedef struct _NODE
	{
		T_ELE Data;
		_NODE* pNext;
	}NODE,*PNODE;

private:	
	PNODE pHeader;
	DWORD len;
	
};

// member function define
template<class T_ELE>
LinkedList<T_ELE>::LinkedList()
{
	if(pHeader=new NODE())
	{
		len=0;
		pHeader->Data=0;
		pHeader->pNext=NULL;
	}
	else
	{
		// malloc error
		printf("malloc error\m");
	}
}

template<class T_ELE>
LinkedList<T_ELE>::~LinkedList()
{
	PNODE pNode;
	PNODE temp;
	pNode=pHeader->pNext;
	for(DWORD i=1;i<=len;i++)
	{
		temp=pNode;
		pNode=pNode->pNext;
		printf("%d\n",temp->Data);
		delete temp;
	}

	delete pHeader;
	printf("destructor!\n");
}

template<class T_ELE>
bool LinkedList<T_ELE>::IsEmpty()
{
	if(pHeader->pNext)
		return 0;
	else 
		return 1;
}

template<class T_ELE>
void LinkedList<T_ELE>::Clear()
{
	PNODE pNode;
	PNODE temp;
	pNode=pHeader->pNext;
	for(DWORD i=0;i<size;i++)
	{
		temp=pNode;
		pNode=pNode->pNext;
		delete temp;
	}

	delete pHeader;
	printf("destructor!\n");
}

template<class T_ELE>
DWORD LinkedList<T_ELE>::Append(IN T_ELE Ele)
{
	DWORD i;
	PNODE pNode=pHeader;
	PNODE pNew;
	i=len;
	// 1, create newNode
	pNew=new NODE();
	pNew->Data=Ele;
	pNew->pNext=NULL;
	// 2, Insert
	while(i--)
		pNode=pNode->pNext;

	pNode->pNext=pNew;
	this->len++;
	return OK;
}
template<class T_ELE>
void LinkedList<T_ELE>::Pop()
{
	if(this->len)
	{
		DWORD i=len-1;
		PNODE pNode=this->pHeader;
		while(i--)
			pNode=pNode->pNext;
		delete pNode->pNext;
		pNode->pNext=NULL;	
		this->len--;
	}
}
template<class T_ELE>
DWORD LinkedList<T_ELE>::Insert(IN T_ELE Ele,IN DWORD dwIndex)
{
	//dwIndex start at 1 .
	if(dwIndex<len)
	{
		// 1, create newNode
		PNODE pNew=new NODE();
		pNew->Data=Ele;
		pNew->pNext=NULL;
		// 2, insert 
		PNODE pNode=this->pHeader;
		DWORD i=dwIndex-1;
		while(i--)
			pNode=pNode->pNext;
		pNew->pNext=pNode->pNext;
		pNode->pNext=pNew;
		this->len++;
		return OK;
	}
	else if(dwIndex==len)
	{
		this->Append(Ele);
		return OK;
	}
	return INDEX_ERROR;
}
template<class T_ELE>
DWORD LinkedList<T_ELE>::Delete(IN DWORD dwIndex)
{
	// dwIndex start at 1
	if(dwIndex < this->len)
	{	
		DWORD i=dwIndex-1;
		PNODE pNode=pHeader;
		PNODE des;
		while(i--)
			pNode=pNode->pNext;
		des=pNode->pNext;
		pNode->pNext=des->pNext;
		this->len--;
		delete des;

	}
	else if(dwIndex == this->len)
	{
		this->Pop();
		return OK;
	}
	return INDEX_ERROR;
}
template<class T_ELE>
DWORD LinkedList<T_ELE>::GetElementByIndex(IN DWORD dwIndex,OUT T_ELE& Ele)
{
	if(dwIndex <= len)
	{
	
		PNODE pNode=pHeader;
		for(DWORD i=1;i<=dwIndex;i++)
			pNode=pNode->pNext;
		Ele=pNode->Data;
		return OK;
	}
	return INDEX_ERROR;
}
template<class T_ELE>
DWORD LinkedList<T_ELE>::GetIndexByElement(IN T_ELE Ele,OUT DWORD& dwIndex)
{
	DWORD i=len;
	PNODE pNode=pHeader;
	while(i--)
	{
		pNode=pNode->pNext;
		if(pNode->Data == Ele)
		{
			dwIndex=len-i;
			return dwIndex;
		}
	}
	return ERROR;
}

template<class T_ELE>
DWORD LinkedList<T_ELE>::GetLen()
{
	return this->len;
}

//main function
int main(int argc, char* argv[])
{
	LinkedList<DWORD>* pLinkList=new LinkedList<DWORD>();
	pLinkList->Append(1);
	pLinkList->Append(2);
	pLinkList->Append(3);
	pLinkList->Append(4);
	pLinkList->Append(5);
	pLinkList->Pop();
	pLinkList->Insert(11,1);
	pLinkList->Delete(2);

	DWORD ele,index;

	pLinkList->GetElementByIndex(2,ele);
	pLinkList->GetIndexByElement(11,index);
	printf("index 2 : %d\n",ele);
	printf("data 3 : %d\n",index);
	
	
	delete pLinkList;
	
	return 0;
}