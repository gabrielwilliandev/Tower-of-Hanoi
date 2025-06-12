#include <stdio.h>
#include <stdlib.h>
#include "discos.h"
#include "historico.h"


// Menu principal
int main() {
    Lista* historico = NULL;
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
                //jogar(historico);
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