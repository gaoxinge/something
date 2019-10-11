#include <stdio.h>
#include <stdlib.h>
#define STACK_BUFFER 3000
#define TOKEN_BUFFER 3000
#define MEMORY_BUFFER 3000

/* simple stack */
typedef struct {
    int size;
    int array[];
} Stack;

Stack *Stack_new() {
    Stack *stack = malloc(sizeof(Stack) + STACK_BUFFER * sizeof(int));
    stack->size = 0;
    return stack;
}

int Stack_empty(Stack *stack) {
    return stack->size == 0;
}

void Stack_push(Stack *stack, int x) {
    if (stack->size == STACK_BUFFER) {
        fprintf(stderr, "reach max stack buffer size");
        exit(-1);
    }
    stack->array[stack->size] = x;
    stack->size++;
}

int Stack_pop(Stack *stack) {
    if (stack->size == 0) {
        fprintf(stderr, "no element in stack");
        exit(-1);
    }
    int x = stack->array[stack->size - 1];
    stack->size--;
    return x;
}

void Stack_free(Stack *stack) {
    free(stack);
}

/* token and tokens */
typedef struct {
    char op;
    int pos;
} Token;

typedef struct {
    int size;
    Token array[];
} Tokens;

Tokens *Tokens_new() {
    Tokens *tokens = malloc(sizeof(Tokens) + TOKEN_BUFFER * sizeof(Token));
    tokens->size = 0;
    return tokens;
}

void Tokens_add(Tokens *tokens, Token token) {
    if (tokens->size == TOKEN_BUFFER) {
        fprintf(stderr, "reach max token buffer size");
        exit(-1);
    }
    tokens->array[tokens->size] = token;
    tokens->size++;
}

void Tokens_set(Tokens *tokens, Token token, int index) {
    if (index < 0 || index >= tokens->size) {
        fprintf(stderr, "invalid index %d of tokens", index);
        exit(-1);
    }
    tokens->array[index] = token;
}

Token Tokens_get(Tokens *tokens, int index) {
    if (index < 0 || index >= tokens->size) {
        fprintf(stderr, "invalid index %d of tokens", index);
        exit(-1);
    }
    return tokens->array[index];
}

void Tokens_free(Tokens *tokens) {
    free(tokens);
}

/* compile */
Tokens *compile(FILE *f) {
    Tokens *tokens = Tokens_new();
    Stack *stack = Stack_new();
    
    Token token;
    int pos = -1;
    while (1) {
        char c = fgetc(f);
        if (c == EOF) {
            if (!Stack_empty(stack)) {
                fprintf(stderr, "no corresponding ] for [ at pos %d", Stack_pop(stack));
                exit(-1);
            }
            break;
        }
        pos += 1;

        switch (c) {
            case '>':
                token.op = '>'; token.pos = -1;
                Tokens_add(tokens, token);
                break;
            case '<':  
                token.op = '<'; token.pos = -1;
                Tokens_add(tokens, token);
                break;
            case '+':
                token.op = '+'; token.pos = -1;
                Tokens_add(tokens, token);
                break;
            case '-':
                token.op = '-'; token.pos = -1;
                Tokens_add(tokens, token);
                break;
            case '.':
                token.op = '.'; token.pos = -1;
                Tokens_add(tokens, token);
                break;
            case ',':
                token.op = ','; token.pos = -1;
                Tokens_add(tokens, token);
                break;
            case '[':
                token.op = '['; token.pos = -1;
                Tokens_add(tokens, token);
                Stack_push(stack, pos);
                break;
            case ']':
                if (Stack_empty(stack)) {
                    fprintf(stderr, "no corresponding [ for ] at pos %d", pos);
                    exit(-1);
                }
                int left_pos = Stack_pop(stack);
                token.op = '['; token.pos = pos;
                Tokens_set(tokens, token, left_pos);
                token.op = ']'; token.pos = left_pos;
                Tokens_add(tokens, token);
                break;
            default:
                fprintf(stderr, "invalid operator %c at pos %d", c, pos);
                exit(-1);
        }
    }
    
    Stack_free(stack);
    return tokens;
}

/* vm */
void vm(Tokens *tokens) {
    int memory[MEMORY_BUFFER] = {0};
    int *ptr = memory;
    
    int index = 0;
    while (1) {
        if (index == tokens->size)
            break;
        Token token = Tokens_get(tokens, index);
        
        switch (token.op) {
            case '>':
                ptr++;
                index++;
                break;
            case '<':
                ptr--;
                index++;
                break;
            case '+':
                ++*ptr;
                index++;
                break;
            case '-':
                --*ptr;
                index++;
                break;
            case '.':
                putchar(*ptr);
                index++;
                break;
            case ',':
                *ptr = getchar();
                index++;
                break;
            case '[':
                if (*ptr == 0) index = token.pos;
                index++;
                break;
            case ']':
                index = token.pos;
                break;
        }
    }
}

int main() {
    FILE *f;
    Tokens *tokens;

    f = fopen("../test/integer.bf", "r");
    tokens = compile(f);
    vm(tokens);
    Tokens_free(tokens);
    fclose(f);
    printf("\n");
    
    f = fopen("../test/cycle.bf", "r");
    tokens = compile(f);
    vm(tokens);
    Tokens_free(tokens);
    fclose(f);
    printf("\n");
    
    f = fopen("../test/helloworld.bf", "r");
    tokens = compile(f);
    vm(tokens);
    Tokens_free(tokens);
    fclose(f);
    return 0;
}