# Project-Simulation
ELEC1601 Robot Project Simulation

**MAP PROGRESS 60%**
* 1 yes
* 2 yes
* 3 no (error at start)
* 4 no (is not handling narrow well) 
* 5 yes
* 6 no (didnt go through narrow at end) 
* 7 yes 
* 8 yes 
* 9 yes 
* 10 no (dies straight away)

**Current progress:**
* Reduced code length
* Added comments to clarify functionality
* Basic Wall following algorithm complete
* Basic maze finished in 29.4 seconds
* Mazes can now be changed automatically, press N for next maze, B for previous
* Brake at the same time as turning
* Improved GUI of the simulation


**List of things to do:**
* Add timer to GUI
* Improve the algorithm for the robot (various steps including curves)
* Improve on mazes not working on
* Incorporate acceleration and momentum
* Fix minor bugs for changing maze
* Learn the maze the first time around to make it faster for subsequent runs. 
This can be done by creating an integer array with a code for each movement the
robot has made. When the robot is a few steps away from a turn it can decelerate.
This will mean the robot can accelerate faster in a straight line and slow down for a turn.

**Rules to be aware of:**
* Maximum speed change of 1 (per timestep), 
    use 0.0 - 1.0 to make it smoother
* Maximum top speed of 25
* Maximum rotation of 15 degrees (per timestap), 
    use 0.0 - 15.0 to make it smoother
* Maximum sensor vision of 30 (pixels), 
    try and use gradient steps for accuracy
* There will be 90 degree corners in the basic maze and curved corners in advanced
