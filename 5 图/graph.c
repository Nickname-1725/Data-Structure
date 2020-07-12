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
    vertex->firstArc = NULL;
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
    Arc *arc = arcNew(startVertex, endVertex);
    arc->nextArc = startVertex->firstArc;
    startVertex->firstArc = arc;
}

void graphDump(Graph *graph)
{
	int i;

    for (i = 0; i < graph->vertexNumber; i++)
	{
        Vertex *vertex = &graph->vertexs[i];
		
		
		Arc *a=vertex->firstArc;
		printf("%c",vertex->elem);
		while(a)
		{
			Elem e= a->endVertex->elem;
			printf("->%c",e);
			a=a->nextArc;
		}
		printf("\n");
    }
	

}

//  a 
// b c
//  d
void graphExample0(Graph *graph)
{
    graphInit(graph);

    Vertex *a = graphAddVertex(graph, 'a');
    Vertex *b = graphAddVertex(graph, 'b');
    Vertex *c = graphAddVertex(graph, 'c');
    Vertex *d = graphAddVertex(graph, 'd');

    graphAddArc(graph, a, c);
    graphAddArc(graph, a, b);
    graphAddArc(graph, b, d);
    graphAddArc(graph, c, d);
}

//   a
//  b c
// d e f
void graphExample1(Graph *graph)
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

void graphDumpTest()
{
    Graph graph;

    graphExample0(&graph);
    graphDump(&graph);
}

int main()
{
    graphDumpTest();
    return 0;
}
