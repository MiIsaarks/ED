#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int destino;
    int custo;
    struct lista *prox;
} lista;

void inicializar(lista **g, int n){
    for(int i = 0; i <= n; i++){
        g[i] = NULL;
    }
}

lista* InserirLista(lista *l, int d, int c){
    lista *no = (lista *)malloc(sizeof(lista));
    no->destino = d;
    no->custo = c;
    no->prox = l;
    return no;
}

void inserirAresta(lista **g, int origem, int destino, int custo){
    g[origem] = InserirLista(g[origem], destino, custo);
}

void removerAresta(lista **g, int origem, int destino){
    lista *atual = g[origem];
    lista *anterior = NULL;
    while(atual != NULL && atual->destino != destino){
        anterior = atual;
        atual = atual->prox;
    }
    if(atual != NULL){
        if(anterior == NULL){
            g[origem] = atual->prox;
        } else{
            anterior->prox = atual->prox;
        }
        free(atual);
        }
    }

    void imprimirLista(lista *l){
    if(l != NULL){
        printf("-(%d, %d)", l->destino, l->custo);
        imprimirLista(l->prox);
    }
}

void imprimirGrafo(lista **g, int n){
    printf("Grafo:\n");
    for(int i = 0; i <= n; i++){
        printf("\n\t%d", i);
        imprimirLista(g[i]);
    }
}

void Grau(lista **g, int n, int v){
    int grauentrada = 0;
    for(int i = 0; i<= n; i++){
          lista *atual = g[i];
          while(atual != NULL){
            if(atual->destino == v){
                grauentrada++;
            }
            atual = atual->prox;
          }
    }

    int grauSaida = 0;
    lista *atual = g[v];
    while(atual != NULL){
        grauSaida++;
        atual = atual->prox;
    }
    printf("Grau de entrada de %d: %d\n", v, grauentrada);
    printf("Grau de saida de %d: %d\n", v, grauSaida);
}

void grafoCompleto(lista **g, int n){
    for(int i = 0; i <= n; i++){
        int full = 0;
        lista *atual = g[i];
        while(atual != NULL){
            full++;
            atual = atual->prox;
        }
        if(full != n-1){
            printf("O grafo nao eh completo\n");
            return;
        }
    }
    printf("O grafo é completo\n");
}

int main(){
    int origem, destino, custo;
    int n;
    int opcoes = 0;
    printf("Digite o numero de vertices do grafo: ");
    scanf("%d", &n);
    lista **g = (lista **)malloc((n+1) * sizeof(lista *));
    inicializar(g, n);

    while(opcoes != 6){
        printf("\n1 - Inserir aresta\n");
        printf("2 - Remover aresta\n");
        printf("3 - Imprimir grafo\n");
        printf("4 - Imprimir os gruas de entrada e saida de um vertice\n");
        printf("5 - Verificar se o grafo e completo\n");
        printf("6 - Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcoes);

        switch(opcoes){
            case 1:
            printf("Digite a origem, destino e custo da aresta: ");
            scanf("%d %d %d", &origem, &destino, &custo);
            inserirAresta(g, origem, destino, custo);
            break;

            case 2:
            printf("Digite a origem e destino da aresta a ser removida: ");
            scanf("%d %d", &origem, &destino);
            removerAresta(g, origem, destino);
            break;

            case 3:
            imprimirGrafo(g, n);
            break;

            case 4:
            printf("Digite o vertice para calcular os graus de entrada e saida: ");
            scanf("%d", &origem);
            Grau(g, n, origem);
            break;

            case 5:
            grafoCompleto(g, n);
            break;
        }
    
        
    }
}