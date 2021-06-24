//
//Copyright (c) Copyright Holders of the Geant4 Collaboration, 1994-2006.
//See http://cern.ch/geant4/license for details on the copyright holders. All rights not expressly granted under this license are reserved.
//

// Changes in code by:
// Copyright 2021 A. Carolina G. B.
// Licensed under the Apache License, Version 2.0 (the "License");

//// Changes from the Original Code for example B2a in Geant4 version 10.6.p02 
////   The actual Primary Particle properties were all modified
//
//
/// \file B2PrimaryGeneratorAction.cc
/// \brief Implementation of the B2PrimaryGeneratorAction class

#include "B2PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2PrimaryGeneratorAction::B2PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic

  // Carolina -----> from here
  G4ParticleDefinition* particleDefinition 
    = G4ParticleTable::GetParticleTable()->FindParticle("alpha");

G4double sign=-1.0;
if(G4UniformRand()>0.5)
	sign=1.0;
  fParticleGun->SetParticleDefinition(particleDefinition);
	G4double phi = (CLHEP::pi)*(G4UniformRand());
	G4double pz = std::cos(phi);
 sign=-1.0;
if(G4UniformRand()>0.5)
  sign=1.0;
	G4double tet = (CLHEP::pi)*2.0*G4UniformRand();
	G4double px =std::sin(phi)*std::cos(tet);
	G4double py =std::sin(phi)*std::sin(tet);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));

  G4double ranum = 100*G4UniformRand();
  if ( ranum <= 22.2 )
	fParticleGun->SetParticleEnergy(2.2*GeV);
  else if ( ranum > 22.2 & ranum < 75.1)
	fParticleGun->SetParticleEnergy(2.5*GeV);

  else
	fParticleGun->SetParticleEnergy(2.6*GeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2PrimaryGeneratorAction::~B2PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the begining of event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume
  // from G4LogicalVolumeStore.

  G4double worldZHalfLength = 0;
  G4LogicalVolume* worldLV
    = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
  G4Box* worldBox = NULL;
  if ( worldLV ) worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
  if ( worldBox ) worldZHalfLength = worldBox->GetZHalfLength();
  else  {
    G4cerr << "World volume of box not found." << G4endl;
    G4cerr << "Perhaps you have changed geometry." << G4endl;
    G4cerr << "The gun will be place in the center." << G4endl;
  }

  // Carolina -----> from here

G4double diamc=2.0*cm*0.5;
G4double espec=0.05*mm*0.5;

G4double sign=-1.0;
if(G4UniformRand()>0.5)
	sign=1.0;
 
G4double equi=diamc*sign*G4UniformRand();

sign=-1.0;
if(G4UniformRand()>0.5)
	sign=1.0;

G4double yee = sign*std::sqrt(diamc*diamc-(equi*equi));

sign=-1.0;
if(G4UniformRand()>0.5)
	sign=1.0;

G4double zzz =-50*cm+(sign*espec*G4UniformRand());

  fParticleGun->SetParticlePosition(G4ThreeVector(equi, yee, zzz));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
