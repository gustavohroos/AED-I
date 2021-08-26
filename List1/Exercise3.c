#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(void);
void *adicionar(void *pBuffer);
void *remover(void *pBuffer);
void listar(void *pBuffer);
void buscar(void *pBuffer);

int size = 0;
 
int main(){

    void *pBuffer;
    int escolha;

    pBuffer = (void *)calloc(1, sizeof(int));

    *(int *)pBuffer = size;

    for(;;){
        escolha = menu();
        switch (escolha){
            case 1:
                size++;
                *(int *)pBuffer = size;
                pBuffer = adicionar(pBuffer);
                break;
            case 2:
                pBuffer = remover(pBuffer);
                *(int *)pBuffer = size;
                break;
            case 3:
                buscar(pBuffer);
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

int menu(void){	
	int escolha = 0;
    
	do{
		printf("\n1 - adicionar;\n");
        printf("2 - remover;\n");
		printf("3 - buscar;\n");
        printf("4 - listar agenda;\n");
		printf("5 - sair do programa.\n");
		printf("\nsua escolha: "); 
        scanf("%d", &escolha);
	}while(escolha < 1 || escolha > 5);
	getchar();

	return escolha;
}

void *adicionar(void *pBuffer){

    char nome[10], telefone[14];
    int idade, celula;

    celula = sizeof(int)+sizeof(char)*10+sizeof(char)*14;

    printf("\ndigite o nome: ");
    scanf("%s", nome);
    printf("digite a idade: ");
    scanf("%d", &idade);
    printf("digite o telefone: ");
    scanf("%s", telefone);

    pBuffer = (char *)realloc(pBuffer, celula*size+sizeof(int)+1);

    pBuffer = pBuffer + sizeof(int);  
    pBuffer = pBuffer + celula*(size-1);
    for(int i = 0; i < strlen(nome)+1; i++){
        *(char *)(pBuffer + i) = nome[i];
    }

    pBuffer = pBuffer + sizeof(char)*10;   
    *(int *)pBuffer = idade;

    for(int i = 0; i < strlen(telefone)+1; i++){
        *(char *)(pBuffer + i) = telefone[i];
    }               

    
    pBuffer = pBuffer - sizeof(int);
    pBuffer = pBuffer - sizeof(char)*10;  
    pBuffer = pBuffer - celula*(size-1);
    pBuffer = pBuffer - sizeof(char)*14;  
    pBuffer = pBuffer - celula*(size-1);

    return pBuffer;
}

void *remover(void *pBuffer){

    char nome[10], aux[10];
    int celula, i, c, k, j;

    if(size == 0){
        printf("\nnenhum nome cadastrado\n");
        return pBuffer;
    }

    celula = sizeof(int)+sizeof(char)*10+sizeof(char)*14;

    printf("digite o nome da pessoa para excluir: ");
    scanf("%s", nome);

    for(i = size, c = 1; c < size+1; i--, c++){

        for(k = 0; k < strlen(nome)+1; k++){
            aux[k] = *(char *)(pBuffer + k + celula*(size-i) + sizeof(int));
        }

        if(strcmp(aux, nome) == 0){

            if(c != size){

                for(j = 0; j < 10; j++){
                    *(char *)(pBuffer + j + celula*(size-i) + sizeof(int)) = *(char *)(pBuffer + j + celula*(size-i+1) + sizeof(int));
                }
                *(int *)(pBuffer+sizeof(char)*10+celula*(size-i) + sizeof(int)) = *(int *)(pBuffer+sizeof(char)*10+celula*(size-i+1) + sizeof(int));
                for(j = 0; j < 14; j++){
                    *(char *)(pBuffer + j + sizeof(char)*10+sizeof(int) + celula*(size-i) + sizeof(int)) = *(char *)(pBuffer + j + sizeof(char)*10+sizeof(int) + celula*(size-i+1) + sizeof(int));
                }


                for(i = i - 1; c < size-1; i--, c++){
                    for(j = 0; j < 10; j++){
                        *(char *)(pBuffer + j + celula*(size-i) + sizeof(int)) = *(char *)(pBuffer + j + celula*(size-i+1) + sizeof(int));
                    }
                    *(int *)(pBuffer+sizeof(char)*10+celula*(size-i) + sizeof(int)) = *(int *)(pBuffer+sizeof(char)*10+celula*(size-i+1) + sizeof(int));
                    for(j = 0; j < 14; j++){
                        *(char *)(pBuffer + j + sizeof(char)*10 + sizeof(int) + celula*(size-i) + sizeof(int)) = *(char *)(pBuffer + j + sizeof(char)*10 + sizeof(int) + celula*(size-i+1) + sizeof(int));
                    }
                }

            }

            pBuffer = (char *)realloc(pBuffer, celula*(size-1)+sizeof(int));

            size--;

            return pBuffer;
        }
    }

    return pBuffer;
}

void buscar(void *pBuffer){
    
    char nome[10], aux[10];
    int celula, i = 0, c = 0, k = 0;

    celula = sizeof(int)*2+sizeof(char)*10;

    if(size == 0){
        printf("\nnenhum nome cadastrado\n");
        return;
    }
    
    printf("digite o nome da pessoa para buscar: ");
    scanf("%s", nome);


    pBuffer = pBuffer + sizeof(int); 

    for(i = size, c = 0; c < size; i--, c++){

        for(k = 0; k < strlen(nome)+1; k++){
            aux[k] = *(char *)(pBuffer + celula*(size-i) + k);
        }
        if(strcmp(aux, nome) == 0){
            printf("\n[%d]: \tnome: ", c);
            for (k = 0; *(char *)(pBuffer + k + celula*(size-i)) >= 'a' && *(char *)(pBuffer + celula*(size-i) + k) <= 'z'; k++){
                printf("%c", *(char *)(pBuffer + celula*(size-i) + k));
            }
            printf("\tidade: %d", *(int *)(pBuffer+sizeof(char)*10+celula*(size-i)));
            printf("     telefone: ");
            for (k = 0; *(char *)(pBuffer + k + sizeof(char)*10 + sizeof(int) + celula*(size-i) + sizeof(int)) >= '0' && *(char *)(pBuffer + k + sizeof(char)*10 + sizeof(int) + celula*(size-i) + sizeof(int) + k) <= '9'; k++){
                printf("%c", *(char *)(pBuffer + celula*(size-i) + k));
            }
            printf("\n\n");
        }
    }
}

void listar(void *pBuffer){
    int celula, i = 0, c = 0, k = 0;
    
    celula = sizeof(int)*2+sizeof(char)*10;

    if(size == 0){
        printf("\nNo data yet!\n");
        return;
    }
    printf("Size: %d\n\n", *(int *)pBuffer);


    pBuffer = pBuffer + sizeof(int); 

    for(i = size, c = 0; c < size; i--, c++){
        printf("%d: \tnome: ", c);
        for (k = 0; *(char *)(pBuffer + k + celula*(size-i)) >= 'a' && *(char *)(pBuffer + celula*(size-i) + k) <= 'z'; k++){
            printf("%c", *(char *)(pBuffer + celula*(size-i) + k));
        }
        printf("\tidade: %d", *(int *)(pBuffer+sizeof(char)*10+celula*(size-i)));
        printf("     telefone: ");
        for (k = 0; *(char *)(pBuffer + k + sizeof(char)*10 + sizeof(int) + celula*(size-i) + sizeof(int)) >= '0' && *(char *)(pBuffer + k + sizeof(char)*10 + sizeof(int) + celula*(size-i) + sizeof(int) + k) <= '9'; k++){
            printf("%c", *(char *)(pBuffer + celula*(size-i) + k));
        }
        printf("\n\n");
    }
}