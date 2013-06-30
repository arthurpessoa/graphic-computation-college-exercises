

/* 
   Programa exemplo para trabalhar com uma janela no ambiente X-Window
   Curso de Computa??o Gr?fica, Bacharelado em Ci?ncia da Computa??o - UFSCar campus Sorocaba
   Prof. Murillo Rodrigo Petrucelli Homem

   Observa??o: a implementa??o de um programa que utiliza a biblioteca X ? bem complexa. Este roteiro
   tem como objetivo apresentar apenas o necess?rio para abrir uma janela gr?fica para a implementa??o
   de alguns algoritmos vistos em sala de aula e dessa forma muitos detalhes ser?o negligenciados.

   Para compilar este programa, digite em um shell (Linux) a seguinte linha de comando:
   gcc roteiro_janela_x.c -o roteiro_janela_x -lX11

   Para executar o programa digite: ./roteiro_janela_x
*/


#include <stdio.h>    /* Biblioteca padr?o das fun??es de entrada e sa?da da linguagem C. */
#include <unistd.h>   /* Para o uso de fun??es como sleep() etc ... */
#include <X11/Xlib.h> /* Arquivo de cabe?alho da biblioteca que implementa as fun??es de baixo n?vel 
                         para acesso ao servidor X. */

int main(void) {
  /* 
     O sistema X-Window pode suportar in?meros "displays" conectados a um ?nico computador.
     Um "display" ? usado para fazer refer?ncia a uma cole??o de monitores que compartilham 
     um teclado e um mouse. Em outras palavras, pode haver in?meros monitores para cada "display". 
     Uma "screen" ? um monitor (hardware).
  */

  /* 
     Cada servidor X tem um nome para o display na forma: hostname:displaynumber.screennumber.
     Esta informa??o ? armazenada em uma estrutura do tipo Display.
     O "hostname" especifica o nome da m?quina na qual o display est? fisicamente conectado.
     O "displaynumber" ? usado para fazer refer?ncia a cole??o de monitores que compartilham um 
     teclado e um mouse. O "screennumber" ? utilizado para referenciar um monitor espec?fico.
     Em sistemas POSIX, o nome do display padr?o ? armazenado na vari?vel de ambiente DISPLAY 
     do sistema operacional. Experimente digitar em um shell: echo $DISPLAY
  */
  Display * display;  

   /* 
     Contexto Gr?fico: define um conjunto de atributos (cor do fundo, como as linhas ser?o 
     desenhadas etc) que ser?o utilizados pelas in?meras fun??es de desenho do ambiente X.
     Quando declaramos uma vari?vel deste tipo, assumimos um conjunto de atributos default, 
     mas eles podem ser alterados pelo programador atrav?s de fun??es espec?ficas.
   */ 
  GC gc;  

  Window win, root_window; /* Ponteiros para as janelas criadas. */

  unsigned long valuemask = 0; /* Vari?vel necess?ria para a fun??o XCreateGC() para criar 
                                  um contexto gr?fico. */
  XGCValues values;  /* Estrutura que cont?m os valores iniciais do GC. */
  XColor cor;        /* XColor ? uma estrutura que cont?m informa??es sobre uma cor 
                        associada a um pixel. */

  /* Vari?veis utilizadas neste programa exemplo. */
  int width = 256, height = 256, x = 0, y = 0, screennumber, espessura = 4;
 
  unsigned long white_pixel, black_pixel;

   /* 
     Abre uma conex?o para o display passado como argumento para a fun??o. Se o argumento NULL 
     ? passado, ? assumido o display padr?o armazenado na vari?vel de ambiente DISPLAY do SO. 
   */
  display = XOpenDisplay(NULL); 

  /* Retorna o n?mero do screen referenciado pela fun??o XOpenDisplay(). */
  screennumber = DefaultScreen(display); 

  /* Determina o identificador da janela raiz do monitor. Esta janela sempre existir?. */
  root_window = RootWindow(display, screennumber); 
  
  /* Valor dos pixels da borda. */
  black_pixel = BlackPixel(display,screennumber);  
  
  /* Valor dos pixels no interior (fundo) da janela. */
  white_pixel = WhitePixel(display, screennumber); 

  /* Cria uma janela. */
  win = XCreateSimpleWindow(display,root_window,x,y,width,height,espessura,black_pixel,white_pixel);
  
  /*
     O fato de criar a janela n?o significa que ela vai aparecer na tela. Para isso, usamos
     a XMapWindow() para que a janela seja exibida na tela.
  */    
  XMapWindow(display, win); 
  
  /* Cria o contexto gr?fico para nossa aplica??o. */
  gc = XCreateGC(display, win, valuemask, &values); 
 
  /* Atua praticamente da mesma forma que a XFlush(). */
  XSync(display, False);  
  
  /* Altera a cor da janela associada ao contexto gr?fico gc. */ 
  XSetForeground(display, gc, white_pixel);

  /* Altera a cor de fundo da janela associada ao contexto gr?fico. */
  XSetBackground(display, gc, black_pixel); 
 
  /* Aloca na vari?vel "cor" as informa??es sobre a cor vermelha. */
  XAllocNamedColor(display, XDefaultColormap(display, screennumber), "red", &cor, &cor);  
   
  /* Altera no contexto gr?fico a cor que ser? usada para desenhar um pixel. */
  XSetForeground(display, gc, cor.pixel);

  /* Desenha um pixel nas coordenadas (15,15) com a cor definida pela fun??o anterior. */
  XDrawPoint(display, win, gc, 15, 15);

  /* Faz com que o X execute todas as requisi??es pendentes. */
  XFlush(display);

  /* Espera por alguns segundos ... */
  sleep(30); 

  /* Libera o GC. */
  XFreeGC(display,gc);  

  /* Encerra a sess?o com o servidor X. */
  XCloseDisplay(display); 

  return 0;
  }

