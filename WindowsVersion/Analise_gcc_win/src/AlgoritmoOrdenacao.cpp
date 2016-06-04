#include "AlgoritmoOrdenacao.h"



#include <iostream>
#include <fstream>

#include <Windows.h>

#define BILLION 1000000000L


void AlgoritmosOrdenacao::gravaRegistroDeTempo(std::string nome, int tam, bool thread){

    std::strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    std::strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));

    std::string textFileName = nome+".txt";

    std::ofstream textFile;

    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|mainThread:"<< thread << "|inicio:" << inicio <<
    "|fim:" << fim << "|duracao(nanosec):" <<  elapsedTime.QuadPart << std::endl;
    textFile.close();

}

void AlgoritmosOrdenacao::gravaRegistroDeTicks(std::string nome, int tam, bool thread){

    std::strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    std::strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));

    std::string textFileName = nome+".txt";

    std::ofstream textFile;

    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|mainThread:"<< thread << "|inicio:" << inicio << "|fim:" << fim << "|clockticks:" << t  << std::endl;
    textFile.close();

}


void AlgoritmosOrdenacao::gravaRegistroDeCiclos(std::string nome, int tam, bool thread){

    std::strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    std::strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));

    std::string textFileName = nome+".txt";

    std::ofstream textFile;

    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|mainThread:"<< thread << "|inicio:" << inicio << "|fim:" << fim << "|ciclos:" << ciclos << std::endl;
    textFile.close();

}
//*/

/* ========================================================================================  */



void BubbleSort::avaliaTempoDeExecucaoTotal(int *v, int tam, bool thread){
    int tamanho = tam;
    //inicio da avalia��o
    time( &startTime );
    // get ticks per second
	QueryPerformanceFrequency(&frequency);
	// start timer
	QueryPerformanceCounter(&t1);



    int i = tam;
    int trocou;
    do{
        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){
                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);
                //printf("%d",i);
            }
        }
    }while(trocou);

    //fim da avalia��o
    QueryPerformanceCounter(&t2);

    time( &endTime );

    elapsedTime.QuadPart = (t2.QuadPart - t1.QuadPart) * BILLION / frequency.QuadPart;
    //elapsedTicks.QuadPart = t2.QuadPart - t1.QuadPart;

    //std::strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));

    gravaRegistroDeTempo("BubbleSort_TempoExecTotal", tamanho, thread);

}

void BubbleSort::avaliaClockTicksTotal(int *v, int tam, bool thread){
    int tamanho = tam;
    //inicio da avalia��o
    time( &startTime );
    t = clock();

    int i = tam;
    int trocou;
    do{
        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){
                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;
                //for(k = 0; k < j; k++)
                //    printf("%d ", v[k]);
                //printf("%d",i);
            }
        }
    }while(trocou);

    //fim da avalia��o
    t = clock() - t;
    time( &endTime );

    gravaRegistroDeTicks("BubbleSort_TicksExecTotal", tamanho, thread);

}

void BubbleSort::avaliaCiclosTotal(int *v, int tam, bool thread){

    //inicio da avalia��o
    int tamanho = tam;
    //inicio da avalia��o
    time( &startTime );

    ciclos = 0;


    int i = tam;
    int trocou;
    do{
        tam--;
        trocou = 0;
        for(i = 0; i < tam; i++){
            if(v[i] > v[i + 1]){
                int aux = 0;
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                trocou = 1;

                ciclos += 1;

            }
        }
    }while(trocou);


    gravaRegistroDeCiclos("BubbleSort_CiclosExecTotal", tamanho, thread);

} //*/


/* ===========================================================================================  */




//Algoritmo de ordenacao QuickSort
void QuickSort::executaQuick(int* v, int tam){
    //int j = tam, k;
    if (tam <= 1)
        return;
    else {
        int x = v[0];
        int a = 1;
        int b = tam-1;
        do{
            while((a < tam) && (v[a] <= x))
                a++;
            while(v[b] > x)
                b--;
            if(a < b){ // faz troca
                int temp = v[a];
                v[a] = v[b];
                v[b] = temp;
                a++;
                b--;
            }
            //for(k = 0; k < j; k++)
            //    printf("%d ", v[k]);
            //printf("\n");
        }while(a <= b);
        // troca pivo
        v[0] = v[b];
        v[b] = x;
        // ordena sub-vetores restantes
        executaQuick(v, b);
        executaQuick(&v[a], tam-a);
        //for(k = 0; k < j; k++)
        //    printf("%d ", v[k]);
        //printf("\n");
    }
}

void QuickSort::executaQuickComCiclos(int* v, int tam){
    //int j = tam, k;
    if (tam <= 1)
        return;
    else {
        int x = v[0];
        int a = 1;
        int b = tam-1;
        do{
            while((a < tam) && (v[a] <= x))
                a++;
            while(v[b] > x)
                b--;
            if(a < b){ // faz troca
                int temp = v[a];
                v[a] = v[b];
                v[b] = temp;
                a++;
                b--;
            }
            //for(k = 0; k < j; k++)
            //    printf("%d ", v[k]);
            //printf("\n");
        }while(a <= b);
        // troca pivo
        v[0] = v[b];
        v[b] = x;
        ciclos += 1;
        // ordena sub-vetores restantes
        executaQuickComCiclos(v, b);
        executaQuickComCiclos(&v[a], tam-a);
        //for(k = 0; k < j; k++)
        //    printf("%d ", v[k]);
        //printf("\n");

    }
}

void QuickSort::avaliaTempoDeExecucaoTotal(int *v, int tam, bool thread){

    //inicio da avalia��o
    time( &startTime );
    // get ticks per second
	QueryPerformanceFrequency(&frequency);
	// start timer
	QueryPerformanceCounter(&t1);

    executaQuick(v, tam);

    //fim da avalia��o
    QueryPerformanceCounter(&t2);

    time( &endTime );

    elapsedTime.QuadPart = (t2.QuadPart - t1.QuadPart) * BILLION / frequency.QuadPart;
    //diff = BILLION * (end_t.tv_sec - start_t.tv_sec) + end_t.tv_nsec - start_t.tv_nsec;

    gravaRegistroDeTempo("QuickSort_TempoExecTotal", tam, thread);

}

void QuickSort::avaliaClockTicksTotal(int *v, int tam, bool thread){

    //inicio da avalia��o
    time( &startTime );
    t = clock();

    executaQuick(v, tam);

    //fim da avalia��o
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("QuickSort_TicksExecTotal", tam, thread);

}


void QuickSort::avaliaCiclosTotal(int *v, int tam, bool thread){

    //inicio da avalia��o
    time( &startTime );
    ciclos = 0;

    executaQuickComCiclos(v, tam);

    //fim da avalia��o
    //ciclos += 1; //TODO :: isso esta errado
    time( &endTime );
    gravaRegistroDeCiclos("QuickSort_CiclosExecTotal", tam, thread);
    ciclos = 0;
}



/* ========================================================================================= */



void MergeSort::executaMergeSort(int* v, int inicio, int fim){
    int i, j, k, meio, *t;
    if(inicio == fim)
        return;
    //ordenacao recursiva das duas metades
    meio = (inicio + fim)/2;
    executaMergeSort(v, inicio, meio);
    executaMergeSort(v, meio+1, fim);
    //intercalacao no vetor temporario t
    i = inicio;
    j = meio+1;
    k = 0;
    t =(int*)malloc(sizeof(int)*(fim - inicio+1));
    while(i < meio+1 || j < fim+1){
        if(i == meio+1){ //i passou do final da primeira metade, pegar v[j]
            t[k] = v[j];
            j++; k++;
        }else if(j == fim+1){ //j passou do final da segunda metade, pegar v[i]
            t[k] = v[i];
            i++; k++;
        }else if(v[i] < v[j]){ //v[i]<v[j], pegar v[i]
            t[k] = v[i];
            i++; k++;
        }else{ //v[j]<=v[i], pegar v[j]
            t[k] = v[j];
            j++; k++;
        }
        //for(z = 0; z < tamanho; z++)
        //    printf("%d ", v[z]);
        //printf("\n");
    }
    //copia vetor intercalado para o vetor original
    for(i = inicio; i <= fim; i++)
        v[i] = t[i-inicio];
    //for(z = 0; z < tamanho; z++)
    //    printf("%d ", v[z]);
    //printf("\n");
    free(t);
}


void MergeSort::executaMergeSortComCiclos(int* v, int inicio, int fim){
    int i, j, k, meio, *t;
    if(inicio == fim)
        return;
    //ordenacao recursiva das duas metades
    meio = (inicio + fim)/2;
    executaMergeSortComCiclos(v, inicio, meio);
    executaMergeSortComCiclos(v, meio+1, fim);
    //intercalacao no vetor temporario t
    i = inicio;
    j = meio+1;
    k = 0;
    t =(int*)malloc(sizeof(int)*(fim - inicio+1));
    while(i < meio+1 || j < fim+1){
        if(i == meio+1){ //i passou do final da primeira metade, pegar v[j]
            t[k] = v[j];
            j++; k++;
        }else if(j == fim+1){ //j passou do final da segunda metade, pegar v[i]
            t[k] = v[i];
            i++; k++;
        }else if(v[i] < v[j]){ //v[i]<v[j], pegar v[i]
            t[k] = v[i];
            i++; k++;
        }else{ //v[j]<=v[i], pegar v[j]
            t[k] = v[j];
            j++; k++;
        }
        //for(z = 0; z < tamanho; z++)
        //    printf("%d ", v[z]);
        //printf("\n");
    }
    //copia vetor intercalado para o vetor original
    for(i = inicio; i <= fim; i++)
        v[i] = t[i-inicio];
    ciclos += 1;
    //for(z = 0; z < tamanho; z++)
    //    printf("%d ", v[z]);
    //printf("\n");
    free(t);

}


void MergeSort::avaliaTempoDeExecucaoTotal(int* v, int inicio, int fim, int tam, bool thread){

    //inicio da avalia��o
    time( &startTime );
    // get ticks per second
	QueryPerformanceFrequency(&frequency);
	// start timer
	QueryPerformanceCounter(&t1);

    executaMergeSort(v, inicio, fim);

    //fim da avalia��o
    QueryPerformanceCounter(&t2);

    time( &endTime );

    elapsedTime.QuadPart = (t2.QuadPart - t1.QuadPart) * BILLION / frequency.QuadPart;
    //diff = BILLION * (end_t.tv_sec - start_t.tv_sec) + end_t.tv_nsec - start_t.tv_nsec;

    gravaRegistroDeTempo("MergeSort_TempoExecTotal", tam, thread);

}

void MergeSort::avaliaClockTicksTotal(int* v, int inicio, int fim, int tam, bool thread){

    //int tamanho = tam;
    //inicio da avalia��o
    time( &startTime );
    t = clock();

    executaMergeSort(v, inicio, fim);

    //fim da avalia��o
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("MergeSort_TicksExecTotal", tam, thread);

}

void MergeSort::avaliaCiclosTotal(int* v, int inicio, int fim, int tam, bool thread){

    //inicio da avalia��o
    //int tamanho = tam;
    //inicio da avalia��o
    time( &startTime );

    ciclos = 0;

    executaMergeSortComCiclos(v, inicio, fim);


    //fim da avalia��o
    // TODO - avalia��o de ciclos esta errada

    time( &endTime );

    gravaRegistroDeCiclos("MergeSort_CiclosExecTotal", tam, thread);
    ciclos = 0;
}

/*
void MergeSort::avaliaTempoCPU(int* v, int inicio, int fim, int tam, bool thread){
    int tamanho = tam;
    //inicio da avalia��o
    time( &startTime );
    //start = mach_absolute_time();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_t);	// mark start time


    executaMergeSort(v, inicio, fim);

    //fim da avalia��o
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_t);	// mark the end time
    time( &endTime );

    diff = BILLION * (end_t.tv_sec - start_t.tv_sec) + end_t.tv_nsec - start_t.tv_nsec;
	//printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);

    gravaRegistroDeTempo("MergeSort_TempoCPUTotal", tamanho, thread);

}
//*/
