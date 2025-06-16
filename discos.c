#include <stdio.h>
#include <stdlib.h>
#include "discos.h"

#define LARGURA_DISCO 2

// Funções para manipulação da pilha
void inicializar_pilha(Pilha* pilha) {
    pilha->topo = NULL;
    pilha->base = NULL;
    pilha->tam = 0;
}


int topo(Pilha* pilha){
    if(pilha->topo == NULL) return 0;
    return  pilha->topo->disco;
}


void push(Pilha* pilha, int disco) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->disco = disco;
    novo->prox = pilha->topo;
    novo->ant = NULL;

    if (pilha->tam != 0) {
        pilha->topo->ant = novo;
    } else {
        pilha->base = novo;
    }

    pilha->topo = novo;
    pilha->tam++;
}

int pop(Pilha* pilha) {
    if (pilha->tam == 0) {
        printf("Pilha vazia!\n");
        return -1;
    }
    Node* temp = pilha->topo;
    int disco = temp->disco;
    pilha->topo = temp->prox;

    if (pilha->topo != NULL) {
        pilha->topo->ant = NULL;
    } else {
        pilha->base = NULL;
    }

    free(temp);
    pilha->tam--;
    return disco;
}

int contar_discos(Pilha* pilha) {
    return pilha->tam;
}

int obter_disco(Pilha* pilha, int pos) {
    Node* atual = pilha->topo;
    for (int i = 0; i < pos && atual; i++) {
        atual = atual->prox;
    }
    return atual ? atual->disco : 0;
}

void imprimir_disco(int disco, int largura_max) {
    int largura = disco * LARGURA_DISCO;
    int espacos = (largura_max - largura) / 2;

    for (int i = 0; i < espacos; i++) printf(" ");
    if (disco == 0) {
        printf("|");
    } else {
        for (int i = 0; i < largura; i++) printf("=");
    }
    for (int i = 0; i < espacos; i++) printf(" ");
}

void imprimir_torres(Pilha* A, Pilha* B, Pilha* C, int altura) {
    int largura_max = altura * LARGURA_DISCO;

    printf("\n");

    for (int linha = altura - 1; linha >= 0; linha--) {
        imprimir_disco(obter_disco(A, linha), largura_max);
        printf("    ");
        imprimir_disco(obter_disco(B, linha), largura_max);
        printf("    ");
        imprimir_disco(obter_disco(C, linha), largura_max);
        printf("\n");
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < largura_max; j++) printf("-");
        printf("    ");
    }
    printf("\n");

    printf("%-*s   %-*s   %-*s\n", largura_max, " Torre A", largura_max, " Torre B", largura_max, " Torre C");
}