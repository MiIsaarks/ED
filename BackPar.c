#include <stdio.h>
#include <stdlib.h>

void par(int *v, int n, int pos, int *u){
    int soma = 0;
    if(pos == n){
        for(int i = 0; i<pos; i++){
            soma += v[i];
        }
        if(soma % 2 == 0){
            for(int i = 0; i < pos; i++){
                printf("%d ", v[i]);
            }
            printf("\n");
        }
    }else{
        for(int i = 0; i < n; i++){
            v[pos] = u[i];
            par(v, n, pos + 1, u);
        }
    }
}

int main(){
    int v[4];
    int u[4] = {15, 31, 55, 44};
    par(v, 4, 0, u);
}