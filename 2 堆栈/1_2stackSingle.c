#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int Elem;

typedef struct node {
    Elem elem;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    int length;
} Stack;

Node *nodeNew(Elem elem)
{
    Node *node = malloc(sizeof(Node));
    node->elem = elem;
    node->next = NULL;
    return node;
}

void nodeDelete(Node *node)
{
    free(node);
}

void stackInit(Stack *stack)
{
    stack->length = 0;
    stack->head = NULL;
}

void stackDestroy(Stack *stack)
{
    while (stack->head) {
        Node *node = stack->head;
        stack->head = stack->head->next;
        nodeDelete(node);
        stack->length--;
    }	
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

    Elem top = stack->head->elem;
    return top;
}

void stackVisitX(Node *node)
{
    if (node) {
        stackVisitX(node->next);
        printf("  %d", node->elem);
    }
}

void stackVisit(Stack *stack)
{
    Node *node;

    printf("Stack elems:");
    stackVisitX(stack->head);
    printf("\n");
}

void stackPush(Stack *stack, Elem elem)
{
	Node *node=nodeNew(elem);
	node->next=stack->head;
	stack->head=node;
	stack->length++;
}

Elem stackPop(Stack *stack)
{
	
	while(stack->head)
	{
		Node *node=stack->head;;
		Elem e=node->elem;
		printf("%d\n",e);
		nodeDelete(node);
		stack->length--;
	}
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
