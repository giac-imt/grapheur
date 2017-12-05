#include "eval.h"

#include <SDL2\SDL.h>

#define NBPOINTS 5000
#define PRECISION 100.0
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 600

void fillColor(SDL_Renderer* renderer);
void drawAxes(SDL_Renderer* renderer, SDL_Window *screen);
void drawTransGrid(SDL_Renderer* renderer);
void drawGrid(SDL_Renderer* renderer);
void drawCurv2(SDL_Renderer* renderer,float point[3][NBPOINTS], SDL_Window* screen);
void drawCurv2Neg(SDL_Renderer* renderer,float points[3][NBPOINTS], SDL_Window* screen);
void drawEverything2(SDL_Renderer* renderer, SDL_Window* screen,float point[3][NBPOINTS],float points[3][NBPOINTS] );
void resetRenderer(SDL_Renderer* renderer);
void nextZoomLevel(int Resize_index);
void nextStep(int step_index);
void handleKeys(SDL_Event* event,SDL_Renderer *renderer,SDL_Window* screen,float point[3][NBPOINTS],float points[3][NBPOINTS]);
