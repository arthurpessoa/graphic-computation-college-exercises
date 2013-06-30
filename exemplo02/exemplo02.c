#include <stdio.h>

#define MAX 30

int main(){
	float x1,y1,x2,y2;
	float a,b;
	float x,y;
	int i,j;


	char imagem[MAX][MAX];

	x1=3.0;
	y1=6.4;
	x2=26.7;
	y2=24.4;


	if(x1==x2)return -1; //reta vertical, vai dar caca :S
	else{
		a=(y2-y1)/(x2-x1);
		b= y1-a*x1;
	}
	for(j=0;j<MAX;j++){
		for (i = 0; i < MAX; i++){	
			imagem[j][i]=' ';
		}
	}
	i=x1;
	j=MAX-y1;
	imagem[j][i]='*';
	i=x2;
	j=MAX-y2;
	imagem[j][i]='*';
	x=x1++;
	y=a*x+b;
	while(y<y2-1.0){
		i=x;
		j=MAX-y;
		imagem[j][i]='*';
		y=a*(++x)+b;
	}
	for (j = 0; j < MAX; j++){
		for(i=0;i<MAX;i++){
			printf("%c",imagem[j][i]);
		}
		printf("\n");
	}
	return 0;
}