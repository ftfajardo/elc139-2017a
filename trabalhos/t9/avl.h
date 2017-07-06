#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#define tam_max 100
struct Node
{
    char nome[tam_max];
    struct Node *left;
    struct Node *right;
    unsigned long long int height;
    unsigned long long int cont;
    struct lis * a;
};


typedef struct lis{
	struct lis* prox;
	char info[100];
}Lista;


/*funcao para pegar altura*/
unsigned long long int height(struct Node *N);

/*funcao para pegar maximo de 2 inteiros*/
unsigned long long int max(unsigned long long int a,unsigned long long int b);

/*funcao auxiliar pra alocar o novo no e os ponteiros*/
struct Node* newNode(char key[],char arquivo[]);

void push(Lista * head, char info[]);

void print_list(Lista * head);

int compara(Lista *t, char var[] );

/*as rotacoes necessarias da arvore*/
struct Node *rightRotate(struct Node *y);

struct Node *leftRotate(struct Node *x);

/*pega o fator de balancemeanto*/
unsigned long long int getBalance(struct Node *N);

/*funcao para inserir e chamar os balanceamentos caso necessario*/
struct Node* insert(struct Node* node, char key[],char arquivo[]);

/*print em preordem*/
void preOrder(struct Node *root);

/*busca um noh na arvore a partir de uma string*/
void search_tree(struct Node *root,char* elemento);

/*funcao que libera a lista da arvore, chamada na libera da arvore*/
void libera_lis(Lista *LISTA);

/*libera as alocacoes da arvore*/
void libera(struct Node *p);

/*pega tempo*/
long wtime();