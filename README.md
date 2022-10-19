# Project-Simulation
ELEC1601 Robot Project Simulation

**MAP PROGRESS 80% (excluding extra)**
- [x] 1
- [x] 2
- [x] 3
- [x] 4
- [ ] 5 (is not handling narrow well) 
- [x] 6
- [x] 7 
- [ ] 8 (choosing left instead of right)
- [x] 9
- [x] 10
EXTRA
- [ ] 11 (dies straight away)
- [ ] 12 (dies straight away)
- [ ] 13 (at the end)
\
\
**List of things to do:**
* Improve the algorithm for the robot (various steps including curves)
* Make it pass all mazes
* Stop it from overshooting the left turn
* Incorporate acceleration and momentum
* Refine the speed
* Fix minor bugs for changing maze
\
\
**List of things to do if time permits**
* Add timer to GUI
* Learn the maze the first time around to make it faster for subsequent runs. 
This can be done by creating an integer array with a code for each movement the
robot has made. When the robot is a few steps away from a turn it can decelerate.
This will mean the robot can accelerate faster in a straight line and slow down for a turn.
\
\
**Current progress:**
* Reduced code length
* Added comments to clarify functionality
* Basic Wall following algorithm complete
* Basic maze finished in 29.4 seconds
* Mazes can now be changed automatically, press N for next maze, B for previous
* Brake at the same time as turning
* Improved GUI of the simulation
\
\
**Rules to be aware of:**
* Maximum speed change of 1 (per timestep), 
    use 0.0 - 1.0 to make it smoother
* Maximum top speed of 25
* Maximum rotation of 15 degrees (per timestap), 
    use 0.0 - 15.0 to make it smoother
* Maximum sensor vision of 30 (pixels), 
    try and use gradient steps for accuracy
* There will be 90 degree corners in the basic maze and curved corners in advanced
