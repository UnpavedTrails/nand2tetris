#ifndef C_SUPPORT_H
#define C_SUPPORT_H

int detect_equal(char buffer[]);
int detect_semicolon(char buffer[]);
void set_jump(char buffer[], char jump[]);
void set_dest(char buffer[], char newBuffer[], int equalFound);
char a_bit_spit(int comp);
const char *comp_bits_spit(int comp);
int comp_bits_index(char buffer[], int start);

#endif
