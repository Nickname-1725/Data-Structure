#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

typedef int Elem;

typedef struct node {
    Elem elem;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    int length;
} List;

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

void listInit(List *list)
{
    list->length = 0;
    list->head = NULL;
}

// DRY
void listDestroy(List *list)
{
	
	while(list->head != NULL)
	{
		Node *node=list->head;
		list->head=node->next;
		nodeDelete(node);
		list->length--;
	}
}

int listLength(List *list)
{
    return list->length;
}

Node *listGetNode(List *list, int index)
{
    assert(index >= 0 && index < list->length);
    int i;
    Node *node;
    
    node = list->head;
    for (i = 0; i < index; i++)
        node = node->next;

    assert(i == index);
    return node;
}

Elem listGetElem(List *list, int index)
{
    Node *node = listGetNode(list, index);
    return node->elem;
}

void listPutElem(List *list, int index, Elem elem)
{
    Node *node = listGetNode(list, index);
    node->elem = elem;
}

void listVisit(List *list)
{
    Node *node;

    printf("List elems:");
    for (node = list->head; node != NULL; node = node->next) {
        printf(" %d", node->elem);
    }
    printf("\n");
}

int listLocateElem(List *list, Elem elem)
{
    Node *node;
    int index = 0;

    for (node = list->head; node != NULL; node = node->next) {
        if (node->elem == elem)
            return index;
        index++;
    }
    return -1;
}

void listInsertElem(List *list, int index, Elem elem)
{
    assert(index >= 0 && index <= list->length);

    Node *node = nodeNew(elem);

    if (index == 0) {
        node->next = list->head;
        list->head = node;
    } else {
        Node *prev = listGetNode(list, index - 1);
        Node *next = prev->next;
        prev->next = node;
        node->next = next;
    }

    list->length++;
}

void listAppendElem(List *list, Elem elem)
{
    listInsertElem(list, list->length, elem);
}

void listPrependElem(List *list, Elem elem)
{
    Node *node = nodeNew(elem);
    node->next = list->head;
    list->head = node;
    list->length++;
}

void listDeleteElem(List *list, int index)
{
    assert(index >= 0 && index < list->length);

    if (index == 0) {
        Node *node = list->head;
        list->head = node->next;
        nodeDelete(node);
    } else {
        Node *prev = listGetNode(list, index - 1);
        Node *node = prev->next;
        Node *next = node->next;
        prev->next = next;
        nodeDelete(node);
    }
    list->length--;
}

void testListAppendElem()
{
    List list;
    listInit(&list);

    int i;
    for (i = 0; i < 8; i++)
        listAppendElem(&list, i);
    listVisit(&list);

    listDestroy(&list);
}

void listReverse(List *list)
{
    Stack stack;
    stackInit(&stack);
	
	//Ñ¹Õ»->É¾±í->µ¯Õ»¡£
	Node *node;

    for (node = list->head; node != NULL; node = node->next) 
	{
        Elem e = node->elem;
		stackPush(&stack,e);
    }
	
    listDestroy(list);
	
	while(!stackEmpty(&stack))
	{
		Elem e = stackPop(&stack);
		listAppendElem(list,e);
	}
	
}

void testListReverse()
{
    List list;
    listInit(&list);

    int i;
    for (i = 0; i < 8; i++)
        listAppendElem(&list, i);

    printf("Before listReverse\n");
    listVisit(&list);

    listReverse(&list);

    printf("After listReverse\n");
    listVisit(&list);
    
    listDestroy(&list);
}

int main()
{
    testListReverse();
    return 0;
}