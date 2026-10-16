#include <stdlib.h>
#include "instruct.h"
#include "c_support.h"

// Fuction to translate A instructions
void a_instructions(char buffer[], char *buffer1) {
    int value = atoi(buffer1); 
    int current = value;
    
    for (int i = 0; i < 16; i++) {
        buffer[i] = '0';
    }
    buffer[16] = '\0';

    for (int i = 15; i > 0; i--) {
        int remender;

        remender = current % 2;
        current /= 2;
        
        if (remender) {
            buffer[i] = '1';
        } 
    }
}

// Fuction to translate C-instructions
void c_instructions(char buffer[]) {
    // temp buffer
    char newBuffer[17]; 
    // initializing fixed bits i.e. bit 15-13 
    newBuffer[0] = '1'; newBuffer[1] = '1';
    newBuffer[2] = '1'; newBuffer[16] = '\0';

    // index of = and ; chars
    int eqFound = detect_equal(&buffer[0]);
    int semiFound = detect_semicolon(&buffer[0]);

    // setting bits for jump i.e. bit 0-2
    if (semiFound) {
        char jump[3] = {buffer[semiFound + 1], buffer[semiFound + 2], buffer[semiFound + 3]};
        set_jump(newBuffer, jump);
    }
    else {
        newBuffer[13] = '0';
        newBuffer[14] = '0';
        newBuffer[15] = '0';
    }

    // setting bits for dest i.e. bit 3-5
    set_dest(buffer, newBuffer, eqFound);
    
    int compStart = eqFound ? eqFound + 1 : 0;
    int compIndex = comp_bits_index(buffer, compStart);    

    newBuffer[3] = a_bit_spit(compIndex);

    const char *comps = comp_bits_spit(compIndex);

    for (int i = 0; comps[i] != '\0'; i++) {
        newBuffer[4 + i] = comps[i];
    }
    
    // implementation of comp bits remaing....
    // so for test those bits set to '-'
    /* for (int i = 3; i < 10; i++) {
        newBuffer[i] = '-';
        } */

    for (int i = 0; i < 16; i++) {
        buffer[i] = newBuffer[i];
    }
}
