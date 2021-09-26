#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOME 20
#define MAX_IDADE 3
#define MAX_TELEFONE 14

// A inspiração para esta seção/organização de defines foi retirada do código do colega de disciplina Otavio Santos (github público: github.com/OtavioFSantos)
// Sequência de defines para facilitar a escrita e leitura do código

#define TAM_PESSOA (sizeof(char) * MAX_NOME + sizeof(char) * MAX_IDADE + sizeof(char) * MAX_TELEFONE + sizeof(void **) * 2)
#define IDADE (sizeof(char) * MAX_NOME)
#define TELEFONE ((sizeof(char) * MAX_NOME) + (sizeof(char) * MAX_IDADE))
#define ANTERIOR ((sizeof(char) * MAX_NOME) + (sizeof(char) * MAX_IDADE) + (sizeof(char) * MAX_TELEFONE))
#define PROXIMO ((sizeof(char) * MAX_NOME) + (sizeof(char) * MAX_IDADE) + (sizeof(char) * MAX_TELEFONE) + sizeof(void **))
#define PRIMEIRO (sizeof(int) + sizeof(void **))
#define ULTIMO (sizeof(int))
#define AUX (sizeof(void **))
#define NOME (sizeof(void **) + sizeof(int))

int menu(void *pBuffer){
    *(int *)(pBuffer + AUX) = 0;

    while (*(int *)(pBuffer + AUX) < 1 || *(int *)(pBuffer + AUX) > 5){
        printf("\n---------MENU---------\n");
        printf("\n1- Incluir\n2- Buscar\n3- Listar\n4- Apagar\n5- Sair\n\nEscolha uma opcao: ");
        scanf("%d", &*(int *)(pBuffer + AUX));
        getchar();
    }

    return *(int *)(pBuffer + AUX);
}

void adicionarPessoa(void *pBuffer, void *listaPessoas){

    void *tracer;
    void *novaPessoa = (void *)malloc(TAM_PESSOA);

    if (!novaPessoa){
        printf("\nErro ao alocar memória para novaPessoa\n");
        return;
    }

    printf("\nEndereço: %p", novaPessoa);
    printf("\nInforme o nome: ");
    scanf("%19[^\n]%*c", (char *)novaPessoa);
    printf("Informe a idade: ");
    scanf("%s", (char *)(novaPessoa + IDADE));
    getchar();
    printf("Informe o numero de telefone: ");
    scanf("%s", (char *)(novaPessoa + TELEFONE));
    getchar();

    *(void **)(novaPessoa + ANTERIOR) = NULL;
    *(void **)(novaPessoa + PROXIMO) = NULL;

    if (*(int *)listaPessoas == 0){
        *(void **)(listaPessoas + ULTIMO) = novaPessoa;
        *(void **)(listaPessoas + PRIMEIRO) = novaPessoa;
        *(int *)listaPessoas += 1;

        return;
    }

    pBuffer = *(void **)(listaPessoas + PRIMEIRO);

    do{
        if (strcmp((char *)novaPessoa, (char *)pBuffer) < 0){

            *(void **)(novaPessoa + ANTERIOR) = *(void **)(pBuffer + ANTERIOR);
            *(void **)(novaPessoa + PROXIMO) = pBuffer;

            if (*(int *)listaPessoas > 1 && *(void **)(pBuffer + ANTERIOR) != NULL){
                tracer = *(void **)(pBuffer + ANTERIOR);
                *(void **)(tracer + PROXIMO) = novaPessoa;
            }
            *(void **)(pBuffer + ANTERIOR) = novaPessoa;

            if (*(void **)(novaPessoa + ANTERIOR) == NULL){
                *(void **)(listaPessoas + PRIMEIRO) = novaPessoa;
            }

            *(int *)listaPessoas += 1;
            return;
        }

        if (*(void **)(pBuffer + PROXIMO) == NULL){
            break;
        }
        pBuffer = *(void **)(pBuffer + PROXIMO);
    } while (pBuffer != NULL);

    *(void **)(novaPessoa + ANTERIOR) = pBuffer;
    *(void **)(pBuffer + PROXIMO) = novaPessoa;
    *(void **)(listaPessoas + ULTIMO) = novaPessoa;

    *(int *)listaPessoas += 1;
    return;
}

void listarTodas(void *pBuffer, void *listaPessoas)
{
    if (*(int *)listaPessoas == 0){
        printf("\nNinguém foi cadastrado ainda.\n");
        return;
    }

    pBuffer = *(void **)(listaPessoas + PRIMEIRO);

    printf("\nCADASTROS ENCONTRADOS: %d\n", *(int *)listaPessoas);

    do{
        printf("\n------------------\n\nEndereço do indivíduo: %p\nNome: %s\nIdade: %s\nTelefone: %s\n\n",
               pBuffer, (char *)pBuffer, (char *)(pBuffer + IDADE), (char *)(pBuffer + TELEFONE));
        pBuffer = *(void **)(pBuffer + PROXIMO);
    } while (pBuffer != NULL);

    return;
}

void buscarPessoa(void *pBuffer, void *listaPessoas)
{
    if (*(int *)listaPessoas == 0){
        printf("\nNinguém foi cadastrado ainda.\n");
        return;
    }

    printf("\nInforme o nome que deseja buscar: ");
    scanf("%19[^\n]%*c", (char *)(pBuffer + NOME));

    void *aux = (pBuffer + NOME);

    pBuffer = *(void **)(listaPessoas + PRIMEIRO);

    while (pBuffer != NULL){
        if (strcmp((char *)aux, pBuffer) == 0){
            printf("\n------------------\n\nEndereço do indivíduo: %p\nNome: %s\nIdade: %s\nTelefone: %s\n------------------\n",
                   pBuffer, (char *)pBuffer, (char *)(pBuffer + IDADE), (char *)(pBuffer + TELEFONE));
            return;
        } else{
            pBuffer = *(void **)(pBuffer + PROXIMO);
        }
    }
    printf("\nNome nao encontrado.\n");

    return;
}

void apagarIndividuo(void *pBuffer, void *listaPessoas){

    void *aux;

    if (*(int *)listaPessoas == 0){
        printf("\nNinguém foi cadastrado ainda.\n");
        return;
    }

    printf("\nIndivíduo a ser removido: ");
    scanf("%19[^\n]%*c", (char *)(pBuffer + NOME));
    
    void *nome = (char *)(pBuffer + NOME);

    pBuffer = *(void **)(listaPessoas + PRIMEIRO);
    do{
        if (strcmp((char *)pBuffer, (char *)nome) == 0){
            if (*(void **)(pBuffer + ANTERIOR) != NULL){
                aux = *(void **)(pBuffer + ANTERIOR);
                *(void **)(aux + PROXIMO) = *(void **)(pBuffer + PROXIMO);
            } else{
                *(void **)(listaPessoas + PRIMEIRO) = *(void **)(pBuffer + PRIMEIRO);
            }
            if (*(void **)(pBuffer + PROXIMO) != NULL){
                aux = *(void **)(pBuffer + PROXIMO);
                *(void **)(aux + ANTERIOR) = *(void **)(pBuffer + ANTERIOR);
            } else{
                *(void **)(listaPessoas + ULTIMO) = *(void **)(pBuffer + ANTERIOR);
            }

            *(int *)listaPessoas -= 1;

            free(pBuffer);
            
            printf("\nIndivíduo removido com sucesso.\n");
            return;
        }
        pBuffer = *(void **)(pBuffer + PROXIMO);
    } while (pBuffer != NULL);

    printf("\nNome não encontrado.\n");
    free(nome);
}

void limparLista(void *pBuffer, void *listaPessoas)
{
    void *aux;
    pBuffer = *(void **)(listaPessoas + PRIMEIRO);

    while (pBuffer != NULL){
        aux = *(void **)(pBuffer + PROXIMO);
        free(pBuffer);
        pBuffer = aux;
    }
    free(aux);
    
    printf("\nLista limpa com sucesso.\n");

    return;
}

int main(){

    void *pBuffer = (void *)calloc(1, sizeof(void **) + sizeof(int) + MAX_NOME * sizeof(char));

    if (!pBuffer){
        printf("\nErro ao alocar memória para pBuffer.\n");
        return (-1);
    }
    void *listaPessoas = (void *)calloc(1, sizeof(int) + sizeof(void **) * 2);

    if (!listaPessoas){
        printf("\nErro ao alocar memória para ListaPessoas.\n");
        return (-1);
    }

    *(int *)listaPessoas = 0;
    *(void **)(pBuffer) = NULL;
    *(void **)(listaPessoas + PRIMEIRO) = NULL;
    *(void **)(listaPessoas + ULTIMO) = NULL;

    for (;;){
        *(int *)(pBuffer + AUX) = menu(pBuffer);

        switch (*(int *)(pBuffer + AUX)){
        case 1:
            adicionarPessoa(pBuffer, listaPessoas);
            break;
        case 2:
            buscarPessoa(pBuffer, listaPessoas);
            break;
        case 3:
            listarTodas(pBuffer, listaPessoas);
            break;
        case 4:
            apagarIndividuo(pBuffer, listaPessoas);
            break;
        case 5:
            limparLista(pBuffer, listaPessoas);
            free(pBuffer);
            free(listaPessoas);
            exit(0);
            break;
        default:
            break;
        }
    }
}