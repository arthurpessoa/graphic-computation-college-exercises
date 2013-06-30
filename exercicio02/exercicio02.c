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


int main(void) {

  Display               * display;
  XImage                * ximage;
  Window                window;
  XEvent                an_event;
  GC                    gc;
  Visual                * visual;
  XGCValues             values;
  int                   m, n, screen, dplanes;
  int                   width, height, ret = 1;

  width = MAXIMOX;
  height = MAXIMOY;
  
  if ((display = XOpenDisplay(NULL)) == NULL) ret = 0;
  else {  
    screen = DefaultScreen(display);
    dplanes = DisplayPlanes(display,screen);   
    visual = XDefaultVisual(display,screen);
  
    if (!(window=XCreateSimpleWindow(display,RootWindow(display,screen),0,0,width,height,1,BlackPixel(display,screen),WhitePixel(display,screen)))) ret = 0;
    else {
      XSelectInput(display, window, EventMask);
      gc = XCreateGC(display, window, 0, &values);
  
      XMapWindow(display,window);
      XSync(display,False);

      ximage = XCreateImage(display,visual,dplanes,ZPixmap,0,malloc(width*height*sizeof(int)),width,height,8,0);
   
      /*Imagens*/
      Image retinha = Line(260,0,0,240, getColor(255,0,0));
      Image retinha2 = Line(10,0,11,240, getColor(0,255,0));
      Image retinha3 = Line(0,0,260,240, getColor(0,0,255));
      Image retangulozinho = Rectangle(200,200, getColor(255,255,0));

      /*Desenhar*/
      Draw(ximage,retangulozinho,150,100);
      Draw(ximage,retinha,100,100);
      Draw(ximage,retinha2,100,100);
      Draw(ximage,retinha3,100,100);

      /*Free memory*/
      Dispose(retangulozinho);
      Dispose(retinha);
      Dispose(retinha2);
      Dispose(retinha3);

      XPutImage(display,window,gc,ximage,0,0,0,0,width,height);
      
      sleep(50);

      }
    }
  return 0;
}

void Dispose(Image image){
  free(image.pixel);
}

Color getColor(int R,int G,int B){
  Color color;
  color.red=R;
  color.green=G;
  color.blue=B;
  return color;
}


Image Rectangle(int sizeX,int sizeY,Color c){
  Image imagem;
  int i, j;
  imagem.sizeX=sizeX;
  imagem.sizeY=sizeY;

  /*Aloca uma matriz de pixels*/
  imagem.pixel = (Pixel**) malloc(sizeX*sizeof(Pixel*));
    for (i = 0; i < sizeX; i++)
      imagem.pixel[i] = (Pixel*) malloc(sizeY*sizeof(Pixel));

  /*Define que a imagem é vazia, e que os pixels são pretos RGB={0,0,0}*/
    for (i=0; i<sizeX;i++){
      for(j=0;j<sizeY;j++){
        imagem.pixel[i][j].color.red=c.red;
        imagem.pixel[i][j].color.green=c.green;
        imagem.pixel[i][j].color.blue=c.blue;
        imagem.pixel[i][j].printable=1;
      }
    }
  return imagem;
}


Image Line(float x1,float y1,float x2,float y2,Color color){
  Image imagem;
  float m;
  int x,y;
  int **buffer;
  //descobre o tamanho da imagem
  if(x1>x2){
    imagem.sizeX=x1+1;
  }else{
    imagem.sizeX=x2+1;
  }

  if(y1>y2){
    imagem.sizeY=y1+1;
  }else{
    imagem.sizeY=y2+1;
  }

  //aloco a imagem
  imagem.pixel = (Pixel**) malloc(imagem.sizeX*sizeof(Pixel*));
  buffer = (int **)malloc(imagem.sizeX*sizeof(int*));
    for (x = 0; x < imagem.sizeX; x++){
      imagem.pixel[x] = (Pixel*) malloc(imagem.sizeY*sizeof(Pixel));
      buffer[x] = (int*) malloc(imagem.sizeY*sizeof(int));
    }

  //defino que tudo é transparente (não imrprimivel)
  for(x=0;x<imagem.sizeX;x++){
    for(y=0;y<imagem.sizeY;y++){
      imagem.pixel[x][y].printable=0;
      buffer[x][y]=0;      
    }
  }

  doTheHarlemShake(buffer,x1,y1,x2,y2,color);

  for(x=0;x<imagem.sizeX;x++){
    for(y=0;y<imagem.sizeY;y++){
      if(buffer[x][y]==1){
        imagem.pixel[x][y].color.red=color.red;
        imagem.pixel[x][y].color.green=color.green;
        imagem.pixel[x][y].color.blue=color.blue;
        imagem.pixel[x][y].printable=1;
      }      
    }
  }
  return imagem;
}

void doTheHarlemShake(int **buffer,float x1,float y1,float x2,float y2,Color color){
  
  int X1 = (int)x1;
  int Y1 = (int)y1;
  int X2 = (int)x2;
  int Y2 = (int)y2;

  int XM= (X1+ X2)/2;
  int YM= (Y1+ Y2)/2;

  if((X1!=XM && X2!=XM)||(Y1!=YM && Y2!=YM)){
    buffer[XM][YM]=1;
    doTheHarlemShake(buffer,X1,Y1,XM,YM,color);
    doTheHarlemShake(buffer,XM,YM,X2,Y2,color);
  }
}

int CompareColor(Color A, Color B){
    if((A.red!=B.red)||(A.green!=B.green)||(A.blue!=B.blue)){
      return 0;
    }else{
      return 1;
    }
}
void Draw(XImage *ximage,Image imagem, int positionX,int positionY){
  int m,n;  
  for(m=positionY;m<imagem.sizeY+positionY;m++) {
    for(n=positionX;n<imagem.sizeX+positionX;n++) {
      int x = n-positionX;
      int y = m-positionY;
      if(imagem.pixel[x][y].printable){
        ximage -> data[(m*4)*MAXIMOX+n*4] = (char) round(imagem.pixel[x][y].color.blue);
        ximage -> data[(m*4)*MAXIMOX+n*4+1] = (char) round(imagem.pixel[x][y].color.green);
        ximage -> data[(m*4)*MAXIMOX+n*4+2] = (char) round(imagem.pixel[x][y].color.red);
        ximage -> data[(m*4)*MAXIMOX+n*4+3] = (char) 0;
      }
    }
  }
}