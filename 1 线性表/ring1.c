#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Elem;

typedef struct node {
    Elem elem;
    struct node *next;
    struct node *prev;
} Node;

Node *nodeNew(Elem elem)
{
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    node->elem = elem;
    return node;
}

void nodeDelete(Node *node)
{
    free(node);
}

void nodeLink(Node *prev, Node *me, Node *next)
{
    me->next = next;
    me->prev = prev;
    prev->next = me;
    next->prev = me;
}

void nodeUnlink(Node *node)
{
    Node *prev = node->prev;
    Node *next = node->next;
    prev->next = next;
    next->prev = prev;
}

Node *createRing(int n)
{
    Node *head = nodeNew(0);
    head->next = head;
    head->prev = head;

    int i;
    for (i = 1; i < n; i++) {
        Node *node = nodeNew(i);
        nodeLink(head->prev, node, head);
    }
    return head;
}

void visitRing(Node *head)
{
    Node *node;
    
    node = head; 
    do {
        printf("%d\n", node->elem);
        node = node->next;
    } while (node != head);
}

Node *move(Node *node, int count)
{
    int i;
    for (i = 0; i < count; i++)
        node = node->next;
    return node;
}

void joseph(int n, int m)
{
    Node *node = createRing(n);
	
    
	createRing(&list, n);
	
	int i;
	
	for(i=m-1;n != 1;i+=m-1)
	{
		i=i % n;
		printf("%d",listGetElem(&list, i));
		nodeUnlink();
		n--;
    }
	printf("%d",listGetElem(&list, 0));
	
}

int main()
{
    joseph(6, 5);
    return 0;
}
