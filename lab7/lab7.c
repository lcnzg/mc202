// Luciano Gigantelli Zago - RA: 182835

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct no
typedef struct no{

	char dado;
	struct no* dir;
	struct no* esq;

} no;

// Constroi a arvore a partir de 2 vetores
no* construir(char* pre, char* em, int* p, int iEm, int fEm){

	// Variavel local que percorre vetor em-ordem
	int e = 0;

	// Final negativo ou final menor que o inicio, retorna
	if(fEm < 0 || fEm < iEm)
		return NULL;

	// Atribui o valor do no atraves da pre-ordem
	no *ponteiro = (no*)malloc(sizeof(no));
	ponteiro->dado = pre[*p];
	(*p)++;

	// Se ja percorreu todos os filhos, filhos sao nulo e retorna ponteiro
	if(iEm == fEm) {

		ponteiro->dir = NULL;
		ponteiro->esq = NULL;
		return ponteiro;
	}

	// Se nao percorreu todos os filhos, procura a posicao no vetor em-ordem
	else while (1) {

		if (ponteiro->dado == em[e])
			break;

		e++;
	}

	// Constroe os filhos da esquerda e da direita, separando as listas sempre em 2
	ponteiro->esq = construir(pre, em, p, iEm, e-1);
	ponteiro->dir = construir(pre, em, p, e+1, fEm);

	return ponteiro;
}

// Imprime a arvore em pos-ordem
void impPos (no* ponteiro){

	if(ponteiro) {

        impPos(ponteiro->esq);
        impPos(ponteiro->dir);
        printf("%c", ponteiro->dado);
    }

	return;
}

// Imprime a arvore em largura
void impLargura(no* raiz, int tam) {

    int fim, inic;

    // Cria uma fila de ponteiros para os nos
    no** fila = (no**)malloc(sizeof(no*)*tam);

    // A raiz inicia a fila
    fila[0] = raiz;

    // Laco para imprimir, depositar e acessar os ponteiros para os nos na fila
    for(fim=0, inic=0; inic<tam; inic++) {

        printf("%c", fila[inic]->dado);

        // Se os filhos nao forem nulos, entram na fila

        if (fila[inic]->esq)
                fila[++fim] = fila[inic]->esq;

        if (fila[inic]->dir)
                fila[++fim] = fila[inic]->dir;
    }

    // Libera a fila
    free(fila);

    return;
}

// Libera a arvore
void liberar(no *ponteiro){

	if (ponteiro) {

        liberar(ponteiro->esq);
        liberar(ponteiro->dir);
        free(ponteiro);
	}

	return;
}

int main (void){

	char buffer1[53], buffer2[53];
	no* arvore;
	int tam = 0, p;

	// Loop para verificar todas as entradas
	while (1) {

		// Sai do loop se chegar ao final do arquivo
		if (scanf(" %s %s", buffer1, buffer2) < 0)
			break;

		// Calcula a quantidade de nos atraves da entrada (inicia no 0)
		tam = strlen(buffer1)-1;

		// Variavel utilizada para manter a posicao da lista em pre-ordem das chamadas recursivas
		p = 0;

		// Constroi a arvore
		arvore = construir(buffer1, buffer2, &p, 0, tam);

		// Imprime e libera a arvore
		impPos(arvore);
		printf(" ");
		impLargura(arvore, tam+1);
		printf("\n");
		liberar(arvore);
	}

	return 0;
}
