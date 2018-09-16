#include "stdafx.h"
#include "windows.h"
#define OK 1
#define ERROR 0

// class Define

class Monster
{
	public:
		DWORD id;
		DWORD level;
		char* name[20];
		Monster()
		{
			id=0;
			level=0;
			memset(this->name,0,20);
		}
		Monster(DWORD id,DWORD level,char* name)
		{
			this->id=id;
			this->level=level;
			memcpy(this->name,name,strlen(name)+1);
		}
};


template<class T_ELE>
class BNode
{
	public:
		T_ELE data;
		BNode<T_ELE>* left;
		BNode<T_ELE>* right;
		BNode()
		{
			memset(&data,0,sizeof(T_ELE));
			left=right=NULL;
		}
		BNode(const T_ELE& ele)
		{
			memcpy(&data,&ele,sizeof(T_ELE));
			left=right=NULL;
			
		}
		void Visit()
		{
			printf("%s\n",this->data.name);
		}
};

template<class T_ELE>
class Stack
{
public:
	Stack()
	{
		this->size=10;
		this->top=-1
		pStack=new BNode<T_ELE>*[size];
		top=0;

	}
	Stack(DWORD size)
	{
		this->size=size;
		this->top=-1;
		pStack=new BNode<T_ELE>*[size];

	}
	virtual ~Stack()
	{
		delete[] pStack;
		pStack=NULL;
		printf("destruct func.\n");
	}
public:
	void Push(BNode<T_ELE>* pEle)
	{
		*(pStack+top+1)=pEle;
		top++;
	}
	void Pop(BNode<T_ELE>** pEle)
	{
		*pEle=*(pStack+top);	
		top--;
	}
	DWORD Empty()
	{
		if(top==-1)
			return 1;
		return 0;
	}
private:
	BNode<T_ELE>** pStack; // BNode<T_ELE>* pStack[];
	DWORD size;
	int top;

};

template<class T_ELE>
class Array
{
public:
	Array()
	{
		this->len=10
		pArray=new BNode<T_ELE>(this->len);
		this->nextIndex=0;
	}
	Array(DWORD size)
	{
		this->len=size;
		this->nextIndex=0;
		pArray=new BNode<T_ELE>(this->size);
	}
	virtual ~Array()
	{
		delete pArray;
	}
	DWORD Append(BNode<T_ELE>* pNode)
	{
		*(pArray+nextIndex)=pNode;
		nextIndex++;
	}
	void Traverse()
	{
		if(nextIndex>=0)
		{
			for(DWORD i=0; i<nextnextIndex;i++)
			{
				*(pArray+i)->Visit();
			}
			
		}
	}
private:
	BNode<T_ELE>** pArray;
	DWORD nextIndex;
	DWORD len;

};

template<class T_ELE>
class BTree
{
	public:
		BTree();
		virtual ~BTree();
	public:
		DWORD AppendNodeByLevel(IN const T_ELE& ele);
		void PreOrderTraverse();
		void InOrderTraverse();
		void PostOrderTraverse();
		void LevelTraverser();
		BNode<T_ELE>* GetNodeByLevelOrder(DWORD index);
		
		DWORD Hight();
	private:
		void Init();
	private:
		BNode<T_ELE>* pRoot;
		DWORD count;
		 

};




// member Fun Define
template<class T_ELE>
BTree<T_ELE>::BTree()
{
	if(this->pRoot=new BNode<T_ELE>())
	{
		memset(pRoot,0,sizeof(BNode<T_ELE>));
		pRoot->left = NULL;
		count=0;
	}
}

template<class T_ELE>
BTree<T_ELE>::~BTree()
{

}

template<class T_ELE>
DWORD BTree<T_ELE>::AppendNodeByLevel(IN const T_ELE& ele)
{
	BNode<T_ELE>* pNew=new BNode<T_ELE>(ele);
	BNode<T_ELE>* pNode=this->pRoot;
	DWORD i=this->count+1;
	if(count==0)
	{
		count++;
		pRoot=pNew;
		return OK;
	}

	
	
	if(i%2)
	{
		i/=2;
		pNode=this->GetNodeByLevelOrder(i);
		pNode->right=pNew;
	}
	else
	{
		i/=2;
		pNode=this->GetNodeByLevelOrder(i);
		pNode->left=pNew;
	}
	this->count++;
	
	
	return OK;

}

template<class T_ELE>
void BTree<T_ELE>::PreOrderTraverse()
{
	Stack<T_ELE>* pStack=new Stack<T_ELE>(10);
	BNode<T_ELE>* pNode=this->pRoot;
	
	while( !pStack->Empty() || pNode )
	{
		if(pNode)
		{
			pNode->Visit();
			pStack->Push(pNode);
			pNode=pNode->left;   // A B D E C
		}
		else
		{
			pStack->Pop(&pNode);
			pNode=pNode->right;
		}
	}
	delete pStack;
	printf("asda");
}

template<class T_ELE>
void BTree<T_ELE>::InOrderTraverse()
{
	Stack<T_ELE>* pStack=new Stack<T_ELE>(10);
	BNode<T_ELE>* pNode=this->pRoot;
	while(!pStack->Empty() || pNode )
	{
		if(pNode)
		{
			pStack->Push(pNode);
			pNode=pNode->left;
		}
		else
		{
			pStack->Pop(&pNode);
			pNode->Visit();
			pNode=pNode->right;
		}

	}
	delete pStack;
	printf("asda");
}

template<class T_ELE>
void BTree<T_ELE>::PostOrderTraverse()
{
	Stack<T_ELE>* pStack=new Stack<T_ELE>(10);
	Stack<T_ELE>* pStack_temp=new Stack<T_ELE>(10);
	BNode<T_ELE>* pNode=this->pRoot;
	while( pNode || !pStack->Empty() )
	{
		if(pNode)
		{
			pStack->Push(pNode);  
			pNode=pNode->left;
		}
		else
		{
			pStack->Pop(&pNode);
			pStack_temp->Push(pNode);
			if(!pNode->right)
			{
				while(!pStack_temp->Empty())
				{
					BNode<T_ELE>* pNode_tmp;
					pStack_temp->Pop(&pNode_tmp);
					pNode_tmp->Visit();
				}
			}
				
			pNode=pNode->right;
		}
	}

	delete pStack;
	delete pStack_temp;
}

template<class T_ELE>
void BTree<T_ELE>::LevelTraverser()
{
	// use Stack as Array.
	
	BNode<T_ELE>** pQue=new BNode<T_ELE>*[10];
	int front;
	int rear;
	rear=front=0;
	BNode<T_ELE>* pNode=this->pRoot;
	pQue[0]=pNode;
	
	while(front <= rear)
	{
		pNode=pQue[front++];
		pNode->Visit();
		if(pNode->left)
			pQue[++rear]=pNode->left;
		if(pNode->right)
			pQue[++rear]=pNode->right;
			
	}
	delete[] pQue;

}

template <class T_ELE>
BNode<T_ELE>* BTree<T_ELE>::GetNodeByLevelOrder(DWORD index)
{
	Stack<T_ELE>* pStack=new Stack<T_ELE>(10);
	BNode<T_ELE>* pNode=this->pRoot;
	DWORD i=0;
	if(index == 0)
		return pNode;
	pStack->Push(pNode);
	while( !pStack->Empty() )
	{
		pStack->Pop(&pNode);
		
		i++;
		if(i==index)
			return pNode;
		if(pNode->right)
			pStack->Push(pNode->right);
		if(pNode->left)
			pStack->Push(pNode->left);
	}
	delete pStack;
	return NULL;
}

//main func
int main(int argc, char* argv[])
{
	BTree<Monster>* pTree = new BTree<Monster>;
	Monster m1(1,2,"Aly");
	Monster m2(2,2,"Bly");
	Monster m3(3,2,"Cly");
	Monster m4(4,2,"Dly");
	Monster m5(5,2,"Ely");
	pTree->AppendNodeByLevel(m1);
	pTree->AppendNodeByLevel(m2);
	pTree->AppendNodeByLevel(m3);
	pTree->AppendNodeByLevel(m4);
	pTree->AppendNodeByLevel(m5);
	//pTree->LevelTraverser();
	//pTree->InOrderTraverse();
	//pTree->PreOrderTraverse();
	//pTree->PostOrderTraverse();
	delete pTree;
	
	printf("Hello World!\n");
	return 0;
}

/*
			1A
		2B		3C
	4D       5E
*/