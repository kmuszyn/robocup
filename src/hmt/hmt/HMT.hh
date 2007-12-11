/*
 *  Gazebo - Outdoor Multi-Robot Simulator
 *  Copyright (C) 2003  
 *     Nate Koenig & Andrew Howard
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
/* Desc: Model for a SickLMS200
 * Author: Andrew Howard
 * Date: 8 May 2003
 * CVS: $Id: HMT.hh,v 1.20 2004/11/05 08:02:34 inspectorg Exp $
 */

#ifndef PIONEER2AT_HH
#define PIONEER2AT_HH

#include <gazebo/Model.hh>

// Forward declarations
class Body;
class HingeJoint;
class RayProximity;


class HMT : public Model
{
  // Construct, destructor
  public: HMT( World *world );
  public: virtual ~HMT();

  // Load the model
  public: virtual int Load( WorldFile *file, WorldFileNode *node );

  // Initialize the model
  public: virtual int Init( WorldFile *file, WorldFileNode *node );

  // Finalize the model
  public: virtual int Fini();

  // Load ODE stuff
  private: int OdeLoad( WorldFile *file, WorldFileNode *node );

  // Load sonar stuff
  private: int LoadSonar( WorldFile *file, WorldFileNode *node );

  // Update the model state
  public: virtual void Update( double step );

  // Update the odometry
  private: void UpdateOdometry( double step );

  // Get commands from the external interface
  private: void GetPositionCmd();
  
  // Update the data in the external interface
  private: void PutPositionData();

  // Update the data in the power interface
  private: void PutPowerData();

  // Update the data in the sonar interface
  private: void PutSonarData();

  // Update parameters
  private: double updatePeriod, updateTime;

  // Robot parameters
  private: double wheelSep, wheelDiam;
    
  // ODE components
  private: Body *chassis;
  private: Body *wheels[2];
  private: HingeJoint *wheelJoints[2];

  // Sensor for sonar ranging
  private: RayProximity *sonarSensor;

  // External interface
  private: gz_position_t *position_iface;
  private: gz_power_t *power_iface;

  // Wheel speeds (left and right wheels are paired)
  private: double wheelSpeed[2];

  // Odometric pose estimate
  private: double odomPose[3];

  // Odometric speed estimate
  private: double odomVel[3];

  // Battery level
  private: double batteryLevel;

  // Coefficients of battery discharge curve
  private: double batteryCurve[2];
};

#endif
