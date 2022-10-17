#include "robot.h"

int firstMove = 0;
int inClockwiseTurn = 0;
int degreesLeftClockwise = 0;

int inCounterClockwiseTurn = 0;
int degreesLeftCounterClockwise = 0;

int speed = 0;

int timeOutOfRightSensor = 0; // This is used to turn the robot once it has been
// out of the right sensor for enough time to make a turn
int timeNeededOutOfSensor = 0;

void setup_robot(struct Robot *robot){
    robot -> x = OVERALL_WINDOW_WIDTH / 2 - 50;
    robot -> y = OVERALL_WINDOW_HEIGHT - 50;
    robot -> true_x = OVERALL_WINDOW_WIDTH / 2 - 50;
    robot -> true_y = OVERALL_WINDOW_HEIGHT - 50;
    robot -> width = ROBOT_WIDTH;
    robot -> height = ROBOT_HEIGHT;
    robot -> direction = 0;
    robot -> angle = 0;
    robot -> currentSpeed = 0;
    robot -> crashed = 0;
    robot -> auto_mode = 0;
    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
}



//Returns 1 if the robot is off the screen OTHERWISE Returns 0
int robot_off_screen(struct Robot * robot){
    if ((robot -> x < 0 || robot -> y < 0) 
        || (robot -> x > OVERALL_WINDOW_WIDTH || robot -> y > OVERALL_WINDOW_HEIGHT))
        return 0;
    return 1;
}

//Returns 1 if the robot has hit the wall OTHERWISE Returns 0
int checkRobotHitWall(struct Robot * robot, struct Wall * wall) {
    int overlap = checkOverlap(robot -> x, robot -> width, robot -> y, robot -> height,
                 wall -> x,wall -> width, wall -> y, wall ->height);

    return overlap;
}

//Returns 1 if the robot has hit any wall OTHERWISE Returns 0
int checkRobotHitWalls(struct Robot * robot, struct Wall_collection * head) {
   struct Wall_collection *ptr = head;
   int hit = 0;

   while(ptr != NULL) {
      hit = (hit || checkRobotHitWall(robot, &ptr->wall));
      ptr = ptr->next;
   }
   return hit;

}

//Returns 1 if the robot has reached the end OTHERWISE Returns 0
int checkRobotReachedEnd(struct Robot * robot, int x, int y, int width, int height) {
    int overlap = checkOverlap(robot->x,robot->width,robot->y,robot->height,
                 x,width,y,height);
    return overlap;
}

//Sets the current speed to 0, prints crash message and sets crashed to false
void robotCrash(struct Robot * robot) {
    robot -> currentSpeed = 0;
    if (!robot -> crashed)
        printf("Ouchies!!!!!\n\nPress space to start again\n");
    robot -> crashed = 1;
}

//Sets the current speed to 0, prints success message and sets crashed to false
void robotSuccess(struct Robot * robot, int msec) {
    robot -> currentSpeed = 0;
    if (!robot->crashed){
        printf("Success!!!!!\n\n");
        printf("Time taken %d seconds %d milliseconds \n", msec / 1000, msec % 1000);
        printf("Press space to start again\n");
    }
    robot -> crashed = 1;
}

//Returns 1 if sensor collides with wall OTHERWISE Returns 0
int checkRobotSensor(int x, int y, int sensorSensitivityLength, struct Wall * wall)  {
    //viewing_region of sensor is a square of 2 pixels * chosen length of sensitivity
    int overlap = checkOverlap(x,2,y,sensorSensitivityLength,
                 wall -> x,wall -> width,wall -> y, wall -> height);

    return overlap;
}

//Checks if the robot sensor will collide with a wall
//Functionality based on which sensor is being used 0 = Centre, 1 = Left, 2 = Right
int checkAllWalls(struct Robot * robot, struct Wall_collection * head, int option) {
    struct Wall_collection *ptr, *head_store;
    double xDir, yDir;
    int hit;
    int sensorSensitivityLength =  floor(SENSOR_VISION/5);

    head_store = head;
    int robotCentreX = robot -> x + ROBOT_WIDTH / 2;
    int robotCentreY = robot -> y + ROBOT_HEIGHT / 2;
    int score = 0;

    for (int i = 0; i < 5; i++)
    {
        ptr = head_store;
        switch (option) {
            case 0: //Centre
                xDir = round(robotCentreX - (-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i) * sin((robot->angle)*PI/180));
                yDir = round(robotCentreY + (-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i) * cos((robot->angle)*PI/180));
                break;
            case 1: //Left
                xDir = round(robotCentreX + (+ROBOT_WIDTH/2) * cos((robot->angle-90)*PI/180) - (-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i) * sin((robot->angle-90)*PI/180));
                yDir = round(robotCentreY + (+ROBOT_WIDTH/2) * sin((robot->angle-90)*PI/180) + (-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i) * cos((robot->angle-90)*PI/180));
                break;
            case 2: //Right
                xDir = round(robotCentreX + (-ROBOT_WIDTH/2) * cos((robot->angle+90)*PI/180) - (-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i) * sin((robot->angle+90)*PI/180));
                yDir = round(robotCentreY + (-ROBOT_WIDTH/2) * sin((robot->angle+90)*PI/180) + (-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i) * cos((robot->angle+90)*PI/180));
                break;
        }
        int xTL = (int) xDir;
        int yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

//Checks if the robots sensor Front Sensor will collide with a wall
int checkRobotSensorFrontCentreAllWalls(struct Robot * robot, struct Wall_collection * head) {
    return checkAllWalls(robot, head, 0);
}

//Checks if the robots sensor Left Sensor will collide with a wall
int checkRobotSensorLeftAllWalls(struct Robot * robot, struct Wall_collection * head) {
    return checkAllWalls(robot, head, 1);
}

//Checks if the robots sensor Left Sensor will collide with a wall
int checkRobotSensorRightAllWalls(struct Robot * robot, struct Wall_collection * head) {
    return checkAllWalls(robot, head, 2);
}



//TODO
void robotUpdate(struct SDL_Renderer * renderer, struct Robot * robot){
    double xDir, yDir;

    int robotCentreX, robotCentreY, xTR, yTR, xTL, yTL, xBR, yBR, xBL, yBL;
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

    /*
    //Other Display options:
    // The actual square which the robot is tested against (not so nice visually with turns, but easier
    // to test overlap
    SDL_Rect rect = {robot->x, robot->y, robot->height, robot->width};
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
    */
    /*
    //Center Line of Robot. Line shows the direction robot is facing
    xDir = -30 * sin(-robot->angle*PI/180);
    yDir = -30 * cos(-robot->angle*PI/180);
    xDirInt = robot->x+ROBOT_WIDTH/2+ (int) xDir;
    yDirInt = robot->y+ROBOT_HEIGHT/2+ (int) yDir;
    SDL_RenderDrawLine(renderer,robot->x+ROBOT_WIDTH/2, robot->y+ROBOT_HEIGHT/2, xDirInt, yDirInt);
    */

    //Rotating Square
    //Vector rotation to work out corners x2 = x1cos(angle)-y1sin(angle), y2 = x1sin(angle)+y1cos(angle)
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;

    xDir = round(robotCentreX+(ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xTR = (int) xDir;
    yTR = (int) yDir;

    xDir = round(robotCentreX+(ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xBR = (int) xDir;
    yBR = (int) yDir;

    xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xBL = (int) xDir;
    yBL = (int) yDir;

    xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xTL = (int) xDir;
    yTL = (int) yDir;

    SDL_RenderDrawLine(renderer,xTR, yTR, xBR, yBR);
    SDL_RenderDrawLine(renderer,xBR, yBR, xBL, yBL);
    SDL_RenderDrawLine(renderer,xBL, yBL, xTL, yTL);
    SDL_RenderDrawLine(renderer,xTL, yTL, xTR, yTR);

    //Front Centre Sensor
    int sensor_sensitivity =  floor(SENSOR_VISION/5);
    int i;
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Left Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(+ROBOT_WIDTH/2)*cos((robot->angle-90)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle-90)*PI/180));
        yDir = round(robotCentreY+(+ROBOT_WIDTH/2)*sin((robot->angle-90)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle-90)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Right Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle+90)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle+90)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle+90)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle+90)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

        //xDir = round(robotCentreX+(ROBOT_WIDTH/2-2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180));
        //yDir = round(robotCentreY+(ROBOT_WIDTH/2-2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle)*PI/180));
}

void resetToMaxSpeed(struct Robot * robot) {
    if (robot -> currentSpeed > MAX_ROBOT_SPEED)
        robot -> currentSpeed = MAX_ROBOT_SPEED;
}


//TODO = Fix this method to make it work on smaller amounts of speed changes
//Implement as a 0.0 - 1.0 * DEFAULT_SPEED_CHANGE, to make it a more fluid motion
//The more fluid motion will allow tighter turns, since the servo is continuous
//Not positional
//
//FINISHED = made the method more readable and concise
void robotMotorMove(struct Robot * robot, int crashed) { //take in a modifier double
    if (crashed)
        robot -> currentSpeed = 0;
    else {
        switch(robot -> direction){
            //Fix all of these to make it continuous not positional
            case UP :
                robot -> currentSpeed += DEFAULT_SPEED_CHANGE;
                resetToMaxSpeed(robot); break;
            case DOWN :
                robot->currentSpeed -= DEFAULT_SPEED_CHANGE;
                resetToMaxSpeed(robot); break;
            case LEFT :
                robot -> angle = (robot -> angle + 360 - DEFAULT_ANGLE_CHANGE) % 360;
                break;
            case RIGHT :
                robot -> angle = (robot -> angle + DEFAULT_ANGLE_CHANGE) % 360;
                break;
        }
    }
    robot -> direction = 0;
    robot -> true_x += (-robot -> currentSpeed * sin(-robot -> angle * PI / 180));
    robot -> true_y += (-robot -> currentSpeed * cos(-robot -> angle * PI / 180));

    robot -> x = (int) round(robot -> true_x);
    robot -> y = (int) round(robot -> true_y);
}


// void robotAutoMotorMove(struct Robot * robot, int front_centre_sensor, int left_sensor, int right_sensor) {
//     if (front_centre_sensor == 0) {
//         if (robot->currentSpeed < 2)
//             robot->direction = UP;
//     }
//     else if ((robot->currentSpeed > 0) && ((front_centre_sensor >= 1) && (left_sensor == 0) && (right_sensor == 0)) ) {
//         robot->direction = DOWN;
//     }
//     else if ((robot->currentSpeed == 0) && ((front_centre_sensor >= 1) && (left_sensor == 0)) ) {
//         robot->direction = LEFT;
//     }
//     else if ((robot->currentSpeed > 0) && ((right_sensor >= 1)) ) {
//         robot->direction = LEFT;
//     }
//     else if ((robot->currentSpeed>0) && ((left_sensor >= 1)) ) {
//         robot -> direction = RIGHT;
//     }
// }

//Slows down the robot and updates the speed to reflect the slow down
void slowDown(struct Robot * robot) {
    robot -> direction = DOWN;
    speed -= 1;
}

//Makes the robot accelerate if the speed is under 5
void moveForward(struct Robot * robot) {
    if (speed < 5) {
        robot -> direction = UP;
        speed += 1;
    }
}

//Rotates the clockwise until the turn is complete
void rotateClockwise(struct Robot * robot) {
    robot -> direction = RIGHT;
    degreesLeftClockwise -= 15;
    if (degreesLeftClockwise <= 0)
        inClockwiseTurn = 0;
}


//Rotates the counter clockwise until the turn is complete
void rotateCounterClockwise(struct Robot * robot) {
    robot -> direction = LEFT;
    degreesLeftCounterClockwise -= 15;
    if (degreesLeftCounterClockwise <= 0)
        inCounterClockwiseTurn = 0;
}


void robotAutoMotorMove(struct Robot * robot, int front_centre_sensor, 
int left_sensor, int right_sensor) {
    if (inClockwiseTurn == 1) // If turning clockwise continue to do so
        rotateClockwise(robot);
    else if (inCounterClockwiseTurn == 1) // If turning counterClockwise continue to do so
        rotateCounterClockwise(robot);
    else {
        if (firstMove == 0) {
            inClockwiseTurn = 1;
            degreesLeftClockwise = 90;
            rotateClockwise(robot);
            firstMove = 1;
            return;
        }
        if (front_centre_sensor >= 1) { // There is a wall ahead
            inCounterClockwiseTurn = 1;
            degreesLeftCounterClockwise = 90;
            rotateCounterClockwise(robot);
        }
        else if (right_sensor < 2 && timeOutOfRightSensor > timeNeededOutOfSensor) { // Corner right
            inClockwiseTurn = 1;
            degreesLeftClockwise = 90;
            timeNeededOutOfSensor = 0;
            timeOutOfRightSensor = 0;
            rotateClockwise(robot);
        }
        else if (right_sensor >= 1) { // Moving along a right wall
            timeNeededOutOfSensor = right_sensor - 1;
            timeOutOfRightSensor = 1;
            moveForward(robot);
        }
        else { // No right wall on the side, prepare for next turn
            if (timeOutOfRightSensor >= 1)
                timeOutOfRightSensor += 1;
            moveForward(robot);
        }
    }
}



