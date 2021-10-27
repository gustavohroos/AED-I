#include <stdio.h>
#include <time.h> //clock(), CLOCKS_PER_SEC e clock_t

void insertion_sort(int *vetor, int n);
void selection_sort(int *vetor, int n);
void quick_sort(int *vetor, int ladoEsq, int ladoDir);
void merge_sort(int *vetor, int inicio, int fim);
void merge(int *vetor, int inicio, int meio, int fim);