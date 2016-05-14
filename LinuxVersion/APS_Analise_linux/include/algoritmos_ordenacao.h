#ifndef ALGORITMOS_ORDENACAO_H
#define ALGORITMOS_ORDENACAO_H

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

class BubbleSort{

    std::string algoritmo = "BubbleSort";

    //para timestamp
    time_t startTime, endTime;
    char inicio[20], fim[20];

    //variáveis para duração
    //uint64_t start,end, elapsed;

    //clock_gettime
    uint64_t diff;
	struct timespec start_t, end_t;

    //variáveis para clock ticks
    clock_t t;

public:
    void avaliaTempoDeExecucaoTotal(int* v, int tam);
    void avaliaClockTicksTotal(int* v, int tam);

    void avaliaTempoCPU(int* v, int tam);

    void avaliaTempoDeExecucaoParte1(int* v, int tam);
    void avaliaClockTicksParte1(int* v, int tam);

    void avaliaTempoDeExecucaoParte2(int* v, int tam);
    void avaliaClockTicksParte2(int* v, int tam);

private:
    void imprimeVetorInicial();
    void imprimeVetorFinal();

    void gravaRegistroDeTempo(std::string nome, int tam);
    void gravaRegistroDeTicks(std::string nome, int tam);
};




class QuickSort{

    std::string algoritmo = "QuickSort";

    //para timestamp
    time_t startTime, endTime;
    char inicio[20], fim[20];

    //variáveis para duração
    //uint64_t start,end, elapsed;

    //clock_gettime
    uint64_t diff;
	struct timespec start_t, end_t;

    //variáveis para clock ticks
    clock_t t;

public:
    void executaQuick(int* v, int tam);

    void avaliaTempoDeExecucaoTotal(int* v, int tam);
    void avaliaClockTicksTotal(int* v, int tam);

    void avaliaTempoDeExecucaoParte1(int* v, int tam);
    void avaliaClockTicksParte1(int* v, int tam);

    void avaliaTempoDeExecucaoParte2(int* v, int tam);
    void avaliaClockTicksParte2(int* v, int tam);

private:
    void imprimeVetorInicial();
    void imprimeVetorFinal();

    void gravaRegistroDeTempo(std::string nome, int tam);
    void gravaRegistroDeTicks(std::string nome, int tam);
};
