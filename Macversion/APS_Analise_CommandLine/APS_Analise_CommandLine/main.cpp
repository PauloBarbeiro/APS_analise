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
    
    /* Quantidade de testes continuos */
    int totalDeExec = 10;
    
    while( totalDeExec >= 0 ){
        int i;
        int vbs[tamanho];
        int vqs[tamanho];
        int vis[tamanho];
        int vss[tamanho];
        int vhs[tamanho];
        int vms[tamanho];
        int vus[tamanho];
    
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
    
    
        BubbleSort bubble;
        QuickSort quick;
        InsertionSort insertion;
        SelectionSort selection;
        HeapSort heap;
        MergeSort merge;
    
        
        bubble.inicia("BubbleSort");
        quick.inicia("QuickSort");
        insertion.inicia("InsertionSort");
        selection.inicia("SelectionSort");
        heap.inicia("HeapSort");
        merge.inicia("MergeSort");
    
    
        
        printf("\t=============================================\n");
        printf("\tOrdenacao com BubbleSort: %d \n", totalDeExec);
        printf("\t=============================================\n");
    
        bubble.avaliaTempoDeExecucaoTotal(vbs, tamanho);
        //bubble.avaliaClockTicksTotal(vbs, tamanho);
        //bubble.avaliaTempoDeExecucaoParte1(vbs, tamanho);
        //bubble.avaliaClockTicksParte1(vbs, tamanho);
    
        printf("\t=============================================\n");
        printf("\tOrdenacao com QuickSort: %d \n", totalDeExec);
        printf("\t=============================================\n");
        
        quick.avaliaTempoDeExecucaoTotal(vqs, tamanho);
        //quick.avaliaClockTicksTotal(vqs, tamanho);
    
        printf("\t=============================================\n");
        printf("\tOrdenacao com InsertionSort: %d \n", totalDeExec);
        printf("\t=============================================\n");
        insertion.avaliaTempoDeExecucaoTotal(vis, tamanho);
    
        printf("\t=============================================\n");
        printf("\tOrdenacao com SelectionSort: %d \n", totalDeExec);
        printf("\t=============================================\n");
        selection.avaliaTempoDeExecucaoTotal(vss, tamanho);
    
        printf("\t=============================================\n");
        printf("\tOrdenacao com HeapSort: %d \n", totalDeExec);
        printf("\t=============================================\n");
        heap.avaliaTempoDeExecucaoTotal(vhs, tamanho);
    
        printf("\t=============================================\n");
        printf("\tOrdenacao com MergeSort: %d \n", totalDeExec);
        printf("\t=============================================\n");
        merge.avaliaTempoDeExecucaoTotal(vms, 0, tamanho-1, tamanho);
    
        totalDeExec--;
    }
    
    
    return 0;
}





