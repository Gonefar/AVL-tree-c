#include "head.h"
#include "func.c"

int main()
{
    int choice, value, flag = 0;
    avlTree *tree = NULL;

    showInfo();
    tree = genInitAVLTree();

    while(1)
    {
        printf("Please input your choice:\n");
        scanf("%d", &choice);
        switch( choice )
        {
            case INSERT:
                printf("Inserting:\n");
                printf("Please input your node value:\n");
                scanf("%d", &value);
                //insertByValue( tree, value);
                avlInsert( tree, value);
                showAVLTree( tree );
                break;
            case DELETE:
                printf("Deleting:\n");
                printf("Please input your node value:\n");
                scanf("%d", &value);
                deleteByValue( tree, value);
                showAVLTree( tree );
                break;
            case FIND:
                printf("Finding:\n");
                printf("Please input your node value:\n");
                scanf("%d", &value);
                findNodeByValue(tree, value);
                showAVLTree( tree );
                break;
            case SHOW:
                showAVLTree(tree);
                break;
            case EXIT:
                printf("Exiting...\n");
                return 0;
            default:
                printf("No this choice!\n");
                break;
        }

        flag++;
        if( flag % 10 == 9 )
        {
            showInfo();
        }
    }
}

