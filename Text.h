#ifndef Text_h
#define Text_h

#include <stdio.h>
#include <stdlib.h>
#include "Geometry.h"
#include "VideoAdapter.h"



typedef struct Inscription
{
    Point * ptrMinPoint;
    int viWidth;
    int viHeight;
    char * acWord;
    int bbBorder;
    int viAlign;
    int viLength;

    void (*fDraw)(void* * this, int ** aaiMatrix);
    void (*fSetWord)(void* * this, char * acWord);
}Inscription;

void member_of_Inscription_fDraw(Inscription * this, int ** aaiMatrix)
{
    int i = 0;
    int j = 0;
    Point * ptrMinPoint = this->ptrMinPoint;
    Point * ptrMaxPoint = new_Point(0, 0);
    ptrMaxPoint->viPosX = ptrMinPoint->viPosX + this->viWidth;
    ptrMaxPoint->viPosY = ptrMinPoint->viPosY + this->viHeight;

    int viPosX_1 = 0;
    int viPosY_1 = 0;

    if(this->viAlign == diLeft)
    {
        viPosX_1 = ptrMinPoint->viPosX;
        viPosY_1 = ptrMinPoint->viPosY;
    }
    else if(this->viAlign == diCenter)
    {
        viPosX_1 = ptrMinPoint->viPosX + (this->viWidth / 2) - (this->viLength / 2);
        viPosY_1 = ptrMinPoint->viPosY + (this->viHeight / 2);
    }
    else
    {
        viPosX_1 = ptrMinPoint->viPosX  + this->viWidth - this->viLength;
        viPosY_1 = ptrMinPoint->viPosY + (this->viHeight / 2);
    }

    for(i = viPosX_1, j = 0; j < this->viLength; i++, j++)
    {
        aaiMatrix[viPosY_1][i] = this->acWord[j];
    }

    if(this->bbBorder == 1)
    {
        fDrawRectangle(aaiMatrix, ptrMinPoint, ptrMaxPoint);
    }
}

void member_of_Inscription_fSetWord(Inscription * this, char * acWord)
{
    this->viLength = strlen(acWord);
    this->acWord = acWord;
}

Inscription * new_Inscription()
{
    Inscription * this = malloc(sizeof(Inscription));

    this->ptrMinPoint = new_Point(0, 0);
    this->viAlign = diCenter;
    this->acWord = 0;
    this->bbBorder = 0;
    this->viLength = 0;

    this->fDraw = member_of_Inscription_fDraw;
    this->fSetWord = member_of_Inscription_fSetWord;

    return this;
}

void delete_Inscription(Inscription * this)
{
    free(this);
    this = 0;
}

#endif
