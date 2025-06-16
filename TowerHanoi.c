#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "discos.h"
#include "historico.h"

// Estrutura para o jogo
typedef struct {
    Pilha torres[3];
    int num_discos;
    int movimentos;
    char nome_jogador[30];
} Jogo;

// Variável global para o histórico
Lista* historico = NULL;

// Função para verificar se o jogo foi vencido
int verificar_vitoria(Jogo* jogo) {
    return contar_discos(&jogo->torres[2]) == jogo->num_discos;
}

// Função para mover disco entre torres
int mover_disco(Jogo* jogo, int origem, int destino) {
    if (origem < 1 || origem > 3 || destino < 1 || destino > 3) {
        printf("Torres inválidas! Use A, B ou C.\n");
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
        printf("Movimento inválido: disco maior não pode ser colocado sobre disco menor!\n");
        push(&jogo->torres[origem], disco_origem); // Devolver o disco
        return 0;
    }

    push(&jogo->torres[destino], disco_origem);
    jogo->movimentos++;
    return 1;
}

// Função principal do jogo
void jogar(Lista* historico) {
    Jogo jogo;
    int num_discos;
    char opcao, destino;

    printf("Digite seu nome: ");
    scanf("%s", jogo.nome_jogador);
    do {
        printf("Digite o número de discos (3-8): ");
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
            printf("Parabéns, %s! Você venceu em %d movimentos!\n", jogo.nome_jogador, jogo.movimentos);
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
            printf("Torre de origem inválida! Use A, B ou C.\n");
            continue;
        }

        scanf(" %c", &destino);
        destino = toupper(destino); // Normalizar para maiúsculas
        if (destino != 'A' && destino != 'B' && destino != 'C') {
            printf("Torre de destino inválida! Use A, B ou C.\n");
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