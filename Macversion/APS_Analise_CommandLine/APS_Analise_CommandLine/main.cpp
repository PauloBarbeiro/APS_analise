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
    std::cerr << "--- # ALGORITMOS DE ORDENAÇÃO #---\nversão Mac OSX 10.11.4\n\n" << "Uso:  <opções> \n" <<
    "\t -h, --help\t Mostra esse painel de ajuda.\n" <<
    "\t -t, --tamanho\t Tamanho do vetor de dados para ordenação. \n\t\t\tSeguido de um número inteiro, define o tamanho para o vetor de testes:\n\t\t\t -t 10000 -> vetor com dez mil unidades randômicas.\n" <<
    "\t -rep, --repeticoes\t Número de repetições de testes. \n\t\t\tSeguido de um número inteiro, define a quantidade de testes:\n\t\t\t -r 10 -> vetor com dez mil unidades randômicas.\n" <<
    "\tITENS PARA AVALIAÇÃO:\n" <<
    "\t -tempo, \t Executa testes de tempo.\n" <<
    "\t -ticks, \t Executa testes de clock ticks.\n" <<
    "\t -ciclos, \t Executa testes de ciclos.\n" <<
    "\tMODO MULTITAREFAS:\n" <<
    "\t -multi, \t Executa em multithreads.\n" <<
    "\tSELECAO DE ALGORITMOS:\n" <<
    "\t -all, \t\t Executa todos os algoritmos.\n" <<
    "\t -bubble, \t\t Executa algoritmo BubbleSort.\n" <<
    "\t -quick, \t\t Executa algoritmo QuickSort.\n" <<
    "\t -merge, \t\t Executa algoritmo MergeSort.\n" <<
    std::endl;
}


void criaVetorRandomico(int tamanho, int vetor[]){
    
    int i = 0;
    for(i = 0; i < tamanho; i++){
        vetor[i] = rand();
    }
    
}




int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "= = = = = APS Análise de Algoritmos de ordenação = = = = = \n";
    
    std::cout << "argc: "<< argc << std::endl;
    
    int objetivoTeste = 0;
    int tamanho = 10;
    char mtarefas = '\0';
    int totalExec = 1;
    bool start_input = true;
    int algoritmo = 0;
    
    if( argc > 1 ){
        std::cout << "Com parametors \n";
        start_input = false;
        
        for(int a=1 ; a<argc ; ++a){
            
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
            if( std::string(argv[a]) == "-rep" || std::string(argv[a]) == "--repeticoes" ){
                std::istringstream ss(argv[a+1]);
                int x;
                if (!(ss >> x)){
                    std::cerr << "Parâmetro inválido para atributo -r (" << argv[a+1] << ")" << std::endl;
                    return 0;
                }
                totalExec = x;
                std::cout << "\t Total de repetições: " << totalExec << std::endl;
            }
            if( std::string(argv[a]) == "-tempo" ){
                objetivoTeste = 1;
            }
            if( std::string(argv[a]) == "-ticks" ){
                objetivoTeste = 2;
                std::cout << "\t Testes de Clock Ticks: OK" << std::endl;
            }
            if( std::string(argv[a]) == "-ciclos" ){
                objetivoTeste = 3;
                std::cout << "\t Testes de Ciclos: OK" << std::endl;
            }
            if( std::string(argv[a]) == "-multi" ){
                mtarefas = 'y';
                std::cout << "\t MultiTarefas: OK" << std::endl;
            }else{ mtarefas = 'n'; }
            if( std::string(argv[a]) == "-all" ){
                algoritmo = 4;
                std::cout << "\t Todos os Algoritmos: OK" << std::endl;
            }
            if( std::string(argv[a]) == "-bubble" ){
                algoritmo = 1;
                std::cout << "\t Todos o Algoritmo BubbleSort: OK" << std::endl;
            }
            if( std::string(argv[a]) == "-quick" ){
                algoritmo = 2;
                std::cout << "\t Todos o Algoritmo QuickSort: OK" << std::endl;
            }
            if( std::string(argv[a]) == "-merge" ){
                algoritmo = 3;
                std::cout << "\t Todos o Algoritmo MergeSort: OK" << std::endl;
            }
            
        }
        
        
    }
    
    
    
    
    do{
        
        if( argc <= 1 && start_input==true){
            //int algoritmo = 0;
            std::cout << "Escolha o algoritmo a ser testado:\n" << std::endl;
            std::cout << "1:BubbleSort \t 2:QuickSort: \t 3:MergeSort \t 4:Todos\n" << std::endl;
            
            while(!(std::cin >> algoritmo)){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Valor inválido.  Tente novamente: ";
            }
            
            
            std::cout << "   ---- Configurações de testes ---- \n" << std::endl;
            
            
            std::cout << "O que deseja testar nos algoritmos?:\n" << std::endl;
            std::cout << "1:Tempo de execução \t 2:ClockTicks \t 3:Ciclos de execução\n" << std::endl;
            
            while(!(std::cin >> objetivoTeste)){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Valor inválido.  Tente novamente: ";
            }
            
            
            
            std::cout << "Digite o tamanho do vetor para testes:" << std::endl;
            while(!(std::cin >> tamanho)){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Valor inválido.  Tente novamente: ";
            }
            
            
            
            std::cout << "Digite a quantidade de execusões para essa bateria de testes:" << std::endl;
            while(!(std::cin >> totalExec)){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Valor inválido.  Tente novamente: ";
            }
            
            
            
            std::cout << "Usar multitarefas nos testes? Y/N" << std::endl;
            std::cin >> mtarefas;
            bool wrong_input = true;
            if (!( mtarefas != 'Y' && mtarefas != 'y') || !( mtarefas != 'N' && mtarefas != 'n')){
                wrong_input = false;
            }
            while(wrong_input){
                std::cout << "Valor inválido.  Tente novamente: ";
                std::cin >> mtarefas;
                if ( !( mtarefas != 'Y' && mtarefas != 'y') || !( mtarefas != 'N' && mtarefas != 'n') ){
                    wrong_input = false;
                }
                std::cin.clear();
            }
            
        }
        
        
        if (!( mtarefas != 'Y' && mtarefas != 'y') ) { // MULTITASK
            
            // Dados para analise
            int i = 0;
            
            
            int vbs[totalExec][tamanho];
            int vqs[totalExec][tamanho];
            int vms[totalExec][tamanho];
            
            for (i=0 ; i < totalExec; i++){
                
                if(algoritmo == 1 || algoritmo == 4){
                    //std::cout << "criaVetorRandomico VBS" << std::endl;
                    criaVetorRandomico(tamanho, vbs[i]);
                }
                if(algoritmo == 2 || algoritmo == 4){
                    //std::cout << "criaVetorRandomico VBQ" << std::endl;
                    criaVetorRandomico(tamanho, vqs[i]);
                }
                if(algoritmo == 3 || algoritmo == 4){
                    //std::cout << "criaVetorRandomico VMS" << std::endl;
                    criaVetorRandomico(tamanho, vms[i]);
                }
                
            }
            
            //threads
            std::vector<std::thread> bubble_threads;
            //bubble_threads.reserve(totalExec);
            std::vector<std::thread> quick_threads;
            //quick_threads.reserve(totalExec);
            std::vector<std::thread> merge_threads;
            //merge_threads.reserve(totalExec);
            
            if( algoritmo == 1 || algoritmo == 4 ){
                //std::cout << "bubble_threads.reserve " << totalExec << std::endl;
                bubble_threads.reserve(totalExec);
            }
            if( algoritmo == 2 || algoritmo == 4 ){
                //std::cout << "quick_threads.reserve " << totalExec << std::endl;
                quick_threads.reserve(totalExec);
            }
            if( algoritmo == 3 || algoritmo == 4 ){
                //std::cout << "merge_threads.reserve " << totalExec << std::endl;
                merge_threads.reserve(totalExec);
            }
            
            //instancias
            // Vetor para instancias para os algoritmos. Segue a qtd de execusões solicitada.
            // necessárias várias instancias para que os resultados das threads, utilizem as ivars de cada
            // intancia, e não alterem resultados de outras threads
            std::vector <BubbleSort> bubbles;
            std::vector <QuickSort> quicks;
            std::vector <MergeSort> merges;
            
            if( algoritmo == 1 || algoritmo == 4 ){
                //std::cout << "bubbles.reserve " << totalExec << std::endl;
                bubbles.reserve(totalExec);
                //instanciando
                for (i=0 ; i < totalExec; i++){
                    //BubbleSort *b = new BubbleSort();
                    //std::cout << "instance of bubble" << &b << std::endl;
                    //bubbles.push_back(*b);
                    bubbles.push_back(*new BubbleSort());
                }
            }
            if( algoritmo == 2 || algoritmo == 4 ){
                //std::cout << "quicks.reserve " << totalExec << std::endl;
                quicks.reserve(totalExec);
                for (i=0 ; i < totalExec; i++){
                    //QuickSort *q = new QuickSort();
                    //std::cout << "instance of quick" << &q << std::endl;
                    quicks.push_back(*new QuickSort());
                }
            }
            if( algoritmo == 3 || algoritmo == 4 ){
                //std::cout << "merges.reserve " << totalExec << std::endl;
                merges.reserve(totalExec);
                for (i=0 ; i < totalExec; i++){
                    //MergeSort *m = new MergeSort();
                    //std::cout << "instance of merge" << &m << std::endl;
                    merges.push_back(*new MergeSort());
                }
            }
            
            
            //INICIA THREADS
            if(algoritmo == 1 || algoritmo == 4){
                std::cout << "Iniciando as bubble threads:" << std::endl;
                for (i=0 ; i < totalExec; i++){
                    if( objetivoTeste == 1 ){
                        //std::cout << "Bubble Objetivo 1 : " << &bubbles[i] << std::endl;
                        bubble_threads.push_back( bubbles[i].avaliaTempo(vbs[i], tamanho) );
                    }
                    else if( objetivoTeste == 2 ){
                        //std::cout << "Bubble Objetivo 2" << std::endl;
                        bubble_threads.push_back( bubbles[i].avaliaTicks(vbs[i], tamanho) );
                    }
                    else if( objetivoTeste == 3 ){
                        //std::cout << "Bubble Objetivo 3" << std::endl;
                        bubble_threads.push_back( bubbles[i].avaliaCiclos(vbs[i], tamanho) );
                    }
                }
            }
            
            if(algoritmo == 2 || algoritmo == 4){
                std::cout << "Iniciando as quicks threads:" << std::endl;
                for (i=0 ; i < totalExec; i++){
                    if( objetivoTeste == 1 ){
                        //std::cout << "Quick Objetivo 1" << std::endl;
                        quick_threads.push_back( quicks[i].avaliaTempo(vqs[i], tamanho) );
                    }
                    else if( objetivoTeste == 2 ){
                        //std::cout << "Quick Objetivo 2" << std::endl;
                        quick_threads.push_back( quicks[i].avaliaTicks(vqs[i], tamanho) );
                    }
                    else if( objetivoTeste == 3 ){
                        //std::cout << "Quick Objetivo 3" << std::endl;
                        quick_threads.push_back( quicks[i].avaliaCiclos(vqs[i], tamanho) );
                    }
                }
            }
            
            if(algoritmo == 3 || algoritmo == 4){
                std::cout << "Iniciando as merge threads:" << std::endl;
                for (i=0 ; i < totalExec; i++){
                    if( objetivoTeste == 1 )
                        merge_threads.push_back( merges[i].avaliaTempo(vms[i], 0, tamanho-1, tamanho) );
                    else if( objetivoTeste == 2 )
                        merge_threads.push_back( merges[i].avaliaTicks(vms[i], 0, tamanho-1, tamanho) );
                    else if( objetivoTeste == 3 )
                        merge_threads.push_back( merges[i].avaliaCiclos(vms[i], 0, tamanho-1, tamanho) );
                }
            }
            
            for (i=0 ; i < totalExec; i++){
                //std::cout << "Join" << std::endl;
                //std::cout << "t\Bubble "<< &bubble_threads[i] << std::endl;
                //std::cout << "t\Bubble "<< &quick_threads[i] << std::endl;
                if(algoritmo == 1 || algoritmo == 4){
                    bubble_threads[i].join();
                }
                if(algoritmo == 2 || algoritmo == 4){
                    quick_threads[i].join();
                }
                if(algoritmo == 3 || algoritmo == 4){
                    merge_threads[i].join();
                }
            }
            
        }
        else{ // --------------------------------------- SINGLETASK
            
            int vetor_de_testes[tamanho];
            
            //criaVetorRandomico(tamanho, vbs);
            
            BubbleSort *bubbleS = nullptr;
            QuickSort *quickS = nullptr;
            MergeSort *mergeS = nullptr;
            std::cout << "ALgoritmo: " << algoritmo << std::endl;
            switch(algoritmo){
                case 1:
                    bubbleS = new BubbleSort();
                    break;
                case 2:
                    quickS = new QuickSort();
                    break;
                case 3:
                    mergeS = new MergeSort();
                    break;
                case 4:
                    bubbleS = new BubbleSort();
                    quickS = new QuickSort();
                    mergeS = new MergeSort();
                    break;
            }
            
            int count_exec = 0;
            while(count_exec < totalExec){
                
                //1:Tempo de execução \t 2:Tempo de CPU: \t 3:ClockTicks \t 4:Ciclos de execução
                switch(algoritmo){
                    case 1:
                        std::cout << "Iniciando testes BubbleSort ..." << std::endl;
                        if(objetivoTeste == 1){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            bubbleS->avaliaTempoDeExecucaoTotal( vetor_de_testes , tamanho, true );
                        }
                        else if( objetivoTeste == 2){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            bubbleS->avaliaClockTicksTotal( vetor_de_testes , tamanho, true );
                        }
                        else if( objetivoTeste == 3){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            bubbleS->avaliaCiclosTotal( vetor_de_testes , tamanho , true);
                        }
                        break;
                    case 2:
                        std::cout << "Iniciando testes QuickSort ..." << std::endl;
                        if(objetivoTeste == 1){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            quickS->avaliaTempoDeExecucaoTotal( vetor_de_testes , tamanho, true );
                        }
                        else if( objetivoTeste == 2){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            quickS->avaliaClockTicksTotal( vetor_de_testes , tamanho, true );
                        }
                        else if( objetivoTeste == 3){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            quickS->avaliaCiclosTotal( vetor_de_testes , tamanho , true);
                        }
                        break;
                    case 3:
                        std::cout << "Iniciando testes MergeSort ..." << std::endl;
                        if(objetivoTeste == 1){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            mergeS->avaliaTempoDeExecucaoTotal( vetor_de_testes, 0, tamanho-1 , tamanho , true);
                        }
                        else if( objetivoTeste == 2){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            mergeS->avaliaClockTicksTotal( vetor_de_testes, 0, tamanho-1 , tamanho , true);
                        }
                        else if( objetivoTeste == 3){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            mergeS->avaliaCiclosTotal( vetor_de_testes, 0, tamanho-1 , tamanho, true );
                        }
                        break;
                    case 4:
                        std::cout << "Iniciando testes em todos os algoritmos ..." << std::endl;
                        if(objetivoTeste == 1){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            bubbleS->avaliaTempoDeExecucaoTotal( vetor_de_testes , tamanho , true);
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            quickS->avaliaTempoDeExecucaoTotal( vetor_de_testes , tamanho , true);
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            mergeS->avaliaTempoDeExecucaoTotal( vetor_de_testes, 0, tamanho-1 , tamanho , true);
                        }
                        else if( objetivoTeste == 2){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            bubbleS->avaliaClockTicksTotal( vetor_de_testes , tamanho , true);
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            quickS->avaliaClockTicksTotal( vetor_de_testes, tamanho , true);
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            mergeS->avaliaClockTicksTotal( vetor_de_testes, 0, tamanho-1 , tamanho , true);
                        }
                        else if( objetivoTeste == 3){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            bubbleS->avaliaCiclosTotal( vetor_de_testes, tamanho , true);
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            quickS->avaliaCiclosTotal( vetor_de_testes, tamanho , true);
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            mergeS->avaliaCiclosTotal( vetor_de_testes, 0, tamanho-1 , tamanho , true);
                        }
                        break;
                }
                
                
                count_exec += 1;
            }
            
        }
        
        std::cout << "Confira os resultados gravados nos arquivos de log.\n" << std::endl;
        
        
        
        char start_test;
        std::cout << "Reiniciar os Testes? Y/N" << std::endl;
        std::cin >> start_test;
        if (!( start_test != 'Y' && start_test != 'y') ){
            start_input = true;
        }
        else if( !( start_test != 'N' && start_test != 'n')){
            start_input = false;
        }
    }while(start_input);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    // Configurações dos testes
    // Quantidade de bateria de testes por execução
    int totalDeExec = 1;
    // Define o tam que o vetor tem
    int tamanho = 10;
    // Modos de testes
    bool testesDeTempo = true;
    bool testesDeTicks = false;
    bool testesDeCiclos = false;
    bool todosOsTestes = false;
    int qtdModos = 0;
    
    for(int a=1 ; a<argc ; ++a){
        
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
            qtdModos += 1;
            std::cout << "\t Testes de tempo: OK" << std::endl;
        }
        if( std::string(argv[a]) == "-ticks" ){
            testesDeTicks = true;
            std::cout << "\t Testes de Clock Ticks: OK" << std::endl;
            qtdModos += 1;
        }
        if( std::string(argv[a]) == "-ciclos" ){
            testesDeCiclos = true;
            std::cout << "\t Testes de Ciclos: OK" << std::endl;
            qtdModos += 1;
        }
        if( std::string(argv[a]) == "-all" ){
            testesDeTempo = true;
            testesDeTicks = true;
            testesDeCiclos = true;
            todosOsTestes = true;
            qtdModos = 3;
            std::cout << "\t Todos os testes: OK" << std::endl;
        }
        
    }
    
    if( qtdModos == 0 ){
        std::cerr << "Erro de execução: Parâmetros inválidos." << std::endl;
        return 0;
    }
    
    std::cout << "# of execs: " << totalDeExec << std::endl;
    std::cout << "# of modos: " << qtdModos << std::endl;
    std::cout << "# of Threads: " << totalDeExec*qtdModos << std::endl;
    std::cout << "# of Threads: " << (totalDeExec*qtdModos)*3 << std::endl;
    
    // vetores de categoria de testes
    
    // vetores
    std::vector<std::thread> bubble_threads;
    std::vector<std::thread> quick_threads;
    std::vector<std::thread> merge_threads;
    
    
    
    bubble_threads.reserve( totalDeExec * qtdModos);
    quick_threads.reserve( totalDeExec * qtdModos);
    merge_threads.reserve( totalDeExec * qtdModos);
    
    
    // vetores de instancias
    std::vector <BubbleSort> bubbles;
    std::vector <QuickSort> quicks;
    std::vector <MergeSort> merges;
    
    
    bubbles.reserve(totalDeExec);
    quicks.reserve(totalDeExec);
    merges.reserve(totalDeExec);
    
    
    // Dados para analise
    std::cout << "Carregando dados nos vetores: "<< tamanho << std::endl;
    int i,j =0;
    
    int vbs_tempo[totalDeExec][tamanho];
    int vqs_tempo[totalDeExec][tamanho];
    int vms_tempo[totalDeExec][tamanho];
    
    int vbs_ticks[totalDeExec][tamanho];
    int vqs_ticks[totalDeExec][tamanho];
    int vms_ticks[totalDeExec][tamanho];
    
    int vbs_ciclos[totalDeExec][tamanho];
    int vqs_ciclos[totalDeExec][tamanho];
    int vms_ciclos[totalDeExec][tamanho];
    
    for (i=0 ; i < totalDeExec; i++){
        for(j = 0; j < tamanho; j++){
            
            if( testesDeTempo || todosOsTestes ){
                vbs_tempo[i][j] = rand();
                vqs_tempo[i][j] = rand();
                vms_tempo[i][j] = rand();
            }
            
            if( testesDeTicks || todosOsTestes ){
                vbs_ticks[i][j] = rand();
                vqs_ticks[i][j] = rand();
                vms_ticks[i][j] = rand();
            }
            
            if( testesDeCiclos || todosOsTestes ){
                vbs_ciclos[i][j] = rand();
                vqs_ciclos[i][j] = rand();
                vms_ciclos[i][j] = rand();
            }

        }
    }
    
    
    
    
    // EXECUÇÕES
    std::cout << "\nIniciando Processos: " << totalDeExec << std::endl;
    
    
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
            
            if( testesDeTempo || todosOsTestes ){
                bubble_threads.push_back( bubbles[i].avaliaTempo(vbs_tempo[i], tamanho) );
                quick_threads.push_back( quicks[i].avaliaTempo(vqs_tempo[i], tamanho) );
                merge_threads.push_back( merges[i].avaliaTempo(vms_tempo[i], 0, tamanho-1, tamanho) );
            }
            if( testesDeTicks || todosOsTestes ){
                bubble_threads.push_back( bubbles[i].avaliaTicks(vbs_ticks[i], tamanho) );
                quick_threads.push_back( quicks[i].avaliaTicks(vqs_ticks[i], tamanho) );
                merge_threads.push_back( merges[i].avaliaTicks(vms_ticks[i], 0, tamanho-1, tamanho) );
            }
            if( testesDeCiclos || todosOsTestes ){
                bubble_threads.push_back( bubbles[i].avaliaCiclos(vbs_ciclos[i], tamanho) );
                quick_threads.push_back( quicks[i].avaliaCiclos(vqs_ciclos[i], tamanho) );
                merge_threads.push_back( merges[i].avaliaCiclos(vms_ciclos[i], 0, tamanho-1, tamanho) );
            }
            
        }
    
        for (i=0 ; i < totalDeExec*qtdModos; i++){
            bubble_threads[i].join();
            quick_threads[i].join();
            merge_threads[i].join();
        }
        
    
    std::cout << "\nEm execusão.  " << (totalDeExec*qtdModos)*3 << " tasks em execusão. Aguarde...\n" << std::endl;
    //*/
    
    return 0;
}





