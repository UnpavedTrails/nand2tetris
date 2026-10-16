#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "c_support.h"

const char *compBits[18] = {
        "101010", "111111", "111010",
        "001100", "110000", "001101",
        "110001", "001111", "110011",
        "011111", "110111", "001110", 
        "110010", "000010", "010011",
        "000111", "000000", "010101"
};

// Parser to detect index of '='
int detect_equal(char buffer[]) {
    int equalIndex = 0;
    
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '=') {
            equalIndex = i;
            break;
        }        
    }
    return equalIndex;
}

// Parser to detct index of ';'
int detect_semicolon(char buffer[]) {
    int semiFound = 0;
    
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == ';') {
            semiFound = i;
            break;
        }
    }
    
    return semiFound;
}

// Fuction to set jump bits 2-0 in newBuffer
void set_jump(char buffer[], char jump[]) {
    if (jump[0] != 'J') {
        buffer[15] = '0';
        buffer[14] = '0';
        buffer[13] = '0'; 
    }
    else {
        switch (jump[1]) {
            case 'E' : buffer[15] = '0'; buffer[14] = '1'; buffer[13] = '0';
                break;
            case 'N' : buffer[15] = '1'; buffer[14] = '0'; buffer[13] = '1';
                break;
            case 'M' : buffer[15] = '1'; buffer[14] = '1'; buffer[13] = '1';   
                break;
            case 'G' : switch (jump[2]) {
                case 'T' : buffer[15] = '1'; buffer[14] = '0'; buffer[13] = '0';   
                    break;
                case 'E' : buffer[15] = '1'; buffer[14] = '1'; buffer[13] = '0';   
                default : break;
            } break;
            case 'L' : switch (jump[2]) {
                case 'E' : buffer[15] = '0'; buffer[14] = '1'; buffer[13] = '1';   
                    break;
                case 'T' : buffer[15] = '0'; buffer[14] = '0'; buffer[13] = '1';   
                    break;
                default : break;
            } break;
            default : break;
        }
    }
}


// Function to set dest bits 3-5 in newBuffer
void set_dest(char buffer[], char newBuffer[], int equalFound) {
    
    // temp string to compare dest from buffer
    // with nand2tetris contract table
    char *dest = malloc(5 * sizeof(char));
    int i = 0;
    for (; i < equalFound; i++) {
        *(dest + i) = buffer[i];
    }
    *(dest + i) = '\0';

    if (!strcmp(dest, "M")) {
        newBuffer[12] = '1';
        newBuffer[11] = '0';
        newBuffer[10] = '0';
    }
    else if(!strcmp(dest, "D")) {
        newBuffer[12] = '0';
        newBuffer[11] = '1';
        newBuffer[10] = '0';
    }
    else if (!strcmp(dest, "MD")) {
        newBuffer[12] = '1';
        newBuffer[11] = '1';
        newBuffer[10] = '0';
    }
    else if (!strcmp(dest, "A")) {
        newBuffer[12] = '0';
        newBuffer[11] = '0';
        newBuffer[10] = '1';
    }
    else if (!strcmp(dest, "AM")) {
        newBuffer[12] = '1';
        newBuffer[11] = '0';
        newBuffer[10] = '1';
    }
    else if (!strcmp(dest, "AD")) {
        newBuffer[12] = '0';
        newBuffer[11] = '1';
        newBuffer[10] = '1';
    }
    else if (!strcmp(dest, "AMD")) {
        newBuffer[12] = '1';
        newBuffer[11] = '1';
        newBuffer[10] = '1';
    }
    else {
        newBuffer[12] = '0';
        newBuffer[11] = '0';
        newBuffer[10] = '0';
    }

    free(dest);
}

char a_bit_spit(int comp) {
    int a = comp % 10;
    if (a) return '1';
    return '0';
}

const char *comp_bits_spit(int comp) {
   int index = (comp / 10) - 1; // comp will be +10 initially
   return compBits[index]; 
}

// tens value will be the index for lookup array
// & ones value will be 'a' bit
// hence this function will return an int btwn 10-181
// 
// Process for index: add ASCII codes of all the chars of comp from buffer in ascii_sum
//                    using the bellow Formula then switch (ascii_sum) 
//                    to update index to a value btwn 1-18
// 
// Note: 1) if the instruction doesn't has an '=' then isEqual = 0 else isEqual = index of '=' + 1;
//       2) if instruction doesn't has ';' then it will loop till end of buffer
//       3) ASCII sum insn't true ASCII sum:
//          A and M will be considered as X
//          each instruction is max 3 chars long, 
//          so along with char it's nth position will also be considered
// 
// Formula for ascii_sum: ASCII * (n + 1) 
int comp_bits_index(char buffer[], int start) { 
    
    bool isM = false;
    int ascii_sum = 0;
    int index; // if index = 0, index = index + 1, i.e. index is natural counting

    for (int i = start, n = 0; buffer[i] != '\0' && buffer[i] != ';'; i++, n++) {

        if (buffer[i] == 'M') isM = true;

        if (buffer[i] == 'M' || buffer[i] == 'A') ascii_sum += 'X' * (n + 1);
        else ascii_sum += buffer[i] * (n + 1);
    }

    switch (ascii_sum) {
        case 48: index = 1;
            break;
        case 49: index = 2;
            break;
        case 143: index = 3;
            break;
        case 68: index = 4;
            break;
        case 88: index = 5;
            break;
        case 169: index = 6;
            break;
        case 209: index = 7;
            break;
        case 181: index = 8;
            break;
        case 221: index = 9;
            break;
        case 301: index = 10;
            break;
        case 321: index = 11;
            break;
        case 305: index = 12;
            break;
        case 325: index = 13;
            break;
        case 418: index = 14;
            break;
        case 422: index = 15; 
            break;
        case 382: index = 16;
            break;
        case 408: index = 17;
            break;
        case 580: index = 18;
            break;
        default: index = 0;
            break;
    }

    return index * 10 + (isM ? 1 : 0);
}
