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

# [Code Theory](THEORY.md)