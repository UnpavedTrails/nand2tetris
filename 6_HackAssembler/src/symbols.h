#ifndef SYMBOLS_H
#define SYMBOLS_H
#include <stdbool.h>
// This headerfile will handle all operations for symbols

#define MAX_SYMB_LEN 50
#define MAX_SYMBOLS  65535

extern int addrCounter;

typedef struct {
    char name[MAX_SYMB_LEN];
    int addr;
} Symbol;

extern Symbol hashTable[MAX_SYMBOLS];

int djb2_hash(char *buffer_symb);
static int find_slot(char *name);
void add_symbol(char *symbolName, int lineCount);
void add_var(char *variable);
int symb_to_num(char *symbol);
bool find_in_table(char *name);

#endif
