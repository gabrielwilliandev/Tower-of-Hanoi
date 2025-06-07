#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para a pilha (torre)
typedef struct Node {
    int disco;
    struct Node* prox;
} Node;

typedef struct {
    Node* topo;
} Pilha;

// Estrutura para o histórico
typedef struct Historico {
    char nome[50];
    int movimentos;
    int discos;
    char data[20];
    struct Historico* prox;
} Historico;

// Variáveis globais
Pilha torres[3];
Historico* historico = NULL;
int num_discos;
char nome_jogador[50];
int movimentos;

// Funções para manipulação da pilha
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

// Função para contar discos em uma torre
int contar_discos(Pilha* pilha) {
    int count = 0;
    Node* atual = pilha->topo;
    while (atual) {
        count++;
        atual = atual->prox;
    }
    return count;
}

// Função para obter disco em uma posição específica
int obter_disco(Pilha* pilha, int pos) {
    Node* atual = pilha->topo;
    for (int i = 0; i < pos && atual; i++) {
        atual = atual->prox;
    }
    return atual ? atual->disco : 0;
}

// Função para exibir as torres graficamente
void exibir_torres() {
    printf("\n=== Torres de Hanoi ===\n");
    int altura_max = num_discos + 1; // Altura máxima para exibição
    int largura_disco = num_discos * 2 + 1; // Largura máxima de um disco

    // Para cada linha da altura máxima
    for (int linha = altura_max - 1; linha >= 0; linha--) {
        for (int torre = 0; torre < 3; torre++) {
            int discos = contar_discos(&torres[torre]);
            int pos_disco = discos - (altura_max - linha - 1);
            int disco = pos_disco > 0 ? obter_disco(&torres[torre], pos_disco - 1) : 0;

            if (disco == 0 && linha == 0) {
                // Base da torre
                for (int i = 0; i < (largura_disco - 1) / 2; i++) printf(" ");
                printf("|");
                for (int i = 0; i < (largura_disco - 1) / 2; i++) printf(" ");
            } else if (disco == 0) {
                // Espaço vazio
                for (int i = 0; i < largura_disco; i++) printf(" ");
            } else {
                // Desenhar disco com #
                int espacos = (largura_disco - (disco * 2 - 1)) / 2;
                for (int i = 0; i < espacos; i++) printf(" ");
                for (int i = 0; i < disco * 2 - 1; i++) printf("#");
                for (int i = 0; i < espacos; i++) printf(" ");
            }
            printf("  "); // Espaço entre torres
        }
        printf("\n");
    }

    // Exibir rótulos das torres
    for (int torre = 0; torre < 3; torre++) {
        for (int i = 0; i < (largura_disco - 7) / 2; i++) printf(" ");
        printf("Torre %d", torre + 1);
        for (int i = 0; i < (largura_disco - 7) / 2; i++) printf(" ");
        printf("  ");
    }
    printf("\nMovimentos: %d\n", movimentos);
}

// Função para verificar vitória
int verificar_vitoria() {
    if (!torres[0].topo && !torres[1].topo) {
        Node* atual = torres[2].topo;
        int count = 0;
        while (atual) {
            count++;
            atual = atual->prox;
        }
        return count == num_discos;
    }
    return 0;
}

// Função para mover disco
int mover_disco(int origem, int destino) {
    int disco = pop(&torres[origem - 1]);
    if (disco == -1) {
        printf("Torre de origem vazia!\n");
        return 0;
    }
    if (torres[destino - 1].topo && torres[destino - 1].topo->disco < disco) {
        printf("Movimento inválido: disco maior sobre menor!\n");
        push(&torres[origem - 1], disco);
        return 0;
    }
    push(&torres[destino - 1], disco);
    movimentos++;
    return 1;
}

// Função para salvar histórico
void salvar_historico() {
    Historico* novo = (Historico*)malloc(sizeof(Historico));
    strcpy(novo->nome, nome_jogador);
    novo->movimentos = movimentos;
    novo->discos = num_discos;
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    strftime(novo->data, 20, "%d/%m/%Y %H:%M", tm);
    novo->prox = historico;
    historico = novo;

    FILE* arquivo = fopen("historico.txt", "a");
    fprintf(arquivo, "%s %d %d %s\n", novo->nome, novo->movimentos, novo->discos, novo->data);
    fclose(arquivo);
}

// Função para carregar histórico
void carregar_historico() {
    FILE* arquivo = fopen("historico.txt", "r");
    if (!arquivo) return;
    Historico temp;
    while (fscanf(arquivo, "%s %d %d %[^\n]", temp.nome, &temp.movimentos, &temp.discos, temp.data) == 4) {
        Historico* novo = (Historico*)malloc(sizeof(Historico));
        *novo = temp;
        novo->prox = historico;
        historico = novo;
    }
    fclose(arquivo);
}

// Função para exibir histórico
void exibir_historico() {
    printf("\n=== Histórico de Partidas ===\n");
    Historico* atual = historico;
    while (atual) {
        printf("Jogador: %s | Movimentos: %d | Discos: %d | Data: %s\n",
               atual->nome, atual->movimentos, atual->discos, atual->data);
        atual = atual->prox;
    }
}

// Função para buscar histórico por nome
void buscar_por_nome(char* nome) {
    printf("\n=== Resultados para '%s' ===\n", nome);
    Historico* atual = historico;
    int encontrou = 0;
    while (atual) {
        if (strstr(atual->nome, nome)) {
            printf("Jogador: %s | Movimentos: %d | Discos: %d | Data: %s\n",
                   atual->nome, atual->movimentos, atual->discos, atual->data);
            encontrou = 1;
        }
        atual = atual->prox;
    }
    if (!encontrou) printf("Nenhuma partida encontrada.\n");
}

// Função para buscar histórico por data
void buscar_por_data(char* data) {
    printf("\n=== Resultados para '%s' ===\n", data);
    Historico* atual = historico;
    int encontrou = 0;
    while (atual) {
        if (strstr(atual->data, data)) {
            printf("Jogador: %s | Movimentos: %d | Discos: %d | Data: %s\n",
                   atual->nome, atual->movimentos, atual->discos, atual->data);
            encontrou = 1;
        }
        atual = atual->prox;
    }
    if (!encontrou) printf("Nenhuma partida encontrada.\n");
}

// Função para inicializar o jogo
void inicializar_jogo() {
    for (int i = 0; i < 3; i++) inicializar_pilha(&torres[i]);
    // Empilhar discos em ordem crescente de cima para baixo (menor no topo)
    for (int i = num_discos; i >= 1; i--) {
        push(&torres[0], i);
    }
    movimentos = 0;
}

// Função principal do jogo
void jogar() {
    printf("Digite seu nome: ");
    scanf("%s", nome_jogador);
    printf("Digite o número de discos (3-8): ");
    scanf("%d", &num_discos);
    if (num_discos < 3 || num_discos > 8) {
        printf("Número inválido! Usando 3 discos.\n");
        num_discos = 3;
    }

    inicializar_jogo();
    while (!verificar_vitoria()) {
        exibir_torres();
        printf("Digite a torre de origem e destino (ex: 1 2) ou 0 0 para sair: ");
        int origem, destino;
        scanf("%d %d", &origem, &destino);
        if (origem == 0 && destino == 0) break;
        if (origem < 1 || origem > 3 || destino < 1 || destino > 3) {
            printf("Torres inválidas!\n");
            continue;
        }
        mover_disco(origem, destino);
    }
    if (verificar_vitoria()) {
        exibir_torres();
        printf("Parabéns, %s! Você venceu em %d movimentos!\n", nome_jogador, movimentos);
        salvar_historico();
    }
}

// Menu principal
int main() {
    carregar_historico();
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
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);

    // Liberar memória
    Historico* atual = historico;
    while (atual) {
        Historico* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    for (int i = 0; i < 3; i++) {
        while (torres[i].topo) pop(&torres[i]);
    }

    return 0;
}