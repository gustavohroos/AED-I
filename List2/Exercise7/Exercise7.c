#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PESSOAS_MAX 10
#define NOME_MAX 30
#define TELEFONE_MAX 30

int menu(void *pBuffer);
void adicionar(void *pBuffer);
void *remover(void *pBuffer);
void listar(void *pBuffer);
void *buscar(void *pBuffer);

typedef struct
{
    char nome[NOME_MAX];
    char telefone[TELEFONE_MAX];
    int idade;
} Pessoa;

Pessoa maximo[PESSOAS_MAX] = {};
 
int main(){

    void *pBuffer;

    pBuffer = (void *)calloc(3, sizeof(int));

    if (!pBuffer){
        printf("Erro! Falta de memória\n");
        return -1;
    }

    *(int *)(pBuffer) = 0;

    for(;;){
        *(int *)pBuffer = menu(pBuffer);
        switch (*(int *)pBuffer){
            case 1:
                adicionar(pBuffer);
                break;
            case 2:
                pBuffer = remover(pBuffer);
                break;
            case 3:
                pBuffer = buscar(pBuffer);
                break;
            case 4:
                listar(pBuffer);
                break;
            case 5:
                free(pBuffer);
                exit(0);
                break;
		}
    }
    return 0;
}

int menu(void *pBuffer){	

	int escolha = 0;
    
	do{
		printf("\n1 - adicionar;\n");
        printf("2 - remover;\n");
		printf("3 - buscar;\n");
        printf("4 - listar agenda;\n");
		printf("5 - sair do programa.\n");
		printf("\nsua escolha: "); 
        scanf("%d", &escolha);
	}while(*(int *)pBuffer < 1 || *(int *)pBuffer > 5);
	getchar();

	return *(int *)pBuffer;
}

void adicionar(void *pBuffer){ //função para adicionar o buffer uma celula com o conteudo nome 
                                //idade e telefone do indivíduo
    if(*(int *)(pBuffer + sizeof(int)) >= 10){
        printf("Erro! Não há mais espaço\n");
        return;
    }

    printf("\ndigite o nome: ");
    scanf("%s", (maximo + *(int *)(pBuffer + sizeof(int)))->nome);
    printf("digite a idade: ");
    scanf("%d", &(maximo + *(int *)(pBuffer + sizeof(int)))->idade);
    printf("digite o telefone: ");
    scanf("%s", (maximo + *(int *)(pBuffer + sizeof(int)))->telefone);

    *(int *)(pBuffer + sizeof(int)) = *(int *)(pBuffer + sizeof(int)) + 1;

    return pBuffer;
}

void *remover(void *pBuffer){ //função para remover a celula do indivíduo do buffer

    if(*(int *)(pBuffer + sizeof(int)) == 0){
        printf("Erro! Nenhum nome cadastrado até agora\n");
        return pBuffer;
    }

    printf("digite o nome da pessoa para excluir: ");
    scanf("%s", nome);
    printf("\n\n");

    for(i = size, c = 1; c < size+1; i--, c++){

        for(k = 0; k < strlen(nome)+1; k++){
            aux[k] = *(char *)(pBuffer + k + celula*(size-i) + sizeof(int));
        }

        if(strcmp(aux, nome) == 0){

            if(c != size){

                for(j = 0; j < 10; j++){
                    *(char *)(pBuffer + j + celula*(size-i) + sizeof(int)) = *(char *)(pBuffer
                    + j + celula*(size-i+1) + sizeof(int));
                }
                *(int *)(pBuffer+sizeof(char) * 10 + celula * (size - i) + sizeof(int)) =
                *(int *)(pBuffer+sizeof(char) * 10 + celula *(size - i + 1) + sizeof(int));
                *(int *)(pBuffer+sizeof(char) * 10 + sizeof(int) + celula * (size - i) +
                sizeof(int)) = *(int *)(pBuffer+sizeof(char) * 10 + sizeof(int) + celula
                *(size - i + 1) + sizeof(int));

                for(i = i - 1; c < size-1; i--, c++){
                    for(j = 0; j < 10; j++){
                        *(char *)(pBuffer + j + celula*(size-i) + sizeof(int)) = *(char *)(pBuffer
                        + j + celula*(size-i+1) + sizeof(int));
                    }
                    *(int *)(pBuffer+sizeof(char) * 10 + celula * (size - i) + sizeof(int)) =
                    *(int *)(pBuffer+sizeof(char) * 10 + celula * (size - i + 1) + sizeof(int));
                    *(int *)(pBuffer+sizeof(char) * 10 + sizeof(int) + celula * (size - i) +
                    sizeof(int)) = *(int *)(pBuffer+sizeof(char) * 10 + sizeof(int) + celula 
                    * (size - i + 1) + sizeof(int));
                }

            }

            pBuffer = (char *)realloc(pBuffer, celula*(size-1)+sizeof(int));

            size--;

            return pBuffer;
        }
    }

    return pBuffer;
}

void *buscar(void *pBuffer){ //função para buscar no buffer a célula com o conteúdo do indivíduo

    int *size = pBuffer;

    if(*(int *)(pBuffer) == 0){
        printf("Erro! Nenhum nome cadastrado até agora\n");
        return pBuffer;
    }

    pBuffer = (void *)realloc(pBuffer, sizeof(int) * 3 + sizeof(char) * NOME_MAX);
    
    printf("digite o nome da pessoa para buscar: ");
    scanf("%s", (char *)(pBuffer+sizeof(int)*3));

   
    int *i = (pBuffer + sizeof(int) + sizeof(char) + sizeof(int));

    for(*i = 0, *i < *size; c < size; i--, c++){

        for(k = 0; k < strlen(nome)+1; k++){
            aux[k] = *(char *)(pBuffer + celula*(size-i) + k);
        }
        if(strcmp(aux, nome) == 0){
            printf("\n%d: \tnome: ", c);
            for(k = 0; *(char *)(pBuffer + k + celula*(size-i)) >= 'a' && *(char *)(pBuffer + k +
            celula * (size - i)) <= 'z'; k++){
            printf("%c", *(char *)(pBuffer + k + celula*(size-i)));
        }

        printf("   idade: %d   telefone: %d\n\n", *(int *)(pBuffer+sizeof(char) * 10 + celula *
        (size - i)), *(int *)(pBuffer+sizeof(char) * 10 + sizeof(int) + celula * (size - i)));
        printf("\n\n");
        }
    }
}

void listar(void *pBuffer){ //semelhante à função buscar, lista todas as células de todos
                            //indivíduos

    celula = sizeof(int) * 2 + sizeof(char) * 10;

    if(size == 0){
        printf("\nnenhum nome cadastrado\n");
        return;
    }

    printf("pessoas cadastradas: %d\n\n", *(int *)pBuffer);

    pBuffer = pBuffer + sizeof(int); 

    for(i = size, c = 0; c < size; i--, c++){
        printf("%d:   nome: ", c);
        for(k = 0; *(char *)(pBuffer + k + celula*(size-i)) >= 'a' && *(char *)(pBuffer + k +
        celula * (size - i)) <= 'z'; k++){
            printf("%c", *(char *)(pBuffer + k + celula*(size-i)));
        }

        printf("   idade: %d   telefone: %d\n\n", *(int *)(pBuffer+sizeof(char) * 10 + celula *
        (size - i)), *(int *)(pBuffer+sizeof(char) * 10 + sizeof(int) + celula * (size - i)));
        printf("\n\n");
    }
}