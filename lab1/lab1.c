//01-triangular
//Luciano Gigantelli Zago - 182835

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (void) {

    int n, i , j;
    double **vetor, media=0, desvio=0;

    scanf("%d\n", &n);

    // Alocar vetor de ponteiros
    vetor =  malloc(n * sizeof(double*));

    for (i=0; i<n; i++) {

        // Alocar vetores apontados (linhas)
        vetor[i] = malloc((i+1) * sizeof(double));

        for (j=0; j<(i+1); j++) {

            scanf("%lf", &vetor[i][j]);

            // Calculo da media
            media += vetor[i][j];
        }
    }

    media /= (n+1)*n/2;


    // Calculo do desvio padrao
    for (i=0; i<n; i++) {

        for (j=0; j<(i+1); j++)
            desvio += pow(vetor[i][j] - media, 2);

    }

    desvio /= (n+1)*n/2;
    desvio = sqrt(desvio);


    // Imprimie a saida
    for (i=0; i<n; i++) {

        for (j=0; j<(i+1); j++)
            printf("%.12lf ", (vetor[i][j] - media)/desvio);

        printf ("\n");
    }

    printf("\n");
    printf ("%.12lf %.12lf \n", media, desvio);


    // Liberar memoria
    for (i=0; i<n; i++)
        free(vetor[i]);

    free (vetor);


    return 1;
}
