#ifndef POLYGON_H
#define POLYGON_H

#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "image.h"

/*Funções de lista*/
typedef struct node_s {
  coordinates data;
  struct node_s *next;  
} Polygon;

Polygon *polygon_create(coordinates data);
Polygon *polygon_insert_point(Polygon *list, coordinates data);
Polygon *clone_polygon(Polygon *node); 
coordinates polygon_max(Polygon *node);
coordinates polygon_min(Polygon *node);


void floodfill(Environment *e, int x, int y, rgb_color background, rgb_color c);

void dispose_polygon(Polygon *node);
int polygon_to_srd(Polygon *node,Environment e,coordinates min, coordinates max);
int add_polygon(Environment *e, Polygon *node, rgb_color c); //adiciona poligono não preenchido

/*Operações com os poligonos*/
void rotate_polygon(Polygon *node, float ang);
void translate_polygon(Polygon *node, float X, float Y);
void scale_polygon(Polygon *node, float X, float Y);

/*Funções adicionais para as operações*/
typedef struct matrix3_s{
	float m[3][3];
}matrix3; //aqui são as coordenadas homogêneas	

coordinates transform(matrix3 m, coordinates p); //aplica a matriz de transformação em uma determinada coordenada

/*Funções de geração das matrizes de transformação*/
matrix3 rot3(float ang); //rotação
matrix3 trans3(float dx, float dy); //translação
matrix3 scale3(float sx, float sy); //escalonamento

int polygon_foreach(Polygon *node, int(*func)(coordinates));// percorre o polígono enquanto houver vertices
int print_coord(coordinates data); //imprime as coordenadas dos vertices (pra testar)

rgb_color getPositionColor(Environment *e,int x,int y);


#endif