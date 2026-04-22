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
// $Id: IronFilterDTGeneratorAction.cc $
//
/// \file IronFilterDTGeneratorAction.cc
/// \brief Implementation of the IronFilterDTGeneratorAction class

#include "TFile.h"

#include "TTree.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1D.h"
#include "THStack.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TMinuit.h"
#include "TColor.h"
#include "TLine.h"
#include "TLatex.h"
#include "TSystem.h"
#include "TApplication.h"

#include "IronFilterDTGeneratorAction.hh"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "G4RunManager.hh"
//#include "G4Navigator.hh"
//#include "G4PhysicalVolumeStore.hh"
//#include "G4VPhysicalVolume.hh"
//#include "G4SolidStore.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ThreeVector.hh"
#include "G4RandomDirection.hh"
//#include "G4Neutron.hh"
//#include "G4TransportationManager.hh"
//#include "G4Navigator.hh"
//include "G4GenericIon.hh"
//#include "G4IonTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterDTGeneratorAction::IronFilterDTGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleSource(0)
{
  fParticleSource = new G4ParticleGun();

  f1 = new TF1("f1","(x/2)*(x/4)*sqrt(2/pi)*exp(-x*x/(2*2*2))",0,11);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterDTGeneratorAction::~IronFilterDTGeneratorAction()
{
  delete fParticleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterDTGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //G4int eventID = anEvent->GetEventID();
  //cout<<eventID<<endl;

  G4double Energy,X,Y,Z,Px,Py,Pz,angle,r;
  G4ThreeVector neutronDirection;


  //Energy= 0.024*MeV;
  //angle=G4UniformRand()*360.0*deg;
  //r=G4UniformRand()*10*mm;
  //X=r*cos(angle);
  //Y=r*sin(angle);
  //Z = -213.0*mm;

  //Px=0;
  //Py=0;
  //Pz=-1;
  Energy = f1->GetRandom();
  //cout<<Energy<<endl;
  //Energy = H_Eout->GetRandom()/1000*MeV;
  //H_XYout->GetRandom2(X,Y);
  //Z = -230.0*mm;
  //H_PXPYPZout->GetRandom3(Px,Py,Pz);


  //Pz=-(TMath::Sqrt(1-Px*Px-Py*Py));
  G4double randomphi,randomtheta;
  randomtheta = G4UniformRand()*180.0*deg;
  randomphi =360.0*deg*G4UniformRand();
  neutronDirection.setRThetaPhi(1.0, randomtheta, randomphi);



// set particle parameters
fParticleSource->SetParticleMomentumDirection(neutronDirection);
fParticleSource->SetParticleEnergy(Energy);
 G4ParticleDefinition* particleDefinition
   = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
 fParticleSource->SetParticleDefinition(particleDefinition);

// Set source position
 fParticleSource->SetParticlePosition(G4ThreeVector(0., 0., 32.84*cm));
 fParticleSource->GeneratePrimaryVertex(anEvent);

}
