#include <iostream>
#include <stdio.h>
//#include <curses.h>
#include <stdlib.h>

#include <sys/timeb.h>
#include <ctime>

#include <time.h>
#include <math.h>
#include <vector>

#ifdef __MACH__
    #include <assert.h>
    #include <CoreServices/CoreServices.h>
    #include <mach/clock.h>
    #include <mach/mach.h>
    #include <mach/mach_time.h>
    #include <unistd.h>
#endif

#include <fstream>
#include <thread>


#include "algoritmos_ordenacao.h"


/*
 Referencias:
    http://www.cplusplus.com/reference/ctime/difftime/
    http://www.cplusplus.com/reference/ctime/clock/
    http://stackoverflow.com/questions/23378063/how-can-i-use-mach-absolute-time-without-overflowing
    https://developer.apple.com/library/mac/qa/qa1398/_index.html

 Json:
 https://github.com/nlohmann/json


    // LINUX
        //chronos
        http://pt.cppreference.com/w/cpp/chrono
        http://codereview.stackexchange.com/questions/48872/measuring-execution-time-in-c

        http://www.informit.com/articles/article.aspx?p=1881386&seqNum=2
        https://www.daniweb.com/programming/software-development/code/445750/simple-timer-using-c-11s-chrono-library

        //ide
        http://stackoverflow.com/questions/21075852/some-c11-features-missing-when-using-code-blocks-13-12-mingw-4-8-1-and-sfml-2
        http://www.cprogramming.com/code_blocks/

        //compilador
        http://www.cprogramming.com/g++.html



        https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html

        THREADS
        https://rafalcieslak.wordpress.com/2014/05/16/c11-stdthreads-managed-by-a-designated-class/

        https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/
        https://solarianprogrammer.com/2012/02/27/cpp-11-thread-tutorial-part-2/

        http://stackoverflow.com/questions/20585896/how-to-use-c11-thread-with-instance-method

        http://stackoverflow.com/questions/10673585/start-thread-with-member-function

        linker issues:
        http://stackoverflow.com/questions/23677690/compiling-multithread-code-with-codeblocks-gnu-compiler
 */

//Define o tam que o vetor tem
#define tamanho 100





int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "= = = = = APS Análise de Algoritmos de ordenação = = = = = \n";

    /* Configurações dos testes */
        // Quantidade de bateria de testes por execução
        int totalDeExec = 2;
        // contador auxiliar
        int counter = 0;


        /* vetores de categoria de testes */
        // testes de tempo
        //static const int num_threads_tempo = (totalDeExec+1)*3;/* vezes três para os tres algoritmos*/
        // testes de ticks
        //static const int num_threads_ticks = totalDeExec*3;

        /* vetores */
        //std::thread tempo_threads[num_threads_tempo];
        std::thread bubbles_tempo_threads[totalDeExec+1];
        std::thread quicks_tempo_threads[totalDeExec+1];
        //std::thread ticks_threads[num_threads_ticks];

        // vetores de instancias
        std::vector <BubbleSort> bubbles;//[totalDeExec];
        bubbles.reserve(totalDeExec);
        //int bubble_size = sizeof(BubbleSort);
        //BubbleSort *bubbles;
        //bubbles = (BubbleSort*) malloc(totalDeExec*bubble_size);

        std::vector <QuickSort> quicks;//[totalDeExec];
        quicks.reserve(totalDeExec);
        //int quick_size = sizeof(QuickSort);
        //QuickSort *quicks;
        //quicks = (QuickSort*) malloc(totalDeExec*quick_size);

        /* Dados para analise */
        int i,j =0;

        int vbs[totalDeExec][tamanho];
        int vqs[totalDeExec][tamanho];

        for (i=0 ; i < totalDeExec; i++){
            for(j = 0; j < tamanho; j++){
                vbs[i][j] = rand();
                vqs[i][j] = rand();
                //vis[i] = rand();
                //vss[i] = rand();
                //vhs[i] = rand();
                //vms[i] = rand();
                //vus[i] = rand();
            }
        }


    /* EXECUÇÔES */
    printf("(Re)Iniciando Processo: (%d)\n", totalDeExec);

    //intancias
    for (i=0 ; i < totalDeExec; i++){
        BubbleSort *b = new BubbleSort();
        bubbles.push_back(*b);
        QuickSort *q = new QuickSort();
        quicks.push_back(*q);
    }

    //threads
    for (i=0 ; i < totalDeExec; i++){
        bubbles_tempo_threads[i] = bubbles[i].avaliaTempo(vbs[i], tamanho);
    }

    for (i=0 ; i < totalDeExec; i++){
        quicks_tempo_threads[i] = quicks[i].avaliaTempo(vbs[i], tamanho);
    }

    for (i=0 ; i < totalDeExec; i++){
        bubbles_tempo_threads[i].join();
        quicks_tempo_threads[i].join();
    }

    /*
    while(counter <= totalDeExec){



        int i;
        int vbs[tamanho];
        int vqs[tamanho];
        //int vis[tamanho];
        //int vss[tamanho];
        //int vhs[tamanho];
        //int vms[tamanho];
        //int vus[tamanho];

        //clrscr();
        //Cria numeros aleatorios para os vetores
        for(i = 0; i < tamanho; i++){
            vbs[i] = rand();
            vqs[i] = rand();
            //vis[i] = rand();
            //vss[i] = rand();
            //vhs[i] = rand();
            //vms[i] = rand();
            //vus[i] = rand();
        }

        //Launch a group of threads
        //for (int i = 0; i < num_threads_tempo; ++i) {
        //    tempo_threads[i] = std::thread(call_from_thread);
        //}

        //Ordenacao com BubbleSort
        printf("\t=============================================\n");
        printf("\tOrdenacao com BubbleSort: (%d/%d)\n", counter, totalDeExec);
        printf("\t=============================================\n");
        //BubbleSort *bubble = new BubbleSort();

        //std::thread bs_t = bubble->avaliaTempo(vbs, tamanho);
        //bs_t.join();
        //tempo_threads[counter*3] = bubble->avaliaTempo(vbs[counter], tamanho);

        printf("\t=============================================\n");
        printf("\tOrdenacao com QuickSort: (%d/%d)\n", counter, totalDeExec);
        printf("\t=============================================\n");
        //QuickSort *quick = new QuickSort();

        //std::thread qs_t = quick->avaliaTempo(vqs, tamanho);
        //qs_t.join();
        //tempo_threads[(counter*3)+1] = quick->avaliaTempo(vqs[counter], tamanho);


        //tempo_threads[(counter*3)].join();
        //tempo_threads[(counter*3)+1].join();


        counter++;
    }


    counter = 0;
    while( counter < totalDeExec ){
        tempo_threads[(counter*3)].join();
        tempo_threads[(counter*3)+1].join();
        counter++;
    }
    */


    //getch();


    return 0;
}




