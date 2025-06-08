#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


int main(){
    int menu_opcao;

    do {
        printf("\n--Torre de Hanoi --\n");
        printf("1. Jogar\n");
        printf("2. Exibir Historico\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao (1 - 3): ");
        scanf("%d", &menu_opcao);

        
        switch(menu_opcao){
            case 1:
                jogar();
                break;
            case 2:
                exibir_historico();
                break;
            case 3:
                SalvarHist();
                DestruirLista();
                printf("Saindo...");
                break;
            default:
                printf("Opcao invalida! Tente novamente (1 - 3):\n");
            
        }

        while (menu_opcao != 3);
    
    }

    return 0;
}