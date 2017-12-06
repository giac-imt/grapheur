#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2\SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>



int RESIZER_MULTIPLIER[4] = {10,50,100,150}; // proposer 10 50 100 150 (au hasard)
int MOVE_LENGTHX[2] = {0,20}; // Quantite de mouvement a effectuer lors de l'appui
int MOVE_LENGTHY[2] = {0,20};
int AXES_LENGTH=2000;
int DEPLACEMENT_Y=0;
int GRADU_MULTIPLIER=100;


float *point(Tree *arbre,float pointResult[3][NBPOINTS])
{
    int j;
    for(j=0;j<NBPOINTS;j++){
        if(Eval(arbre,j/PRECISION).err.code!=310){
            pointResult[0][j]=(j/PRECISION);
            pointResult[1][j]=-Eval(arbre,j/PRECISION).value +*MOVE_LENGTHY;
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
    SDL_RenderDrawLine(renderer,0+ *MOVE_LENGTHY -AXES_LENGTH , WINDOW_WIDTH/2 + *MOVE_LENGTHX , SDL_GetWindowSurface(screen)->w + *MOVE_LENGTHY +AXES_LENGTH, WINDOW_HEIGHT/2 + *MOVE_LENGTHX);//axe vertical
    SDL_RenderDrawLine(renderer,WINDOW_HEIGHT/2 +DEPLACEMENT_Y,0 + *MOVE_LENGTHX-AXES_LENGTH,WINDOW_WIDTH/2 +DEPLACEMENT_Y,SDL_GetWindowSurface(screen)->h + *MOVE_LENGTHX +AXES_LENGTH); //axe horizontal
}
void drawTransGrid(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,30,30,30,255);
    float centerCoordX=WINDOW_WIDTH/2;
    float GridBarCounts=(WINDOW_WIDTH-centerCoordX)/ *RESIZER_MULTIPLIER;
    int i;
    for(i=-AXES_LENGTH/2;i<GridBarCounts*40;i++){
            SDL_RenderDrawLine(renderer,i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2+ *MOVE_LENGTHY +DEPLACEMENT_Y,WINDOW_HEIGHT + *MOVE_LENGTHX +AXES_LENGTH,i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2 + *MOVE_LENGTHY +DEPLACEMENT_Y,0 + *MOVE_LENGTHX -AXES_LENGTH);//axe x positif
            SDL_RenderDrawLine(renderer,-i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2+ *MOVE_LENGTHY +DEPLACEMENT_Y ,WINDOW_HEIGHT + *MOVE_LENGTHX+AXES_LENGTH,-i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2+ *MOVE_LENGTHY +DEPLACEMENT_Y,0+ *MOVE_LENGTHX -AXES_LENGTH);//axe x negatif
            SDL_RenderDrawLine(renderer,0+ *MOVE_LENGTHY +DEPLACEMENT_Y -AXES_LENGTH,i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2+ *MOVE_LENGTHX  ,WINDOW_WIDTH + *MOVE_LENGTHY +DEPLACEMENT_Y,i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2+ *MOVE_LENGTHX);//axe y negatif
            SDL_RenderDrawLine(renderer,0+*MOVE_LENGTHY  +DEPLACEMENT_Y -AXES_LENGTH, i* *RESIZER_MULTIPLIER+ *MOVE_LENGTHX ,WINDOW_WIDTH + *MOVE_LENGTHY  +DEPLACEMENT_Y +AXES_LENGTH,i* *RESIZER_MULTIPLIER+ *MOVE_LENGTHX );//axe y positif
        }
}

void drawGrid(SDL_Renderer* renderer)
{
    float centerCoordX=WINDOW_WIDTH/2;
    float centerCoordY=WINDOW_HEIGHT/2;
    float GridBarCounts=(WINDOW_WIDTH-centerCoordX)/ *RESIZER_MULTIPLIER;
    int i;
    for(i=-AXES_LENGTH/2;i<GridBarCounts*GRADU_MULTIPLIER;i++){
            SDL_RenderDrawLine(renderer,i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2 + *MOVE_LENGTHY +DEPLACEMENT_Y ,(-*RESIZER_MULTIPLIER/10)+centerCoordY + *MOVE_LENGTHX,i* *RESIZER_MULTIPLIER+WINDOW_WIDTH/2 + *MOVE_LENGTHY +DEPLACEMENT_Y,( *RESIZER_MULTIPLIER/10)+centerCoordY+ *MOVE_LENGTHX );//axe x positif
            SDL_RenderDrawLine(renderer,i* *RESIZER_MULTIPLIER + *MOVE_LENGTHY +DEPLACEMENT_Y,(- *RESIZER_MULTIPLIER/10)+centerCoordY + *MOVE_LENGTHX,i* *RESIZER_MULTIPLIER + *MOVE_LENGTHY +DEPLACEMENT_Y,(*RESIZER_MULTIPLIER/10)+centerCoordY + *MOVE_LENGTHX);// axe x negatif
            SDL_RenderDrawLine(renderer,-1*(*RESIZER_MULTIPLIER/10)+centerCoordX + *MOVE_LENGTHY +DEPLACEMENT_Y,i* *RESIZER_MULTIPLIER + *MOVE_LENGTHX,1*(*RESIZER_MULTIPLIER/10)+centerCoordX + *MOVE_LENGTHY +DEPLACEMENT_Y,i* *RESIZER_MULTIPLIER + *MOVE_LENGTHX );
            SDL_RenderDrawLine(renderer,-1*(*RESIZER_MULTIPLIER/10)+centerCoordX + *MOVE_LENGTHY +DEPLACEMENT_Y,i* *RESIZER_MULTIPLIER+centerCoordY + *MOVE_LENGTHX,1*(*RESIZER_MULTIPLIER/10)+centerCoordX + *MOVE_LENGTHY +DEPLACEMENT_Y,i* *RESIZER_MULTIPLIER+centerCoordY + *MOVE_LENGTHX);
        }
}

void drawCurv2(SDL_Renderer* renderer,float point[3][NBPOINTS], SDL_Window* screen)
{
    int i;
    for(i=0;i<NBPOINTS;i++){
                SDL_SetRenderDrawColor(renderer,255,0,0,SDL_ALPHA_OPAQUE);
                SDL_RenderDrawPoint(renderer,(point[0][i] * *RESIZER_MULTIPLIER)+WINDOW_WIDTH/2+ *MOVE_LENGTHY +DEPLACEMENT_Y,point[1][i]* *RESIZER_MULTIPLIER+(SDL_GetWindowSurface(screen)->h)/2 + *MOVE_LENGTHX);
            }

}
void drawCurv2Neg(SDL_Renderer* renderer,float points[3][NBPOINTS], SDL_Window* screen)
{
    int i;
    for(i=0;i>=-NBPOINTS;i--){
        SDL_RenderDrawPoint(renderer,(points[0][-i] * *RESIZER_MULTIPLIER)+WINDOW_WIDTH/2 + *MOVE_LENGTHY +DEPLACEMENT_Y,points[1][-i]* *RESIZER_MULTIPLIER+(SDL_GetWindowSurface(screen)->h)/2 + *MOVE_LENGTHX);
    }

}


void drawEverything2(SDL_Renderer* renderer, SDL_Window* screen,float point[3][NBPOINTS],float points[3][NBPOINTS] )
{
    //drawTransGrid(renderer);
    fillColor(renderer);
    drawAxes(renderer,screen);

    drawGrid(renderer);
    //SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
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

void handleKeys(SDL_Event* event,SDL_Renderer *renderer,SDL_Window* screen,float point[3][NBPOINTS],float points[3][NBPOINTS])
{
    int step_index=0;
    switch(event->type){
        case SDL_KEYDOWN:
            if(event->key.keysym.sym==SDLK_DOWN){
                step_index++;
                nextStep(step_index);
                MOVE_LENGTHY[1]+=10;
                MOVE_LENGTHX[1]+=10;
                //SDL_Delay(20);
                resetRenderer(renderer);
                drawTransGrid(renderer);
                drawEverything2(renderer,screen,point,points);
                SDL_Delay(1);
                SDL_RenderPresent(renderer);
            }
            if(event->key.keysym.sym==SDLK_UP){
                step_index++;
                nextStep(step_index);
                MOVE_LENGTHY[1]-=10;
                MOVE_LENGTHX[1]-=10;
                //SDL_Delay(20);
                //drawEverything2(renderer,screen,point,points);
                resetRenderer(renderer);
                drawTransGrid(renderer);
                drawEverything2(renderer,screen,point,points);
                SDL_Delay(1);
                SDL_RenderPresent(renderer);
            }
            if(event->key.keysym.sym==SDLK_LEFT){
                step_index++;
                nextStep(step_index);
                DEPLACEMENT_Y+=20;
                //SDL_Delay(20);
                //drawEverything2(renderer,screen,point,points);
                resetRenderer(renderer);
                drawTransGrid(renderer);
                drawEverything2(renderer,screen,point,points);
                SDL_Delay(1);
                SDL_RenderPresent(renderer);
            }
            if(event->key.keysym.sym==SDLK_RIGHT){
                step_index++;
                nextStep(step_index);
                DEPLACEMENT_Y-=20;
                //SDL_Delay(20);
                //drawEverything2(renderer,screen,point,points);
                resetRenderer(renderer);
                drawTransGrid(renderer);
                drawEverything2(renderer,screen,point,points);
                SDL_Delay(1);
                SDL_RenderPresent(renderer);
            }
            break;
    }
    //drawEverything2(renderer,screen,pointResult,pointResultNeg);
    //return 0;
}

void tracer(Tree *arbre){
    /*TTF_Init();
    TTF_Font *police = NULL;
    SDL_Surface *texte=NULL;
    SDL_Color color = {0, 0, 0};
    texte=TTF_OpenFont("C:\\Users\\Florent\\Desktop\\Projet_integre\\grapheur-master\\bin\\Debug\\impact.ttf", 10);
    texte = TTF_RenderText_Blended(police, "Salut les Zer0s !",color);*/
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
        handleKeys(&event,renderer,screen,pointResult,pointResultNeg);
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
