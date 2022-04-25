#include <stdio.h>
#include <stdbool.h>

const int MAX_ALUNOS = 10;
const int MAX_NOME = 50;

typedef struct Aluno {
    int ra;
    char nome[MAX_NOME];
} Aluno;


typedef struct Pilha
{
    Aluno *alunos;
    int *topo;
    int *base;
    int limite;
} Pilha;

void reset(Pilha *pilha){
    pilha->alunos = NULL;
    pilha->topo = NULL;
    pilha->base = NULL;
    pilha->limite = 0;
}

bool empty(Pilha *pilha){
    return pilha->topo == NULL;
}

bool push(Pilha *pilha, Aluno *item){
    if(!full(pilha)){
        pilha->alunos[*pilha->topo] = *item;
        pilha->topo =+ 1;
        return true;
    } else {
        return false;
    }
}

void pop(Pilha *pilha, Aluno *item){
    if (pilha->topo == 0){
        return;
    } else {
        pilha->topo =- 1;
        *item = pilha->alunos[*pilha->topo];
    }
}

void listar(Pilha *pilha){
    printf("\nListando ------\n");

    while (!empty){
        Aluno aluno;
        pop(pilha, &aluno);
        printf("\nRA: %d\nNome: %s", pilha->alunos[*pilha->topo]);
    }
}

void reset(Pilha *pilha){
    
}
