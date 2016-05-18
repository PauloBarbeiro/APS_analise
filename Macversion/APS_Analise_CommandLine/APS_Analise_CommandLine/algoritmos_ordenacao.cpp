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


void AlgoritmoParaTeste::gravaRegistroDeTempo(std::string nome, int tam){
    //std::cout << "AlgoritmoParaTeste::gravaRegistroDeTempo " << nome << " :: " << tam << std::endl;
    
    std::strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    std::strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));
    
    std::string textFileName = nome+".txt";
    
    std::ofstream textFile;
    
    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|inicio:" << inicio << "|fim:" << fim << "|duracao(nanosec):" << elapsed << std::endl;
    textFile.close();
    
}

void AlgoritmoParaTeste::gravaRegistroDeTicks(std::string nome, int tam){
    
    std::strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    std::strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));
    
    std::string textFileName = nome+".txt";
    
    std::ofstream textFile;
    
    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|inicio:" << inicio << "|fim:" << fim << "|clockticks:" << t  << std::endl;
    textFile.close();
    
}

void AlgoritmoParaTeste::gravaRegistroDeCiclos(std::string nome, int tam){
    
    std::strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    std::strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));
    
    std::string textFileName = nome+".txt";
    
    std::ofstream textFile;
    
    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tam << "|inicio:" << inicio << "|fim:" << fim << "|ciclos:" << ciclos << std::endl;
    textFile.close();
    
}


/* =================================================================================================== */


void BubbleSort::avaliaTempoDeExecucaoTotal(int *v, int tam){
    
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
    gravaRegistroDeTempo("BubbleSort_TempoExecTotal", tamanho);
    
}

void BubbleSort::avaliaClockTicksTotal(int *v, int tam){
    
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
    gravaRegistroDeTicks("BubbleSort_TicksExecTotal", tamanho);
    
}

void BubbleSort::avaliaCiclosTotal(int *v, int tam){
    
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
    
    
    gravaRegistroDeCiclos("BubbleSort_CiclosExecTotal", tamanho);
    
}


/*  ##################################################################################################
    ##################################################################################################
    ##################################################################################################
    ##################################################################################################
*/





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



void QuickSort::avaliaTempoDeExecucaoTotal(int *v, int tam){
    
    //inicio da avaliação
    time( &startTime );
    start = mach_absolute_time();
    
    executaQuick(v, tam);
    
    //fim da avaliação
    end = mach_absolute_time();
    time( &endTime );
    elapsed = end - start;
    gravaRegistroDeTempo("QuickSort_TempoExecTotal", tam);
    
}

void QuickSort::avaliaClockTicksTotal(int *v, int tam){
    
    //inicio da avaliação
    time( &startTime );
    t = clock();
    
    executaQuick(v, tam);
    
    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("QuickSort_TicksExecTotal", tam);
    
}

void QuickSort::avaliaCiclosTotal(int *v, int tam){
    
    //inicio da avaliação
    time( &startTime );
    t = clock();
    
    executaQuick(v, tam);
    
    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("QuickSort_CiclosExecTotal", tam);
    
}


/* ============================================================================================== */



void InsertionSort::avaliaTempoDeExecucaoTotal(int *v, int tam){
    
    //inicio da avaliação
    time( &startTime );
    start = mach_absolute_time();
    
    int i, j, chave;
    for(j = 1; j < tam; j++){
        chave = v[j];
        i = j-1;
        while((i >= 0) && (v[i] > chave)){
            v[i+1] = v[i];
            i--;
        }
        v[i+1] = chave;
        //for(k = 0; k < j; k++)
        //    printf("%d ", v[k]);
        //printf("\n");
    }
    //for(k = 0; k < j; k++)
    //    printf("%d ", v[k]);
    //printf("\n");
    
    //fim da avaliação
    end = mach_absolute_time();
    time( &endTime );
    elapsed = end - start;
    gravaRegistroDeTempo("InsertionSort_TempoExecTotal", tam);
    
}

void InsertionSort::avaliaClockTicksTotal(int *v, int tam){
    
    //inicio da avaliação
    time( &startTime );
    t = clock();
    
    int i, j, chave;
    for(j = 1; j < tam; j++){
        chave = v[j];
        i = j-1;
        while((i >= 0) && (v[i] > chave)){
            v[i+1] = v[i];
            i--;
        }
        v[i+1] = chave;
        //for(k = 0; k < j; k++)
        //    printf("%d ", v[k]);
        //printf("\n");
    }
    //for(k = 0; k < j; k++)
    //    printf("%d ", v[k]);
    //printf("\n");
    
    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("InsertionSort_TicksExecTotal", tam);
    
}


/* ============================================================================================================ */




void SelectionSort::avaliaTempoDeExecucaoTotal(int *v, int tam){
    
    //inicio da avaliação
    time( &startTime );
    start = mach_absolute_time();
    
    int i, j, min;
    for(i = 0; i < (tam-1); i++){
        min = i;
        for(j = (i+1); j < tam; j++){
            if(v[j] < v[min]){
                min = j;
            }
        }
        if(i != min){
            int swap = v[i];
            v[i] = v[min];
            v[min] = swap;
            //for(k = 0; k < tamanho; k++)
            //    printf("%d ", v[k]);
            //printf("\n");
        }
    }
    
    //fim da avaliação
    end = mach_absolute_time();
    time( &endTime );
    elapsed = end - start;
    gravaRegistroDeTempo("SelectionSort_TempoExecTotal", tam);
    
}

void SelectionSort::avaliaClockTicksTotal(int *v, int tam){
    
    //inicio da avaliação
    time( &startTime );
    t = clock();
    
    int i, j, min;
    for(i = 0; i < (tam-1); i++){
        min = i;
        for(j = (i+1); j < tam; j++){
            if(v[j] < v[min]){
                min = j;
            }
        }
        if(i != min){
            int swap = v[i];
            v[i] = v[min];
            v[min] = swap;
            //for(k = 0; k < tamanho; k++)
            //    printf("%d ", v[k]);
            //printf("\n");
        }
    }
    
    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("SelectionSort_TicksExecTotal", tam);
    
}


/* ====================================================================================================================== */

void HeapSort::PercorreArvore(int* v, int raiz, int folha){
    int percorreu, maxfolhas, temp;
    percorreu = 0;
    while((raiz*2 <= folha) && (!percorreu)){
        if(raiz*2 == folha)
            maxfolhas = raiz * 2;
        else if(v[raiz * 2] > v[raiz * 2 + 1])
            maxfolhas = raiz * 2;
        else
            maxfolhas = raiz * 2 + 1;
        if(v[raiz] < v[maxfolhas]){
            temp = v[raiz];
            v[raiz] = v[maxfolhas];
            v[maxfolhas] = temp;
            raiz = maxfolhas;
        }
        else
            percorreu = 1;
        //for(k = 0; k < tamanho; k++)
        //    printf("%d ", v[k]);
        //printf("\n");
    }
}

void HeapSort::avaliaTempoDeExecucaoTotal(int *v, int tam){
    
    //inicio da avaliação
    time( &startTime );
    start = mach_absolute_time();
    
    int i, temp;
    for(i = (tam / 2); i >= 0; i--)
        PercorreArvore(v, i, tam - 1);
    for(i = tam - 1; i >= 1; i--){
        temp = v[0];
        v[0] = v[i];
        v[i] = temp;
        PercorreArvore(v, 0, i-1);
    }
    
    //fim da avaliação
    end = mach_absolute_time();
    time( &endTime );
    elapsed = end - start;
    gravaRegistroDeTempo("HeapSort_TempoExecTotal", tam);
    
}

void HeapSort::avaliaClockTicksTotal(int *v, int tam){
    
    //inicio da avaliação
    time( &startTime );
    t = clock();
    
    int i, temp;
    for(i = (tam / 2); i >= 0; i--)
        PercorreArvore(v, i, tam - 1);
    for(i = tam - 1; i >= 1; i--){
        temp = v[0];
        v[0] = v[i];
        v[i] = temp;
        PercorreArvore(v, 0, i-1);
    }
    
    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("HeapSort_TicksExecTotal", tam);
    
}


/* =========================================================================================================== */

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

void MergeSort::avaliaTempoDeExecucaoTotal(int* v, int inicio, int fim, int tam){
    
    //inicio da avaliação
    time( &startTime );
    start = mach_absolute_time();
    
    executaMergeSort(v, inicio, fim);
    
    //fim da avaliação
    end = mach_absolute_time();
    time( &endTime );
    elapsed = end - start;
    gravaRegistroDeTempo("MergeSort_TempoExecTotal", tam);
    
}

void MergeSort::avaliaClockTicksTotal(int* v, int inicio, int fim, int tam){
    
    //inicio da avaliação
    time( &startTime );
    t = clock();
    
    executaMergeSort(v, inicio, fim);
    
    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("MergeSort_TicksExecTotal", tam);
    
}

void MergeSort::avaliaCiclosTotal(int* v, int inicio, int fim, int tam){
    
    //inicio da avaliação
    time( &startTime );
    t = clock();
    
    executaMergeSort(v, inicio, fim);
    
    //fim da avaliação
    t = clock() - t;
    time( &endTime );
    gravaRegistroDeTicks("MergeSort_CiclosExecTotal", tam);
    
}
