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





