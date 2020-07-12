#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int Elem;

typedef struct {
    Elem *elems;
    int length;
    int capacity;  
} Stack;

void stackVisit(Stack *stack)
{
    int i;

    printf("Stack elems:");
    for (i = 0; i < stack->length; i++)
        printf("  %d", stack->elems[i]);
    printf("\n");
}

#define INITIAL_CAPACITY 4

void stackInit(Stack *stack)
{
    stack->elems = malloc(sizeof(Elem) * INITIAL_CAPACITY);
    stack->length = 0;
    stack->capacity = INITIAL_CAPACITY;
}

void stackDestroy(Stack *stack)
{
    free(stack->elems);
}

int stackLength(Stack *stack)
{
    return stack->length;
}

int stackEmpty(Stack *stack)
{
    return stack->length == 0;
}

Elem stackGetTop(Stack *stack)
{
    assert(stack->length > 0);

    Elem top = stack->elems[stack->length - 1];
    return top;
}

void stackPush(Stack *stack, Elem elem)
{
    if (stack->length >= stack->capacity) {
        int newCapacity = stack->capacity * 2;
        stack->elems = realloc(stack->elems, sizeof(Elem) * newCapacity);
        stack->capacity = newCapacity;
    }

    stack->elems[stack->length] = elem;
    stack->length++;
}

Elem stackPop(Stack *stack)
{
    assert(stack->length > 0);
    Elem top = stack->elems[stack->length - 1];
    stack->length--;
    return top;
}

void testStack()
{
    Stack stack;

    stackInit(&stack);
    int i;
    for (i = 0; i < 8; i++)
        stackPush(&stack, i);
    stackVisit(&stack);

    printf("Stack elems:");
    while (!stackEmpty(&stack)) {
        Elem top = stackPop(&stack);
        printf("  %d", top);
    }
    printf("\n");
    stackDestroy(&stack);
}

int main()
{
    testStack();
    return 0;
}
