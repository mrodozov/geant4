//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id:$
//
// 
// --------------------------------------------------------------------
// GEANT 4 class header file
//
// 
// G4UTubs
//
// Class description:
//
//   Wrapper class for UTubs to make use of UTubs from USolids module.

// History:
// 30.10.13 G.Cosmo, CERN/PH
// --------------------------------------------------------------------

#ifndef G4UTUBS_HH
#define G4UTUBS_HH

#include "G4USolid.hh"

#if ( defined(G4GEOM_USE_USOLIDS) || defined(G4GEOM_USE_PARTIAL_USOLIDS) )

#include "UTubs.hh"

#include "G4Polyhedron.hh"

class G4UTubs : public G4USolid
{
  public:  // with description

    G4UTubs( const G4String& pName,
                   G4double pRMin,
                   G4double pRMax,
                   G4double pDz,
                   G4double pSPhi,
                   G4double pDPhi );
      // Constructs a tubs with the given name and dimensions

   ~G4UTubs();

    void ComputeDimensions(       G4VPVParameterisation* p,
                            const G4int n,
                            const G4VPhysicalVolume* pRep );

    G4VSolid* Clone() const;

    inline UTubs* GetShape() const;

    G4double GetInnerRadius   () const;
    G4double GetOuterRadius   () const;
    G4double GetZHalfLength   () const;
    G4double GetStartPhiAngle () const;
    G4double GetDeltaPhiAngle () const;

    void SetInnerRadius   (G4double newRMin);
    void SetOuterRadius   (G4double newRMax);
    void SetZHalfLength   (G4double newDz);
    void SetStartPhiAngle (G4double newSPhi, G4bool trig=true);
    void SetDeltaPhiAngle (G4double newDPhi);
    
    inline G4GeometryType GetEntityType() const;

    G4Polyhedron* CreatePolyhedron() const;

  public:  // without description

    G4UTubs(__void__&);
      // Fake default constructor for usage restricted to direct object
      // persistency for clients requiring preallocation of memory for
      // persistifiable objects.

    G4UTubs(const G4UTubs& rhs);
    G4UTubs& operator=(const G4UTubs& rhs); 
      // Copy constructor and assignment operator.
 
};

// --------------------------------------------------------------------
// Inline methods
// --------------------------------------------------------------------

inline UTubs* G4UTubs::GetShape() const
{
  return (UTubs*) fShape;
}

inline G4GeometryType G4UTubs::GetEntityType() const
{
  return "G4Tubs";
}

#endif  // G4GEOM_USE_USOLIDS

#endif
