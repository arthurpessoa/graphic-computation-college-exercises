/*
  Arthur Pessoa de Souza - RA:380075
  Biblioteca Gráfica baseada em X
  libArthur.c

  Universidade Federal de São Carlos - Campus Sorocaba
  Computação Gráfica
*/


#include "libArthur.h"

/*BÁSICAS*/

Image CreatePanel(int x,int y){


  
}








int DisplayWindow(int width,int height, int positionX,int positionY){
  int ret =1;
  WindowProperties.width=width;
  WindowProperties.height=height;

  if ((WindowProperties.display = XOpenDisplay(NULL)) == NULL) ret = 0;
  else {  
    WindowProperties.screen = DefaultScreen(WindowProperties.display);
    WindowProperties.dplanes = DisplayPlanes(WindowProperties.display,WindowProperties.screen);   
    WindowProperties.visual = XDefaultVisual(WindowProperties.display,WindowProperties.screen);
    if (!(WindowProperties.window=XCreateSimpleWindow(WindowProperties.display,RootWindow(WindowProperties.display,WindowProperties.screen),positionX,positionY,width,height,1,BlackPixel(WindowProperties.display,WindowProperties.screen),WhitePixel(WindowProperties.display,WindowProperties.screen)))) ret = 0;
    else{
      XSelectInput(WindowProperties.display, WindowProperties.window, EventMask);
      WindowProperties.gc = XCreateGC(WindowProperties.display, WindowProperties.window, 0, &WindowProperties.values);
      XMapWindow(WindowProperties.display,WindowProperties.window);
      XSync(WindowProperties.display,False);
      WindowProperties.ximage = XCreateImage(WindowProperties.display,WindowProperties.visual,WindowProperties.dplanes,ZPixmap,0,malloc(width*height*sizeof(int)),width,height,8,0);
    }
    return ret;
  }
}

void Clear(Color c){
  int m,n;  
  for(m=0;m<WindowProperties.height;m++) {
    for(n=0;n<WindowProperties.width;n++) {
        WindowProperties.ximage -> data[(m*4)*WindowProperties.width+n*4] = (char)(int)c.blue;
        WindowProperties.ximage -> data[(m*4)*WindowProperties.width+n*4+1] = (char)(int)c.green;
        WindowProperties.ximage -> data[(m*4)*WindowProperties.width+n*4+2] = (char)(int)c.red;
        WindowProperties.ximage -> data[(m*4)*WindowProperties.width+n*4+3] = (char) 0;
    }
  }
}

void Draw(Image imagem, int positionX,int positionY){
  int m,n;  
  for(m=positionY;m<imagem.sizeY+positionY;m++) {
    for(n=positionX;n<imagem.sizeX+positionX;n++) {
      int x = n-positionX;
      int y = m-positionY;
      if(imagem.pixel[x][y].printable){
        WindowProperties.ximage -> data[(m*4)*WindowProperties.width+n*4] = (char)(int)(imagem.pixel[x][y].color.blue);
        WindowProperties.ximage -> data[(m*4)*WindowProperties.width+n*4+1] = (char)(int)(imagem.pixel[x][y].color.green);
        WindowProperties.ximage -> data[(m*4)*WindowProperties.width+n*4+2] = (char)(int)(imagem.pixel[x][y].color.red);
        WindowProperties.ximage -> data[(m*4)*WindowProperties.width+n*4+3] = (char) 0;
      }
    }
  }
  XPutImage(WindowProperties.display,WindowProperties.window,WindowProperties.gc,WindowProperties.ximage,0,0,0,0,WindowProperties.width,WindowProperties.height);
}

void Dispose(Image image){
  free(image.pixel);
}


/*UTEIS*/


Coord SRUToSRD(Coord SRU,Coord min, Coord max){
  Coord nc; //coordenadas normalizadas
  Coord dc; //coordenadas do dispositivo

  /*A transformação de coordenadas do usuário (x,y) 
  para coordenadas normalizadas, denominada transformação de visualização*/
  nc.X = (SRU.X-min.X)/(max.X-min.X);
  nc.Y = (SRU.Y-min.Y)/(max.Y-min.Y);

  /*O mapeamento de coordenadas normalizadas (reais) para coordenadas do
  dispositivo gráfico de saída (inteiras) é uma transformação linear e pode ser considerada como*/
  dc.X=round(nc.X*(WindowProperties.width-1));
  dc.Y=round(nc.Y*(WindowProperties.height-1));
  
  return dc;
}


Color getColor(int R,int G,int B){
  Color color;
  color.red=R;
  color.green=G;
  color.blue=B;
  return color;
}

int CompareColor(Color A, Color B){
  if((A.red!=B.red)||(A.green!=B.green)||(A.blue!=B.blue)){
    return 0;
  }else{
    return 1;
  }
}


/*FORMAS*/

/*Desenhar Reta*/
//função auxiliar para desenhar a reta, chamada recursivamente
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
//função principal para desenhar a reta
Image Line(float x1,float y1,float x2,float y2,Color color){
  Image imagem;
  float m;
  int x,y;
  int **buffer;  
  if(x1>x2){//descobre o tamanho da imagem
    imagem.sizeX=x1+1;
  }else{
    imagem.sizeX=x2+1;
  }
  if(y1>y2){
    imagem.sizeY=y1+1;
  }else{
    imagem.sizeY=y2+1;
  }
  imagem.pixel = (Pixel**) malloc(imagem.sizeX*sizeof(Pixel*));//aloco a imagem
  buffer = (int **)malloc(imagem.sizeX*sizeof(int*));
  for (x = 0; x < imagem.sizeX; x++){
    imagem.pixel[x] = (Pixel*) malloc(imagem.sizeY*sizeof(Pixel));
    buffer[x] = (int*) malloc(imagem.sizeY*sizeof(int));
  }
  for(x=0;x<imagem.sizeX;x++){ //defino que tudo é transparente (não imrprimivel)
    for(y=0;y<imagem.sizeY;y++){
      imagem.pixel[x][y].printable=0;
      buffer[x][y]=0;      
    }
  }
  doTheHarlemShake(buffer,x1,y1,x2,y2,color); //função auxiliar para marcar os pontos em que irão passar a reta
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
  free(buffer);
  return imagem;
}
