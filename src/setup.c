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
        case 3:
        {
            int i, a, b, c, d, e, f, g, h, k, l;
            double j;
            a = 40;
            b = 30;
            c = 6;
            d = 3;
            e = 90;
            f = 140;
            g = b;
            h = c;
            k = d;
            l = e;
            int name_index = 0;

            for (i = 0; i < 500; i++ ) {
                j = i;
                insertAndSetFirstWall(head, name_index++,a + b*sin(c*j * M_PI/180),(i * d)+e,8, 8);
                insertAndSetFirstWall(head, name_index++,f + g*sin(h*j * M_PI/180),(i * k)+l,8, 8);
            }

            insertAndSetFirstWall(head, 1, 40, 20, 8, 80);
            insertAndSetFirstWall(head, 1, 40, 20, 550, 8);
            insertAndSetFirstWall(head, 1, 590, 20, 8, 450);
            insertAndSetFirstWall(head, 1, 280, 460, 310, 8);
            insertAndSetFirstWall(head, 1, 150, 460, 60, 8);
            insertAndSetFirstWall(head, 1, 215, 90, 80, 8);
            insertAndSetFirstWall(head, 1, 120, 380, 95, 8);
            insertAndSetFirstWall(head, 2, 375, 90, 145, 8);
            insertAndSetFirstWall(head, 2, 520, 90, 8, 145);
            insertAndSetFirstWall(head, 2, 445, 400, 75, 8);
            insertAndSetFirstWall(head, 2, 515, 335, 8, 75);


            for (j = 0; j < 135; j++) {
                insertAndSetFirstWall(head, 1, 145+j, 90+j, 8, 8);
                insertAndSetFirstWall(head, 2, 280-j, 225+j, 8, 8);
            }

            for (j=0; j < 145; j++) {
                insertAndSetFirstWall(head, 1, 215+j, 90+j, 8, 8);
                insertAndSetFirstWall(head, 2, 355-j, 235+j, 8, 8);
                insertAndSetFirstWall(head, 1, 295+j, 90+j, 8, 8);
                insertAndSetFirstWall(head, 2, 445-j, 235+j, 8, 8);
                insertAndSetFirstWall(head, 1, 375+j, 90+j, 8, 8);
            }

            for (j=0; j<65;j++) {
                insertAndSetFirstWall(head, 2, 520+j, 90-j, 8, 8);
                insertAndSetFirstWall(head, 2, 445+j, 400-j, 8, 8);
                insertAndSetFirstWall(head, 2, 520+j, 400+j, 8, 8);
            }
        break;
        }
        case 4:

        insertAndSetFirstWall(head, 1, 50, 50, 5, 450);
        insertAndSetFirstWall(head, 2, 150, 150, 5, 350);
        insertAndSetFirstWall(head, 3, 50, 45, OVERALL_WINDOW_WIDTH-50, 5);
        insertAndSetFirstWall(head, 4, 250, 45, 5, 350);
        insertAndSetFirstWall(head, 5, 150, 470, 200, 5);
        insertAndSetFirstWall(head, 6, 350, 150, 5, 350);
        insertAndSetFirstWall(head, 7, 450, 45, 5, 350);
        insertAndSetFirstWall(head, 8, 350, 470, 200, 5);
        insertAndSetFirstWall(head, 9, 550, 150, 5, 350);
        insertAndSetFirstWall(head, 10, 550, 150, OVERALL_WINDOW_WIDTH-550, 5);

        break;

        case 5:
            //Dead end maze.txt
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2+150, 10, OVERALL_WINDOW_HEIGHT/2-150);
            insertAndSetFirstWall(head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+150, 10, OVERALL_WINDOW_HEIGHT/2-150);
            insertAndSetFirstWall(head, 3,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2+150, 100, 10);
            insertAndSetFirstWall(head, 4,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2+150, 250, 10);
            insertAndSetFirstWall(head, 5,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2+100, 400, 10);
            insertAndSetFirstWall(head, 6,  OVERALL_WINDOW_WIDTH/2+250, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-180);
            insertAndSetFirstWall(head, 7,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2-60, 10, OVERALL_WINDOW_HEIGHT/2-20);
            insertAndSetFirstWall(head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2+20, 10, OVERALL_WINDOW_HEIGHT/2-150);
            insertAndSetFirstWall(head, 9,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2+20, 400, 10);
            insertAndSetFirstWall(head, 10,  OVERALL_WINDOW_WIDTH/2+250, OVERALL_WINDOW_HEIGHT/2-210, 10, OVERALL_WINDOW_HEIGHT/2);
            insertAndSetFirstWall(head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-210, 150, 10);
            insertAndSetFirstWall(head, 12,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2-60, 400, 10);
            insertAndSetFirstWall(head, 13,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-210, 10, OVERALL_WINDOW_HEIGHT/2-150);
            insertAndSetFirstWall(head, 14,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-130, 100, 10);
            insertAndSetFirstWall(head, 15,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-130, 10, 30);
            insertAndSetFirstWall(head, 16,  OVERALL_WINDOW_WIDTH/2-50, OVERALL_WINDOW_HEIGHT/2-110, 250, 10);
            insertAndSetFirstWall(head, 17,  OVERALL_WINDOW_WIDTH/2-50, OVERALL_WINDOW_HEIGHT/2-190, 10, OVERALL_WINDOW_HEIGHT/2-150);
            insertAndSetFirstWall(head, 18,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-150, 10, OVERALL_WINDOW_HEIGHT/2-150);
            insertAndSetFirstWall(head, 19,  OVERALL_WINDOW_WIDTH/2-350, OVERALL_WINDOW_HEIGHT/2-200, 310, 10);
            insertAndSetFirstWall(head, 20,  OVERALL_WINDOW_WIDTH/2-350, OVERALL_WINDOW_HEIGHT/2-150, 210, 10);    

        break;

        case 6:
            //delaymap.txt
            //replace robot->true_x = 50; and robot->true_y = OVERALL_WINDOW_HEIGHT-50;

            insertAndSetFirstWall(head, 1,  0, 0, 10, OVERALL_WINDOW_HEIGHT); 
            insertAndSetFirstWall(head, 2,  100,  100, 10, OVERALL_WINDOW_HEIGHT-100); 
            insertAndSetFirstWall(head, 3,  0, 0, OVERALL_WINDOW_WIDTH, 10); // top wall
            insertAndSetFirstWall(head, 4,  200, 0, 10, OVERALL_WINDOW_HEIGHT-100);
            insertAndSetFirstWall(head, 5,  100, OVERALL_WINDOW_HEIGHT-10, OVERALL_WINDOW_WIDTH, 10); 
            insertAndSetFirstWall(head, 6,  300,  100, 10, OVERALL_WINDOW_HEIGHT-100);
            insertAndSetFirstWall(head, 7,  400, 0, 10, OVERALL_WINDOW_HEIGHT-100);
            insertAndSetFirstWall(head, 8,  500,  100, 10, OVERALL_WINDOW_HEIGHT-100);
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH - 10, 0, 10, OVERALL_WINDOW_HEIGHT-100);

        break;

        case 7:
        {
            //Diagonal turns
            float aa, bb;
            int name_index = 0;
            int a = 325;
            aa = 0.5;
            bb = 1;
            int c = 180;
            //int d = 1;
            int e = a+100;
            int f = c;
            c += 50;
            int m = 200;
            for (int i = 0; i < m; i++){
                if (i < 150) {
                    insertAndSetFirstWall(head, name_index++,  a - i*aa , c + i*bb, 10, 10);
                }
                insertAndSetFirstWall(head, name_index++,  e - i*aa , f + i*bb, 10, 10);
            }
            insertAndSetFirstWall(head, name_index++, c-m*bb, a-150, 1000, 10);
            insertAndSetFirstWall(head, name_index++, c-m*bb, a-100, 305, 10);
            insertAndSetFirstWall(head, name_index++,  a - (m-50)*aa , c + (m-50)*bb, 10, 200);
            insertAndSetFirstWall(head, name_index++,  e - m*aa , f + m*bb, 10, 200);
        }
        break;

        case 8:
            //ELEC 1601 maze
            insertAndSetFirstWall(head, 5,  225, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2 - 60);
            insertAndSetFirstWall(head, 5,  325, OVERALL_WINDOW_HEIGHT/2 - 40, 10, OVERALL_WINDOW_HEIGHT/2);
            insertAndSetFirstWall(head, 5,  400, OVERALL_WINDOW_HEIGHT/2, OVERALL_WINDOW_WIDTH/2- 70, 10);
            insertAndSetFirstWall(head, 5,  100, OVERALL_WINDOW_HEIGHT/2, OVERALL_WINDOW_WIDTH/3 - 135, 10);
            insertAndSetFirstWall(head, 5,  150, OVERALL_WINDOW_HEIGHT/2 + 100, OVERALL_WINDOW_WIDTH/3 - 135, 10);
            insertAndSetFirstWall(head, 1,  100, OVERALL_WINDOW_HEIGHT/2+230, OVERALL_WINDOW_WIDTH/2 - 10, 10);
            insertAndSetFirstWall(head, 5,  100, OVERALL_WINDOW_HEIGHT/2 - 100, 10, OVERALL_WINDOW_HEIGHT);
            insertAndSetFirstWall(head, 1,  100, OVERALL_WINDOW_HEIGHT/2 - 100, OVERALL_WINDOW_WIDTH/2 +300, 10);
            insertAndSetFirstWall(head, 5,  400, OVERALL_WINDOW_HEIGHT/2 + 100, 10, OVERALL_WINDOW_HEIGHT/2-100);
            insertAndSetFirstWall(head, 5,  400, OVERALL_WINDOW_HEIGHT/2 + 100, OVERALL_WINDOW_WIDTH/2- 70, 10);

        break;

        case 9:
            //Maze with lots of dead ends
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2+150, 10, OVERALL_WINDOW_HEIGHT/2-150);
            insertAndSetFirstWall(head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+150, 10, OVERALL_WINDOW_HEIGHT/2-150);
            insertAndSetFirstWall(head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+150, 150, 10);
            insertAndSetFirstWall(head, 4,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2+150, 250, 10);
            insertAndSetFirstWall(head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+50, 400, 10);
            insertAndSetFirstWall(head, 6,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+50, 10, OVERALL_WINDOW_HEIGHT/2-140);
            insertAndSetFirstWall(head, 7,  OVERALL_WINDOW_WIDTH/2+150, OVERALL_WINDOW_HEIGHT/2-30, 10, OVERALL_WINDOW_HEIGHT/2-150);
            insertAndSetFirstWall(head, 8,  OVERALL_WINDOW_WIDTH/2+250, OVERALL_WINDOW_HEIGHT/2-220, 10, OVERALL_WINDOW_HEIGHT/2+140);
            insertAndSetFirstWall(head, 9,  OVERALL_WINDOW_WIDTH/2+150, OVERALL_WINDOW_HEIGHT/2-220, 10, OVERALL_WINDOW_HEIGHT/2-140);
            insertAndSetFirstWall(head, 10,  OVERALL_WINDOW_WIDTH/2+150, OVERALL_WINDOW_HEIGHT/2-220, 100, 10);
            insertAndSetFirstWall(head, 11,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-40, 410, 10);
            insertAndSetFirstWall(head, 12,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-120, 220, 10);
            insertAndSetFirstWall(head, 13,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-120, 10, OVERALL_WINDOW_HEIGHT/2-150);
            insertAndSetFirstWall(head, 14,  OVERALL_WINDOW_WIDTH/2+30, OVERALL_WINDOW_HEIGHT/2-120, 130,10);
            insertAndSetFirstWall(head, 15,  OVERALL_WINDOW_WIDTH/2+30, OVERALL_WINDOW_HEIGHT/2-240, 10,OVERALL_WINDOW_HEIGHT/2-120);
            insertAndSetFirstWall(head, 15,  OVERALL_WINDOW_WIDTH/2-40, OVERALL_WINDOW_HEIGHT/2-240, 10,OVERALL_WINDOW_HEIGHT/2-120);
        break;

        case 10:
        {
            //maze.txt
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH/2 - 100, OVERALL_WINDOW_HEIGHT/2+10, 10, OVERALL_WINDOW_HEIGHT/2);
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2+150, 10, OVERALL_WINDOW_HEIGHT/2);
            for (int i = 0; i < 130; i++){

                insertAndSetFirstWall(head, 1,  320- i*0.75 , 255 + i, 10, 10);
            }
            for (int i = 0; i < 60; i++){
                insertAndSetFirstWall(head, 1,  365 - i*0.75 , 325 + i, 10, 10);
            }
            insertAndSetFirstWall(head, 2,  OVERALL_WINDOW_WIDTH/2-90, OVERALL_WINDOW_HEIGHT/2+10, OVERALL_WINDOW_WIDTH/2-30, 10);
            insertAndSetFirstWall(head, 2,  OVERALL_WINDOW_WIDTH/2+50, OVERALL_WINDOW_HEIGHT/2 +80, OVERALL_WINDOW_WIDTH/2-260, 10);
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH/2 +100, OVERALL_WINDOW_HEIGHT/2+85, 10, OVERALL_WINDOW_HEIGHT/2-85);
            insertAndSetFirstWall(head, 2,  OVERALL_WINDOW_WIDTH/2+110, OVERALL_WINDOW_HEIGHT/2+230, OVERALL_WINDOW_WIDTH/2-100, 10);
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH/2 +310, OVERALL_WINDOW_HEIGHT/2-200, 10, OVERALL_WINDOW_HEIGHT/2+200);
            insertAndSetFirstWall(head, 2,  OVERALL_WINDOW_WIDTH/2-195, OVERALL_WINDOW_HEIGHT/2-80, OVERALL_WINDOW_WIDTH/2+85, 10);
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH/2 +200, OVERALL_WINDOW_HEIGHT/2-200, 10, OVERALL_WINDOW_HEIGHT/2-115);
            insertAndSetFirstWall(head, 2,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, OVERALL_WINDOW_WIDTH/2-100, 10);
            for (int i = 0; i < 75; i++){
                insertAndSetFirstWall(head, 1 ,120 + 20*sin(10*i * M_PI/180),(i * 3)+160,10, 10);

            }
            for (int i = 0; i < 45; i++){
                insertAndSetFirstWall(head, 1 ,520 + 20*sin(10*i * M_PI/180),(i * 3)+250,10, 10);

            }
            insertAndSetFirstWall(head, 2,  OVERALL_WINDOW_WIDTH/2-320, OVERALL_WINDOW_HEIGHT/2+230, OVERALL_WINDOW_WIDTH/2-100, 10);
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH/2-320, OVERALL_WINDOW_HEIGHT/2-200, 10, OVERALL_WINDOW_HEIGHT/2+200);
            insertAndSetFirstWall(head, 2,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2-200, OVERALL_WINDOW_WIDTH/2-50, 10);
            insertAndSetFirstWall(head, 2,  OVERALL_WINDOW_WIDTH/2-320, OVERALL_WINDOW_HEIGHT/2-200, OVERALL_WINDOW_WIDTH/2-90, 10);
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH/2 - 100, OVERALL_WINDOW_HEIGHT/2-440, 10, OVERALL_WINDOW_HEIGHT/2);
            insertAndSetFirstWall(head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2-440, 10, OVERALL_WINDOW_HEIGHT/2);
        }
        break;

        case 11:
           { //steep curve.txt
            int i, a, b, c, d, e, f, g, h, k, l, m;
            double j;
            a = 300;
            b = 40;
            c = 10;
            d = 3;
            e = 90;
            f = 200;
            g = b;
            h = c;
            k = d;
            l = e;
            m = 500;
            int name_index = 0;
            for (i = 0; i < m; i++){
                j = i;
                insertAndSetFirstWall(head, name_index++,
                                        a + b*sin(c*j * M_PI/180),
                                        (i * d)+e,
                                        10, 10);
                insertAndSetFirstWall(head, name_index++,
                                        f + g*sin(h*j * M_PI/180),
                                        (i * k)+l,
                                        10, 10);
            }
           }
        break;
        case 12: {
            insertAndSetFirstWall(head, 1,  0, 20, 10, OVERALL_WINDOW_HEIGHT);
            insertAndSetFirstWall(head, 2,  80, 20, 10, OVERALL_WINDOW_HEIGHT/2);
            insertAndSetFirstWall(head, 3,  OVERALL_WINDOW_WIDTH/2-330, OVERALL_WINDOW_HEIGHT/2 + 80, 150, 10);
            insertAndSetFirstWall(head, 4,  OVERALL_WINDOW_WIDTH/2-240, OVERALL_WINDOW_HEIGHT/2, 150, 10);
            insertAndSetFirstWall(head, 5,  600, 0, 10, OVERALL_WINDOW_HEIGHT);
            insertAndSetFirstWall(head, 6,  OVERALL_WINDOW_WIDTH/2-240, OVERALL_WINDOW_HEIGHT/2-200, 520, 10);
            insertAndSetFirstWall(head, 7,  0, 460, 220, 10);
            insertAndSetFirstWall(head, 8,  300, 460, 300, 10);
            insertAndSetFirstWall(head, 9,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
            insertAndSetFirstWall(head, 10,  300, 400, 10, 100);
            insertAndSetFirstWall(head, 11,  210, 340, 10, 130);
            insertAndSetFirstWall(head, 12,  470, 150, 10, 110);
            insertAndSetFirstWall(head, 13,  470, 200, 130, 10);
            insertAndSetFirstWall(head, 14,  210, 330, 130, 10);
            insertAndSetFirstWall(head, 15,  335, 240, 10, 100);
            insertAndSetFirstWall(head, 16,  300, 175, 100, 10);
        }
        break;

        case 13: {
            insertAndSetFirstWall(head, 1,  30, 75, 10, OVERALL_WINDOW_HEIGHT-30);
            insertAndSetFirstWall(head, 2,  30, 75, 500, 10);
            insertAndSetFirstWall(head, 3,  OVERALL_WINDOW_WIDTH/3+250, 0, 10, 85);
            insertAndSetFirstWall(head, 4,  440, 350, 10, 200);
            insertAndSetFirstWall(head, 5,  100, 350, 503, 10);
            insertAndSetFirstWall(head, 6,  OVERALL_WINDOW_WIDTH/3+380, 0, 10, OVERALL_WINDOW_HEIGHT-130);
            insertAndSetFirstWall(head, 7,  170, 175, 300, 10);
            insertAndSetFirstWall(head, 8,  OVERALL_WINDOW_WIDTH/3+100, 175, 10, 75);
            insertAndSetFirstWall(head, 9,  OVERALL_WINDOW_WIDTH/3+100, 250, 160, 10);
            insertAndSetFirstWall(head, 10,  OVERALL_WINDOW_WIDTH/3+250, 175, 10, 85);
            insertAndSetFirstWall(head, 11,  30, 400, 290, 10);
            insertAndSetFirstWall(head, 12,  100, 300, 290, 10);
            insertAndSetFirstWall(head, 13,  100, 300, 10, 60);
            insertAndSetFirstWall(head, 14,  380, 250, 10, 60);
            insertAndSetFirstWall(head, 15,  100, 80, 10, 150);
            insertAndSetFirstWall(head, 16,  100, 230, 130, 10);
            insertAndSetFirstWall(head, 17,  525, 75, 10, 200);
            insertAndSetFirstWall(head, 18,  90, 470, 360, 10);
        }
        break;

        default:
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
    }
}