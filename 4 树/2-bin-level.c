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

//====================================================================================
typedef int Elem;

typedef struct tree {
    struct tree *left;
    struct tree *right;
    Elem elem;
} Tree;

Tree *treeNew(Elem elem, Tree *left, Tree *right)
{
    Tree *tree = malloc(sizeof(Tree));
    tree->elem = elem;
    tree->left = left;
    tree->right = right;
    return tree;
}

//    a
//  b   c
// d e f g
Tree *treeExample0()
{
    Tree *d = treeNew('d', NULL, NULL);
    Tree *e = treeNew('e', NULL, NULL);
    Tree *f = treeNew('f', NULL, NULL);
    Tree *g = treeNew('g', NULL, NULL);
    Tree *b = treeNew('b', d, e);
    Tree *c = treeNew('c', f, g);
    Tree *a = treeNew('a', b, c);
    return a;
}

//    a
//  b   c
// d e   g
Tree *treeExample1()
{
    Tree *d = treeNew('d', NULL, NULL);
    Tree *e = treeNew('e', NULL, NULL);
    Tree *g = treeNew('g', NULL, NULL);
    Tree *b = treeNew('b', d, e);
    Tree *f = NULL;
    Tree *c = treeNew('c', f, g);
    Tree *a = treeNew('a', b, c);
    return a;
}

void treeLevelVisit(Tree *root)
{
	Queue *queue;
	queueInit(queue);
	Tree *current;
	current=root;
	
	queueEnqueue(queue,root);
	
	while(!queueEmpty(queue))
	{
		printf("%c",current->elem);
		
		int i;
		for(i=0;i<queueLength(queue);i++)
		{
			current=queue+i;
			queueDequeue(current);
			if(current->left)
				queueEnqueue(queue,current->left);
			if(current->right)
				queueEnqueue(queue,current->right);
	
		}
	}
	queueDestroy(queue);
}

void treeVisitTest()
{
    Tree *root = treeExample0();
    treeLevelVisit(root);
}

int main()
{
    treeVisitTest();
    return 0;
}