#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "avl.h"
#include <sys/time.h>


/*macro de comando para limpar tela em windows e em linux */
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define lim_arq 10 /*lim de arquivos*/
#define tam_max 100 /*tamanho maximo de uma string*/

int main()
{
	struct Node *root = NULL;                 /*criando a struct da arvore*/
	FILE * pFile;                              /*ponteiro para abrir o  file*/
 	int numero_arqu = 0, numero_dados = 0,cont = 0,i=0,j=0,c;    /*variaveis de controle*/
	const char *arquivos[][1]= {{"progpar.txt"},{"progpar.txt"},{"progpar.txt"},{"progpar.txt"},{"progpar.txt"},{"progpar.txt"},{"progpar.txt"},{"progpar.txt"},{"progpar.txt"},{"progpar.txt"} }; /*matriz com nome de arquivos*/
	char buff[tam_max];   /*buffer de controle para guardar as strings e inserir na arvore*/
	char aux[tam_max];    /*auxiliar para mandar o nome do arquivo*/
	char MAT[tam_max][tam_max];  /*Matriz onde eh armazenada as strings digitadas*/
	long start_time, end_time; /*variavel de tempo */

	printf("Digite o numero de arquivos que vc deseja ler:   \n");
  	fgets (buff, tam_max, stdin);
  	numero_arqu = atoi(buff);

  printf("Digite o numero de strings q vc deseja ler: \n");
	fgets (buff, tam_max, stdin);
	numero_dados = atoi(buff);
	//->arquivos[0][cont]
	start_time = wtime();
	while(cont < numero_arqu){  /*laco para ler o numero de arquivos digitados*/
		if ((pFile = fopen ("progpar.txt" , "r") ) == NULL){   /*if para caso o arquivo esteja com o nome errado*/
			printf("Erro abrindo arquivo\n   %s  ",arquivos[0][cont]);
			exit(1);
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
			//tirar ->strcpy(aux,arquivos[0][cont]);
			//printf("inserindo %s",buff);
			//->send aux
			root = insert(root, buff,"progpar.txt"); /*insercao do buffer na arvore e do arquivo numa lista*/
		}
		if(c == '\n')j = 0;
	}while (c != EOF);

   	fclose(pFile);
		cont++;
	}
	end_time = wtime();
	printf("Tempo de processamento: %ld us\n", (long) (end_time - start_time));
	
	printf("Digite a(s) string(s) que voce quer buscar: \n");
	for(i = 0 ; i < numero_dados;i++){
		scanf("%s",MAT[i]);
	}
	start_time = wtime();
	for ( i = 0; i < numero_dados; i++ ){
		search_tree(root,MAT[i]);
	}
	end_time = wtime();
	printf("Tempo de busca na avl : %ld us\n", (long) (end_time - start_time));


  printf("liberando..");
  libera(root);	/*liberando a arvore*/
  return 0;
}
