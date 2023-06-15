
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "funcoesAuxiliares.h"
#include "arvore.h"
#include "desempenho.h"
#define min(a, b) ((a) < (b) ? (a) : (b))

void insertion_sort_tim(int *arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Função auxiliar para mesclagem de dois subarrays ordenados
void merge_tim(int *arr, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    int left[len1], right[len2];
    for (int i = 0; i < len1; i++){
        left[i] = arr[l + i];
    }
    for (int i = 0; i < len2; i++){
        right[i] = arr[m + 1 + i];
    }
    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < len2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

//Função principal Timsort
void timsort(int arr, int n) {
    const int RUN = 32;
    for (int i = 0; i < n; i += RUN){
        insertion_sort_tim(arr, i, min(i + RUN - 1, n - 1));
    }

    for (int size = RUN; size < n; size = 2 * size){
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);
            merge_tim(arr, left, mid, right);
        }
    }
}

void bubbleSort(int *vetor, int n){
    int i, continua, aux, fim = n;

    do{
        continua = 0;
        for(i = 0; i < fim - 1; i++){
            if(vetor[i] > vetor[i + 1]){
                aux = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = aux;
                continua = i;
            }
        }
        fim--;
    } while(continua != 0);
}

void insertionSort(int *vetor, int n){
    int i, j, aux;
    for(i = 1; i < n; i++){
        aux = vetor[i];
        for(j = i; (j > 0) && (aux < vetor[j - 1]); j--){
            vetor[j] = vetor[j - 1];
        }
        vetor[j] = aux;
    }
}


void selectionSort(int *vetor, int n){
    int i, j, menor, troca;
    for(i = 0; i < n - 1; i++){
        menor = i;
        for(j = i + 1; j < n; j++){
            if(vetor[j] < vetor[menor]){
                menor = j;
            }
        }
        if(i != menor){
            troca = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = troca;
        }
    }
}

void shellSort(int *vetor, int n){
    int i, j;
    int h = 1;
    int aux;
    int ps = 1;

    do h = h * 3 + 1;

    while(h < n);
    do{
        h /= 3; /* h = (h - 1) / 3 */
        for(i = h; i < n; i++){
            aux = vetor[i];
            j = i;
            while(vetor[j - h] > aux){
                vetor[j] = vetor[j - h];
                j -= h;
                if(j < h) break;
            }
            vetor[j] = aux;
            printf("\n");
        }

    } while(h != 1);
}


void radixSort_lsd(int *vetor, int n) {
    int max_num = vetor[0];
    for (int i = 1; i < n; i++) {
        if (vetor[i] > max_num) {
            max_num = vetor[i];
        }
    }

    int exp = 1;

    while (max_num / exp > 0) {
        // Cria buckets para cada dígito (0-9)
        int buckets[10][n];
        int bucket_sizes[10] = {0};

        // Coloca cada número na lista em seu bucket correspondente
        for (int i = 0; i < n; i++) {
            int digit = (vetor[i] / exp) % 10;
            buckets[digit][bucket_sizes[digit]] = vetor[i]; bucket_sizes[digit]++;
        }

        // Reconstroi a lista ordenada pelos dígitos atuais
        int k = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < bucket_sizes[i]; j++) {
                vetor[k] = buckets[i][j]; k++;
            }
        }

        // Incrementa o dígito em 10 vezes para a próxima iteração
        exp *= 10;
    }

}

void quickSort(int *vetor, int inicio, int fim) {
    int pivo;

    if(fim > inicio) {
        pivo = particiona(vetor, inicio, fim);
        quickSort(vetor, inicio, pivo-1);
        quickSort(vetor, pivo+1, fim);
    }
}

int particiona(int *vetor, int inicio, int fim) {
    int esquerda, direita, pivo, aux;

    esquerda = inicio;
    direita = fim;
    pivo = vetor[inicio];
    while(esquerda < direita) {
        while(vetor[esquerda] <= pivo)
            esquerda++;
        while(vetor[direita] > pivo)
            direita--;
        if(esquerda < direita) {
            aux = vetor[esquerda];
            vetor[esquerda] = vetor[direita];
            vetor[direita] = aux;
        }
    }
    vetor[inicio] = vetor[direita];
    vetor[direita] = pivo;

    return direita;
}
void merge(int arr[], int l, int m, int r)
	{
    	// O vetor original foi dividido em duas partes
    	// Vetor esquerdo e direito
    	int len1 = m - l + 1, len2 = r - m;
    	int left[len1], right[len2];
    	for (int i = 0; i < len1; i++)
        	left[i] = arr[l + i];
    	for (int i = 0; i < len2; i++)
        	right[i] = arr[m + 1 + i];
    	int i = 0;
    	int j = 0;
    	int k = l;
    	// Depois de comparar, n�s mesclamos dois vetores
    	// em um subvetor maior
    	while (i < len1 && j < len2)
    	{
        	if (left[i] <= right[j])
        	{
            	arr[k] = left[i];
            	i++;
        	}
        	else
        	{
            	arr[k] = right[j];
            	j++;
        	}
        	k++;
    	}
    	// Copia os elementos que restaram para a esquerda, caso existam
    	while (i < len1)
    	{
        	arr[k] = left[i];
        	k++;
        	i++;
    	}
    	// copia os elementos que restaram para a direita, caso existam
    	while (j < len2)
    	{
        	arr[k] = right[j];
        	k++;
        	j++;
    	}
	}

void mergeSort(int arr[], int inicio, int fim)
{
    if (inicio < fim)
    {
        // Encontra o ponto médio para dividir o array em duas metades
        int meio = inicio + (fim - inicio) / 2;

        // Ordena a primeira e a segunda metade
        mergeSort(arr, inicio, meio);
        mergeSort(arr, meio + 1, fim);

        // Mescla as duas metades ordenadas
        merge(arr, inicio, meio, fim);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n-1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}


