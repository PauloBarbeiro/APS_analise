//
//  main.cpp
//  APS_Analise_CommandLine
//
//  Created by Paulo on 10/05/16.
//
//

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

#include <sys/timeb.h>
#include <ctime>

#include <time.h>
#include <math.h>

#ifdef __MACH__
    #include <assert.h>
    #include <CoreServices/CoreServices.h>
    #include <mach/clock.h>
    #include <mach/mach.h>
    #include <mach/mach_time.h>
    #include <unistd.h>
#endif



#include <fstream>

#include <vector>
#include <thread>

#include "algoritmos_ordenacao.hpp"



/*
 Referencias:
    http://www.cplusplus.com/reference/ctime/difftime/
    http://www.cplusplus.com/reference/ctime/clock/
    http://stackoverflow.com/questions/23378063/how-can-i-use-mach-absolute-time-without-overflowing
    https://developer.apple.com/library/mac/qa/qa1398/_index.html
 
 Json:
 https://github.com/nlohmann/json
 
 
 */





//Helper functions ##################################################################################



uint64_t getExpressibleSpan(uint32_t numer, uint32_t denom) {
    // This is just less than the smallest thing we can multiply numer by without
    // overflowing. ceilLog2(numer) = 64 - number of leading zeros of numer
    
    //uint64_t maxDiffWithoutOverflow = ((uint64_t)1 << (64 - ceilLog2(numer))) - 1;
    uint64_t maxDiffWithoutOverflow = ((uint64_t)1 << (uint64_t)(64 - ceil(log2(numer)) )) - 1;
    return maxDiffWithoutOverflow * numer / denom;
}

// This function returns the rational number inside the given interval with
// the smallest denominator (and smallest numerator breaks ties; correctness
// proof neglects floating-point errors).
static mach_timebase_info_data_t bestFrac(double a, double b) {
    if (floor(a) < floor(b))
    { mach_timebase_info_data_t rv = {static_cast<uint32_t>((int)ceil(a)), 1}; return rv; }
    double m = floor(a);
    mach_timebase_info_data_t next = bestFrac(1/(b-m), 1/(a-m));
    mach_timebase_info_data_t rv = {(int)m*next.numer + next.denom, next.numer};
    return rv;
}

// Returns monotonic time in nanos, measured from the first time the function
// is called in the process.  The clock may run up to 0.1% faster or slower
// than the "exact" tick count. However, although the bound on the error is
// the same as for the pragmatic answer, the error is actually minimized over
// the given accuracy bound.
uint64_t monotonicTimeNanos() {
    uint64_t now = mach_absolute_time();
    static struct Data {
        Data(uint64_t bias_) : bias(bias_) {
            kern_return_t mtiStatus = mach_timebase_info(&tb);
            assert(mtiStatus == KERN_SUCCESS);
            double frac = (double)tb.numer/tb.denom;
            uint64_t spanTarget = 315360000000000000llu; // 10 years
            if ( getExpressibleSpan(tb.numer, tb.denom) >= spanTarget )
                return;
            for (double errorTarget = 1/1024.0; errorTarget > 0.000001;) {
                mach_timebase_info_data_t newFrac =
                bestFrac((1-errorTarget)*frac, (1+errorTarget)*frac);
                if (getExpressibleSpan(newFrac.numer, newFrac.denom) < spanTarget)
                    break;
                tb = newFrac;
                errorTarget = fabs((double)tb.numer/tb.denom - frac) / frac / 8;
            }
            //assert(getExpressibleSpan(tb.numer, tb.denom) >= spanTarget);
        }
        mach_timebase_info_data_t tb;
        uint64_t bias;
    } data(now);
    return (now - data.bias) * data.tb.numer / data.tb.denom;
}




//##############################################################################################################


static void show_usage(std::string name){
    std::cerr << "--- # ALGORITMOS DE ORDENAÇÃO #---\nversão MacOSX 10.11.4\n\n" << "Uso:  <opções> \n" <<
        "\t -h, --help\t Mostra esse painel de ajuda.\n" <<
        "\t -t, --tamanho\t Tamanho do vetor de dados para ordenação. \n\t\t\tSeguido de um número inteiro, define o tamanho para o vetor de testes:\n\t\t\t -t 10000 -> vetor com dez mil unidades randômicas.\n" <<
        "\t -r, --repetir\t Número de repetições de testes. \n\t\t\tSeguido de um número inteiro, define a quantidade de testes:\n\t\t\t -r 10 -> vetor com dez mil unidades randômicas.\n" <<
        "\tMODOS DE EXECUÇÃO:\n" <<
        "\t -tempo, \t Executa testes de tempo.\n" <<
        "\t -ticks, \t Executa testes de clock ticks.\n" <<
        "\t -ciclos, \t Executa testes de ciclos.\n" <<
        "\t -all, \t\t Executa todos os testes.\n" <<
    std::endl;
}




int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "= = = = = APS Análise de Algoritmos de ordenação = = = = = \n";
    
    
    
    
    /* Configurações dos testes */
    // Quantidade de bateria de testes por execução
    int totalDeExec = 1;
    // Define o tam que o vetor tem
    int tamanho = 10;
    // Modos de testes
    bool testesDeTempo = true;
    bool testesDeTicks = false;
    bool testesDeCiclos = false;
    bool todosOsTestes = false;
    
    for(int a=1 ; a<argc ; ++a){
        std::cout << "Argv[" << a << "] : " <<argv[a] << std::endl;
        if( std::string(argv[a]) == "-h" || std::string(argv[a]) == "--help" ){
            show_usage( argv[a] );
            return 0;
        }
        if( std::string(argv[a]) == "-t" || std::string(argv[a]) == "--tamanho" ){
            std::istringstream ss(argv[a+1]);
            int x;
            if (!(ss >> x)){
                std::cerr << "Parâmetro inválido para atributo -t (" << argv[a+1] << ")" << std::endl;
                return 0;
            }
            tamanho = x;
            std::cout << "\t Tamanho dos vetores: " << tamanho << std::endl;
        }
        if( std::string(argv[a]) == "-r" || std::string(argv[a]) == "--repetir" ){
            std::istringstream ss(argv[a+1]);
            int x;
            if (!(ss >> x)){
                std::cerr << "Parâmetro inválido para atributo -r (" << argv[a+1] << ")" << std::endl;
                return 0;
            }
            totalDeExec = x;
            std::cout << "\t Total de repetições: " << totalDeExec << std::endl;
        }
        if( std::string(argv[a]) == "-tempo" ){
            testesDeTempo = true;
            std::cout << "\t Testes de tempo: OK" << std::endl;
        }
        if( std::string(argv[a]) == "-ticks" ){
            testesDeTicks = true;
            std::cout << "\t Testes de Clock Ticks: OK" << std::endl;
        }
        if( std::string(argv[a]) == "-ciclos" ){
            testesDeCiclos = true;
            std::cout << "\t Testes de Ciclos: OK" << std::endl;
        }
        if( std::string(argv[a]) == "-all" ){
            testesDeTempo = true;
            testesDeTicks = true;
            testesDeCiclos = true;
            todosOsTestes = true;
            std::cout << "\t Todos os testes: OK" << std::endl;
        }
        
    }
    
    
    
    /* vetores de categoria de testes */
    // testes de tempo
    //static const int num_threads_tempo = (totalDeExec+1)*3;/* vezes três para os tres algoritmos*/
    // testes de ticks
    //static const int num_threads_ticks = totalDeExec*3;
    
    /* vetores */
    //std::thread bubbles_tempo_threads[totalDeExec+1];
    //std::thread quicks_tempo_threads[totalDeExec+1];
    if( testesDeTempo || todosOsTestes ){
        std::vector<std::thread> bubble_threads;
        bubble_threads.reserve(totalDeExec);
        std::vector<std::thread> quick_threads;
        quick_threads.reserve(totalDeExec);
        std::vector<std::thread> merge_threads;
        merge_threads.reserve(totalDeExec);
    }
    
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
    
    
    std::vector <MergeSort> merges;//[totalDeExec];
    merges.reserve(totalDeExec);
    
    /* Dados para analise */
    printf("Carregando dados nos vetores: (%d)\n", tamanho);
    int i,j =0;
    
    int vbs[totalDeExec][tamanho];
    int vqs[totalDeExec][tamanho];
    int vms[totalDeExec][tamanho];
    
    for (i=0 ; i < totalDeExec; i++){
        for(j = 0; j < tamanho; j++){
            //printf("\t%d\n",j);
            vbs[i][j] = rand();
            vqs[i][j] = rand();
            //vis[i] = rand();
            //vss[i] = rand();
            //vhs[i] = rand();
            vms[i][j] = rand();
            //vus[i] = rand();
            
            //printf("%d  ",vbs[i][j]);
        }
    }
    
    
    
    
    /* EXECUÇÔES */
    printf("\n(Re)Iniciando Processo: (%d)\n", totalDeExec);
    
    //intancias
    for (i=0 ; i < totalDeExec; i++){
        BubbleSort *b = new BubbleSort();
        bubbles.push_back(*b);
        QuickSort *q = new QuickSort();
        quicks.push_back(*q);
        MergeSort *m = new MergeSort();
        merges.push_back(*m);
    }
    
    //threads
    for (i=0 ; i < totalDeExec; i++){
        //bubbles_tempo_threads[i] = bubbles[i].avaliaTempo(vbs[i], tamanho);
        
        printf("Iniciando as bubble threads: \n");
        printf("\n %p \n", vbs[i]);
        
        bubble_threads.push_back( bubbles[i].avaliaTempo(vbs[i], tamanho) );
    }
    
    for (i=0 ; i < totalDeExec; i++){
        //quicks_tempo_threads[i] = quicks[i].avaliaTempo(vbs[i], tamanho);
        
        printf("Iniciando as quick threads: \n");
        printf("\n %p \n", vqs[i]);
        
        quick_threads.push_back( quicks[i].avaliaTempo(vqs[i], tamanho) );
    }
    for (i=0 ; i < totalDeExec; i++){
        //quicks_tempo_threads[i] = quicks[i].avaliaTempo(vbs[i], tamanho);
        
        printf("Iniciando as merge threads: \n");
        printf("\n %p \n", vms[i]);
        
        merge_threads.push_back( merges[i].avaliaTempo(vms[i], 0, tamanho-1, tamanho) );
    }
    
    for (i=0 ; i < totalDeExec; i++){
        //bubbles_tempo_threads[i].join();
        //quicks_tempo_threads[i].join();
        bubble_threads[i].join();
        quick_threads[i].join();
        merge_threads[i].join();
    }
    
    
    
    
    
    
    
    
    
    
    
    
    /* Quantidade de testes continuos
    int totalDeExec = 10;
    
    
    while( totalDeExec >= 0 ){
        int i;
        int vbs[tamanho];
        int vqs[tamanho];
        int vis[tamanho];
        int vss[tamanho];
        int vhs[tamanho];
        int vms[tamanho];
        int vus[tamanho];
    
        //Cria numeros aleatorios para os vetores
        for(i = 0; i < tamanho; i++){
            vbs[i] = rand();
            vqs[i] = rand();
            vis[i] = rand();
            vss[i] = rand();
            vhs[i] = rand();
            vms[i] = rand();
            vus[i] = rand();
        }
    
    
        BubbleSort bubble;
        QuickSort quick;
        
    
    
        
        printf("\t=============================================\n");
        printf("\tOrdenacao com BubbleSort: %d \n", totalDeExec);
        printf("\t=============================================\n");
    
        //std::thread t1 ( bubble.avaliaTempoDeExecucaoTotal);
        
        //bubble.avaliaTempoDeExecucaoTotal(vbs, tamanho)
        //bubble.avaliaClockTicksTotal(vbs, tamanho);
        //bubble.avaliaTempoDeExecucaoParte1(vbs, tamanho);
        //bubble.avaliaClockTicksParte1(vbs, tamanho);
    
        printf("\t=============================================\n");
        printf("\tOrdenacao com QuickSort: %d \n", totalDeExec);
        printf("\t=============================================\n");
        
        quick.avaliaTempoDeExecucaoTotal(vqs, tamanho);
        //quick.avaliaClockTicksTotal(vqs, tamanho);
    
        
    
        totalDeExec--;
    } */
    
    
    return 0;
}





