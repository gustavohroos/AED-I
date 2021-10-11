#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Nodo{
  int chave;
  int alturaSub;
  struct Nodo *nEsq;
  struct Nodo *nDir;
};

// typedef struct Nodo Nodo;

struct Nodo *adicionar(struct Nodo *Nodo, int numero);
struct Nodo *novoNodo(int chave);
struct Nodo *rotDir(struct Nodo *Nodo);
struct Nodo *rotEsq(struct Nodo *Nodo);
int verificar(struct Nodo *Nodo);
int alturaSub(struct Nodo *Nodo);
int maximo(int a, int b);
int calcularFB(struct Nodo *Nodo);
void limparArv(struct Nodo *raiz);
void printArv(struct Nodo *Nodo);
void segundoCenario();
void limparNodo(struct Nodo *Nodo);

int main(){
  struct Nodo *raiz = NULL;
  int qtdNodos, numero;

  printf("\n-> Digite a quantidade de nodos para inserir: ");
  scanf("%d", &qtdNodos);

  srand(time(0));
  for (int i = 0; i < qtdNodos; i++){
    numero = rand() % 100;
    raiz = adicionar(raiz, numero);
  }
  printf("\n\n");
  printArv(raiz);
  printf("\n");

  limparArv(raiz);
  segundoCenario();

  return 0;
}

struct Nodo *adicionar(struct Nodo *Nodo, int numero){
  int fb;

  if (Nodo == NULL){
    return novoNodo(numero);
  }

  if (numero < Nodo->chave){
    Nodo->nEsq = adicionar(Nodo->nEsq, numero);
  }
  else{
    Nodo->nDir = adicionar(Nodo->nDir, numero);
  }

  Nodo->alturaSub = 1 + maximo(alturaSub(Nodo->nEsq), alturaSub(Nodo->nDir));

  fb = calcularFB(Nodo);

  if (fb > 1 && numero < Nodo->nEsq->chave){
    return rotDir(Nodo);
  }
  if (fb < -1 && numero > Nodo->nDir->chave){
    return rotEsq(Nodo);
  }
  if (fb > 1 && numero > Nodo->nEsq->chave){
    Nodo->nEsq = rotEsq(Nodo->nEsq);
    return rotDir(Nodo);
  }
  if (fb < -1 && numero < Nodo->nDir->chave){
    Nodo->nDir = rotDir(Nodo->nDir);
    return rotEsq(Nodo);
  }

  return Nodo;
}

struct Nodo *rotDir(struct Nodo *Nodo){
  struct Nodo *auxLeft = Nodo->nEsq;
  struct Nodo *auxDir = auxLeft->nDir;

  auxLeft->nDir = Nodo;
  Nodo->nEsq = auxDir;
 
  Nodo->alturaSub = maximo(alturaSub(Nodo->nEsq), alturaSub(Nodo->nDir)) + 1;
  auxLeft->alturaSub = maximo(alturaSub(auxLeft->nEsq), alturaSub(auxLeft->nDir)) + 1;

  return auxLeft;
}

struct Nodo *rotEsq(struct Nodo *Nodo){
  struct Nodo *auxDir = Nodo->nDir;
  struct Nodo *auxLeft = auxDir->nEsq;

  auxDir->nEsq = Nodo; 
  Nodo->nDir = auxLeft;

  Nodo->alturaSub = maximo(alturaSub(Nodo->nEsq), alturaSub(Nodo->nDir)) + 1;
  auxDir->alturaSub = maximo(alturaSub(auxDir->nEsq), alturaSub(auxDir->nDir)) + 1;

  return auxDir;
}

int verificar(struct Nodo *Nodo){
  int fb;

  if (Nodo == NULL){
    return 1;
  }
  if (!verificar(Nodo->nEsq)){
    return 0;
  }
  if (!verificar(Nodo->nDir)){
    return 0;
  }
  fb = calcularFB(Nodo);
  if ((fb > 1) || (fb < -1)){
    return 0;
  }
  else{
    return 1;
  }
}

int alturaSub(struct Nodo *Nodo){
  if (Nodo == NULL){
    return 0;
  }
  return Nodo->alturaSub;
}

int maximo(int a, int b){
  return (a > b) ? a : b;
}

int calcularFB(struct Nodo *Nodo){
  if (Nodo == NULL){
    return 0;
  }
  return (alturaSub(Nodo->nEsq) - alturaSub(Nodo->nDir));
}

struct Nodo *novoNodo(int chave){
  struct Nodo *Nodo = (struct Nodo *)calloc(1, sizeof(struct Nodo));
  Nodo->chave = chave;
  Nodo->nEsq = NULL;
  Nodo->nDir = NULL;
  Nodo->alturaSub = 1;
  return Nodo;
}

void printArv(struct Nodo *Nodo){
  if (Nodo != NULL){
    printf("(%d", Nodo->chave);
    printArv(Nodo->nEsq);
    printArv(Nodo->nDir);
    printf(")");
  }
}

void limparNodo(struct Nodo *Nodo){
  if (Nodo != NULL){
    limparNodo(Nodo->nEsq);
    limparNodo(Nodo->nDir);
    free(Nodo);
  }
}

void limparArv(struct Nodo *raiz){
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
  printArv(raiz1);
  limparArv(raiz1);

  printf("\nSegundo caso: \n");
  struct Nodo *raiz2 = NULL;

  raiz2 = adicionar(raiz2, 20);
  raiz2 = adicionar(raiz2, 4);
  raiz2 = adicionar(raiz2, 26);
  raiz2 = adicionar(raiz2, 3);
  raiz2 = adicionar(raiz2, 9);
  raiz2 = adicionar(raiz2, 15);
  printArv(raiz2);
  limparArv(raiz2);

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
  printArv(raiz3);
  limparArv(raiz3);

  printf("\n\n");
}

