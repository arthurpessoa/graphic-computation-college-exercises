#include "polygon.h"


Polygon *polygon_create(coordinates data)
{
  Polygon *node;
  if(!(node=malloc(sizeof(Polygon)))) return NULL;
  node->data=data;
  node->next=NULL;
  return node;
}

Polygon *polygon_insert_point(Polygon *list, coordinates data)
{
  Polygon *newnode;
  newnode=polygon_create(data);
  newnode->next = list;
  return newnode;
}

coordinates polygon_max(Polygon *node){
  float xMax,yMax;

  yMax=node->data.Y;
  xMax=node->data.X;

  //descubro quais os X,Y maior e menor
  while(node) {
    if(node->data.X>xMax)xMax=node->data.X;
    if(node->data.Y>yMax)yMax=node->data.Y;
    node=node->next;
  }
  return getCoord(xMax,yMax);
}

coordinates polygon_min(Polygon *node){
  float xMin,yMin;
  
  yMin=node->data.Y;
  xMin=node->data.X;

  //descubro quais os X,Y maior e menor
  while(node) {
    if(node->data.X<xMin)xMin=node->data.X;
    if(node->data.Y<yMin)yMin=node->data.Y;
    node=node->next;
  }

  return getCoord(xMin,yMin);
}

void dispose_polygon(Polygon *node){
  if(node==NULL)return;
  dispose_polygon(node->next);
  free(node);
  return;
}

int polygon_to_srd(Polygon *node,Environment e,coordinates min, coordinates max)
{
  while(node) {
    node->data=SRUToSRD(node->data,min, max, e);
    node=node->next;
  }
  return 0;
}

int polygon_foreach(Polygon *node, int(*func)(coordinates))
{
  while(node) {
    if(func(node->data)!=0) return -1;
    node=node->next;
  }
  return 0;
}
Polygon * clone_polygon(Polygon *node){
  Polygon *copy;
  copy=polygon_create(node->data);
  node=node->next;
  while(node) {
    copy=polygon_insert_point(copy,node->data);
    node=node->next;
  }
  return copy;
}

int print_coord(coordinates data)
{
  printf("(%f,%f)-->", data.X,data.Y);
  return 0;
}

int add_polygon(Environment *e, Polygon *node, rgb_color c){ //float x1,float y1,float x2,float y2
  while(node && node->next) {
    line(e,node->data.X,node->data.Y,node->next->data.X,node->next->data.Y,c);
    node=node->next;
  }  
}


void rotate_polygon(Polygon *node,float ang){
  matrix3 m = rot3(ang); //crio uma matriz de rotação
  while(node) {
    node->data=transform(m,node->data);
    node=node->next;
  }
}
void translate_polygon(Polygon *node, float X, float Y){
  matrix3 m = trans3(X,Y); //crio uma matriz de translação
  while(node) {
    node->data=transform(m,node->data);
    node=node->next;
  }
}

void scale_polygon(Polygon *node, float X, float Y){
  matrix3 m = scale3(X,Y); //crio uma matriz de escala
  while(node) {
    node->data=transform(m,node->data);
    node=node->next;
  }
}

coordinates transform(matrix3 m, coordinates p){
  coordinates ret;
  ret.X = m.m[0][0] * p.X + m.m[0][1] * p.Y + m.m[0][2] * p.W;
  ret.Y = m.m[1][0] * p.X + m.m[1][1] * p.Y + m.m[1][2] * p.W;
  ret.W = 1;
  return ret;
}

matrix3 rot3(float ang){
  float rad = (M_PI/180)*ang;
  matrix3 matrix;
  matrix.m[0][0]=cos(rad);
  matrix.m[0][1]=-sin(rad);
  matrix.m[0][2]=0;
  matrix.m[1][0]=sin(rad);
  matrix.m[1][1]=cos(rad);
  matrix.m[1][2]=0;
  matrix.m[2][0]=0;
  matrix.m[2][1]=0;
  matrix.m[2][2]=1;
  return matrix;
}

matrix3 trans3(float dx, float dy){
  matrix3 matrix;
  matrix.m[0][0] = 1;
  matrix.m[0][1] = 0;
  matrix.m[0][2] = dx;
  matrix.m[1][0] = 0;
  matrix.m[1][1] = 1;
  matrix.m[1][2] = dy;
  matrix.m[2][0] = 0;
  matrix.m[2][1] = 0;
  matrix.m[2][2] = 1;
  return matrix;
}

matrix3 scale3(float sx, float sy){
  matrix3 matrix;
  matrix.m[0][0] = sx;
  matrix.m[0][1] = 0;
  matrix.m[0][2] = 0;
  matrix.m[1][0] = 0;
  matrix.m[1][1] = sy;
  matrix.m[1][2] = 0;
  matrix.m[2][0] = 0;
  matrix.m[2][1] = 0;
  matrix.m[2][2] = 1;
  return matrix;
}

rgb_color getPositionColor(Environment *e,int x,int y){
  int R = (int)e->ximage -> data[((int)y*4)*e->width+(int)x*4+2];
  int G = (int)e->ximage -> data[((int)y*4)*e->width+(int)x*4+1];
  int B = (int)e->ximage -> data[((int)y*4)*e->width+(int)x*4+0];
  return getRGB(R,G,B);
}

void floodfill(Environment *e, int x, int y, rgb_color background, rgb_color c){

    if(!rgb_color_compare(getPositionColor(e,x,y), background)) return;
    draw_point(e,x,y,c);
    floodfill(e, x+1, y, background, c);
    floodfill(e, x-1, y, background, c);
    floodfill(e, x, y+1, background, c);
    floodfill(e, x, y-1, background, c);
    return;
}
