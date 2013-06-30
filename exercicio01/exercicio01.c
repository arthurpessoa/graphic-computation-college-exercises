#include <stdio.h>   
#include <unistd.h> 
#include <X11/Xlib.h>

#define MAX 256


void desenhaReta(Display *display, Window win, GC gc);
int main() {
  Display * display;  
  GC gc; 
  Window win, root_window; 
  unsigned long valuemask = 0;
  XGCValues values;
  XColor cor; 
  int width = MAX, height = MAX, x = 0, y = 0, screennumber, espessura = 4;
  unsigned long white_pixel, black_pixel;
  display = XOpenDisplay(NULL); 
  screennumber = DefaultScreen(display); 
  root_window = RootWindow(display, screennumber); 
  black_pixel = BlackPixel(display,screennumber); 
  white_pixel = WhitePixel(display, screennumber); 
  win = XCreateSimpleWindow(display,root_window,x,y,width,height,espessura,black_pixel,white_pixel);
  XMapWindow(display, win); 
  gc = XCreateGC(display, win, valuemask, &values); 
  XSync(display, False);  
  XSetForeground(display, gc, white_pixel);
  XSetBackground(display, gc, black_pixel); 
  XAllocNamedColor(display, XDefaultColormap(display, screennumber), "red", &cor, &cor);  
  XSetForeground(display, gc, cor.pixel);

  /*------------------------------------------------*/
  float x1,y1,x2,y2;
  float a,b;
  float xa,ya;
  int i,j;

  x1=3.0;
  y1=6.4;
  x2=126.7;
  y2=124.4;
  
  if(x1==x2); //reta vertical, vai dar caca :S
  else{
    a=(y2-y1)/(x2-x1);
    b= y1-a*x1;
  }
  i=x1;
  j=MAX-y1;
  XDrawPoint(display, win, gc, j, i);
  i=x2;
  j=MAX-y2;
  XDrawPoint(display, win, gc, j, i);
  xa=x1++;
  ya=a*xa+b;
  while(ya<y2-1.0){
    i=xa;
    j=MAX-ya;
    XDrawPoint(display, win, gc, j, i);
    ya=a*(++xa)+b;
  }
  /*------------------------------------------------*/
  XFlush(display);
  sleep(30); 
  XFreeGC(display,gc);  
  XCloseDisplay(display); 

  return 0;
}