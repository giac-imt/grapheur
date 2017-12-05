#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2\SDL.h>
#include <math.h>


/*#define NBPOINTS 5000
#define RESIZER_MULTIPLIER 80 //Taille du graphe qui pourrait etre donnee par l'utilisateur
#define PRECISION 100.0
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 600*/


int RESIZER_MULTIPLIER[4] = {10,50,100,150}; // proposer 10 50 100 150 (au hasard)
int MOVE_LENGTHX[2] = {0,20}; // Quantite de mouvement a effectuer lors de l'appui
int MOVE_LENGTHY[2] = {0,20};

float *point(Tree *arbre,float pointResult[3][NBPOINTS])
{
    int j;
    for(j=0;j<NBPOINTS;j++){
        if(Eval(arbre,j/PRECISION).err.code!=310){
            pointResult[0][j]=(j/PRECISION);
            pointResult[1][j]=-Eval(arbre,j/PRECISION).value;
        }
    }
    return *pointResult;
}

float *pointNeg(Tree *arbre,float pointResult[3][NBPOINTS])
{
    int j;
    for(j=-NBPOINTS;j<=0;j++){
        if(Eval(arbre,j/PRECISION).err.code!=310){
        pointResult[0][-j]=(j/PRECISION);
        pointResult[1][-j]=-Eval(arbre,j/PRECISION).value;
        }
    }
    return *pointResult;
}


void fillColor(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void drawAxes(SDL_Renderer* renderer, SDL_Window *screen)
{
    SDL_RenderDrawLine(renderer,0+ *MOVE_LENGTHX, WINDOW_WIDTH/2 , SDL_GetWindowSurface(screen)->w + *MOVE_LENGTHX, WINDOW_HEIGHT/2);//axe vertical
    SDL_RenderDrawLine(renderer,WINDOW_HEIGHT/2,0 + *MOVE_LENGTHY,WINDOW_WIDTH/2,SDL_GetWindowSurface(screen)->h + *MOVE_LENGTHY); //axe horizontal
}
void drawTransGrid(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,30,30,30,255);
    float centerCoordX=WINDOW_WIDTH/2;
    //float centerCoordY=WINDOW_HEIGHT/2;
    float GridBarCounts=(WINDOW_WIDTH-centerCoordX)/ *RESIZER_MULTIPLIER;
    int i;
    for(i=0;i<GridBarCounts;i++){
            SDL_RenderDrawLine(renderer,i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2,WINDOW_HEIGHT,i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2,0);//axe x positif
            SDL_RenderDrawLine(renderer,-i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2,WINDOW_HEIGHT,-i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2,0);//axe x negatif
            SDL_RenderDrawLine(renderer,0,i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2,WINDOW_WIDTH,i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2);//axe y negatif
            SDL_RenderDrawLine(renderer,0,i* *RESIZER_MULTIPLIER,WINDOW_WIDTH,i* *RESIZER_MULTIPLIER);//axe y positif
        }
}

void drawGrid(SDL_Renderer* renderer)
{
    float centerCoordX=WINDOW_WIDTH/2;
    float centerCoordY=WINDOW_HEIGHT/2;
    float GridBarCounts=(WINDOW_WIDTH-centerCoordX)/ *RESIZER_MULTIPLIER;
    int i;
    for(i=0;i<GridBarCounts;i++){
            SDL_RenderDrawLine(renderer,i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2,(-*RESIZER_MULTIPLIER/10)+centerCoordY,i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2,( *RESIZER_MULTIPLIER/10)+centerCoordY);//axe x positif
            SDL_RenderDrawLine(renderer,i* *RESIZER_MULTIPLIER,(- *RESIZER_MULTIPLIER/10)+centerCoordY,i* *RESIZER_MULTIPLIER,(*RESIZER_MULTIPLIER/10)+centerCoordY);// axe x negatif
            SDL_RenderDrawLine(renderer,-1*(*RESIZER_MULTIPLIER/10)+centerCoordX,i* *RESIZER_MULTIPLIER,1*(*RESIZER_MULTIPLIER/10)+centerCoordX,i* *RESIZER_MULTIPLIER);
            SDL_RenderDrawLine(renderer,-1*(*RESIZER_MULTIPLIER/10)+centerCoordX,i* *RESIZER_MULTIPLIER+centerCoordY,1*(*RESIZER_MULTIPLIER/10)+centerCoordX,i* *RESIZER_MULTIPLIER+centerCoordY);
        }
}

void drawCurv2(SDL_Renderer* renderer,float point[3][NBPOINTS], SDL_Window* screen)
{
    int i;
    for(i=0;i<NBPOINTS;i++){
            SDL_RenderDrawPoint(renderer,(point[0][i] * *RESIZER_MULTIPLIER)+WINDOW_WIDTH/2,point[1][i]* *RESIZER_MULTIPLIER+(SDL_GetWindowSurface(screen)->h)/2);
        }
}
void drawCurv2Neg(SDL_Renderer* renderer,float points[3][NBPOINTS], SDL_Window* screen)
{
    int i;
    for(i=0;i>=-NBPOINTS;i--){
        SDL_RenderDrawPoint(renderer,(points[0][-i] * *RESIZER_MULTIPLIER)+WINDOW_WIDTH/2,points[1][-i]* *RESIZER_MULTIPLIER+(SDL_GetWindowSurface(screen)->h)/2);
    }

}

void drawEverything2(SDL_Renderer* renderer, SDL_Window* screen,float point[3][NBPOINTS],float points[3][NBPOINTS] )
{
    fillColor(renderer);
    drawAxes(renderer,screen);
    drawGrid(renderer);
    drawCurv2(renderer,point,screen);
    drawCurv2Neg(renderer,points,screen);
}

void resetRenderer(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void nextZoomLevel(int Resize_index)
{
    *RESIZER_MULTIPLIER=RESIZER_MULTIPLIER[Resize_index];
}
void nextStep(int step_index)
{
    *MOVE_LENGTHX=MOVE_LENGTHX[step_index];
}

void handleKeys(SDL_Event* event)
{
    int step_index=0;
    switch(event->type){
        case SDL_KEYDOWN:
            if(event->key.keysym.sym==SDLK_LEFT){
                printf("GFDGFGFD \n");
                step_index++;
                nextStep(step_index);
            }
            break;
            }
}

void tracer(Tree *arbre){
    //float points[NBPOINTS];
    float pointResult[3][NBPOINTS];
    float pointResultNeg[3][NBPOINTS];
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* screen = SDL_CreateWindow("Drawn function", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_HEIGHT, WINDOW_WIDTH, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer=SDL_CreateRenderer(screen,-1,0);
    int clicked=0;
    int repeat=0;
    int displayed=0;
    int Resize_index=0;
    SDL_Event event;
    while(!repeat){
        SDL_PollEvent(&event);
        handleKeys(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                repeat=1;
                break;
        }
        if(displayed==0){
            drawTransGrid(renderer);
            drawEverything2(renderer,screen,pointResult,pointResultNeg);
            point(arbre,pointResult);
            pointNeg(arbre,pointResultNeg);
            displayed=1;
        }
        if(SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
            clicked=1;
        if(clicked && displayed){
            nextZoomLevel(Resize_index);
            drawEverything2(renderer,screen,pointResult,pointResultNeg);
            resetRenderer(renderer);
            displayed=0;
            clicked=0;
            Resize_index++;
            if(Resize_index==4)
            Resize_index=0;
            SDL_Delay(200);
            }
        SDL_RenderPresent(renderer);
        }
    SDL_DestroyWindow(screen);

}

/*int main(int argc, char *argv[])
{
    float points[NBPOINTS];
    float pointResult[3][NBPOINTS];
    float pointResultNeg[3][NBPOINTS];
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* screen = SDL_CreateWindow("Drawn function", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_HEIGHT, WINDOW_WIDTH, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer=SDL_CreateRenderer(screen,-1,0);
    int clicked=0;
    int repeat=0;
    int displayed=0;
    int Resize_index=0;
    SDL_Event event;
    while(!repeat){
        SDL_PollEvent(&event);
        handleKeys(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                repeat=1;
                break;
        }
        if(displayed==0){
            drawTransGrid(renderer);
            drawEverything2(renderer,screen,pointResult,pointResultNeg);
            point(pointResult);
            pointNeg(pointResultNeg);
            displayed=1;
        }
        if(SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
            clicked=1;
        if(clicked && displayed){
            nextZoomLevel(Resize_index);
            drawEverything2(renderer,screen,pointResult,pointResultNeg);
            resetRenderer(renderer);
            displayed=0;
            clicked=0;
            Resize_index++;
            if(Resize_index==4)
            Resize_index=0;
            Sleep(200);
            }
        SDL_RenderPresent(renderer);
        }
    SDL_DestroyWindow(screen);
    return 0;
}*/
