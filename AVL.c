#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    struct TreeNode *left;
    struct TreeNode *right;
    int info;
    int FB;
} TreeNode;

TreeNode *ReadTree(FILE *f)
{
    char c;
    int n;

    fscanf(f, "%c", &c);
    fscanf(f, "%d", &n);

    if (n == -1)
    {
        fscanf(f, "%c", &c);
        return NULL;
    }
    else
    {
        TreeNode *node = malloc(sizeof(TreeNode));

        node->info = n;
        node->left = ReadTree(f);
        node->right = ReadTree(f);

        fscanf(f, "%c", &c);

        return node;
    }
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

int Acha_Nivel(TreeNode *a, int cont, int y)
{
    int r;
    if (a != NULL)
    {
        if (a->info == y)
        {
            printf("\nNivel: %d", cont);
            return 1;
        }

        if (y < a->info)
        {
            int r = Acha_Nivel(a->left, cont + 1, y);
        }

        if (y > a->info)
        {
            int r = Acha_Nivel(a->right, cont + 1, y);
        }

        if (r >= 1)
        {
            return 1;
        }
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

void AjustarFB(TreeNode *a)
{
    if (a != NULL)
    {
        int he = height(a->left);
        int hd = height(a->right);
        a->FB = hd - he;

        AjustarFB(a->left);
        AjustarFB(a->right);
    }
}

TreeNode *RotacaoEsqSimples(TreeNode *a)
{

    TreeNode *x = a;
    TreeNode *y = x->right;

    x->right = y->left;
    y->left = x;
    if (y->FB == 1)
    {
        x->FB = 0;
        y->FB = 0;
    }
    else
    {
        x->FB = 1;
        y->FB = -1;
    }
    a = y;
    return a;
}

TreeNode *RotacaoEsqDupla(TreeNode *r)
{
    TreeNode *a = r;
    TreeNode *c = a->right;
    TreeNode *b = c->left;

    c->left = b->right;
      b->right = c;
    a->right = b->left;
    b->left = a;
  

    switch (b->FB)
    {
    case -1:
        a->FB = 0;
        c->FB = 1;
        break;

    case 0:
        a->FB = 0;
        c->FB = 0;
        break;

    case +1:
        a->FB = -1;
        c->FB = 0;
        break;
    }
    b->FB = 0;

    r = b;
    return r;
}

TreeNode *RotacaoLeft(TreeNode *a)
{
    if (a->right->FB == -1)
    {
        a = RotacaoEsqDupla(a);
    }
    else
    {
        a = RotacaoEsqSimples(a);
    }
    return a;
}

TreeNode *RotacaoDirSimples(TreeNode *r)
{

    TreeNode *a = r->left;
    TreeNode *b = r;
    b->left = a->right;
    a->right = b;
    if (a->FB == -1)
    {
        a->FB = 0;
        b->FB = 0;
    }
    else
    {
        a->FB = 1;
        b->FB = -1;
    }
    r = a;
    return r;
}

TreeNode *RotacaoDirDupla(TreeNode *r)
{

    TreeNode *c = r;
    TreeNode *a = c->left;
    TreeNode *b = a->right;
    a->right = b->left;
     b->left = a;
    c->left = b->right;
    b->right = c;

    switch (b->FB)
    {
    case -1:
        a->FB = 0;
        c->FB = 1;
        break;
    case 0:
        a->FB = 0;
        c->FB = 0;
        break;
    case +1:
        a->FB = -1;
        c->FB = 0;
        break;
    }
    b->FB = 0;
    r = b;
    return r;
}

TreeNode *RotacaoDir(TreeNode *r)
{
    if (r->left->FB == 1)
        r = RotacaoDirDupla(r);
    else
        r = RotacaoDirSimples(r);
    return r;
}

TreeNode *insert(TreeNode *r, int x, int *hMudou)
{
    if (r == NULL) // Momento de inserir
    {
        r = (TreeNode *)malloc(sizeof(TreeNode));
        r->info = x;
        r->left = NULL;
        r->right = NULL;
        r->FB = 0;
        *hMudou = 1;
    }
    else
    {
        if (x <= r->info)

        {
            r->left = insert(r->left, x, hMudou);
            if (*hMudou == 1)
            {

                switch (r->FB)

                {
                case -1:
                    r = RotacaoDir(r);
                    *hMudou = 0;
                    break;
                case 0:
                    r->FB = -1;
                    *hMudou = 1;
                    break;
                case +1:
                    r->FB = 0;
                    *hMudou = 0;
                    break;
                }
            }
        }
        else
        {
            r->right = insert(r->right, x, hMudou);
            if (*hMudou == 1)

            {
                switch (r->FB)
                {
                case -1:

                    r->FB = 0;
                    *hMudou = 0;
                    break;
                case 0:
                    r->FB = +1;
                    *hMudou = 1;
                    break;
                case +1:
                    r = RotacaoLeft(r);
                    *hMudou = 0;
                    break;
                }
            }
        }
    }
    return r;
}
TreeNode *remover(TreeNode *a, int x, int *mudou)
{
    if (a != NULL)
    {
        if (a->info == x)
        {
            if (a->left == NULL && a->right == NULL)
            {
                free(a);
                *mudou = 1;
                return NULL;
            }
            else if (a->left == NULL)
            {
                TreeNode *new = a->right;
                free(a);
                *mudou = 1;
                return new;
            }
            else if (a->right == NULL)
            {
                TreeNode *new = a->left;
                free(a);
                *mudou = 1;
                return new;
            }
            else
            {
                TreeNode *temp = a->left;
                while (temp->right != NULL)
                {
                    temp = temp->right;
                }
                a->info = temp->info;
                a->left = remover(a->left, temp->info, mudou);
            }
            if (*mudou == 1)
            {
                switch (a->FB)
                {
                case -1:
                    a->FB = 0;
                    *mudou = 1;
                    break;

                case 0:
                    a->FB = 1;
                    *mudou = 0;
                    break;

                case +1:
                    int aux = a->right->FB;
                    a = RotacaoLeft(a);

                    if (aux == 0)
                    {
                        *mudou = 0;
                    }
                    else
                    {
                        *mudou = 1;
                    }
                    break;
                }
            }
        }

        else if (x < a->info)
        {
            a->left = remover(a->left, x, mudou);
            if (*mudou == 1)
            {
                switch (a->FB)
                {
                case -1:
                    a->FB = 0;
                    *mudou = 1;
                    break;

                case 0:
                    a->FB = 1;
                    *mudou = 0;
                    break;

                case 1:
                    int aux = a->right->FB;
                    a = RotacaoLeft(a);

                    if (aux == 0)
                    {
                        *mudou = 0;
                    }
                    else
                    {
                        *mudou = 1;
                        break;
                    }
                }
            }
        }
        else
        {
            a->right = remover(a->right, x, mudou);
            if (*mudou == 1)
            {
                switch (a->FB)
                {
                case 1:
                    a->FB = 0;
                    *mudou = 1;
                    break;

                case 0:
                    a->FB = -1;
                    *mudou = 0;
                    break;

                case -1:
                    int aux = a->left->FB;
                    a = RotacaoDir(a);
                    if (aux == 0)
                    {
                        *mudou = 0;
                    }
                    else
                    {
                        *mudou = 1;
                        break;
                    }
                }
            }
        }
    }
    return a;
}

int exist(TreeNode *node, int x)
{

    if (node != NULL)
    {
        if (node->info == x)
            return 1;
        if (node->info > x)
            return exist(node->left, x);
        else
            return exist(node->right, x);
    }
    return 0;
}

void leavesNode(TreeNode *node, int x)
{
    if (node != NULL)
    {
        if (node->left == NULL && node->right == NULL)
        {
            if (x > node->info)
            {
                printf("%d ", node->info);
            }
        }
        if (node->info > x)
        {
            leavesNode(node->left, x);
        }
        else
        {
            leavesNode(node->left, x);
            leavesNode(node->right, x);
        }
    }
}

int main()
{
    int choice = 0;
    int mudou = 0;
    TreeNode *rootNode;
    FILE *f;

    while (choice != 9)
    {
        printf("\n");
        printf("1- Ler uma arvore de um arquivo fornecido pelo usuario\n");
        printf("2- Imprimir a arvore (opcoes: pre-ordem; em-ordem; pos-ordem; largura)\n");
        printf("3- Verificar se um elemento x existe na arvore\n");
        printf("4- Imprimir o nivel ao qual o no x pertence\n");
        printf("5- Imprimir os nos folhas da arvore menores que um x \n");
        printf("6- Inserir um no x na arvore\n");
        printf("7- Remover um no x da arvore\n");

        printf("9- Sair\n");
        printf("\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Digite o nome do arquivo: ");

            char fileName[100];
            scanf("%s", fileName);

            f = fopen(fileName, "r");
            if (f == NULL)
            {
                printf("O arquivo nao existe\n");
            }
            rootNode = ReadTree(f);
            AjustarFB(rootNode);
            printf("Arvore lida\n");
        }

        if (choice == 2)
        {
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
        }

        if (choice == 3)
        {
            int elem;
            printf("Escolha o elemento que voce quer achar na arvore: ");
            scanf("%d", &elem);

            if (exist(rootNode, elem) == 1)
            {
                printf("O elemento %d existe na arvore\n", elem);
            }
            else
            {
                printf("O elemento %d nao existe na arvore\n", elem);
            }
        }

        if (choice == 4)
        {
            int a;
            printf("\nO nivel de qual no voce deseja encontrar? ");
            scanf("%d", &a);
            if (Acha_Nivel(rootNode, 0, a) != 1)
            {
                printf("\nNao esta na arvore");
            }
        }

        if (choice == 5)
        {
            int x;
            printf("O no folha deve ser menor que: ");
            scanf("%d", &x);

            printf("Os nos folhas sao: ");
            leavesNode(rootNode, x);
        }

        if (choice == 6)
        {
            int x;
            printf("Qual valor voce quer inserir na arvore ");
            scanf("%d", &x);
            rootNode = insert(rootNode, x, &mudou);
        }

        if (choice == 7)
        {
            int x;
            printf("Qual valor voce deseja remover: ");
            scanf("%d", &x);
            rootNode = remover(rootNode, x, &mudou);
        }
    }

    return 0;
}