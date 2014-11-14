#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#define INSERT 1
#define DELETE 2
#define FIND     3
#define SHOW   4
#define EXIT     5
#define PRINTWIDTH 4
#define NO_ROTATE_FLAG         0
#define SINGER_ROTATE_IFLAG  1
#define SINGER_ROTATE_IIFLAG  2
#define DOUBLE_ROTATE_IFLAG  3
#define DOUBLE_ROTATE_IIFLAG  4


#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

typedef struct _avlNode
{
    int value;
    int height;
    int depth;
    int freq;
    int colIndex;
    struct _avlNode *left;
    struct _avlNode *right;
    struct _avlNode *parent;
}avlNode;

typedef struct _avlTree
{
    int height;
    int depth;
    int freq;
    int size;
    avlNode *root;
}avlTree;

avlTree *genInitAVLTree(void);



#endif


