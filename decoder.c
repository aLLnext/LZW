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

/*void print_pairs(int pos){
    static char CUR[BUF_SIZE];
    memset(CUR, '\0', BUF_SIZE);
    int k = pos;
    int i = 0;
    CUR[i] = HEAP_D[pos].val;
    while (pos != HEAP_D[pos].val){
        pos = HEAP_D[pos].parent;
        CUR[++i] = HEAP_D[pos].val;
    }
    printf("%d: ",k);
    for (int j = i; j >= 0; --j) {
        putc(CUR[j],stdout);
        fflush(stdout);
    }
    printf("\n");
}*/

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
    /*for (int k = i; k >= 0; --k) {
        for (int j = DEFAULT_B; j >= 0; --j) {
            put_bit(((CUR[k] & (1 << i)) != 0), stream_out);
        }
    }*/
    //fflush_bit(stream_out);
    for (int j = i; j >= 0; --j) {
        fputc(CUR[j],out);
        fflush(out);
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
    fscanf(inp, "%d", &current);
    //int bit;
    //int countb = 7;
    //int p2 = 256;
    /*for (int i = countb; i >= 0; --i) {
        bit = fread_bit(stream_in);
        if (bit == 1)
            current |= 1 << i;
        else
            current &= ~(1 << i);
        put_bit(bit, stream_out);
    }*/
    fprintf(out,"%c", current);
    fflush(out);
    start = current;
    while (1) {
        if (fscanf(inp, "%d", &current) != 1)
            break;
        /*if(bit_feof(stream_in) == EOF)
            break;
        current = 0;
        for (int i = countb; i >= 0; --i) {
            bit = fread_bit(stream_in);
            if (bit == 1)
                current |= 1 << i;
            else
                current &= ~(1 << i);
        }*/

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
    //fflush_bit(stream_out);
    fclose(inp);
    fclose(out);
    printf("OK\n");
    return 0;
}