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
    void inicia(std::string nome){
        algoritmo = nome;
    }
    
    void gravaRegistroDeTempo(std::string nome, int tam);
    void gravaRegistroDeTicks(std::string nome, int tam);
};

class BubbleSort : public AlgoritmoParaTeste{
    
public:
    void avaliaTempoDeExecucaoTotal(int* v, int tam);
    void avaliaClockTicksTotal(int* v, int tam);
    
    void avaliaTempoDeExecucaoParte1(int* v, int tam);
    void avaliaClockTicksParte1(int* v, int tam);
    
    void avaliaTempoDeExecucaoParte2(int* v, int tam);
    void avaliaClockTicksParte2(int* v, int tam);
    
};




class QuickSort : public AlgoritmoParaTeste{
    
public:
    void executaQuick(int* v, int tam);
    
    void avaliaTempoDeExecucaoTotal(int* v, int tam);
    void avaliaClockTicksTotal(int* v, int tam);
    
    void avaliaTempoDeExecucaoParte1(int* v, int tam);
    void avaliaClockTicksParte1(int* v, int tam);
    
    void avaliaTempoDeExecucaoParte2(int* v, int tam);
    void avaliaClockTicksParte2(int* v, int tam);
    
};



class InsertionSort : public AlgoritmoParaTeste{
    
public:
    
    void avaliaTempoDeExecucaoTotal(int* v, int tam);
    void avaliaClockTicksTotal(int* v, int tam);
    
};



class SelectionSort : public AlgoritmoParaTeste{
    
public:
    
    void avaliaTempoDeExecucaoTotal(int* v, int tam);
    void avaliaClockTicksTotal(int* v, int tam);

};
 



class HeapSort : public AlgoritmoParaTeste{
    
public:
    void PercorreArvore(int* v, int raiz, int folha);
    
    void avaliaTempoDeExecucaoTotal(int* v, int tam);
    void avaliaClockTicksTotal(int* v, int tam);
    
};




class MergeSort : public AlgoritmoParaTeste{
    
public:
    void executaMergeSort(int* v, int inicio, int fim);
    
    void avaliaTempoDeExecucaoTotal(int* v, int inicio, int fim, int tam);
    void avaliaClockTicksTotal(int* v, int inicio, int fim, int tam);
    
};
