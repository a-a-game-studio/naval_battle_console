#ifndef VideoAdapter_h
#define VideoAdapter_h

#include <stdio.h>
#include <stdlib.h>

typedef struct VideoAdapter
{
    int viWidth;
    int viHeight;
    int ** aaiScreen;
    void (*fDraw)();
    void (*fReset)();
}VideoAdapter;

void member_of_VideoAdapter_fReset(VideoAdapter * ptrVideoAdapter)
{
    int i = 0, j = 0;
    for(i = 0; i < ptrVideoAdapter->viHeight; i++)
    {
        ptrVideoAdapter->aaiScreen[i] = malloc(sizeof(int) * ptrVideoAdapter->viWidth);
        for(j = 0; j < ptrVideoAdapter->viWidth; j++)
        {
            ptrVideoAdapter->aaiScreen[i][j] = ' ';
        }
    }
}

void member_of_VideoAdapter_fDraw(VideoAdapter * ptrVideoAdapter)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < ptrVideoAdapter->viHeight; i++)
    {
        for(j = 0; j < ptrVideoAdapter->viWidth; j++)
        {
            printf("%c", (char)ptrVideoAdapter->aaiScreen[i][j]);
        }
        //printf("\n");
    }
    printf("\n");
    //ptrVideoAdapter->aaiScreen[
}

static VideoAdapter * new_VideoAdapter()
{
    VideoAdapter * ptrVideoAdapter = malloc(sizeof(VideoAdapter));

    ptrVideoAdapter->viHeight = 60;
    ptrVideoAdapter->viWidth = 100;

    int i = 0;
    int j = 0;

    ptrVideoAdapter->aaiScreen = malloc(sizeof(int *) * ptrVideoAdapter->viHeight);
    for(i = 0; i < ptrVideoAdapter->viHeight; i++)
    {
        ptrVideoAdapter->aaiScreen[i] = malloc(sizeof(int) * ptrVideoAdapter->viWidth);
        for(j = 0; j < ptrVideoAdapter->viWidth; j++)
        {
            ptrVideoAdapter->aaiScreen[i][j] = ' ';
        }
    }

    ptrVideoAdapter->fDraw = member_of_VideoAdapter_fDraw;
    ptrVideoAdapter->fReset = member_of_VideoAdapter_fReset;

    return ptrVideoAdapter;
}

#endif
