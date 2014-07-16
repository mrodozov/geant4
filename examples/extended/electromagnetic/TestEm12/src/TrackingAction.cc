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
/// \file electromagnetic/TestEm12/src/TrackingAction.cc
/// \brief Implementation of the TrackingAction class
//
// $Id: TrackingAction.cc 73024 2013-08-15 09:11:40Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TrackingAction.hh"

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "HistoManager.hh"

#include "G4Track.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::TrackingAction(RunAction* run,
                               PrimaryGeneratorAction* kin)
:G4UserTrackingAction(),
 fRunAction(run), fKinematic(kin)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PostUserTrackingAction(const G4Track* track)
{
 // histograms
 //
 G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 
 G4int trackID = track->GetTrackID();
  
 //track length of primary particle or charged secondaries
 //
 G4double tracklen = track->GetTrackLength();
 if (trackID == 1) {
    fRunAction->AddTrackLength(tracklen);
    analysisManager->FillH1(3, tracklen);
 } else if (track->GetDefinition()->GetPDGCharge() != 0.)
    analysisManager->FillH1(6, tracklen);
           
 //extract projected range of primary particle
 //
 if (trackID == 1) {
   G4double pr = (track->GetPosition())*
                 (fKinematic->GetParticleGun()->GetParticleMomentumDirection());
   fRunAction->AddProjRange(pr);
   analysisManager->FillH1(5, pr);
 }
            
 //mean step size of primary particle
 //
 if (trackID == 1) {
   G4int nbOfSteps = track->GetCurrentStepNumber();
   G4double stepSize = tracklen/nbOfSteps;
   fRunAction->AddStepSize(nbOfSteps,stepSize);
 }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

