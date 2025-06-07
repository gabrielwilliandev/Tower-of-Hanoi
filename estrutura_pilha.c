#include <stdio.h>
#include <stdlib.h>

// Estrutura - pilha (torre)
typedef struct Node {
    int disco;
    struct Node* prox;
} Node;

typedef struct {
    Node* topo;
} Pilha;


// Funções p/ manipulação da pilha
void inicializar_pilha(Pilha* pilha) {
    pilha->topo = NULL;
}

void push(Pilha* pilha, int disco) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->disco = disco;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

int pop(Pilha* pilha) {
    if (!pilha->topo) return -1;
    Node* temp = pilha->topo;
    int disco = temp->disco;
    pilha->topo = temp->prox;
    free(temp);
    return disco;
}

// Conter disco em uma torre
int contar_discos(Pilha* pilha) {
    int count = 0;
    Node* atual = pilha->topo;
    while (atual) {
        count++;
        atual = atual->prox;
    }
    return count;
}

// Obter disco em uma posição específica
int obter_disco(Pilha* pilha, int pos) {
    Node* atual = pilha->topo;
    for (int i = 0; i < pos && atual; i++) {
        atual = atual->prox;
    }
    return atual ? atual->disco : 0;
}