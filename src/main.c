#include "stdio.h"
#include "stdlib.h"
#include "SDL.h"
#include "SDL2_gfx-1.0.1/SDL2_gfxPrimitives.h"
#include "time.h"

#include "formulas.h"
#include "wall.h"
#include "robot.h"
#include "file.h"
#include "setup.h"

int done = 0;
SDL_Window *window;
SDL_Renderer *renderer;

struct Robot robot;
struct Wall_collection *head = NULL;
int front_centre_sensor, left_sensor, right_sensor=0;
clock_t start_time, end_time;
int msec;
int crashed = 0;


//Maze Number that determines the maze used
int maze_number = 1;
const static int TOTAL_MAZES = 15;

int init() {
        if(SDL_Init(SDL_INIT_VIDEO) < 0){
            return 1;
        }
        
        window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
        renderer = SDL_CreateRenderer(window, -1, 0);
        crashed = 0;
        msec = 0;
        //front_centre_sensor = 0;
        //left_sensor = 0;
        //right_sensor = 0;
       

        //Loops the maze around if you go past the last one
        if (maze_number > TOTAL_MAZES){
            maze_number = 0;
        } else if (maze_number < 1){
            maze_number = TOTAL_MAZES;
        }

        //Setup maze - Only uncommented for testing, not comp mazes
        //setup_maze(&head, maze_number);
        //memset(&robot, 0, sizeof(robot));

        //Competition mazes:
        //Basic Maze

        insertAndSetFirstWall(head, 2,  640-10-220, 400, 10, 80);
        insertAndSetFirstWall(head, 2,  640-200-20, 400, 200, 10);
        insertAndSetFirstWall(head, 2,  640-10-20, 50, 10, 350);
        insertAndSetFirstWall(head, 2,  640-280-20, 50, 280, 10);
        insertAndSetFirstWall(head, 2,  640-10-300, 50, 10, 100);
        insertAndSetFirstWall(head, 2,  640-110-300, 150, 110, 10);
        insertAndSetFirstWall(head, 2,  640-10-400, 50, 10, 100);
        insertAndSetFirstWall(head, 2,  640-400-220, 50, 220, 10);
        insertAndSetFirstWall(head, 2,  640-10-620, 50, 10, 290);
        insertAndSetFirstWall(head, 2,  640-620-20, 340, 20, 10);


        insertAndSetFirstWall(head, 1,  640-10-320, 300, 10, 180);
        insertAndSetFirstWall(head, 2,  640-200-120, 300, 200, 10);
        insertAndSetFirstWall(head, 2,  640-10-120, 150, 10, 150);
        insertAndSetFirstWall(head, 2,  640-80-120, 150, 80, 10);
        insertAndSetFirstWall(head, 2,  640-10-200, 150, 10, 100);
        insertAndSetFirstWall(head, 2,  640-310-200, 250, 310, 10);
        insertAndSetFirstWall(head, 2,  640-10-500, 150, 10, 100);
        insertAndSetFirstWall(head, 2,  640-20-500, 150, 20, 10);
        insertAndSetFirstWall(head, 2,  640-10-520, 150, 10, 290);
        insertAndSetFirstWall(head, 2,  640-120-520, 440, 120, 10);


        //Advanced maze:

        // int i;
        // insertAndSetFirstWall(head, 12,  640-10-120, 450, 10, 30);
        // insertAndSetFirstWall(head, 12,  640-10-220, 450, 10, 30);

        // for (i = 0; i < 100; i++){
        //     insertAndSetFirstWall(head, i,  640-10-(20 + i) , 350 + i, 10, 10); //1
        //     insertAndSetFirstWall(head, i,  640-10-(20 +100 + i) , 350 + i, 10, 10); //1
        // }
        // insertAndSetFirstWall(head, 12,  640-10-20, 280, 10, 70);
        // insertAndSetFirstWall(head, 12,  640-10-120, 280, 10, 70);

        // for (i = 0; i < 180; i++){
        //     insertAndSetFirstWall(head, i,  640-10-(20 +190 - i/2) , 100 + i, 10, 10); //1
        // }
        // for (i = 0; i < 105; i++){
        //     insertAndSetFirstWall(head, i,  640-10-(20 +105/2 - i/2) , 175 + i, 10, 10); //1
        // }


        // insertAndSetFirstWall(head, 2,  640-105/2-20, 175, 105/2, 10);
        // insertAndSetFirstWall(head, 2,  640-10-20, 20, 10, 155);
        // insertAndSetFirstWall(head, 2,  640-300-20, 20, 300, 10);
        // insertAndSetFirstWall(head, 2,  640-10-320, 20, 10, 60);
        // insertAndSetFirstWall(head, 2,  640-130-80, 100, 130, 10);
        // insertAndSetFirstWall(head, 2,  640-10-80, 80, 10, 20);
        // insertAndSetFirstWall(head, 2,  640-160-80, 80, 160, 10);


        // double j;
        // for (i = 0; i < 50; i++){
        //     j = i;
        //     insertAndSetFirstWall(head, i+1,
        //                         // the most important bit is below.
        //                         // increase the 20 for a tighter bend
        //                         // descrease for a more meandering flow
        //                         640-10-(320 + 30*sin(10*j * M_PI/180)),
        //                         // increase the 5 for a spacier curve
        //                         (i * 5)+80,
        //                         10, 10);
        // }
        // for (i = 0; i < 75; i++){
        //     j = i;
        //     insertAndSetFirstWall(head, i+1,
        //                         // the most important bit is below.
        //                         // increase the 20 for a tighter bend
        //                         // descrease for a more meandering flow
        //                         640-10-(240 + 30*sin(10*j * M_PI/180)),
        //                         // increase the 5 for a spacier curve
        //                         (i * 5)+80,
        //                         10, 10);
        // }

        // insertAndSetFirstWall(head, 2,  640-105-345, 330, 105, 10);
        // insertAndSetFirstWall(head, 2,  640-10-450, 190, 10, 150);
        // insertAndSetFirstWall(head, 2,  640-70-380, 190, 70, 10);
        // insertAndSetFirstWall(head, 2,  640-10-380, 20, 10, 170);
        // insertAndSetFirstWall(head, 2,  640-260-380, 20, 260, 10);

        // insertAndSetFirstWall(head, 2,  640-345-255, 455, 345, 10);
        // insertAndSetFirstWall(head, 2,  640-10-600, 100, 10, 365);
        // insertAndSetFirstWall(head, 2,  640-70-530, 100, 70, 10);
        // insertAndSetFirstWall(head, 2,  640-10-530, 80, 10, 20);
        // insertAndSetFirstWall(head, 2,  640-110-530, 80, 110, 10);



        setup_robot(&robot);
        updateAllWalls(head, renderer);
        return 0;
    };

int main(int argc, char *argv[]) {
    
    if (init()){
        return 1;
        printf("Failed");
    };

    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        //Move robot based on user input commands/auto commands
        if (robot.auto_mode == 1)
            robotAutoMotorMove(&robot, front_centre_sensor, left_sensor, right_sensor);
        // Put an else here the auto move should be seperate
        robotMotorMove(&robot, crashed);

        int result = 0;
        
        //Basic maze:

        result = checkRobotReachedEnd(&robot, 0, 340, 50, 100);

        //Complex maze:

        //result = checkRobotReachedEnd(&robot, 0, 20, 50, 60);

        //Check if robot reaches endpoint. and check sensor values
        if (result){
            end_time = clock();
            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
            robotSuccess(&robot, msec);
        }
        else if(crashed == 1 || checkRobotHitWalls(&robot, head)){
            robotCrash(&robot);
            crashed = 1;
        }
        //Otherwise compute sensor information
        else {
            front_centre_sensor = checkRobotSensorFrontCentreAllWalls(&robot, head);
            if (front_centre_sensor>0)
                printf("Getting close on the centre. Score = %d\n", front_centre_sensor);

            left_sensor = checkRobotSensorLeftAllWalls(&robot, head);
            if (left_sensor>0)
                printf("Getting close on the left. Score = %d\n", left_sensor);

            right_sensor = checkRobotSensorRightAllWalls(&robot, head);
            if (right_sensor>0)
                printf("Getting close on the right. Score = %d\n", right_sensor);
        }
        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != BRAKE){
                robot.direction = ACCELERATE;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != ACCELERATE){
                robot.direction = BRAKE;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                start_time = clock();
            }
            if(state[SDL_SCANCODE_N]){
                maze_number++;
                memset(&head, 0, sizeof(head));
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                init();
            }
            if(state[SDL_SCANCODE_B]){
                maze_number--;
                memset(&head, 0, sizeof(head));
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                init();
            }


            //If the user wants the next map they can press b or n

        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
    return 0;
}
