#include <stdio.h>
#include <stdlib.h>
#define NOME_MAX 30

int menu(void);
void Cadastrar_Pessoa();

typedef struct{
    char nome[NOME_MAX];
    int idade;
    float altura;
}pessoa;

pessoa *ponteiro_pessoa;

int size = 0;

int main(){

    void *pBuffer;
    int escolha;

    ponteiro_pessoa = (pessoa *)malloc(size * sizeof(pessoa));

    for(;;){
        escolha = menu();
        switch (escolha){
            case 1:
                size++;
                *(int *)ponteiro_pessoa = size;
                Cadastrar_Pessoa();
                break;
            case 2:
                // listar();
                // free(pBuffer);
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
		printf("2 - sair do programa e listar adicionados.\n");
		printf("\nsua escolha: "); 
        scanf("%d", &escolha);
	}while(escolha < 1 || escolha > 5);
	getchar();

	return escolha;
}

void Cadastrar_Pessoa()
{

    int i, op, testID = 1;

  	pessoa *celulaPessoa;

    while(testID)
    {
        printf("\n\tDigite o nome do indivíduo: ");
        scanf("%[^\n]%*c", ponteiro_pessoa->nome);
        printf("\n\tDigite a idade do indivíduo: ");
        scanf("%d", &ponteiro_pessoa->idade);
        printf("\n\tDigite a altura do indivíduo: ");
        scanf("%f", &ponteiro_pessoa->altura);

        system("clear");

        printf("Revise as informações:\n");
		// Imprime_Pessoa(ponteiro_pessoa);

        do
        {
            printf("\nDeseja salvar estas informações?\n1.Sim 2.Não\n\nSua escolha: ");
            scanf("%d", &op);
            if (op < 1 || op > 2)
            {
                system("clear");
                printf("Opção inválida!\n");
            }
        }while(op < 1 || op > 2);

        if(op == 1)
        {
			printf("\n\tO indivíduo foi salvo com sucesso!\n");
            
        }
        else if(op == 2)
        {
            system("clear");
            printf("\n\tEste indivíduo não foi salvo...\n");
        }

        do
        {
            printf("\n\tDeseja cadastrar outra pessoa?\n\t1.Sim 2.Não\n\n\tSua escolha: ");
            scanf("%d", &op);
            if (op < 1 || op > 2)
            {
                system("clear");
                printf("\n\tOpção inválida!\n");
            }
        } while (op < 1 || op > 2);

        if (op == 1)
        {
            system("clear");
            testID = 1;
			getchar();
        }
        if (op == 2)
        {
            system("clear");
            testID = 0;
			getchar();
        }
    }

        system("clear");
        return;
}

// void Imprime_Todos()
// {
//     pessoa *end_aluno;
//     int i = 0, matriculas_printadas[SIZE_ALU];

//     if(opcao == 1){
//       for (ponteiro_aluno = Lista_Alunos; ponteiro_aluno->prox != NULL; ponteiro_aluno = ponteiro_aluno->prox)
//         Imprime_Aluno(ponteiro_aluno, 2);
//     }
//     else if(opcao == 0){
//     for (ponteiro_aluno = Lista_Alunos; ponteiro_aluno->prox != NULL; ponteiro_aluno = ponteiro_aluno->prox)
//     {
//         if(Esta_No_Vetor(matriculas_printadas, ponteiro_aluno->matricula) != 1)
//         {
//             matriculas_printadas[i] = ponteiro_aluno->matricula;
//             i++;
//             Imprime_Aluno(ponteiro_aluno, 0);
//             end_aluno = Busca_Alu(ponteiro_aluno->matricula, ponteiro_aluno->prox);
//             while(end_aluno != NULL)
//             {
//                 Imprime_Aluno(end_aluno, 1);
//                 end_aluno = Busca_Alu(ponteiro_aluno->matricula, end_aluno->prox);
//             }
//         }
//     }
//     }
// }

// void Imprime_Pessoa()
// {
//     pessoa *end_aluno;
//     int i = 0, matriculas_printadas[SIZE_ALU];

//     if(opcao == 1){
//       for (ponteiro_aluno = Lista_Alunos; ponteiro_aluno->prox != NULL; ponteiro_aluno = ponteiro_aluno->prox)
//         Imprime_Aluno(ponteiro_aluno, 2);
//     }
//     else if(opcao == 0){
//     for (ponteiro_aluno = Lista_Alunos; ponteiro_aluno->prox != NULL; ponteiro_aluno = ponteiro_aluno->prox)
//     {
//         if(Esta_No_Vetor(matriculas_printadas, ponteiro_aluno->matricula) != 1)
//         {
//             matriculas_printadas[i] = ponteiro_aluno->matricula;
//             i++;
//             Imprime_Aluno(ponteiro_aluno, 0);
//             end_aluno = Busca_Alu(ponteiro_aluno->matricula, ponteiro_aluno->prox);
//             while(end_aluno != NULL)
//             {
//                 Imprime_Aluno(end_aluno, 1);
//                 end_aluno = Busca_Alu(ponteiro_aluno->matricula, end_aluno->prox);
//             }
//         }
//     }
//     }
// }