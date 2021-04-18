# Sumo Robot API

feito no (https://stackedit.io)[StackEdit]

## Include Library

```arduino
#include <SumoRobot.h>
```

## Setup

### Set pins

Create the SumoRobot object and specify the sensors and motors pins.

```arduino
SumoRobot sumobot = SumoRobot(INA, IN1, IN2, IN3, IN4, INB, dist_sensor, tssop_right, tssop_left, border_right, border_left);
```
 * `INA, IN1, IN2, IN3, IN4, INB` - H bridge control pins
 * `dist_sensor` - Distance sensor pin
 * `tssop_right, tssop_left` - Right and left frontal TSSOP sensor pins
 * `border_right, border_left` - Right and left border sensor pins

### Set other pins and values

Functions to set pins from other components and threshold values.

#### Init button
Defines the pin that will be used to connect the robot start button

```arduino
sumobot.defineInitButton(pin);
```
 * `pin` - Pin that the start button will be connected (note that this pin will be set as `INPUT_PULLUP`)

#### Border Threshold

Set the border detection threshold 

```arduino
sumobot.setBorderTH(threshold);
```
* `threshold` - Border detection threshold


### Movement control

Functions related to the robot's movement

#### Forward and backward
Makes a wheel (or both wheels) rotate forward or backward
```arduino
sumobot.goAhead(speed, wheel);
sumobot.goBack(speed, wheel);
```
* `speed` - The rotation speed in percentage (`0` stops, `100` max speed)
* `wheel` - Char that defines which wheel will rotate, where:
	* `'R'` - Right wheel
	* `'L'` - Left wheel
	* `'B'` - Both wheels 

#### Curve
Function to make the robot turn or rotate

```arduino
sumobot.curve(speed, level, direction);
```
* `speed` - The rotation speed in percentage (`0` stops, `100` max speed)
* `level` - A value from `0` to `100` that defines the sharpness of the turn, where a `0` value doesn't make the robot turn and a `100` value makes it rotate
* `direction` - A char value that specifies the turning direction, where:
	* `'R'` - Turns right (or rotates clockwise)
	* `'L'` - Turns left (or rotates anticlockwise)

### Sensor Reading

Override the default SPI interface used by the library. **Must** be called before `LoRa.begin()`.

#### Border

#### Distance

#### TSSOP

#### Front Sensors
=======
# sumo_robot
Repo of a sumo robot that we've made for a competition.

I'll improve it someday