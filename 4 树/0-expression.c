#include <stdio.h>
#include <stdlib.h>

struct tree {
    int data;
    struct tree *left;
    struct tree *right;
};

struct tree *treeNew(int data, struct tree *left, struct tree *right)
{
    struct tree *tree = malloc(sizeof(struct tree));
    tree->data = data;
    tree->left = left;
    tree->right = right;
    return tree;
}

int treeIsLeaf(struct tree *tree)
{
    return tree->left == NULL && tree->right == NULL;
}

int treeToInt(struct tree *root)
{
    int s;
	if(treeIsLeaf(root))
	{
		return root->data;
	}
	
	else 
	{
		if(root ->data=='+')
		{
			s=treeToInt(root->left) + treeToInt(root->right);
		}
	
		if(root ->data=='*')
		{
			s=treeToInt(root->left) * treeToInt(root->right);
		}
		return s;
	}
}

// 1+2

//  +
// 1 2
void testSimple()
{
    struct tree *left = treeNew(1, NULL, NULL);
    struct tree *right = treeNew(2, NULL, NULL);
    struct tree *root = treeNew('+', left, right);
    printf("%d\n", treeToInt(root));
}

// 1+2*3
//
//  +
// 1 *
//  2 3
void testComplex()
{
    struct tree *n1 = treeNew(1, NULL, NULL);
    struct tree *n2 = treeNew(2, NULL, NULL);
    struct tree *n3 = treeNew(3, NULL, NULL);

    struct tree *mul = treeNew('*', n2, n3);
    struct tree *add = treeNew('+', n1, mul);

    printf("%d\n", treeToInt(add));
}

// "1+2*3"
// stringToArray
// [1,+,2,*,3]
// arrayToTree
// + 
// treeToInt
int main()
{
    testComplex();
    return 0;
}