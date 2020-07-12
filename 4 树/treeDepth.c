#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

int treeDepth(Tree *tree)
{
	int a,b;
	if(tree!=NULL)
	{
		a = treeDepth(tree->left);
		b = treeDepth(tree->right);
		return (a>b?:a,b)+1;
	}
	else return 0;
}

void treeDepthTest()
{
    Tree *tree = treeExample1();
    int depth = treeDepth(tree);
    printf("depth = %d\n", depth);
}

int main()
{
    treeDepthTest();
    return 0;
}