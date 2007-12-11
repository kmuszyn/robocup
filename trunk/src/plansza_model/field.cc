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

#include <gazebo/BoxGeom.hh>
#include <gazebo/ModelFactory.hh>

#include "field.hh"


/////////////////////////////////////////////////////////////////////////////
// Register the model
GZ_REGISTER_PLUGIN("Field", Field)


//////////////////////////////////////////////////////////////////////////////
// Constructor
Field::Field( World *world )
    : Model( world )
{
  return;
}


//////////////////////////////////////////////////////////////////////////////
// Destructor
Field::~Field()
{
  return;
}


//////////////////////////////////////////////////////////////////////////////
// Load the sensor
int Field::Load( WorldFile *file, WorldFileNode *node )
{
  //Geom *geom;
  Geom *left,*right,*top,*bottom;
  
  // Create the canonical body
  this->tma = new Body( this->world );
  this->AddBody( this->tma, true );
  
  // Create a simple box
/*
  geom = new BoxGeom( this->tma, this->modelSpaceId, 1, 4, 9 );
  geom->SetRelativePosition(GzVectorSet(0, 0, 4.5) );
  geom->SetMass( 1 );
  geom->SetColor( GzColor(0, 0, 0) );*/

  //building band
  //size of field : 2.5 m x 1.87 m, thickness of band: 38 mm, height: 40mm
  //longer ones

  float thickness = 0.038;
  float t2 = thickness/2;
  float l1 = 2.5;	//length of the longer ones
  float l2 = 1.794;	//shorter ones
  float h = 0.04;	//heigth
  
  GzColor c = GzColor(0.5, 0.2, 0.1);

  
  left = new BoxGeom(this->tma, this->modelSpaceId,thickness,l1,h);
  left->SetRelativePosition(GzVectorSet(t2, l1/2, 0) );
  left->SetMass( 10 );
  left->SetColor(c);

  right = new BoxGeom(this->tma, this->modelSpaceId,thickness,l1,h);
  right->SetRelativePosition(GzVectorSet(l2+thickness+t2, l1/2, 0) );
  right->SetMass( 10 );
  right->SetColor(c);

  //shorter
  top = new BoxGeom(this->tma, this->modelSpaceId,l2,thickness,h);
  top->SetRelativePosition(GzVectorSet(l2/2+thickness, t2, 0) );
  top->SetMass( 10 );
  top->SetColor(c);

  bottom = new BoxGeom(this->tma, this->modelSpaceId,l2,thickness,h);
  bottom->SetRelativePosition(GzVectorSet(l2/2+thickness, l1-t2, 0) );
  bottom->SetMass( 10 );
  bottom->SetColor(c);

  return 0;
}


//////////////////////////////////////////////////////////////////////////////
// Initialize the sensor
int Field::Init( WorldFile *file, WorldFileNode *node )
{
  return 0;
}


//////////////////////////////////////////////////////////////////////////////
// Finalize the sensor
int Field::Fini()
{
  return 0;
}


//////////////////////////////////////////////////////////////////////////////
// Get commands from the external interface
void Field::IfaceGetCmd()
{
  // Receive commands from external interface

  return;
}


//////////////////////////////////////////////////////////////////////////////
// Update external interface
void Field::IfacePutData()
{
  // Update external interfaces
  
  return;
}


//////////////////////////////////////////////////////////////////////////////
// Update the sensor information; returns non-zero if sensor data has
// been updated
void Field::Update( double step )
{
  // Get commands from the external interface
  this->IfaceGetCmd();

  // Command any actuators
  
  // Update any sensors

  // Update the external interface with the new data
  IfacePutData();

  return;
}
