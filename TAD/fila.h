#pragma once

typedef struct fila *Fila;

Fila inicializar();

Fila destriur(Fila F);

int vazio(Fila F);

void inserir(Fila Q, int x);

void remover(Fila F, int *x);

void imprimir(Fila F);
