#ifndef MainMenu_h
#define MainMenu_h

#include <stdio.h>
#include <stdlib.h>
#include "Geometry.h"
#include "VideoAdapter.h"
#include "Text.h"

void ShowMainMenu(VideoAdapter * ptrVideoAdapter)
{

    int ** aaiTitle = fCreateMatrix(sizeof(int), 5, 30, "");
    aaiTitle[0] = "Il progetto finale dell corso di";
    aaiTitle[1] = "\"Programmazione in C\"";
    aaiTitle[2] = "Il progeto preparato da Sakharov Sergey";
    aaiTitle[3] = "studente dell 1 anno 1 semestre";
    aaiTitle[4] = "di Universita degli Studi di Cagliari";

    int i = 0;
    for(i = 0; i < 5; i++)
    {
        Inscription * ptrLabel = new_Inscription();
        ptrLabel->fSetWord(ptrLabel, aaiTitle[i]);

        ptrLabel->ptrMinPoint->viPosX = 25;
        ptrLabel->ptrMinPoint->viPosY = 20 + i * 4;
        ptrLabel->viWidth = 50;
        ptrLabel->viHeight = 4;
        ptrLabel->bbBorder = 1;
        ptrLabel->fDraw(ptrLabel, ptrVideoAdapter->aaiScreen);
    }

}

void DeadOfPlayer(VideoAdapter * ptrVideoAdapter, char * acPlayer)
{
    int ** aaiTitle = fCreateMatrix(sizeof(int), 5, 30, "");
    aaiTitle[0] = "Vinto il giocatore:";
    aaiTitle[1] = acPlayer;

    int i = 0;
    for(i = 0; i < 2; i++)
    {
        Inscription * ptrLabel = new_Inscription();
        ptrLabel->fSetWord(ptrLabel, aaiTitle[i]);

        ptrLabel->ptrMinPoint->viPosX = 25;
        ptrLabel->ptrMinPoint->viPosY = 20 + i * 4;
        ptrLabel->viWidth = 50;
        ptrLabel->viHeight = 4;
        ptrLabel->bbBorder = 1;
        ptrLabel->fDraw(ptrLabel, ptrVideoAdapter->aaiScreen);
    }
}

/*void fInterfacia(VideoAdapter * ptrVideoAdapter, Player * ptrPlayer1, Player * ptrPlayer2)
{
    int ** aaiTitle = fCreateMatrix(sizeof(int), 5, 40, "");
    aaiTitle[0] = "le vostre navi sopravvissuti: ";
    aaiTitle[1] = "le navi nemiche sopravvissuti: ";
    //
    //aaiTitle[2] = ptrPlayer1->viMaxShips - ptrPlayer1->viDestroyedShips
    //aaiTitle[3] = itoa(ptrPlayer2->viMaxShips - ptrPlayer2->viDestroyedShips);

    Inscription * ptrLabel_0 = new_Inscription();
    ptrLabel_0->ptrMinPoint->viPosX = 50;
    ptrLabel_0->ptrMinPoint->viPosY = 10;
    ptrLabel_0->viWidth = 33;
    ptrLabel_0->viHeight = 2;
    ptrLabel_0->bbBorder = 1;



    Inscription * ptrLabel_1 = new_Inscription();
    ptrLabel_1->ptrMinPoint->viPosX = 85;
    ptrLabel_1->ptrMinPoint->viPosY = 10;
    ptrLabel_1->viWidth = 10;
    ptrLabel_1->viHeight = 2;
    ptrLabel_1->bbBorder = 1;

    int i = 0;
    for(i = 0; i < 2; i++)
    {

        ptrLabel_0->fSetWord(ptrLabel_0, aaiTitle[i]);
        ptrLabel_0->ptrMinPoint->viPosY += i * 4;
        ptrLabel_0->fDraw(ptrLabel_0, ptrVideoAdapter->aaiScreen);

        ptrLabel_1->fSetWord(ptrLabel_1, &(aaiTitle[i + 2]));
        ptrLabel_1->ptrMinPoint->viPosY += i * 4;
        ptrLabel_1->fDraw(ptrLabel_1, ptrVideoAdapter->aaiScreen);
    }

    delete_Inscription(ptrLabel_0);
    delete_Inscription(ptrLabel_1);
}*/


#endif



