#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct _no {
    int mov;
    int qntd;
    char nome[30];
    char data[11];
    struct _no *prox;
    struct _no *ant;
} No;

typedef struct _lista {
    No *inicio;
    No *fim;
    size_t tam;
} Lista;

Lista *CriarLista() {
    Lista *L = (Lista*)calloc(1, sizeof(Lista));
    if (L == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    L->inicio = NULL;
    L->fim = NULL;
    L->tam = 0;
    return L;
}

No *CriarNo(char *nome, char *data, int mov, int qntd) {
    No *p = (No*)calloc(1, sizeof(No));
    if (p == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    p->mov = mov;
    p->qntd = qntd;
    strncpy(p->nome, nome, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0';
    strncpy(p->data, data, sizeof(p->data) - 1);
    p->data[sizeof(p->data) - 1] = '\0';
    p->prox = NULL;
    p->ant = NULL;
    return p;
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

void Obterdata(char *data, size_t tam) {
    time_t hoje = time(NULL);
    struct tm *data_local = localtime(&hoje);
    int dia = data_local->tm_mday;
    int mes = data_local->tm_mon + 1;
    int ano = data_local->tm_year + 1900;
    snprintf(data, tam, "%02d/%02d/%04d", dia, mes, ano);
}

void InserirInicio(Lista *L, char *nome, int mov, int qntd) {
    char data[11];
    Obterdata(data, sizeof(data));
    No *p = CriarNo(nome, data, mov, qntd);
    p->prox = L->inicio;
    if (L->tam == 0) {
        L->fim = p;
    } else {
        L->inicio->ant = p;
    }
    L->inicio = p;
    L->tam++;
}

void SalvarHist(Lista *L, const char *historico) {
    FILE *f = fopen(historico, "w");
    if (f == NULL) {
        printf("Erro ao abrir arquivo para escrita!\n");
        exit(1);
    }
    No *p = L->inicio;
    while (p != NULL) {
        fprintf(f, "%s;%s;%d;%d\n", p->nome, p->data, p->mov, p->qntd);
        p = p->prox;
    }
    fclose(f);
}

void LerHist(Lista *L, const char *historico) {
    FILE *f = fopen(historico, "r");
    if (f == NULL) {
        return; // Arquivo pode não existir ainda
    }
    char linha[256];
    while (fgets(linha, sizeof(linha), f)) {
        char nome[30], data[11];
        int mov, qntd;
        if (sscanf(linha, "%[^;];%[^;];%d;%d", nome, data, &mov, &qntd) == 4) {
            InserirInicio(L, nome, mov, qntd);
        }
    }
    fclose(f);
}

void carregar_historico(Lista *L) {
    LerHist(L, "historico.txt");
}

void exibir_historico(Lista *L) {
    No* atual = L->inicio;
    if (!atual) {
        printf("Historico vazio!\n");
        return;
    }
    printf("\n=== Historico de Partidas ===\n");
    while (atual) {
        printf("Nome: %s | Data: %s | Movimentos: %d | Discos: %d\n",
               atual->nome, atual->data, atual->mov, atual->qntd);
        atual = atual->prox;
    }
}

void buscar_por_nome(Lista *L, const char* nome) {
    No* atual = L->inicio;
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

void buscar_por_data(Lista *L, const char* data) {
    No* atual = L->inicio;
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
