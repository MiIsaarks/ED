#include <stdio.h>
#include <stdlib.h>

void Verdades(int *v, int n, int pos){
    if(pos == n){
        if((v[0]&&v[1])||(v[2]&&v[3])){
            for(int i = 0; i < pos; i++){
                if(v[i]== 1){
                    printf("v ");
                }else{
                    printf("f ");
                }
               
            }
             printf("\n");
        }
    }else{
        for(int i = 0; i <= 1; i++){
            v[pos] = i;
            Verdades(v, n, pos + 1);
        }
    }
}

int main(){
    int v[4];
    Verdades(v, 4, 0);
}