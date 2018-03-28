#pragma once
#include "THeadList.h"
#include "cstdlib"
#include "time.h"
#include  <string>
struct TMonom{
	double coeff;
	int x,y,z;

	bool operator<(const TMonom &q){
    return ((x*100+y*10+z)<(q.x*100+q.y*10+q.z));
	}

	bool operator>(const TMonom &q){
    return ((x*100+y*10+z)>(q.x*100+q.y*10+q.z));
	}

	bool operator!=(const TMonom &q){
    if ((x*100+y*10+z)==(q.x*100+q.y*10+q.z))
		return (coeff!=q.coeff);
	else return true;
	}

	bool EqualDegrees(const TMonom &q){
	return ((x*100+y*10+z)==(q.x*100+q.y*10+q.z));
	}

	bool operator==(const TMonom &q){
    if ((x*100+y*10+z)==(q.x*100+q.y*10+q.z))
		return (coeff==q.coeff);
	else return false;
	}

	TMonom operator*(const TMonom &q){
		TMonom tmp;
		tmp.x=q.x+x;
		tmp.y=q.y+y;
		tmp.z=q.z+z;
		tmp.coeff=q.coeff*coeff;
		return tmp;
	}

	TMonom& operator=(const TMonom &q){
		coeff=q.coeff;
		x=q.x;
		y=q.y;
		z=q.z;
		return *this;
	}
};

ostream& operator<<(ostream& os, const TMonom& m){
	if (!m.coeff) {os<<"0"; return os;}
	os<<m.coeff;
	if (m.x) if (m.x>1) os<<"x^"<<m.x;
	         else  os<<"x";
	if (m.y) if (m.y>1) os<<"y^"<<m.y;
	         else  os<<"y";
	if (m.z) if (m.z>1) os<<"z^"<<m.z;
	         else  os<<"z";
	return os;
	}

class TPolynom: public THeadList<TMonom>{
public:
	
	TPolynom():THeadList(){
		pHead->val.coeff=0;
		pHead->val.x=-1;
	}
	
	TPolynom(TPolynom &p):THeadList()
	{
		pHead->val.coeff=0;
		pHead->val.x=-1;
		
		if (p.size)
		{
			TLink<TMonom> *tmp1=new TLink<TMonom>;
			pHead->pNext=tmp1;
			pFirst=pCurr=tmp1;
		
			for(p.reset();!p.isEnd();p.goNext())
			{
				TLink<TMonom> *tmp2=new TLink<TMonom>;
				pCurr->val=p.pCurr->val;
				if (p.pos==p.size-1) {pLast=pCurr; pLast->pNext=pStop; size=p.size; break;}
				pCurr->pNext=tmp2;
				goNext();
		    
			}
		}

	}
	
	TPolynom(const TMonom &m):THeadList()
	{
        TLink<TMonom> *tmp=new TLink<TMonom>;
		
		tmp->pNext=pStop;
		tmp->val=m;	
		pHead->pNext=tmp;
		pFirst=pLast=pCurr=tmp;
	}

	void sortInput(TMonom a)
	{
		if (!size) { addFirst(a); return;}
		for(reset();!isEnd();goNext()){
			if (pCurr->val.EqualDegrees(a)){
				pCurr->val.coeff+=a.coeff;
				if (!pCurr->val.coeff) delCurr();
				return;
			}
			else  if(pCurr->val<a){
				addCurr(a);
				return;
			}
		}
		addLast(a);
	}
	
	TPolynom(TMonom *mas,int size):THeadList()
	{
		pHead->val.coeff=0;
		pHead->val.x=-1;
		
		for(int i=0;i<size;i++)
		  	sortInput(mas[i]);
	}
	
	TPolynom operator+(TPolynom &p)
	{
		TPolynom tmp(*this);
		p.reset();
		
		for(reset();!isEnd();goNext())
		{
			for(p.pCurr;(p.pCurr->val>pCurr->val && !p.isEnd());p.goNext())
			{
				tmp.sortInput(p.pCurr->val);
			}
		}

		if (isEnd() && !p.isEnd()) 
			for(p.pCurr;!p.isEnd();p.goNext())
				tmp.sortInput(p.pCurr->val);
		
		return tmp;
	}

	void operator += (TPolynom TM)
	{
		TM.reset();
		reset();

		while (!isEnd() || !TM.isEnd())
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
					addCurr(TM.pCurr->val);
					TM.goNext();
				}
				else
					goNext();
		}
	}
	
	TPolynom operator-(TPolynom &p)
	{
		TPolynom tmp(*this),tmp2(p);
		tmp2*=-1;
		tmp2.reset();
		
		for(reset();!isEnd();goNext())
		{
			for(tmp2.pCurr;(tmp2.pCurr->val>pCurr->val && !tmp2.isEnd());tmp2.goNext())
			{
				tmp.sortInput(tmp2.pCurr->val);
			}
		}

		if (isEnd() && !tmp2.isEnd()) 
			for(tmp2.pCurr;!tmp2.isEnd();tmp2.goNext())
				tmp.sortInput(tmp2.pCurr->val);
		
		return tmp;
	}
	
	void operator -= (TPolynom TM)
	{
		TM.reset();
		reset();

		while (!isEnd() || !TM.isEnd())
		{
			if (pCurr->val == TM.pCurr->val)
			{
				pCurr->val.coeff -= TM.pCurr->val.coeff;
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
					addCurr(TM.pCurr->val);
					TM.goNext();
				}
				else
					goNext();
		}
	}

	TPolynom& operator=(TPolynom &p)
	{
		pHead->val.coeff=0;
		pHead->val.x=-1;
		
		if (p.size)
		{
        TLink<TMonom> *tmp1=new TLink<TMonom>;
		pHead->pNext=tmp1;
		pFirst=pCurr=tmp1;
		
		for(p.reset();!p.isEnd();p.goNext())
		{
			TLink<TMonom> *tmp2=new TLink<TMonom>;
			
			pCurr->val=p.pCurr->val;
			
			if (p.pos==p.size-1) 
			{
				pLast=pCurr; 
				pLast->pNext=pStop; 
				size=p.size; 
				break;
			}
			
			pCurr->pNext=tmp2;
			goNext();   
		}
		return *this;
	}
	}
	
	TPolynom operator*(TPolynom &p)
	{
		TPolynom tmp;
		
		for(p.reset();!p.isEnd();p.goNext())
			for(reset();!isEnd();goNext()){
				tmp.sortInput(pCurr->val*p.pCurr->val);	
			}
		
		return tmp;		
	}
	
	void operator*=(double a)
	{
       for(reset();!isEnd();goNext())
		   pCurr->val.coeff*=a;	   
	}

	TPolynom operator*(double a)
	{
		TPolynom tmp(*this);
		for(reset();!isEnd();goNext())
			tmp.pCurr->val.coeff*=a;	
		return tmp;		 
	}
	
	double getCoeff()
	{
		return pCurr->val.coeff;
	}
	
	int getX()
	{
		return pCurr->val.x;
	}
	
	int getY()
	{
		return pCurr->val.y;
	}
	
	int getZ()
	{
		return pCurr->val.z;
	}

	bool isLast()
	{
		return pCurr->pNext == pStop;
	}

	void magic()
	{
		TLink<TMonom> *tmp;
	
		reset();

		if ((pCurr->pNext != pStop)) {
			tmp = pCurr->pNext;
			while (tmp->pNext != NULL)
			{
				if (pCurr->val.EqualDegrees(tmp->val)) {
					tmp->val.coeff += pCurr->val.coeff;
					delCurr();
					break;
				}
				tmp = tmp->pNext;
			}
		}			
	}

	friend ostream& operator<<(ostream& os, TPolynom &p)
	{
		if (p.size==0) 
		{
			os<<"0"; 
			return os;
		}

	  for(p.reset();!p.isEnd();p.goNext())
	  {
		if (!p.pos) os<<p.pCurr->val;
		else 
			if(p.pCurr->val.coeff>0) os<<"+ "<<p.pCurr->val;
		    else os<<p.pCurr->val;
	  }
      return os;
	} 
};
