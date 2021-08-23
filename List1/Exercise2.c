#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int menu(void);
void mostrar(char *nomes, int size);
char* adicionar(char *nomes);
char* remover(char *nomes);

int size = 0;

int main(int argc, char const *argv[]) {

    int escolha;
    char *nomes;

    nomes = (char *)calloc(1, 1);

    for(;;){
        escolha = menu();
        switch (escolha){
            case 1:
                nomes = adicionar(nomes);
                size++;
                break;
            case 2:
                nomes = remover(nomes);
                break;
            case 3:
                mostrar(nomes, size);
                break;
            case 4:
                free(nomes);
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
		printf("4) Sair.\n");
		printf("\nPor favor, digite uma escolha: ");
        scanf("%d", &escolha);
	}while(escolha < 1 || escolha > 4);
	getchar();

	return escolha;
}

char* adicionar(char *nomes){

    char buffer[20];

    printf("\nDigite o nome a ser adicionado: "); 
    scanf("%s", buffer);
    strcat(buffer, " ");

    nomes = (char *)realloc(nomes, strlen(nomes)+strlen(buffer)+1);
    strcat(nomes, buffer);

    return nomes;
}

char *remover(char *nomes){

    char buffer[20];
    int i = 0, sizeRem;

    printf("\nDigite o nome a ser removido: "); 
    scanf("%s", buffer);

    char *pch = strstr(nomes, buffer);
    sizeRem = strlen(nomes);

    if(pch){

        for(i = 0; i < strlen(buffer)+1; i++){
            memmove(pch, (pch+1), strlen(pch+1) + 1);
        }

        if(size == i){
            nomes = (char *)realloc(nomes, sizeRem-i+2);
            size--;
            return nomes;
        }
        nomes = (char *)realloc(nomes, size-i+1);

        size--;

    }else{
        printf("\nNome não encontrado na lista :(\n");
    }

    return nomes;
}

void mostrar(char *nomes, int size) {

    if (size == 0) {
        printf("Não existem nomes cadastrados ainda!");
        return;
    }

    printf("Nomes cadastrados:\n%s\n", nomes);

    printf("Pressione Enter para voltar ao menu principal...");
    getchar();

    
}