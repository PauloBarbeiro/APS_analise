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
    //void inicia(std::string nome){
    //    algoritmo = nome;
    //}
    
    void gravaRegistroDeTempo(std::string nome, int tam);
    void gravaRegistroDeTicks(std::string nome, int tam);
    void gravaRegistroDeCiclos(std::string nome, int tam);
};




class BubbleSort : public AlgoritmoParaTeste{
    
public:
    BubbleSort(){
        algoritmo = "BubbleSort";
    }
    
    void avaliaTempoDeExecucaoTotal(int* v, int tam);
    void avaliaClockTicksTotal(int* v, int tam);
    void avaliaCiclosTotal(int* v, int tam);
    
    std::thread avaliaTempo(int* v, int tam) {
        //printf("\t=============================================\n");
        //printf("\tOrdenacao com BubbleSort: %p tam:%d\n", this, tam);
        //printf("\t=============================================\n");
        return std::thread([=] { avaliaTempoDeExecucaoTotal(v, tam); });
    }
    
    std::thread avaliaTicks(int* v, int tam) {
        //printf("\t=============================================\n");
        //printf("\tOrdenacao com BubbleSort: %p tam:%d\n", this, tam);
        //printf("\t=============================================\n");
        return std::thread([=] { avaliaClockTicksTotal(v, tam); });
    }
    
    std::thread avaliaCiclos(int* v, int tam) {
        //printf("\t=============================================\n");
        //printf("\tOrdenacao com BubbleSort: %p tam:%d\n", this, tam);
        //printf("\t=============================================\n");
        return std::thread([=] { avaliaCiclosTotal(v, tam); });
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
    void avaliaCiclosTotal(int* v, int tam);
    
    
    std::thread avaliaTempo(int* v, int tam) {
        //printf("\t=============================================\n");
        //printf("\tOrdenacao com QuickSort: %p\n", this);
        //printf("\t=============================================\n");
        return std::thread([=] { avaliaTempoDeExecucaoTotal(v, tam); });
    }
    
    std::thread avaliaTicks(int* v, int tam) {
        //printf("\t=============================================\n");
        //printf("\tOrdenacao com BubbleSort: %p tam:%d\n", this, tam);
        //printf("\t=============================================\n");
        return std::thread([=] { avaliaClockTicksTotal(v, tam); });
    }
    
    std::thread avaliaCiclos(int* v, int tam) {
        //printf("\t=============================================\n");
        //printf("\tOrdenacao com BubbleSort: %p tam:%d\n", this, tam);
        //printf("\t=============================================\n");
        return std::thread([=] { avaliaCiclosTotal(v, tam); });
    }
    
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
    MergeSort(){
        algoritmo = "MergeSort";
    }
    void executaMergeSort(int* v, int inicio, int fim);
    
    void avaliaTempoDeExecucaoTotal(int* v, int inicio, int fim, int tam);
    void avaliaClockTicksTotal(int* v, int inicio, int fim, int tam);
    void avaliaCiclosTotal(int* v, int inicio, int fim, int tam);
    
    std::thread avaliaTempo(int* v, int inicio, int fim, int tam) {
        //printf("\t=============================================\n");
        //printf("\tOrdenacao com MergeSort: %p\n", this);
        //printf("\t=============================================\n");
        return std::thread([=] { avaliaTempoDeExecucaoTotal(v, inicio, fim,  tam); });
    }
    
    std::thread avaliaTicks(int* v, int inicio, int fim, int tam) {
        //printf("\t=============================================\n");
        //printf("\tOrdenacao com BubbleSort: %p tam:%d\n", this, tam);
        //printf("\t=============================================\n");
        return std::thread([=] { avaliaClockTicksTotal(v, inicio, fim, tam); });
    }
    
    std::thread avaliaCiclos(int* v, int inicio, int fim, int tam) {
        //printf("\t=============================================\n");
        //printf("\tOrdenacao com BubbleSort: %p tam:%d\n", this, tam);
        //printf("\t=============================================\n");
        return std::thread([=] { avaliaCiclosTotal(v, inicio, fim, tam); });
    }
    
};
