#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Geometry.h"
#include "VideoAdapter.h"
#include "Battlefield.h"
#include "Ship.h"
#include "Structure.h"
#include "Scanning.h"
#include "Text.h"


typedef struct Player
{
    int viShotX;
    int viShotY;
    int viMaxShips;
    int viDestroyedShips;
    int aiWoundedIncr[10];
    Scanner * ptrScanner;
    Ship ** Ships;
    Battlefield * ptrFieldPos;
    Battlefield * ptrFieldFire;

    void (*fShot)(void* * this, void* * ptrEnemy);
    void (*fDraw)(void* * this);
    //void (*fDestruction)(void* * this);
}Player;

void member_of_Player_fDraw(Player * this)
{
     this->ptrFieldPos->fDraw(this->ptrFieldPos);
     this->ptrFieldFire->fDraw(this->ptrFieldFire);

     int i = 0, j = 0;
     for(i = 0; i < this->viMaxShips; i++)
     {
         this->Ships[i]->fDrawFP(this->ptrFieldPos, this->Ships[i]);
         this->Ships[i]->fDrawFF(this->ptrFieldFire, this->Ships[i]);
     }

    //fDrawWounded(this->ptrFieldPos);
    //fDrawWounded(this->ptrFieldFire);
     //this->ptrFieldPos->fDraw(this->ptrFieldPos);
     //this->ptrFieldFire->fDraw(this->ptrFieldFire);
}

void member_of_Player_fShot(Player * this, Player * ptrEnemy)
{
    printf("Insert Shot: per esempio: \'A1\', \'b4\', \'a4\' - and press \'Enter\'"); printf("\n");
    scanf("%c%d", &this->viShotX, &this->viShotY);

    printf("Your Shot: "); printf("%c%d", this->viShotX, this->viShotY) ; printf("\n\n");

    //this->viShotX = getchar();
    //this->viShotY = getchar(); //printf('\n');

    if(isupper(this->viShotX))
    {
        this->viShotX = this->viShotX - 'A';
    }
    else if(islower(this->viShotX))
    {
        this->viShotX = this->viShotX - 'a';
    }
    else
    {
        printf("Error: il parametro deve essere una lettera. Per Wesempio: \"A3\"\n");
        getchar();
        member_of_Player_fShot(this, ptrEnemy);
    }

    if(!(this->viShotY >= 0 && this->viShotY <= 9))
    {
        printf("Errore: il numero della letera deve essere \'0\'..\'9\'\n");
        getchar();
        member_of_Player_fShot(this, ptrEnemy);
    }

    //scanf("%c%d", &this->viShotX, &this->viShotY); getchar();
    //printf("Your Shot: "); printf("%c%d", this->viShotX + 'a', this->viShotY) ; printf("\n\n");

    int viIndexOfShip = 0;
    Ship * ptrShip = 0;

    if(ptrEnemy->ptrFieldPos->aaiMatrix[this->viShotY][this->viShotX] == 'O')
    {
        ptrEnemy->ptrFieldPos->aaiWoundedMatrix[this->viShotY][this->viShotX] = '#';
        this->ptrFieldFire->aaiWoundedMatrix[this->viShotY][this->viShotX] = '#';
        viIndexOfShip = ptrEnemy->ptrFieldPos->aaiIndexedMatrix[this->viShotY][this->viShotX];

        //this->aiWoundedIncr[viIndexOfShip]++;
        ptrEnemy->Ships[viIndexOfShip]->viHit++;

        if(ptrEnemy->Ships[viIndexOfShip]->viHit == ptrEnemy->Ships[viIndexOfShip]->viSize)
        {
            ptrEnemy->viDestroyedShips++;
            ptrEnemy->Ships[viIndexOfShip]->fDestruction(ptrEnemy->Ships[viIndexOfShip], ptrEnemy->ptrFieldPos, ptrEnemy->ptrScanner);
            this->Ships[viIndexOfShip]->fDestruction(ptrEnemy->Ships[viIndexOfShip], this->ptrFieldFire, this->ptrScanner);
        }


        //ptrEnemy->ptrFieldPos->fDrawShot(
    }
    else if(ptrEnemy->ptrFieldPos->aaiMatrix[this->viShotY][this->viShotX] == '*')
    {
        printf("Errore: voi avete gia sparato nell quella posizione\n");
        getchar();
        member_of_Player_fShot(this, ptrEnemy);
    }
    else if(ptrEnemy->ptrFieldPos->aaiMatrix[this->viShotY][this->viShotX] == '#')
    {
        printf("Errore: voi avete gia sparato nell quella posizione\n");
        getchar();
        member_of_Player_fShot(this, ptrEnemy);
    }
    else if(ptrEnemy->ptrFieldPos->aaiMatrix[this->viShotY][this->viShotX] == 'X')
    {
        printf("Errore: voi avete gia sparato nell quella posizione\n");
        getchar();
        member_of_Player_fShot(this, ptrEnemy);
    }
    else
    {
        ptrEnemy->ptrFieldPos->aaiMatrix[this->viShotY][this->viShotX] = '*';
        this->ptrFieldFire->aaiMatrix[this->viShotY][this->viShotX] = '*';
    }

    this->ptrFieldFire->fDrawShot(this->ptrFieldFire, ptrEnemy->ptrFieldPos);

    //getchar();
}

Player * new_Player(VideoAdapter * ptrVideoAdapter)
{
    Player * this = malloc(sizeof(Player));

    this->viShotX = 0;
    this->viShotY = 0;
    this->viMaxShips = 10;
    this->viDestroyedShips = 0;



    this->ptrFieldPos = new_Battlefield(diFieldPosition, ptrVideoAdapter, new_Point(3, 3));
    this->ptrFieldFire = new_Battlefield(diFieldFire, ptrVideoAdapter, new_Point(3, 30));

    this->Ships = malloc(sizeof(void* *) * 10);

    this->ptrScanner = new_Scanner();

    int i = 0, j = 0, c = 0, viShipIncr = 0;

    for(i = 0; i < 10; i++)
    {
        this->aiWoundedIncr[i] = 0;
    }

    int viRandCell = 0;
    int viRandDirection = 0;
    int viCurrentDirect = 0;
    Array * ptrArrayOfCells;
    Array * aoDirection;
    Point * ptrTempsPos;

    int ** aaiMX = fCreateMatrix(sizeof(int), 10, 10, ' ');

    for(i = 4, j = 1, viShipIncr; i > 0; i--, j++)
    {
        for(c = 0; c < j; c++, viShipIncr++)
        {
            ptrArrayOfCells = this->ptrScanner->fSelectEmptyCells(this->ptrFieldPos->aaiMatrix);

            m_1:
            viRandCell = rand()%ptrArrayOfCells->viSizeOfArray;

            ptrTempsPos = ptrArrayOfCells->aoArray[viRandCell];
            aoDirection = this->ptrScanner->fDirectionAvailable(this->ptrFieldPos->aaiMatrix, i, ptrTempsPos);

            if(aoDirection->viSizeOfArray != 0)
            {
                viRandDirection = rand()%aoDirection->viSizeOfArray;
                viCurrentDirect = aoDirection->aoArray[viRandDirection];
            }
            else
            {
                goto m_1;
            }

            this->Ships[viShipIncr] = new_Ship(viShipIncr, i, ptrTempsPos->viPosX, ptrTempsPos->viPosY, viCurrentDirect);

            //printf("%d", viShipIncr); printf("\n");
            //printf("%d",  this->Ships[viShipIncr]); printf("\n");

            this->Ships[viShipIncr]->fDrawFP(this->ptrFieldPos, this->Ships[viShipIncr]);

            //this->ptrFieldPos->fDraw(this->ptrFieldPos);

            this->ptrScanner->fFillingAroundSymbol(this->ptrFieldPos->aaiMatrix, 'N', 'O');

            delete_Array(ptrArrayOfCells);
            delete_Array(aoDirection);
        }
    }

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if(this->ptrFieldPos->aaiMatrix[i][j] == 'O')
            {
                aaiMX[i][j] = this->ptrFieldPos->aaiMatrix[i][j];
            }
        }
    }

    this->ptrFieldPos->aaiMatrix = aaiMX;


    this->fShot = member_of_Player_fShot;
    this->fDraw = member_of_Player_fDraw;
    return this;
}

void delete_Player(Player * this)
{
    int i = 0;
    for(i = 0; i < this->viMaxShips; i++)
    {
        delete_Ship(&this->Ships[i]);
    }

    delete_Battlefield(this->ptrFieldPos);
    delete_Battlefield(this->ptrFieldFire);

    free(this);
    this = 0;
}



#endif
