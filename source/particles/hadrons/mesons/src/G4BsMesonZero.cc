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
// $Id: G4BsMesonZero.cc 95951 2016-03-03 10:44:16Z gcosmo $
//
// 
// ----------------------------------------------------------------------
//      GEANT 4 class implementation file
//
//      Created                 Hisaya Kurashige, 16 June 1997
// **********************************************************************
//

#include "G4BsMesonZero.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

// ######################################################################
// ###                         BsMesonZero                            ###
// ######################################################################

G4BsMesonZero* G4BsMesonZero::theInstance = 0;

G4BsMesonZero* G4BsMesonZero::Definition()
{
  if (theInstance !=0) return theInstance;
  const G4String name = "Bs0";
  // search in particle table]
  G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* anInstance = pTable->FindParticle(name);
  if (anInstance ==0)
  {
  // create particle
  //
  //    Arguments for constructor are as follows
  //               name             mass          width         charge
  //             2*spin           parity  C-conjugation
  //          2*Isospin       2*Isospin3       G-parity
  //               type    lepton number  baryon number   PDG encoding
  //             stable         lifetime    decay table
  //             shortlived      subType    anti_encoding

   anInstance = new G4ParticleDefinition(
                 name,     5.36679*GeV, 4.359e-10*MeV,          0.,
                    0,              -1,             0,
                    0,               0,             0,
              "meson",               0,             0,         531,
                false,     1.510e-3*ns,          NULL,
                false,       "Bs");
  }
  theInstance = reinterpret_cast<G4BsMesonZero*>(anInstance);
  return theInstance;
}

G4BsMesonZero*  G4BsMesonZero::BsMesonZeroDefinition()
{
  return Definition();
}

G4BsMesonZero*  G4BsMesonZero::BsMesonZero()
{
  return Definition();
}

