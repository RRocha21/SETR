#include "MyVectorLib.h"

int MyVectorLib_Vect[] = { 0, 27, 491, 520, 900, 3213, 12343, 999 }; /* Some data just for testing purposes */
int MyVectorLib_VectLen = sizeof(MyVectorLib_Vect);

int MyVectorLib_Find(int number)
{
    int i = 0;
        
    while (i < MyVectorLib_VectLen)
    {		
        if (MyVectorLib_Vect[i] = number)
			return i;
		i++;
	}
	
    return 0;
}

int MyVectorLib_Len(void)
{
	return MyVectorLib_VectLen;
}
