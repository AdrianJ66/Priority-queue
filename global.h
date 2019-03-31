#pragma once

typedef struct 
{
	int nKey;
	int nPrior;
} pQueueItem;


typedef struct
{
	pQueueItem** pQueueHeap;
	int PQCurrentSize;
	int PQSize;
}PQueue;

PQueue* PQInit( int qSize );
void PQRelease( PQueue* PriorQueue );
void PQClear( PQueue* PriorQueue );
int PQIsEmpty( PQueue* PriorQueue );
void PQEnqueue( PQueue* PriorQueue, int nKey, int nPrior );
int PQDequeue( PQueue* PriorQueue );
void PQPrint( PQueue* PriorQueue ); 
void UpdateDown( PQueue* PriorQueue, int l, int p );
void UpdateUp( PQueue* PriorQueue, int l, int p );

void DecreaseKey( PQueue* PriorQueue, int x, int nPrior ); // (nPrior < Item.nPrior) // zmiejsza priorytet elementu
void IncreaseKey( PQueue* PriorQueue, int x, int nPrior ); // (nPrior > Item.nPrior) // zwieksza priorytet elementu