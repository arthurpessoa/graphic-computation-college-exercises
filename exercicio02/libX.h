#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <X11/Xlib.h> 
#define MAXIMOX 640
#define MAXIMOY 480
#define EventMask (KeyPressMask | ExposureMask)


typedef struct color {
  int red,
      green,
      blue;
}Color;

typedef struct pixel{
    Color color; //define a cor em RGB do pixel
    int printable; //esse atributo define se o pixel será impresso pela função Draw (1 = sim 0= não)
}Pixel;

typedef struct image{
    Pixel **pixel;
    int sizeX;
    int sizeY;
}Image;

/*Utils*/
Color getColor(int R,int G,int B);
int CompareColor(Color A, Color B);
void Dispose(Image image);

/*Base Func.*/
void Draw(XImage *ximage,Image imagem, int positionX,int positionY);

/*Formas*/
Image Rectangle(int sizeX,int sizeY,Color color);
Image Line(float x1,float y1,float x2,float y2,Color color);
void doTheHarlemShake(int **buffer,float x1,float y1,float x2,float y2,Color color);
