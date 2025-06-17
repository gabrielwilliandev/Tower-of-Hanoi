#ifndef PILHA_H
#define PILHA_H

#include <stddef.h>
#include "historico.h"

// Externando váriavel
extern Lista* historico;

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

// Estrutura para o jogo
struct Jogo{
    struct _Pilha torres[3];
    int num_discos;
    int movimentos;
    char nome_jogador[30];
};

// Typedefs para conveniencia
typedef struct Node Node;
typedef struct _Pilha Pilha;
typedef struct Jogo Jogo;


void inicializar_pilha(Pilha* pilha);
void push(Pilha* pilha, int disco);
int pop(Pilha* pilha);
int topo(Pilha* pilha);
int contar_discos(Pilha* pilha);
void imprimir_disco(int disco, int largura_max);
void imprimir_torres(Pilha* A, Pilha* B, Pilha* C, int altura);
int verificar_vitoria(Jogo* jogo);
int mover_disco(Jogo* jogo, int origem, int destino);
void exibirAjuda(void);
void jogar(Lista* historico);

#endif

