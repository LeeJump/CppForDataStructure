
// LinkList
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#define  OK 1
#define  ERROR -1
#define  MALLOC_ERROR -2
#define  INDEX_ERROR -3

// class define
template<class T_ELE>
class Vector
{
	public:
		Vector();
		Vector(DWORD dwSize);
		virtual ~Vector();
	public:
		DWORD at(DWORD dwIndex,OUT T_ELE* pEle);
		DWORD push(T_ELE ele);
		void  pop();
		DWORD insert(DWORD dwIndex,IN T_ELE Ele);
		void  erase(DWORD dwIndex);
		DWORD remainCapcity();
		DWORD size();
		void  clear();
		bool  empty();
	private:
		bool expand();
	private:
		DWORD m_dwLastIndex;
		DWORD m_dwIncrement;
		DWORD m_dwLen;
		DWORD m_dwInitSize;
		T_ELE* m_pVector;
};

// member function

template<class T_ELE>
Vector<T_ELE>::Vector()
:m_dwInitSize(10),m_dwIncrement(5)
{
	//default size=100
	T_ELE* pVector;
	if(pVector=new T_ELE[100])
	{
		this->m_dwLastIndex=0;
		this->m_dwLen=10;
		this->m_pVector=pVector;
		memset(pVector,0,sizeof(T_ELE)*this->m_dwLen);
		printf("malloc OK..\n len: %d\n",m_dwInitSize);
		
	}
	else
	{
		printf("MALLOC_ERROR\n");
		system("pause");
		
	}
	
	
}

template<class T_ELE>
Vector<T_ELE>::Vector(DWORD dwSize)
:m_dwIncrement(5)
{
	T_ELE* pVector;
	if(pVector=new T_ELE[dwSize])
	{
		this->dwLastIndex=0;
		this->m_dwLen=dwSize;
		this->m_pVector=pVector;
		this->m_dwInitSize=10;
		memset(pVector,0,sizeof(T_ELE)*this->m_dwLen);
		return OK;
	}
	else
	{
		printf("MALLOC_ERROR\n");
		system("pause");
		return MALLOC_ERROR;
	}
	
}

template<class T_ELE>
Vector<T_ELE>::~Vector()
{
	delete[] this->m_pVector;
	this->m_pVector=NULL;
	printf("Destructor finished..\n");
}

template<class T_ELE>
DWORD Vector<T_ELE>::at(DWORD dwIndex,OUT T_ELE* pEle)
{
	if(dwIndex < this->m_dwLastIndex)
	{
		T_ELE* src=&this->m_Vector[this->m_dwIndex];
		memcpy(pEle,src,sizeof(T_ELE));
		return OK;
	}
	else
	{
		printf("current Max index: %d\n",this->m_dwLastIndex-1);
		system("pause");
		return INDEX_ERROR;
	}
}

template<class T_ELE>
DWORD Vector<T_ELE>::push(T_ELE ele)
{
	if(this->m_dwLen < this->m_dwLastIndex+1)
	{
		this->expand();
	}
	T_ELE* des;
	des=m_pVector+m_dwLastIndex;
	memcpy(des,&ele,sizeof(T_ELE));
	this->m_dwLastIndex++;
	return OK;

} 

template<class T_ELE>
void Vector<T_ELE>::pop()
{
	if(this->m_dwLastIndex)
	{
		this->m_dwLastIndex--;
	}
	printf("pop finished..\n");
	
}

template<class T_ELE>
DWORD Vector<T_ELE>::insert(DWORD dwIndex,IN T_ELE Ele)
{
	if(this->m_dwLastIndex >= this->m_dwLen && dwIndex <= this->m_dwLastIndex)
	{
		this->expand();
	}
	else if(dwIndex > this->m_dwLastIndex)
	{
		return INDEX_ERROR;
	}
	this->m_dwLastIndex++;	
	for(int i=this->m_dwLastIndex ; i >= dwIndex ; i--)
	{
		T_ELE* ptr=this->m_pVector;
		T_ELE* src=ptr+i-1;
		T_ELE* des=ptr+i;
		memcpy(des,src,sizeof(T_ELE));
	}
	memcpy(this->m_pVector+dwIndex,&Ele,sizeof(T_ELE));
	printf("Insert OK..\n");
	return OK;
}

template<class T_ELE>
void Vector<T_ELE>::clear()
{
	this->m_dwLastIndex=0;
	printf("clear finished.\n");
}

template<class T_ELE>
bool Vector<T_ELE>::empty()
{
	if(this->m_dwLastIndex)
		return 0;
	else
		return 1;
}

template<class T_ELE>
bool Vector<T_ELE>::expand()
{
	DWORD newSize;
	T_ELE* des_pVector;
	T_ELE* src_pVector;
	newSize=this->m_dwLen+this->m_dwIncrement;

	if(des_pVector=new T_ELE[newSize])
	{
		memset(des_pVector,0,sizeof(T_ELE)*newSize);
		src_pVector=this->m_pVector;
		for(DWORD i=0;i<this->m_dwLen;i++)
		{
			memcpy(des_pVector+i,src_pVector+i,sizeof(T_ELE));
		}
		delete[] this->m_pVector;
		this->m_pVector=des_pVector;
		this->m_dwLen=newSize;
		return OK;
	}
	else
	{
		printf("malloc ERROR.\n");
		return ERROR;
	}
	
}

void test()
{
	Vector<int>* pVect=new Vector<int>();
	pVect->push(1);
	pVect->push(2);
	pVect->push(3);
	pVect->push(4);
	pVect->push(5);
	pVect->push(6);
	pVect->push(7);
	pVect->push(8);
	pVect->push(9);
	pVect->push(10);
	pVect->insert(1,0);
	delete pVect;
}
int main(int argc, char* argv[])
{	
	test();
	system("pause");
	return 0;
}
