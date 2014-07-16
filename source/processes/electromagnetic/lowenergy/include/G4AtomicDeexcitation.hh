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
// $Id: G4AtomicTransitionManager.hh,v 1.2 ????
// GEANT4 tag $Name: not supported by cvs2svn $
//
// Authors: Elena Guardincerri (Elena.Guardincerri@ge.infn.it)
//          Alfonso Mantero (Alfonso.Mantero@ge.infn.it)
//
// History:
// -----------
//  
//  16 Sept 2001  First committed to cvs
//
// -------------------------------------------------------------------

// Class description:
// Low Energy Electromagnetic Physics, management of atomic deexcitation
// Further documentation available from http://www.ge.infn.it/geant4/lowE

// -------------------------------------------------------------------

#ifndef G4AtomicDeexcitation_h
#define G4AtomicDeexcitation_h 1

#include "globals.hh"
#include <vector>
#include "G4DynamicParticle.hh"

class G4AtomicDeexcitation {

public:

  G4AtomicDeexcitation();
  ~G4AtomicDeexcitation();
  
  // Returns a vector contains the photons generated by radiative transitions
  // (non zero particles) or by non radiative transitions (zero particles)  
  std::vector<G4DynamicParticle*>* GenerateParticles(G4int Z, G4int shellId);
  
  void SetCutForSecondaryPhotons(G4double cut);
  // Set threshold energy for fluorescence 

  void SetCutForAugerElectrons(G4double cut);
  // Set threshold energy for Auger electron production

  void ActivateAugerElectronProduction(G4bool val);
  // Activate Auger electron production


private:
  
  // Decides wether a radiative transition is possible and, if it is,
  // returns the identity of the starting shell for the transition
  G4int SelectTypeOfTransition(G4int Z, G4int shellId);
  
  // Generates a particle from a radiative transition and returns it
  G4DynamicParticle* GenerateFluorescence(G4int Z, G4int shellId,G4int provShellId);
 
  // Generates a particle from a non-radiative transition and returns it
  G4DynamicParticle* GenerateAuger(G4int Z, G4int shellId);
 
  // Data member which stores the shells to be filled by 
  // the radiative transition
  G4int newShellId;

  G4double minGammaEnergy;
  G4double minElectronEnergy;
  G4bool   fAuger;

  // Data member wich stores the id of the shell where is the vacancy 
  // left from the Auger electron
  G4int augerVacancyId;
 
};

#endif




