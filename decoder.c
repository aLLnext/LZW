//
// Created by toxaxab on 01.06.18.
//
#include <stdio.h>
#include <memory.h>
#include "define.h"

typedef struct t_node_decoder {
    long long parent;
    unsigned char val;
} t_node_decoder;
t_node_decoder HEAP_D[MAX_SIZE];


FILE *out;
FILE *inp;
t_stream *stream_in;
t_stream *stream_out;
void initializeHEAP() {
    for (int i = 0; i < 256; ++i) {
        HEAP_D[i].val = i;
        HEAP_D[i].parent = i;
    }
}

void del_Heap() {
    memset(HEAP_D, 0, MAX_SIZE * sizeof(t_node_decoder));
}

int get_value(long long pos){
    static char CUR[BUF_SIZE];
    memset(CUR, '\0', BUF_SIZE);
    int i = 0;
    CUR[i] = HEAP_D[pos].val;
    while (pos != HEAP_D[pos].val){
        pos = HEAP_D[pos].parent;
        CUR[++i] = HEAP_D[pos].val;
    }
    return CUR[i];
}

void print_symbol(long long pos) {
    static char CUR[BUF_SIZE];
    memset(CUR, '\0', BUF_SIZE);
    int i = 0;
    CUR[i] = HEAP_D[pos].val;
    while (pos != HEAP_D[pos].val){
        pos = HEAP_D[pos].parent;
        CUR[++i] = HEAP_D[pos].val;
    }
    for (int j = i; j >= 0; --j) {
        fputc(CUR[j],out);
        fflush(out);
    }
}

void read_code(unsigned int *cur, t_stream *stream) {
    *cur = 0;
    int bit = 0;
    for (int i = DEFAULT_B; i >= 0; --i) {
        bit = fread_bit(stream);
        if (bit == 1)
            *cur |= 1 << i;
        else
            *cur &= ~(1 << i);
    }
}

int decode() {
    inp = fopen(inputDECODER, "rb");
    out = fopen(outputDECODER, "wb");
    stream_in = fopen_bit(inp, 0);
    stream_out = fopen_bit(out, BUFF_SIZE);
    int start = 0;
    unsigned int current = 0;
    initializeHEAP();
    int k = DEFAULT_K;
    read_code(&current, stream_in);
    print_symbol(current);
    //int bit;
    //int countb = 7;
    //int p2 = 256;
    start = current;
    while (1) {
        if(bit_feof(stream_in) == EOF)
            break;
        read_code(&current, stream_in);
        if(k <= n){
            if(current < k)
                HEAP_D[k].val = get_value(current);
            else
                HEAP_D[k].val = get_value(start);
            HEAP_D[k].parent = start;
            start = current;
            print_symbol(current);
            k++;
            continue;
        }
        del_Heap();
        initializeHEAP();
        print_symbol(current);
        start = current;
        k = DEFAULT_K;
    }
    fclose_bit(stream_out);
    fclose(inp);
    fclose(out);
    printf("OK\n");
    return 0;
}