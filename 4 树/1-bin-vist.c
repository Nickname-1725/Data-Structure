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

void treePreOrderVisit(Tree *tree)
{
	if(tree!=NULL)
	{

	printf("%c",tree->elem);
	treePreOrderVisit(tree->left);
	treePreOrderVisit(tree->right);
	}
	
}

void treeInOrderVisit(Tree *tree)
{
	if(tree!=NULL)
	{
	treePreOrderVisit(tree->left);		
	printf("%c",tree->elem);
	treePreOrderVisit(tree->right);
	
	}
}

void treePostOrderVisit(Tree *tree)
{
	if(tree!=NULL)
	{

	treePreOrderVisit(tree->left);
	treePreOrderVisit(tree->right);
	printf("%c",tree->elem);
	}
}

void treeVisitTest()
{
    Tree *root = treeExample0();

    treePreOrderVisit(root);
    printf("\n");

    treeInOrderVisit(root);
    printf("\n");

    treePostOrderVisit(root);
    printf("\n");
}

int main()
{
    treeVisitTest();
    return 0;
}