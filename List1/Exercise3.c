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


void *remover(void *pBuffer){
    char name[10], nameaux[10];
    int person, i, c, k, j;

    if(size == 0){
        printf("\nNo data yet!\n");
        return pBuffer;
    }

    person = sizeof(int)*2+sizeof(char)*10;

    
    printf("Name to remove: "); scanf("%s", name);


    for(i = size, c = 1; c < size+1; i--, c++){

        for(k = 0; k < strlen(name)+1; k++){
            nameaux[k] = *(char *)(pBuffer + k + person*(size-i) + sizeof(int));
        }

        if(strcmp(nameaux, name) == 0){

            if(c != size){

                for(j = 0; j < 10; j++){
                    *(char *)(pBuffer + j + person*(size-i) + sizeof(int)) = *(char *)(pBuffer + j + person*(size-i+1) + sizeof(int));
                }
                *(int *)(pBuffer+sizeof(char)*10+person*(size-i) + sizeof(int)) = *(int *)(pBuffer+sizeof(char)*10+person*(size-i+1) + sizeof(int));
                *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i) + sizeof(int)) = *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i+1) + sizeof(int));


                for(i = i - 1; c < size-1; i--, c++){
                    for(j = 0; j < 10; j++){
                        *(char *)(pBuffer + j + person*(size-i) + sizeof(int)) = *(char *)(pBuffer + j + person*(size-i+1) + sizeof(int));
                    }
                    *(int *)(pBuffer+sizeof(char)*10+person*(size-i) + sizeof(int)) = *(int *)(pBuffer+sizeof(char)*10+person*(size-i+1) + sizeof(int));
                    *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i) + sizeof(int)) = *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i+1) + sizeof(int));
                }

            }

            pBuffer = (char *)realloc(pBuffer, person*(size-1)+sizeof(int));
            if (!pBuffer){
                printf("Could not allocate required memory!\n");
                exit(1);
            }
            size--;
            return pBuffer;
        }
    }

    return pBuffer;
}


void buscar(void *pBuffer){
    char name[10], nameaux[10];
    int person, i = 0, c = 0, k = 0;

    person = sizeof(int)*2+sizeof(char)*10;

    if(size == 0){
        printf("\nNo data yet!\n");
        return;
    }
    
    printf("Name to buscar: "); scanf("%s", name);


    pBuffer = pBuffer + sizeof(int); 

    for(i = size, c = 0; c < size; i--, c++){

        for(k = 0; k < strlen(name)+1; k++){
            nameaux[k] = *(char *)(pBuffer + k + person*(size-i));
        }
        if(strcmp(nameaux, name) == 0){
            printf("\nPerson[%d]: \tName: ", c);
            for (k = 0; *(char *)(pBuffer + k + person*(size-i)) >= 'a' && *(char *)(pBuffer + k + person*(size-i)) <= 'z'; k++){
                printf("%c", *(char *)(pBuffer + k + person*(size-i)));
            }
            printf("\n\t\tAge: %d\n\t\tTel: %d\n\n", 
            *(int *)(pBuffer+sizeof(char)*10+person*(size-i)), *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i)));
        }
    }
}


void *adicionar(void *pBuffer){
    char name[10];
    int age, tel, person;

    person = sizeof(int)*2+sizeof(char)*10;

    printf("\n-Adicionar name: "); scanf("%s", name);
    printf("-Adicionar age: "); scanf("%d", &age);
    printf("-Adicionar tel: "); scanf("%d", &tel);

    pBuffer = (char *)realloc(pBuffer, person*size+sizeof(int)+1);
    if (!pBuffer){
        printf("Could not allocate required memory!\n");
        exit(1);
    }


    pBuffer = pBuffer + sizeof(int);  
    pBuffer = pBuffer + person*(size-1);
    for(int i = 0; i < strlen(name)+1; i++){
        *(char *)(pBuffer + i) = name[i];
    }

    pBuffer = pBuffer + sizeof(char)*10;   
    *(int *)pBuffer = age;  

    pBuffer = pBuffer + sizeof(int);    
    *(int *)pBuffer = tel;               

    
    pBuffer = pBuffer - sizeof(int);
    pBuffer = pBuffer - sizeof(char)*10;  
    pBuffer = pBuffer - person*(size-1);
    pBuffer = pBuffer - sizeof(int);

    return pBuffer;
}


void listar(void *pBuffer){
    int person, i = 0, c = 0, k = 0;
    
    person = sizeof(int)*2+sizeof(char)*10;

    if(size == 0){
        printf("\nNo data yet!\n");
        return;
    }
    printf("Size: %d\n\n", *(int *)pBuffer);


    pBuffer = pBuffer + sizeof(int); 

    for(i = size, c = 0; c < size; i--, c++){
        printf("Person[%d]: \tName: ", c);
        for(k = 0; *(char *)(pBuffer + k + person*(size-i)) >= 'a' && *(char *)(pBuffer + k + person*(size-i)) <= 'z'; k++){
            printf("%c", *(char *)(pBuffer + k + person*(size-i)));
        }

        printf("\n\t\tAge: %d\n\t\tTel: %d\n\n", 
        *(int *)(pBuffer+sizeof(char)*10+person*(size-i)), *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i)));
    }
}


int menu(void){	
	int escolha = 0;
    
	do{
		printf("\n1. Adicionar;\n");
        printf("2. Remove;\n");
		printf("3. buscar;\n");
        printf("4. listar all;\n");
		printf("5. Exit.\n");
		printf("\nPlease, choose what you want to do: "); scanf("%d", &escolha);
	}while(escolha < 1 || escolha > 5);
	getchar();

	return escolha;
}
