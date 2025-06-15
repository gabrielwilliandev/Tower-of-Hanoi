#include <stddef.h>
#include <stdlib.h>
#ifndef LISTAH
#define LISTAH

typedef struct _no No;

typedef struct _lista Lista;

Lista *CriarLista();

No *CriarNo(char *nome, char *data, int mov, int qntd);

void DestruirLista(Lista **Lref);

void Obterdata(char *data, size_t tam);

void InserirInicio(Lista *L, char *nome, int mov, int qntd);

void SalvarHist(Lista *L, const char *historico);

void LerHist(Lista *L, const char *historico);

void carregar_historico(Lista *L);

void exibir_historico(Lista *L);

void buscar_por_nome(Lista *L, const char *nome);

void buscar_por_data(Lista *L, const char *data);

#endif