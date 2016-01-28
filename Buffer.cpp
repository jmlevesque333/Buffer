//Jean-Michel Levesque A00172309
//compile sur visual studio

#include <iostream>
#include <time.h>

using namespace std;

int random()
{
	return rand();
}

int* getPointer(int tab[],int num)
	{
		int* temp;
		temp = &tab[num];
		return temp;
	}

class buffer
{
public:
	int info;
	bool dirtyFlag;
	bool lockFlag;
	short accessCount;
	int* ptr;

	buffer()
	{
		dirtyFlag = false;
		lockFlag = false;
		info = -1;
		accessCount = 0;
		ptr = NULL;
	}

	bool releaseBuffer()
	{
		if (lockFlag == 0)
			return false;
		else
			lockFlag = 0;
		return true;
	}

	void readBlock()
	{
		cout << "info: " << info << endl;
		cout << "dirtyFlag: " << dirtyFlag << endl;
		cout << "lockFlag: " << lockFlag << endl;
		cout << "accessCount: " << accessCount << endl;
		accessCount++;
		cout << endl;
		return;
	}

};

void aquireBuffer(int tableau[], buffer tab[], int num, int rand =-1)
{
	int value = tableau[num];
	if (rand != -1)
		value = random();
	int temp;
	for (int i = 0; i < 4; i++)
	{
		if (tab[i].accessCount <= tab[i + 1].accessCount)
			if (tab[i].lockFlag == 0)
				temp = i;
	}
	if (tab[temp + 1].accessCount <= tab[temp].accessCount)
		temp++;
	if(tab[temp].info != -1)
		tab[temp].dirtyFlag = 1;
	tab[temp].info = value;
	tab[temp].accessCount++;
	tab[temp].ptr = getPointer(tableau, num);
	tab[temp].lockFlag = 1;
}

void releaseBuffer(int tableau[], buffer tab[], int num)
{
	int i = 0;
	while(tab[i].ptr != &tableau[num] && i < 5)
	{
		i++;
	}
	if (tab[i].ptr != &tableau[num])
	{
		cout << "value not found";
		return;
	}
	if (tab[i].dirtyFlag != 1)
	{
		cout << "not dirty";
	}
	else
	{
		tableau[num] = tab[i].info;
		tab[i].lockFlag = 0;
	}
	
}

int findBlock(int tableau[], buffer tab[], int* num)
{
	int i = 0;
	while (tab[i].ptr != num && i < 5)
	{
		i++;
	}
	if(tab[i].ptr == num)
		return i;
	else return -1;
}

void readFile(int tab[], int max)
{
	for (int i = 0; i < max; i++)
	{
		cout << "fichier simule:";
		cout << "tab[" << i << "]: " << tab[i] << endl;
	}
	cout << "---------------------------------------------" << endl;

}


int main()
{
	srand(time(NULL));
	int tab[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	buffer bassin[5];
	int input = 0;
	int input2 = 0;

	cout << "Levesque Jean-Michel A00172309" << endl << endl;
	
	while (input != 100)
	{
		readFile(tab, 15);
		for (int i = 0; i < 5; i++)
			bassin[i].readBlock();
		cout << "-------------------------------" << endl;
		cout << "choissez un numero de 0 a 14; 100 pour sortir"<<endl;
		cin >> input;
		cout << endl << endl;
		cout << "Quelle operation voulez vous effectuer?" << endl;
		cout << "1) aquireBuffer" << endl;
		cout << "2) releaseBuffer" << endl;
		cout << "3) readBlock" << endl;
		cout << "4) getPointer" << endl;
		cout << "5) ecrire une valeur aleatoire dans un tampon" << endl;
		cin >> input2;
		cout << endl << endl;
		switch (input2)
			{
			case 1:
			{
				aquireBuffer(tab, bassin, input);
				break;
			}
			case 2:
			{
				releaseBuffer(tab, bassin, input);
				break;
			}
			case 3:
			{
				bassin[findBlock(tab, bassin, getPointer(tab, input))].readBlock();
				break;
			}
			case 4:
			{
				
				break;
			}
			case 5:
			{
				bassin[findBlock(tab, bassin, getPointer(tab, input))].info = random();
				bassin[findBlock(tab, bassin, getPointer(tab, input))].dirtyFlag = 1;
				break;
			}
			default:
			{
				cout << "vous n'avez pas choisit une des options existantes" << endl;
				break;
			}
		}
	}

	

	return 0;
}
