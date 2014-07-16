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
// $Id: G4FTFBinaryPiKBuilder.hh 66892 2013-01-17 10:57:59Z gunter $
//
//---------------------------------------------------------------------------
//
// ClassName:   G4FTFBinaryPiKBuilder
//
// Author: 2008 G.Folger
//
// Modified:
// 30.03.2009 V.Ivanchenko create cross section by new
//
//----------------------------------------------------------------------------
//
#ifndef G4FTFBinaryPiKBuilder_h
#define G4FTFBinaryPiKBuilder_h 1

#include "globals.hh"

#include "G4HadronElasticProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4VPiKBuilder.hh"

#include "G4TheoFSGenerator.hh"
#include "G4ExcitationHandler.hh"
#include "G4PreCompoundModel.hh"
#include "G4BinaryCascade.hh"
#include "G4FTFModel.hh"
#include "G4LundStringFragmentation.hh"
#include "G4ExcitedStringDecay.hh"
#include "G4QuasiElasticChannel.hh"
#include "G4VCrossSectionDataSet.hh"

class G4FTFBinaryPiKBuilder : public G4VPiKBuilder
{
  public: 
    G4FTFBinaryPiKBuilder(G4bool quasiElastic=false);
    virtual ~G4FTFBinaryPiKBuilder();

  public: 
    virtual void Build(G4HadronElasticProcess * aP);
    virtual void Build(G4PionPlusInelasticProcess * aP);
    virtual void Build(G4PionMinusInelasticProcess * aP);
    virtual void Build(G4KaonPlusInelasticProcess * aP);
    virtual void Build(G4KaonMinusInelasticProcess * aP);
    virtual void Build(G4KaonZeroLInelasticProcess * aP);
    virtual void Build(G4KaonZeroSInelasticProcess * aP);
    
    void SetMinEnergy(G4double aM) {theMin = aM;}

  private:
    G4TheoFSGenerator * theModel;
    G4PreCompoundModel * thePreEquilib;
    G4BinaryCascade * theCascade;
    G4FTFModel * theStringModel;
    G4ExcitedStringDecay * theStringDecay;
    G4QuasiElasticChannel * theQuasiElastic;

    G4VCrossSectionDataSet* thePiData;
    G4double theMin;

};

#endif

