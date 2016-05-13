//
//  main.cpp
//  APS_Analise_CommandLine
//
//  Created by Paulo on 10/05/16.
//
//

#include <iostream>
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

#include "json.hpp"

#include <fstream>

#include "algoritmos_ordenacao.hpp"

using json = nlohmann::json;

/*
 Referencias:
    http://www.cplusplus.com/reference/ctime/difftime/
    http://www.cplusplus.com/reference/ctime/clock/
    http://stackoverflow.com/questions/23378063/how-can-i-use-mach-absolute-time-without-overflowing
    https://developer.apple.com/library/mac/qa/qa1398/_index.html
 
 Json:
 https://github.com/nlohmann/json
 
 
 */

//Define o tam que o vetor tem
#define tamanho 100
/*
//Algoritmo de ordenacao BubbleSort
void BubbleSort(int* v, int tam){
    int i, j = tam, k;
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
                for(k = 0; k < j; k++)
                    printf("%d ", v[k]);
                printf("\n");
            }
        }
    }while(trocou);
}
*/

/*
//Algoritmo de ordenacao QuickSort
void QuickSort(int* v, int tam){
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
            printf("\n");
        }while(a <= b);
        // troca pivo
        v[0] = v[b];
        v[b] = x;
        // ordena sub-vetores restantes
        QuickSort(v, b);
        QuickSort(&v[a], tam-a);
        for(k = 0; k < j; k++)
            printf("%d ", v[k]);
        printf("\n");
    }
}
*/

//Algoritmo de ordenacao InsertionSort
void InsertionSort(int* v, int tam){
    int i, j, k, chave;
    for(j = 1; j < tam; j++){
        chave = v[j];
        i = j-1;
        while((i >= 0) && (v[i] > chave)){
            v[i+1] = v[i];
            i--;
        }
        v[i+1] = chave;
        for(k = 0; k < j; k++)
            printf("%d ", v[k]);
        printf("\n");
    }
    for(k = 0; k < j; k++)
        printf("%d ", v[k]);
    printf("\n");
}

//Algoritmo de ordenacao SelectionSort
void SelectionSort(int* v, int tam){
    int i, j, k, min;
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
            for(k = 0; k < tamanho; k++)
                printf("%d ", v[k]);
            printf("\n");
        }
    }
}

//Algoritmo de ordenacao HeapSort
void PercorreArvore(int* v, int raiz, int folha){
    int percorreu, maxfolhas, temp, k;
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
        for(k = 0; k < tamanho; k++)
            printf("%d ", v[k]);
        printf("\n");
    }
}

void HeapSort(int* v, int tam){
    int i, k, temp;
    for(i = (tam / 2); i >= 0; i--)
        PercorreArvore(v, i, tam - 1);
    for(i = tam - 1; i >= 1; i--){
        temp = v[0];
        v[0] = v[i];
        v[i] = temp;
        PercorreArvore(v, 0, i-1);
    }
}

//Algoritmo de ordenacao MergeSort
void MergeSort(int* v, int inicio, int fim){
    int i, j, k, meio, *t, z;
    if(inicio == fim)
        return;
    //ordenacao recursiva das duas metades
    meio = (inicio + fim)/2;
    MergeSort(v, inicio, meio);
    MergeSort(v, meio+1, fim);
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
        for(z = 0; z < tamanho; z++)
            printf("%d ", v[z]);
        printf("\n");
    }
    //copia vetor intercalado para o vetor original
    for(i = inicio; i <= fim; i++)
        v[i] = t[i-inicio];
    for(z = 0; z < tamanho; z++)
        printf("%d ", v[z]);
    printf("\n");
    free(t);
}




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







int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "= = = = = APS Análise de Algoritmos de ordenação = = = = = \n";
    
    int i;
    int vbs[tamanho];
    int vqs[tamanho];
    int vis[tamanho];
    int vss[tamanho];
    int vhs[tamanho];
    int vms[tamanho];
    int vus[tamanho];
    //clrscr();
    //Cria numeros aleatorios para os vetores
    for(i = 0; i < tamanho; i++){
        vbs[i] = rand();
        vqs[i] = rand();
        vis[i] = rand();
        vss[i] = rand();
        vhs[i] = rand();
        vms[i] = rand();
        vus[i] = rand();
    }
    
     //Ordenacao com BubbleSort
     printf("=============================================\n");
     printf("Ordenacao com BubbleSort: \n");
     printf("=============================================\n");
     printf("Vetor original: \n");
     printf("---------------------------------------------\n");
     for(i = 0; i < tamanho; i++){
     printf("%d ", vbs[i]);
     }
     printf("\n---------------------------------------------\n");
     printf("Passos da ordenacao: \n");
     printf("---------------------------------------------\n");
    
    BubbleSort bubble;
    QuickSort quick;
    
    bubble.avaliaTempoDeExecucaoTotal(vbs, tamanho);
    //bubble.avaliaClockTicksTotal(vbs, tamanho);
    //bubble.avaliaTempoDeExecucaoParte1(vbs, tamanho);
    //bubble.avaliaClockTicksParte1(vbs, tamanho);
    
    quick.avaliaTempoDeExecucaoTotal(vqs, tamanho);
    //quick.avaliaClockTicksTotal(vqs, tamanho);
    
    /*
    
    //variáveis para contagem de tempo por segundos
    time_t startTime, endTime;
    double seconds;
    
    //variáveis para contagem de clocks
    clock_t t;
    
    //variáveis para mach
    uint64_t start,end, elapsed, elapsedNano;
    static mach_timebase_info_data_t sTimebaseInfo;
    
    // variáveis para uma tentativa de aprimoramento do uso do mach
    uint64_t start_b, end_b, elapsed_b;
    
    
    
    time( &startTime );
    t = clock();
    start = mach_absolute_time();
    start_b = monotonicTimeNanos();
    
    
     BubbleSort(vbs, tamanho);
    
    
    time( &endTime );
    t = clock() - t;
    end = mach_absolute_time();
    end_b = monotonicTimeNanos();
    
    
    elapsed = end - start;
    if ( sTimebaseInfo.denom == 0 ) {
        (void) mach_timebase_info(&sTimebaseInfo);
    }
    elapsedNano = elapsed * sTimebaseInfo.numer / sTimebaseInfo.denom;
    
    
    seconds = difftime(endTime, startTime);
    
    elapsed_b = end_b - start_b;
    
    
    printf("\n\nBubbleSort duração: %f segundos (Usando ctime)\n", seconds);
    printf("BubbleSort clock ticks: %lu (%f segundos  (Usando clock: tempo é IMPRECISO)\n", t, ((float)t)/CLOCKS_PER_SEC );
    
    std::cout << "BubblseSort segundos: " << elapsed/1000000000.00 << " :: nanosegundos: " << elapsed << std::endl;
    std::cout << "BubblseSort nanosegundos from Mach: " << elapsedNano <<  std::endl;
    
    //std::cout << "BubblseSort nanosegundos from Mach 2: " << elapsed_b << std::endl;
    
    
    // variáveis para Json
    std::string algoritmo = "BubbleSort";
    char inicio[20];
    std::strftime(inicio, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime));
    char fim[20];
    std::strftime(fim, 20, "%Y-%m-%d %H:%M:%S", localtime(&endTime));
    
    // create an array value
    json array = {
        {"algoritmo",   algoritmo},
        {"tamanho", tamanho},
        {"inicio",      inicio},
        {"fim",         fim},
        {"ticks",       t},
        {"duracao",     (elapsed/1000000000.00)}
    };
    
    // get am iterator to the first element
    //json::iterator it = array.begin();
    
    // serialize the element that the iterator points to
    //std::cout << array << '\n';
    //std::cout << *it << '\n';
    
    std::cout << std::setw(4) << array << std::endl;
    std::string format = ".json";
    //std::string jsonFileName = algoritmo+"-"+inicio+format;
    std::string jsonFileName = algoritmo+format;
    std::string textFileName = algoritmo+".txt";
    //std::cout << jsonFileName << std::endl;
    
    std::ofstream jsonFile;
    std::ofstream textFile;
    
    jsonFile.open(jsonFileName, std::ios::app);
    jsonFile << std::setw(4) << array << std::endl;
    jsonFile.close();
    
    textFile.open(textFileName, std::ios::app);
    textFile << "algoritmo:" << algoritmo << "|tamanho:" << tamanho << "|inicio:" << inicio << "|fim:" << fim << "|clockticks:" << t << "|duracao:" << (elapsed/1000000000.00) << std::endl;
    textFile.close();
    */
    
    /*
     Ordenacao com QuickSort
     printf("\n\n\n=============================================\n");
     printf("Ordenacao com QuickSort: \n");
     printf("=============================================\n");
     printf("Vetor original: \n");
     printf("---------------------------------------------\n");
     for(i = 0; i < tamanho; i++){
     printf("%d ", vqs[i]);
     }
     printf("\n---------------------------------------------\n");
     printf("Passos da ordenacao: \n");
     printf("---------------------------------------------\n");
     QuickSort(vqs, tamanho);
    */
    
    /*Ordenacao com InsertionSort
     printf("\n\n\n=============================================\n");
     printf("Ordenacao com InsertionSort: \n");
     printf("=============================================\n");
     printf("Vetor original: \n");
     printf("---------------------------------------------\n");
     for(i = 0; i < tamanho; i++){
     printf("%d ", vis[i]);
     }
     printf("\n---------------------------------------------\n");
     printf("Passos da ordenacao: \n");
     printf("---------------------------------------------\n");
     InsertionSort(vis, tamanho);
     */
    
    /*Ordenacao com SelectionSort
     printf("\n\n\n=============================================\n");
     printf("Ordenacao com SelectionSort: \n");
     printf("=============================================\n");
     printf("Vetor original: \n");
     printf("---------------------------------------------\n");
     for(i = 0; i < tamanho; i++){
     printf("%d ", vss[i]);
     }
     printf("\n---------------------------------------------\n");
     printf("Passos da ordenacao: \n");
     printf("---------------------------------------------\n");
     SelectionSort(vss, tamanho);
     */
    
    /*Ordenacao com HeapSort
     printf("\n\n\n=============================================\n");
     printf("Ordenacao com HeapSort: \n");
     printf("=============================================\n");
     printf("Vetor original: \n");
     printf("---------------------------------------------\n");
     for(i = 0; i < tamanho; i++){
     printf("%d ", vhs[i]);
     }
     printf("\n---------------------------------------------\n");
     printf("Passos da ordenacao: \n");
     printf("---------------------------------------------\n");
     HeapSort(vhs, tamanho);
     */
    
    /*Ordenacao com MergeSort
     printf("\n\n\n=============================================\n");
     printf("Ordenacao com MergeSort: \n");
     printf("=============================================\n");
     printf("Vetor original: \n");
     printf("---------------------------------------------\n");
     for(i = 0; i < tamanho; i++){
     printf("%d ", vms[i]);
     }
     printf("\n---------------------------------------------\n");
     printf("Passos da ordenacao: \n");
     printf("---------------------------------------------\n");
     MergeSort(vms, 0, tamanho-1);
     */
    
    
    //getch();
    
    
    return 0;
}





