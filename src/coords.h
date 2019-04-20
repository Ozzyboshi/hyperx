#ifndef _COORDS_H_
#define _COORDS_H_
// SCREEN RESOLUTION
#define XSCREEN_RES 320
#define YSCREEN_RES 256

// Playground size
#define PLAYGROUND_WIDTH 180
#define PLAYGROUND_HEIGHT 210

// Playground coordinates macro
#define PLAYGROUND_X1(var) ((int)var->uwWidth/2)-(PLAYGROUND_WIDTH/2);
#define PLAYGROUND_X2(var) ((int)var->uwWidth/2)+(PLAYGROUND_WIDTH/2);
#define PLAYGROUND_Y1(var) ((int)var->uwHeight/2)+(PLAYGROUND_HEIGHT/2);
#define PLAYGROUND_Y2(var) ((int)var->uwHeight/2)-(PLAYGROUND_HEIGHT/2);

typedef struct Coordlimits
{
	int minY;
	int maxY;
	int yMaxFlodded;
}Coordlimits;

#endif 
