#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Nodo{
  int chave;
  int alturaNodo;
  struct Nodo *nEsq, *nDir;
};

typedef struct Nodo Nodo;

Nodo *adicionar( Nodo *Nodo, int numero);
Nodo *novoNodo(int chave);
Nodo *rotDir( Nodo *Nodo);
Nodo *rotEsq( Nodo *Nodo);
int verificar( Nodo *Nodo);
int alturaNodo( Nodo *Nodo);
int maximo(int a, int b);
int calcularFB( Nodo *Nodo);
void limparArv( Nodo *raiz);
void printar( Nodo *Nodo);
void segundoCenario();
void limparNodo( Nodo *Nodo);

int main(){
   Nodo *raiz = NULL;
  int qtdNodos, numero;

  printf("\n-> Digite a quantidade de nodos para inserir: ");
  scanf("%d", &qtdNodos);

  srand(time(0));
  for (int i = 0; i < qtdNodos; i++){
    numero = rand() % 100;
    raiz = adicionar(raiz, numero);
  }
  printf("\n\n");
  printar(raiz);
  printf("\n");

  limparArv(raiz);
  segundoCenario();

  return 0;
}

 Nodo *adicionar( Nodo *Nodo, int numero){
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

  Nodo->alturaNodo = 1 + maximo(alturaNodo(Nodo->nEsq), alturaNodo(Nodo->nDir));

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

 Nodo *rotDir(Nodo *Nodo){
  struct Nodo *auxEsq = Nodo->nEsq;
  struct Nodo *auxDir = auxEsq->nDir;

  auxEsq->nDir = Nodo;
  Nodo->nEsq = auxDir;
 
  Nodo->alturaNodo = maximo(alturaNodo(Nodo->nEsq), alturaNodo(Nodo->nDir)) + 1;
  auxEsq->alturaNodo = maximo(alturaNodo(auxEsq->nEsq), alturaNodo(auxEsq->nDir)) + 1;

  return auxEsq;
}

 Nodo *rotEsq(Nodo *Nodo){

  struct Nodo *auxDir = Nodo->nDir;
  struct Nodo *auxEsq = auxDir->nEsq;

  auxDir->nEsq = Nodo; 
  Nodo->nDir = auxEsq;

  Nodo->alturaNodo = maximo(alturaNodo(Nodo->nEsq), alturaNodo(Nodo->nDir)) + 1;
  auxDir->alturaNodo = maximo(alturaNodo(auxDir->nEsq), alturaNodo(auxDir->nDir)) + 1;

  return auxDir;
}

int verificar(Nodo *Nodo){
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

int alturaNodo(Nodo *Nodo){
  if (Nodo == NULL){
    return 0;
  }
  return Nodo->alturaNodo;
}

int maximo(int a, int b){
  return (a > b) ? a : b;
}

int calcularFB(Nodo *Nodo){
  if (Nodo == NULL){
    return 0;
  }
  return (alturaNodo(Nodo->nEsq) - alturaNodo(Nodo->nDir));
}

Nodo *novoNodo(int chave){
  Nodo *Nodo = (struct Nodo *)calloc(1, sizeof( Nodo));
  Nodo->chave = chave;
  Nodo->nEsq = NULL;
  Nodo->nDir = NULL;
  Nodo->alturaNodo = 1;
  return Nodo;
}

void printar(Nodo *Nodo){
  if (Nodo != NULL){
    printf("(%d", Nodo->chave);
    printar(Nodo->nEsq);
    printar(Nodo->nDir);
    printf(")");
  }
}

void limparNodo(Nodo *Nodo){
  if (Nodo != NULL){
    limparNodo(Nodo->nEsq);
    limparNodo(Nodo->nDir);
    free(Nodo);
  }
}

void limparArv(Nodo *raiz){
  if (raiz != NULL){
    limparNodo(raiz);
  }
}

void segundoCenario(){
  printf("Primeiro caso: \n");
  Nodo *raiz1 = NULL;

  raiz1 = adicionar(raiz1, 20);
  raiz1 = adicionar(raiz1, 4);
  raiz1 = adicionar(raiz1, 15);
  printar(raiz1);
  limparArv(raiz1);

  printf("\nSegundo caso: \n");
  Nodo *raiz2 = NULL;

  raiz2 = adicionar(raiz2, 20);
  raiz2 = adicionar(raiz2, 4);
  raiz2 = adicionar(raiz2, 26);
  raiz2 = adicionar(raiz2, 3);
  raiz2 = adicionar(raiz2, 9);
  raiz2 = adicionar(raiz2, 15);
  printar(raiz2);
  limparArv(raiz2);

  printf("\nTerceiro caso: \n");
  Nodo *raiz3 = NULL;

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
  printar(raiz3);
  limparArv(raiz3);

  printf("\n\n");
}

