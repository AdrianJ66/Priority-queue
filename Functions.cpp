#include "global.h"
#include <iostream>

using namespace std;

void   UpdateDown( PQueue* PriorQueue, int l, int p );
void   UpdateUp( PQueue* PriorQueue, int l, int p );

void PQClear( PQueue* PriorQueue );


//------------------------------------------------------------------------------

PQueue* PQInit( int qSize )
{
	PQueue* PriorQueue = ( PQueue* )malloc( sizeof( PQueue ) );
	PriorQueue->pQueueHeap = ( pQueueItem** )calloc( qSize, sizeof( pQueueItem* ) );
	if ( !( PriorQueue->pQueueHeap ) )
	{
		printf( "Heap initialisation FAILED! \n" );
		return NULL;
	}
	else
	{
		PriorQueue->PQCurrentSize = 0;
		PriorQueue->PQSize = qSize;
		return PriorQueue;
	}
}

//------------------------------------------------------------------------------

int PQIsEmpty( PQueue* PriorQueue )
{
	return !( PriorQueue->PQCurrentSize );
}

//------------------------------------------------------------------------------

void PQEnqueue( PQueue* PriorQueue, int pInfo, int nPrior )
{
	if ( PriorQueue->PQCurrentSize == PriorQueue->PQSize )
	{
		printf( "Priority queue is FULL! \n" );
	}
	else
	{
		pQueueItem* item = ( pQueueItem* )malloc( sizeof( pQueueItem ) );
		if ( !item )
		{
			printf( "Element creation FAILED! \n" );
		}
		else
		{
			item->nKey = pInfo;
			item->nPrior = nPrior;

			int i = PriorQueue->PQCurrentSize++;
			PriorQueue->pQueueHeap[i] = item;
			
			UpdateUp( PriorQueue, 0, i );
		}
	}
}

//------------------------------------------------------------------------------

int PQDequeue( PQueue* PriorQueue )
{
	if ( PQIsEmpty( PriorQueue ) )
	{
		printf( "Priority queue is EMPTY! \n" );
		return NULL;
	}
	else
	{
		int value = PriorQueue->pQueueHeap[0]->nKey;
		PriorQueue->pQueueHeap[0] = PriorQueue->pQueueHeap[PriorQueue->PQCurrentSize-1];
		PriorQueue->pQueueHeap[PriorQueue->PQCurrentSize-1] = NULL;
		PriorQueue->PQCurrentSize--;

		//UpdateDown( PriorQueue, 1, PriorQueue->PQCurrentSize );
		UpdateDown( PriorQueue, 0, PriorQueue->PQCurrentSize-1 );

		
		return value;
	}
}

//------------------------------------------------------------------------------

void PQClear( PQueue* PriorQueue )
{
	while ( !PQIsEmpty(PriorQueue ))
	{
		PQDequeue( PriorQueue );
	}

	printf( "\n\n\nPriority queue has been CLEARED! \n" );

}

//------------------------------------------------------------------------------

void PQRelease( PQueue* PriorQueue )
{
	PQClear( PriorQueue );
	free( PriorQueue );
}

//------------------------------------------------------------------------------

void PQPrint( PQueue* PriorQueue ) // inOrder albo normalnie
{
	printf( "Priority queue contains the following elements : \n" );
	for ( int i = 0; i < PriorQueue->PQCurrentSize; i++  )
	{
		printf( "%d ", PriorQueue->pQueueHeap[i]->nPrior );
	}
}

//------------------------------------------------------------------------------

//void   UpdateDown( PQueue* PriorQueue, int l, int p )
//{
//	if ( l == p )
//		return;
//
//	int i = l;  // i oraz j wskazuja na elementy, ktore moga ulec zamianie 
//	int j = 2 * i + 1;
//	pQueueItem* tmp = PriorQueue->pQueueHeap[i];
//
//	while ( j <= p )
//	{
//		if ( ( j < p ) && ( PriorQueue->pQueueHeap[j]->nPrior < PriorQueue->pQueueHeap[j + 1]->nPrior ) )
//			j++;
//		if ( tmp->nPrior > PriorQueue->pQueueHeap[j]->nPrior )
//			break;
//
//		PriorQueue->pQueueHeap[i] = PriorQueue->pQueueHeap[j];
//		i = j;
//		j = 2 * i + 1;
//	}
//	PriorQueue->pQueueHeap[i] = tmp;
//}

//void UpdateDown( PQueue* PriorQueue, int l, int p )
//{
//	if ( l == p )
//		return;
//
//	int i = l;  
//	int j = 2 * i;  //lewy potomek
//	pQueueItem* tmp = PriorQueue->pQueueHeap[i];
//
//	while ( true )
//	{
//		if ( j > p ) break;
//		if ( ( j + 1 ) <= p && PriorQueue->pQueueHeap[j]->nPrior >= PriorQueue->pQueueHeap[j + 1]->nPrior )  //prawy potomek nie musi istniec
//		{
//			j++;
//		}
//		if ( PriorQueue->pQueueHeap[i]->nPrior > PriorQueue->pQueueHeap[j]->nPrior ) break; //jezeli ma wiekszy priorytet od wiekszego potomka to																					//konczymy petle
//
//			PriorQueue->pQueueHeap[i] = PriorQueue->pQueueHeap[j];
//			i = j;
//			j = 2 * i;
//	}
//	PriorQueue->pQueueHeap[i] = tmp;
//}

void UpdateDown( PQueue* PriorQueue, int l, int p )
{
	if ( l == p ) return;
	int i = l;
	int j = 2 * i + 1;
	pQueueItem* tmp = PriorQueue->pQueueHeap[i];

	while ( j <= p )
	{
		if ( j < p )
		{
			if ( PriorQueue->pQueueHeap[j]->nPrior < PriorQueue->pQueueHeap[j + 1]->nPrior )
			{
				j++;
			}
		}

			if ( PriorQueue->pQueueHeap[i]->nPrior < tmp->nPrior ) break;

			PriorQueue->pQueueHeap[i] = PriorQueue->pQueueHeap[j];
			i = j;
			j = 2 * i + 1;
		
	}
	PriorQueue->pQueueHeap[i] = tmp;
}

//------------------------------------------------------------------------------

void UpdateUp( PQueue* PriorQueue, int l, int p )
{
	if ( l == p ) return;
	int j = p;
	int i =  j / 2;
	pQueueItem* tmp = PriorQueue->pQueueHeap[j];

	while ( ( j > l ) && ( PriorQueue->pQueueHeap[i]->nPrior < tmp->nPrior ) )
	{

		PriorQueue->pQueueHeap[j] = PriorQueue->pQueueHeap[i];
		j = i;
		i = j / 2;
	}

	PriorQueue->pQueueHeap[j] = tmp;
}

//------------------------------------------------------------------------------

void DecreaseKey( PQueue* PriorQueue, int x, int nPrior ) // (nPrior < Item.nPrior) // zmiejsza priorytet x-tego elementu do nPrior
{
	if ( PriorQueue->pQueueHeap[x]->nPrior > nPrior )
	{
		PriorQueue->pQueueHeap[x]->nPrior = nPrior;
		UpdateDown( PriorQueue, x, PriorQueue->PQCurrentSize );
	}
	else
	{
		printf( "ERROR: Given element has equal or lower priority than desired nPrior! \n" );
	}
}

//------------------------------------------------------------------------------

void IncreaseKey( PQueue* PriorQueue, int x, int nPrior ) // (nPrior > Item.nPrior) // zwieksza priorytet x-tego elementu do nPrior
{
	if ( PriorQueue->pQueueHeap[x]->nPrior < nPrior )
	{
		PriorQueue->pQueueHeap[x]->nPrior = nPrior;
		UpdateUp( PriorQueue, 0, x );
	}
	else
	{
		printf( "ERROR: Given element has equal or higher priority than desired nPrior! \n" );
	}
}

//------------------------------------------------------------------------------
