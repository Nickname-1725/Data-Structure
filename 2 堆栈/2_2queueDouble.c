#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int Elem;

typedef struct node {
    Elem elem;
    struct node *next;
    struct node *prev;
} Node;

typedef struct {
    Node dummy;
    int length;
} Queue;

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

void queueInit(Queue *queue)
{
    Node *dummy = &queue->dummy;

    queue->length = 0;
    dummy->next = dummy;
    dummy->prev = dummy;
}

void queueDestroy(Queue *queue)
{
    Node *dummy = &queue->dummy;

    while (dummy->next != dummy) {
        Node *node = dummy->next;
        nodeUnlink(node);
        nodeDelete(node);
        queue->length--;
    }
}

int queueLength(Queue *queue)
{
    return queue->length;
}

int queueEmpty(Queue *queue)
{
    return queue->length == 0;
}

void queueVisit(Queue *queue)
{
    Node *node;
    Node *dummy = &queue->dummy;

    printf("Queue elems:");
    for (node = dummy->next; node != dummy; node = node->next) {
        printf(" %d", node->elem);
    }
    printf("\n");
}

Elem queueGetHead(Queue *queue)
{
    assert(!queueEmpty(queue));

    Node *head = queue->dummy.next;
    return head->elem;
}

Elem queueGetTail(Queue *queue)
{
    assert(!queueEmpty(queue));

    Node *tail = queue->dummy.prev;
    return tail->elem;
}

void queueEnqueue(Queue *queue, Elem elem)
{
	Node *p=(queue->dummy).prev;
	Node *n=&(queue->dummy);
	Node *node=nodeNew(elem);
	
	nodeLink(p, node,n);
	
	queue->length++;
}

Elem queueDequeue(Queue *queue)
{
	;
	queue->length--;
}

void testQueue()
{
    Queue queue;

    queueInit(&queue);
    int i;
    for (i = 0; i < 8; i++)
        queueEnqueue(&queue, i);
    queueVisit(&queue);

    printf("Queue elems:");
    while (!queueEmpty(&queue)) {
        Elem elem = queueDequeue(&queue);
        printf(" %d", elem);
    }
    printf("\n");
    queueDestroy(&queue);
}

int main()
{
    testQueue();
    return 0;
}

