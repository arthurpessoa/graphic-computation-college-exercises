#include "image.h"

/*Função draw*/
int draw(Environment *e){
  XPutImage(e->display,e->window,e->gc,e->ximage,0,0,0,0,e->width,e->height);
  return 1;
}

/*Função init*/
int init(Environment *e) {
  if ((e->display = XOpenDisplay(NULL)) == NULL)return 0;
  else {  
    e->screen = DefaultScreen(e->display);
    e->dplanes = DisplayPlanes(e->display,e->screen);   
    e->visual = XDefaultVisual(e->display,e->screen);
  
    if (!(e->window=XCreateSimpleWindow(e->display,RootWindow(e->display,e->screen),0,0,e->width,e->height,1,BlackPixel(e->display,e->screen),WhitePixel(e->display,e->screen)))) return 0;
    else {
      XSelectInput(e->display, e->window, EventMask);
      e->gc = XCreateGC(e->display, e->window, 0, &e->values);
  
      XMapWindow(e->display,e->window);
      XSync(e->display,False);
      e->ximage = XCreateImage(e->display,e->visual,e->dplanes,ZPixmap,0,malloc(e->width*e->height*sizeof(int)),e->width,e->height,8,0) ;
      return 1;
      }
    }
  }

int clear(Environment *e, rgb_color c){
  int x,y;
  for(x=0;x<=e->width;x++){
      for(y=0;y<=e->height;y++){
        draw_point(e,x,y,c);
      }
  }
}

/*Função draw_point*/
void draw_point(Environment *e,float X,float Y,rgb_color c){
   if((Y<=e->height&&X<=e->width)&&(Y>0&&X>0))
    {
      e->ximage -> data[((int)Y*4)*e->width+(int)X*4] = (char) c.blue;
      e->ximage -> data[((int)Y*4)*e->width+(int)X*4+1] = (char) c.green;
      e->ximage -> data[((int)Y*4)*e->width+(int)X*4+2] = (char) c.red;
      e->ximage -> data[((int)Y*4)*e->width+(int)X*4+3] = (char) 0;
    }
}

void line(Environment *e,float x1,float y1,float x2,float y2, rgb_color c){
  int X1 = (int)x1;
  int Y1 = (int)y1;
  int X2 = (int)x2;
  int Y2 = (int)y2;

  int XM= (X1+ X2)/2;
  int YM= (Y1+ Y2)/2;
  if((X1!=XM && X2!=XM)||(Y1!=YM && Y2!=YM)){

    draw_point(e,XM,YM,c);
    draw_point(e,X1,Y1,c);
    draw_point(e,X2,Y2,c);

    line(e,X1,Y1,XM,YM,c);
    line(e,XM,YM,X2,Y2,c);
  }
}
