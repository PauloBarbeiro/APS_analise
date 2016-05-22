//
//  algoritmos_ordenacao.hpp
//  APS_Analise_CommandLine
//
//  Created by Paulo on 10/05/16.
//
//

#ifndef algoritmos_ordenacao_hpp
#define algoritmos_ordenacao_hpp

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
    
    //variáveis para duração
    uint64_t start,end, elapsed;
    
    //variáveis para clock ticks
    clock_t t;
    
    // ciclos de execução
    int ciclos;
    
    bool inMainThread;
    
    void avaliaTempoDeExecucaoTotal(int* v, int tam, bool thread);
    void avaliaClockTicksTotal(int* v, int tam, bool thread);
    void avaliaCiclosTotal(int* v, int tam, bool thread);
    
    //para mergesort
    void avaliaTempoDeExecucaoTotal(int* v, int inicio, int fim, int tam, bool thread);
    void avaliaClockTicksTotal(int* v, int inicio, int fim, int tam, bool thread);
    void avaliaCiclosTotal(int* v, int inicio, int fim, int tam, bool thread);
    
    //virtual void avaliaTempoDeExecucaoTotal() = 0;
    void gravaRegistroDeTempo(std::string nome, int tam, bool thread);
    void gravaRegistroDeTicks(std::string nome, int tam, bool thread);
    void gravaRegistroDeCiclos(std::string nome, int tam, bool thread);
    
};




class BubbleSort : public AlgoritmoParaTeste{
    
public:
    BubbleSort(){
        algoritmo = "BubbleSort";
    }
    
    void avaliaTempoDeExecucaoTotal(int* v, int tam, bool thread);
    void avaliaClockTicksTotal(int* v, int tam, bool thread);
    void avaliaCiclosTotal(int* v, int tam, bool thread);
    
    
    std::thread avaliaTempo(int* v, int tam) {
        return std::thread([=] { avaliaTempoDeExecucaoTotal(v, tam, false); });
    }
    
    std::thread avaliaTicks(int* v, int tam) {
        return std::thread([=] { avaliaClockTicksTotal(v, tam, false); });
    }
    
    std::thread avaliaCiclos(int* v, int tam) {
        return std::thread([=] { avaliaCiclosTotal(v, tam, false); });
    }
    
};




class QuickSort : public AlgoritmoParaTeste{
    
public:
    QuickSort(){
        algoritmo = "QuickSort";
    }
    
    void executaQuick(int* v, int tam);
    void executaQuickComCiclo(int* v, int tam);
    
    void avaliaTempoDeExecucaoTotal(int* v, int tam, bool thread);
    void avaliaClockTicksTotal(int* v, int tam, bool thread);
    void avaliaCiclosTotal(int* v, int tam, bool thread);
    
    
    std::thread avaliaTempo(int* v, int tam) {
        return std::thread([=] { avaliaTempoDeExecucaoTotal(v, tam, false); });
    }
    
    std::thread avaliaTicks(int* v, int tam) {
        return std::thread([=] { avaliaClockTicksTotal(v, tam, false); });
    }
    
    std::thread avaliaCiclos(int* v, int tam) {
        return std::thread([=] { avaliaCiclosTotal(v, tam, false); });
    }
    
};




class MergeSort : public AlgoritmoParaTeste{
    
public:
    MergeSort(){
        algoritmo = "MergeSort";
    }
    void executaMergeSort(int* v, int inicio, int fim);
    
    void avaliaTempoDeExecucaoTotal(int* v, int inicio, int fim, int tam, bool thread);
    void avaliaClockTicksTotal(int* v, int inicio, int fim, int tam, bool thread);
    void avaliaCiclosTotal(int* v, int inicio, int fim, int tam, bool thread);
    
    
    std::thread avaliaTempo(int* v, int inicio, int fim, int tam) {
        return std::thread([=] { avaliaTempoDeExecucaoTotal(v, inicio, fim,  tam, false); });
    }
    
    std::thread avaliaTicks(int* v, int inicio, int fim, int tam) {
        return std::thread([=] { avaliaClockTicksTotal(v, inicio, fim, tam, false); });
    }
    
    std::thread avaliaCiclos(int* v, int inicio, int fim, int tam) {
        return std::thread([=] { avaliaCiclosTotal(v, inicio, fim, tam, false); });
    }
    
};
