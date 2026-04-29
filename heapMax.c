#include <stdio.h>
#include <stdlib.h>

int heap[100];
int QntElemntos = 0;

int FilhoE(int x){
    int indice = (2*x)+1;
    if(x >= QntElemntos || indice >= QntElemntos){
        return -1;
    }
    return indice;
}

int FilhoD(int x){
    int indice = (2*x)+2;
    if(x >= QntElemntos || indice >= QntElemntos){
        return -1;
    }
    return indice;
}

int Pai(int x){
    int indice = (x-1)/2;
    if(indice < 0 || x > QntElemntos){
        return -1;
    }
    return indice;
}

void ajustar(int x, int *heap){
    if(x != -1){
        int p = Pai(x);
        if(p != -1){
        if(heap[p] < heap[x]){
            int aux = heap[p];
            heap[p] = heap[x];
            heap[x] = aux;
            ajustar(p, heap);
        }
    }
    }
}

void InsertH(int x, int *heap){
   heap[QntElemntos] = x;
     QntElemntos += 1;

     ajustar(QntElemntos - 1, heap);
}



void ajustardown(int *heap, int x){
    if(x != -1){
        int maior;
    int fd = FilhoD(x);
    int fe = FilhoE(x);
    if(fe != -1){
        maior = fe;
        if(fd != -1){

    if(heap[fd] > heap[fe]){
        maior =fd;
    }
    }
        if(heap[maior] > heap[x]){
        int aux = heap[x];
        heap[x] = heap[maior] ;
        heap[maior] = aux;
        ajustardown(heap, maior);
        }
   
    }
}
}

int remover(int *heap){
    if(QntElemntos == 0){
        return -1;
    }

    int aux = heap[0];
    heap[0] = heap[QntElemntos-1];
    QntElemntos -= 1;
    ajustardown(heap, 0);

    return aux;
}



int main(){
    int x = 0;
    while(x != 4){
        printf("\nO que deseja fazer? ");
        printf("\n1 - Inserir um elemento na heap");
        printf("\n2 - Remover um elemento da heap");
        printf("\n3 - Imprimir o heap");
        printf("\n4 - Sair\n");
        scanf("%d", &x);

        if(x == 1){
            int y;
            printf("\nQual valor sera inserido? ");
            scanf("%d", &y);
            InsertH(y, heap);
        }

        if(x == 2){
            int y = remover(heap);
            printf("\nValor removido: %d", y);
        }

        if(x == 3){
            for(int y = 0; y < QntElemntos; y++){
                printf("%d ", heap[y]);
            }
        }
    }
}