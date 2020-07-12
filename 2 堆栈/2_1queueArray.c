#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int Elem;

typedef struct {
    Elem *elems;
    int head;
    int rear;
} Queue;

#define QUEUE_CAPACITY 64 
void queueInit(Queue *queue)
{
    queue->elems = malloc(sizeof(Elem) * QUEUE_CAPACITY);
    queue->head = 0;
    queue->rear = 0;
}

static int inc(int index)
{
    return (index + 1) % QUEUE_CAPACITY;
}

static int dec(int index)
{
    return (index - 1 + QUEUE_CAPACITY) % QUEUE_CAPACITY;
}

void queueDestroy(Queue *queue)
{
    free(queue->elems);
}

int queueLength(Queue *queue)
{
    return (queue->rear - queue->head + QUEUE_CAPACITY) % QUEUE_CAPACITY;
}

int queueEmpty(Queue *queue)
{
    return queue->head == queue->rear;
}

int queueFull(Queue *queue)
{
    return queue->head == inc(queue->rear);
}

void queueVisit(Queue *queue)
{
    printf("Queue elems:");
    int i;
    for (i = queue->head; i != queue->rear; i = inc(i)) {
        Elem elem = queue->elems[i];
        printf(" %d", elem);
    }
    printf("\n");
}

Elem queueGetHead(Queue *queue)
{
    assert(!queueEmpty(queue));

    return queue->elems[queue->head];
}

Elem queueGetTail(Queue *queue)
{
    assert(!queueEmpty(queue));

    int tail = dec(queue->rear);
    return queue->elems[tail];
}

void queueEnqueue(Queue *queue, Elem elem)
{
    assert(!queueFull(queue));
    queue->elems[queue->rear] = elem;
    queue->rear = inc(queue->rear);
}

Elem queueDequeue(Queue *queue)
{
    assert(!queueEmpty(queue));
    Elem elem = queue->elems[queue->head];
    queue->head = inc(queue->head);
    return elem;
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
