#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>
#include <string.h>

#define tam_max 100
#define MASTER 0
#define WORK_TAG    1
#define DATA_TAG    2
#define STOP_TAG    3

char text[] = "progpar.txt";

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
unsigned long long int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

/*funcao para pegar maximo de 2 inteiros*/

 unsigned long long int max( unsigned long long int a, unsigned long long int b){
	return (a > b)? a : b;
}

/*funcao auxiliar pra alocar o novo no e os ponteiros*/
struct Node* newNode(char key[],char arquivo[])
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));

	if (node == NULL) {
		printf("sem memoria\n");
		MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}

	strcpy(node->nome,key);

	node->left   = NULL;
	node->right  = NULL;
	node->height = 1;
	node->cont = 1;

	node->a = NULL;  /*a partir daqui alocacao da lista*/
	node->a =  (Lista*)malloc(sizeof(Lista));
	if(node->a == NULL){
		printf("sem memoria\n");
		MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}

	strcpy(node->a->info,arquivo);
	node->a->prox = NULL;

	return(node);
}

void push(Lista * head, char info[]) {       /*funcao que insere no fim na lista*/
	
	
	
	Lista* current = head;
	while (current->prox != NULL) 
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
unsigned long long int getBalance(struct Node *N)
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
    unsigned long long int balance = getBalance(node);

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


int main(int argc, char **argv)
{
	int taskid, ntasks;
	double start_time, end_time;
	struct Node *root = NULL;                 /*criando a struct da arvore*/
	FILE * pFile;                              /*ponteiro para abrir o  file*/
 	char buff[tam_max];
	int id,i = 0,j = 0;
	char msg[tam_max];
	strcpy (msg,text);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

	if (taskid == MASTER)
	{
		MPI_Status status;
		int numero_arqu = 0, numero_dados = 0,cont = 0,nproc = 0;
		char MAT[tam_max][tam_max];  /*Matriz onde eh armazenada as strings digitadas*/
		printf("Digite o numero de arquivos que vc deseja ler:   \n");
  		fgets (buff, tam_max, stdin);
 		numero_arqu = atoi(buff);
		int resto = numero_arqu - (ntasks-1);
		//printf("Digite o numero de strings q vc deseja ler: \n");
		//fgets (buff, tam_max, stdin);
		numero_dados = atoi(buff);

		if(ntasks-1 > numero_arqu){
			j = numero_arqu+1;
			for(i = j ; i < ntasks; i++){
				MPI_Send(&text, 0, MPI_INT, i, STOP_TAG, MPI_COMM_WORLD);
			}
			ntasks = numero_arqu+1;
		}

		//numero minimo para executar o programa com mestre e escravo
		if(ntasks <=1 || numero_arqu < 1){
			printf("n de tarefas invalido\n");
			MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
			exit(EXIT_FAILURE);
		}

		start_time =  MPI_Wtime();
		//manda o arquivo para os processos iniciais
		for (i = 1; i < ntasks; i++){
			MPI_Send(msg, tam_max, MPI_CHAR, i, WORK_TAG, MPI_COMM_WORLD);
			//fprintf(stderr,"for,enviei %s para o %d\n ",text,i);
			++nproc;
		}

		while(nproc > 0){//enquanto existir processos ativos
			MPI_Recv(&msg, tam_max, MPI_CHAR, MPI_ANY_SOURCE,DATA_TAG, MPI_COMM_WORLD, &status);

			--nproc;//chegou um processo diminuir ativos
			//printf("np %d\n",nproc);
			id = status.MPI_SOURCE;

			//fprintf(stderr,"id %d linhaaux: %s \n",id,msg);

			if(resto > 0){//numero de processos restantes
				//fprintf(stderr," laço id %d linhaparte: %d \n",id,linha_parte);
				MPI_Send(msg, tam_max, MPI_CHAR, id, WORK_TAG, MPI_COMM_WORLD);
				++nproc;//enviou processo aumentar ativos
				--resto;// diminuir de quantos processos faltam
			}

			if(nproc == 0){//quando os processos chegarem em 0 mata todos com a tag
				for(i = 1 ; i < ntasks ; i++){
					MPI_Send(msg, tam_max, MPI_CHAR, i, STOP_TAG, MPI_COMM_WORLD);}
			}
		}
		end_time =  MPI_Wtime();;
		fprintf(stderr,"Tempo: %f \n", (double)(end_time - start_time));

	}
	else {
		MPI_Status status;
		char msga[tam_max];
    		int c;
		while ( ((MPI_Recv(&msga, tam_max, MPI_CHAR, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status)) == MPI_SUCCESS) &&
					(status.MPI_TAG == WORK_TAG) )//recebe a linha com a tag de trabalho
		{
			//fprintf(stderr," recebi do mestre a linha %s,task %d\n",msg,taskid);
			if ((pFile = fopen ( msga , "r") ) == NULL){   /*if para caso o arquivo esteja com o nome errado*/
				//printf("Erro abrindo arquivo\n   %s  ",arquivos[0][cont]);
				MPI_Finalize();
				return EXIT_SUCCESS;
			}
   		/* PARTE DO CODIGO QUE PERCORRE O ARQUIVO ACHA AS STRINGS , DEPOIS INSERE NA ARVORE AVL , logica feita com fgetc e suor*/
  		do{
    			c = fgetc(pFile);
    			if(c != ' ' && c != '.' && c != ','  && c != ';' && c != '\t' && c != '\"' && c != ':' && c != '?' && c != '[' && c != ']' && c != '{' && c != '}' && c != '(' && c != ')' && c != '!'
   			&& c != '?' && c != '<' && c != '>' && c != '\n' && (int)c!= -1){
   				j = 1;
   				buff[i] = c;
   				i++;
			}
   			if((c == ' ' || c == '.' || c == ',' || c == ';'  || c == '\t' || c == '\"' || c == ':' || c == '?' || c == '[' || c == ']' || c == '{' || c == '}' || c == '(' || c == ')' || c == '!'
   			|| c == '?' || c == '<' || c == '>' || c== '\n') && j ==1 ){
				buff[i] = '\0';
				i = 0;
				j = 0;

				root = insert(root, buff,msga); /*insercao do buffer na arvore e do arquivo numa lista*/
			}
			if(c == '\n')j = 0;
		}while (c != EOF);

	   	fclose(pFile);
		MPI_Send(msga, tam_max, MPI_CHAR, 0, DATA_TAG, MPI_COMM_WORLD);

		}

	}
	printf("liberando..");
  	libera(root);	/*liberando a arvore*/

	MPI_Finalize();
	return EXIT_SUCCESS;
}
