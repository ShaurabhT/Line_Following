# Line_Following
A Line Follower Robot, as the name suggests, is an automated guided vehicle, which follow a visual line embedded on the floor or ceiling. Usually, the visual line is
the path in which the line follower robot goes and it will be a black line on a white surface but the other way (white line on a black surface) is also possible. 

Components:

Sensors (IR Sensor): We have used IR Sensor Module as the line detecting sensor for the project. It consists of an IR LED and a Photo diode and some other components 
like comparator, LED etc.
Controller (Arduino UNO): Arduino UNO is the main controller in the project. The data from the sensors (IR Sensors) will be given to Arduino and it gives corresponding 
signals to the Motor Driver IC.
Motor Driver (L293D): L293D Motor Driver IC is used in this project to drive the motors of the robot. It receives signals from Arduino based on the information from the
IR Sensors.
Motors (Geared Motors): We have used two geared motors at the rear of the line follower robot. These motors provide more torque than normal motors and can be used for 
carrying some load as well.

Working:

In this project, we have designed an Arduino based Line Follower Robot. The working of the project is pretty simple: detect the black line on the surface and move along
that line. The detailed working is explained here.

We need sensors to detect the line. For line detection logic, we used two IR Sensors, which consists of IR LED and Photodiode. They 
are placed in a reflective way i.e. side – by – side so that whenever they come in to proximity of a reflective surface, the light emitted by IR LED will be detected by 
Photo diode.
In case of black surface, which has a low reflectance, the light gets completely absorbed by the black surface and doesn’t reach the photodiode.

Using the same principle, we will setup the IR Sensors on the Line Follower Robot such that the two IR Sensors are on the either side of the black line on the floor.

When the robot moves forward, both the sensors wait for the line to be detected. For example, if the IR Sensor 1 in the above image detects the black line, it means 
that there is a right curve (or turn) ahead.

Arduino detects this change and sends signal to motor driver accordingly. In order to turn right, the motor on the right side of the robot is slowed down using PWM,
while the motor on the left side is run at normal speed.

Similarly, when the IR Sensor 2 detects the black line first, it means that there is a left curve ahead and the robot has to turn left. For the robot to turn left, 
the motor on the left side of the robot is slowed down (or can be stopped completely or can be rotated in opposite direction) and the motor on the right side is run 
at normal speed.

Arduino continuously monitors the data from both the sensors and turns the robot as per the line detected by them.


~Shaurabh R. Tuladhar
