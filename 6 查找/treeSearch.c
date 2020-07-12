#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree {
    int sno;
    char name[8];
    struct tree *left;
    struct tree *right;
} Tree;

void treeDump(Tree *tree)
{
    printf("sno = %d, name = %s\n", tree->sno, tree->name);
}

Tree *treeNew(int sno, char *name, Tree *left, Tree *right)
{
    Tree *tree = malloc(sizeof(Tree));
    tree->sno = sno;
    strcpy(tree->name, name);
    tree->left = left;
    tree->right = right;
    return tree;
}

//     4
//  2     6
// 1 3   5 7
Tree *createTree()
{
    Tree *a = treeNew(1, "A", NULL, NULL);
    Tree *c = treeNew(3, "C", NULL, NULL);
    Tree *b = treeNew(2, "B", a, c);

    Tree *f = treeNew(5, "E", NULL, NULL);
    Tree *g = treeNew(7, "G", NULL, NULL);
    Tree *e = treeNew(6, "F", f, g);

    Tree *d = treeNew(4, "D", b, e);
    return d;
}

void treeVisit(Tree *tree)
{
    if (tree != NULL) {
        treeVisit(tree->left);
        treeDump(tree);
        treeVisit(tree->right);
    }
}

// 使用二分查找
char *treeSearch(Tree *root, int sno)
{
    if(!root)
		return NULL;
	
	
	if(sno == root->sno)
		return root->name;
	
	else if(sno > root->sno)
		return treeSearch(root->right,sno);
	
	else if(sno < root->sno)
		return treeSearch(root->left,sno);
}

void treeSearchTest()
{
    Tree *root = createTree();
    for (int sno = 1; sno <= 7; sno++) {
        char *name = treeSearch(root, sno);
        printf("sno = %d, name = %s\n", sno, name);
    }
}

void treeVisitTest()
{
    Tree *root = createTree();
    treeVisit(root);
}

int main()
{
    treeSearchTest();
    return 0;
}
