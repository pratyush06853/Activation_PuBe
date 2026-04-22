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
// $Id: IronFilterDetectorConstruction.hh $
//
/// \file IronFilterDetectorConstruction.hh
/// \brief Definition of the IronFilterDetectorConstruction class

#ifndef IronFilterDetectorConstruction_h
#define IronFilterDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"

class G4VPhysicalVolume;
class IronFilterDetectorMessenger;//pratyush

class IronFilterDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    IronFilterDetectorConstruction();
    virtual ~IronFilterDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();

    // get methods
    //
    ////const G4VPhysicalVolume* GetairlayersolidPV() const;
    //const G4VPhysicalVolume* GetroomsolidPV() const;
    //const G4VPhysicalVolume* GetshieldingleadPV() const;
    //const G4VPhysicalVolume* GetfilteraluminumPV() const;
    //const G4VPhysicalVolume* GetmoderatorironPV() const;
    //const G4VPhysicalVolume* GetshieldcapironPV() const;
    ///const G4VPhysicalVolume* GetinnershieldPV() const;
    //const G4VPhysicalVolume* GetLabFloorExtendedsolidPV() const;
    //const G4VPhysicalVolume* GetLabFloorsolidPV() const;
    //const G4VPhysicalVolume* GetDTsolidPV() const;
    const G4VPhysicalVolume* GetIronsolidPV() const;
    const G4VPhysicalVolume* GetSteelCasePV() const;
    const G4VPhysicalVolume* GetroomsolidPV() const;
    const G4VPhysicalVolume* GetDTsolidPV() const;
    const G4VPhysicalVolume* GetshieldingleadPV() const;
    const G4VPhysicalVolume* GetmoderatorironPV() const;
    const G4VPhysicalVolume* GetfilteraluminumPV() const;
    const G4VPhysicalVolume* GetLabFloorExtendedsolidPV() const;
    const G4VPhysicalVolume* GetLabFloorsolidPV() const;
    const G4VPhysicalVolume* GetshieldcapironPV() const;
    const G4VPhysicalVolume* GetinnershieldPV() const;

    //const G4VPhysicalVolume* GetshieldingleadPV1() const;
    //const G4VPhysicalVolume* GetfilteraluminumPV1() const;
    //const G4VPhysicalVolume* GetmoderatorironPV1() const;
    //const G4VPhysicalVolume* GetshieldcapironPV1() const;
    //const G4VPhysicalVolume* GetDTsolidPV1() const;
    //const G4VPhysicalVolume* GetIronsolidPV1() const;




  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
    ////G4VPhysicalVolume* airlayer_solid_PV;

    //G4VPhysicalVolume* shielding_lead_PV;
    //G4VPhysicalVolume* filter_aluminum_PV;
    //G4VPhysicalVolume* moderator_iron_PV;
    //G4VPhysicalVolume* shield_cap_iron_PV;
    ////G4VPhysicalVolume* inner_shield_PV;
    //G4VPhysicalVolume* LabFloorExtended_solid_PV;
    //G4VPhysicalVolume* LabFloor_solid_PV;
    //G4VPhysicalVolume* DT_solid_PV;
    G4VPhysicalVolume* Iron_solid_PV;
    G4VPhysicalVolume* SteelCase_PV;
    G4VPhysicalVolume* room_solid_PV;
    G4VPhysicalVolume* DT_solid_PV;
    G4VPhysicalVolume* shielding_lead_PV;
    G4VPhysicalVolume* moderator_iron_PV;
    G4VPhysicalVolume* filter_aluminum_PV;
    G4VPhysicalVolume* shield_cap_iron_PV;
    G4VPhysicalVolume* inner_shield_PV;
    G4VPhysicalVolume* LabFloorExtended_solid_PV;
    G4VPhysicalVolume* LabFloor_solid_PV;

    //G4VPhysicalVolume* shielding_lead_PV_1;
    //G4VPhysicalVolume* filter_aluminum_PV_1;
    //G4VPhysicalVolume* moderator_iron_PV_1;
    //G4VPhysicalVolume* shield_cap_iron_PV_1;
    //G4VPhysicalVolume* DT_solid_PV_1;
    //G4VPhysicalVolume* Iron_solid_PV_1;



    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

//// inline functions

////inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetairlayersolidPV() const {
////  return airlayer_solid_PV;
////}
/*
inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetroomsolidPV() const {
  return room_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV() const {
  return shielding_lead_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV() const {
  return filter_aluminum_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV() const {
return moderator_iron_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV() const {
  return shield_cap_iron_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetLabFloorExtendedsolidPV() const {
  return LabFloorExtended_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetLabFloorsolidPV() const {
  return LabFloor_solid_PV;
}

///inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetinnershieldPV() const {
///  return inner_shield_PV;
///}



inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV() const {
  return DT_solid_PV;
}



*/
inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetSteelCasePV() const {
  return SteelCase_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV() const {
  return Iron_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV() const {
  return shielding_lead_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetroomsolidPV() const {
  return room_solid_PV;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV() const {
  return DT_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV() const {
return moderator_iron_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV() const {
  return filter_aluminum_PV;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV() const {
  return shield_cap_iron_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetinnershieldPV() const {
  return inner_shield_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetLabFloorExtendedsolidPV() const {
  return LabFloorExtended_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetLabFloorsolidPV() const {
  return LabFloor_solid_PV;
}


//2nd Detector
/*
inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV1() const {
  return shielding_lead_PV_1;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV1() const {
 return moderator_iron_PV_1;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV1() const {
  return filter_aluminum_PV_1;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV1() const {
  return shield_cap_iron_PV_1;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV1() const {
  return DT_solid_PV_1;
}



inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV1() const {
  return Iron_solid_PV_1;
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
