#pragma once
#include <iostream>
using namespace std;
template <class T>
struct TLink {
	T val;
	TLink *pNext;
};
template <class T> 
class TList{
protected:
	TLink<T> *pFirst, *pLast, *pPrev, *pCurr, *pStop;
	int size, pos;
public:
	TList(){
		pFirst=pLast=pCurr=pStop=NULL;
		size=0;
		pos=-1;
	}
	void sortInput(T a){
		if (pFirst==pStop || a<pFirst->val ) 
		{ 
			addFirst(a); 
			pCurr=pPrev=pFirst; 
			return ;
		}
		if (a>=pLast->val)
		{ addLast(a); 
		for(reset();!(pCurr->pNext==pStop);goNext())
		{} 
		return ;
		}
		for(reset();!isEnd();goNext()){
			if (pCurr->val>a) {addCurr(a); return; }
		}

	}
	void insSort(){
		
		T tmp;
		for (int i=0;i<size-1;i++){
			reset();
			for(int j=0;j<size-1-i;j++){
				goNext();
				if (pPrev->val>pCurr->val){
					tmp=pCurr->val;
					pCurr->val=pPrev->val;
					pPrev->val=tmp;
				}
			}
		}
	}

	void insFirst (T a){
		TLink<T> *tmp=new TLink <T>;
		tmp->val=a;
		if (size==0)
		{
			pFirst=pLast=pCurr=tmp;
			tmp->pNext=pStop;
		}
		else
		{
			tmp->pNext=pFirst;
			pFirst=tmp;
            if(size==1) pPrev=pFirst;
		}
		
		pos++;
		size++;
	}
	void insCurr (T a){
		if (pFirst==pCurr) insFirst(a);
		else 
		{

			TLink<T> *tmp=new TLink<T>;
			tmp->val=a;
			tmp->pNext=pCurr;
			pPrev->pNext=tmp;
			pCurr=tmp;
			size++;
		}
		
	}
	void insLast (T a){
		if (pFirst==pStop) insFirst(a);
		else{
             TLink<T> *tmp=new TLink<T>;
			 tmp->val=a;
			 pLast->pNext=tmp;
			 tmp->pNext=pStop;
             pLast=tmp;
			 size++;						
		}
		
	}
	T getElem(){ return pCurr->val; }
	void delFirst (){
		if (size==1)
		{
			delete pFirst;
			pFirst=pLast=pPrev=pCurr=pStop;
		}
		else
		{
			TLink<T> *tmp=pFirst->pNext;
			delete pFirst;
			pFirst=tmp;
		}
		size--;
		pos--;
	}
	void delCurr (){
		if (pCurr==pFirst)
		
			delFirst();
		
		else 
		{
			pCurr=pCurr->pNext;
			delete pPrev->pNext;
			pPrev->pNext=pCurr;
			size--;

		}
	}
	void delLast (){
	  if (pLast==pFirst) delFirst();
	  else{
		  for(reset();!(pCurr->pNext==pStop);goNext()){}
		  delete pLast;
		  pLast=pCurr=pPrev;
	      reset();
		  size--;
		  pos--;
	  }
	}
	void reset(){
		pPrev=pCurr=pFirst;
		pos=0;
	}
	void goNext (){
		pPrev=pCurr;
		pCurr=pCurr->pNext;
		pos++;
	}
	bool isEnd (){
		return pCurr==pStop;
	}

	bool isEmpty(){
		return pFirst==pStop;
	}
	T operator[](int m){
		for(reset();!isEnd();goNext()){
			if (pos==m-1)
			return pCurr->val;
		}
	}	
};


template <class T>
class THeadList :public TList<T>
{
protected:
	TLink<T>*pHead;
public:
	THeadList() : TList()
	{
		pHead = new TLink<T>;
		pStop = pHead;
		pHead->pNext = pHead;
	}
	
	~THeadList()
	{
		TList::~TList();
		delete pHead;
	}

	void insFirst(const T elem)
	{
		TList::insFirst(elem);
		pHead->pNext = pFirst;
	}

	void delFirst()
	{
		TList::delFirst();
		pHead->pNext = pFirst;
	}
};

struct TMonom
{
	double coeff;
	int x, y, z;
};

bool operator <(const TMonom&T1, const TMonom&T2)
{
	if (T1.x < T2.x) return true;
	if (T1.x == T2.x)
	{
		if (T1.y < T2.y) return true;
		if (T1.y == T2.y)
		{
			if (T1.z < T2.z) return true;
			else return false;
		}
		else return false;
	}
	else
		return false;
}

bool operator >(const TMonom&T1, const TMonom&T2)
{
	if (T1.x > T2.x) return true;
	if (T1.x == T2.x)
	{
		if (T1.y > T2.y) return true;
		if (T1.y == T2.y)
		{
			if (T1.z > T2.z) return true;
			else return false;
		}
		else return false;
	}
	else
		return false;
}

bool operator ==(const TMonom&T1, const TMonom&T2)
{
	if ((T1.x == T2.x) && (T1.y == T2.y) && (T1.z == T2.z)) return true;
	else return false;
}



class TPolynom: public THeadList<TMonom>
{
public:
	TPolynom():THeadList<TMonom>()
	{
		pHead->val.coeff = 0;
		pHead->val.x = 0;
		pHead->val.y = 0;
		pHead->val.z = 0;
	}
	
	TPolynom(TMonom*TM, int size) :THeadList<TMonom>()
	{
		pHead->val.coeff = 0;
		pHead->val.z = 0;

		for (int i = 0; i < size; i++) insLast(TM[i]);
	}

	void insOrder(const TMonom&TM)
	{
		for (reset();!isEnd();goNext())
		{
			if (TM == pCurr->val)
			{
				pCurr->val.coeff += TM.coeff;
				if (pCurr->val.coeff == 0) delCurr();
				return;
			}
			if (TM > pCurr->val)
			{
				insCurr(TM);
				return;
			}
		}
		insLast(TM);
	}

	void operator *= (int c)
	{
		for (reset();!isEnd();goNext()) pCurr->val.coeff *= c;
	}

	void operator += (TPolynom TM)
	{
		TM.reset();
		reset();

		while(!isEnd()||!TM.isEnd())
		{
			if (pCurr->val == TM.pCurr->val)
			{
				pCurr->val.coeff += TM.pCurr->val.coeff;
				if (pCurr->val.coeff == 0)
				{
					delCurr();
					TM.goNext();
				}
				else 
				{
					goNext();
					TM.goNext();
				}
			}
			else
				if (pCurr->val < TM.pCurr->val)
				{
					insCurr(TM.pCurr->val);
					TM.goNext();
				}
				else
					goNext();
		}
	}

	bool isLast() 
	{
		return pCurr->pNext == pStop;
	}

};