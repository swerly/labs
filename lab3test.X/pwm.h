/* 
 * File:   pwm.h
 * Author: Seth
 *
 * Created on March 21, 2015, 12:38 PM
 */

#ifndef PWM_H
#define	PWM_H

#define LCD_VL 0
#define MOTOR_ONE 1
#define MOTOR_TWO 2
#define FORWARD 0
#define REVERSE 1

void initLCDPWM();
void initMotorPWM();
void setDutyCycle(int motor, int percent);
void setDirection(int dir);
void testMotors();

#endif	/* PWM_H */

