#include <ace/utils/bitmap.h>
#include <ace/utils/chunky.h>
#include "coords.h"
#include "geometry.h"
#include "colors.h"

#define IS_FILLED(var) PLAYGROUND[var.y][var.x]==FILL_COLOR_INDEX
#define IS_ON_TRACK(var)  PLAYGROUND[var.y][var.x]==TRACK_COLOR_INDEX

enum FLOOD_TYPE { NONE,FIRST_POINT, INNER, ALL};


struct TFlood_queue
{
	int x;
	int y;
	UBYTE color;
	struct TFlood_queue* next;
};


void rect_flood(tBitMap* ,int , int , UBYTE , UBYTE );
Coordlimits* shape_flood(int , int , UBYTE , UBYTE,enum FLOOD_TYPE );
int test();


struct TFlood_queue* create_tflood_elem(int ,int ,UBYTE);
struct TFlood_queue* enqueue_tflood_elem(struct TFlood_queue* ,struct TFlood_queue*);
void forceFillAll(struct TFlood_queue,int,int,Coordlimits*,int,struct TFlood_queue**);
void forceFillPoint(point curPoint,Coordlimits* limits,int);
int inside_playarea ( point P  );
void fillTracks(struct TFlood_queue N,int XStep,int YStep,Coordlimits* limits,int replacement_color,struct TFlood_queue** trackQueue);
void fillTracksCorners(struct TFlood_queue* ,Coordlimits* ,int );
int is_vertex(point ,point ,int ,int );

