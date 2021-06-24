//
//Copyright (c) Copyright Holders of the Geant4 Collaboration, 1994-2006.
//See http://cern.ch/geant4/license for details on the copyright holders. All rights not expressly granted under this license are reserved.
//

// Changes in code by:
// Copyright 2021 A. Carolina G. B.
// Licensed under the Apache License, Version 2.0 (the "License");

//// Changes from the Original Code for example B2a in Geant4 version 10.6.p02 
//   Based on other examples in Geant4 as B5
//   The actual way to record the information and what to save is new

/// \file B2EventAction.cc
/// \brief Implementation of the B2EventAction class

#include "B2EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "g4analysis.hh"
#include "B2TrackerHit.hh"
#include "G4SystemOfUnits.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2EventAction::B2EventAction()
: G4UserEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2EventAction::~B2EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2EventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2EventAction::EndOfEventAction(const G4Event* event)
{
  // get number of stored trajectories

  G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
 
     G4VHitsCollection* hc = event->GetHCofThisEvent()->GetHC(0);


 // Carolina -----> from here
G4float totenerc11=0.0;
G4float totenerc22=0.0;
G4float totenerc33=0.0;
G4float totenerc44=0.0;
G4float totenerc55=0.0;
G4float totenerc66=0.0;
 G4int cham = 0;


  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
//newHit->SetTrackID 
for (unsigned int i = 0; i<hc->GetSize(); ++i) {//hits stored in this even
      auto hit = static_cast<B2TrackerHit*>(hc->GetHit(i));
 
cham =hit->GetChamberNb();
if(cham == 1)
 totenerc11+= (hit->GetEdep()/keV);
else if(cham == 2)
 totenerc22+= (hit->GetEdep()/keV);
else if(cham == 3)
 totenerc33+= (hit->GetEdep()/keV);
else if(cham == 4)
 totenerc44+= (hit->GetEdep()/keV);
else if(cham == 5)
 totenerc55+= (hit->GetEdep()/keV);
else if(cham == 6)
 totenerc66+= (hit->GetEdep()/keV);
else
G4cout << "chamber not counting    " <<cham<<G4endl;
    }
  analysisManager->FillNtupleIColumn(0, 0,eventID);
  analysisManager->FillNtupleDColumn(0, 1,totenerc11);
  analysisManager->FillNtupleDColumn(0, 2,totenerc22);
  analysisManager->FillNtupleDColumn(0, 3,totenerc33);
  analysisManager->FillNtupleDColumn(0, 4,totenerc44);
  analysisManager->FillNtupleDColumn(0, 5,totenerc55);
  analysisManager->FillNtupleDColumn(0, 6,totenerc66);

  analysisManager->AddNtupleRow(0);

if (totenerc11!=0.0)
 	analysisManager->FillH1(0, totenerc11);
if (totenerc22!=0.0)
	analysisManager->FillH1(1, totenerc22);
if (totenerc33!=0.0)
 	analysisManager->FillH1(2, totenerc33);
if (totenerc44!=0.0)
	analysisManager->FillH1(3, totenerc44);
if (totenerc55!=0.0)
	analysisManager->FillH1(4, totenerc55);   
 
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//********************************************************************** END
