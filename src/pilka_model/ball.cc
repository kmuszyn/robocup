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
/*
 * Desc: Factory for creating models
 * Author: Andrew Howard
 * Date: 14 Jul 2004
 * CVS info: $Id: ExampleModel.cc,v 1.5 2004/11/16 19:22:53 inspectorg Exp $
 */


#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gazebo/SphereGeom.hh>
#include <gazebo/ModelFactory.hh>

#include "ball.hh"


/////////////////////////////////////////////////////////////////////////////
// Register the model
GZ_REGISTER_PLUGIN("Ball", Ball)


//////////////////////////////////////////////////////////////////////////////
// Constructor
Ball::Ball( World *world )
    : Model( world )
{
  return;
}


//////////////////////////////////////////////////////////////////////////////
// Destructor
Ball::~Ball()
{
  return;
}


//////////////////////////////////////////////////////////////////////////////
// Load the sensor
int Ball::Load( WorldFile *file, WorldFileNode *node )
{
  Geom *ballShape;

  
  // Create the canonical body
  this->tma = new Body( this->world );
  this->AddBody( this->tma, true );
  
  //golf ball dimensions

  float r = 0.021;
  float m = 0.045;
  
  GzColor c = GzColor(1.0, 0.4, 0.0);
  
  ballShape = new SphereGeom(this->tma, this->modelSpaceId,r);
  ballShape->SetRelativePosition(GzVectorSet(0, 0, 0) );
  ballShape->SetMass( m );
  ballShape->SetColor(c);

 
  return 0;
}


//////////////////////////////////////////////////////////////////////////////
// Initialize the sensor
int Ball::Init( WorldFile *file, WorldFileNode *node )
{
  return 0;
}


//////////////////////////////////////////////////////////////////////////////
// Finalize the sensor
int Ball::Fini()
{
  return 0;
}


//////////////////////////////////////////////////////////////////////////////
// Get commands from the external interface
void Ball::IfaceGetCmd()
{
  // Receive commands from external interface

  return;
}


//////////////////////////////////////////////////////////////////////////////
// Update external interface
void Ball::IfacePutData()
{
  // Update external interfaces
  
  return;
}


//////////////////////////////////////////////////////////////////////////////
// Update the sensor information; returns non-zero if sensor data has
// been updated
void Ball::Update( double step )
{
  // Get commands from the external interface
  this->IfaceGetCmd();

  // Command any actuators
  
  // Update any sensors

  // Update the external interface with the new data
  IfacePutData();

  return;
}
