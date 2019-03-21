#include "geometry.h"
#include <math.h>

int verify(point p, point a, point b) {
  //Inicializando as variaveis double para tornar possivel as operacoes e organizar melhor o codigo.
  double t, g, comp, ymax, xmax, ymin, xmin, ax, bx, ay, by, px, py, xlim, m;
  ax = a.x;
  ay = a.y;
  bx = b.x;
  by = b.y;
  px = p.x;
  py = p.y;

  //Estabelecendo valores maximos e minimos para os pontos que limitam o segmento.
  if (ay > by) {
    ymax = ay;
    ymin = by;
  } else {
    ymax = by;
    ymin = ay;
  }

  if (ax > bx) {
    xmax = ax;
    xmin = bx;
  } else {
    xmax = bx;
    xmin = ax;
  }

  /*Algoritmo que usa a equacao da reta dado por (y-y0) = m(x-x0), sendo o lado direito 
  representado pela variavel t, e o lado esquerdo pela variavel g. Substituindo os valores
  dos pontos do segmento para descobrir a equacao da reta e substituindo as cordenados do
  ponto p na mesma equacao podemos constatar que o ponto p esta no segmento da reta, caso 
  o lado esquerdo seja igual ao lado direito e ele esteja entre os limites de x e y. Para
  casos em que o coeficiente angular tende ao infinito (reta vertical) testa-se se o valor 
  de x do ponto possui mesmo valor de x da reta e limita o tamanho do segmento.*/
  m = ((ay - by) / (ax - bx));
  t = m * (px - bx);
  g = py - by;

  if (ax != bx) {
    comp = fabs(t - g);
    if (comp < 0.000001 && px <= xmax && px >= xmin && py <= ymax && py >= ymin) {
      return 2;
    }
  } else if (px == bx && py <= ymax && py >= ymin && ax == bx) {
    return 2;
  }

  /*Usando a mesma equacao porem de forma a descobrir o x da equacao da reta
  dado o valor de y do ponto p, o algoritmo testa se o ponto p esta antes ou depois da reta 
  realizando o raycasting horizontal, levando em conta a perturbacao na limitacao de ymax e ymin.*/
  xlim = -(m * (-bx) - py + by) / m;

  if (py <= ymax && py > ymin && px <= xlim) {
    return 1;
  } else if (py <= ymax && py > ymin && ax == bx && px < ax) {
    return 1;
  } else {
    return 0;
  }
}

/*Algoritmo roda um for com o tamanho n de vertices na figura e chama a funcao verify do ponto de indice 
  i com o ponto de indice i+1 ate chegar no ultimo ponto para voltar a i=0, fechando a figura. Se a funcao retornar
  2 significa que o ponto ja esta dentro, porem caso a funcao retorne 1 soma-se +1 ao contador soma e depois caso esse
  contador seja impar o ponto esta dentro da figura e caso seja par esta fora */
int inside(point p, point poly[], int n) {
  int checa, soma;

  soma = 0;
  for (int i = 0; i < n; i++) {
    if (i == n - 1) {
      checa = verify(p, poly[i], poly[0]);
    } else {
      checa = verify(p, poly[i], poly[i + 1]);
    }
    if (checa == 2) {
      return 1;
    }
    if (checa == 1) {
      soma++;
    }
  }

  if (soma % 2 != 0) {
    return 1;
  } else {
    return 0;
  }
}
