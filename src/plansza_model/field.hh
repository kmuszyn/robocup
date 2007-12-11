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
 * Desc: EXAMPLE ONLY for dynamically-loaded models
 * Author: Andrew Howard
 * Date: 14 Jul 2004
 * CVS: $Id: ExampleModel.hh,v 1.2 2004/09/09 18:31:41 inspectorg Exp $
 */

#ifndef FIELD_HH
#define FIELD_HH

#include <gazebo/Body.hh>
#include <gazebo/Model.hh>


class Field : public Model
{
  // Constructor
  public: Field( World *world );
  
  // Destructor
  public: virtual ~Field();

  // Load stuff
  public: int Load( WorldFile *file, WorldFileNode *node );
  
  // Initialize stuff
  public: int Init( WorldFile *file, WorldFileNode *node );

  // Finalize stuff
  public: int Fini();
  
  // Get commands from the external interface
  private: void IfaceGetCmd();

  // Update the data in the external interface
  private: void IfacePutData();  

  // Do updates
  public: void Update( double step );

  // The canonical body
  private: Body *tma;
};

#endif
