#ifndef Battlefield_h
#define Battlefield_h

#include <stdio.h>
#include <stdlib.h>
#include "Geometry.h"
#include "VideoAdapter.h"

#define diFieldFire 0
#define diFieldPosition 1

typedef struct Battlefield;
typedef struct Battlefield
{
    Point * ptrPoint;
    Point * viMinFieldPoint;
    Point * viMaxFieldPoint;
    int viSize;
    int ** aaiMatrix;
    int ** aaiWoundedMatrix;
    int ** aaiIndexedMatrix;
    int viType;
    VideoAdapter * ptrVideoAdapter;
    void (*fDraw)(void ** ptrBattlefield);
    void (*fDrawShot)(void* * ptrCurrPlayer, void* * ptrEnemyPlayer);
}Battlefield;



//-------------------------------------------------------------------------------------------------------

void member_of_Battlefield_fDrawShot(Battlefield * ptrCurrPlayerField, Battlefield * ptrEnemyPlayerField)
{
    int i = 0, j = 0;
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if(ptrEnemyPlayerField->aaiWoundedMatrix[i][j] == 'X')
            {
                ptrCurrPlayerField->aaiMatrix[i][j] = ptrCurrPlayerField->aaiWoundedMatrix[i][j];
                ptrEnemyPlayerField->aaiMatrix[i][j] = ptrEnemyPlayerField->aaiWoundedMatrix[i][j];
            }
            else if(ptrEnemyPlayerField->aaiWoundedMatrix[i][j] == '*')
            {
                ptrCurrPlayerField->aaiMatrix[i][j] = ptrCurrPlayerField->aaiWoundedMatrix[i][j];
                ptrEnemyPlayerField->aaiMatrix[i][j] = ptrEnemyPlayerField->aaiWoundedMatrix[i][j];
            }
            else if(ptrEnemyPlayerField->aaiWoundedMatrix[i][j] == '#')
            {
                ptrCurrPlayerField->aaiMatrix[i][j] = ptrCurrPlayerField->aaiWoundedMatrix[i][j];
                ptrEnemyPlayerField->aaiMatrix[i][j] = ptrEnemyPlayerField->aaiWoundedMatrix[i][j];
            }
        }
    }
}

void member_of_Battlefield_fDrawFieldOfPosition(Battlefield * ptrBattlefield)
{
    VideoAdapter * ptrVideoAdapter = ptrBattlefield->ptrVideoAdapter;
    Point * ptrFieldPosXY = ptrBattlefield->ptrPoint;

    int i = 0;
    int j = 0;
    int c = 0;

    int viColumnLetter = 5;
    int viRowNumber = 2;
    int viColumnIncrement = 3;
    int viRowIncrement = 0;
    int viIntersectionIncr = 3;

    for(i = 0; i < 11; i++)
    {
        if(i < 10)
        {
            ptrVideoAdapter->aaiScreen[0 + ptrFieldPosXY->viPosY][viColumnLetter + (i * 3) + ptrFieldPosXY->viPosX] = 'A' + i;

            ptrVideoAdapter->aaiScreen[(i * 2) + viRowNumber + ptrFieldPosXY->viPosY][1 + ptrFieldPosXY->viPosX] = '0' + i;
        }


        for(j = 0; j < 10; j++)
        {
            if(i < 10)
            {
                //Matrice of Postional Field
                ptrVideoAdapter->aaiScreen[(i * 2) + viRowNumber + ptrFieldPosXY->viPosY][5 + (j * 4) + ptrFieldPosXY->viPosX] = ptrBattlefield->aaiMatrix[i][j];
            }
        }

        ptrVideoAdapter->aaiScreen[0 + ptrFieldPosXY->viPosY][viColumnIncrement + (i * 4) + ptrFieldPosXY->viPosX] = '|';

        viRowIncrement = 0;
        for(c = 0; c < 3; c++)
        {
            //Spliter number
            ptrVideoAdapter->aaiScreen[(i * 2) + 1 + ptrFieldPosXY->viPosY][viRowIncrement + ptrFieldPosXY->viPosX] = '-';

            //Horisontal Up line
            ptrVideoAdapter->aaiScreen[1 + ptrFieldPosXY->viPosY][(i * 4) + viRowIncrement + ptrFieldPosXY->viPosX] = '-';

            //Bottom line
            ptrVideoAdapter->aaiScreen[(10 * 2) + 1 + ptrFieldPosXY->viPosY][(i * 4) + viRowIncrement + ptrFieldPosXY->viPosX] = '-';

            viRowIncrement++;
        }

        //Left vertical Line
        ptrVideoAdapter->aaiScreen[(i * 2) + ptrFieldPosXY->viPosY][viColumnIncrement + ptrFieldPosXY->viPosX] = '|';
        ptrVideoAdapter->aaiScreen[(i * 2) + 1 + ptrFieldPosXY->viPosY][viIntersectionIncr + ptrFieldPosXY->viPosX] = '+';

        //Right vertical Line
        ptrVideoAdapter->aaiScreen[(i * 2) + ptrFieldPosXY->viPosY][(10 * 4) + viColumnIncrement + ptrFieldPosXY->viPosX] = '|';
        ptrVideoAdapter->aaiScreen[(i * 2) + 1 + ptrFieldPosXY->viPosY][(10 * 4) + viColumnIncrement + ptrFieldPosXY->viPosX] = '|';

        //Horisontal Line
        ptrVideoAdapter->aaiScreen[(10 * 2) + 1 + ptrFieldPosXY->viPosY][(i * 4) + viIntersectionIncr + ptrFieldPosXY->viPosX] = '-';

        //Intesaction
        ptrVideoAdapter->aaiScreen[1 + ptrFieldPosXY->viPosY][(i * 4) + viIntersectionIncr + ptrFieldPosXY->viPosX] = '+';

        viColumnLetter++;
    }

    ptrVideoAdapter->aaiScreen[(10 * 2) + 1 + ptrFieldPosXY->viPosY][(10 * 4) + viIntersectionIncr + ptrFieldPosXY->viPosX] = '+';

}

//--------------------------------------------------------------------------------------------------------

void member_of_Battlefield_fDrawFieldOfFire(Battlefield * ptrBattlefield)
{

    VideoAdapter * ptrVideoAdapter = ptrBattlefield->ptrVideoAdapter;
    Point * ptrFieldPosXY = ptrBattlefield->ptrPoint;

    int i = 0;
    int j = 0;
    int c = 0;

    int viColumnLetter = 5;
    int viRowNumber = 2;
    int viColumnIncrement = 3;
    int viRowIncrement = 0;
    int viIntersectionIncr = 3;

    for(i = 0; i < 11; i++)
    {
        if(i < 10)
        {
            ptrVideoAdapter->aaiScreen[0 + ptrFieldPosXY->viPosY][viColumnLetter + (i * 3) + ptrFieldPosXY->viPosX] = 'A' + i;

            ptrVideoAdapter->aaiScreen[(i * 2) + viRowNumber + ptrFieldPosXY->viPosY][1 + ptrFieldPosXY->viPosX] = '0' + i;
        }



        for(j = 0; j < 11; j++)
        {
            if(i < 10 && j < 10)
            {
                //Matrice of Fire Field
                ptrVideoAdapter->aaiScreen[(i * 2) + viRowNumber + ptrFieldPosXY->viPosY][5 + (j * 4) + ptrFieldPosXY->viPosX] = ptrBattlefield->aaiMatrix[i][j];
            }

            viRowIncrement = 0;
            for(c = 0; c < 3; c++)
            {
                ptrVideoAdapter->aaiScreen[(j * 2) + 1 + ptrFieldPosXY->viPosY][viRowIncrement + (i * 4) + ptrFieldPosXY->viPosX] = '-';

                viRowIncrement++;
            }

            ptrVideoAdapter->aaiScreen[(i * 2) + ptrFieldPosXY->viPosY][viColumnIncrement + (j * 4) + ptrFieldPosXY->viPosX] = '|';

            ptrVideoAdapter->aaiScreen[(i * 2) + 1 + ptrFieldPosXY->viPosY][viIntersectionIncr + (j * 4) + ptrFieldPosXY->viPosX] = '+';


        }

        viColumnLetter++;
    }

}

//------------------------------------------------------------------------------------------------------------

static Battlefield * new_Battlefield(int viType, VideoAdapter * ptrVideoAdapter, Point * ptrPoint)
{
    Battlefield * ptrBattlefield = malloc(sizeof(Battlefield));

    ptrBattlefield->ptrPoint = ptrPoint;

    ptrBattlefield->viSize = 10;

    ptrBattlefield->aaiMatrix = fCreateMatrix(sizeof(int), 10, 10, ' ');
    ptrBattlefield->aaiWoundedMatrix = fCreateMatrix(sizeof(int), 10, 10, ' ');
    ptrBattlefield->aaiIndexedMatrix = fCreateMatrix(sizeof(int), 10, 10, ' ');

    ptrBattlefield->viMinFieldPoint = new_Point(0, 0);
    Point * viMinFieldPoint = ptrBattlefield->viMinFieldPoint;

    ptrBattlefield->viMaxFieldPoint = new_Point(0, 0);
    Point * viMaxFieldPoint = ptrBattlefield->viMaxFieldPoint;

    viMinFieldPoint->viPosX = ptrPoint->viPosX + 3;
    viMinFieldPoint->viPosY = ptrPoint->viPosY + 1;

    viMaxFieldPoint->viPosX = ptrPoint->viPosX + ptrBattlefield->viSize * 4;
    viMaxFieldPoint->viPosY = ptrPoint->viPosY + ptrBattlefield->viSize * 2;

    ptrBattlefield->viType = viType;
    ptrBattlefield->ptrVideoAdapter = ptrVideoAdapter;


    if(viType == diFieldPosition)
    {
        ptrBattlefield->fDraw = member_of_Battlefield_fDrawFieldOfPosition;
    }
    else if(viType == diFieldFire)
    {
        ptrBattlefield->fDraw = member_of_Battlefield_fDrawFieldOfFire;
    }
    else
    {
        printf("#Errore: type of field\n");
    }

    ptrBattlefield->fDrawShot = member_of_Battlefield_fDrawShot;

    return ptrBattlefield;
}

static void delete_Battlefield(Battlefield * ptrBattlefield)
{
    int i = 0;
    for(i = 0; i < 10; i++)
    {
        free(ptrBattlefield->aaiMatrix[i]);
        ptrBattlefield->aaiMatrix[i] = 0;

        free(ptrBattlefield->aaiWoundedMatrix[i]);
        ptrBattlefield->aaiWoundedMatrix[i] = 0;

        free(ptrBattlefield->aaiIndexedMatrix[i]);
        ptrBattlefield->aaiIndexedMatrix[i] = 0;
    }
    free(ptrBattlefield->aaiMatrix);
    ptrBattlefield->aaiMatrix = 0;

    free(ptrBattlefield->aaiWoundedMatrix);
    ptrBattlefield->aaiWoundedMatrix = 0;

    free(ptrBattlefield->aaiIndexedMatrix);
    ptrBattlefield->aaiIndexedMatrix = 0;
}


#endif
