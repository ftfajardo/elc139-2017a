#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define tam 15000


int * insertionSort(int original[], int length) {
	int i, j,temp;
	
	for (i = 1; i <= length; i++) {
		temp = original[i];		
		j =  i-1;

		while ((j >= 0) && (original[j] > temp)) {
			original[j+1] = original[j];
			j = j - 1;
		}
		original[j+1] = temp;
		
	}

	return (int * )original;
} 

int * maloca(int n){
	int *vet = (int*)malloc(sizeof(int) * n);
	if (vet != NULL)
         printf("\nFirst allocation of %d ints successful.",tam);
     else
     {
         printf("\nAttempt to allocate %d ints failed.\n",tam);
         exit(1);
     }
	return vet;
}


int *preenche (int n,int arr[]) {
	srand(time(NULL));
	int i;	
	for(i = 0; i < tam ;i++ )
		arr[i] = rand()%10;   
	return arr;
}

void imprime(int arr[]){
	int i;
	for(i = 0; i < tam ;i++ )
		printf("%d,",arr[i]);	
    
}

int main()
{		
	    
	int* arr = maloca(tam); 
	int* arr2 = maloca(tam);
	 	

	arr = preenche(tam,arr);
	arr2 = preenche(tam,arr);

    arr =insertionSort(arr, tam);
	arr2 =insertionSort(arr2, tam);
	
	imprime(arr);
	printf("\n");
	imprime(arr2);    	
 	printf("\n");
	   
	return 0;
}