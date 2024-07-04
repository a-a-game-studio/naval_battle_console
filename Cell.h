#ifndef Cell_h
#define Cell_h

typedef struct Cell
{
    int viPosX;
    int viPosY;

    //Length direction
    int viUp;
    int viRight;
    int viDown;
    int viLeft;

    char bbEmpty;

}Cell;

#endif
