#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOME 20
#define MAX_IDADE 3
#define MAX_TELEFONE 14

// A inspiração para esta seção/organização de defines foi retirada do código do colega de disciplina Otavio Santos (github público: github.com/OtavioFSantos)

// Sequência de defines para facilitar a escrita e leitura do código

#define TAM_PESSOA (sizeof(char) * MAX_NOME + sizeof(char) * MAX_IDADE + sizeof(char) * MAX_TELEFONE + sizeof(void **) * 2) //Nome[MAX_NOME] + idade + telefone + end elemento anterior + end próximo elemento
#define IDADE (sizeof(char) * MAX_NOME)
#define TELEFONE ((sizeof(char) * MAX_NOME) + (sizeof(char) * MAX_IDADE))
#define ANTERIOR ((sizeof(char) * MAX_NOME) + (sizeof(char) * MAX_IDADE) + (sizeof(char) * MAX_TELEFONE))
#define PROXIMO ((sizeof(char) * MAX_NOME) + (sizeof(char) * MAX_IDADE) + (sizeof(char) * MAX_TELEFONE) + sizeof(void **))
#define PRIMEIRO (sizeof(int) + sizeof(void **))
#define ULTIMO (sizeof(int))
#define AUX (sizeof(void **))                // Segundo elemento do pBuffer. Armazena uma variável int auxiliar
#define NOME (sizeof(void **) + sizeof(int)) // Terceiro elemento do pBuffer. Armazena uma string auxiliar para ler nomes

int menu(void *pBuffer)
{
    *(int *)(pBuffer + AUX) = 0; // Reinicializa em 0

    while (*(int *)(pBuffer + AUX) < 1 || *(int *)(pBuffer + AUX) > 5){
        printf("\n---------MENU---------\n");
        printf("\n1- Incluir\n2- Buscar\n3- Listar\n4- Apagar\n5- Sair\n\nEscolha uma opcao: ");
        scanf("%d", &*(int *)(pBuffer + AUX));
        getchar();
    }

    return *(int *)(pBuffer + AUX);
}

void adicionarPessoa(void *pBuffer, void *listaPessoas)
{
    void *tracer;
    void *novaPessoa = (void *)malloc(TAM_PESSOA);

    if (!novaPessoa) // Testa se foi possível alocar
    {
        printf("\nErro ao alocar memória para novaPessoa\n");
        return;
    }

    printf("\nEndereço: %p", novaPessoa);
    printf("\nInforme o nome: ");
    scanf("%[^\n]%*c", (char *)novaPessoa);
    // fgets((char *)novaPessoa, MAX_NOME, stdin);
    printf("Informe a idade: ");
    scanf("%s", (char *)(novaPessoa + IDADE));
    getchar();
    printf("Informe o numero de telefone: ");
    scanf("%s", (char *)(novaPessoa + TELEFONE));
    getchar();

    printf("\nNome inserido: %s\n", (char *)novaPessoa);
    printf("\nIdade inserida: %s\n", (char *)novaPessoa + IDADE);
    printf("\nTelefone inserido: %s\n", (char *)novaPessoa + TELEFONE);

    *(void **)(novaPessoa + ANTERIOR) = NULL;
    *(void **)(novaPessoa + PROXIMO) = NULL;

    if (*(int *)listaPessoas == 0) // Verifica se é a primeira pessoa
    {
        *(void **)(listaPessoas + ULTIMO) = novaPessoa;
        *(void **)(listaPessoas + PRIMEIRO) = novaPessoa;
        
        *(int *)listaPessoas += 1;

        return;
    }

    pBuffer = *(void **)(listaPessoas + PRIMEIRO); //Aponta para o primeiro elemento da lista

    while (1)
    {
        if (strcmp((char *)novaPessoa, (char *)pBuffer) < 0)
        {
            *(void **)(novaPessoa + ANTERIOR) = *(void **)(pBuffer + ANTERIOR);
            *(void **)(novaPessoa + PROXIMO) = pBuffer;
            // *(void **)(pBuffer + ANTERIOR) = novaPessoa;

            if (pBuffer == *(void **)listaPessoas + PRIMEIRO)
            {
                *(void **)(listaPessoas + PRIMEIRO) = novaPessoa;
                *(int *)listaPessoas += 1;
                return;
            }
            else
            {
                *(void **)(tracer + PROXIMO) = novaPessoa;
                *(int *)listaPessoas += 1;
                return;
            }
        }
        else
        {
            tracer = pBuffer;
            pBuffer = *(void **)(pBuffer + PROXIMO);

            if (pBuffer == NULL)
            {
                *(void **)(tracer + PROXIMO) = novaPessoa;
                *(void **)(novaPessoa + ANTERIOR) = tracer;
                *(void **)(novaPessoa + PROXIMO) = NULL;
                *(void **)(listaPessoas + ULTIMO) = novaPessoa;
            }
        }
    }
}

void listarTodas(void *pBuffer, void *listaPessoas)
{
    if (*(int *)listaPessoas == 0){
        printf("\nNinguém foi cadastrado ainda.\n");
        return;
    }

    pBuffer = *(void **)(listaPessoas + PRIMEIRO);
    *(int *)(pBuffer + AUX) = 1;

    printf("CADASTROS ENCONTRADOS: %d\n", *(int *)listaPessoas);

    do{
        printf("\n------Pessoa %d------\nEndereço do indivíduo: %p\nNome: %s\nIdade: %s\nTelefone: %s\n\n", *(int *)(pBuffer + AUX), pBuffer, (char *)pBuffer, (char *)(pBuffer + IDADE), (char *)(pBuffer + TELEFONE));
        *(int *)(pBuffer + AUX) += 1;
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
    scanf("%[^\n]%*c", (char *)(pBuffer + NOME));

    void *aux = (pBuffer + NOME);

    pBuffer = *(void **)(listaPessoas + PRIMEIRO);

    while (pBuffer != NULL){
        if (strcmp((char *)aux, pBuffer) == 0){
            printf("\nNome: %s\nIdade: %s\nTelefone: %s\n", (char *)pBuffer, (char *)(pBuffer + IDADE), (char *)(pBuffer + TELEFONE));
            return;
        }
        else{
            pBuffer = *(void **)(pBuffer + PROXIMO);
        }
    }

    printf("\nNome nao encontrado!\n");

    return;
}

void apagarIndividuo(void *pBuffer, void *listaPessoas){
    
    void *aux1;
    void *aux2 = calloc(1, sizeof(char)*20);

    //if there is no one yet
    if (*(int *)listaPessoas == 0){
        printf("\nNinguém foi cadastrado ainda.\n");
        return;
    }

    printf("\nIndivíduo a ser removido: "); scanf("%[^\n]%*c", (char *)aux2);

    pBuffer = *(void **)(listaPessoas + PRIMEIRO); 
    do{
        //if finds the right person to remove
        if(strcmp((char *)pBuffer, (char *)aux2) == 0){

            if(*(void **)(pBuffer + ANTERIOR) != NULL){
                aux1 = *(void **)(pBuffer + ANTERIOR);
                *(void **)(aux1 + PROXIMO) = *(void **)(pBuffer + PROXIMO);
            }else{
                *(void **)(listaPessoas + PRIMEIRO) = *(void **)(pBuffer + PRIMEIRO);
            }
            
            if(*(void **)(pBuffer + PRIMEIRO) != NULL){
                aux1 = *(void **)(pBuffer + PRIMEIRO);
                *(void **)(aux1 + ANTERIOR) = *(void **)(pBuffer + ANTERIOR);
            }else{
                *(void **)(listaPessoas + ULTIMO) = *(void **)(pBuffer + ANTERIOR); 
            }
   
            *(int *)listaPessoas -= 1; 
            free(pBuffer);
            free(aux2);
            return;
        } 
        
        pBuffer = *(void **)(pBuffer + PROXIMO);
    }while(pBuffer != NULL);

    printf("\nNome não encontrado.\n");
    free(aux2);
}


void limparLista(void *pBuffer, void *listaPessoas)
{
    void *aux;
    pBuffer = *(void **)(listaPessoas + PRIMEIRO);

    while (pBuffer != NULL)
    {
        aux = *(void **)(pBuffer + PROXIMO);
        free(pBuffer);
        pBuffer = aux;
    }

    return;
}

int main()
{
    void *pBuffer = (void *)calloc(1, sizeof(void **) + sizeof(int) + MAX_NOME * sizeof(char)); // Armazena na sequência -> Ponteiro para ponteiros auxiliar /
    // int para contadores e auxiliares / string auxiliar para ler nomes

    if (!pBuffer) // Testa se foi possível alocar
    {
        printf("\nErro ao alocar memória para pBuffer\n");
        return (-1);
    }
    void *listaPessoas = (void *)calloc(1, sizeof(int) + sizeof(void **) * 2); // Armazena na sequência -> int para contar pessoas(size) / Endereço primeira e endereço última pessoa

    if (!listaPessoas) // Testa se foi possível alocar
    {
        printf("\nErro ao alocar memória para ListaPessoas\n");
        return (-1);
    }

    //Inicializando contador de pessoas e ponteiros em NULL

    *(int *)listaPessoas = 0;
    *(void **)(pBuffer) = NULL;
    *(void **)(listaPessoas + PRIMEIRO) = NULL;
    *(void **)(listaPessoas + ULTIMO) = NULL;

    for (;;)
    {
        *(int *)(pBuffer + AUX) = menu(pBuffer);

        switch (*(int *)(pBuffer + AUX))
        {
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
            free(listaPessoas);
            exit(0);
            break;
        default:
            break;
        }
    }
}