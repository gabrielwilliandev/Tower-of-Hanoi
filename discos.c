#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "discos.h"
#include "historico.h"

#define LARGURA_DISCO 2

// Variável global para o histórico
Lista* historico = NULL;

// Funções para manipulação da pilha
void inicializar_pilha(Pilha* pilha) {
    pilha->topo = NULL;
    pilha->base = NULL;
    pilha->tam = 0;
}

// Função do topo
int topo(Pilha* pilha){
    if(pilha->topo == NULL) return -1;
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

void imprimir_disco(int disco, int largura_max) {
    if (disco == 0) {
        // Centraliza a haste '|'
        int meio = largura_max / 2;
        for (int i = 0; i < largura_max; i++) {
            if (i == meio)
                printf("|");
            else
                printf(" ");
        }
    } else {
        int largura = disco * LARGURA_DISCO;
        int espacos = (largura_max - largura) / 2;

        for (int i = 0; i < espacos; i++) printf(" ");
        for (int i = 0; i < largura; i++) printf("=");
        for (int i = 0; i < largura_max - espacos - largura; i++) printf(" ");
    }
}


void imprimir_torres(Pilha* A, Pilha* B, Pilha* C, int altura) {
    int largura_max = altura * LARGURA_DISCO;

    printf("\n");

    for (int linha = 0; linha < altura; linha++) {
        // Torre A
        Node* atualA = A->base;
        for (int i = 0; i < altura - linha - 1; i++) {
            if (atualA != NULL) atualA = atualA->ant;
        }
        if (atualA != NULL)
            imprimir_disco(atualA->disco, largura_max);
        else
            imprimir_disco(0, largura_max);

        printf("    ");

        // Torre B
        Node* atualB = B->base;
        for (int i = 0; i < altura - linha - 1; i++) {
            if (atualB != NULL) atualB = atualB->ant;
        }
        if (atualB != NULL)
            imprimir_disco(atualB->disco, largura_max);
        else
            imprimir_disco(0, largura_max);

        printf("    ");

        // Torre C
        Node* atualC = C->base;
        for (int i = 0; i < altura - linha - 1; i++) {
            if (atualC != NULL) atualC = atualC->ant;
        }
        if (atualC != NULL)
            imprimir_disco(atualC->disco, largura_max);
        else
            imprimir_disco(0, largura_max);

        printf("\n");
    }

    // base
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < largura_max; j++) printf("-");
        printf("    ");
    }
    printf("\n");

    // nomes
    printf("%-*s   %-*s   %-*s\n", largura_max, " Torre A", largura_max, " Torre B", largura_max, " Torre C");
}

// Função para verificar se o jogo foi vencido
int verificar_vitoria(Jogo* jogo) {
    return contar_discos(&jogo->torres[2]) == jogo->num_discos;
}

// Função para mover disco entre torres
int mover_disco(Jogo* jogo, int origem, int destino) {
    if (origem < 1 || origem > 3 || destino < 1 || destino > 3) {
        printf("Torres invalidas! Use A, B ou C.\n");
        return 0;
    }
    origem--; // Ajustar para índice 0-based
    destino--;

    int disco_origem = pop(&jogo->torres[origem]);
    if (disco_origem == -1) {
        printf("Torre de origem vazia!\n");
        return 0;
    }

    int disco_destino = topo(&jogo->torres[destino]);;
    if (disco_destino != -1 && disco_origem > disco_destino) {
        printf("Movimento invalido: disco maior não pode ser colocado sobre disco menor!\n");
        push(&jogo->torres[origem], disco_origem); // Devolver o disco
        return 0;
    }

    push(&jogo->torres[destino], disco_origem);
    jogo->movimentos++;
    return 1;
}

void exibirAjuda(){
    printf("\n===== AJUDA =====\n");
    printf("Objetivo do jogo: Mover todos os discos da Torre A para a Torre C\n");
    printf("Regras:\n");
    printf(" - So e possivel mover o topo de uma torre por vez\n");
    printf(" - Nao e permitido colocar um disco maior sobre um menor\n\n");
    printf("Comandos:\n");
    printf(" A B -> Move o topo da Torre A para a Torre B\n");
    printf(" R -> Reinicia o jogo\n");
    printf(" S -> Sai do jogo\n");
    printf("==============\n\n");
}

// Função principal do jogo
void jogar(Lista* historico) {
    Jogo jogo;
    int num_discos;
    char opcao, destino;

    printf("Digite seu nome: ");
    scanf("%s", jogo.nome_jogador);
    do {
        printf("Digite o numero de discos (3-8): ");
        scanf("%d", &num_discos);
    } while (num_discos < 3 || num_discos > 8);



    // Inicializar jogo
    jogo.num_discos = num_discos;
    jogo.movimentos = 0;
    for (int i = 0; i < 3; i++) {
        inicializar_pilha(&jogo.torres[i]);
    }
    for (int i = num_discos; i >= 1; i--) {
        push(&jogo.torres[0], i);
    }

    // Loop do jogo
    while (1) {
        imprimir_torres(&jogo.torres[0], &jogo.torres[1], &jogo.torres[2], jogo.num_discos);
        printf("Movimentos: %d\n", jogo.movimentos);
        if (verificar_vitoria(&jogo)) {
            printf("Parabens, %s! Voce venceu em %d movimentos!\n", jogo.nome_jogador, jogo.movimentos);
            InserirInicio(historico, jogo.nome_jogador, jogo.movimentos, jogo.num_discos);
            SalvarHist(historico, "historico.txt");
            break;
        }

        printf("Digite a torre de origem e destino (ex: A B) ou 'R' para reiniciar, 'S' para sair: ");
        scanf(" %c", &opcao);
        opcao = toupper(opcao); // Normalizar para maiúsculas

        if (opcao == 'R') {
            // Reiniciar jogo
            for (int i = 0; i < 3; i++) {
                while (pop(&jogo.torres[i]) != -1);
                inicializar_pilha(&jogo.torres[i]);
            }
            for (int i = num_discos; i >= 1; i--) {
                push(&jogo.torres[0], i);
            }
            jogo.movimentos = 0;
            printf("Jogo reiniciado!\n");
            continue;
        }
        if (opcao == 'S') {
            break;
        }

        // Validar entrada de origem e destino
        if (opcao != 'A' && opcao != 'B' && opcao != 'C') {
            printf("Torre de origem invalida! Use A, B ou C.\n");
            continue;
        }

        scanf(" %c", &destino);
        destino = toupper(destino); // Normalizar para maiúsculas
        if (destino != 'A' && destino != 'B' && destino != 'C') {
            printf("Torre de destino invalida! Use A, B ou C.\n");
            continue;
        }

        int orig = opcao - 'A' + 1;
        int dest = destino - 'A' + 1;
        mover_disco(&jogo, orig, dest);
    }

    // Liberar memória
    for (int i = 0; i < 3; i++) {
        while (pop(&jogo.torres[i]) != -1);
    }
}