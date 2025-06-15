#ifndef PILHA_H
#define PILHA_H

#include <stddef.h>

// Estrutura do nó da pilha
struct Node {
    int disco;
    struct Node* prox;
    struct Node* ant;
};

// Estrutura da pilha (torre)
struct _Pilha {
    struct Node* topo;
    struct Node* base;
    size_t tam;
};

// Typedefs para conveniencia
typedef struct Node Node;
typedef struct _Pilha Pilha;

void inicializar_pilha(Pilha* pilha);
void push(Pilha* pilha, int disco);
int pop(Pilha* pilha);
int contar_discos(Pilha* pilha);
int obter_disco(Pilha* pilha, int pos);
void imprimir_disco(int disco, int largura_max);
void imprimir_torres(Pilha* A, Pilha* B, Pilha* C, int altura);

#endif

