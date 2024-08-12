# Line Folower Robot

## Materials
- Standard 4WD Chasis
- Microcontroller that supports Arduino Code
- L298N Motor Driver
- IR Sensor Array (5 Sensors)
- Portable Power Source

## Step 1: Assemble the Chasis and fix the Sensor to the bottom of the Car's front <br> Attach L298N Motor Driver Module and Arduino on the top of the car.
### Wiring circuits

| From     | Pin  | <== Pin Name   | To      | Pin |
| -------- | ---- | -------------- | ------- | --- |
| L298N    | IN1  | Left Forward   | Arduino | 2   |
| L298N    | ENA  | Left Speed     | Arduino | 3   |
| L298N    | IN2  | Left Backward  | Arduino | 4   |
| L298N    | IN3  | Right Forward  | Arduino | 5   |
| L298N    | ENB  | Right Speed    | Arduino | 6   |
| L298N    | IN4  | Right Backward | Arduino | 7   |
|          |      |                |         |     |
| IR Array | OUT1 | Very Left      | Arduino | 8   |
| IR Array | OUT2 | Slight Left    | Arduino | 9   |
| IR Array | OUT3 | Middle         | Arduino | 10  |
| IR Array | OUT4 | Slight Right   | Arduino | 11  |
| IR Array | OUT5 | Very Right     | Arduino | 12  |

#### Note: Wiring depends on your orientation <br> This is why I have included "Pin Name" to describe which Pin I am actually referring to. You can use your own pinouts too.

### Wiring motors

| From         | Pin | To    | Pin  |
| ------------ | --- | ----- | ---- |
| Left Motors  | Vcc | L298N | OUT1 |
| Left Motors  | GND | L298N | OUT2 |
| Right Motors | Vcc | L298N | OUT3 |
| Right Motors | GND | L298N | OUT4 |

## Step 2: Power
- Power is upto you, you can use any thing that has between 7 - 12 Volts
- You simply need to connect it in the following way

  | From    | Pin | To       | Pin |
  | ------- | --- | -------- | --- |
  | Supply  | Vcc | L298N    | 12V |
  | Supply  | GND | L298N    | GND |
  | L298N   | 5V  | Arduino  | Vin |
  | L298N   | GND | Arduino  | GND |
  | Arduino | 5V  | IR Array | 5V  |
  | Arduino | GND | IR Array | GND |

## Step 3: Upload the code
## Step 4: Try it on different tracks!

## Code Theory

Now let's get into the theory of the code

### Difference between turn and rotate

First of all I need to clarify to you the difference between rotating and turning.<br> When turning you are moving forward and going either left or right. When rotating you are standing still and changing your direction.

![Difference between Trunign and Rotating](/Line%20Follower/images/Turn%20&%20Rotate.png)

This is a very common rookie mistake, they rotate every time the car leaves the track. It is in fact true that the car will still follow the track but it will take more time and power. For small deviations it is best to turn instead of rotating which will save us time and momentum.

### Function-like behaviour
This code was written in such a way so that you can modify the accuracy based on two parameters, ```TurnSensitivity``` which can have any value from ```1 to 0```, and ```Max``` which can have any value from ```0 to 255```.

```TurnSensitivity``` is directly propotional to how much your car wobbles and inversely propotional to how much speed it has overall.<br>
By utilizing a very simple mathematical based approach it will modify the speed at which your car turns most of the time. The exception to this is when your car has offshooted. In that case you want your car to rotate at full speed instead so that it may find the track again instantly.

```Max``` is the maximum speed your car can have at any time. The value you give it will not be exceeded throughout the execution. 0 is no speed at all and 255 is full speed.
### Optimized control flow
Let's take a look at the standard flow of code that you can find everywhere on youtube<br>

![Standard control flow diagram](/Line%20Follower/images/Standard%20Control%20Flow.png)<br><br><br>

It is a straight forward program. It checks every single possibilty and makes an appropriate decision. Then it exits and begins again. <br> Notice that the program always starts by making the car move forward. This means that when turning left, it will do so in the folowing manner:
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

Now I want you to take a look at the contorl flow of my program.<br>

![My control flow diagram](/Line%20Follower/images/Optimized%20Control%20Flow.png)

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
