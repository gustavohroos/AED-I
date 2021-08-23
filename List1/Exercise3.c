#include <stdio.h>
#include <stdlib.h>

void *adicionar(void *pBuffer);
void *remover(void *pBuffer);
void mostrar(void *pBuffer);
void buscar(void *pBuffer);
int menu(void);

int size = 0;

int main(){

    int escolha;
    void *pBuffer;

    pBuffer = (char *)calloc(1, 1);

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
                mostrar(pBuffer);
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
		printf("\n1) Adicionar nome;\n");
        printf("2) Remover nome;\n");
		printf("3) Listar;\n");
        printf("4) Buscar;\n");
		printf("5) Sair.\n");
		printf("\nPor favor, digite uma escolha: ");
        scanf("%d", &escolha);
	}while(escolha < 1 || escolha > 4);
	getchar();

	return escolha;
}

void *adicionar(void *pBuffer){

    char buffer[20];

    printf("\nDigite o nome a ser adicionado: "); 
    scanf("%s", buffer);
    strcat(buffer, "\n");

    pBuffer = (char *)realloc(pBuffer, strlen(pBuffer)+strlen(buffer)+1);
    strcat(pBuffer, buffer);

    return pBuffer;
}

void *remover(void *pBuffer){
    
    char buffer[20];
    int i = 0, size;

    printf("\nDigite o nome a ser removido: "); 
    scanf("%s", buffer);

    char *localizador = strstr(pBuffer, buffer);
    size = strlen(pBuffer);

    if(localizador){

        for(i = 0; i < strlen(buffer)+1; i++){
            memmove(localizador, (localizador+1), strlen(localizador+1) + 1);
        }

        if(size == i){
            pBuffer = (char *)realloc(pBuffer, size-i+2);
            sizepBuffer--;
            return pBuffer;
        }
        pBuffer = (char *)realloc(pBuffer, size-i+1);

        sizepBuffer--;

    }else{
        printf("\nNome não foi encontrado :(\n");
    }

    return pBuffer;
}

void mostrar(void *pBuffer){

    if (sizepBuffer == 0) {
        printf("\nNão existem pBuffer cadastrados ainda!\n");
        return;
    }

    printf("\npBuffer cadastrados:\n%s", pBuffer);

    printf("\nPressione Enter para voltar ao menu principal...");
    getchar();

    
}

void buscar(void *pBuffer){


}

