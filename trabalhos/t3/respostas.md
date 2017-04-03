 #T3: Programação Paralela
 Franciso Tassinari Fajardo



1. Particionamento : 
		
		O particionamento depende do número de threads , onde o vetor
		será dividido internamente um espaço para cada thread.
	
		int wsize = dotdata.wsize;
   		int start = offset*wsize;
   		int end = start + wsize;		

		Nota-se que o start e end são diferentes para cada thread.


   Comunicação:
		
		É quando no código occorre os locks para não deixar multiplas threads
		escreverem na mesma variavel ao mesmo tempo.
	
		pthread_mutex_lock (&mutexsum);
    	dotdata.c += mysum;
   		pthread_mutex_unlock (&mutexsum);
 
   Aglomeração:
   		
		É quando ocorre a junção das somas parcias por cada thread para fazer a conta final
		
		dotdata.c += mysum;

   Mapeamento:
		
		for (i = 0; i < nthreads; i++) {
      			pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);
    	}

		Etapa de criação das treads , mapeamento estático.

2.	
	(a) 1 thread(s), 6932200 usec
	(b) 2 thread(s), 3791705 usec

	speedup = (a) / (b) 
	speedup = 1,83  

3 e 4.

	(1 Thread)	
	| Tamanho | Repetições | Tempo(s) | Speedup |
	|---------|------------|----------|---------|
	|1500000  | 1000       |   5.1    |         |
	|1500000  | 1500       |   7.7    |         |
    

	(2 Thread)	
	| Tamanho | Repetições | Tempo(s) | Speedup |
	|---------|------------|----------|---------|
	|750000   | 1000       |   2.9    |  1,75   |
	|750000   | 1500       |   4.2    |  1,83   |


	(4 Thread)	
	| Tamanho | Repetições | Tempo(s) | Speedup |
	|---------|------------|----------|---------|
	|375000   | 1000       |   2.4    |   2,1   |
	|375000   | 1500       |   3.6    |   2,1   |


	(8 Thread)	
	| Tamanho | Repetições | Tempo(s) | Speedup |
	|---------|------------|----------|---------|
	|187500   | 1000       |   2.4    |   2,1   |
	|187500   | 1500       |   3.6    |   2,1   |



	Nota-se que aconteceu um aumento do speedup de 2 para 4 threads devido a arqui-
	tetura do computador que possui dois cores mas pode utililar 4 threads. Além 
	disso nota-se que o speedup continua na mesma fixa para dois cores e quando passa de 
	quatro não faz diferença.

5.Não está correto devido ao fato que falta o lock e unlock para a variável causando assim problema nos calculos, 
porém isso não impede que ocorra uma saída válida.


-----------------------OpenMP-----------------------


1.open.c


2.

	(1 Thread)	
	| Tamanho | Repetições | Tempo(s) | Speedup |
	|---------|------------|----------|---------|
	|1500000  | 1000       |   5.4    |         |
	|1500000  | 1500       |   8.1    |         |
    

	(2 Thread)	
	| Tamanho | Repetições | Tempo(s) | Speedup |
	|---------|------------|----------|---------|
	|750000   | 1000       |   2.8    |  1,92   |
	|750000   | 1500       |   4.3    |  1,88   |


	(4 Thread)	
	| Tamanho | Repetições | Tempo(s) | Speedup |
	|---------|------------|----------|---------|
	|375000   | 1000       |   2.3    |   2,3   |
	|375000   | 1500       |   3.4    |   2,4   |


	(8 Thread)	
	| Tamanho | Repetições | Tempo(s) | Speedup |
	|---------|------------|----------|---------|
	|187500   | 1000       |   2.2    |   2,45  |
	|187500   | 1500       |   3.4    |   2,4   |


	Análise: Rodando com uma thread houve uma demora, porém quando aumentado o número de threads 
	houve respostas no mesmo tempo ou mais rápidas que usando posix(não muito mais rápidas).





