#include <iostream>
#include <stdio.h>
#include <sstream>
//#include <curses.h>
#include <stdlib.h>
#include<limits>

#include <sys/timeb.h>
#include <ctime>

#include <time.h>
#include <math.h>
#include <vector>
#include <thread>
#include <fstream>

#include "AlgoritmosOrdenacao.h"

//using namespace std;

void criaVetorRandomico(int tamanho, int vetor[]){

    int i = 0;
    for(i = 0; i < tamanho; i++){
            vetor[i] = rand();
        }

}


static void show_usage(std::string name){
    std::cerr << "--- # ALGORITMOS DE ORDENAÇÃO #---\nversão Linux Ubuntu 14.10\n\n" << "Uso:  <opções> \n" <<
        "\t -h, --help\t Mostra esse painel de ajuda.\n" <<
        "\t -t, --tamanho\t Tamanho do vetor de dados para ordenação. \n\t\t\tSeguido de um número inteiro, define o tamanho para o vetor de testes:\n\t\t\t -t 10000 -> vetor com dez mil unidades randômicas.\n" <<
        "\t -rep, --repeticoes\t Número de repetições de testes. \n\t\t\tSeguido de um número inteiro, define a quantidade de testes:\n\t\t\t -r 10 -> vetor com dez mil unidades randômicas.\n" <<
        "\tMODOS DE EXECUÇÃO:\n" <<
        "\t -tempo, \t Executa testes de tempo.\n" <<
        "\t -cpu, \t Executa testes de tempo.\n" <<
        "\t -ticks, \t Executa testes de clock ticks.\n" <<
        "\t -ciclos, \t Executa testes de ciclos.\n" <<
        "\t -multi, \t Executa em multithreads.\n" <<
        "\t -all, \t\t Executa todos os algoritmos.\n" <<
        "\t -bubble, \t\t Executa algoritmo BubbleSort.\n" <<
        "\t -quick, \t\t Executa algoritmo QuickSort.\n" <<
        "\t -merge, \t\t Executa algoritmo MergeSort.\n" <<
    std::endl;
}


int main(int argc, const char * argv[])
{

    int objetivoTeste = 0;
    int tamanho = 10;
    char mtarefas;
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
                objetivoTeste = 3;
                std::cout << "\t Testes de Clock Ticks: OK" << std::endl;
            }
            if( std::string(argv[a]) == "-ciclos" ){
                objetivoTeste = 4;
                std::cout << "\t Testes de Ciclos: OK" << std::endl;
            }
            if( std::string(argv[a]) == "-cpu" ){
                objetivoTeste = 2;
                std::cout << "\t Testes de CPU: OK" << std::endl;
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
    std::cout << "= = = = = APS Análise de Algoritmos de ordenação = = = = = \n\n";




    do{

        if( argc <= 0 && start_input==true){
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
            std::cout << "1:Tempo de execução \t 2:Tempo de CPU: \t 3:ClockTicks \t 4:Ciclos de execução\n" << std::endl;

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
                        bubble_threads.push_back( bubbles[i].avaliaCPU(vbs[i], tamanho) );
                    }
                    else if( objetivoTeste == 3 ){
                        //std::cout << "Bubble Objetivo 3" << std::endl;
                        bubble_threads.push_back( bubbles[i].avaliaTicks(vbs[i], tamanho) );
                    }
                    else if( objetivoTeste == 4 ){
                        //std::cout << "Bubble Objetivo 4" << std::endl;
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
                        quick_threads.push_back( quicks[i].avaliaCPU(vqs[i], tamanho) );
                    }
                    else if( objetivoTeste == 3 ){
                        //std::cout << "Quick Objetivo 3" << std::endl;
                        quick_threads.push_back( quicks[i].avaliaTicks(vqs[i], tamanho) );
                    }
                    else if( objetivoTeste == 4 ){
                        //std::cout << "Quick Objetivo 4" << std::endl;
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
                        merge_threads.push_back( merges[i].avaliaCPU(vms[i], 0, tamanho-1, tamanho) );
                    else if( objetivoTeste == 3 )
                        merge_threads.push_back( merges[i].avaliaTicks(vms[i], 0, tamanho-1, tamanho) );
                    else if( objetivoTeste == 4 )
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

            BubbleSort *bubbleS;
            QuickSort *quickS;
            MergeSort *mergeS;
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
                        else if(objetivoTeste == 2){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            bubbleS->avaliaTempoCPU( vetor_de_testes , tamanho , true);
                        }
                        else if( objetivoTeste == 3){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            bubbleS->avaliaClockTicksTotal( vetor_de_testes , tamanho, true );
                        }
                        else if( objetivoTeste == 4){
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
                        else if(objetivoTeste == 2){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            quickS->avaliaTempoCPU( vetor_de_testes , tamanho , true);
                        }
                        else if( objetivoTeste == 3){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            quickS->avaliaClockTicksTotal( vetor_de_testes , tamanho, true );
                        }
                        else if( objetivoTeste == 4){
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
                        else if(objetivoTeste == 2){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            mergeS->avaliaTempoCPU( vetor_de_testes, 0, tamanho-1 , tamanho, true );
                        }
                        else if( objetivoTeste == 3){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            mergeS->avaliaClockTicksTotal( vetor_de_testes, 0, tamanho-1 , tamanho , true);
                        }
                        else if( objetivoTeste == 4){
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
                        else if(objetivoTeste == 2){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            bubbleS->avaliaTempoCPU( vetor_de_testes, tamanho , true);
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            quickS->avaliaTempoCPU( vetor_de_testes, tamanho , true);
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            mergeS->avaliaTempoCPU( vetor_de_testes, 0, tamanho-1 , tamanho , true);
                        }
                        else if( objetivoTeste == 3){
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            bubbleS->avaliaClockTicksTotal( vetor_de_testes , tamanho , true);
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            quickS->avaliaClockTicksTotal( vetor_de_testes, tamanho , true);
                            criaVetorRandomico(tamanho, vetor_de_testes);
                            mergeS->avaliaClockTicksTotal( vetor_de_testes, 0, tamanho-1 , tamanho , true);
                        }
                        else if( objetivoTeste == 4){
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

    return 0;
}
