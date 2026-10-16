#include <ctype.h> 
#include "cleaning_utils.h"

// Fuction to remove comments from instruction line:
//      this fxn will remove txt that starts with '//'
//      and replace it with '\n\0' i.e. comments line
//      will be replaced with blank lines.
void remove_comments(char buffer[]) {
    for (int i = 0; buffer[i] != '\0'; i++) {

        if (buffer[i] == '/' && buffer[i + 1] == '/') {
            buffer[i] = '\n'; buffer[i + 1] = '\0';
            break;
        }
    }
}

// Function to remove spaces:
//      this function will remove all types of whitespaces
//      like '\n', '\r', ' ', from the entire buffer
//      And will add '\0' at the end of all chars.
//      '\0' will be at buffer[0] if buffer didn't had any chars.
void remove_spaces(char buffer[]) {
    int j = 0;

    // j will keep track of previous index of buffer
    // that doesn't has any space and then the loop
    // will shift buffer components back if there's
    // any space between chars.
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            buffer[j] = buffer[i];
            j++;
        }
    }
    buffer[j] = '\0';
}
