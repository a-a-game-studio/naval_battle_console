#ifndef Scanning_h
#define Scanning_h

#include <stdio.h>
#include <stdlib.h>
#include "Geometry.h"
#include "Structure.h"
//#include "Ship.h"

typedef struct Cell
{
    Point * ptrPosition;

    //Length direction
    int viUp;
    int viRight;
    int viDown;
    int viLeft;

    char bbEmpty;

}Cell;

//====================================================================================================

typedef struct Scanner
{
    Array * (*fSelectEmptyCells)(int ** aaiMatrix);
    Array * (*fDirectionAvailable)(int ** aaiMatrix, int viSizeOfShip, Point * ptrPosition);
    void (*fFillingAroundSymbol)(int ** aaiMatrix, char vcNeutralSymbol, char vcTargetSymbol);

}Scanner;

void member_of_Scanner_fFillingAroundSymbol(int ** aaiMatrix, char vcNeutralSymbol, char vcTargetSymbol)
{
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;

    Point * ptrMinPoint = new_Point(0, 0);
    Point * ptrMaxPoint = new_Point(0, 0);

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if(aaiMatrix[i][j] != vcTargetSymbol && aaiMatrix[i][j] != vcNeutralSymbol)
            {
                ptrMinPoint->viPosY = i;
                ptrMinPoint->viPosX = j;
                ptrMaxPoint->viPosY = i;
                ptrMaxPoint->viPosX = j;
                if(i > 0)
                {
                    ptrMinPoint->viPosY--;
                }
                if(i < 9)
                {
                    ptrMaxPoint->viPosY++;
                }
                if(j > 0)
                {
                    ptrMinPoint->viPosX--;
                }
                if(j < 9)
                {
                    ptrMaxPoint->viPosX++;
                }

                for(y = ptrMinPoint->viPosY; y <= ptrMaxPoint->viPosY; y++)
                {
                    for(x = ptrMinPoint->viPosX; x <= ptrMaxPoint->viPosX; x++)
                    {
                        if(aaiMatrix[y][x] == vcTargetSymbol)
                        {
                            aaiMatrix[i][j] = vcNeutralSymbol;
                            //break;
                        }
                    }
                }

                /*if(i < 9 && (aaiMatrix[i + 1][j] != vcSymbol && aaiMatrix[i + 1][j] != 'H'))
                {
                    if(j < 9 && (aaiMatrix[i + 1][j + 1] != vcSymbol && aaiMatrix[i + 1][j + 1] != 'H'))
                    {
                        aaiMatrix[i][j + 1] = 'H';
                    }
                    if(j > 0 && (aaiMatrix[i + 1][j - 1] != vcSymbol && aaiMatrix[i + 1][j - 1] != 'H'))
                    {
                        aaiMatrix[i][j - 1] = 'H';
                    }
                }

                if(i > 0 && (aaiMatrix[i - 1][j] != vcSymbol && aaiMatrix[i - 1][j] != 'H'))
                {
                    if(j < 9 && (aaiMatrix[i - 1][j + 1] != vcSymbol && aaiMatrix[i - 1][j + 1] != 'H'))
                    {
                        aaiMatrix[i][j + 1] = 'H';
                    }
                    if(j > 0 && (aaiMatrix[i - 1][j - 1] != vcSymbol && aaiMatrix[i - 1][j - 1] != 'H'))
                    {
                        aaiMatrix[i][j - 1] = 'H';
                    }
                }*/
            }
        }
    }

}

//----------------------------------------------------------------------------------------------------

Array * member_of_Scanner_fDirectionAvailable(int ** aaiMatrix, int viSizeOfShip, Point * ptrPosition)
{
    int i = 0;
    int j = 0;
    int viSign = 1;

    int viPosX_1 = 0;
    int viPosY_1 = 0;

    char bbStatus = 0;

    Array * aiDirections = new_Array(sizeof(int), 4);
    aiDirections->viSizeOfArray = 0;
    for(i = 0; i < 4; i++)
    {
        if(diTop == i || diLeft == i)
        {
            viSign = -1;
        }
        else
        {
            viSign = 1;
        }
        bbStatus = 1;
        if(diRight == i || diLeft == i)
        {
            for(j = 0; j < viSizeOfShip; j++)
            {
                viPosX_1 = ptrPosition->viPosX + j * viSign;
                viPosY_1 = ptrPosition->viPosY;

                if(viPosY_1 < 0 || viPosY_1 > 9)
                {
                    bbStatus = 0;
                    break;
                }
                if(viPosX_1 < 0 || viPosX_1 > 9)
                {
                    bbStatus = 0;
                    break;
                }

                if(aaiMatrix[viPosY_1][viPosX_1] != ' ')
                {
                    bbStatus = 0;
                    break;
                }
            }
        }
        else
        {
            for(j = 0; j < viSizeOfShip; j++)
            {
                viPosY_1 = ptrPosition->viPosY + j * viSign;
                viPosX_1 = ptrPosition->viPosX;


                if(viPosY_1 < 0 || viPosY_1 > 9)
                {
                    bbStatus = 0;
                    break;
                }
                if(viPosX_1 < 0 || viPosX_1 > 9)
                {
                    bbStatus = 0;
                    break;
                }

                if(aaiMatrix[viPosY_1][viPosX_1] != ' ')
                {
                    bbStatus = 0;
                    break;
                }
            }
        }

        if(bbStatus == 1)
        {
            aiDirections->aoArray[aiDirections->viSizeOfArray] = i;
            aiDirections->viSizeOfArray++;
        }

    }

    return aiDirections;
}

//------------------------------------------------------------------------------------------------

Array * member_of_Scanner_fSelectEmptyCells(int ** aaiMatrix)
{
    int i = 0;
    int j = 0;

    Array * ptrArray = new_Array(sizeof(Point *), 100);
    ptrArray->viSizeOfArray = 0;

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if(aaiMatrix[i][j] == ' ')
            {
                ptrArray->aoArray[ptrArray->viSizeOfArray] = new_Point(j, i);
                ptrArray->viSizeOfArray++;
            }
        }
    }

    return ptrArray;
}

//---------------------------------------------------------------------------------------------------

Scanner * new_Scanner()
{
    Scanner * ptrScaner = malloc(sizeof(Scanner));

    ptrScaner->fSelectEmptyCells = member_of_Scanner_fSelectEmptyCells;
    ptrScaner->fDirectionAvailable = member_of_Scanner_fDirectionAvailable;
    ptrScaner->fFillingAroundSymbol = member_of_Scanner_fFillingAroundSymbol;

    return ptrScaner;
}

#endif
