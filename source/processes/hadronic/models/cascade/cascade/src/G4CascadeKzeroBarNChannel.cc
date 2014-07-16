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
// $Id: G4CascadeKzeroBarNChannel.cc 67796 2013-03-08 06:18:39Z mkelsey $
//
// 20100804  M. Kelsey -- Add name string to ctor
// 20110719  M. Kelsey -- Add initial state code to ctor
// 20110725  M. Kelsey -- Instantiate cross-section object for self-registration
// 20110916  M. Kelsey -- Drop self-registration due to platform inconsistencies

#include "G4CascadeKzeroBarNChannel.hh"
#include "G4InuclParticleNames.hh"
using namespace G4InuclParticleNames;

namespace {
  // Outgoing particle types of a given multiplicity

  static const G4int kzbn2bfs[8][2] =
    {{2, 17}, {1, 13}, {7, 21},  {5, 23}, 
     {7, 25}, {3, 27}, {15, 29}, {11, 31} };

  static const G4int kzbn3bfs[20][3] =
    {{2,7,17},   {2,3,13},   {1,5,17},   {1,7,13},   {7,7,21},
     {3,5,21},   {11,13,21}, {15,17,21}, {5,7,23},   {13,15,23},
     {7,7,25},   {3,5,25},   {11,13,25}, {15,17,25}, {3,7,27},
     {11,17,27}, {7,15,29},  {5,11,29},  {3,15,31},  {7,11,31} };

  static const G4int kzbn4bfs[34][4] =
    {{2,7,7,17},   {2,3,5,17},   {2,3,7,13},   {1,5,7,17}, 
     {1,7,7,13},   {1,3,5,13},   {7,7,7,21},   {3,5,7,21},
     {3,13,15,21}, {5,11,17,21}, {7,11,13,21}, {7,15,17,21},
     {5,7,7,23},   {3,5,5,23},   {7,7,7,25},   {3,5,7,25},
     {3,7,7,27},   {3,3,5,27},   {7,13,15,23}, {5,11,13,23},
     {5,15,17,23}, {3,13,15,25}, {5,11,17,25}, {7,11,13,25},
     {7,15,17,25}, {3,11,13,27}, {3,15,17,27}, {7,11,17,27},
     {7,7,15,29},  {3,5,15,29},  {5,7,11,29},  {3,7,15,31},
     {7,7,11,31},  {3,5,11,31} };

  static const G4int kzbn5bfs[48][5] =
    {{2,7,7,7,17},   {2,3,5,7,17},   {2,3,7,7,13},   {2,3,3,5,13},
     {1,5,7,7,17},   {1,3,5,5,17},   {1,7,7,7,13},   {1,3,5,7,13},   
     {7,7,7,7,21},   {3,5,7,7,21},   {3,3,5,5,21},   {3,7,13,15,21},
     {5,7,11,17,21}, {7,7,11,13,21}, {3,5,11,13,21}, {7,7,15,17,21}, 
     {3,5,15,17,21}, {5,7,7,7,23},   {3,5,5,7,23},   {7,7,13,15,23},
     {3,5,13,15,23}, {5,7,11,13,23}, {5,7,15,17,23}, {5,5,11,17,23},
     {7,7,7,7,25},   {3,5,7,7,25},   {3,3,5,5,25},   {3,7,13,15,25},
     {5,7,11,17,25}, {7,7,11,13,25}, {3,5,11,13,25}, {7,7,15,17,25},
     {3,5,15,17,25}, {3,7,7,7,27},   {3,3,5,7,27},   {3,7,11,13,27},
     {3,7,15,17,27}, {7,7,11,17,27}, {3,5,11,17,27}, {3,3,13,15,27},
     {7,7,7,15,29},  {3,5,7,15,29},  {5,7,7,11,29},  {3,5,5,11,29},
     {7,7,7,11,31},  {3,5,7,11,31},  {3,7,7,15,31},  {3,3,5,15,31} };

  static const G4int kzbn6bfs[22][6] =
    {{2,7,7,7,7,17}, {2,3,5,7,7,17}, {2,3,3,5,5,17}, {2,3,7,7,7,13}, 
     {2,3,3,5,7,13}, {1,5,7,7,7,17}, {1,3,5,5,7,17}, {1,7,7,7,7,13},
     {1,3,5,7,7,13}, {1,3,3,5,5,13}, {7,7,7,7,7,21}, {3,5,7,7,7,21}, 
     {3,3,5,5,7,21}, {5,7,7,7,7,23}, {3,5,5,7,7,23}, {3,3,5,5,5,23},
     {7,7,7,7,7,25}, {3,5,7,7,7,25}, {3,3,5,5,7,25}, {3,7,7,7,7,27},
     {3,3,5,7,7,27}, {3,3,3,5,5,27} };

  static const G4int kzbn7bfs[16][7] =
    {{2,7,7,7,7,7,17}, {2,3,5,7,7,7,17}, {2,3,3,5,5,7,17},
     {2,3,7,7,7,7,13}, {2,3,3,5,7,7,13}, {2,3,3,3,5,5,13},
     {1,5,7,7,7,7,17}, {1,3,5,5,7,7,17}, {1,3,3,5,5,5,17},
     {1,7,7,7,7,7,13}, {1,3,5,7,7,7,13}, {1,3,3,5,5,7,13},
     {7,7,7,7,7,7,21}, {3,5,7,7,7,7,21}, {3,3,5,5,7,7,21},
     {3,3,3,5,5,5,21} };

  // Cross sections for K0bar n -> 2-7 body final states
  // 
  // first index:    0-7: channels for mult = 2
  //                8-27: channels for mult = 3 
  //               28-61: channels for mult = 4
  //              62-109: channels for mult = 5
  //             110-131: channels for mult = 6
  //             132-147: channels for mult = 7
  //
  // second index: kinetic energy
  // 
  static const G4double kzbnCrossSections[148][31] = {
    //
    // multiplicity 2 (8 channels)
    //  
    // K0bar n 
    {400.0,110.0, 37.6, 29.0, 22.29,21.0, 21.0, 21.0, 21.0, 21.0,
     21.0, 10.98, 7.66, 6.51, 5.41, 5.02, 4.63, 4.30, 4.00, 3.90,
     3.80, 3.70, 3.60, 3.60, 3.50, 3.40, 3.30, 3.20, 3.20, 3.18, 3.00},

    // K- p
    {173.0, 36.75, 8.0,  9.75, 4.81, 4.61, 4.86, 5.12, 5.37, 5.63,
     5.88, 2.78, 1.13, 0.75, 0.50, 0.36, 0.27, 0.22, 0.18, 0.15,
     0.13, 0.11, 0.10, 0.09, 0.08, 0.07, 0.07, 0.06, 0.06, 0.06, 0.03},
 
    // L pi0
    {325.0, 62.08, 5.37, 3.88, 3.13, 3.00, 3.00, 3.00, 3.00, 3.00,
     3.00, 1.55, 0.62, 0.29, 0.17, 0.11, 0.07, 0.05, 0.04, 0.03,
     0.03, 0.02, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01},
 
    // S+ pi-
    {241.0, 50.17,11.41, 9.52, 6.54, 5.58, 5.06, 4.55, 4.03, 3.52,
     3.01, 1.22, 0.69, 0.42, 0.29, 0.21, 0.15, 0.12, 0.10, 0.09,
     0.08, 0.07, 0.06, 0.05, 0.05, 0.04, 0.04, 0.03, 0.03, 0.03, 0.02},
 
    // S0 pi0
    {243.0, 47.17, 5.02, 6.78, 2.80, 2.52, 2.30, 2.08, 1.86, 1.64,
     1.42, 0.33, 0.09, 0.03, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,
     0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    // S- pi+
    {615.0,112.9,  7.40, 6.45, 3.46, 2.84, 2.65, 2.45, 2.26, 2.07,
     1.87, 0.56, 0.19, 0.07, 0.03, 0.12, 0.02, 0.01, 0.0,  0.0,
     0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    // X0 K0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.06, 0.05, 0.02, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    // X- K+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.15, 0.11, 0.07, 0.03, 0.02, 0.01, 0.01, 0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    //
    //  multiplicity 3 (20 channels)
    //
    // n K0bar pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.10, 0.22, 0.34, 0.46, 0.58,
      0.70, 1.44, 1.51, 1.23, 1.02, 0.88, 0.76, 0.67, 0.60, 0.54,
      0.49, 0.45, 0.41, 0.38, 0.36, 0.34, 0.32, 0.30, 0.29, 0.28, 0.19},
 
    // n K- pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.06, 0.13, 0.20, 0.28, 0.35,
      0.42, 1.57, 1.89, 1.54, 1.23, 0.97, 0.78, 0.65, 0.54, 0.46,
      0.40, 0.36, 0.33, 0.30, 0.28, 0.26, 0.25, 0.23, 0.21, 0.20, 0.14},
 
    // p K0bar pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.07, 0.15, 0.24, 0.32, 0.41,
      0.49, 2.07, 2.49, 2.10, 1.74, 1.52, 1.32, 1.15, 1.00, 0.89,
      0.80, 0.75, 0.70, 0.65, 0.60, 0.56, 0.53, 0.50, 0.48, 0.46, 0.31},
 
    // p K- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.08, 0.18, 0.27, 0.37, 0.47,
      0.56, 1.13, 1.07, 0.83, 0.80, 0.80, 0.76, 0.74, 0.72, 0.67,
      0.61, 0.58, 0.53, 0.50, 0.47, 0.44, 0.42, 0.40, 0.38, 0.37, 0.31},
 
    // L 2pi0
    { 0.0,  0.0,  0.24, 1.48, 1.10, 1.24, 1.40, 1.56, 1.73, 1.89,
      2.06, 1.59, 0.86, 0.54, 0.46, 0.41, 0.31, 0.24, 0.19, 0.15,
      0.12, 0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.05, 0.04, 0.04, 0.02},
 
    // L pi+ pi-
    { 0.0,  0.0,  0.44, 1.05, 1.42, 1.76, 2.07, 2.39, 2.70, 3.02,
      3.33, 2.65, 1.62, 0.92, 0.62, 0.43, 0.31, 0.24, 0.19, 0.15,
      0.12, 0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.05, 0.04, 0.04, 0.02},
 
    // L K+ K- 
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.05, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.04, 
      0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.01},
 
    // L K0 K0bar
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.03, 0.05, 0.06, 0.05, 0.04, 0.04, 0.04, 0.05,
      0.05, 0.05, 0.05, 0.05, 0.05, 0.04, 0.04, 0.04, 0.03, 0.03, 0.01},
 
    // S+ pi- pi0
    { 0.0,  0.0,  0.06, 0.10, 0.17, 0.27, 0.35, 0.43, 0.51, 0.60,
      0.68, 1.06, 0.90, 0.67, 0.46, 0.33, 0.26, 0.20, 0.16, 0.13,
      0.11, 0.09, 0.08, 0.07, 0.06, 0.05, 0.05, 0.04, 0.04, 0.04, 0.02},
 
    // S+ K- K0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.02, 0.01, 0.01, 0.01, 0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    // S0 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.12, 0.14, 0.17, 0.19, 0.22,
      0.24, 0.45, 0.37, 0.25, 0.18, 0.11, 0.08, 0.06, 0.04, 0.03,
      0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0,  0.0,  0.0},
 
    // S0 pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.14, 0.19, 0.24, 0.28, 0.33,
      0.38, 0.74, 0.61, 0.42, 0.29, 0.20, 0.14, 0.10, 0.07, 0.05,
      0.04, 0.03, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0,  0.0},
 
    // S0 K+ K-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.03, 0.02, 0.02, 0.02, 0.01, 0.01, 0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    // S0 K0 K0bar
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.02, 0.03, 0.03, 0.03, 0.02, 0.02, 0.02,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.0},
  
    // S- pi+ pi0
    { 0.0,  0.0,  0.0,  0.10, 0.10, 0.16, 0.24, 0.32, 0.39, 0.47,
      0.54, 0.79, 0.72, 0.45, 0.25, 0.15, 0.09, 0.06, 0.04, 0.03,
      0.02, 0.02, 0.01, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    // S- K+ K0bar
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0},
 
    // X0 K0 pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.02, 0.03, 0.04, 0.04, 0.04, 0.05, 0.05, 0.04,
      0.04, 0.02, 0.02, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    // X0 K+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.05, 0.06, 0.02, 0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // X- K0 pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.08, 0.08, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01,
      0.01, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    // X- K+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.03, 0.04, 0.03, 0.02, 0.02, 0.01, 0.01, 0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0,  0.0},
 
    //
    //  multiplicity 4 (34 channels)
    //
    // n K0bar 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.11, 0.44, 0.72, 0.78, 0.72, 0.69, 0.66, 0.63, 0.61,
      0.60, 0.58, 0.57, 0.55, 0.54, 0.53, 0.52, 0.50, 0.49, 0.48, 0.43},
 
    // n K0bar pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.17, 0.73, 1.20, 1.30, 1.21, 1.15, 1.10, 1.05, 1.02,
      1.00, 0.97, 0.95, 0.92, 0.90, 0.88, 0.86, 0.84, 0.82, 0.81, 0.71},
 
    // n K- pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.08, 0.46, 0.99, 1.10, 1.00, 0.94, 0.89, 0.85, 0.81,
      0.78, 0.75, 0.72, 0.70, 0.68, 0.66, 0.64, 0.62, 0.61, 0.60, 0.51},
 
    // p K0bar pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.11, 0.28, 0.52, 0.55, 0.50, 0.47, 0.45, 0.43, 0.40,
      0.39, 0.38, 0.36, 0.35, 0.34, 0.33, 0.32, 0.31, 0.30, 0.30, 0.25},
 
    // p K- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.06, 0.28, 0.50, 0.63, 0.71, 0.79, 0.78, 0.72, 0.65,
      0.59, 0.54, 0.49, 0.45, 0.41, 0.38, 0.36, 0.33, 0.31, 0.30, 0.19},
 
    // p K- pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.10, 0.45, 0.83, 1.05, 1.07, 0.94, 0.83, 0.72, 0.65,
      0.59, 0.54, 0.49, 0.45, 0.41, 0.38, 0.36, 0.33, 0.31, 0.30, 0.19},
 
    // L 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.05, 0.08, 0.11, 0.13,
      0.16, 1.13, 1.59, 1.33, 1.12, 1.10, 0.86, 0.70, 0.34, 0.28,
      0.38, 0.32, 0.27, 0.23, 0.11, 0.10, 0.08, 0.07, 0.06, 0.05, 0.02},
 
    // L pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.04, 0.09, 0.13, 0.18, 0.23,
      0.27, 1.77, 2.19, 1.84, 1.44, 1.12, 0.86, 0.70, 0.56, 0.46,
      0.38, 0.32, 0.27, 0.23, 0.19, 0.16, 0.14, 0.12, 0.10, 0.09, 0.03},
 
    // L K- K0 pi+ 
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.03, 0.02, 0.02, 0.03, 0.03, 0.03, 0.03,
      0.03, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02},
 
    // L K+ K0bar pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.03, 0.02, 0.02,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.01},
 
    // L K+ K- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.03, 0.05, 0.07, 0.08, 0.08, 0.08,
      0.09, 0.09, 0.09, 0.09, 0.09, 0.09, 0.08, 0.08, 0.08, 0.08, 0.07},
 
    // L K0 K0bar pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03, 0.03,
      0.04, 0.04, 0.05, 0.05, 0.06, 0.06, 0.05, 0.05, 0.04, 0.04, 0.03},
 
    // S+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.02, 
      0.02, 0.09, 0.16, 0.16, 0.14, 0.13, 0.11, 0.10, 0.09, 0.08,
      0.08, 0.07, 0.07, 0.07, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05, 0.01},
 
    // S+ pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.03,
      0.04, 0.14, 0.26, 0.26, 0.24, 0.21, 0.19, 0.17, 0.15, 0.14,
      0.13, 0.12, 0.11, 0.11, 0.10, 0.10, 0.09, 0.09, 0.08, 0.07, 0.02},
 
    // S0 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.04, 0.05, 0.06,
      0.08, 0.22, 0.29, 0.35, 0.41, 0.36, 0.25, 0.20, 0.17, 0.14,
      0.11, 0.10, 0.08, 0.07, 0.06, 0.05, 0.04, 0.04, 0.03, 0.03, 0.01},
 
    // S0 pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.04, 0.06, 0.09, 0.11,
      0.13, 0.36, 0.49, 0.59, 0.69, 0.59, 0.41, 0.33, 0.28, 0.23,
      0.19, 0.16, 0.14, 0.12, 0.10, 0.08, 0.07, 0.06, 0.05, 0.05, 0.02},
 
    // S- pi+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.06, 0.10, 0.12, 0.11, 0.09, 0.07, 0.07, 0.06, 0.05,
      0.05, 0.04, 0.04, 0.04, 0.03, 0.03, 0.02, 0.02, 0.02, 0.02, 0.01},
 
    // S- 2pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.01, 0.10, 0.18, 0.20, 0.18, 0.15, 0.12, 0.11, 0.10, 0.08,
      0.08, 0.07, 0.06, 0.06, 0.05, 0.05, 0.04, 0.04, 0.04, 0.03, 0.01},
  
    // S+ K- K0 pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.02,
      0.02, 0.02, 0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01},
 
    // S+ K+ K- pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.03, 0.03, 0.03,
      0.03, 0.03, 0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.02, 0.02, 0.01},

    // S+ K0 K0bar pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.03, 0.04, 0.04,
      0.04, 0.04, 0.04, 0.04, 0.03, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01},

    // S0 K- K0 pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.04, 0.04,
      0.04, 0.02, 0.02, 0.02, 0.02, 0.02, 0.0,  0.0,  0.0,  0.0,  0.0},
 
    // S0 K+ K0bar pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.01, 0.02,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    // S0 K+ K- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.02, 0.02,
      0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.02},
 
    // S0 K0 K0bar pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.02,
      0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.03, 0.03, 0.02, 0.02, 0.01},
 
    // S- K+ K- pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.02, 0.02, 
      0.02, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0},
 
    // S- K0 K0bar pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 
      0.02, 0.02, 0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.01, 0.01, 0.0},
 
    // S- K+ K0bar pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01,
      0.01, 0.01, 0.02, 0.02, 0.02, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0},
 
    // X0 K0 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.02, 0.03, 0.03, 0.04, 0.04, 
      0.04, 0.04, 0.04, 0.04, 0.04, 0.02, 0.02, 0.02, 0.01, 0.01, 0.0},
 
    // X0 K0 pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.03, 0.03, 0.03, 0.03, 0.05, 0.05,
      0.06, 0.06, 0.06, 0.06, 0.06, 0.04, 0.04, 0.03, 0.03, 0.03, 0.02},
 
    // X0 K+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.02, 0.02, 0.02,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.01, 0.0,  0.0,  0.0,  0.0},
 
    // X- K0 pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.03, 0.03, 0.02, 0.02,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0},
                                                                          
    // X- K+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    // X- K+ pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02,
      0.01, 0.01, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    //
    //  multiplicity 5 (48 channels)
    // 
    // n K0bar 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.01, 0.06, 0.16, 0.27, 0.38, 0.48, 0.54, 0.55, 0.54,
      0.53, 0.52, 0.52, 0.52, 0.51, 0.50, 0.50, 0.50, 0.49, 0.49, 0.47},
 
    // n K0bar pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.02, 0.10, 0.26, 0.45, 0.64, 0.80, 0.90, 0.92, 0.90,
      0.89, 0.87, 0.87, 0.86, 0.85, 0.84, 0.83, 0.83, 0.82, 0.82, 0.79},
 
    // n K- pi+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.04, 0.09, 0.18, 0.27, 0.32, 0.32, 0.32,
      0.32, 0.32, 0.32, 0.32, 0.31, 0.30, 0.30, 0.30, 0.29, 0.28, 0.24},
                                                                             
    // n K- 2pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.02, 0.06, 0.15, 0.27, 0.32, 0.32, 0.32, 0.32,
      0.32, 0.32, 0.32, 0.32, 0.31, 0.30, 0.30, 0.30, 0.29, 0.28, 0.24},
 
    // p K0bar pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.02, 0.05, 0.12, 0.19, 0.24, 0.25, 0.25, 0.26,
      0.26, 0.27, 0.28, 0.28, 0.28, 0.29, 0.28, 0.28, 0.28, 0.27, 0.20},
 
    // p K0bar pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.01, 0.03, 0.08, 0.20, 0.32, 0.39, 0.41, 0.42, 0.43,
      0.44, 0.45, 0.46, 0.46, 0.47, 0.48, 0.47, 0.47, 0.46, 0.45, 0.33},
 
    // p K- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.02, 0.05, 0.12, 0.21, 0.34, 0.42, 0.44, 0.47,
      0.48, 0.49, 0.51, 0.51, 0.52, 0.52, 0.53, 0.53, 0.53, 0.52, 0.47},
 
    // p K- pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.01, 0.03, 0.08, 0.20, 0.36, 0.57, 0.69, 0.74, 0.77,
      0.79, 0.82, 0.83, 0.84, 0.86, 0.87, 0.88, 0.89, 0.88, 0.87, 0.81},
 
    // L 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.01, 0.04, 0.06, 0.09, 0.15, 0.14, 0.13, 0.13, 0.12,
      0.11, 0.11, 0.10, 0.10, 0.03, 0.03, 0.03, 0.03, 0.02, 0.02, 0.01},
 
    // L pi+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.02, 0.05, 0.10, 0.13, 0.15, 0.14, 0.13, 0.13, 0.12,
      0.11, 0.11, 0.10, 0.10, 0.09, 0.09, 0.08, 0.07, 0.06, 0.06, 0.03},
 
    // L 2pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.03, 0.09, 0.16, 0.17, 0.15, 0.14, 0.13, 0.13, 0.12,
      0.11, 0.11, 0.10, 0.10, 0.09, 0.09, 0.08, 0.07, 0.06, 0.06, 0.03},
 
    // L K- K0 pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.03,
      0.04, 0.04, 0.05, 0.05, 0.05, 0.05, 0.04, 0.04, 0.03, 0.03, 0.02},
 
    // L K+ K0bar pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03,
      0.04, 0.06, 0.07, 0.07, 0.07, 0.07, 0.06, 0.06, 0.05, 0.05, 0.04},
 
    // L K+ K- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02},
 
    // L K+ K- pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02},
 
    // L K0 K0bar 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.04, 0.07, 0.05, 0.06,
      0.07, 0.08, 0.08, 0.07, 0.07, 0.07, 0.06, 0.06, 0.06, 0.06, 0.03},
 
    // L K0 K0bar pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.04, 0.05, 0.06,
      0.07, 0.08, 0.08, 0.07, 0.07, 0.07, 0.06, 0.06, 0.06, 0.06, 0.03},
 
    // S+ pi- 3pi0 
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.04, 0.11, 0.14, 0.14, 0.14, 0.14, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.14, 0.14, 0.12},

    // S+ pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.01, 0.07, 0.19, 0.24, 0.24, 0.24, 0.24, 0.25, 0.25,
      0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.24, 0.24, 0.20},
 
    // S+ K- K0 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    // S+ K- K0 pi+ pi- 
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02},
 
    // S+ K+ K- pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02},
 
    // S+ K0 K0bar pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.02, 0.04, 0.04, 0.04, 0.04, 0.04, 0.03, 0.03, 0.02, 0.02, 0.02},
 
    // S+ K+ K0bar 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0},
 
    // S0 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.03, 0.02,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01},
 
    // S0 pi+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.02, 0.07, 0.04, 0.04, 0.04, 0.04, 0.04,
      0.04, 0.04, 0.03, 0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.02, 0.01},
 
    // S0 2pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.02, 0.03, 0.03, 0.07, 0.07, 0.07, 0.07, 0.06,
      0.06, 0.06, 0.05, 0.05, 0.05, 0.05, 0.04, 0.03, 0.03, 0.03, 0.02},
 
    // S0 K- K0 pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.04,
      0.04, 0.06, 0.06, 0.06, 0.05, 0.05, 0.04, 0.04, 0.03, 0.03, 0.03},
 
    // S0 K+ K0bar pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.04,
      0.04, 0.04, 0.04, 0.04, 0.03, 0.03, 0.02, 0.02, 0.02, 0.02, 0.01},
 
    // S0 K+ K- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},
 
    // S0 K+ K- pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},
 
    // S0 K0 K0bar 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.02,
      0.04, 0.04, 0.04, 0.04, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.02},
 
    // S0 K0 K0bar pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.04,
      0.06, 0.07, 0.07, 0.07, 0.07, 0.06, 0.06, 0.05, 0.05, 0.05, 0.04},
 
    // S- pi+ 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.04, 0.09, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11,
      0.11, 0.11, 0.12, 0.12, 0.12, 0.12, 0.11, 0.11, 0.11, 0.11, 0.08},
                                                                              
    // S- 2pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.01, 0.06, 0.14, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19,
      0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.19, 0.19, 0.18, 0.18, 0.14},
 
    // S- K+ K- pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01,
      0.02, 0.03, 0.04, 0.05, 0.06, 0.06, 0.07, 0.08, 0.09, 0.09, 0.09},
 
    // S- K0 K0bar pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01,
      0.02, 0.03, 0.04, 0.05, 0.06, 0.06, 0.07, 0.08, 0.09, 0.09, 0.09},
 
    // S- K+ K0bar 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01},
 
    // S- K+ K0bar pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02},
 
    // S- K- K0 2pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},
 
    // X0 K0 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.04,
      0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.03, 0.02, 0.02, 0.02, 0.02},
 
    // X0 K0 pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.03, 0.04, 0.05,
      0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.05, 0.03, 0.05, 0.05, 0.04},
 
    // X0 K+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.02,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02},
 
    // X0 K+ pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03,
      0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03},
  
    // X- K+ 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.02, 
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02},
 
    // X- K+ pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03,
      0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03},
 
    // X- K0 pi+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.04,
      0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.03, 0.03, 0.02, 0.02, 0.02},
 
    // X- K0 2pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.03, 0.04, 0.05,
      0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.04, 0.04, 0.03},

    //
    //  multiplicity 6 (22 channels)
    // 
    // n K0bar 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.03, 0.03, 0.04,
      0.04, 0.04, 0.05, 0.05, 0.06, 0.06, 0.07, 0.07, 0.07, 0.07, 0.08},
 
    // n K0bar pi+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.03, 0.04, 0.05, 0.05, 0.06,
      0.07, 0.07, 0.08, 0.08, 0.10, 0.10, 0.11, 0.11, 0.12, 0.12, 0.13},
 
    // n K0bar 2pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.03, 0.05, 0.06, 0.08, 0.09, 0.10,
      0.11, 0.12, 0.13, 0.14, 0.16, 0.17, 0.18, 0.19, 0.20, 0.20, 0.21},
 
    // n K- pi+ 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.06, 0.15, 0.24, 0.29, 0.34,
      0.39, 0.40, 0.41, 0.43, 0.44, 0.46, 0.48, 0.50, 0.53, 0.53, 0.57},
 
    // n K- 2pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.08, 0.17, 0.24, 0.29, 0.34,
      0.39, 0.40, 0.41, 0.43, 0.44, 0.46, 0.48, 0.50, 0.53, 0.53, 0.57},
 
    // p K0bar pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.06, 0.09, 0.12, 0.14, 0.17,
      0.19, 0.20, 0.20, 0.22, 0.22, 0.23, 0.24, 0.25, 0.26, 0.26, 0.28},
 
    // p K0bar pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.03, 0.09, 0.15, 0.20, 0.24, 0.28,
      0.32, 0.33, 0.34, 0.36, 0.36, 0.38, 0.40, 0.41, 0.44, 0.44, 0.47},

    // p K- 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.04, 0.05, 0.05, 0.06,
      0.07, 0.07, 0.09, 0.11, 0.11, 0.14, 0.16, 0.16, 0.18, 0.18, 0.17},
 
    // p K- pi+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.05, 0.06, 0.09, 0.09, 0.10,
      0.11, 0.12, 0.14, 0.16, 0.17, 0.19, 0.21, 0.23, 0.25, 0.25, 0.20},
 
    // p K- 2pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.06, 0.07, 0.08, 0.09, 0.10,
      0.11, 0.12, 0.14, 0.16, 0.17, 0.19, 0.21, 0.23, 0.25, 0.25, 0.20},

    // L 5pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.04, 0.07, 0.15, 0.20, 0.23, 0.27, 0.31,
      0.34, 0.34, 0.33, 0.33, 0.32, 0.31, 0.26, 0.21, 0.16, 0.16, 0.13},
 
    // L pi+ pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.02, 0.05, 0.09, 0.16, 0.20, 0.23, 0.27, 0.31,
      0.34, 0.34, 0.33, 0.33, 0.32, 0.31, 0.26, 0.21, 0.16, 0.16, 0.13},

    // L 2pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.03, 0.11, 0.12, 0.16, 0.20, 0.23, 0.27, 0.31,
      0.34, 0.34, 0.33, 0.33, 0.32, 0.31, 0.26, 0.21, 0.16, 0.16, 0.13},

    // S+ pi- 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.04, 0.07, 0.09, 0.09,
      0.09, 0.09, 0.09, 0.09, 0.09, 0.08, 0.08, 0.08, 0.08, 0.08, 0.07},

    // S+ pi+ 2pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.04, 0.06, 0.12, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.14, 0.14, 0.14, 0.14, 0.13, 0.13, 0.13, 0.11},

    // S+ 2pi+ 3pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.03, 0.06, 0.10, 0.20, 0.25, 0.25,
      0.25, 0.25, 0.25, 0.24, 0.24, 0.23, 0.23, 0.22, 0.21, 0.21, 0.19},

    // S0 5pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.03, 0.04, 0.05, 0.06, 0.07,
      0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.06, 0.05, 0.04, 0.04, 0.03},

    // S0 pi+ pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.05, 0.07, 0.08, 0.10, 0.11,
      0.12, 0.12, 0.12, 0.12, 0.11, 0.11, 0.10, 0.08, 0.06, 0.06, 0.05},

    // S0 2pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.03, 0.08, 0.11, 0.14, 0.16, 0.19,
      0.20, 0.20, 0.20, 0.20, 0.19, 0.19, 0.16, 0.13, 0.10, 0.10, 0.08},

    // S- pi+ 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.04, 0.05, 0.07, 0.07,
      0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.06, 0.06, 0.06, 0.06, 0.06},

    // S- 2pi+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.04, 0.06, 0.09, 0.11, 0.11,
      0.12, 0.12, 0.12, 0.12, 0.11, 0.11, 0.11, 0.11, 0.10, 0.10, 0.10},

    // S- 3pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.06, 0.10, 0.15, 0.19, 0.19,
      0.20, 0.20, 0.20, 0.20, 0.19, 0.19, 0.18, 0.18, 0.17, 0.17, 0.16},

    //
    //  multiplicity 7 (16 channels)
    // 
    // n K0bar 5pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.03, 0.05,
      0.06, 0.07, 0.08, 0.09, 0.10, 0.12, 0.13, 0.14, 0.16, 0.17, 0.21},
 
    // n K0bar pi+ pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.05, 0.08,
      0.10, 0.11, 0.14, 0.16, 0.17, 0.20, 0.22, 0.24, 0.26, 0.28, 0.35},
 
    // n K0bar 2pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.04, 0.09, 0.13,
      0.16, 0.19, 0.23, 0.26, 0.29, 0.33, 0.36, 0.40, 0.43, 0.45, 0.58},
 
    // n K- pi+ 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.02, 0.02,
      0.02, 0.02, 0.02, 0.03, 0.04, 0.04, 0.04, 0.06, 0.06, 0.06, 0.07},
 
    // n K- 2pi+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03,
      0.03, 0.04, 0.04, 0.05, 0.06, 0.06, 0.07, 0.08, 0.09, 0.09, 0.09},
 
    // n K- 3pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03,
      0.03, 0.04, 0.04, 0.05, 0.06, 0.06, 0.07, 0.08, 0.09, 0.09, 0.09},
 
    // p K0bar pi- 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.02, 0.03,
      0.03, 0.04, 0.04, 0.05, 0.05, 0.05, 0.06, 0.06, 0.07, 0.07, 0.07},
 
    // p K0bar pi+ 2pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.03, 0.04, 0.05,
      0.05, 0.06, 0.07, 0.08, 0.08, 0.09, 0.10, 0.10, 0.11, 0.11, 0.11},
 
    // p K0bar 2pi+ 3pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.03, 0.04, 0.05, 0.06, 0.08,
      0.09, 0.10, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.18},
 
    // p K- 5pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.05, 0.09,
      0.11, 0.13, 0.15, 0.17, 0.19, 0.23, 0.26, 0.28, 0.32, 0.34, 0.45},
 
    // p K- pi+ pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.03, 0.03, 0.09, 0.14,
      0.18, 0.20, 0.26, 0.30, 0.32, 0.39, 0.45, 0.49, 0.53, 0.53, 0.55},
 
    // p K- 2pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.04, 0.07, 0.16, 0.23,
      0.29, 0.35, 0.42, 0.48, 0.55, 0.64, 0.73, 0.81, 0.83, 0.83, 0.87},
 
    // L 6pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.02, 0.02, 0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.01},
 
    // L pi+ pi- 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.02, 0.02, 0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.01},
 
    // L 2pi+ 2pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.01},
 
    // L 3pi+ 3pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.01} };
}

const G4CascadeKzeroBarNChannelData::data_t
G4CascadeKzeroBarNChannelData::data(kzbn2bfs, kzbn3bfs, kzbn4bfs,
				    kzbn5bfs, kzbn6bfs, kzbn7bfs,
				    kzbnCrossSections, k0b*neu, "KzeroBarN");
