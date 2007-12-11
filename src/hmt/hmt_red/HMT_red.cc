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
/* Desc: Model for a HMT
 * Author: Andrew Howard
 * Date: 8 May 2003
 * CVS: $Id: HMT.cc,v 1.50 2005/05/06 17:09:28 natepak Exp $
 */

/// @addtogroup models 
/// @{
/** @defgroup HMT Pioneer 2 AT

@htmlinclude HMT_view.html

The HMT model simulates an ActivMedia HMT mobile robot
base with 16 sonars.

@par libgazebo interfaces

- Position information is available through the @ref position interface.
- Power information is available through the @ref power interface.
- Sonar information is available through the @ref sonar interface.


@par Player drivers

- Position information is available through the %gz_position driver.
- Power information is available through the %gz_power driver.
- Sonar information is available through the %gz_sonar driver.

@par Attributes

The following attributes are supported.

@htmlinclude default_attr_include.html

- updateRate (float, Hz)
  - Updates per second
  - Default: 10

- batteryLevel (float, volts)
  - Initial battery level
  - Default: 12.4

- batteryCurve (float)
  - Discharge curve: about one hour quiescent
  - Default: 2/3600  2/1e4


@par Bodies

The following bodies are created by this model.

@htmlinclude default_body_include.html

@par Example

@verbatim
<model:HMT>
  <xyz>0 0 0</xyz>
</model:HMT>
@endverbatim

@par Views

@htmlinclude HMT_more_views.html

@par Authors

Andrew Howard, Nate Koenig

*/
/// @} 

#include <assert.h>
#include <gazebo.h>
#include <gazebo/World.hh>
#include <gazebo/WorldFile.hh>
#include <gazebo/ModelFactory.hh>
#include <gazebo/Body.hh>
#include <gazebo/BoxGeom.hh>
#include <gazebo/SphereGeom.hh>
#include <gazebo/SphereGeom.hh>
#include <gazebo/WheelGeom.hh>
//#include <gazebo/PrismGeom.hh>
#include <gazebo/HingeJoint.hh>
#include <gazebo/RayProximity.hh>

#include "HMT.hh"



//////////////////////////////////////////////////////////////////////////////
// Register this model
GZ_REGISTER_PLUGIN("HMT_RED", HMT)


//////////////////////////////////////////////////////////////////////////////
// Constructor
HMT::HMT( World *world )
    : Model( world )
{
  int i;
  this->chassis = NULL;
  for (i=0; i<2; i++)
  {
    this->wheels[i] = NULL;
    this->wheelJoints[i] = NULL;
  }

  return;
}


//////////////////////////////////////////////////////////////////////////////
// Destructor
HMT::~HMT()
{
  int i;
  if (this->chassis)
    delete this->chassis;

  this->chassis = NULL;
  for (i=0; i<2; i++)
  {
    if (this->wheels[i])
      delete this->wheels[i];

    if (this->wheelJoints[i])
      delete this->wheelJoints[i];

    this->wheels[i] = NULL;
    this->wheelJoints[i] = NULL;
  }

  return;
}


//////////////////////////////////////////////////////////////////////////////
// Load the model
int HMT::Load( WorldFile *file, WorldFileNode *node )
{
  this->wheelSep = 0.105;
  this->wheelDiam = 0.08;

  this->updatePeriod = 1.0 / (node->GetDouble("updateRate", 10) + 1e-6);
  this->updateTime = -updatePeriod;

  // Create the ODE objects
  if (this->OdeLoad(file, node) != 0)
    return -1;

  // Initial battery level
  this->batteryLevel = node->GetDouble("batteryLevel", 12.4);

  // Discharge curve: about one hour quiescent
  this->batteryCurve[0] = node->GetTupleDouble("batteryCurve", 0, 2 / 3600.0);
  this->batteryCurve[1] = node->GetTupleDouble("batteryCurve", 1, 2 / 1e4);  

  return 0;
}


//////////////////////////////////////////////////////////////////////////////
// Load ODE objects
int HMT::OdeLoad( WorldFile *file, WorldFileNode *node )
{
  int i;
  double length, width, oz;
  double mass;
  double wheelSep, wheelDiam, wheelThick;
  Geom *geom;

  length = 0.108;
  width = 0.095;
  mass = 0.5;

  wheelSep = this->wheelSep;
  wheelDiam = this->wheelDiam;
  wheelThick = 0.006;

  oz = wheelDiam / 2;
  
  // Create the main chassis of the robot
  this->chassis = new Body( this->world );

  geom = new BoxGeom( this->chassis, this->modelSpaceId, length, width, 0.04);
  geom->SetRelativePosition( GzVectorSet(0, 0, oz) );
  geom->SetMass( mass );
 // geom->SetColor( GzColor(0.8, 0.78, 0.78) );  
  geom->SetColor( GzColor(0.88, 0.18, 0.18) ); 

  geom = new SphereGeom( this->chassis, this->modelSpaceId, 0.006);
  geom->SetRelativePosition( GzVectorSet(+0.045, 0, 0.01) );
  geom->SetMass( 0 );
  geom->SetColor( GzColor(0.8, 0.78, 0.78) );  

  geom = new SphereGeom( this->chassis, this->modelSpaceId, 0.006);
  geom->SetRelativePosition( GzVectorSet(-0.045, 0, 0.01) );
  geom->SetMass( 0 );
  geom->SetColor( GzColor(0.8, 0.78, 0.78) );  

  this->AddBody( this->chassis, true );

  // Create the wheels
  for (i = 0; i < 2; i++)
  {
    this->wheels[i] = new Body( this->world );

    geom = new WheelGeom( this->wheels[i], this->modelSpaceId, wheelDiam/2, wheelThick/2);
    geom->SetRelativePosition( GzVectorSet(0, 0, oz) );
    geom->SetMass( 1.0 );
    geom->SetColor( GzColor(0.3, 0.3, 0.3) );

    this->AddBody( this->wheels[i] );
  }

  this->wheels[0]->SetPosition(GzVectorSet(0.0, +0.05 * wheelSep, oz));
  this->wheels[0]->SetRotation(GzQuaternFromAxis(1, 0, 0, -M_PI / 2));
  this->wheels[1]->SetPosition(GzVectorSet(0.0, -0.05 * wheelSep, oz));
  this->wheels[1]->SetRotation(GzQuaternFromAxis(1, 0, 0, +M_PI / 2));
  
  // Attach the wheels to the chassis
  for (i = 0; i < 2; i++)
  {
    this->wheelJoints[i] = new HingeJoint( this->world );
    this->wheelJoints[i]->Attach( this->wheels[i], this->chassis );

    GzVector a = wheels[i]->GetPosition();    
    this->wheelJoints[i]->SetAnchor( a/*a.x, a.y, a.z*/);
	GzVector b ={0,1,0};
    this->wheelJoints[i]->SetAxis( b );
    this->wheelJoints[i]->SetParam( dParamSuspensionERP, 0.4 );
    this->wheelJoints[i]->SetParam( dParamSuspensionCFM, 0.8 );
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////
// Initialize the model
int HMT::Init( WorldFile *file, WorldFileNode *node )
{
  // Create position interface
  this->position_iface = gz_position_alloc();
  assert(this->position_iface);
  if (gz_position_create(this->position_iface, this->world->gz_server, this->GetId(),
                         "HMT", (int) this, (int) this->parent) != 0)
    return -1;

  // Create power inteface
  this->power_iface = gz_power_alloc();
  if (gz_power_create(this->power_iface, this->world->gz_server, this->GetId(),
                      "HMT", (int) this, (int) this->parent) != 0)
    return -1;

  // Reset odometric pose
  this->odomPose[0] = 0.0;
  this->odomPose[1] = 0.0;
  this->odomPose[2] = 0.0;

  return 0;
}


//////////////////////////////////////////////////////////////////////////////
// Finalize the model
int HMT::Fini()
{
  // Close power interface
  gz_power_destroy( this->power_iface );
  gz_power_free( this->power_iface );
  this->power_iface = NULL;

  // Close position interface
  gz_position_destroy( this->position_iface );
  gz_position_free( this->position_iface );
  this->position_iface = NULL;

  return 0;
}


//////////////////////////////////////////////////////////////////////////////
// Update model
void HMT::Update( double step )
{
  // Do nothing if paused
  if (step == 0)
    return;
  
  // Update the odometry (do this always for better accuracy)
  this->UpdateOdometry( step );

  // Otherwise, update periodically
  if (this->world->GetSimTime() - this->updateTime > this->updatePeriod)
  {
    this->updateTime = this->world->GetSimTime();

    // Get commands from the external interface
    this->GetPositionCmd();

    this->wheelJoints[0]->SetParam( dParamVel, 
                                    this->wheelSpeed[1] / this->wheelDiam * 2 );
    this->wheelJoints[1]->SetParam( dParamVel, 
                                    this->wheelSpeed[0] / this->wheelDiam * 2 );

    this->wheelJoints[0]->SetParam( dParamFMax, 10.0 );
    this->wheelJoints[1]->SetParam( dParamFMax, 10.0 );
  
    // Update the interface
    this->PutPositionData();
    this->PutPowerData();
  }
  
  return;
}


//////////////////////////////////////////////////////////////////////////////
// Update the odometry
void HMT::UpdateOdometry( double step )
{
  double wd, ws;
  double d1, d2;
  double dr, da;

  wd = this->wheelDiam;
  ws = this->wheelSep;

  // Average distance travelled by left and right wheels
  d1 = step * wd / 2 * wheelJoints[0]->GetAngleRate();
  d2 = step * wd / 2 * wheelJoints[1]->GetAngleRate();

  dr = (d1 + d2) / 2;
  da = (d2 - d1) / ws;
  
  // Compute odometric pose
  this->odomPose[0] += dr * cos( this->odomPose[2] );
  this->odomPose[1] += dr * sin( this->odomPose[2] );
  this->odomPose[2] += da;

  // Compute odometric instantaneous velocity
  this->odomVel[0] = dr / step;
  this->odomVel[1] = 0.0;
  this->odomVel[2] = da / step;

  // Update the power discharge; this is probably completely bogus
  this->batteryLevel -= this->batteryCurve[0] * step;
  this->batteryLevel -= this->batteryCurve[1] * d1 * d1;
  this->batteryLevel -= this->batteryCurve[1] * d2 * d2;

  return;
}


//////////////////////////////////////////////////////////////////////////////
// Get commands from the external interface
void HMT::GetPositionCmd()
{
  double vr, va;

  gz_position_lock(this->position_iface, 1);
  vr = this->position_iface->data->cmd_vel_pos[0];
  va = this->position_iface->data->cmd_vel_rot[2];
  gz_position_unlock(this->position_iface);
  
  this->wheelSpeed[0] = vr + va * this->wheelSep / 2;
  this->wheelSpeed[1] = vr - va * this->wheelSep / 2;
  
  return;
}


//////////////////////////////////////////////////////////////////////////////
// Update the data in the erinterface
void HMT::PutPositionData()
{
  gz_position_lock(this->position_iface, 1);
    
  // Data timestamp
  this->position_iface->data->time = this->world->GetSimTime();

  this->position_iface->data->pos[0] = this->odomPose[0];
  this->position_iface->data->pos[1] = this->odomPose[1];
  this->position_iface->data->rot[2] = this->odomPose[2];

  this->position_iface->data->vel_pos[0] = this->odomVel[0];
  this->position_iface->data->vel_rot[2] = this->odomVel[2];

  gz_position_unlock(this->position_iface);

  return;
}


//////////////////////////////////////////////////////////////////////////////
// Update the data in the power interface
void HMT::PutPowerData()
{
  gz_power_lock(this->power_iface, 1);
    
  this->power_iface->data->time = this->world->GetSimTime();
  this->power_iface->data->levels[0] = this->batteryLevel;

  gz_power_unlock(this->power_iface);
    
  return;
}


