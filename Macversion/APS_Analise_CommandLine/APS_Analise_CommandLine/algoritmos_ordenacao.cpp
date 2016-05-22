//
//  algoritmos_ordenacao.cpp
//  APS_Analise_CommandLine
//
//  Created by Paulo on 10/05/16.
//
//


#include <iostream>
#include <fstream>

#include "algoritmos_ordenacao.hpp"


void AlgoritmoParaTeste::gravaRegistroDeTempo(std::string nome, int tam, bool thread){
    //std::cout << "AlgoritmoParaTeste::gravaRegistroDeTempo " << nome << " :: " << tam << std::endl;
    
    std::strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    std::strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));
    
    std::string textFileName = nome+".txt";
    
    std::ofstream textFile;
    
    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|mainThread:"<< thread  << "|inicio:" << inicio << "|fim:" << fim << "|duracao(nanosec):" << elapsed << std::endl;
    textFile.close();
    
}

void AlgoritmoParaTeste::gravaRegistroDeTicks(std::string nome, int tam, bool thread){
    
    std::strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    std::strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));
    
    std::string textFileName = nome+".txt";
    
    std::ofstream textFile;
    
    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|mainThread:"<< thread  << "|inicio:" << inicio << "|fim:" << fim << "|clockticks:" << t  << std::endl;
    textFile.close();
    
}

void AlgoritmoParaTeste::gravaRegistroDeCiclos(std::string nome, int tam, bool thread){
    
    std::strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    std::strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));
    
    std::string textFileName = nome+".txt";
    
    std::ofstream textFile;
    
    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|mainThread:"<< thread  << "|inicio:" << inicio << "|fim:" << fim << "|ciclos:" << ciclos << std::endl;
    textFile.close();
    
}


/* =================================================================================================== */


void BubbleSort::avaliaTempoDeExecucaoTotal(int *v, int tam, bool thread){
    
    //inicio da avaliação
    int tamanho = tam;
    time( &startTime );
    start = mach_absolute_time();
    
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
    
    //fim da avaliação
    end = mach_absolute_time();
    time( &endTime );
    elapsed = end - start;
    gravaRegistroDeTempo("BubbleSort_TempoExecTotal", tamanho, thread);
    
}

void BubbleSort::avaliaClockTicksTotal(int *v, int tam, bool thread){
    
    //inicio da avaliação
    int tamanho = tam;
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
    
    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("BubbleSort_TicksExecTotal", tamanho, thread);
    
}


void BubbleSort::avaliaCiclosTotal(int *v, int tam, bool thread){
    
    //inicio da avaliação
    int tamanho = tam;
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
    
}


/*  ##################################################################################################
    ##################################################################################################
    ##################################################################################################
    ##################################################################################################
*/





//Algoritmo de ordenacao QuickSort
void QuickSort::executaQuick(int* v, int tam){
    int j = tam, k;
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
            for(k = 0; k < j; k++)
                printf("%d ", v[k]);
            printf(" - ciclo! \n");
            ciclos += 1;
        }while(a <= b);
        // troca pivo
        v[0] = v[b];
        v[b] = x;
        // ordena sub-vetores restantes
        executaQuick(v, b);
        executaQuick(&v[a], tam-a);
        for(k = 0; k < j; k++)
            printf("%d ", v[k]);
        printf(" - ciclo? \n");
        ciclos += 1;
    }
}


//Algoritmo de ordenacao QuickSort
void QuickSort::executaQuickComCiclo(int* v, int tam){
    int j = tam, k;
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
            //printf(" - ciclo! \n");
            ciclos += 1;
        }while(a <= b);
        // troca pivo
        v[0] = v[b];
        v[b] = x;
        // ordena sub-vetores restantes
        executaQuickComCiclo(v, b);
        executaQuickComCiclo(&v[a], tam-a);
        //for(k = 0; k < j; k++)
        //    printf("%d ", v[k]);
        //printf(" - ciclo? \n");
        ciclos += 1;
    }
}


void QuickSort::avaliaTempoDeExecucaoTotal(int *v, int tam, bool thread){
    
    //inicio da avaliação
    time( &startTime );
    start = mach_absolute_time();
    
    executaQuick(v, tam);
    
    //fim da avaliação
    end = mach_absolute_time();
    time( &endTime );
    elapsed = end - start;
    gravaRegistroDeTempo("QuickSort_TempoExecTotal", tam, thread);
    
}

void QuickSort::avaliaClockTicksTotal(int *v, int tam, bool thread){
    
    //inicio da avaliação
    time( &startTime );
    t = clock();
    
    executaQuick(v, tam);
    
    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("QuickSort_TicksExecTotal", tam, thread);
    
}

void QuickSort::avaliaCiclosTotal(int *v, int tam, bool thread){
    
    //inicio da avaliação
    time( &startTime );
    //t = clock();
    
    executaQuickComCiclo(v, tam);
    
    //fim da avaliação
    //t = clock() - t;
    std::cout << " Ciclos:  " << ciclos << std::endl;
    time( &endTime );
    gravaRegistroDeTicks("QuickSort_CiclosExecTotal", tam, thread);
    ciclos = 0;
}




/* =========================================================================================================== */

void MergeSort::executaMergeSort(int* v, int inicio, int fim){
    int i, j, k, meio, *t;
    //int z;
    //int tamanho = 16;
    
    if(inicio == fim)
        return;
    //ciclos += 1;
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
        //printf(" - ciclo? \n");
    }
    //copia vetor intercalado para o vetor original
    for(i = inicio; i <= fim; i++)
        v[i] = t[i-inicio];
    //for(z = 0; z < tamanho; z++)
    //    printf("%d ", v[z]);
    //printf("\n");
    
    free(t);
}

void MergeSort::avaliaTempoDeExecucaoTotal(int* v, int inicio, int fim, int tam, bool thread){
    
    //inicio da avaliação
    time( &startTime );
    start = mach_absolute_time();
    
    executaMergeSort(v, inicio, fim);
    
    //fim da avaliação
    end = mach_absolute_time();
    time( &endTime );
    elapsed = end - start;
    gravaRegistroDeTempo("MergeSort_TempoExecTotal", tam, thread);
    
}

void MergeSort::avaliaClockTicksTotal(int* v, int inicio, int fim, int tam, bool thread){
    
    //inicio da avaliação
    time( &startTime );
    t = clock();
    
    executaMergeSort(v, inicio, fim);
    
    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("MergeSort_TicksExecTotal", tam, thread);
    
}

void MergeSort::avaliaCiclosTotal(int* v, int inicio, int fim, int tam, bool thread){
    
    //inicio da avaliação
    time( &startTime );
    t = clock();
    
    executaMergeSort(v, inicio, fim);
    
    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    //gravaRegistroDeTicks("MergeSort_CiclosExecTotal", tam, thread);
    std::cout << ciclos << std::endl;
    ciclos = 0;
}
