# Integrated Design Project (Group 206) 
A central repository for the Cambridge Engineering Tripos 1B Integrated Design Project (IDP), Group 206. 

## Our robot 🤖
The name of our robot is called Howard! It has been built from scratch from mechanical design to embedded software implementation. The code which drives Howard is located in the `Howard` folder.

<img src="https://github.com/Vincentho711/IDP_Group_206/blob/main/images/howard.jpg" width="600" height="756">

## Demo 🎭
![Demo](https://github.com/Vincentho711/IDP_Group_206/blob/main/images/howard_gif.gif)

## About the task 📃
### Task description
Many robot applications require the ability of a robot to carry out a task to a high degree of precision. In this task
you are required to build a robot to demonstrate the collection, detection and delivery of blocks to a high degree of
precision in a structured environment.

### Specific Specification
Blocks should be clearly identified before they are transported. This should be indicated by illuminating a red
LED for red blocks and a green LED for blue. The LED should clearly illuminate for >5 seconds.
- The robot must not make contact with the block before the colour has been clearly identified
- The robot may traverse between the two sides of the table by either navigating around the obstruction or
making use of the ramp over the obstruction.
- Blocks will be scored for delivery at the end of the task.
Embedded software to drive the Arduino Uno with different peripherals.

### Arena
![Arena](https://github.com/Vincentho711/IDP_Group_206/blob/main/images/arena.JPG?raw=true)

### Scoring
| Action | Score |
| --- | --- |
| Robot first traverses to other side of table (no part of robot on ramp) | +10 |
| Red package delivered to red target  | See Below |
| Blue package delivered to blue target  | See Below |
| Package transported to delivery side of table  | +10 |
| Correct LED displayed to identify package without contact  | +10 |
| Robot finally returns to a start/end box and stops such that at least 50% of the robot is within the box. The robot must have made a sporting attempt to move parcels on to targets | +20 |

![Target Scoring](https://github.com/Vincentho711/IDP_Group_206/blob/main/images/target_scoring.JPG?raw=true)

We scored a total score of +45 in the end.

## Built with 🔧
- [C++](https://www.cplusplus.com/)
- [VSCode](https://code.visualstudio.com/)
- [PlatformIO](https://platformio.org/)