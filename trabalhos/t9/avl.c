#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include <string.h>
#include <sys/time.h>


/*funcao para pegar altura*/
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

/*funcao para pegar maximo de 2 inteiros*/

int max(  int a,  int b){
	 return (a > b)? a : b;
}

/*funcao auxiliar pra alocar o novo no e os ponteiros*/
struct Node* newNode(char key[],char arquivo[])
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));

	if (node == NULL) {
		printf("sem memoria\n");
		exit(1);
	}

	strcpy(node->nome,key);

	node->left   = NULL;
	node->right  = NULL;
	node->height = 1;
	node->cont = 1;

	node->a = NULL;  /*a partir daqui alocacao da lista*/
	node->a =  (Lista*)malloc(sizeof(Lista));
	if(node->a == NULL)exit(1);

	strcpy(node->a->info,arquivo);
	node->a->prox = NULL;

	return(node);
}

void push(Lista * head, char info[]) {       /*funcao que insere no fim na lista*/
    Lista* current = head;
    while (current->prox != NULL) {
        current = current->prox;
    }


    current->prox = malloc(sizeof(Lista));
    strcpy(	current->prox->info,info);
    current->prox->prox = NULL;
}

void print_list(Lista * head) {     /*funcao que imprime a lista*/
    Lista *current = head;

    while (current != NULL) {
        printf("%s-", current->info);
        current = current->prox;
    }
    printf("\n");
}

int compara(Lista *t, char var[] ){        /*funcao que so insere no fim da lista se vier de arquivo diferente*/
 	int cont = 0;
	while(t != NULL){
 		if(strcmp(t->info,var) != 0)
 			cont = 1;
 		else
 			cont = 0;

		 t= t->prox;
 	}
 	if(cont == 0)return 0;
 	else return 1;
 }

/*as rotacoes necessarias da arvore*/
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    /*aciona a rotacao*/
    x->right = y;
    y->left = T2;

    /*atualiza alturas*/
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    /*Retorna nova arvore*/
    return x;
}


struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    /*Perform rotation*/
    y->left = x;
    x->right = T2;

    /*Update heights*/
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    /*Return new root*/
    return y;
}

/*pega o fator de balancemeanto*/
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

/*funcao para inserir e chamar os balanceamentos caso necessario*/
struct Node* insert(struct Node* node, char key[],char arquivo[])
{
    /*insercao normal de BST*/
    if (node == NULL)
        return(newNode(key,arquivo));

    if ( strcmp(key,node->nome) < 0)        /*key < node->key*/
        node->left  = insert(node->left,key,arquivo);
    else if (strcmp(key,node->nome) > 0)        /*(key > node->key)*/
        node->right = insert(node->right,key,arquivo);
    else{ /* elementos iguas nao sao permitidos BST mas foi feito um contador pois pode ocorrer varias vezes a mesma string e tambem e necessario armazenar o arquivo de origem*/
        node->cont = node->cont + 1;
    	if(compara(node->a,arquivo) == 1)push(node->a,arquivo);

		return node;
		}

    node->height = 1 + max(height(node->left),
                           height(node->right));
    int balance = getBalance(node);

    /*Se ficou nao balanceada chama um dos 4 casos possives, caso esteja balanceada retorna normal*/

    if (balance > 1 && strcmp(key,node->left->nome) < 0) /*key < node->left->key)*/
        return rightRotate(node);

    if (balance < -1 && strcmp(key,node->right->nome) > 0) /*key > node->right->key)*/
        return leftRotate(node);

    if (balance > 1 && strcmp(key,node->left->nome) > 0)/*key > node->left->key)*/
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && strcmp(key,node->right->nome) < 0)/*/key < node->right->key)*/
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/*print em preordem*/
void preOrder(struct Node *root)
{
	if(root != NULL)
  {
		printf("valor :%s    contador:%llu   \n", root->nome,root->cont);
		print_list(root->a);
		preOrder(root->left);
		preOrder(root->right);
	}
}

/*busca um noh na arvore a partir de uma string*/
void search_tree(struct Node *root,char* elemento){
	if(root != NULL){
		if(strcmp(root->nome,elemento) == 0 ){
			printf("Palavra:%s    contador:%llu    ", root->nome,root->cont);
			print_list(root->a);
		}
		else if(strcmp(root->nome,elemento) > 0)
			search_tree(root->left,elemento);
		else if(strcmp(root->nome,elemento) < 0)
			search_tree(root->right,elemento);
	}
	else
		printf("Palavra:%s nao encontrado \n", elemento);

}
/*funcao que libera a lista da arvore, chamada na libera da arvore*/
void libera_lis(Lista *LISTA)
{
	if(LISTA != NULL ){
		Lista *proxNode,*atual;
		atual = LISTA->prox;
		while(atual != NULL){
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}

/*libera as alocacoes da arvore*/
void libera(struct Node *p)
{
	struct Node* d;
	if (p != NULL)
	{
		libera(p->left);
		libera(p->right);
		d=p;
		libera_lis(d->a);
		free(d);
		p=NULL;
	}
}

long wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec*1000000 + t.tv_usec;
}

