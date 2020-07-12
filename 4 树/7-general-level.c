#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef void *Data;

typedef struct {
    Data *datas;
    int head;
    int rear;
} Queue;

#define QUEUE_CAPACITY 64 
void queueInit(Queue *queue)
{
    queue->datas = malloc(sizeof(Data) * QUEUE_CAPACITY);
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
    free(queue->datas);
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

void queueEnqueue(Queue *queue, Data data)
{
    assert(!queueFull(queue));
    queue->datas[queue->rear] = data;
    queue->rear = inc(queue->rear);
}

Data queueDequeue(Queue *queue)
{
    assert(!queueEmpty(queue));
    Data data = queue->datas[queue->head];
    queue->head = inc(queue->head);
    return data;
}

typedef int Elem;

typedef struct tree {
    struct tree *child;
    struct tree *sibling;
    Elem elem;
} Tree;

Tree *treeNew(Elem elem, Tree *child, Tree *sibling)
{
    Tree *tree = malloc(sizeof(Tree));
    tree->elem = elem;
    tree->child = child;
    tree->sibling = sibling;
    return tree;
}

void treeLevelVisit(Tree *root)
{
    Queue queue;Tree *current;

    queueInit(&queue);
    
	queueEnqueue(&queue,root);
	
	
	current = root;
	
	while(!queueEmpty(&queue))
	{
		queueDequeue(&queue);
		printf("%c",root->elem);
	
		while(root->child)
		{
			treeLevelVisit(root->child);
			root=root->child;
		}
	}
	
	
	//queue = {A}

	//current = A 
	//queue = {}
	//visit A
	//queue = {B C D}
	
	
	
	
	
	
	
	queueDestroy(&queue);

    printf("\n");
}

//      a
//  b   c   d
Tree *treeCreateSimple()
{
    Tree *d = treeNew('d', NULL, NULL);
    Tree *c = treeNew('c', NULL, d);
    Tree *b = treeNew('b', NULL, c);
    Tree *a = treeNew('a', b, NULL);
    return a;
}

//      a
//  b   c   d
// e f    g h i
//
// preOrder A B E F C D G H I
//            -----   -------
// posOrder E F B C G H I D A
//          -----   -------
Tree *treeCreateComplex()
{
    Tree *i = treeNew('i', NULL, NULL);
    Tree *h = treeNew('h', NULL, i);
    Tree *g = treeNew('g', NULL, h);
    Tree *d = treeNew('d', g, NULL);

    Tree *c = treeNew('c', NULL, d);

    Tree *f = treeNew('f', NULL, NULL);
    Tree *e = treeNew('e', NULL, f);
    Tree *b = treeNew('b', e, c);

    Tree *a = treeNew('a', b, NULL);
    return a;
}

int main()
{
    Tree *root = treeCreateComplex();
	treeLevelVisit(root);
    return 0;
}
