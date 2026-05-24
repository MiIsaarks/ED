#include <stdio.h>
#include <stdlib.h>

void  comb(char *v, int n, int pos, char *u){
    int ci = 0;
    int ce = 0;
    if(pos == n){
         for(int i = 0; i<pos; i++){
           if(v[i] == 'i'){
            ci++;
           }else if(v[i] == 'e'){
            ce++;
           }
        }
        if(ci > ce){
        for(int i = 0; i<pos; i++){
            printf("%c ", v[i]);
        }
        printf("\n");
    }
    }else{
   for(int i = 0; i < n; i++){
    v[pos] = u[i];
    comb(v, n, pos + 1, u);
   }
    }
    
}

int main(){
    char v[3];
    char u[3] = {'a', 'e', 'i'};
    comb(v, 3, 0, u);
}