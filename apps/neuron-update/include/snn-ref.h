#include "trap.h"

#define TESTLIM 1000

void    cont_print(uint64_t a, uint64_t b, int times, char* str, uint64_t r1, uint64_t r2){
    /*
    if(strcmp(str, "ltd") == 0){
        //printf("random input: syn=0x%lx, w(expected syn number)=%d", r1, r2);
        //printf("[   %06d] %s:", times, str);     
        //printf("\033[32m pass \033[0m\t");
        if(b == r2){
            printf("dut syn number:%d ref syn number:%d\n", a, b);
        }else{
            printf("dut syn:0x%lx ref syn:0x%lx\n", a, b);
        }
        return;   
    }
    */
   if(strcmp(str, "ltd") == 0){
    return; 
   }
    bool assert = a == b;
    //printf("random input: a=0x%lx, b=0x%lx", r1, r2);
    //printf("[   %06d] %s:", times, str);
    if(assert) {
        //continue;
        //printf("\033[32m pass \033[0m\t");
        //printf("dut:0x%lx ref:0x%lx\n", a, b);
        return;
    } 
    else{
        printf("\033[31m failed \033[0m\n");
        printf("[   %06d] %s failed, dut_result is 0x%lx, ref_result is 0x%lx\n", times, str, a, b);
        return ;
    }
}

uint64_t rand_like(uint64_t seed){
    srand(seed);
    return rand();
}

uint64_t _ands(uint64_t a, uint64_t b){
    return a & b;
}

uint64_t _rpop(uint64_t a){
    uint64_t cnt = 0;
    for (uint64_t i = 0; i < 64; i++){
        cnt += a & 0x1;
        a >>= 1;
    }
    return cnt;
}

uint64_t _sge(uint64_t vneuron, uint64_t vth, uint64_t vinit){
    return (vneuron >> 1) >= vth ? (vinit << 1) + 1: vneuron & 0xfffffffffffffffe;
}

uint64_t _sls(uint64_t a, bool stdpEn, uint64_t vneuron){
    return stdpEn ? a >> 1: ((a << 1) +(vneuron & 0x1)); 
}

uint64_t _inf(uint64_t a){
    return a;
}

uint64_t _sup(uint64_t syn, uint64_t input, uint64_t output){
    return (input & output);
}

uint64_t _nadd(uint64_t vneuron, uint64_t vin, uint64_t vleak){
    return (vneuron + vin - vleak) << 1;
}

uint64_t _vleak(uint64_t a){
    return a;
}

void PassMassage(void){
    printf("\033[32m===========================\n");
    printf("ALL PASSED\n");
    printf("===========================\033[0m\n");
}

uint16_t rand16bits(){
    int r1 = rand(), r2 = rand();
    int offset = (r2 & 1) << 15;
    return r1 + offset;
}

uint32_t rand32bits(){
    return (rand16bits() << 16) + rand16bits();
}

uint64_t rand64bits(){
    uint64_t high = rand32bits();
    uint64_t low = rand32bits();
    return (high << 32) + low;
}
