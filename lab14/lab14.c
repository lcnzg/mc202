// Luciano Gigantelli Zago - RA: 182835

#include <stdio.h>
#include <stdlib.h>

// Estrutura para lista ligada
typedef struct no {

    struct no* prox;
    int vertice;
} no;

// Estrutura que contem o grafo
typedef struct {

    int n; // Numero de vertices
    no** vetor; // Vetor de ponteiros para o no
    char* cor; // Vetor com branco, cinza ou preto
    int *t1; // Vetor com o tempo de descoberta
    int *t2; // Vetor com o termpo de termino
    int tAux; // Tempo auxiliar
    char ciclo; // 0 ou 1
    int *ordem; // Vetor que salva a ordem de descoberta
    int j; // Variavel auxiliar
} grafo;

// Insere uma aresta na lista de adjacencia
void inserir (grafo *g, int a, int b) {

    // Ponteiros para o no auxiliares
    no *aux,*novo;

    // Insere um no na lista
    novo = malloc(sizeof(no));
    novo->vertice = b;
    novo->prox = NULL;

    // Insere o no no vetor
    if(g->vetor[a-1] == NULL)
        g->vetor[a-1] = novo;

    // Insere no fim da lista
    else {

        // Procura o fim da lista
        aux = g->vetor[a-1];

        while(aux->prox)
            aux = aux->prox;

        // Liga o no com o ultimo vertice da lista
        aux->prox = novo;
    }

    return;
}

// Funcao recursiva que visita os nos
void dfsVisitar(grafo *g, int v){

    no* aux;
    int i;

    // Salva a ordem de descoberta
    g->ordem[(g->j)++] = (v+1);

    // Torna o vertice cinza
    g->cor[v] = 'c';

    // Aumenta o tempo
    (g->tAux)++;

    // Salva o tempo inicial
    g->t1[v] = g->tAux;

    // Auxiliares
    aux = g->vetor[v];
    i = v;

    // Percorre a lista
    while(aux != NULL) {
        i = (aux->vertice)-1;

        // Verifica se ocorreu um ciclo
        if (g->cor[i] == 'c' && aux != g->vetor[i]) {
            g->ciclo = 1;
            break;
        }

        // Se o vertice nao foi visitado, e feito recursivamente
        if(g->cor[i] == 'b')
            dfsVisitar(g, i);

        aux = aux->prox;
    }

    // Torna o vertice preto
    g->cor[v] = 'p';

    // Aumenta o tempo
    (g->tAux)++;

    // Salva o tempo final
    g->t2[v] = g->tAux;

    return;
}

// Funcao que realiza a busca em profundidade
void dfs(grafo *g){

    int i;

    // Aloca memoria para os vetores
    g->cor = malloc(g->n*sizeof(char));
    g->t1 = malloc(g->n*sizeof(int));
    g->t2 = malloc(g->n*sizeof(int));
    g->ordem = malloc(g->n*sizeof(int));

    // Inicializa o vetor como nulo
    for(i=0; i<g->n; i++)
        g->cor[i] = 'b';

    g->ciclo = 0;
    g->tAux = 0;
    g->j = 0;

    for (i=0; i<g->n; i++){

        if (g->cor[i] == 'b')
            dfsVisitar(g, i);
    }

    return;
}

// Funcao que libera recursivamente a memoria da lista
void liberar(no *ponteiro){

	if (ponteiro) {
        liberar(ponteiro->prox);
        free(ponteiro);
	}

	return;
}


int main (void) {

    int i=0, a=0, b=0;

    //Inicializar os elementos
    grafo* g = malloc(sizeof(grafo));

    // Le o numero de vertices
    scanf("%d", &g->n);

    // Aloca memoria para o vetor
    g->vetor = malloc (g->n*sizeof(no));

    // Inicializa o vetor de listas como nulo
    for(i=0; i<g->n; i++)
        g->vetor[i] = NULL;

    // Le e monta o grafo
    while (1) {
        scanf("%d,%d", &a, &b);

        // Para se chegar no fim
        if (!a)
            break;

        inserir(g, a, b);
    }

    // Percorrer o grafo por dfs
    dfs(g);

    // Imprime os tempos do dfs
    for (i=0; i<g->n; i++)
        printf("%d [%d,%d]\n", g->ordem[i], g->t1[g->ordem[i]-1], g->t2[g->ordem[i]-1]);

    // Imprime se ocorreu ciclo
    if (g->ciclo)
        printf("aciclico: nao\n");
    else
        printf("aciclico: sim\n");

    // Libera o espaco alocado
    for (i=0; i<g->n; i++)
        liberar(g->vetor[i]);

    free(g->cor);
    free(g->t1);
    free(g->t2);
    free(g->vetor);
    free(g);

    return 0;
}
