#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_MAX 20
#define TELEFONE_MAX 14

typedef struct
{
    char nome[NOME_MAX];
    char telefone[TELEFONE_MAX];
    int idade;
} Pessoa;

typedef struct Celula *Lista;

struct Celula
{
    struct Celula *anterior;
    Pessoa informaçoes;
    struct Celula *proximo;
}

typedef struct Celula Celula;

Lista *pIni;

void *pBuffer = NULL;

Lista *CriarLista();

int menu(Lista *pIni, void *pBuffer);
void adicionar(Lista *pIni, void *pBuffer);
void remover(Lista *pIni, void *pBuffer);
void listar(Lista *pIni);
void buscar(Lista *pIni, void *pBuffer);

int main()
{

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

Lista *criarLista()
{
    Lista *pIni = (Lista *)malloc(sizeof(Lista));
    if (pIni != NULL)
        *pIni = NULL;
    return pIni;
}

void limparLista(Lista *pIni)
{
    if (pIni != NULL)
    {
        Celula *celula;
        while ((*pIni) != NULL)
        {
            celula = *pIni;
            *pIni = (*pIni)->proximo;
            free(celula);
        }
        free(pIni);
    }
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

void inserirDadosOrdenados(Lista *pIni, void *pBuffer)
{
    if (pIni != NULL)
    {
        Celula *celula = (celula *)malloc(sizeof(celula));
        if (celula != NULL)
        {
            celula->infos = *(Pessoa *)pBuffer;

            if ((*pIni) == NULL)
            {
                celula->anterior = NULL;
                celula->proximo = NULL;
                *pIni = celula;
            }
            else
            {
                Celula *anterior, *atual = *pIni;
                if ((*(int *)(pBuffer + sizeof(Pessoa) + (sizeof(char) * 10))) == 1)
                {
                    while (atual != NULL && strcmp(atual->infos.nome, (*(Pessoa *)pBuffer).nome) < 0)
                    {
                        anterior = atual;
                        atual = atual->proximo;
                    }
                }
                else
                {
                    while (atual != NULL && atual->infos.idade < (*(Pessoa *)pBuffer).idade)
                    {
                        anterior = atual;
                        atual = atual->proximo;
                    }
                }

                if (atual == *pIni)
                {
                    celula->anterior = NULL;
                    (*pIni)->anterior = celula;
                    celula->proximo = (*pIni);
                    *pIni = celula;
                }
                else
                {
                    celula->proximo = anterior->proximo;
                    celula->anterior = anterior;
                    anterior->proximo = celula;
                    if (atual != NULL)
                        atual->anterior = celula;
                }
            }
        }
    }
}
void *remover(void *pBuffer)
{

    if (*(int *)(pBuffer + sizeof(int)) == 0)
    {
        printf("Erro! Nenhum nome cadastrado até agora\n");
        return pBuffer;
    }

    pBuffer = (void *)realloc(pBuffer, sizeof(int) * 3 + sizeof(char) * NOME_MAX + sizeof(char) * TELEFONE_MAX);

    printf("Digite o nome da pessoa para excluir: ");
    scanf("%s", (char *)(pBuffer + sizeof(int) * 3));
    printf("\n\n");

    for (*(int *)(pBuffer + sizeof(int) * 2) = 0; *(int *)(pBuffer + sizeof(int) * 2) <
                                                  *(int *)(pBuffer + sizeof(int));
         *(int *)(pBuffer + sizeof(int) * 2) =
             *(int *)(pBuffer + sizeof(int) * 2) + 1)
    {

        if (strcmp((char *)(pBuffer + sizeof(int) * 3), (maximo + *(int *)(pBuffer +
                                                                           sizeof(int) * 2))
                                                            ->nome) == 0)
        {
            for (; *(int *)(pBuffer + sizeof(int) * 2) < (*(int *)(pBuffer + sizeof(int)) - 1);
                 *(int *)(pBuffer + sizeof(int) * 2) = *(int *)(pBuffer + sizeof(int) * 2) + 1)
            {
                strcpy((maximo + *(int *)(pBuffer + sizeof(int) * 2))->nome, (maximo + 1 +
                                                                              *(int *)(pBuffer + sizeof(int) * 2))
                                                                                 ->nome);
                (maximo + *(int *)(pBuffer + sizeof(int) * 2))->idade = (maximo + 1 +
                                                                         *(int *)(pBuffer + sizeof(int) * 2))
                                                                            ->idade;
                strcpy((maximo + *(int *)(pBuffer + sizeof(int) * 2))->telefone, (maximo + 1 +
                                                                                  *(int *)(pBuffer + sizeof(int) * 2))
                                                                                     ->telefone);
            }

            *(int *)(pBuffer + sizeof(int)) = *(int *)(pBuffer + sizeof(int)) - 1;
            return pBuffer;
        }
    }

    printf("\nNome não encontrado\n");
    return pBuffer;
}

void buscar(Lista *pIni, void *pBuffer)
{
    if (pIni != NULL)
    {
        Celula *celula = *pIni;
        while ((celula != NULL) && (strcmp((char *)(pBuffer + sizeof(int)), celula->infos.nome) != 0))
        {
            celula = celula->proximo;
        }
        if (celula == NULL)
        {
            printf("\n\tErro na busca: nome não encontrado.\n");
        }
        else
        {
            printf("\n\tNome: %s", celula->infos.nome);
            printf("\tIdade: %d", celula->infos.idade);
            printf("\tTelefone: %s\n", celula->infos.telefone);
        }
    }
}

void listar(Lista *pIni)
{
    if (pIni != NULL)
    {
        Celula *celula = *pIni;
        while (celula != NULL)
        {
            printf("\n\tNome: %s", celula->infos.nome);
            printf("\tIdade: %d", celula->infos.idade);
            printf("\tTelefone: %s\n", celula->infos.telefone);
            celula = celula->proximo;
        }
    }
}