#include <stdio.h>
#include <stdlib.h>
#include <time.h> //clock(), CLOCKS_PER_SEC e clock_t

void insertionSort(int *vetor, int n);
void selectionSort(int *vetor, int n);
void quickSort(int *vetor, int ladoEsq, int ladoDir);
void mergeSort(int *vetor, int inicio, int fim);
void merge(int *vetor, int inicio, int meio, int fim);
void printarVetor(int *vetor, int n);
void verificar(int *vetor, int n);

int main(){
    int *vetorInicial, *vetorInsertionSort, *vetorSelectionSort, *vetorMergeSort,
    *vetorQuicksort;
    int n;
    clock_t t;

    printf("Digite o valor de n (tamanho do vetor): ");
    scanf("%d", &n);


    vetorInicial = (int *)malloc(sizeof(int) * n);
    vetorInsertionSort = (int *)malloc(sizeof(int) * n);
    vetorSelectionSort = (int *)malloc(sizeof(int) * n);
    vetorMergeSort = (int *)malloc(sizeof(int) * n);
    vetorQuicksort = (int *)malloc(sizeof(int) * n);

    srand(time(NULL));

    for(int i = 0; i < n; i++){
        vetorInicial[i] = rand() % 100;
        vetorInsertionSort[i] = vetorInicial[i];
        vetorSelectionSort[i] = vetorInicial[i];
        vetorMergeSort[i] = vetorInicial[i];
        vetorQuicksort[i] = vetorInicial[i];
    }

    verificar(vetorInicial, n);

    if(n <= 100){
        printf("Vetor: ");
        printarVetor(vetorInicial, n);
    }
    
    //Insertion sort
    t = clock(); //armazena tempo
    insertionSort(vetorInsertionSort, n);
    t = clock() - t; //tempo final - tempo inicial
    printf("\nTempo gasto Insertion Sort: %.8lf milissegundos\n", ((double)t)/((CLOCKS_PER_SEC)/1000));
    verificar(vetorInsertionSort, n);
    

    //Selection sort
    t = clock(); //armazena tempo
    selectionSort(vetorSelectionSort, n);
    t = clock() - t; //tempo final - tempo inicial
    printf("\nTempo gasto Selection Sort: %.8lf milissegundos\n", ((double)t)/((CLOCKS_PER_SEC)/1000));
    verificar(vetorSelectionSort, n);

    //Quick sort
    t = clock(); //armazena tempo
    quickSort(vetorQuicksort, 0, (n - 1));
    t = clock() - t; //tempo final - tempo inicial
    printf("\nTempo gasto Quick Sort: %.8lf milissegundos\n", ((double)t)/((CLOCKS_PER_SEC)/1000));
    verificar(vetorQuicksort, n);

    //Merge sort
    t = clock(); //armazena tempo
    mergeSort(vetorMergeSort, 0, (n - 1));
    t = clock() - t; //tempo final - tempo inicial
    printf("\nTempo gasto Merge Sort: %.8lf milissegundos\n", ((double)t)/((CLOCKS_PER_SEC)/1000));
    verificar(vetorMergeSort, n);

    free(vetorInicial);
	free(vetorInsertionSort);
	free(vetorSelectionSort);
	free(vetorMergeSort);
	free(vetorQuicksort);

	return 0;
}

void printarVetor(int *vetor, int n){
    printf("[");
    for(int i= 0; i < n; i++){
        if (i < n - 1){
            printf("%d, ", vetor[i]);
        }
        else{
            printf("%d", vetor[i]);
        }
    }
    printf("]\n");      
}

void verificar(int *vetor, int n){

    if(n > 1){
        for(int i = 0; i < n; i++){
            if(vetor[i - 1] > vetor[i]){
                printf("---------- Vetor não ordenado\n");
                return;
            }
        }
        printf("---------- Vetor está ordenado\n");
        return;
    }

}

void insertionSort(int *vetor, int n){
    int aux = 0, j =  0;

    for(int i = 1; i < n; i++){
        aux = vetor[i];
        for(j = i; ((j > 0) && (aux < vetor[j - 1])); j--){
            vetor[j] = vetor[j - 1];
        }
        vetor[j] = aux;
    }
}

void selectionSort(int *vetor, int n){
    int aux1, aux2; //aux2 = menor valor

    for(int i = 0; i < (n - 1); i++){
        aux2 = i;
        for (int j = (i + 1); j < n; j++){
            if(vetor[j] < vetor[aux2]){
                aux2 = j;
            }
        }
        if(i != aux2){
            aux1 = vetor[i];
            vetor[i] = vetor[aux2];
            vetor[aux2] = aux1;
        }
    }
}

void quickSort(int *vetor, int ladoEsq, int ladoDir){


}
void mergeSort(int *vetor, int inicio, int fim){


}
void merge(int *vetor, int inicio, int meio, int fim){


}
