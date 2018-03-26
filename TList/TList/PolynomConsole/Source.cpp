#include "C:\Users\sirku\Desktop\TList-master\include\TList.h"

int main()
{
	TPolynom poly1, poly2;
	TMonom monom;

	monom.coeff = 2;
	monom.x = 2;
	monom.y = 2;
	monom.z = 2;

	poly1.insFirst(monom);
	poly2.insFirst(monom);
	
	poly1 *= 10;

	poly1.reset();
	cout << poly1.getElem().coeff << endl;
	cout << poly1.getElem().x << endl;
	cout << poly1.getElem().y << endl;
	cout << poly1.getElem().z << endl;

	
}
