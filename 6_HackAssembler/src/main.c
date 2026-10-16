#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cleaning_utils.h"
#include "symbols.h"
#include "instruct.h"

int main(int argc, char* argv[]) {

    // Ensure proper usage
    if (argc != 3) {
        printf("Usage: ./Hackassembler <file.asm> <file.hack>\n");
        return 1;
    }

    // Remember file names
    char *infile = argv[1];
    char *outfile = argv[2];

    // Open input file 
    FILE *src = fopen(infile, "r");
    if (src == NULL) {
        printf("Failed to load %s.\n", infile);
        return 2;
    }
    // Open output file
    FILE *dst = fopen(outfile, "w");
    if (dst == NULL) {
        printf("Failed to open %s.\n", outfile);
        fclose(src);
        return 3;
    }

    char buffer[256];
    bool first = true;

    // ---- PASS 1: labels only, no output ----
    int romAddr = 0; 
    // romAddr is the number os instructs before the label
    while (fgets(buffer, sizeof(buffer), src) != NULL) {
        remove_comments(buffer);
        remove_spaces(buffer);

        if (buffer[0] == '\0') continue;

        if (buffer[0] == '(') {
            char passSymbol[MAX_SYMB_LEN]; 
            int i = 1;
            for (; buffer[i] != ')'; i++) {
                passSymbol[i - 1] = buffer[i]; 
            }
            passSymbol[i - 1] = '\0';
            
            add_symbol(passSymbol, romAddr);
            
            continue;
        }
        // anything else is a real instruction
        romAddr++;
    }

    rewind(src);

    // ---- PASS 2: translate, write output ----
    while(fgets(buffer, sizeof(buffer), src) != NULL) {
        
        remove_comments(buffer);
        remove_spaces(buffer);

        if (buffer[0] == '\0' || buffer[0] == '(') continue;
        
        if (buffer[0] == '@') {
            // @symbol to @value            
            if (isalpha(buffer[1])) {
                // looking up in table for existence
                bool inTable = find_in_table(&buffer[1]);
                // if not in table, add
                if (!inTable) add_var(&buffer[1]);
                
                char newbuff[10];
                
                int addr = symb_to_num(&buffer[1]);
                sprintf(newbuff, "%d", addr);

                int i = 0;
    
                while (newbuff[i] != '\0') {
                    buffer[i + 1] = newbuff[i];
                    i++;
                }
                buffer[++i] = '\0';
            }            
            
            a_instructions(buffer, &buffer[1]);
        }
        else c_instructions(buffer);

        buffer[16] = '\0';

        if (!first) fputc('\n', dst);
        first = false;
        
        fputs(buffer, dst);     
    }

    fclose(src);
    fclose(dst);
    return 0;
}
