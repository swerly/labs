/* 
 * File:   pwm.h
 * Author: Seth
 *
 * Created on March 21, 2015, 12:38 PM
 */

#ifndef PWM_H
#define	PWM_H

#define MOTOR_ONE 1
#define MOTOR_TWO 2
#define BOTH 3
#define FORWARD 0
#define REVERSE 1
#define OUTPUT 0
#define INPUT 1

void initMotorOnePWM();
void initMotorTwoPWM();
void setDutyCycle(int motor, float percent);
void setDirection(int motor, int dir);
void testMotors();

#endif	/* PWM_H */

