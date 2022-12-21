# USYD ELEC1601 Arduino Maze Follower Simulation

Created as a team project with: Mika Delevaux ([@*meface1*](https://github.com/meface1)) , Andrew Guo ([@*andrewguoo*](https://github.com/andrewguoo)), Adam Kareen (myself) and Jacob Kazem ([@yakk1](https://github.com/yakk*1)).

Requires SDL2 to be installed to run.

**Usage**

Build instructions:

`make`

Run instructions:

`make run`

##### Simulation Information:

The robot simulated has three sensors: left, centre and right. These sensors determine the distance an object is from the robot.

The algorithm that we have implemented for the project simulation is a wall following algorithm, as given a well defined perimeter exit maze, it will always reach the end. It has been based on maintaining a certain distance using a proportional controller from its selected wall (using a variable called closeness).

At the start of the program, our wall following algorithm prefers to follow a right wall. If there are both left and right walls, the robot follows the right wall. If there is only a left wall, the robot will follow the left wall. If there are no walls, the robot will seek out the nearest right wall by doing a 90 degree turn and moving forward.

![Alt text](file:///Users/ak/Library/Mobile Documents/com~apple~CloudDocs/Github/Arduino-Robot-Maze-Follower-Simulation/docs/images/follow_leftwall.gif?raw=true?msec=1671582069400 "Title")

- Our maze robot utilises a proportional controller to maintain a certain distance from the wall its following
  
- When the robot is not close enough to the wall it is following, it will move closer to the wall.
  
- Alternatively, if the robot is too close to the wall it is following then the robot will turn away from the wall to maintain the target distance.
  
- If the robot is the correct distance from the desired wall, then the robot will accelerate until it reaches the max speed.
  

![Alt text](file:///Users/ak/Library/Mobile Documents/com~apple~CloudDocs/Github/Arduino-Robot-Maze-Follower-Simulation/docs/images/correcting_closeness.gif?raw=true?msec=1671582171528 "Title")

To make our turns smooth we have created two cases for the direction of the robot “BRAKELEFT” and “BRAKERIGHT”. When these directions are used the robot will brake and turn the desired direction at the same time. This was made to allow the robot to turn and brake simultaneously making turns smoother and more reliable. The robot will brake and turn when it is turning at a speed greater than 3 or 4 depending on the speed limit.

![Alt text](file:///Users/ak/Library/Mobile Documents/com~apple~CloudDocs/Github/Arduino-Robot-Maze-Follower-Simulation/docs/images/smooth_turning.gif?raw=true?msec=1671582285889 "Title")

To make our robot faster we have allowed the robot to brake and turn simultaneously. Furthermore, the robot speeds up when it is not in a narrow section, and slows down in narrow sections. A narrow section occurs when both left and right sensors are active.

##### Additional Improvements:

We are proud of the maze testing program we have created. To effectively and repeatedly test our algorithm, we implemented a way to cycle through 10 different mazes by pressing **n** or **b** while the program is running, so we never needed to copy and paste maze code.

##### Acknowledgements:

The logic of the robot and the algorithm underlying its performance was created by the team accreddited above.

The Maze switching portion of the code was created solely by Jacob Kazem ([@yakk1](https://github.com/yakk*1)).

The underlying engine used in this simulation was created by the ELEC1601 staff at the University of Sydney. The unit coordinator for that unit is Dr. Boland.

The maps used in the simulation were created by ELEC1601 staff, Daniel Cocking, Linus Foley, Axel Hu, Tze Teoh, Shengyun Ma, Yutong Xu, Alex Sugg, Erik Hai, Raphael Chan, Zicheng Li, Tommy Roche, Jacky Zhang, Aidan Robinson, Alec Lu, Duc Thanh Truong.
