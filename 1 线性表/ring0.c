#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Elem;

typedef struct {
    Elem *elems;
    int length;
    int capacity;  
} List;

void listVisit(List *list)
{
    int i;

    printf("List elems:");
    for (i = 0; i < list->length; i++)
        printf("  %d", list->elems[i]);
    printf("\n");
}

#define INITIAL_CAPACITY 4

void listInit(List *list)
{
    list->elems = malloc(sizeof(Elem) * INITIAL_CAPACITY);
    list->length = 0;
    list->capacity = INITIAL_CAPACITY;
}

void listDestroy(List *list)
{
    free(list->elems);
}

int listLength(List *list)
{
    return list->length;
}

int listEmpty(List *list)
{
    return list->length == 0;
}

Elem listGetElem(List *list, int index)
{
    assert(index >= 0 && index < list->length);
    return list->elems[index];
}

void listPutElem(List *list, int index, Elem elem)
{
    assert(index >= 0 && index < list->length);
    list->elems[index] = elem;
}

int listLocateElem(List *list, Elem elem)
{
    int i;

    for (i = 0; i < list->length; i++) {
        if (list->elems[i] == elem)
            return i;
    }
    return -1;
}

void listInsertElem(List *list, int index, Elem elem)
{
    assert(index >= 0 && index <= list->length);

    if (list->length >= list->capacity) {
        int newCapacity = list->capacity * 2;
        list->elems = realloc(list->elems, sizeof(Elem) * newCapacity);
        list->capacity = newCapacity;
    }

    int i;
    for (i = list->length; i > index; i--)
        list->elems[i] = list->elems[i - 1];
    list->elems[index] = elem;
    list->length++;
}

void listAppendElem(List *list, Elem elem)
{
    listInsertElem(list, list->length, elem);
}

void listDeleteElem(List *list, int index)
{
    assert(index < list->length);

    int i;
    for (i = index; i < list->length - 1; i++) 
        list->elems[i] = list->elems[i + 1];
    list->length--;
}

void createRing(List *list, int n)
{
    int i;

    for (i = 0; i < n; i++)
        listAppendElem(list, i);
}

void joseph(int n, int m)
{
    List list;
    listInit(&list);
    createRing(&list, n);
	int i;
	for(i=m-1;list.length != 1;i+=m-1)
	{
		i=i % list.length;
		printf("%d",listGetElem(&list, i));
		listDeleteElem(&list,i);
    }
	printf("%d",listGetElem(&list, 0));
}

int main()
{
    joseph(6, 5);
    return 0;
}
