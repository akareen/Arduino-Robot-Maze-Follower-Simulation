# Project-Simulation
ELEC1601 Robot Project Simulation

**Current progress:**
* Reduced code length
* Added comments to clarify functionality
* Basic Wall following algorithm complete
* Basic maze finished in 29.4 seconds


**List of things to do:**
* Accelerate / Brake at the same time as turning
* Improve GUI of the simulation
* Improve the algorithm for the robot (various steps including curves)
* Test on other mazes for the robot
* Incorporate acceleration and momentum
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