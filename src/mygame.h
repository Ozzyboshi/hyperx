#ifndef _GAME_H_
#define _GAME_H_
#include "geometry.h"
// Function headers from game.c go here
// It's best to put here only those functions which are needed in other files.


#define PLOT_POINT(varCol, varX, varY) chunkyToPlanar(varCol, varX, varY, s_pMainBuffer->pFront);\
		chunkyToPlanar(varCol, varX, varY, s_pMainBufferRealPlay->pFront);\
        PLAYGROUND[varY-YPADDING][varX]=varCol;

void gameGsCreate(void);

void gameGsLoop(void);

void gameGsDestroy(void);

int positionAllowed(int ,int ,int,int);

//void flood(int, int, UBYTE, UBYTE); 
void refreshscreen(int,int);
int getFloodCoords(point*,int ,int ,int* ,int*, point*);
//void trackEvaluate(struct TFlood_queue* );



#endif // _GAME_H_