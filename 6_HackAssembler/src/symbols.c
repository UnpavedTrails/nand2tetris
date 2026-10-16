#include <string.h>
#include <stdbool.h>
#include "symbols.h"

// Predefined address R0..R15 are already occupied addresses
// so new symbols are alloted address from 16
int addrCounter = 15;

Symbol hashTable[MAX_SYMBOLS] = {
    {"R0", 0}, {"R1", 1}, {"R2", 2},
    {"R3", 3}, {"R4", 4}, {"R5", 5},
    {"R6", 6}, {"R7", 7}, {"R8", 8},
    {"R9", 9}, {"R10", 10}, {"R11", 11},
    {"R12", 12}, {"R13", 13}, {"R14", 14},
    {"R15", 15},
    {"SCREEN", 16384}, {"KBD", 24576},
    {"SP", 0}, {"LCL", 1}, {"ARG", 2},
    {"THIS", 3}, {"THAT", 4}
};

// DJB2 hashing fxn for hashing ONLY symbols 
// input = string, output = index to hashtable
int djb2_hash(char *buffer_symb) {

    // Predefined indexes
    if (!strcmp(buffer_symb, "R0")) return 0;
    else if (!strcmp(buffer_symb, "R1")) return 1;
    else if (!strcmp(buffer_symb, "R2")) return 2;
    else if (!strcmp(buffer_symb, "R3")) return 3;
    else if (!strcmp(buffer_symb, "R4")) return 4;
    else if (!strcmp(buffer_symb, "R5")) return 5;
    else if (!strcmp(buffer_symb, "R6")) return 6;
    else if (!strcmp(buffer_symb, "R7")) return 7;
    else if (!strcmp(buffer_symb, "R8")) return 8;
    else if (!strcmp(buffer_symb, "R9")) return 9;
    else if (!strcmp(buffer_symb, "R10")) return 10;
    else if (!strcmp(buffer_symb, "R11")) return 11;
    else if (!strcmp(buffer_symb, "R11")) return 11;
    else if (!strcmp(buffer_symb, "R12")) return 12;
    else if (!strcmp(buffer_symb, "R13")) return 13;
    else if (!strcmp(buffer_symb, "R14")) return 14;
    else if (!strcmp(buffer_symb, "R15")) return 15;
    else if (!strcmp(buffer_symb, "SCREEN")) return 16;
    else if (!strcmp(buffer_symb, "KBD")) return 17;
    else if (!strcmp(buffer_symb, "SP")) return 18;
    else if (!strcmp(buffer_symb, "LCL")) return 19;
    else if (!strcmp(buffer_symb, "ARG")) return 20;
    else if (!strcmp(buffer_symb, "ARG")) return 20;
    else if (!strcmp(buffer_symb, "THIS")) return 21;
    else if (!strcmp(buffer_symb, "THAT")) return 22;
    
    unsigned long hash = 5381;
    int c;

    // Iterate through each char until '\0' is reached
    while ((c = *buffer_symb++)) {
        hash = ((hash << 5) + hash) + c;
    }

    // MAX_SYMBOLS - 23, cause we have 23 predefined symbols
    // and we must prevent out of bound array indexing
    return (hash % (MAX_SYMBOLS - 23)) + 23;
}

// Finds the slot in hashTable where `name` lives, or where it should go.
//
//   1. djb2_hash() gives the "home" slot for the name.
//   2. Predefined symbols (R0-R15, SCREEN, KBD, SP, LCL, ARG, THIS, THAT)
//      have fixed slots 0-22, so those are returned as they are.
//   3. For any other symbol, the home slot may already be taken by a
//      DIFFERENT name (a hash collision). In that case move on to the
//      next slot, and keep going until we find either:
//          - a slot holding this same name   -> the symbol already exists
//          - an empty slot (name[0] == '\0') -> the symbol is new, put it here
//   4. If we run off the end of the table, wrap around to slot 23.
//      Slots 0-22 are never used for probing because they're reserved.
//
// Without this, two symbols hashing to the same slot overwrite each other
// (e.g. RET_ADDRESS_EQ25 and RET_ADDRESS_CALL90 in Pong.asm), and the
// first one is then wrongly treated as a new variable.
//
// Every function that touches hashTable (add_symbol, add_var,
// find_in_table, symb_to_num) must go through this, so they all agree
// on which slot a name lives in.
static int find_slot(char *name) {
    int idx = djb2_hash(name);      // home slot
    if (idx < 23) return idx;       // predefined symbol: fixed slot
  
    // slot is occupied by a different name -> try the next slot  
    while (hashTable[idx].name[0] != '\0' && strcmp(hashTable[idx].name, name) != 0) {
        idx++;
        if (idx >= MAX_SYMBOLS) idx = 23;   // wrap around, skip reserved slots
    }
    return idx;
}

// Adding a Symbol to the table
// input will be symbol's name as a string (char *)
void add_symbol(char *symbolName, int lineCount) {
    int slot = find_slot(symbolName);
    
    strcpy(hashTable[slot].name, symbolName);
    
    hashTable[slot].addr = lineCount;
}

// Replacing Symbols to num addr as int 
// further sprintf this int into the buffer "sprintf(buffer, "%d", addr);"
// rest will be handled by instruction converting functions
int symb_to_num(char *symbol) {
    return hashTable[find_slot(symbol)].addr;
}

// adding variables to the hash table. variables get addresses from 16 onwards
void add_var(char *variable) {
    int slot = djb2_hash(variable);
    strcpy(hashTable[slot].name, variable);
    hashTable[slot].addr = ++addrCounter;
}

bool find_in_table(char *name) {
    return strcmp(hashTable[find_slot(name)].name, name) == 0;
}
