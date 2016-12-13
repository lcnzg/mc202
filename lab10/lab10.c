// Luciano Gigantelli Zago - RA: 182835

#include <stdio.h>
#include <stdlib.h>

// Tamanho primo da tabela e divisor primo do hashing duplo
#define THASH 62497
#define T2 62483

// Estrutura da tabela
typedef struct tabela{

    char flag;
    unsigned int chave;
    int valor;

} tabela;

// Funcao que cria a tabela
tabela *cria(){

    unsigned int i;
    tabela *hash = (tabela*)malloc(THASH*sizeof(tabela));

    // Inicializa como vazia
    for (i=0; i<THASH; i++)
        hash[i].flag = 'v';

    return hash;
}

// Funcao que calcula o indice (hashing)
int h(unsigned int chave, int r){

    return (chave + r*(1+(chave%T2)))%THASH;
}

// Funcao que insere o elemento
int inserir(tabela *hash, unsigned int chave, int valor){

    int i = 0;
    int indice;

    // Encontra a posicao
    while (1){

        // Calcula o hashing
        indice = h(chave, i++);

        // Para se estiver vazio
        if (hash[indice].flag == 'v')
            break;

        // Para se ja existir o elemento
        if (hash[indice].chave == chave)
            break;
    }

    // Insere/atualiza elemento no vetor
    hash[indice].flag = 'i';
    hash[indice].chave = chave;
    hash[indice].valor = valor;

    return 1;
}

// Funcao que busca o elemento na tabela
int buscar(tabela* hash, unsigned int chave){

    int i = 0;
    int indice;

    // Encontra a posicao
    while (1){

        // Calcula o hashing
        indice = h(chave, i++);

        // Retorna 0 se nao existir elemento
        if (hash[indice].flag == 'v')
            return 0;

        // Para se encontrar o elemento
        if (hash[indice].chave == chave) {
            if (hash[indice].flag == 'i')
                break;
        }
    }

    // Imprime o valor encontrado
    printf ("valor para %u: %d\n", chave, hash[indice].valor);

    return 1;
}

// Funcao que remove elemento
int remover(tabela* hash, unsigned int chave){

    int i = 0;
    int indice;

    // Encontra a posicao
    while (1){

        indice = h(chave, i++);

        // Retorna 0 se nao existir elemento
        if (hash[indice].flag == 'v')
            return 0;

        // Para se encontrar o elemento
        if (hash[indice].chave == chave) {
            if (hash[indice].flag == 'i')
                break;
        }
    }

    // Remove o  elemento da tabela
    hash[indice].flag = 'r';

    return 1;
}


// Funcao que libera a tabela
void liberar(tabela* hash){

    free(hash);
    return;
}

int main (void){

    char c;
    unsigned int chave;
    int valor;

    // Criar tabela
    tabela* hash = cria();

    // Loop para leitura dos comandos
    while (1) {

        // Le o tipo do comando
        scanf(" %c", &c);

        // Insere o elemento na tabela
        if (c == 'i'){
            scanf(" %u %d", &chave, &valor);
            inserir(hash, chave, valor);
        }

        // Busca se o elemento esta na tabela
        else  if (c == 'b'){
            scanf(" %u", &chave);

            // Se o retorno for 0, nao existe o elemento na tabela
            if (!buscar(hash, chave))
                printf("%u nao existe\n", chave);
        }

        // Remove o elemento da tabela
        else  if (c == 'r'){
            scanf(" %u", &chave);
            remover(hash, chave);
        }

        // Termina o programa
        else  if (c == 'f'){
            liberar(hash);
            break;
        }
    }

    return 0;
}
