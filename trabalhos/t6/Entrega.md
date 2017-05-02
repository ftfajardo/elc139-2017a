Francisco Tassinari Fajardo - T6

--Parte 1 ----
 
Tentativa de executar falhou pois estava passando direto o executável e assim não dava(pendente)


---Parte 2---

No código mpi_errado1 o erro ocorre em usar o rank para pegar a tag pois o processo 0 espera uma mensagem do 0 e o processo 1
espera uma mensagem do 1, a solução é colocar a tag como pode ser visto no código [mpi_certo1e2.c](mpi_certo1e2.c).
No código mpi_errado2 falta o  MPI_Finalize() que faz com que o mpi nao finalize corretamente,o código solução é igual o de cima.


O código de pipeline está em [pipeline.c](pipeline.c)
