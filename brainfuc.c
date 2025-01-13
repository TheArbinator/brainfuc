// BrainFuC
// Last updated 12 January 2025 by TheArbinator
// A simple Brainfuck interpreter in C.

#include <stdio.h>
#include <stdint.h>

char program[30000];
char arr[30000];
uint16_t loop_pointer_table[256];
uint8_t loop_index = 0;

int main (int argc, char** argv) {

    FILE* input = fopen(argv[1], "r");
    fread(program, 1, 30000, input);
    fclose(input);

    char* head = arr;
    uint16_t program_index = 0;

    while(program_index < 30000 && program[program_index] != '\0') {
        switch (program[program_index]) {
            case '>':
                head++;
                break;
            
            case '<':
                head--;
                break;
            
            case '+':
                (*head)++;
                break;

            case '-':
                (*head)--;
                break;

            case '.':
                printf("%c", *head);
                break;

            case ',':
                *head = getchar();
                break;

            case '[':
                if(*head) {
                    loop_pointer_table[loop_index] = program_index;
                    loop_index++;
                }
                else {
                    int open_brackets = 1;
                    while (open_brackets) {
                        program_index++;
                        if(program[program_index] == '[') open_brackets++;
                        if(program[program_index] == ']') open_brackets--;
                    }
                }
                break;
            
            case ']':
                if(*head) {
                    program_index = loop_pointer_table[loop_index - 1];
                }
                else {
                    loop_index--;
                }
                break;
            
        }
        program_index++;

    }
    return 0;
}