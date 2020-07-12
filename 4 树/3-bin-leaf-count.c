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

int treeLeafCount(Tree *tree)
{
	int count=0;
	if(tree!=NULL)
	{

		if(tree->left==NULL&&tree->right==NULL )
		{
			count++;
		}

		count=count+treeLeafCount(tree->left);
		
		count=count+treeLeafCount(tree->right);
		
	}
	return count;
}

void treeLeafCountTest()
{
    Tree *tree = treeExample1();
    int count = treeLeafCount(tree);
    printf("count = %d\n", count);
}

int main()
{
    treeLeafCountTest();
    return 0;
}