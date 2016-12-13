// 02-auto-organizavel

// Luciano Gigantelli Zago - 182835

#include <stdio.h>
#include <stdlib.h>

// Estrutura dos nos da lista
struct no{
	int num;
	int cont;
	struct no *prox;
};

typedef struct no no;

// Declaracao de funcoes
no *criaL(int n);
void refazL(no *lista, int n);
int mtf(no *inicio, int n, int r, int *v);
int tr(no *lista, int n, int r, int *v);
int c(no *lista, int n, int r, int *v);
void liberaL(no *lista);

// Funcao cria lista
no *criaL(int n){

    int i;

    no *inicio=NULL, *ponteiro=NULL, *anterior=NULL;

    // Inicia com sentinela
    for(i=0; i<=n; i++){

        ponteiro = (no*) malloc(sizeof(no));

        if (!inicio) {
            inicio = ponteiro;
            anterior = inicio;

        }

        else {
        anterior->prox = ponteiro;
        anterior=ponteiro;

        }

    }

    ponteiro->prox = NULL;

    return inicio;
}

// Funcao refaz lista
void refazL(no *lista, int n){

    int i;
    no *ponteiro;

    ponteiro = lista;

    // 0 é sentinela
    for(i=0; i<=n; i++){

        ponteiro->num = i;
        ponteiro->cont = 0;
        ponteiro=ponteiro->prox;

    }

}

// Funcao Move-to-Front
int mtf(no *sentinela, int n, int r, int *v){

    no *ponteiro, *aux;
    int i, j, custo=0;

    // Procura as entradas em ordem
    for (j=0; j<r; j++) {

        ponteiro = sentinela;

        for (i=0; i<n; i++) {

        custo++;

            // Se o numero pedido ja esta no inicio, nao faz nada
            if (ponteiro==sentinela && ponteiro->prox->num == v[j])
                break;


            if (ponteiro->prox->num == v[j]){ // ponteiro é o anterior

                // Refazer ponteiros entre os nos
                aux = sentinela->prox; // salva o inicio antigo
                sentinela->prox=ponteiro->prox; // leva o novo no para o inicio
                ponteiro->prox=ponteiro->prox->prox; // liga o anterior e o prox no do retirado
                sentinela->prox->prox = aux; // liga o no 1 para o no 2

                break;

            }

            // Avanca para o proximo no na lista
            ponteiro = ponteiro->prox;

        }

    }

    return custo;
}

// Funcao Transpose
int tr(no *sentinela, int n, int r, int *v){

    no *ponteiro, *aux, *aux2;
    int i, j, custo=0;

    // Procura as entradas em ordem
    for (j=0; j<r; j++) {

        ponteiro = sentinela;

        custo++;


        for (i=0; i<n-1; i++) {

            // Se o numero pedido ja esta no inicio, nao faz nada
            if (ponteiro==sentinela && ponteiro->prox->num == v[j])
                break;

            custo++;


            if (ponteiro->prox->prox->num == v[j]){ // ponteiro é o 2 anterior

                // Refazer ponteiros entre os nos
                aux = ponteiro->prox; // salva o anterior
                aux2 = ponteiro->prox->prox->prox; // salva o proximo dos 2
                ponteiro->prox=ponteiro->prox->prox; // traz para frente o no
                ponteiro->prox->prox = aux; // liga o no encontrado com o no invertido
                ponteiro->prox->prox->prox = aux2; // liga o no invertido com o proximo

                break;

            }

            // Avanca para o proximo no na lista
            ponteiro = ponteiro->prox;

        }

    }

    return custo;
}

// Funcao Count
int c(no *sentinela, int n, int r, int *v){

    no *ponteiro, *aux, *anterior, *aux2;
    int i, j, custo=0;

        ponteiro = sentinela->prox;
        anterior = sentinela;
        aux = anterior;

    // Laco que varia a requisicao
    for (j=0; j<r; j++) {

        //custo++;
        ponteiro = sentinela->prox;
        anterior = sentinela;
        //aux = anterior;

        for (i=0; i<n; i++) {

            custo++;
           // printf("%d ", j);

            // Se encontrou aumenta a contagem e prepara para sair do laco
            if (ponteiro->num == v[j]) {
                (ponteiro->cont)++;

                if (aux->cont >= anterior->cont) {

                    aux = anterior;
                }

                // Se foi o primeiro nao faz nada
                if (ponteiro == sentinela->prox) { }



                else if (anterior->cont <= ponteiro->cont) {

                    aux2 = ponteiro->prox;
                    ponteiro->prox = aux->prox;
                    aux->prox = ponteiro;
                    anterior->prox = aux2;

                }

                // Sai do laco se completa mudanca de nos
                break;

            }

        // Avanca para o proximo no na lista
        anterior = ponteiro;
        ponteiro = ponteiro->prox;

        }
    }

    return custo;
}

// Funcao libera lista
void liberaL(no *lista){

    no *ponteiro, *aux;

    ponteiro  = lista;

    while (ponteiro){
        aux = ponteiro;
        ponteiro=ponteiro->prox;
        free (aux);


    }

}

void imprime (no *sentinela){

    no *ponteiro;

    ponteiro = sentinela->prox;

    printf ("IMPRIME: ");

    while (ponteiro){

        printf ("%d ", ponteiro->num);
        printf ("%d ", ponteiro->cont);


        ponteiro = ponteiro->prox;
    }

    printf("\n");

}


int main(void){

    int n, r, i, j, custo[3];

    // Apontador para a lista
    no *lista;

    // Leitura entrada
    scanf("%d\n%d", &n, &r);

    int v[r];

    // Leitura entrada (salva no vetor)
    for (i=0; i<r; i++) {
        scanf(" %d", &v[i]);
    }

    // Cria a lista
    lista = criaL(n);


    // Insere os numeros na lista
    refazL(lista, n);



    //imprime(lista);
    // Calculo custo Move-to-Front
    custo[0] = mtf(lista, n, r, v);
    //imprime(lista);
    refazL(lista, n);

    // Calculo custo Transpose
    custo[1] = tr(lista, n, r, v);
    //imprime(lista);


    refazL(lista, n);

    // Calculo custo Count
    custo[2] = c(lista, n, r, v);
    //imprime(lista);


    // Desaloca a lista
    liberaL(lista);


    // Imprime saida
    printf("%d %d %d\n", custo[0], custo[1], custo[2]);


    return 0;
}
