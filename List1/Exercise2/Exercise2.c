// bibliografia: https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int menu(void);
void mostrar(char *nomes, int sizenomes);
char *adicionar(char *nomes);
char *remover(char *nomes);

int sizenomes = 0;

int main()
{

    int escolha;
    char *nomes;

    nomes = (char *)calloc(1, 1);

    for (;;)
    {
        escolha = menu();
        switch (escolha)
        {
        case 1:
            nomes = adicionar(nomes);
            sizenomes++;
            break;
        case 2:
            nomes = remover(nomes);
            break;
        case 3:
            mostrar(nomes, sizenomes);
            break;
        case 4:
            free(nomes);
            exit(0);
            break;
        }
    }
    return 0;
}

int menu(void)
{

    int escolha = 0;

    do
    {
        printf("\n1) adicionar nome;\n");
        printf("2) remover nome;\n");
        printf("3) listar;\n");
        printf("4) sair.\n");
        printf("\npor favor, digite uma escolha: ");
        scanf("%d", &escolha);
    } while (escolha < 1 || escolha > 4);
    getchar();

    return escolha;
}

char *adicionar(char *nomes)
{

    char buffer[20];

    printf("\ndigite o nome a ser adicionado: ");
    scanf("%s", buffer);
    strcat(buffer, "\n");

    nomes = (char *)realloc(nomes, strlen(nomes) + strlen(buffer) + 1);
    strcat(nomes, buffer);

    return nomes;
}

char *remover(char *nomes)
{

    char buffer[20];
    int i = 0, size;

    printf("\ndigite o nome a ser removido: ");
    scanf("%s", buffer);

    char *localizador = strstr(nomes, buffer);
    size = strlen(nomes);

    if (localizador)
    {

        for (i = 0; i < strlen(buffer) + 1; i++)
        {
            memmove(localizador, (localizador + 1), strlen(localizador + 1) + 1);
        }

        if (size == i)
        {
            nomes = (char *)realloc(nomes, size - i + 2);
            sizenomes--;
            return nomes;
        }
        nomes = (char *)realloc(nomes, size - i + 1);

        sizenomes--;
    }
    else
    {
        printf("\nnome não foi encontrado :(\n");
    }

    return nomes;
}

void mostrar(char *nomes, int sizenomes)
{

    if (sizenomes == 0)
    {
        printf("\nnão existem nomes cadastrados ainda!\n");
        return;
    }

    printf("\nnomes cadastrados:\n%s", nomes);

    printf("\npressione enter para voltar ao menu principal...");
    getchar();
}