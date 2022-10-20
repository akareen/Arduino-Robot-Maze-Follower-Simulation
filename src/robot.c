#include "robot.h"
#include "stdbool.h"

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
    
    
    robot -> firstMove = 0;
    robot -> closeness = 2;
    //Must comply with regulations
    robot -> speedLimit = 7;
    robot -> totalAngle = 0;
    //robot -> moveCodes[0] = 0;
    //robot -> moveCodes[1] = 0;

    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
}

int angleChange = 15;
int totalAngle = 0;

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
    if (!robot -> crashed){
        printf("Success!!!!!\n\n");
        printf("Time taken %d seconds %d milliseconds\n", msec / 1000, msec % 1000);
        printf("Press space to start again or press N for the next maze or B for previous\n");
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

//Function that updates the robot
void robotUpdate(struct SDL_Renderer * renderer, struct Robot * robot){
    double xDir, yDir;

    int robotCentreX, robotCentreY, xTR, yTR, xTL, yTL, xBR, yBR, xBL, yBL, xDirInt, yDirInt;
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

    // this will change the image of the robot to a 20x20 mooshroom bitmap image,
    // where all the instructions were specified in ed post #829
    SDL_Rect rect = {robot->x, robot->y, robot->height, robot->width};
    SDL_Surface * img = SDL_LoadBMP("arduino.bmp");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, img);
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, robot->angle, NULL, flip);
    SDL_DestroyTexture(texture);

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

    // this is commented out as we added a custom image to the robot before
    // all this does is create a rectangular outline under the image
    /*
    SDL_RenderDrawLine(renderer,xTR, yTR, xBR, yBR);
    SDL_RenderDrawLine(renderer,xBR, yBR, xBL, yBL);
    SDL_RenderDrawLine(renderer,xBL, yBL, xTL, yTL);
    SDL_RenderDrawLine(renderer,xTL, yTL, xTR, yTR);
    */

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

//If the speed exceeds the maximum brings it back down
void resetToMaxSpeed(struct Robot * robot) {
    if (robot -> currentSpeed > MAX_ROBOT_SPEED)
        robot -> currentSpeed = MAX_ROBOT_SPEED;
}


//Moves the robot based on the direction provided
void robotMotorMove(struct Robot * robot, int crashed) { //take in a modifier double
    if (crashed)
        robot -> currentSpeed = 0;
    else {
        switch(robot -> direction){
            //Fix all of these to make it continuous not positional
            case ACCELERATE :
                robot -> currentSpeed += DEFAULT_SPEED_CHANGE;
                resetToMaxSpeed(robot); break;
            case BRAKE :
                robot -> currentSpeed -= DEFAULT_SPEED_CHANGE;
                resetToMaxSpeed(robot); break;
            case LEFT :
                robot -> totalAngle -= angleChange;
                robot -> angle = (robot -> angle + 360 - angleChange) % 360;
                break;
            case RIGHT :
                robot -> totalAngle += angleChange;
                robot -> angle = (robot -> angle + angleChange) % 360;
                break;
            case BRAKELEFT :
                robot->currentSpeed -= DEFAULT_SPEED_CHANGE;
                robot -> angle = (robot -> angle + 360 - angleChange) % 360;
                break;
            case BRAKERIGHT :
                robot->currentSpeed -= DEFAULT_SPEED_CHANGE;
                robot -> angle = (robot -> angle + angleChange) % 360;
                break;

        }
    }
    robot -> direction = 0;
    robot -> true_x += (-robot -> currentSpeed * sin(-robot -> angle * PI / 180));
    robot -> true_y += (-robot -> currentSpeed * cos(-robot -> angle * PI / 180));

    robot -> x = (int) round(robot -> true_x);
    robot -> y = (int) round(robot -> true_y);
}


//Stores consecutive movement, ex: 6 right turns = {3,6}
void updateMoveCodes(struct Robot * robot, int code) {
   // if (robot -> moveCodes[0] == code)
   //     robot -> moveCodes[1] += 1;
   // else {
   //     robot -> moveCodes[0] = code;
   //     robot -> moveCodes[1] = 1;
   // }
}

//Tells if the robot has looped
//int hasLooped(struct Robot * robot) {
//    return (robot -> moveCodes[0] == 2 || robot -> moveCodes[0] == 3) 
//    && robot -> moveCodes[1] >= 6 * 4; 
//}

//Accelerates the robot forward as long as it is under the custom speedLimi
void moveForward(struct Robot * robot) {
    if ((robot -> currentSpeed) < robot -> speedLimit) {
        robot -> direction = ACCELERATE;
        updateMoveCodes(robot, 0);
    }
}

//Turns on the brakes as long as the robot is moving
void slowDown(struct Robot * robot) {
    if ((robot -> currentSpeed) > 0) {
        robot -> direction = BRAKE;
        updateMoveCodes(robot, 1);
    }
}

//If the speed is higher than 3 brakes and turns left at the same time
//Otherwise just turns left
void turnLeft(struct Robot * robot) {
    updateMoveCodes(robot, 2);
    
    if (robot -> currentSpeed > 3)
        robot -> direction = BRAKELEFT; // Brake and turn left same time
    else
        robot -> direction = LEFT;
}

//If the speed is higher than 3 brakes and turns right at the same time
//Otherwise just turns right
void turnRight(struct Robot * robot) {
    updateMoveCodes(robot, 3);
    
    if (robot -> currentSpeed > 3)
        robot -> direction = BRAKERIGHT; // Brake and turn right same time
    else
         robot -> direction = RIGHT;
}

//First step of the program if there is a right wall it is finished
//Otherwise it will do a 90 degree clockwise turn and move forward until it
//finds a wall infront of it upon which it will turn left and exit the function
bool firstStep(struct Robot * robot, int front_sensor, int right_sensor, int left_sensor) {
    if (right_sensor > 1) {
        robot -> firstMove = 2;
        moveForward(robot);
        return false;
    } else if (left_sensor > 1){
        robot -> firstMove = 2;
        moveForward(robot);
        return true;
    }
    
    if (robot -> firstMove == 0) {
        turnRight(robot);   
        if (robot -> totalAngle >= 30 || robot -> totalAngle <= -30) 
            //printf("first move");
            robot -> firstMove++;
        return false;
    }
    else if (robot -> firstMove == 1) {            
        if (front_sensor >= 1) {
            //printf("Second move");
            robot -> firstMove = 2;
            turnLeft(robot);
        }
        else
            moveForward(robot);
    }
    return true;
}

int robotMove;
unsigned long loops = 0;
unsigned long lastLoops = 0;
int narrowWait = 25;

unsigned long lastTurnLoops = 0;
unsigned long lastMoveLoops = 0;
int turnWait = 1;
int uTurnWait = 2;

//Follow the right wall
void followRightWall(int front_centre_sensor, int right_sensor, int left_sensor, struct Robot * robot){
    
    if (front_centre_sensor >= 3){
        turnLeft(robot);
        angleChange = 15;
    }else if (front_centre_sensor >= 1){
        slowDown(robot);
        angleChange = 15;
        if (right_sensor < robot -> closeness -1) {
            turnRight(robot);
        } else {
            turnLeft(robot);
        }

        if (robot -> currentSpeed <= 1){
            angleChange = 10;
            turnRight(robot);
            moveForward(robot);
        }

    }else if (right_sensor == 0){
        if (loops - lastTurnLoops > turnWait){
            angleChange = 10;
            turnRight(robot);
        } else {
            moveForward(robot);
        }
    }
    else if (right_sensor < robot -> closeness){ //not close enough to right wall
        angleChange = 10;
        turnRight(robot);
    }
    else if (right_sensor == robot -> closeness){ //close enough to right wall
        angleChange = 10;
        moveForward(robot);
        lastTurnLoops = loops;
        lastMoveLoops = loops;
    }
    else if (right_sensor > robot -> closeness){ //too close to right wall
        angleChange = 15;
        turnLeft(robot);
    }
}

//Follow the left wall
void followLeftWall(int front_centre_sensor, int right_sensor, int left_sensor, struct Robot * robot){
    if (front_centre_sensor >= 3){
        turnRight(robot);
        angleChange = 15;
    } else if (front_centre_sensor >= 1){
        slowDown(robot);
        angleChange = 15;
        if (left_sensor < robot -> closeness -1) {
            turnLeft(robot);
        } else {
            turnRight(robot);
        }

        if (robot -> currentSpeed <= 1){
            angleChange = 10;
            turnLeft(robot);
            moveForward(robot);
        }

    }
    else if (left_sensor == 0){
        if (loops - lastTurnLoops > turnWait){
            angleChange = 10;
            turnLeft(robot);
        } else {
            moveForward(robot);
        }
    }
    else if (left_sensor < robot -> closeness){ //not close enough to left wall
        angleChange = 10;
        turnLeft(robot);
    }
    else if (left_sensor == robot -> closeness){ //close enough to left wall
        angleChange = 10;
        moveForward(robot);
        lastTurnLoops = loops;
        lastMoveLoops = loops;
    }
    else if (left_sensor > robot -> closeness){ //too close to left wall
        angleChange = 15;
        turnRight(robot);
    }
}

//TODO:
//Account better for narrow paths
//Insert some code that detects if the robot is stuck in a loop
// Im thinking that we make a variable that stores the last turn
//if the robot turned right 4 times (90 degrees) or turned left 4 times then it looped

// Have added movecodes that stores the above, have not done loop code yet
// int[] moveCodes: 
// [0]: 0 = forward, 1 = down, 2 = left, 3 = right
// [1]: number of consecutive

bool doingUturn = false;

void robotAutoMotorMove(struct Robot * robot, int front_centre_sensor, 
int left_sensor, int right_sensor) {

    loops++;

    //printf("total angle:  %d\n", totalAngle);

    //Loop check - did the robot go in a circle:
    //Should it check for one loop or two loops? maybe there will be a false positive on one loop
   // if (robot -> totalAngle < -720 || robot -> totalAngle > 720){
    //    robotMove = !robotMove;
    //    robot -> totalAngle = 0;
    //}

    //Navigation Basic
     if ((left_sensor >= 2 && right_sensor >=2 && front_centre_sensor >= 1) || doingUturn) {
        if (robot -> currentSpeed > 0){
            slowDown(robot); 
            printf("speed:  %d\n", robot->currentSpeed);
        } //Get to a complete stop in a u-turn
            
        else {
            doingUturn = true;
            lastMoveLoops = loops;
            if (robotMove == 1){
                turnLeft(robot);
            } else if (robotMove == 0){
                turnRight(robot);
            }
            if (front_centre_sensor == 0){
                doingUturn = false;
            }
        }
        return;
    } 
    else if ((left_sensor >= 1 && right_sensor >= 1 && front_centre_sensor >= 1) || doingUturn) {
        if (robot -> currentSpeed > 0){
            slowDown(robot); 
            printf("speed:  %d\n", robot->currentSpeed);
        } //Get to a complete stop in a u-turn
        
        if (robotMove == 1){
            slowDown(robot);
            turnLeft(robot);
        } else if (robotMove == 0){
            slowDown(robot);
            turnRight(robot);
        }
        return;
    } 
    
    //Deal with narrow paths
    else if (left_sensor >= 1 && right_sensor >= 1) { //In a narrow path
        robot -> closeness = 3;
        robot -> speedLimit = 5;
        if (robot -> currentSpeed > 4) { //Slow it enought for turns
            slowDown(robot);
            return;
        }
    }
    //Very narrow paths
    else if (left_sensor >= 2 && right_sensor >= 2) { //In a very narrow path
        robot -> closeness = 3;
        robot -> speedLimit = 4;
        printf("Very Narrow");
        if (robot -> currentSpeed > 2) { //Slow it enought for turns
            slowDown(robot);
            return;
        }
    }
    else { 
        //Normal top speed - only after a short delay
        if ((loops - lastLoops) > narrowWait){
            lastLoops = loops;
            robot -> speedLimit = 6; //This needs to be adjusted more
            robot -> closeness = 2;
        }
    }

    if (robot -> firstMove < 2) { // Move to the first right wall
        angleChange = 10;
        robotMove = firstStep(robot, front_centre_sensor, right_sensor, left_sensor);
    } else if (robotMove){ //Follow right wall
        followLeftWall(front_centre_sensor, right_sensor, left_sensor, robot);
    } else {
        followRightWall(front_centre_sensor, right_sensor, left_sensor, robot);
    }
    
}