#ifndef ALGORITMOS_ORDENACAO_H
#define ALGORITMOS_ORDENACAO_H

#include <stdio.h>
#include <iostream>

#include <time.h>
#include <thread>

#ifdef __MACH__
#include <assert.h>
#include <CoreServices/CoreServices.h>
#include <mach/clock.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <unistd.h>
#endif

#endif /* algoritmos_ordenacao_hpp */


class AlgoritmoParaTeste{

public:
    std::string algoritmo;

    //para timestamp
    time_t startTime, endTime;
    char inicio[20], fim[20];

    //clock_gettime
    uint64_t diff;
	struct timespec start_t, end_t;

    //variáveis para clock ticks
    clock_t t;

    //void inicia(std::string nome){
    //    algoritmo = nome;
    //}

    //virtual void avaliaTempoDeExecucaoTotal() = 0;
    void gravaRegistroDeTempo(std::string nome, int tam);
    void gravaRegistroDeTicks(std::string nome, int tam);
};

class BubbleSort : public AlgoritmoParaTeste {

private:
    //int *dados;
    //int tam;

    /*
    std::thread the_thread;
    bool stop_thread = false; // Super simple thread stopping.
    void ThreadMain(){
        while(!stop_thread){
            // Do something useful, e.g:
            std::this_thread::sleep_for( std::chrono::seconds(1) );
        }
    }*/

public:
    /*
    BubbleSort() : the_thread(&BubbleSort::ThreadMain, this) {}
    ~BubbleSort(){
         stop_thread = true;
         the_thread.join();
    }
    */
    BubbleSort(){
        algoritmo = "BubbleSort";
    }

    void avaliaTempoDeExecucaoTotal(int* v, int tam);
    void avaliaClockTicksTotal(int* v, int tam);

    void avaliaTempoCPU(int* v, int tam);

    void avaliaTempoDeExecucaoParte1(int* v, int tam);
    void avaliaClockTicksParte1(int* v, int tam);

    void avaliaTempoDeExecucaoParte2(int* v, int tam);
    void avaliaClockTicksParte2(int* v, int tam);

    std::thread avaliaTempo(int* v, int tam) {
          return std::thread([=] { avaliaTempoDeExecucaoTotal(v, tam); });
      }
};




class QuickSort : public AlgoritmoParaTeste{

public:
    QuickSort(){
        algoritmo = "QuickSort";
    }

    void executaQuick(int* v, int tam);

    void avaliaTempoDeExecucaoTotal(int* v, int tam);
    void avaliaClockTicksTotal(int* v, int tam);

    void avaliaTempoDeExecucaoParte1(int* v, int tam);
    void avaliaClockTicksParte1(int* v, int tam);

    void avaliaTempoDeExecucaoParte2(int* v, int tam);
    void avaliaClockTicksParte2(int* v, int tam);

    std::thread avaliaTempo(int* v, int tam) {
          return std::thread([=] { avaliaTempoDeExecucaoTotal(v, tam); });
      }

};
