#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PESSOAS_MAX 10
#define NOME_MAX 20
#define TELEFONE_MAX 14

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

int main()
{

    void *pBuffer;

    pBuffer = (void *)calloc(3, sizeof(int));

    if (!pBuffer)
    {
        printf("Erro! Falta de memória\n");
        return -1;
    }

    *(int *)(pBuffer + sizeof(int)) = 0;

    for (;;)
    {
        *(int *)pBuffer = menu(pBuffer);
        switch (*(int *)pBuffer)
        {
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

int menu(void *pBuffer)
{

    do
    {
        printf("\n1 - Adicionar;\n");
        printf("2 - Remover;\n");
        printf("3 - Buscar;\n");
        printf("4 - Listar agenda;\n");
        printf("5 - Sair do programa.\n");
        printf("\nEscolha: ");
        scanf("%d", &*(int *)pBuffer);
    } while (*(int *)pBuffer < 1 || *(int *)pBuffer > 5);
    getchar();

    return *(int *)pBuffer;
}

void adicionar(void *pBuffer)
{ //função para adicionar o buffer uma celula com o conteudo nome
    //idade e telefone do indivíduo
    if (*(int *)(pBuffer + sizeof(int)) >= 10)
    {
        printf("Erro! Não há mais espaço\n");
        return;
    }

    printf("\nDigite o nome: ");
    scanf("%s", (maximo + *(int *)(pBuffer + sizeof(int)))->nome);
    printf("Digite a idade: ");
    scanf("%d", &(maximo + *(int *)(pBuffer + sizeof(int)))->idade);
    printf("Digite o telefone: ");
    scanf("%s", (maximo + *(int *)(pBuffer + sizeof(int)))->telefone);

    *(int *)(pBuffer + sizeof(int)) = *(int *)(pBuffer + sizeof(int)) + 1;
}

void *remover(void *pBuffer)
{ //função para remover a celula do indivíduo do buffer

    if (*(int *)(pBuffer + sizeof(int)) == 0)
    {
        printf("Erro! Nenhum nome cadastrado até agora\n");
        return pBuffer;
    }

    pBuffer = (void *)realloc(pBuffer, sizeof(int) * 3 + sizeof(char) * NOME_MAX + sizeof(char) *
    TELEFONE_MAX);

    printf("Digite o nome da pessoa para excluir: ");
    scanf("%s", (char *)(pBuffer + sizeof(int) * 3));
    printf("\n\n");

    for (*(int *)(pBuffer + sizeof(int) * 2) = 0; *(int *)(pBuffer + sizeof(int) * 2) <
    *(int *)(pBuffer + sizeof(int)); *(int *)(pBuffer + sizeof(int) * 2) =
    *(int *)(pBuffer + sizeof(int) * 2) + 1)
    {

        if (strcmp((char *)(pBuffer + sizeof(int) * 3), (maximo + *(int *)(pBuffer +
        sizeof(int) * 2))->nome) == 0)
        {
            for (; *(int *)(pBuffer + sizeof(int) * 2) < (*(int *)(pBuffer + sizeof(int)) - 1);
            *(int *)(pBuffer + sizeof(int) * 2) = *(int *)(pBuffer + sizeof(int) * 2) + 1)
            {
                strcpy((maximo + *(int *)(pBuffer + sizeof(int) * 2))->nome, (maximo + 1 +
                *(int *)(pBuffer + sizeof(int) * 2))->nome);
                (maximo + *(int *)(pBuffer + sizeof(int) * 2))->idade = (maximo + 1 +
                *(int *)(pBuffer + sizeof(int) * 2))->idade;
                strcpy((maximo + *(int *)(pBuffer + sizeof(int) * 2))->telefone, (maximo + 1 +
                *(int *)(pBuffer + sizeof(int) * 2))->telefone);
            }

            *(int *)(pBuffer + sizeof(int)) = *(int *)(pBuffer + sizeof(int)) - 1;
            return pBuffer;
        }
    }

    printf("\nNome não encontrado\n");
    return pBuffer;
}

void *buscar(void *pBuffer)
{ //função para buscar no buffer a célula com o conteúdo do indivíduo

    if (*(int *)(pBuffer) == 0)
    {
        printf("\nErro! Nenhum nome cadastrado até agora\n");
        return pBuffer;
    }

    pBuffer = (void *)realloc(pBuffer, sizeof(int) * 3 + sizeof(char) * NOME_MAX);

    printf("\nDigite o nome da pessoa para buscar: ");
    scanf("%s", (char *)(pBuffer + sizeof(int) * 3));

    for (*(int *)(pBuffer + sizeof(int) * 2) = 0; *(int *)(pBuffer + sizeof(int) * 2) <
    *(int *)(pBuffer + sizeof(int)); *(int *)(pBuffer + sizeof(int) * 2) += 1)
    {

        if (strcmp((char *)(pBuffer + sizeof(int) * 3), (maximo + *(int *)(pBuffer +
        sizeof(int) * 2))->nome) == 0)
        {
            printf("\n\tNome: %s\tIdade: %d\tTelefone: %s\n", (maximo + *(int *)(pBuffer + sizeof(int) * 2))->nome,
            (maximo + *(int *)(pBuffer + sizeof(int) * 2))->idade, (maximo + *(int *)(pBuffer +
            sizeof(int) * 2))->telefone);
            return pBuffer;
        }
    }

    printf("\nNome não encontrado\n");
    return pBuffer;
}

void listar(void *pBuffer)
{ //semelhante à função buscar, lista todas as células de todos
    //indivíduos

    if ((pBuffer + sizeof(int)) == 0)
    {
        printf("\nNenhum nome cadastrado\n");
        return;
    }

    printf("\nPessoas cadastradas: %d\n\n", *(int *)(pBuffer + sizeof(int)));

    for (*(int *)(pBuffer + sizeof(int) * 2) = 0; *(int *)(pBuffer + sizeof(int) * 2) <
    *(int *)(pBuffer + sizeof(int)); *(int *)(pBuffer + sizeof(int) * 2) =
    *(int *)(pBuffer + sizeof(int) * 2) + 1)
    {
        printf("\n\tIndivíduo %d\tNome: %s\tIdade: %d\tTelefone: %s\n", *(int *)(pBuffer +
        sizeof(int) * 2), (maximo + *(int *)(pBuffer + sizeof(int) * 2))->nome, (maximo
        + *(int *)(pBuffer + sizeof(int) * 2))->idade, (maximo + *(int *)(pBuffer +
        sizeof(int) * 2))->telefone);
    }
}