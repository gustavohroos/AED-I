#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Nodo *adicionar(struct Nodo *Nodo, int numero);
struct Nodo *rotDir(struct Nodo *Nodo);
struct Nodo *rotEsq(struct Nodo *Nodo);
struct Nodo *novoNodo(int chave);
void printarArvore(struct Nodo *Nodo);
int maximo(int a, int b);
int altura(struct Nodo *Nodo);
int getFB(struct Nodo *Nodo);
int verificar(struct Nodo *Nodo);
void limparNodo(struct Nodo *Nodo);
void limparArvore(struct Nodo *raiz);
void segundoCenario();

struct Nodo{
  int chave;
  struct Nodo *nodoEsq;
  struct Nodo *nodoDir;
  int altura;
};

struct Nodo *adicionar(struct Nodo *Nodo, int numero){
  int fb;

  if (Nodo == NULL){
    return novoNodo(numero);
  }

  if (numero < Nodo->chave){
    Nodo->nodoEsq = adicionar(Nodo->nodoEsq, numero);
  }
  else{
    Nodo->nodoDir = adicionar(Nodo->nodoDir, numero);
  }

  Nodo->altura = 1 + maximo(altura(Nodo->nodoEsq), altura(Nodo->nodoDir));

  fb = getFB(Nodo);

  if (fb > 1 && numero < Nodo->nodoEsq->chave){
    return rotDir(Nodo);
  }
  if (fb < -1 && numero > Nodo->nodoDir->chave){
    return rotEsq(Nodo);
  }
  if (fb > 1 && numero > Nodo->nodoEsq->chave){
    Nodo->nodoEsq = rotEsq(Nodo->nodoEsq);
    return rotDir(Nodo);
  }
  if (fb < -1 && numero < Nodo->nodoDir->chave){
    Nodo->nodoDir = rotDir(Nodo->nodoDir);
    return rotEsq(Nodo);
  }

  return Nodo;
}

struct Nodo *rotDir(struct Nodo *Nodo){
  struct Nodo *auxLeft = Nodo->nodoEsq;
  struct Nodo *auxDir = auxLeft->nodoDir;

  auxLeft->nodoDir = Nodo;
  Nodo->nodoEsq = auxDir;
 
  Nodo->altura = maximo(altura(Nodo->nodoEsq), altura(Nodo->nodoDir)) + 1;
  auxLeft->altura = maximo(altura(auxLeft->nodoEsq), altura(auxLeft->nodoDir)) + 1;

  return auxLeft;
}

struct Nodo *rotEsq(struct Nodo *Nodo){
  struct Nodo *auxDir = Nodo->nodoDir;
  struct Nodo *auxLeft = auxDir->nodoEsq;

  auxDir->nodoEsq = Nodo; 
  Nodo->nodoDir = auxLeft;

  Nodo->altura = maximo(altura(Nodo->nodoEsq), altura(Nodo->nodoDir)) + 1;
  auxDir->altura = maximo(altura(auxDir->nodoEsq), altura(auxDir->nodoDir)) + 1;

  return auxDir;
}

int verificar(struct Nodo *Nodo){
  int fb;

  if (Nodo == NULL){
    return 1;
  }
  if (!verificar(Nodo->nodoEsq)){
    return 0;
  }
  if (!verificar(Nodo->nodoDir)){
    return 0;
  }
  fb = getFB(Nodo);
  if ((fb > 1) || (fb < -1)){
    return 0;
  }
  else{
    return 1;
  }
}

int altura(struct Nodo *Nodo){
  if (Nodo == NULL){
    return 0;
  }
  return Nodo->altura;
}

int maximo(int a, int b){
  return (a > b) ? a : b;
}

int getFB(struct Nodo *Nodo){
  if (Nodo == NULL){
    return 0;
  }
  return (altura(Nodo->nodoEsq) - altura(Nodo->nodoDir));
}

struct Nodo *novoNodo(int chave){
  struct Nodo *Nodo = (struct Nodo *)calloc(1, sizeof(struct Nodo));
  Nodo->chave = chave;
  Nodo->nodoEsq = NULL;
  Nodo->nodoDir = NULL;
  Nodo->altura = 1;
  return Nodo;
}

void printarArvore(struct Nodo *Nodo){
  if (Nodo != NULL){
    printf("(%d", Nodo->chave);
    printarArvore(Nodo->nodoEsq);
    printarArvore(Nodo->nodoDir);
    printf(")");
  }
}

void limparNodo(struct Nodo *Nodo){
  if (Nodo != NULL){
    limparNodo(Nodo->nodoEsq);
    limparNodo(Nodo->nodoDir);
    free(Nodo);
  }
}

void limparArvore(struct Nodo *raiz){
  if (raiz != NULL){
    limparNodo(raiz);
  }
}

void segundoCenario(){
  printf("Primeiro caso: \n");
  struct Nodo *raiz1 = NULL;

  raiz1 = adicionar(raiz1, 20);
  raiz1 = adicionar(raiz1, 4);
  raiz1 = adicionar(raiz1, 15);
  printarArvore(raiz1);
  limparArvore(raiz1);

  printf("\nSegundo caso: \n");
  struct Nodo *raiz2 = NULL;

  raiz2 = adicionar(raiz2, 20);
  raiz2 = adicionar(raiz2, 4);
  raiz2 = adicionar(raiz2, 26);
  raiz2 = adicionar(raiz2, 3);
  raiz2 = adicionar(raiz2, 9);
  raiz2 = adicionar(raiz2, 15);
  printarArvore(raiz2);
  limparArvore(raiz2);

  printf("\nTerceiro caso: \n");
  struct Nodo *raiz3 = NULL;

  raiz3 = adicionar(raiz3, 20);
  raiz3 = adicionar(raiz3, 4);
  raiz3 = adicionar(raiz3, 26);
  raiz3 = adicionar(raiz3, 3);
  raiz3 = adicionar(raiz3, 9);
  raiz3 = adicionar(raiz3, 21);
  raiz3 = adicionar(raiz3, 30);
  raiz3 = adicionar(raiz3, 2);
  raiz3 = adicionar(raiz3, 7);
  raiz3 = adicionar(raiz3, 11);
  raiz3 = adicionar(raiz3, 15);
  printarArvore(raiz3);
  limparArvore(raiz3);

  printf("\n\n");
}

int main(){
  struct Nodo *raiz = NULL;
  int quantidade, numero;

  printf("\nDigite a quantidade de nodos para inserir: ");
  scanf("%d", &quantidade);

  srand(time(0));
  for (int i = 0; i < quantidade; i++){
    numero = rand() % 100;
    raiz = adicionar(raiz, numero);
  }
  printf("\n\n");
  printarArvore(raiz);
  printf("\n");

  if (verificar(raiz) == 0){
    printf("Não ");
  }
  printf("OK\n\n");

  limparArvore(raiz);
  segundoCenario();

  return 0;
}