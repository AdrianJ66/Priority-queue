// pQueue.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include "global.h"
#include <iostream>

using namespace std;

int main( int argc, char* argv )
{
	
	int elements[] = { 37, 41, 26, 14, 19, 99, 23, 17, 12, 20, 25, 42 };
	int no = sizeof( elements ) / sizeof( int );

	PQueue* NewQ = PQInit( no );


	for ( int i = 1; i <= no; i++ )
	{
		PQEnqueue( NewQ, i, elements[i-1] );
	}

	printf( "Liczba elementow: %d \n", no );
	PQPrint( NewQ );

	PQDequeue( NewQ );
	printf( "\n\nTabela po usunieciu elementu: \n" );
	PQPrint( NewQ );

	PQDequeue( NewQ );
	printf( "\n\nTabela po usunieciu elementu: \n" );
	PQPrint( NewQ );

	PQDequeue( NewQ );
	printf( "\n\nTabela po usunieciu elementu: \n" );
	PQPrint( NewQ );

	IncreaseKey( NewQ, 3, 125 );
	printf( "\n\nTabela po zwiekszeniu priorytetu elementu: \n" );
	PQPrint( NewQ );

	DecreaseKey( NewQ, 6, 4 );
	printf( "\n\nTabela po zmniejszeniu priorytetu elementu: \n" );
	PQPrint( NewQ );


	PQRelease( NewQ );
	return 0;
}


