#include "RPiRecieve.h"
#include "Arduino.h"


    double goalDist = -1 ;
    double goalAzi = -1;
    double goalAlt = -1;
    double crossDist = -1;
    double crossAzi = -1;
    double crossAlt = -1;
    double val = -1;
    double foundGoal = false;
    double foundCross = false;    


void rpiInit()
{
  Serial.begin(9600);
}

void rpiRead()
{
  	if(Serial.available() <= 0)
	l	return false;
 	else if(Serial.available() == 4) 
	{
		if(Serial.read() == '0')
		{
			foundGoal = true;
            goalDist = Serial.read();
            goalAzi = Serial.read();
            goalAlt = Serial.read();			
		}
		else
		{
		    foundCross = true;
            crossDist = Serial.read();
            crossAzi = Serial.read();
            crossAlt = Serial.read();
		}
		
	}
	else if(Serial.available() == 8)
	{
	    foundGoal = true;
	    foundCross = true;
	    val = Serial.read()
	    goalDist = Serial.read();
        goalAzi = Serial.read();
        goalAlt = Serial.read();
        val = Serial.read();
        crossDist = Serial.read();
        crossAzi = Serial.read();
        crossAlt = Serial.read();		
	       
	}	



#ifdef DEBUG
  Serial.println("distance: " + distance ", azimuth: " + azimuth ", altitude: " + altitude);
#endifa

  //return true;
}

bool foundCross()
{
    return foundCross;
}
bool foundGoal()
{
    return foundGoal;
}

double goalGetDistance()
{
  return goalDist;
}

double goalGetAzimuth()
{
  return goalAzi;
}

double goalGetAltitude()
{
  return goalAlt;
}

double crossGetDistance()
{
  return crossDist;
}

double crossGetAzimuth()
{
  return crossAzi;
}

double crossGetAltitude()
{
  return crossAlt;
}
