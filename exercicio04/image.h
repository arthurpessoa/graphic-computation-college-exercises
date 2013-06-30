/*
  Arthur Pessoa de Souza - RA:380075
  Biblioteca Gráfica baseada em X

  Universidade Federal de São Carlos - Campus Sorocaba
  Computação Gráfica

  image.h
  Desc: Essa biblioteca é a responsável por abstrair as operações do X em camadas mais altas
  e humanamente entendíveis
*/


#ifndef IMAGE_H
#define IMAGE_H

#include "util.h" 
#include <stdlib.h>
#include <stdio.h>

int init(Environment *e);
int draw(Environment *e);
int clear(Environment *e, rgb_color c);

/*Elementos básicos*/
void draw_point(Environment *e,float X,float Y,rgb_color c); //ponto
void line(Environment *e, float x1,float y1,float x2,float y2, rgb_color c);

rgb_color getPositionColor(Environment *e,int x,int y);

#endif
