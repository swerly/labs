/* 
 * File:   timer.h
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#ifndef INITTIMER_H
#define	INITTIMER_H

void initTMR4();
char* getTimeString(int min, int sec, int ms);
void delayUs(unsigned int delay);

#endif	/* INITTIMER_H */

