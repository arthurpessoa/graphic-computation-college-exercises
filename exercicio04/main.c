/*
  Arthur Pessoa de Souza - RA:380075
  Biblioteca Gráfica baseada em X
  main.c

  Universidade Federal de São Carlos - Campus Sorocaba
  Computação Gráfica
*/

#include <stdio.h>
#include "polygon.h"
void A();
void B();
void C();

int main() {
	A();
	return 0;
}

/* Exercício A */
void A(){
	Environment e;
	e.width=640; //tamanho dajanela
	e.height=480;

	if(init(&e)){

		
		Polygon *Face1; // Face1		
		Face1=polygon_create(getCoord(10, 10, 0)); //insere a coordenada inicial do polígono 1
		Face1=polygon_insert_point(Face1, getCoord(10, 0, 15); //insere os demais pontos na estrutura polygon
		Face1=polygon_insert_point(Face1, getCoord(10, -10, 0);
		
		Polygon *Face2; // Face2	
		Face2=polygon_create(getCoord(10, 10, 0)); //insere a coordenada inicial do polígono 1
		Face2=polygon_insert_point(Face2, getCoord(10, 0, 15); //insere os demais pontos na estrutura polygon
		Face2=polygon_insert_point(Face2, getCoord(10, -10, 0);

		Polygon *Face3; // Face3		
		Face3=polygon_create(getCoord(10, 10, 0)); //insere a coordenada inicial do polígono 1
		Face3=polygon_insert_point(Face3, getCoord(10, 0, 15); //insere os demais pontos na estrutura polygon
		Face3=polygon_insert_point(Face3, getCoord(10, -10, 0);


		//Viewpoint sobre Z -> N = (0, 0, -1)
		//View-Up -> V = (0, 1, 0)

		coordinates N = getCoord(0, 0, -1);
		coordinates V = getCoord(0, 1, 0);
		
		dispose_polygon(Face1);
		dispose_polygon(Face2);
		dispose_polygon(Face3);

		draw(&e);//exibo a minha view-port
		sleep(2);
	}
}

