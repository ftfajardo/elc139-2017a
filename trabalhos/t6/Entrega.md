Francisco Tassinari Fajardo - T6

---Parte 1---
 
Tentativa de executar falhou pois estava passando direto o executável e assim não dava e depois fechou o servidor.

---Análise---

**Mapeamento**
	
Mapeamento é estático e pode ser visto em: 

       MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
       MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

	
**Particionamento**

Ocorre a divisão do vetor na parte:
	
       part_size = n / ntasks;  
  
onde n é o tamanho to vetor e ntasks é o numero de processos.
 

**Comunicação**

Ocorre entre o send dos processos filhos e o recieve do pai, depois que recebe faz-se a conta, exemplo:
	
       MPI_Send(&mydot, 1, MPI_DOUBLE, MASTER, msg_tag, MPI_COMM_WORLD);  

       MPI_Recv(&dot, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);  

**Aglomeração**

É a soma das parcias como no código:  
 
        mydot += dot;


---Parte 2---

No código mpi_errado1 o erro ocorre em usar o rank para pegar a tag pois o processo 0 espera uma mensagem do 0 e o processo 1
espera uma mensagem do 1, a solução é colocar a tag como 0 em tudo resolvendo assim o conflito, isso pode ser visto no código [mpi_certo1e2.c](mpi_certo1e2.c).
No código mpi_errado2 falta o  MPI_Finalize() que faz com que o mpi nao finalize corretamente,o código solução é igual o de cima.


O código de pipeline está em [pipeline.c](pipeline.c)
