// Luciano Gigantelli Zago - RA: 182835

#include <stdio.h>
#include <stdlib.h>

// Estrutura de entrada
typedef struct {

    int i;
    int j;
    int dado;
} vCoord;

// Estrutura do CSR
typedef struct {

    // Ponteiros para vetores
    int *a;
    int *r;
    int *c;
    int nLinha, nColuna;
} CSR;

// Funcao usada para ordenar a entrada
int comparar(const void *g, const void *h) {

     const vCoord *a = (const vCoord *)g;
     const vCoord *b = (const vCoord *)h;

    // Retorna 1 ou -1 se nao estiver na mesma linha
    if (a->i > b->i) return 1;
    if (a->i < b->i) return -1;

    // Se estiver na mesma linha, retorna 1 e -1 comparando a coluna
    if (a->j > b->j) return 1;
    if (a->j < b->j) return -1;

     return 0;
}

// Funcao que converte para CSR
CSR converter(vCoord *triplas, int n){

    CSR p;

    int aux=0, b=0;

    // Valor da maior linha
    p.nLinha = triplas[n-1].i;

    // Procura o valor da maior coluna
    for (aux = 0; aux < n; aux++){

        if(b < triplas[aux].j)
            b = triplas[aux].j;
    }

    // Valor da maior coluna
    p.nColuna = b;

    // Alocar memoria (a, r, c)
    p.a = (int*)malloc(n*sizeof(int)); // Tamanho n
    p.c = (int*)malloc(n*sizeof(int)); // Tamanho n
    p.r = (int*)malloc((p.nLinha+2)*sizeof(int)); // Tamanho i + 1

    // Zera o vetor r auxiliar
    for (aux=0; aux<p.nLinha+2; aux++ )
        p.r[aux] = 0;

    // Inicia o CSR
    p.a[0] = triplas[0].dado;
    p.c[0] = triplas[0].j;

    // Percorre o vetor e preenche o CSR
    for(aux=1; aux<n; aux++){

        p.a[aux] = triplas[aux].dado;
        p.c[aux] = triplas[aux].j;
        p.r[triplas[aux-1].i+1]++;
    }

    // Ultimo elemento do r e o total de valores
    p.r[p.nLinha+1] = n;

    // Encaideia as somas dos elementos por linha
    for (aux=1; aux<=p.nLinha; aux++)
            p.r[aux] += p.r[aux-1];

    // Retorna a estrutura do CSR
    return p;
}

// Funcao que busca no CSR
int buscar(CSR matriz, int i, int j){

    int a=0;

    // Se nao esta representado na matriz, retorna 0
    if (i > matriz.nLinha || j > matriz.nColuna)
        return 0;

    // Se a linha estiver vazia é 0
    else if (matriz.r[i] == matriz.r[i+1])
        return 0;

    // Procura a coluna entre as linhas
    else
        for (a = matriz.r[i]; a<matriz.r[i+1]; a++){
            if (j == matriz.c[a])
                return matriz.a[a];
    }

    return 0;
}

int main (void){

    int n, i, j;
    vCoord *entrada;
    // Estrutura de ponteiros para vetores
    CSR matriz;

    scanf(" %d", &n);

    // Aloca memoria para a entrada
    entrada = (vCoord*)malloc(n*sizeof(vCoord));

    // Le a entrada
    for(i=0; i<n; i++)
        scanf (" %d %d %d", &entrada[i].i, &entrada[i].j, &entrada[i].dado);

    // Ordena a entrada
    qsort(entrada, n, sizeof(vCoord), comparar);

    // Converte para CSR
    matriz = converter(entrada, n);

    // Libera a memoria da entrada
    free(entrada);

    // Busca no CSR
    scanf(" %d %d", &i, &j);

    while (i != -1){

        printf("(%d,%d) = %d\n", i, j, buscar(matriz, i, j));
        scanf(" %d %d", &i, &j);
    }

    // Libera a memoria da matriz CSR
    free(matriz.a);
    free(matriz.r);
    free(matriz.c);

    return 0;
}
