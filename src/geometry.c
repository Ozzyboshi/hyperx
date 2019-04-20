#include <stdlib.h>
#include "geometry.h"

point* point_enqueue(point* pointList,int x,int y)
{
	point* ptr;
	point* newPoint =malloc (sizeof(point));
	newPoint->x=x;
	newPoint->y=y*-1;
	newPoint->next=NULL;
	newPoint->prev=NULL;
	if (pointList==NULL)
		return newPoint;
	ptr=pointList;
	while(ptr->next)
		ptr=(point*)ptr->next;
	ptr->next=(struct point*)newPoint;
	//point* prev=(point*)newPoint->prev;
	newPoint->prev=(point*)ptr;
	return pointList;
}

int compreso ( int a , int x , int b )
{
	if (( a <= x && x <= b ) || (b <= x && x <= a ))
		return 1;
	return 0;
}
int interseca ( point P , point p1 , point p2 )
{
	float m , q ; // retta che passa per p1 e p2 : y = m * x + q
	float inters ;
	// Y del punto di intersezione fra la retta y = m * x + q e la retta x = P . x
	if ( compreso ( p1 .x , P .x , p2 . x ))
	{
		m = ( p1 .y - p2 . y )/( float )( p1 .x - p2 . x );
		q = p1 .y - m * p1 . x ;
		inters = m * P . x + q ;
		if ( inters > P . y )
			return 1;
		else
			return 0;
	}
	return 0;
}
/*int interno ( point P , point* poly )
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
			if (interseca (P , prec  , succ))
			{
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

int interno ( point P , point* poly )
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
      prec.y=ptr->y*-1;
      point* nextNode=(point*)poly;
      succ.x=nextNode->x;
      succ.y=nextNode->y*-1;
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

void buildPoint(int x,int y,point* outPoint)
{
  outPoint->x=x;
  outPoint->y=y;
  return ;
}

int geometryGetRightArea(point* pointList,int reverse,point point1,point point2)
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
    //logWrite("Moltiplico tab 1 %d X %d\n",X2,Y1);
    /*areaX+=X2*ptr->y;
    areaY+=Y1*ptr->x;*/
    areaX+=point2.x*ptr->y;
    areaY+=point2.y*ptr->x;
    //logWrite("Moltiplico tab 1 %d X %d\n",X2,ptr->y);
    while(ptr)
    {
      if (ptr->next)
      {
        areaX+=ptr->x*((point *)ptr->next)->y;
        areaY+=ptr->y*((point *)ptr->next)->x;
        //logWrite("Moltiplico tab 1 %d X %d\n",X2,((point *)ptr->next)->y);
      }
      else
      {
        areaX+=ptr->x*point1.y;
        areaY+=ptr->y*point1.x;
        //logWrite("Moltiplico tab 1 %d X %d\n",X2,Y2);
      }
      ptr=(point*)ptr->next;
    }
    //logWrite("right area: %d\n",areaRight);
    
  }
  return areaX-areaY;
}