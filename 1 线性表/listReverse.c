#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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


// list 1 2 3
// tmpL

// list 2 3
// tmpL 1

// list 3
// tmpL 2 1

// list 
// tmpL 3 2 1

// list 3 2 1
// tmpL
void listReverse(List *list)
{
    List tmpL;
    listInit(&tmpL);
	
	while(list->head!=NULL)
	{
		Elem e= list->head->elem;
		listInsertElem(&tmpL,0,e);
		listDeleteElem(list,0);
	}
	
	list->head=tmpL.head;
	tmpL.head=NULL;
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