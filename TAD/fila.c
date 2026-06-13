#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

#define tamanho 1024

struct fila{
    int info[tamanho];
    int n;
    int inicio;
    int fim;
};

Fila inicializar(){
    Fila F = malloc(sizeof(struct fila));
    F->n = 0;
    F->inicio = F->fim = 0;
    return F;
}

Fila destriur(Fila F){
    free(F);
    return NULL;
}

int vazio(Fila F){
    if(F->n == 0){
        return 1;
    }else{
        return 0;
    }
}

void inserir(Fila F, int x){
    if(F->n < tamanho){
        F->info[F->fim] = x;
        F->n++;
        F->fim = F->fim + 1;
    }
}

void remover(Fila F, int* x){
    if(!vazio(F)){
        *x = F->info[F->inicio];
        F->n--;
        F->inicio = F->inicio + 1;
    }
}
void imprimir(Fila F){
    for(int i = F->inicio; i < F->fim; i++){
        printf("%d ", F->info[i]);
    }
    printf("\n");
}