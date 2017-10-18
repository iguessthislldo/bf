# bf

A simple Brainfuck Interpreter I made for fun after learning how simple
Brainfucks's basic rules where.

Usage: `./bf ARRAY_SIZE FILE`

## Implementation

- bf has an extra symbol `'!'` which causes the interpreter to exit with
a successful status.
- The Brainfuck program is read from file into the array, terminated with a
`'!'` and the data pointer is set to the next cell when the program starts.
- If DEBUG is defined the interpreter will step through the program showing
the interprter state before and after executing the current symbol.

