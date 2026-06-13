#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main(){
    int opcao = 0;
    int x;
    Fila a = inicializar();
    while(opcao != 4){
       
        printf("1 - Inserir um elemento na fila\n");
        printf("2 - Remover um elemento na fila\n");
        printf("3 - Imprimir a fila\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
            printf("Qual elemento você deseja inserir: ");
            scanf("%d", &x);
            inserir(a, x);
            break;

            case 2:
            remover(a, &x);
            printf("Item removido %d\n", x);
            break;

            case 3:
            printf("Imprimindo fila\n");
            imprimir(a);
            break;
            }
    }

    a = destriur(a);
}