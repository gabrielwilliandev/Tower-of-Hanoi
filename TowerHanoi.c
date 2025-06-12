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

Lista* historico = NULL;

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
                jogar(historico);
                break;
            case 2:
                exibir_historico(historico);
                break;
            case 3:
                printf("Digite o nome para busca: ");
                scanf("%s", busca);
                buscar_por_nome(historico, busca);
                break;
            case 4:
                printf("Digite a data (ex: 06/06/2025): ");
                scanf("%s", busca);
                buscar_por_data(historico, busca);
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