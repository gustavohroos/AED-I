#include <stdio.h>
#include <stdlib.h>
#include <time.h> //clock(), CLOCKS_PER_SEC e clock_t

void insertionSort(int *vetor, int n);
void selectionSort(int *vetor, int n);
void quickSort(int *vetor, int esquerda, int direita);
void mergeSort(int *vetor, int esquerda, int direita);
void merge(int *vetor, int inicio, int meio, int fim);
void printarVetor(int *vetor, int n);
void verificar(int *vetor, int n);
void swap(int *primeiro, int *segundo);

int main(){
    int *vetorInsertionSort, *vetorSelectionSort, *vetorMergeSort,
    *vetorQuickSort;
    int n;
    clock_t t;

    printf("Digite o valor de n (tamanho do vetor): ");
    scanf("%d", &n);

    vetorInsertionSort = (int *)calloc(sizeof(int), n);
    vetorSelectionSort = (int *)calloc(sizeof(int), n);
    vetorMergeSort = (int *)calloc(sizeof(int), n);
    vetorQuickSort = (int *)calloc(sizeof(int), n);

    srand(time(NULL));

    for(int i = 0; i < n; i++){
        vetorInsertionSort[i] = rand() % 100;
        vetorSelectionSort[i] = vetorInsertionSort[i];
        vetorMergeSort[i] = vetorInsertionSort[i];
        vetorQuickSort[i] = vetorInsertionSort[i];
    }

    if(n <= 100){
        printf("Vetor: ");
        printarVetor(vetorInsertionSort, n);
    }
    
    //Insertion sort
    t = clock(); //armazena tempo
    insertionSort(vetorInsertionSort, n);
    t = clock() - t; //tempo final - tempo inicial
    printf("\nTempo gasto Insertion Sort: %.8lf milissegundos\n", ((double)t)/((CLOCKS_PER_SEC)/1000));
    verificar(vetorInsertionSort, n);
    free(vetorInsertionSort);

    //Selection sort
    t = clock(); //armazena tempo
    selectionSort(vetorSelectionSort, n);
    t = clock() - t; //tempo final - tempo inicial
    printf("\nTempo gasto Selection Sort: %.8lf milissegundos\n", ((double)t)/((CLOCKS_PER_SEC)/1000));
    verificar(vetorSelectionSort, n);
    free(vetorSelectionSort);

    //Quick sort
    t = clock(); //armazena tempo
    quickSort(vetorQuickSort, 0, (n - 1));
    t = clock() - t; //tempo final - tempo inicial
    printf("\nTempo gasto Quick Sort: %.8lf milissegundos\n", ((double)t)/((CLOCKS_PER_SEC)/1000));
    verificar(vetorQuickSort, n);
    free(vetorQuickSort);

    //Merge sort
    t = clock(); //armazena tempo
    mergeSort(vetorMergeSort, 0, (n - 1));
    t = clock() - t; //tempo final - tempo inicial
    printf("\nTempo gasto Merge Sort: %.8lf milissegundos\n", ((double)t)/((CLOCKS_PER_SEC)/1000));
    verificar(vetorMergeSort, n);
    free(vetorMergeSort);
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
        for(int i = 1; i < n; i++){
            if(vetor[i - 1] > vetor[i]){
                printf("---------- Vetor não ordenado\n");
                return;
            }
        }
    }
    printf("---------- Vetor está ordenado\n");

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
        swap(&vetor[aux2], &vetor[i]);
    }
}

void quickSort(int *vetor, int inicio, int fim){

    int pivo, aux;
    int i = inicio;
    int j = fim;

    pivo = vetor[(inicio + fim) / 2];
    do{
        while (vetor[i] < pivo){
            i++;
        }
        while (pivo < vetor[j]){
            j--;
        }

        if(i <= j){
            swap(&vetor[i], &vetor[j]);
            i++;
            j--;
        }
        
    } while (i <= j);
    if(inicio < j){
        quickSort(vetor, inicio, j);
    }
    if(i < fim){
        quickSort(vetor, i, fim);
    }
    


}

void mergeSort(int *vetor, int esquerda, int direita){

    if(esquerda < direita){
        int pivo = (esquerda + (direita - esquerda) / 2);
        mergeSort(vetor, esquerda, pivo);
        mergeSort(vetor, pivo + 1, direita);
        merge(vetor, esquerda, pivo, direita);
    }
}

void merge(int *vetor, int esquerda, int pivo, int direita){

    int *aux, auxEsquerda, auxDireita, tam, j, k;
    int fim1 = 0, fim2 = 0;
    tam = direita - esquerda + 1;
    auxEsquerda = esquerda;
    auxDireita = pivo + 1;
    aux = (int *)calloc(sizeof(int), tam);

    if(aux != NULL){
        for(int i = 0; i < tam; i++){
            if(!fim1 && !fim2){
                if(vetor[auxEsquerda] < vetor[auxDireita]){
                    aux[i] = vetor[auxEsquerda + 1];
                }
                else{
                    aux[i] = vetor[auxDireita + 1];
                }
                if(auxEsquerda > pivo){
                    fim1 = 1;
                }
                if(auxDireita > direita){
                    fim2 = 1;
                }
            }
            else{
                if(!fim1){
                    aux[i] = vetor[auxEsquerda + 1];
                }
                else{
                    aux[i] = vetor[auxDireita + 1];
                }
            }
        }
        for(j = 0, k = esquerda; j < tam; j++, k++){
            vetor[k] = aux[j];
        }
    }
    free(aux);
}

void swap(int *primeiro, int *segundo){ 
    int aux = *primeiro;
    *primeiro = *segundo;
    *segundo = aux;
}