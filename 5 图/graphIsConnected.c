#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef char Elem;

struct arc {
    struct vertex *startVertex;
    struct vertex *endVertex;
    struct arc *nextArc;
};

struct vertex {
    Elem elem;
    int visited;
    struct arc *firstArc;
};

#define MAX_VERTEXS 32
struct graph {
    int vertexNumber;
    struct vertex vertexs[MAX_VERTEXS];
};

typedef struct arc Arc;
typedef struct vertex Vertex;
typedef struct graph Graph;

void vertexInit(Vertex *vertex, Elem elem)
{
    vertex->elem = elem;
    vertex->visited = 0;
    vertex->firstArc = NULL;
}

void vertexVisit(Vertex *vertex)
{
    if (!vertex->visited) {
        printf("%c ", vertex->elem); 
        vertex->visited = 1;
    }
}

Arc *arcNew(Vertex *startVertex, Vertex *endVertex)
{
    Arc *arc = malloc(sizeof(Arc));
    arc->startVertex = startVertex;
    arc->endVertex = endVertex;
    arc->nextArc = NULL;
    return arc;
}

void graphInit(Graph *graph)
{
    graph->vertexNumber = 0;
}

Vertex *graphAddVertex(Graph *graph, Elem elem)
{
    Vertex *vertex = &graph->vertexs[graph->vertexNumber];
    vertexInit(vertex, elem);
    graph->vertexNumber++;
    return vertex;
}

Vertex *graphLocateVertex(Graph *graph, Elem elem)
{
    int i;

    for (i = 0; i < graph->vertexNumber; i++) {
        Vertex *vertex = &graph->vertexs[i];
        if (vertex->elem == elem)
            return vertex;
    }

    return NULL;
}

void graphAddArc(Graph *graph, Vertex *startVertex, Vertex *endVertex)
{
    Arc *arcSE = arcNew(startVertex, endVertex);
    arcSE->nextArc = startVertex->firstArc;
    startVertex->firstArc = arcSE;

    Arc *arcES = arcNew(endVertex, startVertex);
    arcES->nextArc = endVertex->firstArc;
    endVertex->firstArc = arcES;
}

void graphDump(Graph *graph)
{
    int i;
    for (i = 0; i < graph->vertexNumber; i++) {
        Vertex *startVertex = graph->vertexs + i;
        printf("%c:\n", startVertex->elem);

        Arc *arc;
        for (arc = startVertex->firstArc; arc != NULL; arc = arc->nextArc) {
            assert(startVertex == arc->startVertex);
            printf("  %c -> %c\n", arc->startVertex->elem, arc->endVertex->elem);
        }
    }
}

//   a
//  b c
// d e f
void graphExample0(Graph *graph)
{
    graphInit(graph);

    Vertex *a = graphAddVertex(graph, 'a');
    Vertex *b = graphAddVertex(graph, 'b');
    Vertex *c = graphAddVertex(graph, 'c');
    Vertex *d = graphAddVertex(graph, 'd');
    Vertex *e = graphAddVertex(graph, 'e');
    Vertex *f = graphAddVertex(graph, 'f');

    graphAddArc(graph, a, c);
    graphAddArc(graph, a, b);

    graphAddArc(graph, b, e);
    graphAddArc(graph, b, d);

    graphAddArc(graph, c, f);
    graphAddArc(graph, c, e);
}

//   a
//  b c
//
// d e f
void graphExample1(Graph *graph)
{
    graphInit(graph);

    Vertex *a = graphAddVertex(graph, 'a');
    Vertex *b = graphAddVertex(graph, 'b');
    Vertex *c = graphAddVertex(graph, 'c');

    graphAddArc(graph, a, c);
    graphAddArc(graph, a, b);

    Vertex *d = graphAddVertex(graph, 'd');
    Vertex *e = graphAddVertex(graph, 'e');
    Vertex *f = graphAddVertex(graph, 'f');

    graphAddArc(graph, e, d);
    graphAddArc(graph, e, f);
}

void graphDumpTest()
{
    Graph graph;

    graphExample0(&graph);
    graphDump(&graph);
}

// 基于 graphDFS 实现
int graphDFSV(Vertex *root)
{
	int count=0;
	root->visited = 1;
	count =count + 1;

	Arc *arc = root->firstArc;
	while(arc)
	{
		if(!arc->endVertex->visited)
		{
			count = count +graphDFSV(arc->endVertex);
		}
		
		arc = arc->nextArc;
	}
	return count;
}

int graphIsConnected(Graph *graph)
{
    Vertex *root = &graph->vertexs[0];
	
	int num = graph->vertexNumber;
	int count = graphDFSV(root);
	
	return num==count;
}

void graphIsConnectedTest()
{
    int isConnected;

    Graph graph0;
    graphExample0(&graph0);
    isConnected = graphIsConnected(&graph0);
    printf("isConnected = %d\n", isConnected);

    Graph graph1;
    graphExample1(&graph1);
    isConnected = graphIsConnected(&graph1);
    printf("isConnected = %d\n", isConnected);
}

int main()
{
    graphIsConnectedTest();
    return 0;
}
