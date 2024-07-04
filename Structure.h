#ifndef Structure_h
#define Structure_h

typedef struct Array
{
    int viSizeOfArray;
    void* * aoArray;
}Array;

Array * new_Array(int viSizeOfType, int viSizeOfArray)
{
    Array * ptrArray = malloc(sizeof(Array));
    ptrArray->viSizeOfArray = viSizeOfArray;
    ptrArray->aoArray = malloc(viSizeOfType * viSizeOfArray);

    return ptrArray;

}

void delete_Array(Array * ptrArray)
{
    free(ptrArray->aoArray);
    free(ptrArray);
    ptrArray = 0;
}

//=======================================================================================

typedef struct NodeOfList
{
    void* voElement;
    void* * ptrNextNode;
}NodeOfList;

typedef struct List
{
    int viCount;
    NodeOfList * ptrRootNode;
    NodeOfList * ptrLastNode;

    void (*fAdd)(void* * ptrList, void* voElement);
}List;

void member_of_List_fAdd(List * ptrList, void* voElement)
{
    if(ptrList->ptrRootNode == 0)
    {
        ptrList->ptrRootNode = malloc(sizeof(NodeOfList));
        ptrList->ptrRootNode->ptrNextNode = 0;
        ptrList->ptrLastNode = ptrList->ptrRootNode;
    }

    NodeOfList * ptrNewNode = malloc(sizeof(NodeOfList));
    ptrNewNode->ptrNextNode = 0;
    ptrNewNode->voElement = voElement;
    ptrList->viCount++;

    ptrList->ptrLastNode->ptrNextNode = ptrNewNode;
    ptrList->ptrLastNode = ptrList->ptrLastNode->ptrNextNode;
}

List * new_List()
{
    List * ptrList = malloc(sizeof(List));

    ptrList->viCount = 0;
    ptrList->ptrRootNode = 0;
    ptrList->ptrLastNode = 0;
    ptrList->fAdd = member_of_List_fAdd;
    return ptrList;
}

void delete_List(List * ptrList)
{
    ptrList->ptrLastNode = ptrList->ptrRootNode;

    NodeOfList * ptrRefNode = 0;
    if(ptrList->ptrLastNode->ptrNextNode != 0)
    {
        ptrRefNode = ptrList->ptrLastNode;
        ptrList->ptrLastNode = ptrRefNode->ptrNextNode;
        free(ptrRefNode);
    }

    free(ptrList->ptrLastNode);

    free(ptrList);
    ptrList = 0;
}

#endif
