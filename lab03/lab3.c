// Lab 03 - Lista simetrica
// Luciano Gigantelli Zago - 182835

#include <stdio.h>
#include <stdlib.h>

typedef struct no {

	double valor;
	struct no* a;
	struct no* b;

} no;

// Funcao que cria lista inicial com sentinelas de inicio e fim
no* criarL(){

    no* inicio = (no*)malloc(sizeof(no));
    no* fim = (no*)malloc(sizeof(no));

    inicio->valor = -1;
    fim->valor = -1;
    inicio->b = NULL;
    inicio->a = fim;
    fim->b = inicio;
    fim->a = NULL;

    return inicio;
}

// Funcao que insere o no em uma posicao especifica
no* inserir(no* lista, int pos, double v){

    int i;
    no* anterior = lista;
	no* ponteiro = lista->a;

	// Encontra a posicao
	for(i=0; i<pos; i++){

        // Se chegar no fim da lista para e insere no fim
        if (!ponteiro->a)
            break;

        // Muda para o proximo no
		if (ponteiro->a == anterior) {
            anterior = ponteiro;
            ponteiro = ponteiro->b;
		}

		else if (ponteiro->b == anterior) {
            anterior = ponteiro;
            ponteiro = ponteiro->a;
		}

	}

	no* aux = (no*)malloc(sizeof(no));

	if (anterior->a == ponteiro)
        anterior->a = aux;

        else
            anterior->b = aux;

    if (ponteiro->a == anterior)
        ponteiro->a = aux;

        else
            ponteiro->b = aux;

    aux->a = ponteiro;
    aux->b = anterior;
    aux->valor = v;

	}

// Funcao que imprime a lista
void imprimir(no* lista){

	no *ponteiro, *anterior;

	ponteiro = lista->a;
	anterior = lista;

	while(ponteiro->a && ponteiro->b){

		printf("%.4lf ", ponteiro->valor);

		// Muda para o proximo no
		if (ponteiro->a == anterior) {
            anterior = ponteiro;
            ponteiro = ponteiro->b;
		}

		else if (ponteiro->b == anterior) {
            anterior = ponteiro;
            ponteiro = ponteiro->a;
		}

	}

	printf("\n");

	}

// Funcao que reverte um trecho da lista
void reverter(no* lista, int pInic, int pFin){

    int i;
    no* anterior, *ponteiro, *aux1, *posterior, *aux2;

    anterior=lista;
    ponteiro = lista->a;

    // Procura a posicao inicial
    for (i=0; i<pInic; i++) {

        // Muda para o proximo no
		if (ponteiro->a == anterior) {
            anterior = ponteiro;
            ponteiro = ponteiro->b;
		}

            else {
                anterior = ponteiro;
                ponteiro = ponteiro->a;
		}
    }

    aux1 = ponteiro;

    aux2 = lista;
    posterior = lista->a;

    // Procura a posicao final
    for (i=0; i<=pFin; i++) {

        // Muda para o proximo no
		if (posterior->a == aux2) {
            aux2 = posterior;
            posterior = posterior->b;
		}

            else {
                aux2 = posterior;
                posterior = posterior->a;
		}
    }

    // Troca os nos de posicao
    if (anterior->a == aux1)
        anterior->a = aux2;

        else
            anterior->b = aux2;

    if (aux1->b == anterior)
        aux1->b = posterior;

        else
            aux1->a = posterior;

    if (aux2->a == posterior)
        aux2->a = anterior;

        else
            aux2->b = anterior;


    if (posterior->a == aux2)
        posterior->a = aux1;

        else
            posterior->b = aux1;

    return;

}

// Funcao que libera a memoria da lista
void liberar(no* lista){

	no *ponteiro, *anterior, *aux;

	ponteiro = lista->a;
	anterior = lista;

	while(ponteiro->a && ponteiro->b){

		// Muda para o proximo no
		if (ponteiro->a == anterior) {
            aux = anterior;
            anterior = ponteiro;
            ponteiro = ponteiro->b;
		}

		else if (ponteiro->b == anterior) {
            aux = anterior;
            anterior = ponteiro;
            ponteiro = ponteiro->a;
		}

		free(aux);

	}

	free(anterior);
	free(ponteiro);

    return;

}


int main (void){

	char c;
	int i, j;
	double v;

	// Cria uma lista com sentinelas
	no* lista = criarL();

	while(1) {

		// Le e chama os comandos em um loop
		scanf(" %c", &c);

		switch(c){

			case 'i':

				scanf(" %d %lf", &i, &v);
				inserir(lista, i, v);

				break;

			case 'p':

				imprimir(lista);

				break;

			case 'v':

				scanf(" %d %d", &i, &j);
				reverter(lista, i, j);

				break;

			case 't':

				liberar(lista);
				return 0;

		}
	}

	return 0;

}
