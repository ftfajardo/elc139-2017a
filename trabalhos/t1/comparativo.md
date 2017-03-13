[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2016a) > T1

TOP500 & me: Comparativo de Arquiteturas Paralelas
--------------------------------------------------

Nome:  Franciso Fajardo 

| Característica                                            | Computador no TOP500  | Meu computador  |
| --------------------------------------------------------- | --------------------- | --------------- |
| Nome/Título                                               | Titan                 |  Inspiron 14    |
| Imagem (foto, diagrama, screenshot, etc.)                 |<img src="https://121oies.files.wordpress.com/2014/02/02_titan3_m.jpg" width="200"> | <img src="http://www.pinoytechblog.com/wp-content/uploads/2014/05/Dell-Inspiron-14-3000-Series-Philippines.jpg?x60048" width="200">|
| Classificação de Flynn                                    |       Mimd                |  Mimd           |
| Memória: compartilhada, distribuída ou ambas?             |     ambas                  |  compartilhada       |
| Número total de núcleos de processamento                  | 560,640               |  cores = 2 threads = 4               |
| Fabricante e modelo do(s) processador(es)                 |    Cray Inc.,Opteron 6274 16C            | intel - i5-5200U |
| Frequência do(s) processador(es)                          |    2.2GHz             |normal = 2.2GHz turbo = 2.7GHz |
| Memória total                                             |  	710,144 GB          | 8GB              |
| Tipo(s) de interconexão entre os núcleos/processadores    |Cray Gemini interconnect|                 |
| Desempenho Linpack                                        |	17,590 TFlop/s         |      abaixo           |

Limpack:

Intel(R) Optimized LINPACK Benchmark data

Current date/time: Mon Mar 13 19:51:48 2017

CPU frequency:    2.693 GHz
Number of CPUs: 1
Number of cores: 2
Number of threads: 2

Parameters are set to:

Number of tests: 15
Number of equations to solve (problem size) : 1000  2000  5000  10000 15000 18000 20000 22000 25000 26000 27000 30000 35000 40000 45000
Leading dimension of array                  : 1000  2000  5008  10000 15000 18008 20016 22008 25000 26000 27000 30000 35000 40000 45000
Number of trials to run                     : 4     2     2     2     2     2     2     2     2     2     1     1     1     1     1    
Data alignment value (in Kbytes)            : 4     4     4     4     4     4     4     4     4     4     4     1     1     1     1    

Maximum memory requested that can be used=9800701024, at the size=35000

=================== Timing linear equation system solver ===================

Size   LDA    Align. Time(s)    GFlops   Residual     Residual(norm) Check
1000   1000   4      0.035      19.1655  9.394430e-13 3.203742e-02   pass
1000   1000   4      0.026      25.5350  9.394430e-13 3.203742e-02   pass
1000   1000   4      0.033      20.3270  9.394430e-13 3.203742e-02   pass
1000   1000   4      0.025      26.3564  9.394430e-13 3.203742e-02   pass
2000   2000   4      0.109      48.9256  4.085732e-12 3.554086e-02   pass
2000   2000   4      0.109      48.9801  4.085732e-12 3.554086e-02   pass
5000   5008   4      1.403      59.4365  2.368622e-11 3.302852e-02   pass
5000   5008   4      1.494      55.8223  2.368622e-11 3.302852e-02   pass
10000  10000  4      10.593     62.9516  9.899764e-11 3.490757e-02   pass
10000  10000  4      10.397     64.1415  9.899764e-11 3.490757e-02   pass
15000  15000  4      36.183     62.1968  2.271511e-10 3.577668e-02   pass
15000  15000  4      37.476     60.0503  2.271511e-10 3.577668e-02   pass
18000  18008  4      64.952     59.8700  3.396281e-10 3.719345e-02   pass
18000  18008  4      64.689     60.1131  3.396281e-10 3.719345e-02   pass

