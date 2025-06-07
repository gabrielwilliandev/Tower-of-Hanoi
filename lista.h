#include <stddef.h>
#include <stdlib.h>
#ifndef LISTAH
#define LISTAH



typedef struct _no No;

typedef struct _lista Lista;

Lista *CriarLista();

No *CriarNo(int val);

void DestruirLista(Lista **Lref);

void Obterdata(char *data, size_t tam);

void InserirInicio(Lista *L, char *nome, int mov, int qntd);

void SalvarHist(Lista *L, const char *historico);

void LerHist(Lista *L, const char *historico);




#endif 