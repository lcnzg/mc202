// Luciano Gigantelli Zago - RA: 182835

#include <stdio.h>
#include <stdlib.h>

// Macros para linearizar a arvore
#define pai(x) (x-1) / 2
#define fesq(x) (2*x) + 1
#define fdir(x) (2*x) + 2

// Define a estrutura do heap
typedef struct{

    int chave;
    int custo;
} h;

// Troca dois elementos de posicao
void trocar(h *i, h *j, int *v) {

    // Usa 2 auxiliares
	h k;
	int a;

	if (i->chave < 0|| j->chave < 0)
        return;

    // Troca na heap e no vetor de posicao
	k = (*i);
	a = v[i->chave];
	v[i->chave] = v[j->chave];
	(*i) = (*j);
	v[j->chave] = a;
	(*j) = k;

	return;
}

// Funcao recursiva que verifica se os filhos sao maiores que os pais, se nao, o troca com o pai
void refazer(h *heap, int *v, int i, int e) {
    int min = i;

    // Retorna se i for invalido
    if (i > e)
        return;

    // Se existir filho esquerdo, compara com o pai e pega o menor
    if (fesq(i) < e) {
        if(heap[fesq(i)].custo < heap[i].custo)
            min = fesq(i);

        else
            min = i;
    }

    // Se existir filho esquerdo, compara com o pai atual e pega o menor
    if (fdir(i) < e) {
        if(heap[fdir(i)].custo < heap[min].custo)
            min = fdir(i);
    }

    // Se encontrou filho menor, troca com o pai e verifica a subarvore
    if(min != i) {
        trocar(&(heap[i]), &(heap[min]), v);
        refazer(heap, v, min, e);
    }

    return;
}

// Insere o novo elemento no heap
int inserir(h *heap, int *v, int chave, int custo, int *e){

    int i;

    // Se a chave já existir, não insere
    if (v[chave] >= 0)
        return 0;

    // Insere o elemento no fim
    heap[*e].chave = chave;
    heap[*e].custo = custo;
    v[chave] = *e;

    // Aumenta o tamanho do heap
    (*e)++;

    // O no inserido escala a arvore se for menor que o pai
	for (i = (*e)-1; heap[pai(i)].custo > heap[i].custo && i > 0; i = pai(i))
		trocar(&heap[pai(i)], &heap[i], v);

    return 1;
}


int remin(h *heap, int *v, int *e){

    // Se estiver vazia, não há o que remover
    if (*e <= 0)
        return 0;

    // Diminui o numero de elementos
    (*e)--;

    // Imprime o minimo
    printf("minimo {%d,%d}\n", heap[0].chave, heap[0].custo);

    // Remove o minimo
    v[heap[0].chave] = -1;
    heap[0].chave = -1;

    // Se só tiver 1 elemento
    if ((*e) <= 0)
        return 1;

    // Coloca o ultimo no inicio e refaz a heap
    heap[0] = heap[*e];
    v[heap[*e].chave] = 0;
    heap[*e].chave = -1;
    refazer(heap, v, 0, *e);

    return 1;
}

void diminuir(h *heap, int *v, int chave, int custo, int e){

    int i;

    // Se a chave nao existir, nao diminui
    if(v[chave] < 0)
        return;

    // Diminui o custo
    heap[v[chave]].custo = custo;

    // Refaz o heap
    for(i = e-1; i >= 0; i--)
        refazer(heap, v, i, e);

    return;
}

int main (void){

    char c;
    int n, chave, custo, e=0, i;

    scanf(" %d", &n);

    // Cria heap sequencial
    h *heap = (h*)malloc(n*sizeof(h));

    // Inicia o heap
    for (i=0; i<n; i++)
        heap[i].chave = -1;

    // Cria vetor de posicao
    int *v = (int*)malloc(n*sizeof(int));

    // Inicia o vetor de posicao
    for (i=0; i<n; i++)
        v[i] = -1;

    while (1) {

        // Le o tipo do comando
        scanf(" %c", &c);

        // Insere o par no heap
        if (c == 'i'){
            scanf(" %d %d", &chave, &custo);
            inserir(heap, v, chave, custo, &e);
        }

        // Remove o minimo do heap
        else  if (c == 'm'){
            if (!remin(heap, v, &e))
                printf("vazio\n");
        }

        // Diminui o custo da chave
        else  if (c == 'd'){
            scanf(" %d %d", &chave, &custo);
            diminuir(heap, v, chave, custo, e);
        }

        // Termina o programa
        else  if (c == 't'){
            free(heap);
            free(v);
            break;
        }
    }

    return 0;
}
