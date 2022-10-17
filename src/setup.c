#include "stdio.h"
#include "stdlib.h"
#include "SDL.h"
#include "SDL2_gfx-1.0.1/SDL2_gfxPrimitives.h"

#include "wall.h"
#include "setup.h"

// SETUP MAZE
// You can create your own maze here. line of code is adding a wall.
// You describe position of top left corner of wall (x, y), then width and height going down/to right
// Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
// But you can use absolute positions. 10 is used as the width, but you can change this.

void setup_maze(struct Wall_collection **head, int number){
    //Function that sets up the maze
    //The maze setup can be changed depending on preferences
    //Hard-Code in the various mazes here since reading off the files in the maze folder doesnt work
    //C is not an interpreted language
    switch (number){

        case 1:
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
            insertAndSetFirstWall(head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
            insertAndSetFirstWall(head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
            insertAndSetFirstWall(head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 150, 10);
            insertAndSetFirstWall(head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
            insertAndSetFirstWall(head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
            insertAndSetFirstWall(head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 450, 10);
            insertAndSetFirstWall(head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 250, 10);
            insertAndSetFirstWall(head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
            insertAndSetFirstWall(head, 10,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-100, 10, 300);
            insertAndSetFirstWall(head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
            insertAndSetFirstWall(head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);
        break;
        case 2:
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH/1.50-100, 275, 10, OVERALL_WINDOW_HEIGHT);
            insertAndSetFirstWall(head, 2,  OVERALL_WINDOW_WIDTH/1.25-100, 350, 10, OVERALL_WINDOW_HEIGHT);
            insertAndSetFirstWall(head, 4,  OVERALL_WINDOW_WIDTH/2.25-100, 200, 10, OVERALL_WINDOW_HEIGHT);
            insertAndSetFirstWall(head, 5, 415, 350, 150, 10);
            insertAndSetFirstWall(head, 6, 260, 275, 220, 10);
            insertAndSetFirstWall(head, 7, 560, 60, 10, 300);
            insertAndSetFirstWall(head, 8, 50, 60, 10, 300);
            insertAndSetFirstWall(head, 9, 560, 60, 10, 300);
            insertAndSetFirstWall(head, 10, 475, 135, 10, 150);
            insertAndSetFirstWall(head, 11, 50, 60, 520, 10);
            insertAndSetFirstWall(head, 11, 125, 135, 350, 10);
            insertAndSetFirstWall(head, 10, 125, 135, 10, 150);
            insertAndSetFirstWall(head, 5, 60, 350, 125, 10);
            insertAndSetFirstWall(head, 5, 185, 200, 200, 10);
        break;

    }
}