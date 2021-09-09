#include <iostream>
#include "Avl.h"
#include "Avl.cpp"

int main()
{
	Avl<int> at;

	at.Insert(1);
	at.Insert(2);
	at.Insert(3);
	at.Insert(4);
	at.Insert(5);
	at.Insert(6);
	at.Insert(7);

	at.Remove_val(4);

	return 0;
}