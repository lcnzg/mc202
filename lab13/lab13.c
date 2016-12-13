// Luciano Gigantelli Zago - 182835
// Lab 13 - Ordenacao: comparacao

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COMP(a, b) (((a) - (b)) == 0 ? 0 : (((a) - (b)) / abs((a) - (b))))

int compar (const void * a, const void * b) {
  if ( *(int*)a <  *(int*)b ) return -1;
  if ( *(int*)a >  *(int*)b ) return 1;
  return 0;
}


void BubbleSort(int vetor[], int n) {
    int c, d, t;

    for (c = 0 ; c < ( n - 1 ); c++) {
        for (d = 0 ; d < n - c - 1; d++) {
            if (vetor[d] > vetor[d+1]) {
                /* Trocas */
                t = vetor[d];
                vetor[d] = vetor[d+1];
                vetor[d+1] = t;
            }
        }
    }
}


void ShellSort(int *vet, int size) {
    int i , j , value;
    int gap = 1;
    while(gap < size) {
        gap = 3*gap+1;
    }
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < size; i++) {
            value = vet[i];
            j = i - gap;
            while (j >= 0 && value < vet[j]) {
                vet [j + gap] = vet[j];
                j -= gap;
            }
            vet [j + gap] = value;
        }
    }
}

void InsertionSort(int original[], int length)
{
	int i, j, atual;

	for (i = 1; i < length; i++)
	{
		atual = original[i];
		j = i - 1;

		while ((j >= 0) && (atual < original[j]))
		{
			original[j + 1] = original[j];
            j = j - 1;
		}

		original[j + 1] = atual;
	}

	return;
}

void RadixSort(int vetor[], int tamanho) {
    int i;
    int *b;
    int maior = vetor[0];
    int exp = 1;

    b = (int *)calloc(tamanho, sizeof(int));

    for (i = 0; i < tamanho; i++) {
        if (vetor[i] > maior)
    	    maior = vetor[i];
    }

    while (maior/exp > 0) {
        int bucket[10] = { 0 };
    	for (i = 0; i < tamanho; i++)
    	    bucket[(vetor[i] / exp) % 10]++;
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
    	for (i = tamanho - 1; i >= 0; i--)
    	    b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
    	for (i = 0; i < tamanho; i++)
    	    vetor[i] = b[i];
    	exp *= 10;
    }

    free(b);
}

// 1: crescente / 0: desordenado / -1: crescente
int verifica_ordem(int v[], int n) {
   int i, state = 0;

   for (i = 1; i < n; ++i) {
       if (state == 0)
           state = COMP(v[i-1], v[i]);
       else if (COMP(v[i-1], v[i]) != 0 && state != COMP(v[i-1], v[i]))
           return 0;
   }

   return state;
}

int main (void){

    int i, j, k, n=0, *vetor;
    clock_t tempo=0;

    printf("Insira o numero de entradas: ");
    scanf("%d", &n);
 printf("Tipo de ordenacao:\n1-Insertion / 2-Bubble / 3-Shell / 4-Radix / 5-Quick\n");
    scanf("%d", &i);
    for (j=0; j<5; j++){
    vetor = malloc(n*sizeof(int));

    srand(77);

    // Preenche o vetor randomico
    for (k=0; k< n; k++)
        vetor[k] = rand();



    if(i==1){

        tempo = clock();
        InsertionSort(vetor, n);
        tempo = clock() - tempo;
    }

    else if (i==2){

        tempo = clock();
        BubbleSort(vetor, n);
        tempo = clock() - tempo;
    }

        else if (i==3){

        tempo = clock();
        ShellSort(vetor, n);
        tempo = clock() - tempo;
    }
        else if (i==4){

        tempo = clock();
        RadixSort(vetor, n);
        tempo = clock() - tempo;
    }
        else if (i==5){

        tempo = clock();
        qsort(vetor, n, sizeof(int), compar);
        tempo = clock() - tempo;
    }

    printf("A funcao foi executada em %.3lf segundos\n", ((double)tempo)/CLOCKS_PER_SEC);

    // Verifica ordenacao
   switch (verifica_ordem(vetor, n)) {
       case 1:
           printf("O vetor esta ordenado por ordem decrescente\n");
           break;
       case 0:
           printf("O vetor nao esta ordenado ou tem menos que dois elementos\n");
           break;
       case -1:
           printf("O vetor esta ordenado por ordem crescente\n");
           break;
       default:
           printf("Valor de retorno inesperado\n");
           break;
   }

   free(vetor);
    }
    return 0;
}
