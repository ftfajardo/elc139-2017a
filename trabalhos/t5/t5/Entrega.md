Alunos: Jhillian Bianchi, Francisco Tassinari Fajardo
Mat:201310739, 201510495

ELC139 - Programação Paralela
Prof. Andrea Schwertner Charão


Trabalho 5 - Firesim em OpenMP

Analisando o programa, identificamos duas possíveis estratégias para que seja possível a redução do tempo de execução.

O trecho de código a ser paralelizado seria o seguinte:

for (int ip = 0; ip < n_probs; ip++) {
       prob_spread[ip] = prob_min + (double) ip * prob_step;
       percent_burned[ip] = 0.0;
       rand.setSeed(base_seed+ip);
         
       for (int it = 0; it < n_trials; it++) {
            forest->burnUntilOut(forest->centralTree(), prob_spread[ip], rand);
            percent_burned[ip] += forest->getPercentBurned();
       }
}


A primeira das estratégias seria paralelizar o laço mais externo, de forma que cada thread seja responsável por uma fatia de probabilidades. Um problema dessa abordagem, é que as fatias de probabilidade mais baixa terminam muito rápido, enquanto as mais altas demoram a finalizar, gerando um desbalanceamento na carga de trabalho das threads.

A segunda estratégia é paralelizar o laço interno, para que dessa forma, haja um balanceamento maior na carga de trabalho das threads. Nessa estratégia, cada thread fica com todas as probabilidades, mas dividem o processo de queima.

Na estratégia que utilizamos de paralelizar usando schedule dynamic testamos para três entradas de problema ,com 5, 30 e 60 respectivamente, as repetições foram 1000 e o número de probabilidades 101. 

Para o programa sequencial os resultados obtidos na média de execuções foram: 
                     
                     |   5   |  30  |  60  |
                     |-------|------|------|
                     | 0.28s | 21.5s| 130s |
                     
Já com 2 threads obtivemos:
  
                     |   5   |  30  |  60  |
                     |-------|------|------|
                     | 0.31s | 14.5s| 83.2s|

E com 4:

                     |   5   |  30  |  60  |
                     |-------|------|------|
                     | 0.43s | 14.0s| 73.4s|


Análise dos resultados:
              
       Pode-se observar que com entradas pequenas não se nota a eficiência de usar paralelismo, pois perde se tempo com criação 
       das mesmas,a partir da entrada 30 o speedup para 2 começa a ser notado e resulta em quase 1.5 que é bom para 2 threads,  
       porém quando vamos para 4 threads o ganho é bem menor resultando em um speedup de 1.53 para 4, o que pode ser explicado                     
       pelo computador testado não ter 4 cores puros,quando o tamanho da floresta começa a aumentar ai começamos a notar 
       ganhos para 4 treads em relação ao de 2 threads e do de 2 para o sequencial também,obtivemos um speedup de 1.6 para 2 ,
       e 1.77 para 4.
       O código usado para medição de tempo sequencial foi o fornecido porém os pirnts foram retirados de dentro do laço de 
       repetição, mesma coisa com a medição de tempo do código paralelizado(prints fora da medição).
    
                   
O hardware usado foi:

       Arquitetura:           x86_64
       Modo(s) operacional da CPU:32-bit, 64-bit
       Ordem dos bytes:       Little Endian
       CPU(s):                4
       Lista de CPU(s) on-line:0-3
       Thread(s) per núcleo: 2
       Núcleo(s) por soquete:2
       Soquete(s):            1
       Nó(s) de NUMA:        1
       ID de fornecedor:      GenuineIntel
       Família da CPU:       6
       Modelo:                61
       Nome do modelo:        Intel(R) Core(TM) i5-5200U CPU @ 2.20GHz
       Step:                  4
       CPU MHz:               2182.409
       CPU MHz máx.:         2700,0000
       CPU MHz mín.:         500,0000
       BogoMIPS:              4391.85
       Virtualização:       VT-x
       cache de L1d:          32K
       cache de L1i:          32K
       cache de L2:           256K
       cache de L3:           3072K
       CPU(s) de nó0 NUMA:   0-3
 
       OBS: na verdade são 2 cores e 2 hiperthreads mas o linux não pega
    
    
    
    
    
    






                     
                     







