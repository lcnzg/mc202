// Luciano Gigantelli Zago - RA: 182835

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct no
typedef struct no {

    int dado;
    struct no *dir;
    struct no *esq;

} no;

// Insere no na arvore
no* inserir(no* ponteiro, int dado, int* tam){

    // Se chegar no fim da arvore, insere o elemento na posicao certa
	if (!ponteiro) {

        // Aumenta o tamanho da arvore
		(*tam)++;
		ponteiro = (no*)malloc(sizeof(no));
		ponteiro->dado = dado;
		ponteiro->esq = NULL;
		ponteiro->dir = NULL;
	}

    // Se nao encontrar, decide o lado da arvore para continuar a busca
	if (dado < ponteiro->dado)
		ponteiro->esq = inserir(ponteiro->esq, dado, tam);

	if (dado > ponteiro->dado)
		ponteiro->dir = inserir(ponteiro->dir, dado, tam);

	return ponteiro;
}

// Busca no na arvore
int buscar(no* ponteiro, int dado){

    // Se nao encontrar o no, retorna 0
	if (!ponteiro)
		return 0;

    // Se encontrar o no, retorna 1
	if (dado == ponteiro->dado)
		return 1;

    // Se nao percorrer a arvore inteira, escolhe o caminho correto e continua
	if (dado < ponteiro->dado)
		return buscar(ponteiro->esq, dado);

	else
		return buscar(ponteiro->dir, dado);
}

// Encontra valor minimo
no* minimo(no *ponteiro) {

    // Se chegar no fim, retorna nulo
	if (!ponteiro)
		return NULL;

    // Encontra o no mais a esquerda
	else {

		while (ponteiro->esq)
			ponteiro=ponteiro->esq;
    }

    return ponteiro;
}

// Encontra o valor maximo
no* maximo(no *ponteiro) {

    // Se chegar no fim, retorna nulo
	if (!ponteiro)
		return NULL;

    // Encontra o no mais a direita
	else {

		while (ponteiro->dir)
			ponteiro=ponteiro->dir;
	}

    return ponteiro;
}

// Imprime a arvore em pos-ordem
int impPos(no * ponteiro, int r) {

    // Se a arvore estiver vazia, retorna 0
    if (!ponteiro && r==0)
        return 0;

    if (ponteiro) {

		impPos(ponteiro->esq, 1);
		impPos(ponteiro->dir, 1);
		printf("%d ", ponteiro->dado);
    }

    return 1;
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

// Imprime a arvore em pre ordem
int impPre(no * ponteiro, int r) {

    // Se a arvore estiver vazia, retorna 0
    if (!ponteiro && r==0)
        return 0;

    if (ponteiro) {

		printf("%d ", ponteiro->dado);
		impPre(ponteiro->esq, 1);
		impPre(ponteiro->dir, 1);
    }

    return 1;
}

// Imprime a arvore em largura
int impLargura(no * raiz, int tam) {

    int fim, inic;

    // Se a arvore estiver vazia, retorna 0
    if (!raiz)
        return 0;

    // Cria uma fila de ponteiros para os nos
    no **fila = (no **) malloc(sizeof(no *) * tam);

    // A raiz inicia a fila
    fila[0] = raiz;

    // Laco para imprimir, depositar e acessar os ponteiros para os nos na fila
    for (fim = 0, inic = 0; inic < tam; inic++) {

		printf("%d ", fila[inic]->dado);

		// Se os filhos nao forem nulos, entram na fila

		if (fila[inic]->esq)
			fila[++fim] = fila[inic]->esq;

		if (fila[inic]->dir)
			fila[++fim] = fila[inic]->dir;
	}

    // Libera a fila
    free(fila);

    return 1;
}

// Exclui o da arvore
no* excluir(no* raiz, int dado, int* tam){

    no *ponteiro = NULL, *min = NULL, *pai = NULL, *paiMin = NULL;

    ponteiro = raiz;
    pai = ponteiro;

    // Encontra o no procurado e guarda seu pai
    while(ponteiro && ponteiro->dado != dado){

        pai = ponteiro;

        if (dado < ponteiro->dado)
            ponteiro = ponteiro->esq;

        else if (dado > ponteiro->dado)
            ponteiro = ponteiro->dir;
    }

    // Se nao existir, retorna sem excluir
    if (!ponteiro)
        return raiz;

    // Se tem so 1 filho ou nenhum
    // Se a esquerda for nula
    if (!ponteiro->esq) {

        // Troca o no encontrado pelo seu filho da direita
        if (ponteiro == raiz)
            raiz = ponteiro->dir;

        else if (pai->dir == ponteiro)
            pai->dir = ponteiro->dir;

        else if (pai->esq == ponteiro)
            pai->esq = ponteiro->dir;

        // Libera o no
        free(ponteiro);
    }


    // Se a direita for nula
    else if (!ponteiro->dir) {

        // Troca o no encontrado pelo seu filho da esquerda
        if (ponteiro == raiz)
            raiz = ponteiro->esq;

        else if (pai->dir == ponteiro)
            pai->dir = ponteiro->esq;

        else if (pai->esq == ponteiro)
            pai->esq = ponteiro->esq;

        // Libera o no
        free(ponteiro);
    }

    // Se tem 2 filhos
    else {

        // Encontra o minimo da subarvore direita (min)
        min = ponteiro->dir;
        paiMin = ponteiro;

        while(min->esq) {

            paiMin = min;
            min = min->esq;

        }

        // Se o minimo nao for filho do no encontrado
        if (paiMin != ponteiro) {

            // Troca o minimo pelo seu filho da direita
            if (min == raiz)
                raiz = min->dir;

            else if (paiMin->dir == min)
                paiMin->dir = min->dir;

            else if (paiMin->esq == min)
                paiMin->esq = min->dir;

            // Minimo toma lugar do no encontrado
            min->dir = ponteiro->dir;
        }

        // Se for a raiz, troca o no encontrado pelo minimo
        if (ponteiro == raiz)
            raiz = min;

        else if (pai->dir == ponteiro)
            pai->dir = min;

        else if (pai->esq == ponteiro)
            pai->esq = min;

        // Libera o no
        free(ponteiro);
    }

    // Diminui o tamanho da arvore
    (*tam)--;
    return raiz;
}


// Libera a arvore
void liberar(no * ponteiro) {

    if (ponteiro) {

		liberar(ponteiro->esq);
		liberar(ponteiro->dir);
		free(ponteiro);
    }

    return;
}

int main(void) {

    int aux, tam = 0;
    char comando[10];
    no *arvore = NULL, *aux2=NULL;

    while (1) {

		// Le e chama os comandos em um loop
		scanf(" %s", comando);

		if (strcmp(comando, "inserir") == 0) {

			scanf("%d", &aux);
			arvore = inserir(arvore, aux, &tam);
		}

		else if (strcmp(comando, "excluir") == 0) {

			scanf("%d", &aux);
			arvore = excluir(arvore, aux, &tam);
		}

		else if (strcmp(comando, "buscar") == 0) {

			scanf("%d", &aux);
			if(buscar(arvore, aux))
				printf("pertence\n");

			else
				printf("nao pertence\n");

		}

		else if (strcmp(comando, "minimo") == 0) {

			aux2 = minimo(arvore);

			if(aux2)
				printf("%d\n", aux2->dado);

			else
				printf("vazia\n");
		}

		else if (strcmp(comando, "maximo") == 0) {

			aux2 = maximo(arvore);

			if(aux2)
				printf("%d\n", aux2->dado);

			else
				printf("vazia\n");
		}

		else if (strcmp(comando, "pos-ordem") == 0) {

			if (impPos(arvore, 0))
                printf("\n");

            else
                printf("vazia\n");
		}

		else if (strcmp(comando, "em-ordem") == 0) {

			if (impEm(arvore, 0))
                printf("\n");

            else
                printf("vazia\n");

		}

		else if (strcmp(comando, "pre-ordem") == 0) {

			if (impPre(arvore, 0))
                printf("\n");

            else
                printf("vazia\n");

		}

		else if (strcmp(comando, "largura") == 0) {

			if (impLargura(arvore, tam))
                printf("\n");

            else
                printf("vazia\n");

		}

		else if (strcmp(comando, "terminar") == 0) {

			liberar(arvore);
			break;

		}
    }

    return 0;
}
