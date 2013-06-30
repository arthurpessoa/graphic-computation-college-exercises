/*
  Arthur Pessoa de Souza - RA:380075
  Biblioteca Gráfica baseada em X
  main.c

  Universidade Federal de São Carlos - Campus Sorocaba
  Computação Gráfica

  R: O dispositivo é de saída é Matricial, e não, não é adequado, porém pode ser mapeado de forma que 
  o SRU seja completamente mapeado para o Dispositivo.
*/

#include "libArthur.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct poligon{
  Coord *Vertices;
  int nVertices;
  Color cor;
}Poligon;

int main() {

    /*Limites do SRU (fora da tela)*/ 
    Coord min;
    Coord max;
    
    min.X=-20;
    min.Y=-20;
    max.X=10;
    max.Y=15;

    /*Ler os valores em SRU*/

    int qtpoligonos=2;

    Poligon *Poligono = (Poligon*)malloc(qtpoligonos*sizeof(Poligon));
    int i,j;
    
    /*POLIGONO 1*/ 
    Poligono[0].nVertices=4;
    Poligono[0].Vertices = (Coord*)malloc(Poligono[0].nVertices*sizeof(Coord));
    Poligono[0].cor=getColor(0,0,255); //AZUL
    Poligono[0].Vertices[0].X=-6; //Vertice 1
    Poligono[0].Vertices[0].Y=-2;

    Poligono[0].Vertices[1].X=-1; //Vertice 2
    Poligono[0].Vertices[1].Y=-2;

    Poligono[0].Vertices[2].X=-1; //Vertice 3
    Poligono[0].Vertices[2].Y=-6;

    Poligono[0].Vertices[3].X=-6; //Vertice 4
    Poligono[0].Vertices[3].Y=-6;

    /*POLIGONO 2*/
    Poligono[1].nVertices=4;
    Poligono[1].Vertices = (Coord*)malloc(Poligono[0].nVertices*sizeof(Coord));
    Poligono[1].cor=getColor(255,0,0); //VERMELHO
    Poligono[1].Vertices[0].X=-7; //Vertice 1
    Poligono[1].Vertices[0].Y=-3;

    Poligono[1].Vertices[1].X=-4; //Vertice 2
    Poligono[1].Vertices[1].Y=-4;

    Poligono[1].Vertices[2].X=-3; //Vertice 3
    Poligono[1].Vertices[2].Y=-6;

    Poligono[1].Vertices[3].X=-6; //Vertice 4
    Poligono[1].Vertices[3].Y=-9;

    Poligono[1].Vertices[4].X=-9; //Vertice 5
    Poligono[1].Vertices[4].Y=-8;

    /*Exibe na tela*/
    if(DisplayWindow(640,480,0,0)){ //cria uma nova janela de tamanho 640x480
      Clear(getColor(0,0,0)); //limpa a tela pra preto
      Image aresta;
      for(i=0;i<qtpoligonos;i++){
        for(j=1;j<=Poligono[i].nVertices;j++){
          if(Poligono[i].nVertices>1){
            float x1=Poligono[i].Vertices[(j-1)%Poligono[i].nVertices].X;
            float y1=Poligono[i].Vertices[(j-1)%Poligono[i].nVertices].Y;
            float x2=Poligono[i].Vertices[(j)%Poligono[i].nVertices].X;
            float y2=Poligono[i].Vertices[(j)%Poligono[i].nVertices].Y;

            //Converter os pontos em SRU para SRD
            Coord CU1; //Coordenadas no Sistema do Universo
            CU1.X=x1;
            CU1.Y=y1;

            Coord CU2;
            CU2.X=x2;
            CU2.Y=y2;

            Coord CD1; //Coordenadas no Dispositivo
            Coord CD2;
            CD1 = SRUToSRD(CU1,min, max);
            CD2 = SRUToSRD(CU2,min, max);

            aresta = Line(CD1.X,CD1.Y,CD2.X,CD2.Y, Poligono[i].cor); 

            Coord CU3;
            CU3.X=-8;
            CU3.Y=-7;
            Coord viewport;

            //Alinha a visão em relação ao viewport
            viewport = SRUToSRD(CU3,min, max);
            Draw(aresta,-viewport.X,viewport.Y);
          }
        }
      }
      sleep(100);   
      Dispose(aresta);  

    }
    return 0;    
}