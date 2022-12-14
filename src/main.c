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

        //Setup maze
        setup_maze(&head, maze_number);
        //memset(&robot, 0, sizeof(robot));
        setup_robot(&robot, maze_number);
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
        if (maze_number == 14)
            result = checkRobotReachedEnd(&robot, 0, 20, 50, 60);
        else if (maze_number == 15)
            result = checkRobotReachedEnd(&robot, 0, 340, 50, 100);
        else
            result = checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT/2+100, 10, 100);

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
                setup_robot(&robot, maze_number);
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
