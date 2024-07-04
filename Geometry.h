#ifndef Geometry_h
#define Geometry_h

#include <stdio.h>
#include <stdlib.h>

//Direction
#define diTop 0
#define diRight 1
#define diBottom 2
#define diLeft 3
#define diCenter 4

typedef struct Point
{
    int viPosX;
    int viPosY;
}Point;

Point * new_Point(int viPosX, int viPosY)
{
    Point * ptrPoint = malloc(sizeof(Point));

    ptrPoint->viPosX = viPosX;
    ptrPoint->viPosY = viPosY;

    return ptrPoint;
}

void delete_Point(Point * ptrPoint)
{
    free(ptrPoint);
    ptrPoint = 0;
}

//--------------------------------------------------------------------------------

void fDrawSymbol(int ** aaiMatrix, char vcSymbol, Point * ptrPosition)
{
    aaiMatrix[ptrPosition->viPosY][ptrPosition->viPosX] = vcSymbol;
}

//--------------------------------------------------------------------------------

void fDrawHorizontalLine(int ** aaiMatrix, Point * ptrMinPoint, Point * ptrMaxPoint)
{
    int i = 0;
    for(i = ptrMinPoint->viPosX; i <= ptrMaxPoint->viPosX; i++)
    {
        aaiMatrix[ptrMinPoint->viPosY][i] = '-';
    }
}

//--------------------------------------------------------------------------------

void fDrawVerticalLine(int ** aaiMatrix, Point * ptrMinPoint, Point * ptrMaxPoint)
{
    int i = 0;
    for(i = ptrMinPoint->viPosY; i <= ptrMaxPoint->viPosY; i++)
    {
        aaiMatrix[i][ptrMinPoint->viPosX] = '|';
    }
}

//--------------------------------------------------------------------------------

void fDrawRectangle(int ** aaiMatrix, Point * ptrMinPoint, Point * ptrMaxPoint)
{
    Point * ptrLineMinPoint = new_Point(0, 0);
    Point * ptrLineMaxPoint = new_Point(0, 0);

    ptrLineMinPoint->viPosX = ptrMinPoint->viPosX;
    ptrLineMinPoint->viPosY = ptrMinPoint->viPosY;
    ptrLineMaxPoint->viPosX = ptrMaxPoint->viPosX;
    ptrLineMaxPoint->viPosY = ptrMinPoint->viPosY;
    fDrawHorizontalLine(aaiMatrix, ptrLineMinPoint, ptrLineMaxPoint);


    ptrLineMinPoint->viPosY = ptrMaxPoint->viPosY;
    fDrawHorizontalLine(aaiMatrix, ptrLineMinPoint, ptrLineMaxPoint);

    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    ptrLineMinPoint->viPosY = ptrMinPoint->viPosY;
    ptrLineMaxPoint->viPosY = ptrMaxPoint->viPosY;
    fDrawVerticalLine(aaiMatrix, ptrLineMinPoint, ptrLineMaxPoint);

    fDrawSymbol(aaiMatrix, '+', ptrLineMinPoint);

    ptrLineMinPoint->viPosX = ptrMaxPoint->viPosX;
    fDrawVerticalLine(aaiMatrix, ptrLineMinPoint, ptrLineMaxPoint);

    fDrawSymbol(aaiMatrix, '+', ptrLineMinPoint);

    fDrawSymbol(aaiMatrix, '+', ptrLineMaxPoint);

    ptrLineMaxPoint->viPosX = ptrMinPoint->viPosX;
    ptrLineMaxPoint->viPosY = ptrMaxPoint->viPosY;
    fDrawSymbol(aaiMatrix, '+', ptrLineMaxPoint);

    delete_Point(ptrLineMinPoint);
    delete_Point(ptrLineMaxPoint);
}

//--------------------------------------------------------------------------------

void fCopyMatrix(void* ** aaoIn, void* ** aaoFrom, int viHeight, int viWidth)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < viHeight; i++)
    {
        for(j = 0; j < viWidth; j++)
        {
            aaoIn[i][j] = aaoFrom[i][j];
        }
    }
}

//---------------------------------------------------------------------------------

void* ** fCreateMatrix(int viSizeOfType, int viHeight, int viWidth, void* vcDefValue)
{
    int i = 0;
    int j = 0;

    void* ** aaoMatrix = malloc(sizeof(void* *) * viHeight);
    for(i = 0; i < viHeight; i++)
    {
        aaoMatrix[i] = malloc(viSizeOfType * viWidth);
        for(j = 0; j < viWidth; j++)
        {
            aaoMatrix[i][j] = vcDefValue;
        }
    }

    return aaoMatrix;
}

#endif
