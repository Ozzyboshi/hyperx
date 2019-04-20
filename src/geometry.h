#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_
typedef struct
{
	int x , y ;
	struct point* next;
	struct point* prev;
} point ;
point* point_enqueue(point* ,int ,int );

int compreso ( int , int , int );
int interseca ( point  , point  , point  );
int interno ( point  , point *   );
void buildPoint(int ,int ,point* );

int geometryGetRightArea(point* ,int ,point,point);


#endif // _GEOMETRY_H_
