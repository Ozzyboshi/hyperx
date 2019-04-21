
#include "flood.h"
#include "colors.h"
#include <stdlib.h>

extern UBYTE PLAYGROUND [PLAYGROUND_HEIGHT][XSCREEN_RES];
extern unsigned int SCORE;
extern int X1;
extern int X2;
extern int Y1;
extern int Y2;

/**Flood-fill (node, target-color, replacement-color):
  1. If target-color is equal to replacement-color, return.
  2. If color of node is not equal to target-color, return.
  3. Set the color of node to replacement-color.
  4. Set Q to the empty queue.
  5. Add node to the end of Q.
  6. While Q is not empty:
  7.     Set n equal to the first element of Q.
  8.     Remove first element from Q.
  9.     If the color of the node to the west of n is target-color,
             set the color of that node to replacement-color and add that node to the end of Q.
 10.     If the color of the node to the east of n is target-color,
             set the color of that node to replacement-color and add that node to the end of Q.
 11.     If the color of the node to the north of n is target-color,
             set the color of that node to replacement-color and add that node to the end of Q.
 12.     If the color of the node to the south of n is target-color,
             set the color of that node to replacement-color and add that node to the end of Q.
 13. Continue looping until Q is exhausted.
 14. Return.
 */

int test()
{
  if (PLAYGROUND[0][0]==1) return 1;
  return 0;
  
}

// Non recorsive Flood region
Coordlimits* shape_flood(int x, int y, UBYTE replacement_color, UBYTE target_color,enum FLOOD_TYPE floodtype)
{
  Coordlimits* limits=NULL;
  struct TFlood_queue* Q=NULL,*newelem=NULL,*TMP=NULL;

  // track variables
  struct TFlood_queue* trackFlood=NULL;

  if (floodtype==NONE) return NULL;

  limits=malloc(sizeof(Coordlimits));

  //UBYTE color_node=chunkyFromPlanar(bitmap, x,y);
  UBYTE color_node=PLAYGROUND[y][x];

  //1. If target-color is equal to replacement-color, return.
  if (target_color==replacement_color) return NULL; 

   //2. If color of node is not equal to target-color, return.
  if (color_node!=target_color) return NULL;

  PLAYGROUND[y][x]=replacement_color;
  SCORE++;
  limits->minY=limits->maxY=y;
  limits->yMaxFlodded=0;

  if (floodtype==FIRST_POINT) return limits;

  //4. Set Q to the empty queue.
  Q=NULL;

  //5. Add node to the end of Q.
  newelem=create_tflood_elem(x,y,color_node);
  Q=newelem;

  //6. While Q is not empty:
  while (Q) 
  {
    // 7.     Set n equal to the first element of Q.
    TMP = Q;
    struct TFlood_queue N;
    N.x=Q->x;
    N.y=Q->y;
    N.color=Q->color;

    // 8.     Remove first element from Q.
    Q=Q->next;
    free(TMP);

    //9.     If the color of the node to the east (RIGHT) of n is target-color,
    //         set the color of that node to replacement-color and add that node to the end of Q.
    //color_node=chunkyFromPlanar(bitmap, N.x+1,N.y);
    color_node=PLAYGROUND[N.y][N.x+1];
    if (color_node==target_color)
    {
      //chunkyToPlanar(replacement_color, N.x+1, N.y, bitmap);
      PLAYGROUND[N.y][N.x+1]=replacement_color;
      SCORE++;
      if (N.y<limits->minY) limits->minY=N.y;
      if (N.y>limits->maxY) limits->maxY=N.y;
      Q=enqueue_tflood_elem(Q,create_tflood_elem(N.x+1,N.y,color_node));
    }
    else if (color_node==TRACK_COLOR_INDEX||color_node==CURSOR_COLOR_INDEX) fillTracks(N,+1,0,limits,replacement_color,&trackFlood);

    //10.     If the color of the node to the north (UP) of n is target-color,
    //         set the color of that node to replacement-color and add that node to the end of Q.

    color_node=PLAYGROUND[N.y-1][N.x];
    if (color_node==target_color)
    {
      PLAYGROUND[N.y-1][N.x]=replacement_color;
      SCORE++;
      if (N.y-1<limits->minY) limits->minY=N.y-1;
      if (N.y-1>limits->maxY) limits->maxY=N.y-1;
      Q=enqueue_tflood_elem(Q,create_tflood_elem(N.x,N.y-1,color_node));
    }
    else if (color_node==TRACK_COLOR_INDEX||color_node==CURSOR_COLOR_INDEX) fillTracks(N,0,-1,limits,replacement_color,&trackFlood);

    //11.     If the color of the node to the west (LEFT) of n is target-color,
    //         set the color of that node to replacement-color and add that node to the end of Q.

    color_node=PLAYGROUND[N.y][N.x-1];
    if (color_node==target_color)
    {
      PLAYGROUND[N.y][N.x-1]=replacement_color;
      SCORE++;
      if (N.y<limits->minY) limits->minY=N.y;
      if (N.y>limits->maxY) limits->maxY=N.y;
      Q=enqueue_tflood_elem(Q,create_tflood_elem(N.x-1,N.y,color_node));
    }
    else if (color_node==TRACK_COLOR_INDEX||color_node==CURSOR_COLOR_INDEX) fillTracks(N,-1,0,limits,replacement_color,&trackFlood);

    //12.     If the color of the node to the south (DOWN) of n is target-color,
    //         set the color of that node to replacement-color and add that node to the end of Q.
    //color_node=chunkyFromPlanar(bitmap, N.x,N.y+1);

    color_node=PLAYGROUND[N.y+1][N.x];
    if (color_node==target_color)
    {
      PLAYGROUND[N.y+1][N.x]=replacement_color;
      SCORE++;
      if (N.y+1<limits->minY) limits->minY=N.y+1;
      if (N.y+1>limits->maxY) limits->maxY=N.y+1;
      //if (N.y+1<PLAYGROUND_HEIGHT) 
      Q=enqueue_tflood_elem(Q,create_tflood_elem(N.x,N.y+1,color_node));
    }
    else if (color_node==TRACK_COLOR_INDEX||color_node==CURSOR_COLOR_INDEX) fillTracks(N,0,+1,limits,replacement_color,&trackFlood);
  }

  //trackEvaluate(trackFlood);
  //fillTracksCorners(trackFlood,limits,replacement_color);

  return limits;
}

void fillTracks(struct TFlood_queue N,int XStep,int YStep,Coordlimits* limits,int replacement_color,struct TFlood_queue** trackQueue)
{
  point nextPoint,curPoint;
  struct TFlood_queue* trackFlood=*trackQueue;

  //Buld first point
  buildPoint(N.x+XStep,N.y+YStep,&curPoint);

  // Build next point
  buildPoint(curPoint.x+XStep,curPoint.y+YStep,&nextPoint);
  
  // If next point is a fill color, fill the first point
  if (IS_FILLED(nextPoint) || inside_playarea(nextPoint)==0)
  {
    forceFillPoint(curPoint,limits,replacement_color);

    // Going UP , check for upleft and upright corners
    /*if (YStep==-1||YStep==1)
    {
      if (is_vertex2(curPoint,nextPoint,-1,0))
      {
        point vPoint;
        buildPoint(curPoint.x-1,curPoint.y,&vPoint);
        if (IS_ON_TRACK(vPoint))
          forceFillPoint(vPoint,limits,FILL_COLOR_INDEX);
      }
      /*else*//* if (is_vertex2(curPoint,nextPoint,1,0))
      {
        point vPoint;
        buildPoint(curPoint.x+1,curPoint.y,&vPoint);
        if (IS_ON_TRACK(vPoint))
          forceFillPoint(vPoint,limits,FILL_COLOR_INDEX);
      }
    }*/
  }

  
  /*else if (IS_ON_TRACK(nextPoint))
     trackFlood=enqueue_tflood_elem(trackFlood,create_tflood_elem(curPoint.x,curPoint.y,TRACK_COLOR_INDEX));*/
   //*trackQueue=trackFlood;
}


int is_vertex(point curPoint,point nextPoint,int xStep,int YStep)
{
  point vCurPoint,vNextPoint;
  if (curPoint.y+YStep<=0||curPoint.y+YStep>=PLAYGROUND_HEIGHT-1)
    return 1;
  buildPoint(curPoint.x+xStep,curPoint.y+YStep,&vCurPoint);
  buildPoint(nextPoint.x+xStep,nextPoint.y+YStep,&vNextPoint);
    //logWrite("is_vertex provo torno zero per %d,%d\n",curPoint.x+xStep,curPoint.y+YStep);
  
  
  if (IS_ON_TRACK(vCurPoint) && (IS_ON_TRACK(vNextPoint)||IS_FILLED(vNextPoint)))
  {
    return 1;
  }
  //logWrite("is_vertex torno zero per %d,%d\n",curPoint.x+xStep,curPoint.y+YStep);
  return 0;
}



/*
Practical implementations intended for filling rectangular areas can use a loop for the west and east directions as an optimization to avoid the overhead of stack or queue management:

Flood-fill (node, target-color, replacement-color):
 1. If target-color is equal to replacement-color, return.
 2. If color of node is not equal to target-color, return.
 3. Set Q to the empty queue.
 4. Add node to Q.
 5. For each element N of Q:
 6.     Set w and e equal to N.
 7.     Move w to the west until the color of the node to the west of w no longer matches target-color.
 8.     Move e to the east until the color of the node to the east of e no longer matches target-color.
 9.     For each node n between w and e:
10.         Set the color of n to replacement-color.
11.         If the color of the node to the north of n is target-color, add that node to Q.
12.         If the color of the node to the south of n is target-color, add that node to Q.
13. Continue looping until Q is exhausted.
14. Return.**/


void rect_flood(tBitMap* bitmap,int x, int y, UBYTE replacement_color, UBYTE target_color)
{
  struct TFlood_queue* Q,*N;
  UBYTE color_node=chunkyFromPlanar(bitmap, x,y);
  int xWest,xEast;

  //1. If target-color is equal to replacement-color, return.
  if (target_color==replacement_color) return ;
  
  //2. If color of node is not equal to target-color, return.
  if (color_node!=target_color) return ;
  
  // 3. Set Q to the empty queue.
  Q=NULL;
  
  //4. Add node to Q.
  Q=create_tflood_elem(x,y,color_node);

  // 5. For each element N of Q:
  for (N=Q;N;N=N->next)
  {
    //  6.     Set w and e equal to N.
    struct TFlood_queue* W,*E=N;

    // 7.     Move w to the west until the color of the node to the west of w no longer matches target-color.
    for (xWest=N->x-1;chunkyFromPlanar(bitmap,xWest,N->y)!=target_color;xWest--) {}
    
      //


      /*if (chunkyFromPlanar(bitmap,xWest,y)!=target_color)
      {
        create_tflood_elem(x,y-1,color_node);
      }*/
    

    // 8.     Move e to the east until the color of the node to the east of e no longer matches target-color.
    for (xEast=xWest+1;chunkyFromPlanar(bitmap,xWest,N->y)!=target_color;xEast++) {}

    // 9.     For each node n between w and e:
    for (int xCont=xWest;xCont<=xEast;xCont++)
    {
      // 10.         Set the color of n to replacement-color.
      chunkyToPlanar(replacement_color, xCont, y, bitmap);
    }




  }
}

// Create flood element
struct TFlood_queue* create_tflood_elem(int x,int y,UBYTE color)
{
  struct TFlood_queue* queue_elem=(struct TFlood_queue*)malloc(sizeof(struct TFlood_queue));
  queue_elem->color=color;
  queue_elem->x=x;
  queue_elem->y=y;
  queue_elem->next=NULL;
  return queue_elem;
}

// Put a new element at the end of the queue
struct TFlood_queue* enqueue_tflood_elem(struct TFlood_queue* Q,struct TFlood_queue* newelem)
{
  struct TFlood_queue* ptr=Q;
  if (Q==NULL) return newelem;
  while (ptr->next!=NULL)
    ptr=ptr->next;
  ptr->next=newelem;
  return Q;
}

void forceFillAll(struct TFlood_queue N,int XStep,int YStep,Coordlimits* limits,int replacement_color,struct TFlood_queue** trackQueue)
{
  int forceBreak=0;
  point nextPoint,curPoint;
  struct TFlood_queue* trackFlood=*trackQueue;

  //buildPoint(N.x+XStep,N.y+YStep,&curPoint);
  buildPoint(N.x+XStep,N.y+YStep,&curPoint);
    
  // Continue until BLUE
  while (forceBreak==0  && PLAYGROUND[curPoint.y][curPoint.x]==TRACK_COLOR_INDEX)
  {
    // Break if position is shared with the cursor
    //if (XCursorPosition==forceFillXPosition && YCursorPosition==N.y) break;

      
    // Init nextpoint
    buildPoint(curPoint.x+XStep,curPoint.y+YStep,&nextPoint);
    /*nextPoint.x=curPoint.x+XStep;
    nextPoint.y=curPoint.y+YStep;*/



    // check if next point is in the playearea

//|| inside_playarea(nextPoint)==0
    // Fill only if next position is NOT EMPTY (fill color or track color or cursor color) fill and exit  printf("Forcefillall!!!\n");

    if (PLAYGROUND[nextPoint.y][nextPoint.x]!=EMPTY_COLOR_INDEX || inside_playarea(nextPoint)==0)
    {
      if (PLAYGROUND[nextPoint.y][nextPoint.x]==TRACK_COLOR_INDEX || PLAYGROUND[nextPoint.y][nextPoint.x]==CURSOR_COLOR_INDEX )
      {
        trackFlood=enqueue_tflood_elem(trackFlood,create_tflood_elem(curPoint.x,curPoint.y,TRACK_COLOR_INDEX));
      }
      else 
      {
        point prevPoint;
        buildPoint(curPoint.x-XStep,curPoint.y-YStep,&prevPoint);
        if (PLAYGROUND[prevPoint.y][prevPoint.x]!=TRACK_COLOR_INDEX) forceFillPoint(curPoint,limits,replacement_color);
        
          else trackFlood=enqueue_tflood_elem(trackFlood,create_tflood_elem(curPoint.x,curPoint.y,TRACK_COLOR_INDEX));
      }
      if (PLAYGROUND[nextPoint.y][nextPoint.x]!=TRACK_COLOR_INDEX )
      {
        forceBreak=1;

        // search for polygon inside the filled area
        point insideshapePoint;
        buildPoint(nextPoint.x+XStep,nextPoint.y+YStep,&insideshapePoint);
        while (inside_playarea(insideshapePoint))
        {
          if (PLAYGROUND[insideshapePoint.y][insideshapePoint.x]==TRACK_COLOR_INDEX || PLAYGROUND[insideshapePoint.y][insideshapePoint.x]==CURSOR_COLOR_INDEX )
          {
            trackFlood=enqueue_tflood_elem(trackFlood,create_tflood_elem(insideshapePoint.x,insideshapePoint.y,TRACK_COLOR_INDEX));
            //forceFillPoint(insideshapePoint,limits,replacement_color);
          }
          insideshapePoint.x+=XStep;
          insideshapePoint.y+=YStep;
        }
      }
    }
    else forceBreak=1;

    if (forceBreak==0)
    {
      curPoint.x+=XStep;
      curPoint.y+=YStep;
    }
  }

  *trackQueue=trackFlood;
}

void forceFillPoint(point curPoint,Coordlimits* limits,int replacement_color)
{
  if (curPoint.y<0) return;
  if (PLAYGROUND[curPoint.y][curPoint.x]==replacement_color) return ;
  PLAYGROUND[curPoint.y][curPoint.x]=replacement_color;
  SCORE++;
  if (curPoint.y<limits->minY) limits->minY=curPoint.y;
  if (curPoint.y>limits->maxY) limits->maxY=curPoint.y;
}

int inside_playarea ( point P  )
{
  if (P.x>=X1 && P.x<=X2 && P.y>=0 && P.y<PLAYGROUND_HEIGHT) return 1;
  return 0;
}
