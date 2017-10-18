#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG
//#define VERBOSE

// DEBUG implies VERBOSE
#ifdef DEBUG
#define VERBOSE
#endif

// Definitions
#define DATA_TYPE int
#define MAX_ARRAY_SIZE 65535 // 2**16-1
#define CHECK(X) if ((X) >= s) { fprintf(stderr, "Out of bounds: %u\n", X); return 4; }
#define USAGE "usage: bf SIZE FILE\n"

// Array
DATA_TYPE * a;

// Array Size 
unsigned s;

// Data Position
unsigned p;

// Program Position
size_t pc = 0;

// Program Value
DATA_TYPE c;

int main(int argc, char * argv[]) {

    // Arguments
    if (argc != 3) {
        fprintf(stderr, USAGE);
        return 1;
    }
    s = atol(argv[1]);
    if (s == 0 || s >= MAX_ARRAY_SIZE) {
        fprintf(stderr, "Invalid Array Size");
        return 5;
    }

    // Init Array
    a = calloc(s, sizeof(DATA_TYPE));
    if (a == NULL) return 3;

    // Read File into the Array
    FILE * file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("Could not open file");
        return 2;
    }
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        CHECK(p) a[p++] = ch;
    }
    fclose(file);
    CHECK(p) a[p++] = '!';

    // Main Loop
    bool is_cmd;
    while (true) {
        CHECK(pc) 
        c = a[pc];

#ifdef VERBOSE
        is_cmd = p[pc] == '+' | c == '-' | c == '<' | c == '>' | c == '[' | c == ']' | c == '!';
        if (is_cmd)
            fprintf(stderr, "(a[%u] = '%c'; a[%u] = %d) =>", pc, a[pc], p, a[p]);
#endif

        // Interpret
        unsigned brackets;
        switch (c) {
            // Move
            case '>': p++; CHECK(p) break;
            case '<': p--; CHECK(p) break;

            // Set Value
            case '+': a[p]++; break;
            case '-': a[p]--; break;

            // I/O
            case '.': fputc(a[p], stdout); break;
            case ',': a[p] = fgetc(stdin); break;

            // Branch
            case '[':
                if (a[p]) { // Continue to next pc
                    break;
                }
                // Jump forwards
                brackets = 1;
                while (brackets) {
                    pc++;
                    CHECK(pc) 
                    c = a[pc];
                    brackets = brackets + (c == '[');
                    brackets = brackets - (c == ']');
                }
                break;
            case ']':
                if (!a[p]) { // Continue to next pc
                    break;
                }
                // Jump Backwards
                brackets = 1;
                while (brackets) {
                    pc--;
                    CHECK(pc) 
                    c = a[pc];
                    brackets = brackets - (c == '[');
                    brackets = brackets + (c == ']');
                }
                break;

            // Halt
            case '!':
                return 0;
                break;

            // Anything Else
            default:
                break;
        }


#ifdef VERBOSE
        is_cmd = p[pc] == '+' | c == '-' | c == '<' | c == '>' | c == '[' | c == ']' | c == '!';
        if (is_cmd) {
            fprintf(stderr, "(a[%u] = '%c'; a[%u] = %d)"
#ifndef DEBUG
                "\n"
#endif
                , pc, a[pc], p, a[p]);
#ifdef DEBUG
            fgetc(stdin);
#endif
        }
#endif

        pc++;
    }
}
