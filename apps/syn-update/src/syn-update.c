#include "snn.h"
#include "snn-ref.h"

// initial defination
#define VINIT   (20 << 1)   // initial voltage(VINIT[63:1],Spike[0] = 0)
#define VTH     40          // treshold voltage(20 << 1)
#define VLEAK   5           // leaky voltage

int vneuron[] = {
    VINIT, VINIT, VINIT, VINIT, VINIT
}; // initialize 5 neurons
int vin[] = {
    25, 10, 15, 20, 25
}; // set 5 input values for each neuron

int main(){
    sinit(VINIT, 1);
    uint64_t output = 0;

    
    // trigger spike before sup
    uint64_t a = 0xffff000ul, b = 0xfffful;
    inf(sge(20 << 1,10));
    output = sup(a, b);
    printf("spike sup 0x%lx\n", output);
    // compute the LTD possibility
    int dw = 0;
    uint64_t possible = 0;
    int wsum = 0;
    int w = 13;
    uint64_t syn = output;
    uint64_t syn_new = 0;
    wsum = rpop(syn);
    dw = wsum > w ? wsum - w : 0;
    possible = dw * 1024 / wsum;
    // LTD
    syn_new = ltd(possible, syn);
    printf("ltd 0x%lx, the number of 1 is %d\n", syn_new, rpop(syn_new));


    // no spike before sup
    inf(sge(5 << 1,10)); 
    output = sup(a,b);
    printf("no spike sup 0x%llx\n", output);


    return 0;
}
