/*
  Arthur Pessoa de Souza - RA:380075
  Biblioteca Gráfica baseada em X
  libArthur.h

  Universidade Federal de São Carlos - Campus Sorocaba
  Computação Gráfica
*/

#include <math.h>
#include <stdlib.h>   
#include <X11/Xlib.h> 

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

typedef struct coord{
	float X;
	float Y;
}Coord;

typedef struct windowProperties{
  Display               * display;
  XImage                * ximage;
  Window                window;
  XEvent                an_event;
  GC                    gc;
  Visual                * visual;
  XGCValues             values;
  int                   m, n, screen, dplanes;
  int                   width, height;
}WinProperties;

WinProperties WindowProperties;

/*BÁSICAS*/
void Init();
void Draw(Image imagem, int positionX,int positionY); //Desenha uma imagem dada a posição desejada
void Dispose(Image image); //Limpa a memória alocada para uma imagem
int DisplayWindow(int width,int height, int positionX,int positionY);
void Clear(Color c);
Image CreatePanel(int x,int y);

/*UTEIS*/
Color getColor(int R,int G,int B); //Gera uma estrutura cor, a partir de valores da tabela RGB dados na entrada
Coord SRUToSRD(Coord SRU,Coord min, Coord max); //Converte uma coordenada do SRU para SRD
int CompareColor(Color A, Color B); //Compara duas cores, retornando 1 para caso sejam iguais

/*FORMAS*/
Image Line(float x1,float y1,float x2,float y2,Color color);
