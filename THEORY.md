# Code Theory

Now let's get into the theory of the code

## Difference between turn and rotate

First of all I need to clarify to you the difference between rotating and turning.<br> When turning you are moving forward and going either left or right. When rotating you are standing still and changing your direction.

![Difference between Turning and Rotating](/images/Turn%20&%20Rotate.png)

This is a very common rookie mistake, they rotate every time the car leaves the track. It is in fact true that the car will still follow the track but it will take more time and power. For small deviations it is best to turn instead of rotating which will save us time and momentum.

## Function-like behavior
This code was written in such a way so that you can modify the accuracy based on two parameters, ```TurnSensitivity``` which can have any value from ```1 to 0```, and ```Max``` which can have any value from ```0 to 255```.

```TurnSensitivity``` is directly proportional to how much your car wobbles and also directly proportional to how much speed it has overall.<br>
By utilizing a very simple mathematical based approach it will modify the speed at which your car turns most of the time. The exception to this is when your car has offshooted. In that case you want your car to rotate at full speed instead so that it may find the track again instantly.

```Max``` is the maximum speed your car can have at any time. The value you give it will not be exceeded throughout the execution. 0 is no speed at all and 255 is full speed.
## Optimized control flow
Let's take a look at the standard flow of code that you can find everywhere on YouTube<br>

![Standard control flow diagram](/images/Standard%20Control%20Flow.png)<br><br><br>

It is a straight forward program. It checks every single possibility and makes an appropriate decision. Then it exits and begins again. <br> Notice that the program always starts by making the car move forward. This means that when turning left, it will do so in the following manner:
```
Turn Left
Move Forward
Turn Left
Move Forward
Turn Left
Move Forward
Turn Left
Move Forward
...........
```
This will slow down the car considerably.

Now I want you to take a look at the control flow of my program.<br>

![My control flow diagram](/images/Optimized%20Control%20Flow.png)

My program works on a "State-lock" system. This means it locks itself into a state and doesn't change it until a certain condition has been met.

In my case that condition would be that the error has been corrected. This means that if my car needs to go left, it would lock into the "SlightLeft" state and keep turning left indefinitely until it is back on the track meeting the "NoError" condition.

```
Turn Left
Turn Left
Turn Left
Turn Left
Turn Left
Turn Left
Turn Left
NoError - Move Forward
NoError - Move Forward
NoError - Move Forward
.............
```

Another thing to note about my program is that it has a special exit condition for "VeryLeft" indicating that the car has offshooted and we need to rotate at full speed instead of just turning.
