//
//Copyright (c) Copyright Holders of the Geant4 Collaboration, 1994-2006.
//See http://cern.ch/geant4/license for details on the copyright holders. All rights not expressly granted under this license are reserved.
//

// Changes in code by:
// Copyright 2021 A. Carolina G. B.
// Licensed under the Apache License, Version 2.0 (the "License");

//// Implementation to include extra geometry in example B2a 
//   in Geant4 version 10.6.p02 
//   
//  
//
/// \file B2aDetectorConstruction.cc
/// \brief Implementation of the B2aDetectorConstruction class
 

#include "G4LogicalSkinSurface.hh"
#include "G4SurfaceProperty.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"


#include "G4EllipticalTube.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4ThreadLocal 
G4GlobalMagFieldMessenger* B2aDetectorConstruction::fMagFieldMessenger = 0;

B2aDetectorConstruction::B2aDetectorConstruction()
:G4VUserDetectorConstruction(), 
 fNbOfChambers(0),
 fLogicTarget(NULL), fLogicChamber(NULL), fLogicSource(NULL),
 fTargetMaterial(NULL), fChamberMaterial(NULL), 
 fStepLimit(NULL),
 fCheckOverlaps(true)
{
  fMessenger = new B2aDetectorMessenger(this);

  fNbOfChambers = 5;
  fLogicChamber = new G4LogicalVolume*[fNbOfChambers];
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B2aDetectorConstruction::DefineVolumes()
{
  G4Material* air  = G4Material::GetMaterial("G4_lAr");

  //            ......
  //             ..
  //             ..
  //             ..
  //             ..
  //             ..

 G4Material* qluminio=nistManager->FindOrBuildMaterial("G4_Al");
G4double diamc=2.0*cm;
G4double espec=0.05*mm;


G4ThreeVector posAlualpha= G4ThreeVector(0,0,-50*cm+(espec*0.5));

 G4EllipticalTube* alualpha = new G4EllipticalTube("alualpha", diamc*0.5, diamc*0.5, espec);
  
       
fLogicSource= new G4LogicalVolume(alualpha, qluminio, "logAluminio");

new G4PVPlacement(0, posAlualpha, fLogicSource, "alumalpha",worldLV,true,0,fCheckOverlaps);


  //            ......
  //             ..
  //             ..
  //             ..
  //             ..
  //             ..



	G4SurfaceProperty *prolAr = new G4SurfaceProperty();
	prolAr->SetName("namsurlAr");
	prolAr->SetType(dielectric_metal);
	new G4LogicalSkinSurface ("parA", fLogicSource, prolAr);




//**********************************************************************************************************************   END

