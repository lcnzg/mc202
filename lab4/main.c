// Luciano Gigantelli Zago - RA: 182835

#include <stdio.h>
#include <string.h>
#include "vdin.h"

int main(void){

	vetor s;

	char comando[12];

	criar(&s);

	while(1) {

		// Le e chama os comandos em um loop
		scanf(" %s", comando);

        if (strcmp(comando, "unshift") == 0) {

            unshift(&s);
            realocar(&s);

            }

        else if (strcmp(comando, "shift") == 0) {

            shift(&s);
            realocar(&s);

            }

        else if (strcmp(comando, "print-first") == 0) {

            pfirst(&s);

            }

        else if (strcmp(comando, "push") == 0) {

            push(&s);
            realocar(&s);

            }

        else if (strcmp(comando, "pop") == 0) {

            pop(&s);
            realocar(&s);

		}

        else if (strcmp(comando, "print-last") == 0) {

            plast(&s);

            }

        else if (strcmp(comando, "is-empty") == 0) {

            vazia(&s);

            }

        else if (strcmp(comando, "exit") == 0) {

            liberar(&s);
            break;

            }
	}

	return 0;
}
