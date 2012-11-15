//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
// 
// GRINS - General Reacting Incompressible Navier-Stokes 
//
// Copyright (C) 2010-2012 The PECOS Development Team
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the Version 2 GNU General
// Public License as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301 USA
//
//-----------------------------------------------------------------------el-
//
// $Id$
//
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

#ifndef GRINS_REACTING_LOW_MACH_NAVIER_STOKES_H
#define GRINS_REACTING_LOW_MACH_NAVIER_STOKES_H

#include "reacting_low_mach_navier_stokes_base.h"

namespace GRINS
{
  template<class Mixture>
  class ReactingLowMachNavierStokes : public ReactingLowMachNavierStokesBase<Mixture>
  {
  public:

    ReactingLowMachNavierStokes(const PhysicsName& physics_name, const GetPot& input);
    ~ReactingLowMachNavierStokes();
    
    //! Read options from GetPot input file.
    virtual void read_input_options( const GetPot& input );

    // Context initialization
    virtual void init_context( libMesh::DiffContext &context );

    // Time dependent part(s)
    virtual bool element_time_derivative( bool request_jacobian,
					  libMesh::DiffContext& context,
					  libMesh::FEMSystem* system );

    virtual bool side_time_derivative( bool request_jacobian,
				       libMesh::DiffContext& context,
				       libMesh::FEMSystem* system );

    // Constraint part(s)
    virtual bool element_constraint( bool request_jacobian,
				     libMesh::DiffContext& context,
				     libMesh::FEMSystem* system );
    //! Handles Dirichlet boundary conditions
    /*! Note that for any generic function specifications, 
      any components not specified will be assigned a zero Dirichlet value. */
    virtual bool side_constraint( bool request_jacobian,
				  libMesh::DiffContext& context,
				  libMesh::FEMSystem* system );

    // Mass matrix part(s)
    virtual bool mass_residual( bool request_jacobian,
				libMesh::DiffContext& context,
				libMesh::FEMSystem* system );

  protected:

    void assemble_mass_time_deriv(libMesh::FEMContext& c, 
				  const ReactingFlowCache& cache, 
				  unsigned int qp);

    void assemble_species_time_deriv(libMesh::FEMContext& c, 
				     const ReactingFlowCache& cache, 
				     unsigned int qp);

    void assemble_momentum_time_deriv(libMesh::FEMContext& c, 
				      const ReactingFlowCache& cache, 
				      unsigned int qp);

    void assemble_energy_time_deriv(libMesh::FEMContext& c, 
				    const ReactingFlowCache& cache, 
				    unsigned int qp);

    //! Enable pressure pinning
    bool _pin_pressure;
    
    PressurePinning _p_pinning;

  private:

    ReactingLowMachNavierStokes();

  };

} // namespace GRINS

#endif //GRINS_REACTING_LOW_MACH_NAVIER_STOKES_H
