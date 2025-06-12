#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

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

void DestruirLista(Lista **Lref) {
    Lista *L = *Lref;
    No *p = L->inicio;
    while (p != NULL) {
        No *aux = p;
        p = p->prox;
        free(aux);
    }
    free(L);
    *Lref = NULL;
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

// Funções de histórico

Lista* historico = NULL;

void exibir_historico() {
    No* atual = historico->inicio;
    if (!atual) {
        printf("Histórico vazio!\n");
        return;
    }
    printf("\n=== Histórico de Partidas ===\n");
    while (atual) {
        printf("Nome: %s | Data: %s | Movimentos: %d | Discos: %d\n",
               atual->nome, atual->data, atual->mov, atual->qntd);
        atual = atual->prox;
    }
}

void buscar_por_nome(const char* nome) {
    No* atual = historico->inicio;
    int encontrado = 0;
    printf("\n=== Resultados da busca por nome '%s' ===\n", nome);
    while (atual) {
        if (strstr(atual->nome, nome)) {
            printf("Nome: %s | Data: %s | Movimentos: %d | Discos: %d\n",
                   atual->nome, atual->data, atual->mov, atual->qntd);
            encontrado = 1;
        }
        atual = atual->prox;
    }
    if (!encontrado) {
        printf("Nenhuma partida encontrada para '%s'.\n", nome);
    }
}

void buscar_por_data(const char* data) {
    No* atual = historico->inicio;
    int encontrado = 0;
    printf("\n=== Resultados da busca por data '%s' ===\n", data);
    while (atual) {
        if (strcmp(atual->data, data) == 0) {
            printf("Nome: %s | Data: %s | Movimentos: %d | Discos: %d\n",
                   atual->nome, atual->data, atual->mov, atual->qntd);
            encontrado = 1;
        }
        atual = atual->prox;
    }
    if (!encontrado) {
        printf("Nenhuma partida encontrada para a data '%s'.\n", data);
    }
}

// Menu principal
int main() {
    historico = CriarLista();
    carregar_historico(historico);
    int opcao;
    char busca[50];
    do {
        printf("\n=== Torre de Hanoi ===\n");
        printf("1. Jogar\n2. Exibir histórico\n3. Buscar por nome\n4. Buscar por data\n5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                jogar();
                break;
            case 2:
                exibir_historico();
                break;
            case 3:
                printf("Digite o nome para busca: ");
                scanf("%s", busca);
                buscar_por_nome(busca);
                break;
            case 4:
                printf("Digite a data (ex: 06/06/2025): ");
                scanf("%s", busca);
                buscar_por_data(busca);
                break;
            case 5:
                printf("Saindo\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);
    
    DestruirLista(&historico);
    return 0;
}