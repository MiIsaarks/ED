#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho 11

typedef struct Aluno
{
    int matricula;
    char nome[50];
    char curso[100];
    int disponibilidade;
}Aluno;

int hash(int matricula){
    return matricula % tamanho;
}


void inicializar(char *Arq){
    FILE *arq = fopen(Arq, "wb");
    if(arq == NULL){
        printf("Erro ao criar arquivo\n");
        return;
    }
    Aluno a;
    int i;
    a.matricula = 0;
    memset(a.nome, 0, 50);
    memset(a.curso, 0, 100);
    a.disponibilidade = 1;
    for(i = 0; i < tamanho; i++){
        fwrite(&a, sizeof(Aluno), 1, arq);
    }
    fclose(arq);
}


int AcharPosicao(char *Arq, int x){
    int pos = hash(x);
    Aluno a;
    FILE *arq = fopen(Arq, "rb");
    if(arq == NULL) return -1;
    fseek(arq, pos*sizeof(Aluno), SEEK_SET);
    fread(&a, sizeof(Aluno), 1, arq);
    while(a.disponibilidade == 0){
        pos = (pos+1)%tamanho;
        fseek(arq, pos*sizeof(Aluno), SEEK_SET);
        fread(&a, sizeof(Aluno), 1, arq);
    }
    fclose(arq);
    return pos;
}

void inserir(char *Arq, int x, char *nome, char *curs){
    int pos = AcharPosicao(Arq, x);
    if(pos == -1) return;
    FILE *arq = fopen(Arq, "r+b");
    if(arq == NULL) return;
    Aluno a;
    a.matricula = x;
    strncpy(a.nome, nome, 49);
    a.nome[49] = '\0';
    strncpy(a.curso, curs, 99);
    a.curso[99] = '\0';
    a.disponibilidade = 0;
    fseek(arq, pos*sizeof(Aluno), SEEK_SET);
    fwrite(&a, sizeof(Aluno), 1, arq);
    fclose(arq);
}

void buscar_aluno(char *Arq){
    FILE *arq = fopen(Arq, "rb");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    int mat; 
    printf("\nDigite a matricula: ");
    scanf("%d", &mat);
    getchar();  // consume the newline

   int pos = hash(mat);
   int pos_aux = pos;
    Aluno a;
    int found = 0;
    do{
        fseek(arq, pos_aux*sizeof(Aluno), SEEK_SET);
        fread(&a, sizeof(Aluno), 1, arq);

        if(a.matricula == mat && a.disponibilidade == 0){
            printf("Aluno: %s\n", a.nome);
            printf("Curso: %s\n", a.curso);
            printf("Matricula %d\n", a.matricula);
            found = 1;
            break;
        }
        pos_aux = (pos_aux + 1) % tamanho;

    }while(pos != pos_aux);

    if(!found){
        printf("Aluno nao encontrado\n");
    }
}

void imprimir(char *Arq){
    FILE *arq = fopen(Arq, "rb");
    if(arq == NULL){
        printf("Erro ao ler o arquivo");
        return;
    } 

    Aluno a;
    printf("\n==================== TABELA HASH EM ARQUIVO ====================\n");
    printf("%-5s | %-10s | %-20s | %-20s\n", "Pos", "Matrícula", "Nome", "Curso");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < tamanho; i++) {
        fread(&a, sizeof(Aluno), 1, arq);
        if (a.disponibilidade == 0) {
            printf("[%02d]  | %-10d | %-20s | %-20s\n", i, a.matricula, a.nome, a.curso);
        } else {
            printf("[%02d]  | %-10s | %-20s | %-20s\n", i, "---", "[Livre]", "---");
        }
    }
    printf("================================================================\n");

    fclose(arq);
}

int main(){
    char *Arq = "Hash.dat";
    int opcao = 0;
    inicializar(Arq);
    int espaco = tamanho;

    while(opcao != 4){
        printf("\n1 - Inserir um novo elemento\n");
        printf("2 - Imprimir informacoes de um aluno\n");
        printf("3 - Imprimir tabela de dispersao\n");
        printf("4 - Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &opcao);
        getchar();  // consume the newline

        switch(opcao){
            case 1: {
                
                if(espaco != 0){
                    espaco -= 1;
                int x;
                char nome[50];
                char curso[50];
                printf("\nInsira a matricula do Aluno: ");
                scanf("%d", &x);
                getchar();  // consume the newline
                printf("Insira o nome do aluno: ");
                fgets(nome, 50, stdin);
                // Remove newline from nome
                nome[strcspn(nome, "\n")] = 0;
                printf("insira o curso do aluno: ");
                fgets(curso, 50, stdin);
                // Remove newline from curso
                curso[strcspn(curso, "\n")] = 0;
                inserir(Arq, x, nome, curso);
                printf("Aluno inserido com sucesso!\n");
                }else{
                    printf("\nTabela lotada\n");
                }
                break;
            }
            case 2:
                buscar_aluno(Arq);
                break;
            case 3:
                imprimir(Arq);
                break;
            case 4:
                printf("Saindo...\n");
                break;
        }
    }
    return 0;
}
