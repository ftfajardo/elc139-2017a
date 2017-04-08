
1.  O programa não faz com que as variáveis ajam independentemente em cada thread,pois o padrão do open mp é shared logo nas variáveis
id e total seriam compartilhadas pelas threads causando assim erro , por exemplo pegava o mesmo valor para o id nas duas threads e o total dava igual.
2.
  #include <omp.h>
  #include <stdio.h>
  #include <stdlib.h>

  int main (int argc, char *argv[]) 
  {
  int nthreads, i, tid;
  float total;

  /*** Spawn parallel region ***/
  #pragma omp parallel private(tid,total)
  {
  /* Obtain thread number */
  tid = omp_get_thread_num();
  /* Only master thread does this */
  if (tid == 0) {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }
  printf("Thread %d is starting...\n",tid);

  #pragma omp barrier 

  /* do some work */
  total = 0.0;
  #pragma omp for schedule(dynamic,10)
  for (i=0; i<20; i++){ 
     total = total + i*1.0;
	/*printf("{ %e },t = %d",total,tid);*/	
	}
  printf ("Thread %d is done! Total= %e\n",tid,total);

  } /*** End of parallel region ***/
}
