// Luciano Gigantelli Zago - RA: 182835

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vdin.h"

// Criar vetor
char **criar (vetor* s){

	s->vetor = (char**)malloc(2*sizeof(char*));

	s->tam = 2;
	s->itens = 0;
	s->p=0;
	s->u=0;

	return s->vetor;
}

// Redimensionar
char ** realocar(vetor* s){

	char** ponteiro;
	int i, r=0;

	if (s->itens == 0)
        return NULL;

    // Recalcula posicao do ultimo
	s->u = (s->p + s->itens -1)%s->tam;

	// Verificar
    if ((s->itens) == s->tam )
        r=1;

    else if ((s->itens) <= s->tam*(1/4) )
        r=2;

    else if (r==0)
        return NULL;

	// Alocar
    if (r==1)
        ponteiro = (char**)malloc(2*s->tam*sizeof(char*));

    if (r==2)
        ponteiro = (char**)malloc((1/2)*s->tam*sizeof(char*));

	// Copiar
	for(i=0; i<s->itens; i++)
        ponteiro[i] = s->vetor[((s->p)+i)%(s->tam)];

	s->p=0;
	s->u=s->itens-1;

	if (r==1)
        s->tam *= 2;

    else if(r==2)
        s->tam /= 2;


	// Liberar
	if (s->vetor)
        free (s->vetor);
	s->vetor = ponteiro;

	return ponteiro;
}


// Le a string
char * ler(vetor* s, char* buffer){

    int i, inic = 0, tam = 0;

    scanf("%[^\n]s", buffer);

    tam = strlen(buffer);

    // Remove espacos finais
    for (i=1; i<tam; i++) {

        if (buffer[tam-i] == ' ')
            buffer[tam-i] = '\0';

        else
            break;

    }

    // Remove espacos iniciais
    for (i=0; i<tam; i++) {

        if (buffer[i] != ' ')
            break;

            inic++;
    }

    // Retorna a string lida e adaptada
    return &buffer[inic];
}

// Unshift
void unshift(vetor* s){

    char buffer[1001];
    char *aux, *string;
    int tam;

    aux = ler(s, buffer);
    tam = strlen(aux);

    string = (char*)malloc(tam*sizeof(char));
    strcpy(string, aux);

    if (s->itens != 0) {
        (s->p)--;

        if (s->p < 0)
            s->p += s->tam;

    }

    (s->itens)++;

    s->vetor[s->p] = string;

	return;
}

// Shift
void shift(vetor* s){

    if (s->itens==0)
        return;

    if (s->vetor[s->p])
        free(s->vetor[s->p]);

    s->vetor[s->p] = NULL;

    (s->p)++;
    (s->p) %= s->tam;

    (s->itens)--;


    return;
}

// Print-first
void pfirst(vetor* s){

    if (s->itens==0)
        return;

    printf("%s\n", s->vetor[s->p]);

    return;
}

// Push
void push(vetor* s){

    char buffer[1001];
    char *aux, *string;
    int tam;

    aux = ler(s, buffer);
    tam = strlen(aux);

    string = (char*)malloc(tam*sizeof(char));
    strcpy(string, aux);

    if (s->itens != 0) {
        (s->u)++;

        s->u %= s->tam;
    }

    (s->itens)++;

    s->vetor[s->u] = string;

	return;
}

// Pop
void pop(vetor* s){

    if (s->itens==0)
        return;

    if (s->vetor[s->u])
        free(s->vetor[s->u]);

    s->vetor[s->u] = NULL;

    (s->u)--;
    (s->itens)--;

    if (s->u < 0)
        s->u += s->tam;

    return;
}

// Print-last
void plast(vetor* s){

    if (s->itens==0)
        return;

    printf("%s\n", s->vetor[s->u]);

    return;
}

// Is-empty
void vazia(vetor* s){

    if (s->itens==0)
        printf("yep\n");

    else
        printf("nope\n");

    return;
}


// Exit
void liberar(vetor* s){

    int i;

    for (i=0; i<(s->itens); i++) {

        if (s->vetor[((s->p)+i)%s->tam])
            free(s->vetor[((s->p)+i)%s->tam]);
        s->vetor[((s->p)+i)%s->tam] = NULL;

    }

    if(s->vetor)
        free(s->vetor);

    return;
}
