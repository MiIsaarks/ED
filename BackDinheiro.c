#include <stdio.h>
#include <stdlib.h>

void Conta(int valor, int *moedas, int *comb, int ind){
    if(valor == 0){
        for(int i = 0; i < 5; i++){
            if(comb[i] > 0){
                printf("\n%d moedas de %d", comb[i], moedas[i]);
            }
            
        }
        printf("\n");
        return;
    }
    if(valor < 0 || ind >= 5){
        return;
    }
    int moeda = moedas[ind];
    int valor_max = valor/moeda;
    for(int qtd = valor_max; qtd >= 0; qtd --){
        comb[ind] = qtd;
        Conta(valor - qtd*moeda, moedas, comb, ind + 1);
    }
}

int main(){
    int moedas[5] = {50, 25, 10, 5, 1};
    int comb[5] = {0, 0, 0, 0, 0};
    int valor;
    printf("insira o valor em centavos: ");
    scanf("%d", &valor);
    Conta(valor, moedas, comb, 0);
}