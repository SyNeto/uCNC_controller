/*
 * This file is part of uCNC_controller.
 *
 * Copyright (C) 2016  D.Herrendoerfer
 *
 *   uCNC_controller is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   uCNC_controller is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with uCNC_controller.  If not, see <http://www.gnu.org/licenses/>.
 */

void plan_line(posval_t x2, posval_t y2, posval_t z2, float feedrate)
{
  posval_t n, deltax, deltay, deltaz, sgndeltax, sgndeltay, sgndeltaz, deltaxabs, deltayabs, deltazabs, x, y, z, maxdeltaabs;
  unsigned int feedHz; 

  deltax = x2 - X;
  deltay = y2 - Y;
  deltaz = z2 - Z;
  deltaxabs = abs(deltax);
  deltayabs = abs(deltay);
  deltazabs = abs(deltaz);
  sgndeltax = sgn(deltax);
  sgndeltay = sgn(deltay);
  sgndeltaz = sgn(deltaz);
  x = deltaxabs >> 1;
  y = deltayabs >> 1;
  z = deltazabs >> 1;

  // dX is biggest
  if(deltaxabs >= deltayabs && deltaxabs >= deltazabs){
    maxdeltaabs = deltaxabs;
    feedHz = feedrate * stepNumPerMillimeter_X;
    
    if (stepIssueFrequency_X < feedHz)
      feedHz = stepIssueFrequency_X;    
  }
  // dY is biggest
  else if(deltayabs >= deltaxabs && deltayabs >= deltazabs){
    maxdeltaabs = deltayabs;
    feedHz = feedrate * stepNumPerMillimeter_Y;
    
    if (stepIssueFrequency_Y < feedHz)
      feedHz = stepIssueFrequency_Y;
  }
  // dZ is biggest
  else if(deltazabs >= deltaxabs && deltazabs >= deltayabs){
    maxdeltaabs = deltazabs;
    feedHz = feedrate * stepNumPerMillimeter_Z;
    
    if (stepIssueFrequency_Z < feedHz)
      feedHz = stepIssueFrequency_Z;
  }
    Serial.print("Feed rate:");
    Serial.print(feedHz);
    Serial.println("Hz");
  
  if (deltaxabs)  
    mStepperX.plan(0, sgndeltax, maxdeltaabs, deltaxabs, x, feedHz);

  if (deltayabs)  
    mStepperY.plan(0, sgndeltay, maxdeltaabs, deltayabs, y, feedHz);

  if (deltazabs)  
    mStepperZ.plan(0, sgndeltaz, maxdeltaabs, deltazabs, z, feedHz);

  X = x2;
  Y = y2;
  Z = z2;
}


