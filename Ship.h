#ifndef Ship_h
#define Ship_h

#include <stdio.h>
#include <stdlib.h>
#include "Geometry.h"
#include "VideoAdapter.h"
#include "Battlefield.h"
#include "Text.h"
#include "Scanning.h"





//Status
#define diIntact 0
#define diWounded 1
#define diDestroyed 2

typedef struct Ship
{
    int viIndex;
    int viPosX;
    int viPosY;
    int viDirection;
    int viSize;
    int viHit;
    int viStatus;
    Point * aoTemplate[4];
    VideoAdapter * ptrVideoAdapter;
    void (*fDrawFF)(void* * ptrBattlefield, void* * ptrShip);
    void (*fDrawFP)(void* * ptrBattlefield, void* * ptrShip);
    void (*fDestruction)(void* * this, void* * ptrBattlefield, Scanner * ptrScanner);
}Ship;

void member_of_Ship_fDestruction(Ship * this, Battlefield * ptrBattlefield, Scanner * ptrScanner)
{
    Point * ptrCurrPos = 0;

    int i = 0;
    for(i = 0; i < this->viSize; i++)
    {
        ptrCurrPos = this->aoTemplate[i];
        ptrBattlefield->aaiWoundedMatrix[ptrCurrPos->viPosY][ptrCurrPos->viPosX] = 'X';
    }

    ptrScanner->fFillingAroundSymbol(ptrBattlefield->aaiWoundedMatrix, '*', 'X');
}

void member_of_Ship_fDrawFF(Battlefield * ptrBattlefield, Ship * ptrShip)
{
}

void member_of_Ship_fDrawFP(Battlefield * ptrBattlefield, Ship * ptrShip)
{
    int i = 0;
    int j = 0;
    int viPosX = ptrShip->viPosX;
    int viPosY = ptrShip->viPosY;
    int viPosX_1 = 0;
    int viPosY_1 = 0;

    VideoAdapter * ptrVideoAdapter = ptrBattlefield->ptrVideoAdapter;

    Point * ptrMinPoint = new_Point(0, 0);
    Point * ptrMaxPoint = new_Point(0, 0);

    Point * ptrMinFieldPoint = ptrBattlefield->viMinFieldPoint;
    Point * ptrMaxFieldPoint = ptrBattlefield->viMaxFieldPoint;

    Point * ptrShipPos = new_Point(ptrShip->viPosX, ptrShip->viPosY);



    switch(ptrShip->viDirection)
    {
        case diTop:
        {
            //printf("%d", ptrShip->viPosY); printf("\n");
            //printf("%d", ptrShip->viSize); printf("\n");
            ptrShipPos->viPosY -= ptrShip->viSize - 1;
            ptrMaxPoint->viPosY += (ptrShip->viSize * 2);
            ptrMaxPoint->viPosX += (1 * 4);
        } break;

        case diBottom:
        {
            ptrMaxPoint->viPosY += (ptrShip->viSize * 2);
            ptrMaxPoint->viPosX += (1 * 4);
        } break;

        case diLeft:
        {
            ptrShipPos->viPosX -= ptrShip->viSize - 1;
            ptrMaxPoint->viPosX += (ptrShip->viSize * 4);
            ptrMaxPoint->viPosY += (1 * 2);
        } break;

        case diRight:
        {
            ptrMaxPoint->viPosX += (ptrShip->viSize * 4);
            ptrMaxPoint->viPosY += (1 * 2);
        } break;
    }

    ptrMinPoint->viPosX += ptrMinFieldPoint->viPosX + (ptrShipPos->viPosX * 4);
    ptrMinPoint->viPosY += ptrMinFieldPoint->viPosY + (ptrShipPos->viPosY * 2);
    ptrMaxPoint->viPosX += ptrMinFieldPoint->viPosX + (ptrShipPos->viPosX * 4);
    ptrMaxPoint->viPosY += ptrMinFieldPoint->viPosY + (ptrShipPos->viPosY * 2);

    fDrawRectangle(ptrVideoAdapter->aaiScreen, ptrMinPoint, ptrMaxPoint);

    if(ptrShip->viStatus == diIntact)
    {

        for(i = 0; i < ptrShip->viSize; i++)
        {
            if(ptrShip->viDirection == diTop || ptrShip->viDirection == diBottom)
            {
                viPosY_1 = ptrShipPos->viPosY + i;
                viPosX_1 = ptrShipPos->viPosX;
                ptrBattlefield->aaiMatrix[viPosY_1][viPosX_1] = 'O';
                ptrBattlefield->aaiIndexedMatrix[viPosY_1][viPosX_1] = ptrShip->viIndex;
                ptrShip->aoTemplate[i]->viPosX = viPosX_1;
                ptrShip->aoTemplate[i]->viPosY = viPosY_1;

            }
            else
            {
                viPosY_1 = ptrShipPos->viPosY;
                viPosX_1 = ptrShipPos->viPosX + i;
                ptrBattlefield->aaiMatrix[viPosY_1][viPosX_1] = 'O';
                ptrBattlefield->aaiIndexedMatrix[viPosY_1][viPosX_1] = ptrShip->viIndex;
                ptrShip->aoTemplate[i]->viPosX = viPosX_1;
                ptrShip->aoTemplate[i]->viPosY = viPosY_1;

            }
        }
    }
    else if(ptrShip->viStatus == diWounded)
    {
    }
    else
    {
    }

    delete_Point(ptrMinPoint);
    delete_Point(ptrMaxPoint);
}


Ship * new_Ship(int viIndex, int viSize, int viPosX, int viPosY, int viDirection)
{
    Ship * ptrShip = malloc(sizeof(Ship));

    ptrShip->viSize = viSize;
    ptrShip->viPosX = viPosX;
    ptrShip->viPosY = viPosY;
    ptrShip->viDirection = viDirection;
    ptrShip->viStatus = diIntact;
    ptrShip->viHit = 0;
    ptrShip->viIndex = viIndex;

    int i = 0;
    for(i = 0; i < ptrShip->viSize; i++)
    {
        ptrShip->aoTemplate[i] = new_Point(0, 0);
    }

    ptrShip->fDrawFF = member_of_Ship_fDrawFF;
    ptrShip->fDrawFP = member_of_Ship_fDrawFP;
    ptrShip->fDestruction = member_of_Ship_fDestruction;

    return ptrShip;
}

void delete_Ship(Ship * this)
{
    int i = 0;
    for(i = 0; i < this->viSize; i++)
    {
        free(this->aoTemplate[i]);
    }
    free(this);
    this = 0;
}

#endif
