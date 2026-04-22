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
// $Id: IronFilterSteppingAction.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file IronFilterSteppingAction.cc
/// \brief Implementation of the IronFilterSteppingAction class

#include "IronFilterSteppingAction.hh"
#include "IronFilterEventAction.hh"
#include "IronFilterDetectorConstruction.hh"
#include "G4AnalysisManager.hh"
#include "IronFilterAnalysis.hh"
#include "G4Neutron.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4Ions.hh"
#include "G4SystemOfUnits.hh"
using namespace std;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterSteppingAction::IronFilterSteppingAction(
                      const IronFilterDetectorConstruction* detectorConstruction,
                      IronFilterEventAction* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterSteppingAction::~IronFilterSteppingAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterSteppingAction::UserSteppingAction(const G4Step* step)
{
// Collect energy and number of scatters step by step

  G4StepPoint* preStep = step->GetPreStepPoint();
  G4StepPoint* postStep = step->GetPostStepPoint();

  G4Track* track = step->GetTrack();

  // get volume of the current step
  const G4VPhysicalVolume* volume = postStep->GetTouchableHandle()->GetVolume();
  //const G4ParticleDefinition* particle = track->GetDefinition();
  const G4String processName = postStep->GetProcessDefinedStep()->GetProcessName();
  G4int test_volumeID;
  G4int flag=1;

        if(volume == fDetConstruction->GetSteelCasePV()){ //steelcase
          test_volumeID = 1;
        }
        else if(volume == fDetConstruction->GetinnershieldPV()){ //test plane
         test_volumeID = 0;
        }

        else if(volume == fDetConstruction->GetshieldingleadPV()){ //Polyethylene
          test_volumeID = 6;
        }

        else if(volume == fDetConstruction->GetfilteraluminumPV()){ //EJ 426
          test_volumeID = 2;
        }

        else if(volume == fDetConstruction->GetDTsolidPV()){ //Acrylic Light Guide
          test_volumeID = 3;
        }

        else if(volume == fDetConstruction->GetshieldcapironPV()){ //EJ 426
         test_volumeID = 4;
        }

        else if(volume == fDetConstruction->GetIronsolidPV()){ //back Polyethylene
          test_volumeID = 5;
        }

        else if(volume == fDetConstruction->GetmoderatorironPV()){ //Paraffin
         test_volumeID = 12;
        }
        else if(volume == fDetConstruction->GetroomsolidPV()){//Gr crystal
          test_volumeID = -1;
        }

        else {
          test_volumeID =11;
        }
        // energy deposit
        G4double energy = preStep->GetKineticEnergy();
        //G4double energy = postStep->GetKineticEnergy();
        G4double edep = step->GetTotalEnergyDeposit();
        //if(energy*1000 < 1 ){
        //  track->SetTrackStatus(fStopAndKill);
        //  flag = 0;
        //  cout<<"Track is killed as the energy of the particle is than 1 KeV"<<endl;
        //}

        // get analysis manager
        if(flag){
              G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
              G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
              G4int trackID = track->GetTrackID();
              G4int stepID = track->GetCurrentStepNumber();
              //cout<<"Track ID  "<<trackID<<endl;
              // TODO: turn this into a tree that gets filled
              //cout<<eventID<<"   "<<test_volumeID <<"   "<<particle_name<<"  "<<processName<<endl;
              const G4ParticleDefinition* pd = track->GetParticleDefinition();

              G4String particle_name = pd->GetParticleName();
              G4int particle_ID = pd->GetPDGEncoding();


              if(  (particle_name.find("117") != std::string::npos) && (test_volumeID == -1) && (particle_ID == 1000501171) ){
                       cout<<eventID<<"  "<<trackID<<"   "<<stepID <<"   "<<particle_name<<"  "<<processName<<"    "<<particle_ID<<"   "<<track->GetGlobalTime()<<endl;
                       analysisManager->FillNtupleIColumn(0, eventID);
                       analysisManager->FillNtupleIColumn(1, trackID);
                       analysisManager->FillNtupleIColumn(2, stepID);
                       analysisManager->FillNtupleIColumn(3, particle_ID);
                       analysisManager->FillNtupleIColumn(4, test_volumeID);

                       analysisManager->FillNtupleDColumn(5, edep*1000);
                       analysisManager->FillNtupleDColumn(6, track->GetPosition().x());
                       analysisManager->FillNtupleDColumn(7, track->GetPosition().y());
                       analysisManager->FillNtupleDColumn(8, abs(track->GetPosition().z()));
                       analysisManager->FillNtupleDColumn(9, track->GetGlobalTime());
                       analysisManager->FillNtupleDColumn(10, track->GetMomentumDirection().x());
                       analysisManager->FillNtupleDColumn(11, track->GetMomentumDirection().y());
                       analysisManager->FillNtupleDColumn(12, track->GetMomentumDirection().z());
                       //analysisManager->FillNtupleDColumn(12, step->GetTotalEnergyDeposit());
                       analysisManager->AddNtupleRow();
              }

        }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
