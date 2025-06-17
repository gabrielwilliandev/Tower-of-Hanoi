#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "discos.h"
#include "historico.h"

// Menu principal
int main() {
    historico = CriarLista();
    carregar_historico(historico);
    int opcao;
    char busca[50];
    do {
        printf("\n=== Torre de Hanoi ===\n");
        printf("1. Jogar\n2. Exibir historico\n3. Buscar por nome\n4. Buscar por data\n5. Ajuda\n6.Sair\n");
        printf("Escolha uma opcao: ");
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
                exibirAjuda();
                break;
            case 6:
                printf("Saindo\n");
                break;
            default:
                printf("Opção invalida!\n");
        }
    } while (opcao != 6);

    DestruirLista(&historico);
    return 0;
}