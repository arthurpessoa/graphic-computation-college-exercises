#ifndef UTIL_H
#define UTIL_H

#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define EventMask (KeyPressMask | ExposureMask)


typedef struct environment_s{
	Display               * display;
	XImage                * ximage;
	Window                window;
	XEvent                an_event;
	GC                    gc;
	Visual                * visual;
	XGCValues             values;
	int                   m, n, screen, dplanes;
	int width, height;
}Environment;

typedef struct coordinates_s{
	float X;
	float Y;
	float Z;
	float W;

}coordinates;


typedef struct rgb_color_s {
  int red,
      green,
      blue;
}rgb_color;

typedef struct hsv_color_s {
    double hue,        
        sat,        
        val;
}hsv_color;

coordinates getCoord(float X, float Y, float Z);
rgb_color getRGB(int R,int G,int B); //Gera uma estrutura cor, a partir de valores da tabela RGB dados na entrada
hsv_color getHSV(int H, int S, int V);
/*funções de conversão*/ 
coordinates SRUToSRD(coordinates SRU,coordinates min, coordinates max, Environment e);
rgb_color HSVToRGB(hsv_color hsv);
int rgb_color_compare(rgb_color a, rgb_color b);


#endif