#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N 50

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

List StudentTable[N];

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

// 使用 hash 技术
void addStudent(int sno, char *name)
{
    int Index = sno / 10;
	List *list = StudentTable + Index;
	
	listInsertElem(list, list->length , sno, name);
	
	printf("addStudent %d %s\n", sno, name);
}

// 使用 hash 技术
char *queryStudent(int sno)
{
	int Index = sno / 10;
	List *list = StudentTable + Index;
	
	Node *node;

    for (node = list->head; node != NULL; node = node->next) 
        if(node->sno==sno)
			return node->name;
	
    return NULL;
}

// 创建 26 个学生
// - 学号为 1，姓名为 "a"
// - 学号为 2，姓名为 "b"
// - ...
// - 学号为 26，姓名为 "z"
void createStudents()
{
    int sno;
    char name[2];
    char ch = 'a';

    for (sno = 1; sno <= 26; sno++) {
        name[0] = ch;
        name[1] = 0;
        ch++;
        addStudent(sno, name);
    }
}

void testQueryStudent()
{
    int sno;
    char *name;

    createStudents();

    sno = 3;
    name = queryStudent(sno);
    printf("sno = %d, name = %s\n", sno, name); 

    sno = 16;
    name = queryStudent(sno);
    printf("sno = %d, name = %s\n", sno, name); 
}

int main()
{
    testQueryStudent();
    return 0;
}
