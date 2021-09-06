#include <stdio.h>
#include <stdlib.h>
#define NOME_MAX 30

typedef struct
{
    char nome[NOME_MAX];
    int idade;
    float altura;
} pessoa;

int main()
{

    pessoa *ponteiro_pessoa;

    int size = 0, escolha, i;

    ponteiro_pessoa = (pessoa *)calloc(1, sizeof(pessoa));

    do
    {
        printf("\n\t#####__ARMAZENANDO INFORMAÇÕES__#####");
        printf("\n\tDigite o nome do indivíduo: ");
        scanf("%[^\n]%*c", (ponteiro_pessoa + size)->nome); // "%[^\n]%*c" para adicionar nomes compostos
        printf("\n\tDigite a idade do indivíduo: ");
        scanf("%d", &(ponteiro_pessoa + size)->idade);
        printf("\n\tDigite a altura do indivíduo: ");
        scanf("%f", &(ponteiro_pessoa + size)->altura);
        size++;
        printf("\n\tDeseja adicionar mais alguém?\n\t1 - Sim 2 - Não\n\tSua escolha: ");
        scanf("%d", &escolha);
        getchar();

        if (escolha == 1)
        {
            ponteiro_pessoa = (pessoa *)realloc(ponteiro_pessoa, sizeof(pessoa) * (size + 1));
        }

    } while (escolha == 1);

    for (i = 0; i < size; i++)
    {
        printf("\n\tIndivíduo[%d]:\tNome: %s\tIdade: %d\tAltura: %.2f\n\n", i,
               (ponteiro_pessoa + i)->nome, (ponteiro_pessoa + i)->idade, (ponteiro_pessoa + i)->altura);
    }

    free(ponteiro_pessoa);
    return 0;
}