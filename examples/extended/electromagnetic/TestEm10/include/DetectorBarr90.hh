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
/// \file electromagnetic/TestEm10/include/DetectorBarr90.hh
/// \brief Definition of the DetectorBarr90 class
//
//
// $Id: DetectorBarr90.hh 72513 2013-07-24 20:37:54Z gum $
//
// Setuo from G.D. Barr et al NIM A294 (1990) 465-472 (fig.11)

#ifndef DetectorBarr90_h
#define DetectorBarr90_h 1

#include "globals.hh"

#include "RadiatorDescription.hh"

class G4VPhysicalVolume;

class DetectorBarr90 
{
  public:
    DetectorBarr90();
    ~DetectorBarr90();

    // methods
    G4VPhysicalVolume* Construct();

    // get methods
    RadiatorDescription* GetRadiatorDescription() const { return fRadiatorDescription; }

  private:
    // data members
    RadiatorDescription* fRadiatorDescription; 
};

#endif
