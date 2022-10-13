#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"
#include "SDL2/SDL.h"
#include "SDL2_gfx-1.0.1/SDL2_gfxPrimitives.h"

#include "structures.h"

void wallSetPosition(struct Wall * wall, int x, int y, int width, int height);
void wallUpdate(SDL_Renderer * renderer, struct Wall * wall);

void insertFirstWall(struct Wall_collection ** head, int key, struct Wall * wall);
void insertAndSetFirstWall(struct Wall_collection ** head, int key, int x, int y, int width, int height);
void updateAllWalls(struct Wall_collection * head, SDL_Renderer * renderer);
#endif // WALL_H_INCLUDED
