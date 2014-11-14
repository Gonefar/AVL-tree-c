void showInfo(void)
{
    printf("----Welcom to use AVL tree----\n");
    printf("----1: Insert             ----\n");
    printf("----2: Delete             ----\n");
    printf("----3: Find node          ----\n");
    printf("----4: show tree          ----\n");
    printf("----5: Exit               ----\n");
    printf("---->>>>>>>               ----\n");
}

int updateNodeInfo(avlNode *startNode)
{
    if( startNode == NULL )
    {
        return 0;
    }

    if( startNode->left != NULL )
    {
        startNode->left->depth = startNode->depth + 1;
        startNode->left->colIndex = startNode->colIndex * 2 - 1;
        updateNodeInfo( startNode->left );
    }

    if(startNode->right != NULL)
    {
        startNode->right->depth = startNode->depth + 1;
        startNode->right->colIndex = startNode->colIndex * 2;
        updateNodeInfo( startNode->right );
    }

    return 0;
}

int setRootNodeInfo(avlNode *rootNode)
{
    if(rootNode == NULL)
    {
        printf("%s %d:paramter is negative!\n", __FILE__, __LINE__);
        return 1;
    }

    rootNode->depth = 0;
    rootNode->colIndex = 1;

    return 0;
}

avlTree *genInitAVLTree(void)
{
    avlTree *tree = (avlTree *)malloc(sizeof(avlTree));

    if( tree != NULL)
    {
        tree->height = 0;
        tree->depth  = 0;
        tree->freq     = 0;
        tree->size     = 0;
        tree->root    = NULL;
    }
    else
    {
        printf("Create tree error!\n");
    }

    return tree;
   
}

avlNode *createNode(void)
{
    avlNode *node = (avlNode *)malloc(sizeof(avlNode));

    if( node != NULL)
    {
        node->freq    = 0;
        node->depth  = 0;
        node->height = 0;
        node->colIndex = 0;
        node->left     = NULL;
        node->right   = NULL;
        node->parent = NULL;
        node->value = -1;
    }
    else
    {
        printf("Create node error\n");
    }

    return node;
}

void printBlank(int blankNum)
{
    int i = 0;

    if( blankNum < 0 )
    {
        printf("%s %d:paramter is negative!\n", __FILE__, __LINE__);
        return;
    }
    
    for( i = 0; i < blankNum; i++ )
    {
        printf(" ");
    }

    return;
}

int normalTraverse(avlNode *startNode)
{
    if( startNode == NULL )
    {
        return 0;
    }

    printf("<%d", startNode->value);
    if(startNode->parent != NULL)
    {
        printf(" %d ", startNode->parent->value);
    }
    else
    {
        printf(" NU " );
    }

    if( startNode->parent != NULL && startNode->parent->parent != NULL )
    {
        printf("%d", startNode->parent->parent->value);
    }
    else
    {
        printf("NU" );
    }
    printf("(%d %d)>", startNode->depth, startNode->colIndex);
    normalTraverse(startNode->left);
    normalTraverse(startNode->right);

    return 0;
}

int traverseTreeAsDepthOutput(avlNode *startNode, int depth, int maxDepth, int *outputNum)
{
    int blankNum = 0;
    
    if( startNode == NULL )
    {
        return 0;
    }

    if(depth > maxDepth)
    {
        printf("depth(%d): out of max depth(%d)\n", depth, maxDepth);
        return 1;
    }
    
    if( startNode->depth == depth )
    {
        if( startNode->colIndex == 1 )
        {
            blankNum = PRINTWIDTH * ( (int)pow(2, maxDepth-depth) - 1 ) / 2;
        }
        else
        {
            blankNum = PRINTWIDTH * ( (int)pow(2, maxDepth-depth) - 1 );
        }

        if( startNode->colIndex != 1 && 
            outputNum[depth] != ( ( startNode->colIndex - 1 ) * ( PRINTWIDTH + blankNum ) - blankNum / 2 ) )
        {
            //printf("output char num:%d<<<", outputNum[depth]);
            printBlank( ( startNode->colIndex - 1 ) * ( PRINTWIDTH + blankNum ) - blankNum / 2 - outputNum[depth] );
            outputNum[depth] =  ( startNode->colIndex - 1 ) * ( PRINTWIDTH + blankNum ) - blankNum / 2;
        }
        
        printBlank( blankNum );
        printf("%-4d", startNode->value);
        outputNum[depth] += (blankNum + PRINTWIDTH);
    }
    
    traverseTreeAsDepthOutput( startNode->left, depth, maxDepth, outputNum);
    traverseTreeAsDepthOutput( startNode->right, depth, maxDepth, outputNum);
    
}


/* depth: the path length from root to node */
int getDepthOfNode( avlNode *node )
{
    int depth = 0;
    avlNode *temp = node;

    if( node == NULL )
    {
        printf("%s %d:Node is NULL!\n", __FILE__, __LINE__);
        return 1;
    }
    
    while( temp->parent != NULL )
    {
        depth++;
        temp = temp->parent;
    }

    return depth;
}

/* height: the largest path length from node to leaf */
int getHeightOfNode(avlNode *node)
{
    int height = 0;

    if( node == NULL )
    {
        return 0;
    }
    //printf("get height process\n");
    height = MAX(1+getHeightOfNode(node->left), 1+getHeightOfNode(node->right));
    
    return height;
}

int insertByNode(avlTree *tree, avlNode *node)
{
    int insertFlag = 0;
    avlNode *temp = tree->root;
    avlNode *latestParent = NULL;

    if( node == NULL || tree == NULL)
    {
        printf("%s %d:NULL pointer!\n", __FILE__, __LINE__);
        return 1;
    }
    
    while(1)
    {
        if( tree->root == NULL )
        {
            node->colIndex = 1;
            node->depth = 0;
            tree->root = node;
            printf("root:%p, node:%p\n", tree->root, node);
            break;
        }
        
        if( node->value > temp->value )
        {
            latestParent = temp;
            temp = temp->right;
        }
        else if( node->value < temp->value )
        {
            latestParent = temp;
            temp = temp->left;
            insertFlag = 1;   // 1:left 0:right
        }
        else
        {
            temp->freq++;
            break;
        }

        if( temp == NULL )
        {
            printf("Insert success!(value:%d)\n", node->value);
            node->parent = latestParent;
            node->depth = latestParent->depth+1;

            if( insertFlag == 1)
            {
                node->colIndex = 2 * latestParent->colIndex - 1;
                latestParent->left = node;
            }
            else
            {
                node->colIndex = 2 * latestParent->colIndex;
                latestParent->right = node;
            }
            
            break;
        }
        
        insertFlag = 0;
    }

    tree->size++;
    
    return 0;
}

int insertByValue(avlTree *tree, int value)
{
    avlNode *newNode = createNode();

    newNode->value = value;
    insertByNode( tree, newNode);

    return 0;
    
}

avlNode *findNodeByValue(avlTree *tree, int value)
{
    avlNode *temp = tree->root;
    
    while(1)
    {
        if( value > temp->value )
        {
            //printf("Find to right:cur:%d input:%d\n", temp->value, value);
            temp = temp->right;
        }
        else if( value < temp->value )
        {
            //printf("Find to right:cur:%d input:%d\n", temp->value, value);
            temp = temp->left;
        }
        else
        {
            //printf("Find to right:cur:%d input:%d\n", temp->value, value);
            break;   //find the node
        }

        if( temp == NULL )
        {
            printf("No this node(value:%d) in the AVL-tree!\n", value);
        }

    } 

    printf("Find it!col:%d, depth:%d value:%d\n", temp->colIndex, temp->depth, temp->value);
    return temp;
}

int singleRotate(avlTree *tree, avlNode *startNode)
{  
    avlNode * temp = NULL, *temppp = NULL;
    
    if( startNode == NULL || startNode->parent == NULL
        || startNode->parent->parent == NULL ) //three nodes to be totated 
    {
        printf("%s %d:Node is NULL!\n", __FILE__, __LINE__);
        return 1;
    }
      
    temp = startNode->parent->parent->parent;
    temppp = startNode->parent->parent;
    
    if( startNode->parent->parent->parent == NULL)
    {
        tree->root = startNode->parent;
        printf("root node changed:%p<<<<\n", tree->root);
    }
    else
    {
         if( startNode->parent->left == startNode ) 
         {
            startNode->parent->parent->parent->left = startNode->parent;
         }
         else
         {
            startNode->parent->parent->parent->right = startNode->parent;
         }
    }     

    if( startNode->parent->left == startNode ) //left-left mode
    {     
        printf("left-left mode\n");
        startNode->parent->parent->left = startNode->parent->right;
        if( startNode->parent->right != NULL )
        {
            startNode->parent->right->parent = startNode->parent->parent;
        }
        startNode->parent->right = startNode->parent->parent;
    }
    else                                                         //right-right mode
    {
        printf("right-right mode\n"); 
        startNode->parent->parent->right = startNode->parent->left;
        if( startNode->parent->left != NULL )
        {
            startNode->parent->left->parent = startNode->parent->parent;
        }
        startNode->parent->left = startNode->parent->parent;                 
    }

    //startNode->parent->parent->parent = startNode->parent;
    startNode->parent->parent = temp;  
    temppp->parent = startNode->parent;

    if( temp != NULL )
    {
        printf(">>>>single start value:%d start node value:%d start-p:%d, start-p-p:%d\n", temp->value,
            startNode->value, startNode->parent->value, startNode->parent->parent->value);
        updateNodeInfo( temp );
    }
    else
    {
        setRootNodeInfo( tree->root );
        updateNodeInfo( tree->root );
    }
        
    return 0;    
}

int doubleRotate(avlTree *tree, avlNode *startNode)
{
    avlNode *temp = NULL, *temppp = NULL;
    
    if( startNode == NULL || startNode->parent == NULL
        || startNode->parent->parent == NULL ) //three nodes to be totated 
    {
        printf("%s %d:Node is NULL!\n", __FILE__, __LINE__);
        return 1;
    }

    temp = startNode->parent->parent->parent;
    temppp = startNode->parent->parent;
 
    if( startNode->parent->parent->parent == NULL)
    {
        tree->root = startNode;
    }
    else
    {         
         if( startNode->parent->left == startNode ) 
         {
            startNode->parent->parent->parent->right = startNode;
         }
         else
         {
            startNode->parent->parent->parent->left = startNode;
         }         
    }
    
    if( startNode->parent->left == startNode ) //right-left mode
    {
        printf("%d:right-left mode\n", __LINE__);
        startNode->parent->parent->right = startNode->left;
        if( startNode->left != NULL)
        {
            startNode->left->parent = startNode->parent->parent;
        }
        
        startNode->parent->left = startNode->right;
        if(startNode->right != NULL)
        {
            startNode->right->parent = startNode->parent;
        }
        
        startNode->right = startNode->parent;
        startNode->left = startNode->parent->parent;
    }
    else                                                         //left-right mode
    {
        printf("%d:left-right mode\n", __LINE__);
        startNode->parent->parent->left= startNode->left;
        startNode->parent->right = startNode->right;
        startNode->right = startNode->parent;
        startNode->left = startNode->parent->parent;           
    }        

    startNode->parent->parent->parent= startNode;
    startNode->parent->parent= startNode;
    startNode->parent = temp;
    //temppp->parent = startNode;
    //temppp = startNode;

    if( temp != NULL )
    {
        printf(">>double: start value:%d\n", temp->value);
        updateNodeInfo( temp );
    }
    else
    {
        setRootNodeInfo( tree->root );
        updateNodeInfo( tree->root );
    }
    
    return 0;    
    
}
int rotateProcess(avlTree *tree, avlNode *insertedNode)
{
    int leftHeight = 0, rightHeight = 0, recurTimes = 0, heightDiff = 0;
    avlNode *temp = insertedNode, *recordNode1 = NULL, *recordNode2 = NULL, *recordNode3 = NULL;
    
    if( tree == NULL || insertedNode == NULL)
    {
        printf("%s %d:NULL pointer!\n", __FILE__, __LINE__);
        return -1;
    }

    while( temp != NULL )
    {
        printf("%d->", temp->value);
        leftHeight = getHeightOfNode(temp->left);
        rightHeight = getHeightOfNode(temp->right);
        heightDiff = MAX(leftHeight, rightHeight) - MIN(leftHeight, rightHeight);
        
        if( leftHeight - rightHeight > 1 && recurTimes > 2 )
        {
            printf("%d:left-right mode\n", __LINE__);
            if( recordNode3 == recordNode3->parent->left )
            {
                singleRotate(tree, recordNode3);
            }
            else
            {
                doubleRotate(tree, recordNode3); 
            }
            return 0;
        }
        else if( leftHeight - rightHeight > 1 && recurTimes == 2 )
        {
            printf("%d:left-right mode\n", __LINE__);
            if( insertedNode == insertedNode->parent->left )
            {
                singleRotate( tree, insertedNode);
            }
            else
            {
                doubleRotate( tree, insertedNode);
            }
            
            return 0;
        }
        else if( rightHeight - leftHeight > 1 && recurTimes > 2 )
        {
            printf("%d:right-left mode\n", __LINE__);
            if( recordNode3 == recordNode3->parent->right )
            {
                singleRotate(tree, recordNode3);
            }
            else
            {
                printf("%d:>>>>double: start node value:%d start-p:%d, start-p-p:%d\n", __LINE__,
                recordNode3->value, recordNode3->parent->value, recordNode3->parent->parent->value);                
                doubleRotate(tree, recordNode3); 
            }
            return 0;
        }
        else if( rightHeight - leftHeight > 1 && recurTimes == 2 )
        {
            printf("%d:right-left mode\n", __LINE__);
            if( insertedNode == insertedNode->parent->right )
            {
                singleRotate( tree, insertedNode);
            }
            else
            {
                doubleRotate( tree, insertedNode);
            }
            
            return 0;
        }
        else
        {
        }
        
        temp = temp->parent;
        recurTimes++;
	
        recordNode3 = recordNode2;
        recordNode2 = recordNode1;
        recordNode1 = temp;
    
    }

    printf("No need to rotate.\n");
    return 0;
}

int avlInsert(avlTree *tree, int value)
{
    avlNode *node = NULL;
    int rotateFlag = -1;

    insertByValue( tree, value);
    showAVLTree( tree);
    node = findNodeByValue( tree, value);
    rotateProcess( tree, node );

    return 0;    
}

avlNode *getLeftmostNode(avlNode *startNode)
{
    avlNode *temp = startNode;
    
    if( temp == NULL )
    {
        printf("%s %d:Node is NULL!\n", __FILE__, __LINE__);
        return NULL;
    }

    while( temp->left != NULL )
    {
        temp = temp->left;
    }

    return temp;
    
}

avlNode *getRightmostNode(avlNode *startNode)
{
    avlNode *temp = startNode;
    
    if( temp == NULL )
    {
        printf("%s %d:Node is NULL!\n", __FILE__, __LINE__);
        return NULL;
    }

    while( temp->right != NULL )
    {
        temp = temp->right;
    }

    return temp;
    
}

int deleteByValue(avlTree *tree, int value)
{
    avlNode *temp = NULL, *leftmostNode = NULL, *rightmostNode = NULL;

    if( tree == NULL)
    {
        printf("%s %d:NULL pointer!\n", __FILE__, __LINE__);
        return 1;
    }

    temp = findNodeByValue( tree, value );

    /*delete process*/
    if( temp != NULL )
    {
        if( temp == tree->root )
        {
            printf("Deleting when tree size is 1!\n");
        }
        else if( temp == temp->parent->left )
        {
            leftmostNode = getLeftmostNode(temp);
            temp->parent->left = temp->right;
            leftmostNode->left = temp->left;        
        }
        else
        {
            rightmostNode = getRightmostNode(temp);
            temp->parent->right = temp->right;
            rightmostNode->left = temp->left;
        }

        free(temp);
        temp = NULL;
    }

    tree->size--;
    
    return 0;
}

int showAVLTree(avlTree *tree)
{
    int i = 0;
    int outputNum[10] = {0};
    
    if( tree == NULL )
    {
        printf("%s %d:NULL pointer\n", __FILE__, __LINE__);
        return 1;
    }
    normalTraverse(tree->root);
    printf("\n");
#if 1
    tree->height = getHeightOfNode(tree->root); //as define, true height of tree is tree->height - 1

    printf("tree info:size-%d add-%p height:%d\n", tree->size, tree->root, tree->height);

    for( i = 0; i < tree->height; i++ )
    {
        traverseTreeAsDepthOutput(tree->root, i, tree->height - 1, outputNum);
        printf("\n");
    }
#else 
    normalTraverse(tree->root);
#endif
    return 0;
}


