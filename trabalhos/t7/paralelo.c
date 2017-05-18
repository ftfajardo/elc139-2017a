#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <sys/timeb.h>
#include <time.h>


// Total de cidades para construção do grafo
#define TOTALCIDADES 12

// Grafo de distancia entre as cidades
int distancias[TOTALCIDADES*TOTALCIDADES];
double custos[TOTALCIDADES];

/*
Funcao criaGrafo
- Rand para o total de ligacoes que o grafo irá ter
- Rand para qual cidade origem e destino
- Verifica se nao eh a mesma cidade e se ja nao possui ligacao entre as mesmas
- Rand para a distância
- Vetor distancias:
- Pos 0 ate (TOTALCIDADES - 1) = cidade 1
- Pos (TOTALCIDADES) ate ((2*TOTALCIDADES) -1) = cidade 2
*/
void criaGrafo() {
	int origem, destino, totalLigacoes, i, ok, distancia;

	totalLigacoes = rand() % (TOTALCIDADES * 4);
	printf("TOTAL LIGACOES: %i\n", totalLigacoes);

	for (i = 0; i < totalLigacoes; i++) {
		ok = 0;
		while (ok == 0) {
			origem = rand() % TOTALCIDADES;
			destino = rand() % TOTALCIDADES;
			if (origem != destino) {
				if (distancias[(origem)* TOTALCIDADES + destino] == -1) {
					distancia = (rand() % 20) + 1;
					distancias[(origem)* TOTALCIDADES + destino] = distancia;
					ok = 1;
					printf("Ligacao entre as cidades: %i e %i com distancia: %i\n", origem, destino, distancia);
				}
			}
		}
	}
}

/*
Funcao menorCaminho
- Recebe a origem e destino para calculo
- Aloca vetor necessário
- Verifica as ligacoes que direta que a "cidade" possui
- Por fim, é feito o calculo do menor caminho
- Impresso o resultado
*/

void dijkstra(int origem, int destino) {
	int i = 0, aux = 0;
	int *verticesNoCaminho; // Vertices que sao acessados para o menor caminho
	double distMinima; // Custoo com os caminhos

	verticesNoCaminho = (int*)calloc(TOTALCIDADES, sizeof(int));

	if (verticesNoCaminho == NULL) {
		printf("ERROR: Erro na alocacao \n");
		printf("ERROR: Erro na alocacao \n");
		exit(-1);
	}


	for (i = 0; i < TOTALCIDADES; i++) {
		verticesNoCaminho[i] = 0;
		if (distancias[(origem)* TOTALCIDADES + i] != -1) {
			custos[i] = distancias[(origem)* TOTALCIDADES + i];
		}
		else {
			custos[i] = HUGE_VAL;
		}
	}

	verticesNoCaminho[origem] = 1;
	custos[origem] = 0;

	// Principal laço
	do {
		distMinima = HUGE_VAL;

		for (i = 0; i < TOTALCIDADES; i++) {
			if (!verticesNoCaminho[i]) {
				if (custos[i] >= 0 && custos[i] < distMinima) {
					distMinima = custos[i];
					aux = i;
				}
			}
		}

		if (distMinima != HUGE_VAL && aux != destino) {
			verticesNoCaminho[aux] = 1;
			for (i = 0; i < TOTALCIDADES; i++) {
				if (!verticesNoCaminho[i]) {
					if (distancias[aux * TOTALCIDADES + i] != -1 && custos[aux] + distancias[aux * TOTALCIDADES + i] < custos[i]) {
						custos[i] = custos[aux] + distancias[aux * TOTALCIDADES + i];
					}
				}
			}
		}
	} while (aux != destino && distMinima != HUGE_VAL);


	/*IMPRIME RESULTADO*/
	printf("Distancia de %i ate %i: ", origem, destino);
	printf("Custo: %f\n", custos[destino]);

}

/*
Funcao calculoDistancia
- Dois for's que chamam a funcao para calculo do menor caminho
*/

void calculoDistancia(int ntask,int rank) {
	int i, j, n;
	n = (TOTALCIDADES/ntask);
	for (i = rank*n; i < n+n*rank; i++) {
		for (j = 0; j < TOTALCIDADES; j++) {
			dijkstra(i, j);
		}
	}

}

/*
Todas as distancias e custos sao zeradas, pois na hora do algoritmo eh verificado
as cidades que tem ligacoes.
*/
void zeraDistancia() {
	int i;
	for (i = 0; i < TOTALCIDADES * TOTALCIDADES; i++) {
		distancias[i] = -1;
	}

	/* Zera custos*/
	for (i = 0; i < TOTALCIDADES; i++) {
		custos[i] = 0;
	}
}

int main(int argc, char** argv) {
	int ntasks,rank,valor;
	//struct timeval tv1,tv2;
	double start, end;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
			
	srand((unsigned)TOTALCIDADES);
	zeraDistancia();
	criaGrafo();		
	printf("rank = : %d\n", rank);
	
	MPI_Barrier(MPI_COMM_WORLD);
	start = MPI_Wtime();

	calculoDistancia(ntasks,rank);
	
	MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime();

	MPI_Finalize();	

	if(rank == 0){
		printf("+%f\n", end-start);
	}
	
	
	return 0;
}