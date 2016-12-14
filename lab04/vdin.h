// Luciano Gigantelli Zago - RA: 182835

// Struct vetor
typedef struct {

	int tam;
	int itens;
	int p;
	int u;

	char ** vetor;

} vetor;

// Criar vetor
char **criar (vetor* s);

// Redimensionar
char **realocar(vetor* s);

// Le a string
char *ler(vetor* s, char* buffer);

// Unshift
void unshift(vetor* s);

// Shift
void shift(vetor* s);

// Print-first
void pfirst(vetor* s);

// Push
void push(vetor* s);

// Pop
void pop(vetor* s);

// Print-last
void plast(vetor* s);

// Is-empty
void vazia(vetor* s);

// Exit
void liberar(vetor* s);
