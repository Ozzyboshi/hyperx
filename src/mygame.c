#include <ace/managers/key.h> // We'll use key* fns here
#include <ace/managers/game.h> // For using gameClose
#include <ace/managers/system.h> // For systemUnuse and systemUse
#include <ace/managers/viewport/simplebuffer.h> // Simple buffer
#include <ace/utils/chunky.h>
#include <ace/managers/joy.h>
#include <ace/managers/blit.h>
#include "coords.h"
#include "mygame.h"
#include "flood.h"
#include "geometry.h"
#include <stdlib.h>
#include "white.h"
#include "../images/Valkyrie2.h"
#include "../music/forden.h"

//#define   REG(x,y) register y __asm(#x)
#define SOUND

int interno2 ( point , point* );
int interno3 ( point , point* );

int geometryGetRightArea2(point* ,int ,point,point);
int geometryReverseArea2(point* ,int ,point,point);
void refreshScreenRealPlay();
void snd_init();
long mt_init(const unsigned char*);
void mt_music();
void wait1();
void wait2();


// "Gamestate" is a long word, so let's use shortcut "Gs" when naming fns
tView *s_pView,*s_pViewRealPlay;
tSimpleBufferManager *s_pMainBuffer,*s_pMainBufferRealPlay;
tVPort *s_pVpMain,*s_pVpMainRealPlay,*s_pVpMainCurrent;
tSimpleBufferManager *s_pScoreBuffer,*s_pScoreBufferRealPlay;

int X1,X2,Y1,Y2;
//UBYTE PLAYGROUND [PLAYGROUND_HEIGHT][PLAYGROUND_WIDTH];
UBYTE PLAYGROUND [PLAYGROUND_HEIGHT][XSCREEN_RES];
int YPADDING=0;
int PVPMAIN_XMIDDLEPOINT,PVPMAIN_YMIDDLEPOINT;
//point* pointList;

void gameGsCreate(void) {
  int i;
  //static tView *s_pView; // View containing all the viewports

  static tVPort *s_pVpScore,*s_pVpScoreRealPlay; // Viewport for score
  // static tSimpleBufferManager *s_pScoreBuffer,*s_pScoreBufferRealPlay;
  
  //static tVPort *s_pVpMain; // Viewport for playfield
  //static tSimpleBufferManager *s_pMainBuffer;

  s_pView = viewCreate(0,TAG_VIEW_GLOBAL_CLUT, 1,TAG_END);
  s_pVpScore = vPortCreate(0,TAG_VPORT_VIEW, s_pView,TAG_VPORT_BPP, 2,TAG_VPORT_HEIGHT, 32,TAG_END);
  s_pScoreBuffer = simpleBufferCreate(0,TAG_SIMPLEBUFFER_VPORT, s_pVpScore, TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_CLEAR,TAG_END);
  s_pVpMain = vPortCreate(0,TAG_VPORT_VIEW, s_pView,TAG_VPORT_BPP, 4,TAG_END);
  s_pMainBuffer = simpleBufferCreate(0,TAG_SIMPLEBUFFER_VPORT, s_pVpMain,TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_CLEAR,TAG_END);

  s_pViewRealPlay = viewCreate(0,TAG_VIEW_GLOBAL_CLUT, 1,TAG_END);
  s_pVpScoreRealPlay = vPortCreate(0,TAG_VPORT_VIEW, s_pViewRealPlay,TAG_VPORT_BPP, 4,TAG_VPORT_HEIGHT, 32,TAG_END);
  s_pScoreBufferRealPlay = simpleBufferCreate(0,TAG_SIMPLEBUFFER_VPORT, s_pVpScoreRealPlay, TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_CLEAR,TAG_END);
  s_pVpMainRealPlay = vPortCreate(0,TAG_VPORT_VIEW, s_pViewRealPlay,TAG_VPORT_BPP, 4,TAG_END);
  s_pMainBufferRealPlay = simpleBufferCreate(0,TAG_SIMPLEBUFFER_VPORT, s_pVpMainRealPlay,TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_CLEAR,TAG_END);
  
//  blitLine(s_pMainBuffer->pBack, 60, 10, 260, 10, 1, 0xFFFF, 0);
  
  // Build play area
  X1=PLAYGROUND_X1(s_pVpMain);
  X2=PLAYGROUND_X2(s_pVpMain);
  Y1=PLAYGROUND_Y1(s_pVpMain);
  Y2=PLAYGROUND_Y2(s_pVpMain);
  YPADDING=PLAYGROUND_Y2(s_pVpMain);
  PVPMAIN_XMIDDLEPOINT=(int)s_pVpMain->uwWidth/2;
  PVPMAIN_YMIDDLEPOINT=PLAYGROUND_HEIGHT/2;

  for (int yCont=0;yCont<PLAYGROUND_HEIGHT;yCont++)
    for (int xCont=0;xCont<320;xCont++)
       PLAYGROUND[yCont][xCont]=0;
  
  //blitLine(s_pMainBuffer->pBack, X1-10, Y1, X2+10, Y1, 1, 0xFFFF, 0); // Horizontal bottom
  //blitLine(s_pMainBuffer->pBack, X1-10, Y2-1, X2+10, Y2-1, 1, 0xFFFF, 0); // Horizontal top
  
  // Draw horizontal
  for (i=X1;i<X2;i++)
  {
    PLAYGROUND[0][i]=(UBYTE)3;
    PLAYGROUND[PLAYGROUND_HEIGHT-1][i]=(UBYTE)3;
  }
  logWrite("Y1: %d Y2: %d - PLAYGROUND_HEIGHT : %d YPADDING: %d\n",Y1,Y2,PLAYGROUND_HEIGHT,YPADDING);
  
  //blitLine(s_pMainBuffer->pBack, X1, Y2, X1 ,Y1, 1, 0xFFFF, 0); // Vertical left
  //blitLine(s_pMainBuffer->pBack, X2, Y2, X2 ,Y1, 1, 0xFFFF, 0); // Vertical right

  for (i=0;i<PLAYGROUND_HEIGHT;i++) {PLAYGROUND[i][X1]=(UBYTE)3;PLAYGROUND[i][X2]=(UBYTE)3;}
  /*for (int yCont=0;yCont<PLAYGROUND_HEIGHT;yCont++)
    for (int xCont=0;xCont<320;xCont+=16)
      chunkyToPlanar16(&PLAYGROUND[yCont][xCont],xCont,yCont+Y2,s_pMainBuffer->pFront);*/
  refreshscreen(0,PLAYGROUND_HEIGHT);
  refreshScreenRealPlay();
  
  //bitmapLoadFromFile(s_pMainBuffer->pBuffer,"background.bm",0,0);
  for (i=1;i<10;i++)
  {
    chunkyToPlanar(1, 16*i, 0, s_pScoreBuffer->pBack);
  }
  for (i=1;i<10;i++)
  {
    chunkyToPlanar(2, 16*i, 5, s_pScoreBuffer->pFront);
  }
  for (i=1;i<10;i++)
  {
    chunkyToPlanar(3, 16*i, 7, s_pScoreBuffer->pFront);
  }
  
  s_pVpScore->pPalette[0] = 0x0000; // First color is also border color
  s_pVpScore->pPalette[1] = 0x0F00; // Gray
  s_pVpScore->pPalette[2] = 0x00F0; // Red - not max, a bit dark
  s_pVpScore->pPalette[3] = 0x000F; // Blue - same brightness as red

  s_pVpScoreRealPlay->pPalette[0] = 0x0000; // First color is also border color
  s_pVpScoreRealPlay->pPalette[1] = 0x0F00; // Gray
  s_pVpScoreRealPlay->pPalette[2] = 0x00F0; // Red - not max, a bit dark
  s_pVpScoreRealPlay->pPalette[3] = 0x000F; // Blue - same brightness as red*/

  s_pVpScoreRealPlay->pPalette[4] = 0x019; // First color is also border color
  s_pVpScoreRealPlay->pPalette[5] = 0x0B66; // Gray
  s_pVpScoreRealPlay->pPalette[6] = 0x0CCC; // Red - not max, a bit dark
  s_pVpScoreRealPlay->pPalette[7] = 0x0620;
  s_pVpScoreRealPlay->pPalette[8] = 0x955; // First color is also border color
  s_pVpScoreRealPlay->pPalette[9] = 0x0FA8; // Gray
  s_pVpScoreRealPlay->pPalette[10] = 0x0E0A; // Red - not max, a bit dark
  s_pVpScoreRealPlay->pPalette[11] = 0x0F99;
  s_pVpScoreRealPlay->pPalette[12] = 0x0F88; // First color is also border color
  s_pVpScoreRealPlay->pPalette[13] = 0x0EAA; // Gray
  s_pVpScoreRealPlay->pPalette[14] = 0x0004; // Red - not max, a bit dark
  s_pVpScoreRealPlay->pPalette[15] = 0x078A;


  
  /*s_pVpMain->pPalette[0] = 0x0000; // First color is also border color
  s_pVpMain->pPalette[1] = 0x0F00; // Gray
  s_pVpMain->pPalette[2] = 0x0F00; // Red - not max, a bit dark
  s_pVpMain->pPalette[3] = 0x0F00;*/ // Blue - same brightness as red
  
  //UBYTE lol = chunkyFromPlanar(s_pScoreBuffer->pBack, 16,0);
  
  // Initializations for this gamestate - load bitmaps, draw background, etc.
  // We don't need anything here right now except for unusing OS
  systemUnuse();
  g_pCustom->intena = INTF_SETCLR | INTF_INTEN | (
                        INTF_BLIT | INTF_COPER | INTF_VERTB |   
                        INTF_PORTS
                );
  logWrite("intena :  %d\n",INTF_SETCLR | INTF_INTEN | (INTF_BLIT | INTF_COPER | INTF_VERTB |   INTF_PORTS));
  logWrite("intenar : %d\n",g_pCustom->intenar);
  s_pVpMainCurrent=s_pVpMainRealPlay;
  viewLoad(s_pViewRealPlay);
   
    /*register int a __asm("a0");
    a=&forden_data;*/
  //long a = (long)forden_data;

#ifdef SOUND  
  mt_init(forden_data);
#endif

  /*  if (mt_init(forden_data)==1)
    {
      viewLoad(s_pViewRealPlay);
      s_pVpMainCurrent=s_pVpMainRealPlay;
    }
    else
    {
      viewLoad(s_pView);
    }*/

}

void gameGsLoop(void) {
  static int XCoordinate=-1;
  static int YCoordinate=-1;
  static int oldXCoordinate=0;
  static int oldYCoordinate=0;
  static UBYTE drawSession=0; // Holds 1 if we are drawing
  static int lastMoveflag=0;
  static int orientation=0;
  static int firstMoveLastDraw=0;
  static point* pointList;
  static point firstPoint;
  static unsigned int cornerCounter;

  UBYTE fillShape=0;
  int corner=0;
  int YFloodCoordinate=0;
  int XFloodCoordinate=0;
  int firePressed=0;

  //if (fillShape) return ;
  
  // Cursor starts at the upper left corner
  if (XCoordinate==-1) XCoordinate=PLAYGROUND_X1(s_pVpMain);
  if (YCoordinate==-1) YCoordinate=PLAYGROUND_Y2(s_pVpMain);
  
  int moveFlag=0;
  
  //vPortWaitForEnd(s_pVpMain); // Wait for vertical blank

  //vPortWaitForEnd(s_pVpMainCurrent);
 /* UWORD uwEndPos = s_pVpMainCurrent->uwOffsY + s_pVpMainCurrent->uwHeight + 0x2C;
  UWORD uwCurrFrame;
  if(g_pRayPos->bfPosY < uwEndPos)
  {
    while(g_pRayPos->bfPosY < uwEndPos) {}
  }
else {
    // Otherwise wait for pos @ next frame
    uwCurrFrame = timerGet();
    while(
      g_pRayPos->bfPosY < uwEndPos || timerGet() == uwCurrFrame ) {       
}
  }*/

#ifdef SOUND
  wait1();
  mt_music();
#endif
  
  //if (skipFrame) {skipFrame=0; return; }
  
  // This will loop forever until you "pop" or change gamestate
  // or close the game
  if(keyCheck(KEY_ESCAPE)||joyCheck(JOY2_FIRE)) {
    gameClose();
    return ;
  }
  else if (keyUse(KEY_1)&&s_pVpMainCurrent!=s_pVpMain)
  {
    s_pVpMainCurrent=s_pVpMain;
    viewLoad(s_pView);
  }
  else if (keyUse(KEY_2)&&s_pVpMainCurrent!=s_pVpMainRealPlay)
  {
    s_pVpMainCurrent=s_pVpMainRealPlay;
    viewLoad(s_pViewRealPlay);
  }
  else {
    // Process loop normally
    // We'll come back here later
    
    // Save old coords
    oldXCoordinate=XCoordinate;
    oldYCoordinate=YCoordinate;
    
    // Process joy input
    if(joyCheck(JOY1_RIGHT)) 	    { XCoordinate+=1; moveFlag=JOY1_RIGHT; }
    else if(joyCheck(JOY1_LEFT))  { XCoordinate-=1; moveFlag=JOY1_LEFT; }
    else if(joyCheck(JOY1_DOWN))  { YCoordinate+=1; moveFlag=JOY1_DOWN; }
    else if(joyCheck(JOY1_UP))    { YCoordinate-=1; moveFlag=JOY1_UP; }
    if(joyCheck(JOY1_FIRE))  firePressed=1;

    // If the user moved the cursor i check if there is a change of direction
    if (moveFlag && lastMoveflag!=moveFlag)
    {
      // underclock wise
      if (lastMoveflag==JOY1_DOWN && moveFlag==JOY1_RIGHT)       {corner=1;orientation--; logWrite("change orientation :%d\n",orientation);}
      else if (lastMoveflag==JOY1_RIGHT && moveFlag==JOY1_UP)    {corner=1;orientation--; logWrite("change orientation :%d\n",orientation);}
      else if (lastMoveflag==JOY1_UP && moveFlag==JOY1_LEFT)     {corner=1;orientation--; logWrite("change orientation :%d\n",orientation);}
      else if (lastMoveflag==JOY1_LEFT && moveFlag==JOY1_DOWN)   {corner=1;orientation--; logWrite("change orientation :%d\n",orientation);}

      // clock wise
      if (lastMoveflag==JOY1_DOWN && moveFlag==JOY1_LEFT)        {corner=1;orientation++; logWrite("change orientation :%d\n",orientation);}
      else if (lastMoveflag==JOY1_LEFT && moveFlag==JOY1_UP)     {corner=1;orientation++; logWrite("change orientation :%d\n",orientation);}
      else if (lastMoveflag==JOY1_UP && moveFlag==JOY1_RIGHT)    {corner=1;orientation++; logWrite("change orientation :%d\n",orientation);}
      else if (lastMoveflag==JOY1_RIGHT && moveFlag==JOY1_DOWN)  {corner=1;orientation++; logWrite("change orientation :%d\n",orientation);}      
    }

    if (moveFlag>0) lastMoveflag=moveFlag;

    // If the user moved the cursor
    if (moveFlag)
    {

      // If new position is not allowed restore previous position
      if (!positionAllowed(XCoordinate,YCoordinate,firePressed,moveFlag))
      {
        XCoordinate=oldXCoordinate;
        YCoordinate=oldYCoordinate;
      }
      else
      {
    
        // DrawSession management
        UBYTE color = chunkyFromPlanar(s_pMainBuffer->pFront, XCoordinate,YCoordinate);
        //if (drawSession==0 && chunkyFromPlanar(s_pMainBuffer->pFront, XCoordinate,YCoordinate)==0)
        if (drawSession==0 && color==EMPTY_COLOR_INDEX)
        {
          drawSession=1;
          firstMoveLastDraw=moveFlag;
          pointList=point_enqueue(pointList,XCoordinate,YCoordinate-YPADDING);
          logWrite("\n\nDrawsession started at %d %d\n\n",XCoordinate,YCoordinate);
          buildPoint(oldXCoordinate,oldYCoordinate,&firstPoint);
        }
        //else if (drawSession==1 && chunkyFromPlanar(s_pMainBuffer->pFront, XCoordinate,YCoordinate)!=0)
        //else if (drawSession==1 && color!=EMPTY_COLOR_INDEX)
        else if (drawSession==1 && color==TRACK_COLOR_INDEX)
        {
          drawSession=0;
          pointList=point_enqueue(pointList,XCoordinate,YCoordinate-YPADDING);
          logWrite("\n\nDrawsession ended at %d %d\n\n",XCoordinate,YCoordinate);
          fillShape=1;
        }
        else if (corner && drawSession==1) 
        {
          pointList=point_enqueue(pointList,XCoordinate,YCoordinate-YPADDING);
          cornerCounter++;
        }
        
        // Plot new point
   
        PLOT_POINT(CURSOR_COLOR_INDEX,XCoordinate,YCoordinate)

       
        
        if (!firePressed||(firePressed&&!drawSession)) { PLOT_POINT(TRACK_COLOR_INDEX,oldXCoordinate,oldYCoordinate) }

        // If the draw session ended i fill the shape
        if (fillShape)
        {
          point floodCoords;
          int forceFill=0;

          // Vertical straight line
          //if ((moveFlag==JOY1_UP||moveFlag==JOY1_DOWN) /*&& cornerCounter==0*/ )
          if ((firstMoveLastDraw==JOY1_UP&&moveFlag==JOY1_UP) || (firstMoveLastDraw==JOY1_DOWN && moveFlag==JOY1_DOWN) )
          {
            logWrite("Vertical line case with 0 corners!\n");
            if (cornerCounter==0)
            {
              int xStep=1;
              if (pointList->x<PVPMAIN_XMIDDLEPOINT) xStep=-1;
              buildPoint(pointList->x+xStep,pointList->y,&floodCoords);
            }
            // case of a vertical line with angles
            else
            {
                logWrite("Vertical line case with at least 1 corner!\n");

              if (moveFlag==JOY1_DOWN)
              {
                point point1,point2;
                buildPoint(X2,-1*(Y1-YPADDING),&point1);
                buildPoint(X2,-1*(Y2-YPADDING),&point2);

                logWrite("Point 1: %d,%d\n",point1.x,point1.y);
                logWrite("Point 2: %d,%d\n",point2.x,point2.y);
                int rightArea = geometryGetRightArea2(pointList,0,point1,point2);
                logWrite("Right area: %d\n",rightArea);

                buildPoint(X1,-1*(Y2-YPADDING),&point1);
                buildPoint(X1,-1*(Y1-YPADDING),&point2);
                logWrite("Point 1: %d,%d\n",point1.x,point1.y);
                logWrite("Point 2: %d,%d\n",point2.x,point2.y);
                int leftArea = geometryReverseArea2(pointList,0,point1,point2);
                logWrite("Left area: %d\n",leftArea);
                if (rightArea<leftArea)
                  buildPoint(pointList->x+1,pointList->y,&floodCoords);
                else
                  buildPoint(pointList->x-1,pointList->y,&floodCoords);
              }
              else
              {
                point point1,point2;
                buildPoint(X2,-1*(Y1-YPADDING),&point1);
                buildPoint(X2,-1*(Y2-YPADDING),&point2);

                logWrite("Point 1: %d,%d\n",point1.x,point1.y);
                logWrite("Point 2: %d,%d\n",point2.x,point2.y);
                int rightArea = geometryReverseArea2(pointList,0,point1,point2);
                logWrite("Right area: %d\n",rightArea);

                buildPoint(X1,-1*(Y2-YPADDING),&point1);
                buildPoint(X1,-1*(Y1-YPADDING),&point2);
                logWrite("Point 1: %d,%d\n",point1.x,point1.y);
                logWrite("Point 2: %d,%d\n",point2.x,point2.y);
                int leftArea = geometryGetRightArea2(pointList,0,point1,point2);
                logWrite("Left area: %d\n",leftArea);
                if (rightArea<leftArea)
                  buildPoint(pointList->x+1,pointList->y,&floodCoords);
                else
                  buildPoint(pointList->x-1,pointList->y,&floodCoords);
              }
            }
          }

          // Horizontal straight line
         // else if ((moveFlag==JOY1_LEFT||moveFlag==JOY1_RIGHT) /*&& cornerCounter==0*/ )
          if ((firstMoveLastDraw==JOY1_LEFT&&moveFlag==JOY1_LEFT) || (firstMoveLastDraw==JOY1_RIGHT && moveFlag==JOY1_RIGHT) )
          {
            if (cornerCounter==0)
            {
              logWrite("Horizontal line case with 0 corners! %d,%d,%d\n",pointList->y,YPADDING,PVPMAIN_YMIDDLEPOINT);
              int yStep=-1;
              if (pointList->y*-1-YPADDING<PVPMAIN_YMIDDLEPOINT) yStep=1;
              buildPoint(pointList->x,pointList->y+yStep,&floodCoords);
            }
            else
            {
              logWrite("Horizontal line case with al least corner! %d,%d,%d\n",pointList->y,YPADDING,PVPMAIN_YMIDDLEPOINT);
              if (moveFlag==JOY1_RIGHT)
              {
                point point1,point2;
                buildPoint(X2,-1*(Y2-YPADDING),&point1);
                buildPoint(X1,-1*(Y2-YPADDING),&point2);

                logWrite("Point 1: %d,%d\n",point1.x,point1.y);
                logWrite("Point 2: %d,%d\n",point2.x,point2.y);
                int upArea = geometryGetRightArea2(pointList,0,point1,point2);
                logWrite("Up area: %d\n",upArea);

                buildPoint(X1,-1*(Y1-YPADDING),&point1);
                buildPoint(X2,-1*(Y1-YPADDING),&point2);
                logWrite("Point 1: %d,%d\n",point1.x,point1.y);
                logWrite("Point 2: %d,%d\n",point2.x,point2.y);
                int downArea = geometryReverseArea2(pointList,0,point1,point2);
                logWrite("Down area: %d\n",downArea);
                if (upArea<downArea)
                  buildPoint(pointList->x,pointList->y-1,&floodCoords);
                else
                  buildPoint(pointList->x,pointList->y+1,&floodCoords);
              }
            }
          }
          //chunkyToPlanar(2, XCoordinate+1, YCoordinate-1, s_pMainBuffer->pFront);
          //flood(XCoordinate+1, YCoordinate-1,2,0); 
          //point tryPoint;

          /*// Up right
          tryPoint.x=XCoordinate+1+1;
          tryPoint.y=-1*(YCoordinate-YPADDING-1-1);
          logWrite("Interno upright: %d (%d,%d)\n",interno2(tryPoint,pointList),tryPoint.x,tryPoint.y);*/
          
          /*//Down right

          tryPoint.x=XCoordinate+1;
          tryPoint.y=-1*(YCoordinate-YPADDING+1);
          logWrite("Interno downright: %d (%d,%d)\n",interno2(tryPoint,pointList),tryPoint.x,tryPoint.y);
          
          // Up left
          tryPoint.x=XCoordinate-1;
          tryPoint.y=-1*(YCoordinate-YPADDING-1);
          logWrite("Interno upleft: %d (%d,%d)\n",interno2(tryPoint,pointList),tryPoint.x,tryPoint.y);*/

          // Down left
         /* tryPoint.x=XCoordinate-2;
          tryPoint.y=-1*(YCoordinate-YPADDING+2);
          logWrite("Interno downleft: %d (%d,%d)\n",interno2(tryPoint,pointList),tryPoint.x,tryPoint.y);*/

          //int YFloodCoordinate=0;
          //if (orientation>0) YFloodCoordinate=YCoordinate-YPADDING-1;
          //else if (orientation<0)  YFloodCoordinate=YCoordinate-YPADDING+1;

          else
          {
            int coordFound=1;
            
            logWrite("**************** FIND OUT THE CORNER POINT !!!!!! ************************\n");
            for (point* ptr=pointList;coordFound&&ptr;ptr=(point*)ptr->next)
            {
              logWrite("Corner Point :##%d,%d##\n",ptr->x,ptr->y);
              coordFound=getFloodCoords(pointList, ptr->x, ptr->y,&XFloodCoordinate,&YFloodCoordinate,&floodCoords);
              // if the coord found is already filled go on and try the next
              if (PLAYGROUND[-1*floodCoords.y][floodCoords.x]==FILL_COLOR_INDEX) coordFound=1;
            }
            PLOT_POINT(CURSOR_COLOR_INDEX,firstPoint.x,firstPoint.y) // Mark where the session really started with a red dot

            //getFloodCoords( XCoordinate, YCoordinate,&XFloodCoordinate,&YFloodCoordinate);

            
            
            if (firstMoveLastDraw==JOY1_RIGHT) forceFill|=1;
            else if (firstMoveLastDraw==JOY1_LEFT) forceFill|=2;
            else if (firstMoveLastDraw==JOY1_DOWN) forceFill|=4;
            else if (firstMoveLastDraw==JOY1_UP) forceFill|=8;
            if (moveFlag==JOY1_UP) forceFill|=4;
          }
          logWrite("Shape flood starts at (%d,%d), orientation: %d Coordinates: %d,%d\n",floodCoords.x,-1*floodCoords.y,orientation,XCoordinate,YCoordinate);

          Coordlimits* limits = shape_flood(floodCoords.x, -1*floodCoords.y,FILL_COLOR_INDEX,EMPTY_COLOR_INDEX,ALL,forceFill);
          //Coordlimits* limits = shape_flood(s_pMainBuffer->pFront,floodCoords.x, floodCoords.y,FILL_COLOR_INDEX,0,1);
          //Coordlimits* limits=NULL;
          if (limits)
          {
            logWrite("Y limits : %d,%d- yMaxFlodded:%d\n",limits->minY,limits->maxY,limits->yMaxFlodded);
            PLOT_POINT(TRACK_COLOR_INDEX,firstPoint.x,firstPoint.y)
            refreshscreen(limits->minY-2,limits->maxY+2);
            refreshScreenRealPlay();
            free(limits);
          }
          else 
          {
              refreshscreen(0,PLAYGROUND_HEIGHT);
              refreshScreenRealPlay();
          }
          
          fillShape=0;
          lastMoveflag=orientation=0;

          // Corner queue free
          point* ptr=pointList;
          while(ptr)
          {
            point* tmp=ptr;
            ptr=(point*)ptr->next;
            logWrite("Corner Point free :##%d,%d##\n",tmp->x,tmp->y);
            free(tmp);
          }
          pointList=NULL;
          logWrite("Pointlist freed!\n");
          firstMoveLastDraw=cornerCounter=0;
          return;
        }
      }
    }
  }
  #ifdef SOUND
  wait2();
  #endif
}

void gameGsDestroy(void) {
  systemUse();
  // Cleanup when leaving this gamestate
  // Empty at the moment except systemUse
}

int positionAllowed(int x,int y,int firePressed,int moveFlag)
{
  int x2=0,y2=0;
  switch (moveFlag)
  {
    case JOY1_UP: x2=x; y2=y-1; break;
    case JOY1_DOWN: x2=x; y2=y+1; break;
    case JOY1_RIGHT: x2=x+1; y2=y; break;
    case JOY1_LEFT: x2=x-1; y2=y; break;
  }
  if (firePressed && chunkyFromPlanar(s_pMainBuffer->pFront, x2,y2)==CURSOR_COLOR_INDEX)
  {
    logWrite("Mov denied (point in last draw)\n");
    return 0; 
  }

  UBYTE color = chunkyFromPlanar(s_pMainBuffer->pFront, x,y);
  //if (chunkyFromPlanar(s_pMainBuffer->pFront, x,y)==FILL_COLOR_INDEX)
  /*if (color==CURSOR_COLOR_INDEX && firePressed)
  {
    logWrite("Mov denied (point in last draw)\n");
    return 0;
  }*/

  if (color==FILL_COLOR_INDEX)
  {
    logWrite("Mov denied (point already drawn)\n");
    return 0;
  }
  else if (color==EMPTY_COLOR_INDEX && !firePressed)
  {
    logWrite("Mov denied (fire not pressed on empty point)\n");
    return 0;
  }
  // Cant go to an empty point if fire is not pressed

  if (x<X1)
  {
    logWrite("Mov denied (out of left border)\n");
    return 0;
  }
  if (x>X2)
  {
    logWrite("Mov denied (out of right border)\n");
    return 0;
  }
  if (y<Y2)
  {
    logWrite("Mov denied (out of top border)\n");
    return 0;
  }
  if (y>Y1-1)
  {
    logWrite("Mov denied (out of bottom border)\n");
    return 0;
  }
  return 1;
}

/*void flood(int x, int y, UBYTE new_col, UBYTE old_col) 
{ 
    // check current pixel is old_color or not 
    //if (getpixel(x, y) == old_col) 
    if (chunkyFromPlanar(s_pMainBuffer->pFront, x,y)==old_col)
    { 
  
        // put new pixel with new color 

        chunkyToPlanar(new_col, x, y, s_pMainBuffer->pFront);

        // recursive call for bottom pixel fill 
        flood(x + 1, y, new_col, old_col); 
  
        // recursive call for top pixel fill 
        flood(x - 1, y, new_col, old_col); 
  
        // recursive call for right pixel fill 
        flood(x, y + 1, new_col, old_col); 
  
        // recursive call for left pixel fill 
        flood(x, y - 1, new_col, old_col); 
    } 
} */

void refreshscreen(int yMin,int yMax)
{
  //for (int i=0;i<PLAYGROUND_HEIGHT;i++) {PLAYGROUND[i][X1]=(UBYTE)3;PLAYGROUND[i][X2]=(UBYTE)3;}
  //for (int yCont=0;yCont<PLAYGROUND_HEIGHT;yCont++)
  if (yMin<0) yMin=0;
  else if (yMax>PLAYGROUND_HEIGHT) yMax=PLAYGROUND_HEIGHT;
  for (int yCont=yMin;yCont<yMax;yCont++)
    for (int xCont=0;xCont<320;xCont+=16)
    {
      for (int zCont=0;zCont<16;zCont++)
      {
        if (PLAYGROUND[yCont][xCont+zCont]==CURSOR_COLOR_INDEX) PLAYGROUND[yCont][xCont+zCont]=TRACK_COLOR_INDEX;
        else if (xCont>0 && yCont>0 && PLAYGROUND[yCont][xCont+zCont]==TRACK_COLOR_INDEX && PLAYGROUND[yCont][xCont+zCont-1]==FILL_COLOR_INDEX && PLAYGROUND[yCont][xCont+zCont+1]==FILL_COLOR_INDEX && PLAYGROUND[yCont-1][xCont+zCont]==FILL_COLOR_INDEX && PLAYGROUND[yCont+1][xCont+zCont]==FILL_COLOR_INDEX) PLAYGROUND[yCont][xCont+zCont]=FILL_COLOR_INDEX;
      }
      chunkyToPlanar16(&PLAYGROUND[yCont][xCont],xCont,yCont+Y2,s_pMainBuffer->pFront);
    }
}

/*int interno2 ( point P , point* poly )
{
  int intersezioni =0;
  point prec,succ;
  //for ( i =1; i < n ; i ++)
  // Consider external for lists with less than 3 points
  if (poly == NULL || poly->next==NULL) return 0;
  point* ptr=poly;
  while (ptr)
  {
    if ( ptr->next)
    {
      prec.x=ptr->x;
      prec.y=ptr->y*-1;
      point* nextNode=(point*)ptr->next;
      succ.x=nextNode->x;
      succ.y=nextNode->y*-1;
      logWrite("Provo Interseca a %d,%d %d,%d\n",prec.x,prec.y,succ.x,succ.y);
      if (interseca (P , prec  , succ))
      {
        logWrite("Interseca a %d,%d %d,%d\n",prec.x,prec.y,succ.x,succ.y);
        intersezioni ++;
      }
    }
    else
    {
      prec.x=ptr->x;
      prec.y=ptr->y*-1;
      point* nextNode=(point*)poly;
      succ.x=nextNode->x;
      succ.y=nextNode->y*-1;
      logWrite("Provo Interseca a %d,%d %d,%d\n",prec.x,prec.y,succ.x,succ.y);
      if (interseca (P , prec  , succ))
      {
        logWrite("Interseca a %d,%d %d,%d\n",prec.x,prec.y,succ.x,succ.y);
        intersezioni ++;
      }
    }
    ptr=(point*)ptr->next;
  }
  if ( intersezioni % 2 ==0)
    return 0;
  else
    return 1;
}*/

int getFloodCoords(point* pointList,int XCoordinate,int YCoordinate,int* XFloodCoordinate,int* YFloodCoordinate,point* floodCoords)
{
  const int offset=2;
  point tryPoint;
  *XFloodCoordinate=*YFloodCoordinate=0;

  // DOWN right
  tryPoint.x=XCoordinate+offset;
  //tryPoint.y=-1*(YCoordinate-YPADDING-2);
  tryPoint.y=YCoordinate-offset;
  if (interno3(tryPoint,pointList))
  {
    *XFloodCoordinate=XCoordinate+1;
    *YFloodCoordinate=YCoordinate-1;
    floodCoords->x=tryPoint.x;
    floodCoords->y=tryPoint.y;
    logWrite("FloodPoint : downright detected\n");
    return 0;
  }
  else 
  {
    logWrite("FloodPoint : NO downright detected for point %d,%d\n",tryPoint.x,tryPoint.y);
  }
  //logWrite("Interno upright: %d (%d,%d)\n",interno2(tryPoint,pointList),tryPoint.x,tryPoint.y);
          
  //UP right
  tryPoint.x=XCoordinate+offset;
  //tryPoint.y=-1*(YCoordinate-YPADDING+2);
  tryPoint.y=YCoordinate+offset;
  //logWrite("Interno downright: %d (%d,%d)\n",interno2(tryPoint,pointList),tryPoint.x,tryPoint.y);
  if (interno3(tryPoint,pointList))
  {
    *XFloodCoordinate=XCoordinate+1;
    *YFloodCoordinate=YCoordinate+1;
    floodCoords->x=tryPoint.x;
    floodCoords->y=tryPoint.y;
    logWrite("FloodPoint : upright detected\n");
    return 0;
  }
  else logWrite("FloodPoint : NO upright detected for point %d,%d\n",tryPoint.x,tryPoint.y);

  // Down left
  tryPoint.x=XCoordinate-2;
  //tryPoint.y=-1*(YCoordinate-YPADDING-2);
  tryPoint.y=YCoordinate-offset;
  //logWrite("Interno upleft: %d (%d,%d)\n",interno2(tryPoint,pointList),tryPoint.x,tryPoint.y);
  if (interno3(tryPoint,pointList))
  {
    *XFloodCoordinate=XCoordinate-1;
    *YFloodCoordinate=YCoordinate-1;
    floodCoords->x=tryPoint.x;
    floodCoords->y=tryPoint.y;
    logWrite("FloodPoint : Down left detected\n");
    return 0;
  }
  else logWrite("FloodPoint : NO Downl eft detected for point %d,%d\n",tryPoint.x,tryPoint.y);

  // UP left
  tryPoint.x=XCoordinate-2;
  //tryPoint.y=-1*(YCoordinate-YPADDING+2);
  tryPoint.y=YCoordinate+offset;
  //logWrite("Interno downleft: %d (%d,%d)\n",interno2(tryPoint,pointList),tryPoint.x,tryPoint.y);
  if (interno3(tryPoint,pointList))
  {
    *XFloodCoordinate=XCoordinate-1;
    *YFloodCoordinate=YCoordinate+1;
    floodCoords->x=tryPoint.x;
    floodCoords->y=tryPoint.y;
    logWrite("FloodPoint : upleft detected\n");
    return 0;
  }
  else logWrite("FloodPoint : NO upleft detected for point %d,%d\n",tryPoint.x,tryPoint.y);
  logWrite("FloodPoint : No point inside shape detected\n");
  return 1;
}

int interno2 ( point P , point* poly )
{
  int intersezioni =0;
  point prec,succ;
  //for ( i =1; i < n ; i ++)
  // Consider external for lists with less than 3 points
  if (poly == NULL || poly->next==NULL) return 0;
  point* ptr=poly;
  while (ptr)
  {
    if ( ptr->next)
    {
      prec.x=ptr->x;
      prec.y=ptr->y*-1;
      point* nextNode=(point*)ptr->next;
      succ.x=nextNode->x;
      succ.y=nextNode->y*-1;
      logWrite("Provo Interseca a %d,%d %d,%d\n",prec.x,prec.y,succ.x,succ.y);
      if (interseca (P , prec  , succ))
      {
        logWrite("Interseca a %d,%d %d,%d\n",prec.x,prec.y,succ.x,succ.y);
        intersezioni ++;
      }
    }
    else
    {
      prec.x=ptr->x;
      prec.y=ptr->y*-1;
      point* nextNode=(point*)poly;
      succ.x=nextNode->x;
      succ.y=nextNode->y*-1;
      logWrite("Provo Interseca a %d,%d %d,%d\n",prec.x,prec.y,succ.x,succ.y);
      if (interseca (P , prec  , succ))
      {
        logWrite("Interseca a %d,%d %d,%d\n",prec.x,prec.y,succ.x,succ.y);
        intersezioni ++;
      }
    }
    ptr=(point*)ptr->next;
  }
  if ( intersezioni % 2 ==0)
    return 0;
  else
    return 1;
}

int interno3 ( point P , point* poly )
{
  int intersezioni =0;
  point prec,succ;
  //for ( i =1; i < n ; i ++)
  // Consider external for lists with less than 3 points
  if (poly == NULL || poly->next==NULL) return 0;
  point* ptr=poly;
  while (ptr)
  {
    if ( ptr->next)
    {
      prec.x=ptr->x;
      prec.y=ptr->y;
      point* nextNode=(point*)ptr->next;
      succ.x=nextNode->x;
      succ.y=nextNode->y;
      //logWrite("Provo Interseca a %d,%d %d,%d\n",prec.x,prec.y,succ.x,succ.y);
      if (interseca (P , prec  , succ))
      {
        //logWrite("Interseca a %d,%d %d,%d\n",prec.x,prec.y,succ.x,succ.y);
        intersezioni ++;
      }
    }
    else
    {
      prec.x=ptr->x;
      prec.y=ptr->y;
      point* nextNode=(point*)poly;
      succ.x=nextNode->x;
      succ.y=nextNode->y;
      //logWrite("Provo Interseca a %d,%d %d,%d\n",prec.x,prec.y,succ.x,succ.y);
      if (interseca (P , prec  , succ))
      {
        //logWrite("Interseca a %d,%d %d,%d\n",prec.x,prec.y,succ.x,succ.y);
        intersezioni ++;
      }
    }
    ptr=(point*)ptr->next;
  }
  if ( intersezioni % 2 ==0)
    return 0;
  else
    return 1;
}

void trackEvaluate(struct TFlood_queue* tflood)
{
  struct TFlood_queue* tfloodCur=tflood;
  struct TFlood_queue* tmp;
  logWrite("trackEvaluate start\n");
  while (tfloodCur)
  {
    logWrite("trackEvaluate iter\n");
    int newY=tfloodCur->y;
    int newX=tfloodCur->x;
    //PLAYGROUND[newY][newX]=CURSOR_COLOR_INDEX;
    
    // If Up and down are not zero force fill the point
   /* if (PLAYGROUND[tfloodCur->y-1][tfloodCur->x]==FILL_COLOR_INDEX && PLAYGROUND[tfloodCur->y+1][tfloodCur->x]==FILL_COLOR_INDEX)
      PLAYGROUND[newY][newX]=FILL_COLOR_INDEX;
    else*/ if (PLAYGROUND[tfloodCur->y-1][tfloodCur->x-1]==FILL_COLOR_INDEX && PLAYGROUND[tfloodCur->y+1][tfloodCur->x-1]==FILL_COLOR_INDEX && PLAYGROUND[tfloodCur->y-1][tfloodCur->x+1]==FILL_COLOR_INDEX && PLAYGROUND[tfloodCur->y+1][tfloodCur->x+11]==FILL_COLOR_INDEX)
      PLAYGROUND[newY][newX]=FILL_COLOR_INDEX;

    tmp=tfloodCur;
    tfloodCur=tfloodCur->next;
    free(tmp);
  }
}

void fillTracksCorners(struct TFlood_queue* tflood,Coordlimits* limits,int replacement_color)
{
  point upLeft,upRight;
  point downLeft,downRight;
  point curPoint;

  struct TFlood_queue* tfloodCur=tflood;
  struct TFlood_queue* tmp;
  
  while (tfloodCur)
  {
    
    buildPoint(tfloodCur->x,tfloodCur->y,&curPoint);
    logWrite("Evalueting corner (%d,%d)!\n",curPoint.x,curPoint.y);

    if (IS_FILLED(curPoint))
    {
      logWrite("Already filled!\n");
    }
    else
    {
      buildPoint(tfloodCur->x-1,tfloodCur->y-1,&upLeft);
      buildPoint(tfloodCur->x+1,tfloodCur->y-1,&upRight);
      buildPoint(tfloodCur->x-1,tfloodCur->y+1,&downLeft);
      buildPoint(tfloodCur->x+1,tfloodCur->y+1,&downRight);

      int upLeftFilled = IS_FILLED(upLeft) || inside_playarea(upLeft)==0 ? 1 : 0;
      int upRightFilled = IS_FILLED(upRight) || inside_playarea(upRight)==0 ? 1 : 0;

      int downLeftFilled = IS_FILLED(upLeft) || inside_playarea(upLeft)==0 ? 1 : 0;
      int downRightFilled = IS_FILLED(upRight) || inside_playarea(upRight)==0 ? 1 : 0;

      if (upLeftFilled&&upRightFilled&&downLeftFilled&&downRightFilled) forceFillPoint(curPoint,limits,replacement_color);
    }
    tmp=tfloodCur;
    tfloodCur=tfloodCur->next;
    free(tmp);

  }
}

int is_vertex2(point curPoint,point nextPoint,int xStep,int YStep)
{
  point vCurPoint,vNextPoint;
  if (curPoint.y+YStep<=0||curPoint.y+YStep>=PLAYGROUND_HEIGHT-1)
    return 1;
  buildPoint(curPoint.x+xStep,curPoint.y+YStep,&vCurPoint);
  buildPoint(nextPoint.x+xStep,nextPoint.y+YStep,&vNextPoint);
    //logWrite("is_vertex provo torno zero per %d,%d\n",curPoint.x+xStep,curPoint.y+YStep);
  
  
  if ((IS_ON_TRACK(vCurPoint)||IS_FILLED(vCurPoint)) && (IS_ON_TRACK(vNextPoint)||IS_FILLED(vNextPoint)))
  {
    logWrite("is_vertex torno 1\n");
    return 1;
  }
  //logWrite("is_vertex torno zero per %d,%d\n",curPoint.x+xStep,curPoint.y+YStep);
  return 0;
}

int geometryGetRightArea2(point* pointList,int reverse,point point1,point point2)
{
  int areaX=0;
  int areaY=0;
  point* ptr=pointList;
  if (reverse==0)
  {

    /*areaX=X2*Y1;
    areaY=Y2*X2;*/
    areaX=point1.x*point2.y;
    areaY=point1.y*point2.x;
    logWrite("1 Moltiplico tab 1 %d X %d parziale %d\n",point1.x,point2.y,areaX);
    logWrite("1 Moltiplico tab 2 %d X %d : parziale %d\n",point1.y,point2.x,areaY);
    /*areaX+=X2*ptr->y;
    areaY+=Y1*ptr->x;*/
    areaX+=point2.x*ptr->y;
    areaY+=point2.y*ptr->x;
    logWrite("2 Moltiplico tab 1 %d X %d parziale %d\n",point2.x,ptr->y,areaX);
    logWrite("2 Moltiplico tab 2 %d X %d : parziale %d\n",point2.y,ptr->x,areaY);
    while(ptr)
    {
      if (ptr->next)
      {
        areaX+=ptr->x*((point *)ptr->next)->y;
        areaY+=ptr->y*((point *)ptr->next)->x;
        logWrite("3 Moltiplico tab 1 %d X %d parziale %d\n",ptr->x,((point *)ptr->next)->y,areaX);
        logWrite("3 Moltiplico tab 2 %d X %d : parziale %d\n",ptr->y,((point *)ptr->next)->x,areaY);
      }
      else
      {
        areaX+=ptr->x*point1.y;
        areaY+=ptr->y*point1.x;
        logWrite("4 Moltiplico tab 1 %d X %d parziale %d\n",ptr->x,point1.y,areaX);
        logWrite("4 Moltiplico tab 2 %d X %d : parziale %d\n",ptr->y,point1.x,areaY);
      }
      ptr=(point*)ptr->next;
    }
    logWrite("areax-areay area: %d - %d\n",areaX,areaY);
   
  }
  return areaX-areaY;
}

int geometryReverseArea2(point* pointList,int reverse,point point1,point point2)
{
  int areaX=0;
  int areaY=0;
  point* ptr=pointList;
  if (reverse==0)
  {

    while(ptr->next) ptr=(point*)ptr->next;


    /*areaX=X2*Y1;
    areaY=Y2*X2;*/
    areaX=point1.x*point2.y;
    areaY=point1.y*point2.x;
    logWrite("1 Moltiplico tab 1 %d X %d parziale %d\n",point1.x,point2.y,areaX);
    logWrite("1 Moltiplico tab 2 %d X %d : parziale %d\n",point1.y,point2.x,areaY);
    /*areaX+=X2*ptr->y;
    areaY+=Y1*ptr->x;*/
    areaX+=point2.x*ptr->y;
    areaY+=point2.y*ptr->x;
    logWrite("2 Moltiplico tab 1 %d X %d parziale %d\n",point2.x,ptr->y,areaX);
    logWrite("2 Moltiplico tab 2 %d X %d : parziale %d\n",point2.y,ptr->x,areaY);

    while (ptr->prev)
    {
      if (ptr->prev)
      {
        areaX+=ptr->x*((point *)ptr->prev)->y;
        areaY+=ptr->y*((point *)ptr->prev)->x;
        logWrite("3 Moltiplico tab 1 %d X %d parziale %d\n",ptr->x,((point *)ptr->prev)->y,areaX);
        logWrite("3 Moltiplico tab 2 %d X %d : parziale %d\n",ptr->y,((point *)ptr->prev)->x,areaY);
      }
      else
      {
        areaX+=ptr->x*point1.y;
        areaY+=ptr->y*point1.x;
        logWrite("4 Moltiplico tab 1 %d X %d parziale %d\n",ptr->x,point1.y,areaX);
        logWrite("4 Moltiplico tab 2 %d X %d : parziale %d\n",ptr->y,point1.x,areaY);
      }
      ptr=(point*)ptr->prev;
    }
    logWrite("areax-areay area: %d - %d\n",areaX,areaY);
   
  }
  return areaX-areaY;
}

void refreshScreenRealPlay()
{
  blitWait();
  g_pCustom->bltcon0 = 0x0FE0;
  g_pCustom->bltcon1 = 0x0000;
  g_pCustom->bltafwm = 0xFFFF;
  g_pCustom->bltalwm = 0xFFFF;
  g_pCustom->bltamod = 0x0000;
  g_pCustom->bltbmod = 0x0000;
  g_pCustom->bltcmod = 0x0000;
  g_pCustom->bltdmod = 0x0000;
  g_pCustom->bltapt = (UBYTE*)((ULONG)s_pMainBuffer->pBack->Planes[1]);
  /*img_data=malloc(40*256);
  memset(img_data,10,40*256);*/
  /*lol=bitmapCreate((UWORD)320,(UWORD)256,(UBYTE)1,(UBYTE)0);
  memset(lol->Planes[0],0,40*256);
  memset(lol->Planes[0],0XFF,100);
  memcpy(lol->Planes[0],img1_data,100);*/
  //g_pCustom->bltbpt = (UBYTE*)((ULONG)lol->Planes[0]);
  g_pCustom->bltbpt = (UBYTE*)((ULONG)Valkyrie2_data);
  g_pCustom->bltcpt = (UBYTE*)((ULONG)s_pMainBuffer->pBack->Planes[0]);
  g_pCustom->bltdpt = (UBYTE*)((ULONG)s_pMainBufferRealPlay->pBack->Planes[0]);
  g_pCustom->bltsize = 0x3714;



  blitWait();
  g_pCustom->bltcon0 = 0x0FE0;
  g_pCustom->bltcon1 = 0x0000;
  g_pCustom->bltafwm = 0xFFFF;
  g_pCustom->bltalwm = 0xFFFF;
  g_pCustom->bltamod = 0x0000;
  g_pCustom->bltbmod = 0x0000;
  g_pCustom->bltcmod = 0x0000;
  g_pCustom->bltdmod = 0x0000;
  g_pCustom->bltapt = (UBYTE*)((ULONG)s_pMainBuffer->pBack->Planes[1]);
  g_pCustom->bltbpt = (UBYTE*)((ULONG)&Valkyrie2_data[40*256*1]);
  g_pCustom->bltcpt = (UBYTE*)((ULONG)s_pMainBuffer->pBack->Planes[0]);
  g_pCustom->bltdpt = (UBYTE*)((ULONG)s_pMainBufferRealPlay->pBack->Planes[1]);
  g_pCustom->bltsize = 0x3714;


  blitWait();
  g_pCustom->bltcon0 = 0x0F40;
  g_pCustom->bltcon1 = 0x0000;
  g_pCustom->bltafwm = 0xFFFF;
  g_pCustom->bltalwm = 0xFFFF;
  g_pCustom->bltamod = 0x0000;
  g_pCustom->bltbmod = 0x0000;
  g_pCustom->bltcmod = 0x0000;
  g_pCustom->bltdmod = 0x0000;
  g_pCustom->bltapt = (UBYTE*)((ULONG)s_pMainBuffer->pBack->Planes[1]);
  g_pCustom->bltbpt = (UBYTE*)((ULONG)&Valkyrie2_data[40*256*2]);
  g_pCustom->bltcpt = (UBYTE*)((ULONG)s_pMainBuffer->pBack->Planes[0]);
  g_pCustom->bltdpt = (UBYTE*)((ULONG)s_pMainBufferRealPlay->pBack->Planes[2]);
  g_pCustom->bltsize = 0x3714;

  blitWait();
  g_pCustom->bltcon0 = 0x0F40;
  g_pCustom->bltcon1 = 0x0000;
  g_pCustom->bltafwm = 0xFFFF;
  g_pCustom->bltalwm = 0xFFFF;
  g_pCustom->bltamod = 0x0000;
  g_pCustom->bltbmod = 0x0000;
  g_pCustom->bltcmod = 0x0000;
  g_pCustom->bltdmod = 0x0000;
  g_pCustom->bltapt = (UBYTE*)((ULONG)s_pMainBuffer->pBack->Planes[1]);
  g_pCustom->bltbpt = (UBYTE*)((ULONG)&Valkyrie2_data[40*256*3]);
  g_pCustom->bltcpt = (UBYTE*)((ULONG)s_pMainBuffer->pBack->Planes[0]);
  g_pCustom->bltdpt = (UBYTE*)((ULONG)s_pMainBufferRealPlay->pBack->Planes[3]);
  g_pCustom->bltsize = 0x3714;

  logWrite("bitmapinterleaved : %d\n",bitmapIsInterleaved(s_pMainBuffer->pBack));
  return ;

  


}

void snd_init()
{
  //mt_init();
//__asm__("bsr.w   mt_init");

/*__asm__("mt_init:\n\t\
  move.l  mt_data,A0\n\t\
  ");
__asm__( "SECTION GRAPHIC,DATA_C\n\t\
  mt_data:     dc.l mt_data1");
__asm__( "mt_data1:    dc.l 0");*/



/*
  MOVE.L  A0,mt_SongDataPtr\n\t
  MOVE.L  A0,A1\n\t
  LEA 952(A1),A1\n\t
  MOVEQ #127,D0\n\t
  MOVEQ #0,D1\n\t
mtloop:\n\t
  MOVE.L  D1,D2\n\t
  SUBQ.W  #1,D0\n\t
mtloop2:\n\t
  MOVE.B  (A1)+,D1\n\t
  CMP.B D2,D1\n\t
  BGT.S mtloop\n\t
  DBRA  D0,mtloop2\n\t
  ADDQ.B  #1,D2\n\t
  LEA mt_SampleStarts(PC),A1\n\t
  ASL.L #8,D2\n\t
  ASL.L #2,D2\n\t
  ADD.L #1084,D2\n\t
  ADD.L A0,D2\n\t
  MOVE.L  D2,A2\n\t
  MOVEQ #30,D0\n\t
mtloop3:\n\t
  CLR.L (A2)\n\t
  MOVE.L  A2,(A1)+\n\t
  MOVEQ #0,D1\n\t
  MOVE.W  42(A0),D1\n\t
  ASL.L #1,D1\n\t
  ADD.L D1,A2\n\t
  ADD.w #30,A0\n\t
  DBRA  D0,mtloop3\n\t
  OR.B  #2,$BFE001\n\t
  MOVE.B  #6,mt_speed\n\t
  CLR.B mt_counter\n\t
  CLR.B mt_SongPos\n\t
  CLR.W mt_PatternPos\n\t
mt_end:\n\t
  CLR.W $DFF0A8\n\t
  CLR.W $DFF0B8\n\t
  CLR.W $DFF0C8\n\t
  CLR.W $DFF0D8\n\t
  MOVE.W  #$F,$DFF096\n\t
  RTS\n\t");*/
}