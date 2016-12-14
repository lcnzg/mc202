// Luciano Gigantelli Zago - 182835

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct no{

	struct no* esq;
	struct no* dir;
	int dado;
	float pesoEsq;
	float pesoDir;
};

typedef struct no no;

no* inserir(){

    char values[50];
    int p=0, t, i;
	char c , *pos1, *pos2;

	pos1 = values;

	no* ponteiro = NULL;

	c = getchar();

    if (c == ')')
            return NULL;

	// Cria subarvore esquerda e chama recursao
    ponteiro = (no*)malloc(sizeof(no));
    ponteiro->esq = inserir();
    ponteiro->pesoEsq = 0;
    ponteiro->pesoDir = 0;

	// Le os valores e pesos dos nos em uma string




    scanf("%50[^(]", values);
/*

    t = strlen(num);

    // Conta o numero de ':'
   for(i=0; i<t; i++){

        if (num[i] == ':')
            p++;
   }

    if (ponteiro->esq)
        ponteiro->pesoEsq = strtof(num, &pos1);

    if (p==0)
        ponteiro->dado = (int)strtof(num, NULL);

    else if (!ponteiro->esq)
        ponteiro->dado = (int)strtof(pos1, &pos2);

    if ((p==1 && !ponteiro->esq) || (p==2))
        ponteiro->pesoDir = strtof(pos2, NULL);

*/
c = getchar();
	if (c == '(') {
		ponteiro->dir = inserir();
	}

    if(ponteiro->esq && ponteiro->dir)
        sscanf(values, "%f:%d:%f", &ponteiro->pesoEsq, &ponteiro->dado, &ponteiro->pesoDir);

    else if(ponteiro->esq)
        sscanf(values, "%f:%d", &ponteiro->pesoEsq, &ponteiro->dado);

    else if(ponteiro->dir)
        sscanf(values, "%d:%f", &ponteiro->dado, &ponteiro->pesoDir);

    else
        sscanf(values, "%d", &ponteiro->dado);


    c = getchar();

	if (c == ')')
		return ponteiro;

}

float pesoMax(no* ponteiro){

    float pesoE = 0, pesoD = 0;

    if (!ponteiro)
        return 0;

    pesoE = ponteiro->pesoEsq + pesoMax(ponteiro->esq);

    pesoD = ponteiro->pesoDir + pesoMax(ponteiro->dir);

   if (pesoE>=pesoD)
        return pesoE;

    else
        return pesoD;
}

void liberar(no* ponteiro){

    if (ponteiro) {

		liberar(ponteiro->esq);
		liberar(ponteiro->dir);
		free(ponteiro);
    }

    return;
}

// Imprime a arvore em ordem
int impEm(no * ponteiro, int r) {

    // Se a arvore estiver vazia, retorna 0
    if (!ponteiro && r==0)
        return 0;

    if (ponteiro) {

		impEm(ponteiro->esq, 1);
		printf("%d ", ponteiro->dado);
		impEm(ponteiro->dir, 1);
    }

    return 1;
}

int main (void){

	float peso=0;
	char c;
    no* raiz = NULL;

	while (1){

        c = getchar();

        if (c == EOF)
            break;

        raiz = inserir();

        peso = pesoMax(raiz);

        printf("%.3f\n", peso);

        	if (impEm(raiz, 0))
                printf("\n");

            else
                printf("vazia\n");


        liberar(raiz);

        getchar();

	}

	return 0;
}
