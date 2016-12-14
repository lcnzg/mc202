// Lab 05 - Vetor de bits
// Luciano Gigantelli Zago - 182835


// Bibliotecas utilizadas
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Macros para manipular bits
#define bit_set(A,i) ((A)[bit_slot(i)] |= bit_mask(i))
#define bit_clear(A,i) ((A)[bit_slot(i)] &= bit_mask(i))
#define bit_test(A,i) ((A)[bit_slot(i)] & bit_mask(i))
#define bit_slot(i) ((i) / CHAR_BIT)
#define bit_nslots(n) ((n) / CHAR_BIT + 1)
#define bit_mask(i) (1 << ((i) % CHAR_BIT))


// Funcao criar vetor de bits OK
unsigned char* create(unsigned char* vetor, int n){
	
	unsigned char* ponteiro;
	
	if (vetor)		
		free(vetor);
	
	
	ponteiro = calloc(bit_nslots(n), sizeof(unsigned char));
			
	return ponteiro;
	
}


// Funcao adicionar elemento ao vetor OK
void add(unsigned char* vetor, int i, int n){
	
	bit_set(vetor, i);	
	
	return;
	
}

// Funcao remover elemento do vetor OK
void remover(unsigned char* vetor, int i, int n){
	
	bit_clear(vetor, i);
		
	return;
	
}

// Funcao verificar se elemento esta contido no vetor OK
void in(unsigned char* vetor, int i, int n){
			
	if (bit_test(vetor, i))
		printf("belongs(%d) = true", i);
	
	else
		printf("belongs(%d) = false", i);
	
	return;
	
}

// Funcao que encontra o elemento e imprime quantidade de elementos anteriores OK
void rank(unsigned char* vetor, int i, int n){
			
	if (i>n)
		return;
			
	for (j=0; j<=i; j++){
		
		if (bit_test(vetor, j))
			j++;		
		
		}
		
	printf("rank(%d) = %d", j);	
	
	return;
	
	}


// Funcao que encontra e imprime elemento
void select(unsigned char* vetor, int i, int n){
	
	int j;
	
	
	if (i>n)
		return;
	
	
	
	
	
	bit_test(vetor, pow(2, i));
	
	
	
	
	printf("select(%d) = %d", i, v);
	
	return;
	
}

// Funcao que imprime o numero de elementos em um intervalo
void rangecount(unsigned char* vetor, int j, int k, int n){
	
	int c;
	
	// Procura primeiro elemento
	
	
	
	
	
	
	
	
	
	// Percorre ate o ultimo elemento
	
	
	
	printf("rangecount(%d,%d) = %d", j, k, c);
	
	return;
	
}

// Funcao que imprime todos os elementos
void print(unsigned char* vetor, int n){
	
	
	
	return;
	
}


int main(void){
	
	unsigned char *vetor = NULL;
	int n, i, j;
	int tuChar;
	
	char comando[11];
	
	tuChar = sizeof(unsigned char);

	while(1) {

		// Le e chama os comandos em um loop
		scanf(" %s", comando);

	if (strcmp(comando, "create") == 0) {
		
		scanf(" %d", &n);
		
		vetor = create(vetor, n);
		
		}
	
	else if (strcmp(comando, "add") == 0) {
		
		scanf(" %d", &i);
		add(vetor, i, n);
		
		}
		
	else if (strcmp(comando, "remove") == 0) {
		
		scanf(" %d", &i);
		remover(vetor, i, n);
		
		}
		
	else if (strcmp(comando, "in") == 0) {
		
		scanf(" %d", &i);
		in(vetor, i, n);
		
		}
		
	else if (strcmp(comando, "rank") == 0) {
		
		scanf(" %d", &i);
		rank(vetor, i, n);
		
		}		

	
	else if (strcmp(comando, "select") == 0) {
		
		scanf(" %d", &i);
		select(vetor, i, n);
		
		}
		
	else if (strcmp(comando, "rangecount") == 0) {
		
		scanf(" %d %d", &i, &j);
		rangecount(vetor, i, j, n);
		
		}
		
	else if (strcmp(comando, "print") == 0) {
		
		print(vetor, n);
		
		}
		
	else if (strcmp(comando, "exit") == 0) {
		
		free(vetor);
		break;
		
		
		}
	}
	
	return 0;
}
