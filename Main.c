#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Geometry.h"
#include "VideoAdapter.h"
#include "Battlefield.h"
#include "Ship.h"
#include "Structure.h"
#include "Scanning.h"
#include "Text.h"
#include "Player.h"
#include "MainMenu.h"






int main()
{
    printf("Per funzionamento della programma\n");
    printf("e necessario di impostare resoluzione della console:\n\n\n");
    printf("\tLargeza = 100\n\n");
    printf("\tAlteza = 65\n\n\n");
    printf("Per continuare press \"Enter\"(Invio)\n\n\n");

    getchar();

    srand(time(NULL));

    VideoAdapter * ptrVideoAdapter = new_VideoAdapter();

    ShowMainMenu(ptrVideoAdapter);

    ptrVideoAdapter->fDraw(ptrVideoAdapter);

    printf("Per continuare press \"Enter\"(Invio)\n\n\n");

    getchar();

    ptrVideoAdapter->fReset(ptrVideoAdapter);

    Player * ptrPlayer_1 = new_Player(ptrVideoAdapter);
    Player * ptrPlayer_2 = new_Player(ptrVideoAdapter);

    Inscription * ptrLabel_0 = new_Inscription();
    ptrLabel_0->ptrMinPoint->viPosX = 50;
    ptrLabel_0->ptrMinPoint->viPosY = 3;
    ptrLabel_0->viWidth = 30;
    ptrLabel_0->viHeight = 4;
    ptrLabel_0->bbBorder = 1;




    ptrVideoAdapter->fReset(ptrVideoAdapter);

    while(1)
    {
        ptrVideoAdapter->fReset(ptrVideoAdapter);

        if(ptrPlayer_1->viMaxShips == ptrPlayer_1->viDestroyedShips)
        {
            DeadOfPlayer(ptrVideoAdapter, "Player 2");
            ptrVideoAdapter->fDraw(ptrVideoAdapter);
            break;
        }
        else if(ptrPlayer_2->viMaxShips == ptrPlayer_2->viDestroyedShips)
        {
            DeadOfPlayer(ptrVideoAdapter, "Player 1");
            ptrVideoAdapter->fDraw(ptrVideoAdapter);
            break;
        }



        ptrLabel_0->fSetWord(ptrLabel_0, "Player 1");
        ptrLabel_0->fDraw(ptrLabel_0, ptrVideoAdapter->aaiScreen);

        ptrPlayer_1->fDraw(ptrPlayer_1);
        //fInterfacia(ptrVideoAdapter, ptrPlayer_1, ptrPlayer_2);

        ptrVideoAdapter->fDraw(ptrVideoAdapter);

        ptrPlayer_1->fShot(ptrPlayer_1, ptrPlayer_2);

        getchar();

        ptrVideoAdapter->fReset(ptrVideoAdapter);

        ptrLabel_0->fSetWord(ptrLabel_0, "Player 2");
        ptrLabel_0->fDraw(ptrLabel_0, ptrVideoAdapter->aaiScreen);

        ptrPlayer_2->fDraw(ptrPlayer_2);
        //fInterfacia(ptrVideoAdapter, ptrPlayer_2, ptrPlayer_1);

        ptrVideoAdapter->fDraw(ptrVideoAdapter);

        ptrPlayer_2->fShot(ptrPlayer_2, ptrPlayer_1);

        getchar();

    }

    printf("Avete vinto\n");
    getchar();

    return 0;
}
