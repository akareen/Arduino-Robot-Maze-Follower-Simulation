# Project-Simulation
ELEC1601 Robot Project Simulation

**Current progress:**
* Reduced code length
* Added comments to clarify functionality
* Basic Wall following algorithm complete
* Basic maze finished in 23.7 seconds


**List of things to do:**
* Improve GUI of the simulation
* Improve the algorithm for the robot (various steps including curves)
* Test on other mazes for the robot
* Incorporate acceleration and momentum

**Rules to be aware of:**
* Maximum speed change of 1 (per timestep), 
    use 0.0 - 1.0 to make it smoother
* Maximum top speed of 25
* Maximum rotation of 15 degrees (per timestap), 
    use 0.0 - 15.0 to make it smoother
* Maximum sensor vision of 30 (pixels), 
    try and use gradient steps for accuracy
* There will be 90 degree corners in the basic maze and curved corners in advanced