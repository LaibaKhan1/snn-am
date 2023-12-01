#include "trap.h"

inline uint64_t ands(uint64_t rs1, uint64_t rs2){
/*
    rd = rs1 & rs2
*/

    register uint64_t src1  asm("a1") = rs1;
    register uint64_t src2  asm("a2") = rs2;
    register uint64_t dest  asm("a0");
    asm volatile (
        ".word 0xC5850B"
        :[dest]"=r"(dest)
        :[src1]"r"(src1), [src2]"r"(src2)
    );
    printf("ands_rs1 = %d\n", src1);
    printf("ands_rs2 = %d\n", src2);
    printf("ands_rs1 = %d\n", dest);
    return dest;
}

inline uint64_t rpop(uint64_t rs){
/*
    rd = the population of '1' in rs
*/
    register uint64_t src asm("a1") = rs;
    register uint64_t dest asm("a0");
    asm volatile (
        ".word 0x5950B"
        :[dest]"=r"(dest)
        :[src]"r"(src)
    );
    return dest;
}

inline void sinit(uint64_t vinit/*initial voltage*/, uint64_t enable/*online learning enable*/){
/*
    set snn initial parameters, vinit for intial voltage and enable for STDP enable flag
*/
    // vinit = vinit << 16;
    // enable = enable << 15;
    register uint64_t rd asm("a0");
    int a0 = 10 << 7;
    int func = 7 << 12;
    int opcode = 0xb;
    int instr = vinit + enable + func + a0 + opcode;
     //printf("asm_a0 = %d\n", a0);
     //printf("func = %d\n", func);
    //  printf("instr = %b\n", instr);
    // printf("instr = 0x%llx\n", instr);
    printf("vinit %d\n", vinit);

    asm volatile (
            ".word %[instr]"
            :[rd]"=r"(rd)
            :[instr]"i"(instr)
            );
}

inline uint64_t sge(uint64_t vneuron, uint64_t vth){
/*
    vneuron = vneuron >= vth ? [vinit,1] : [vneuron,0];
*/

    register uint64_t src1 asm("a2") = vneuron;
    register uint64_t src2 asm("a1") = vth;
    register uint64_t res asm("a0");
    asm volatile (
            ".word 0xB6450B"
            :[res]"=r"(res)
            :[src1]"r"(src1), [src2]"r"(src2)
            );
    return res;
}

inline uint64_t nadd(uint64_t vneuron, uint64_t vin){
/*
    vneuron = (vneuron + vin - vleak) << 1
*/

    register uint64_t src1 asm("a2") = vneuron;
    register uint64_t src2 asm("a1") = vin;
    register uint64_t res asm ("a0");
    int a1 = 11 << 20;
    int a2 = 12 << 15;
int func = 2 << 12;
    int a0 = 10 << 7;
    int opcode = 0xb;
    int instr =a1 + a2 + func + a0 + opcode;
    asm volatile (
            ".word %[instr]"
            :[res]"=r"(res)
            :[src1]"r"(src1), [src2]"r"(src2), [instr]"i"(instr)
            );
    return res;
}

inline uint64_t sls(uint64_t output){
/*
    res = output << 1
*/

    register uint64_t src1 asm("a1") = output;
    register uint64_t res asm("a0");
    asm volatile (
        ".word 0x205950B"
        :[res]"=r"(res)
        :[src1]"r"(src1)
    );
    return res;
}

inline uint64_t sup(uint64_t syn, uint64_t input){
/*
    res = syn | input
*/

    register uint64_t res asm("a0");
    register uint64_t src1 asm("a1") = syn;
    register uint64_t src2 asm("a2") = input;
    asm volatile (
        ".word 0x6C5950B"
        :[res]"=r"(res)
        :[src1]"r"(src1), [src2]"r"(src2)
    );
    return res;
}

inline uint64_t nld(uint64_t* base, uint64_t offset){
/*
    res = mem[base + offset]
*/

    register uint64_t* src1 asm("a1") = base;
    register uint64_t res asm("a0");
    int a0 = 10 << 7;
    int a1 = 11 << 15;
    offset = offset << 25;
    int func = 5 << 12;
    int opcode = 0xb;
    int instr = offset + a1 + func + a0 + opcode;
    asm volatile (
        ".word %[instr]"
        :[res]"=r"(res)
        :[src1]"r"(src1), [instr]"i"(instr)
    );
    return res;
}

inline void nst(uint64_t* base, uint64_t rs,  uint64_t offset){
/*
    mem[base + offset] = rs
*/


    register uint64_t src1 asm("a1") = rs;
    register uint64_t* src2 asm("s0") = base;
    int offset_11_5 = offset;
    int offset_4_0 = offset & 0x1f;
    offset_11_5 = offset_11_5 >> 5;
    int s0 = 8 << 15;
    int a1 = 11 << 20;
    int func = 3 << 12;
    int opcode = 0xb;
    offset_11_5 = offset_11_5 << 25;
    offset_4_0 = offset_4_0 << 7;
    int instr = offset_11_5 + a1 + s0 + func + offset_4_0 + opcode;
    asm volatile (
        ".word %[instr]"
        :
        :[src1]"r"(src1), [src2]"r"(src2), [instr]"i"(instr)
    );
}

inline uint64_t inf(uint64_t rs) {
/*
   set inf register with rs
*/
    register uint64_t src   asm("a1") = rs;
    register uint64_t dest  asm("a0");
    asm volatile (
        ".word  0x405950B"
        :[dest]"=r"(dest)
        :[src]"r"(src)
    );
    return dest;
}

inline uint64_t vleak(uint64_t src1){
/*
    set vleak register with src1
*/
    register uint64_t  rs1 asm("a1") = src1;
    register uint64_t  rd  asm("a0");
    asm volatile (
        ".word  0x805950B" //from main file 
        :[rd]"=r"(rd)
        :[rs1]"r"(rs1)
    );
    return rd;
}

inline uint64_t ltd(uint64_t src1, uint64_t src2){
/*
    the synapses with value 1 will be modify by the BS-STDP.
    If a random number is smaller than LTD possibility, then synapses will be set to 0.
*/
    register uint64_t  rs1 asm("a1") = src1;
    register uint64_t  rs2 asm("a3") = src2;
    register uint64_t  rd  asm("a0");
    asm volatile (
        ".word  0xD5E50B"
        :[rd]"=r"(rd)
        :[rs1]"r"(rs1), [rs2]"r"(rs2)
    );
    return rd;
}
