#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int Elem;

typedef struct node {
    int sno;
    char name[16];
    struct node *next;
} Node;

typedef struct {
    Node *head;
    int length;
} List;

List list;

Node *nodeNew(int sno, char *name)
{
    Node *node = malloc(sizeof(Node));
    node->sno = sno;
    strcpy(node->name, name);
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

void listVisit(List *list)
{
    Node *node;

    printf("Students:\n");
    for (node = list->head; node != NULL; node = node->next) {
        printf("%d %s\n", node->sno, node->name);
    }
}

void listInsertElem(List *list, int index, int sno, char *name)
{
    assert(index >= 0 && index <= list->length);

    Node *node = nodeNew(sno, name);

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

void addStudent(int sno, char *name)
{
	listInsertElem(&list,list.length,sno,name);
}

char *queryStudent(int sno)
{
    //±éÀúµ¥Á´±í 
	Node *node;int i=0;

    for (node = list.head; node != NULL; node = node->next) 
	{
        if(node->sno==sno)
		{
			break;
		}
		i++;
    }
	if(i<list.length)
	{
		node = listGetNode(&list, i);
		return node->name;
	}
	else return "Not Found";
}

void testQueryStudent()
{
    addStudent(1, "tom");
    addStudent(2, "jerry");
    addStudent(3, "mike");
    addStudent(4, "john");

    int sno;
    char *name;

    sno = 2;
    name = queryStudent(sno);
    printf("sno = %d, name = %s\n", sno, name); 

    sno = 3;
    name = queryStudent(sno);
    printf("sno = %d, name = %s\n", sno, name); 
}


int main()
{
	listInit(&list);
    testQueryStudent();
    return 0;
}