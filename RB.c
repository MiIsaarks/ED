#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    struct TreeNode *left;
    struct TreeNode *right;
    int info;
    char cor;
} TreeNode;

TreeNode *ReadTree(FILE *f)
{
    char c;
    int n;

    // Skip opening parenthesis
    fscanf(f, " %c", &c);
    
    // Read the value
    if (fscanf(f, "%d", &n) != 1) {
        return NULL;
    }

    if (n == -1)
    {
        // Skip closing parenthesis for NULL node
        fscanf(f, " %c", &c);
        return NULL;
    }
    
    // Read the color (p or v)
    fscanf(f, " %c", &c);
    
    TreeNode *node = malloc(sizeof(TreeNode));
    node->info = n;
    node->cor = c;
    
    // Read left and right subtrees
    node->left = ReadTree(f);
    node->right = ReadTree(f);
    
    // Skip closing parenthesis
    fscanf(f, " %c", &c);

    return node;
}
void printTreePre(TreeNode *node)
{
    if (node != NULL)
    {
        printf("%d ", node->info);
        printTreePre(node->left);
        printTreePre(node->right);
    }
}

void printTreeIn(TreeNode *node)
{
    if (node != NULL)
    {
        printTreeIn(node->left);
        printf("%d ", node->info);
        printTreeIn(node->right);
    }
}

void printTreePos(TreeNode *node)
{
    if (node != NULL)
    {
        printTreePos(node->left);
        printTreePos(node->right);
        printf("%d ", node->info);
    }
}

void printLevel(TreeNode *a, int cont, int nivel)
{
    if (a != NULL)
    {
        if (cont == nivel)
            printf("%d ", a->info);
        else
        {
            printLevel(a->left, cont + 1, nivel);
            printLevel(a->right, cont + 1, nivel);
        }
    }
}

void printTreeWidth(TreeNode *node, int h)
{
    for (int i = 0; i < h; i++)
    {
        printLevel(node, 0, i);
        printf("\n");
    }
}

int height(TreeNode *a)
{
    if (a == NULL)
    {
        return 0;
    }
    else
    {
        int he = height(a->left);
        int hd = height(a->right);
        if (he > hd)
        {
            return he + 1;
        }
        else
        {
            return hd + 1;
        }
    }
}

int heightN(TreeNode *a){
    if(a == NULL){
        return 0;
    }else{
        int he = heightN(a->left);
        int hd = heightN(a->right);
      
            if(he >= hd && a->cor == 'p'){
                return he + 1;
            }else if(he <= hd && a->cor == 'p'){
                return hd + 1;
            }else  if(he >= hd){
                return he;
            }else{
                return hd;
            }
        }
    }

    int exist(TreeNode *a, int x){
        if(a == NULL){
            return 0;
        }

        if(a->info == x){
            return 1;
        }

        if(a->info > x){
           return exist(a->left, x);
        }else{
            return exist(a->right, x);
        }
    }

    int doubleRed(TreeNode *a){
        if(a == NULL){
            return 0;
        }

        if(a->left != NULL){
        if(a->cor == 'v' && a->left->cor == 'v' ){
            return 1;
        }
    }
        if( a->right != NULL){
        if(a->cor == 'v' && a->right->cor == 'v' ){
            return 1;
        }
    }
        return doubleRed(a->left) + doubleRed(a->right);
        
    }


int main(){
     TreeNode *rootNode;
    FILE *f;

     printf("Digite o nome do arquivo: ");

            char fileName[100];
            scanf("%s", fileName);

            f = fopen(fileName, "r");
            if (f == NULL)
            {
                printf("O arquivo nao existe\n");
            }
            rootNode = ReadTree(f);
            fclose(f);
          
            printf("Arvore lida\n");



             if (rootNode == NULL)
            {
                printf("A arvore nao existe\n");
            }
            else
            {
                int choice2;
                printf("1 - pre-ordem\n");
                printf("2 - em-ordem\n");
                printf("3 - pos-ordem\n");
                printf("4 - largura\n");
                printf("Digite a ordem em que voce quer imprimir: ");

                scanf("%d", &choice2);

                if (choice2 == 1)
                    printTreePre(rootNode);
                if (choice2 == 2)
                    printTreeIn(rootNode);
                if (choice2 == 3)
                    printTreePos(rootNode);
                if (choice2 == 4)
                    printTreeWidth(rootNode, height(rootNode));
            }

            printf("\naltura negra: %d", heightN(rootNode));

              int elem;
            printf("\nEscolha o elemento que voce quer achar na arvore: ");
            scanf("%d", &elem);

            if (exist(rootNode, elem) == 1)
            {
                printf("O elemento %d existe na arvore\n", elem);
            }
            else
            {
                printf("O elemento %d nao existe na arvore\n", elem);
            }

            if(doubleRed(rootNode) >= 1){
                printf("\nDois vermelhos consecutivos");
            }else{
                printf("\nTudo certo");
            }

            return 0;
}