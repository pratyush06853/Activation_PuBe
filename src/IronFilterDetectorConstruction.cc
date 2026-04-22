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
// $Id: IronFilterDetectorConstruction.cc $
//
/// \file IronFilterDetectorConstruction.cc
/// \brief Implementation of the IronFilterDetectorConstruction class

#include "IronFilterDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4NeutronHPThermalScatteringNames.hh"
#include "G4UnitsTable.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Polycone.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterDetectorConstruction::IronFilterDetectorConstruction()
 : G4VUserDetectorConstruction(),
   ////airlayer_solid_PV(0),
   room_solid_PV(0),
   shielding_lead_PV(0),
   filter_aluminum_PV(0),
   moderator_iron_PV(0),
   shield_cap_iron_PV(0),
   inner_shield_PV(0),
   DT_solid_PV(0),
   Iron_solid_PV(0),
   LabFloorExtended_solid_PV(0),
   LabFloor_solid_PV(0),
   //LabFloorExtended_solid_PV(0),
   //LabFloor_solid_PV(0),
   //2nd detector
   //shielding_lead_PV_1(0),
   //filter_aluminum_PV_1(0),
   //moderator_iron_PV_1(0),
   //shield_cap_iron_PV_1(0),
   /////inner_shield_PV(0),
   //DT_solid_PV_1(0),
   //Iron_solid_PV_1(0),
   //neutron Source
   //Paraffincylinder_PV(0),
   SteelCase_PV(0),
   fCheckOverlaps(true)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterDetectorConstruction::~IronFilterDetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* IronFilterDetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterDetectorConstruction::DefineMaterials()
{
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;
  G4double density, fractionMass;
  G4String symbol, name;
  G4int nComponents, nAtoms;
  G4double temp;

  G4Element* elH  = new G4Element(name = "Hydrogen", symbol = "H", z = 1.0, a = 1.008*g/mole);
  G4Element* elC  = new G4Element(name = "Carbon", symbol = "C", z = 6.0, a = 12.011*g/mole);
  G4Element* elB  = new G4Element(name = "Boron", symbol = "B", z = 5.0, a = 10.811*g/mole);
  //G4Element* elBe = new G4Element(name = "Beryllium", symbol = "Be", z = 4.0, a = 9.012*g/mole);
  //G4Element* elLi  = new G4Element(name = "Lithium", symbol = "Li", z = 3.0, a = 6.015*g/mole);

  G4Element* elF = new G4Element(name= "Fluorine", symbol = "F", z = 9.0, a= 18.998403*g/mole); //pratyush

  G4Element* elO  = new G4Element(name = "Oxygen", symbol = "O", z = 8.0, a = 15.999*g/mole);


  G4Element* elCr  = new G4Element(name = "Chromium", symbol = "Cr", z = 24.0, a = 51.996*g/mole);
  G4Element* elFe  = new G4Element(name = "Iron", symbol = "Fe", z = 26.0, a = 55.845*g/mole);
  G4Element* elNi  = new G4Element(name = "Nickel", symbol = "Ni", z = 28.0, a = 58.693*g/mole);
  G4Element* elMn  = new G4Element(name = "Maganese", symbol = "Mn", z = 25.0, a = 54.938*g/mole);
  G4Element* elSi  = new G4Element(name = "Silicon", symbol = "Si", z = 14.0, a = 28.085*g/mole);

  //G4Element* elMo  = new G4Element(name = "Molybdenum", symbol = "Mo", z = 42.0, a = 95.94*g/mole);
  G4Element* elAl  = new G4Element(name = "Aluminum", symbol = "Al", z = 13.0, a = 26.982*g/mole);
  //G4Element* elI  = new G4Element(name = "Iodine", symbol = "I", z = 53.0, a = 127*g/mole);
  G4Element* elI  = new G4Element(name = "Iodine", symbol = "I", z = 53.0, a = 126.904473*g/mole);
  G4Element* elLi6 = new G4Element(name = "Lithium6", symbol = "Li", z = 3.0, a = 6.015122*g/mole);
  G4Element* elLi7 = new G4Element(name = "Lithium6", symbol = "Li", z = 3.0, a = 7.016003*g/mole);
  G4Element* elB10 = new G4Element(name = "Boron10", symbol = "B", z = 5.0, a = 10.00*g/mole);
  G4Element* elB11 = new G4Element(name = "Boron11", symbol = "B", z = 5.0, a = 11.00*g/mole);
  G4Element* elZn  = new G4Element(name = "zinc", symbol = "Ti", z = 30.0, a = 65.38*g/mole);
  G4Element* elS  = new G4Element(name = "sulphur", symbol = "S", z = 16.0, a = 32.065*g/mole);

  G4Element* elK = new G4Element("Potassium",symbol ="K",z = 19.,a= 39.098*g/mole);

  G4Element* elCa = new G4Element("Calcium",symbol ="Ca",z = 20.,a= 40.08*g/mole);

  G4Element* elNa = new G4Element("Sodium",symbol ="Na",z = 11.,a= 22.99*g/mole);

  G4Element* elMg = new G4Element("Magnesium",symbol ="Mg",z = 12.,a= 24.305*g/mole);



/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
  G4Element* elH  = new G4Element(name = "Hydrogen", symbol = "H", z = 1.0, a = 1.008*g/mole);
  G4Element* elC  = new G4Element(name = "Carbon", symbol = "C", z = 6.0, a = 12.011*g/mole);
  G4Element* elNa  = new G4Element(name = "Sodium", symbol = "Na", z = 11.0, a = 22.990*g/mole);
  G4Element* elSi  = new G4Element(name = "Silicon", symbol = "Si", z = 14.0, a = 28.085*g/mole);
  G4Element* elP  = new G4Element(name = "Phosphorus", symbol = "P", z = 15.0, a = 30.974*g/mole);
  G4Element* elK  = new G4Element(name = "Potassium", symbol = "K", z = 19.0, a = 39.098*g/mole);
  G4Element* elCa  = new G4Element(name = "Calcium", symbol = "Ca", z = 20.0, a = 40.078*g/mole);
  G4Element* elMn  = new G4Element(name = "Maganese", symbol = "Mn", z = 25.0, a = 54.938*g/mole);
  G4Element* elTi  = new G4Element(name = "Titanium", symbol = "Ti", z = 22.0, a = 47.867*g/mole);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
  //Vacuum
  new G4Material("galactic", z = 1.0, a = 1.01*g/mole, density = universe_mean_density, kStateGas, 2.73*kelvin, 3.e-18*pascal);


  //Aluminum
  new G4Material("NatAluminum", z = 13.0, a = 26.9815384*g/mole, density = 2.70*g/cm3, kStateSolid, 296*kelvin);

  new G4Material("NatLead", 82.0, 207.19*g/mole,  11.36*g/cm3, kStateSolid, 296*kelvin);

  // Silicon
  G4Isotope* Si28 = new G4Isotope("Si28", 14, 28, 27.9769265350*g/mole);
  G4Isotope* Si29 = new G4Isotope("Si29", 14, 29, 28.9764946653*g/mole);
  G4Isotope* Si30 = new G4Isotope("Si30", 14, 30, 29.973770137*g/mole);

  G4Element* NatSi = new G4Element("silicon_natural", "Si",3);
  NatSi->AddIsotope(Si28,92.2*perCent);
  NatSi->AddIsotope(Si29,4.7*perCent);
  NatSi->AddIsotope(Si30,3.1*perCent);

  G4Material* silicon = new G4Material("silicon", 2.3290*g/cm3,1, kStateSolid, 296*kelvin);
  silicon->AddElement(NatSi, 1);

  //LiI
  G4Isotope* Li6 = new G4Isotope("Li6", 3, 6, 6.01*g/mole);
  G4Isotope* Li7 = new G4Isotope("Li7", 3, 7, 7.01*g/mole);

  G4Element* Li6enriched = new G4Element("silicon_enchried", "Li",2);
  Li6enriched->AddIsotope(Li6,97.0*perCent);
  Li6enriched->AddIsotope(Li7,3.0*perCent);

  G4Material* Li6I = new G4Material("Li6I", density= 4.1 * g / cm3,nComponents= 2, kStateSolid, 296*kelvin);
  Li6I->AddElement(Li6enriched, 4.46*perCent);
  //Li6I->AddElement(elI,1);96.0*perCent
  Li6I->AddElement(elI,95.54*perCent);

  G4Material* Li6F = new G4Material("Li6F", density= 2.64 * g / cm3,nComponents= 2, kStateSolid, 296*kelvin);
  Li6F->AddElement(Li6enriched, 1);
  //Li6I->AddElement(elI,1);96.0*perCent
  Li6F->AddElement(elF,1);

  G4Material* ZnS = new G4Material("ZnS", density= 4.09 * g / cm3,nComponents= 2, kStateSolid, 296*kelvin);
  ZnS->AddElement(elZn, 1);
  //Li6I->AddElement(elI,1);96.0*perCent
  ZnS->AddElement(elS,1);


  // Titanium

  G4Isotope* Ti46 = new G4Isotope("Ti46", 22, 46, 45.9526316*g/mole);
  G4Isotope* Ti47 = new G4Isotope("Ti47", 22, 47, 46.9517631*g/mole);
  G4Isotope* Ti48 = new G4Isotope("Ti48", 22, 48, 47.9479463*g/mole);
  G4Isotope* Ti49 = new G4Isotope("Ti49", 22, 49, 48.9478700*g/mole);
  G4Isotope* Ti50 = new G4Isotope("Ti50", 22, 50, 49.9447912*g/mole);

  G4Element* NatTi = new G4Element("titanium_natural", "Ti",5);
  NatTi->AddIsotope(Ti46,8.25*perCent);
  NatTi->AddIsotope(Ti47,7.44*perCent);
  NatTi->AddIsotope(Ti48,73.72*perCent);
  NatTi->AddIsotope(Ti49,5.41*perCent);
  NatTi->AddIsotope(Ti50,5.18*perCent);

  G4Material* titanium = new G4Material("titanium", 4.507*g/cm3,1, kStateSolid, 296*kelvin);
  titanium->AddElement(NatTi, 1);


  // Boron  -------------------------------------------------------------
  G4Isotope* B10 = new G4Isotope("B10", 5, 10, 10.0129*g/mole);
  G4Isotope* B11 = new G4Isotope("B11", 5, 11, 11.00930*g/mole);

  G4Element* NatB = new G4Element("Boron_natural", "B",2);
  NatB->AddIsotope(B10,20*perCent);
  NatB->AddIsotope(B11,80*perCent);

  // Carbon  -------------------------------------------------------------
  G4Isotope* C12 = new G4Isotope("C12", 6, 12, 12.011*g/mole);
  G4Isotope* C13 = new G4Isotope("C13", 6, 13, 13.003355*g/mole);

  G4Element* NatC = new G4Element("Carbon_natural", "C",2);
  NatC->AddIsotope(C12,98.9*perCent);
  NatC->AddIsotope(C13,1.1*perCent);

  // Hydrogen -------------------------------------------------------------
  G4Element *NatH = new G4Element("TS_H_of_Polyethylene", "H", 1, 1.007*g/mole);
  G4Element *NatH_Water = new G4Element("TS_H_of_Water", "H", 1, 1.007*g/mole);
  //G4Isotope* H1 = new G4Isotope("H1", 1, 1, 1.007*g/mole);
  //G4Isotope* H2 = new G4Isotope("H2", 1, 2, 	2.01*g/mole);

  //G4Element* NatH = new G4Element("Hydrogen_natural", "H",2);
  //NatH->AddIsotope(H1,99.98*perCent);
  //NatH->AddIsotope(H2,0.02*perCent);

  //BoratedLiquid Scintillator one percent
  G4Material* ej_254_5pc = new G4Material( "ej_254_5pc", density=1.026*g/cm3, nComponents=3, kStateSolid, 296*kelvin);
  //ej_254_5pc->AddElement( elB10, 0.96*perCent );
  //ej_254_5pc->AddElement( elB11, 4.73*perCent ); //0.915*g/cm3
  //ej_254_5pc->AddElement( NatC, 62.25*perCent );
  //ej_254_5pc->AddElement( NatH, 9.01*perCent );
  //ej_254_5pc->AddElement( elO, 23.05*perCent );

  ej_254_5pc->AddElement( NatB, 5.46*perCent );
  ej_254_5pc->AddElement( NatC, 86.11*perCent );   //1.026*g/cm3
  ej_254_5pc->AddElement( NatH, 8.43*perCent );

  G4Material* ej_230 = new G4Material( "ej_230", density=1.023*g/cm3, nComponents=2, kStateSolid, 296*kelvin);
  ej_230->AddElement( NatC, 91.6*perCent );   //1.026*g/cm3
  ej_230->AddElement( NatH, 8.4*perCent );

  //Remeber HD has 1:2 LiF to ZnS concentration
  G4Material* ej_426_HD= new G4Material( "ej_426_HD", density=3.60*g/cm3, nComponents=2, kStateSolid, 296*kelvin);
  ej_426_HD->AddMaterial( Li6F, 33.3*perCent );   //1.026*g/cm3
  ej_426_HD->AddMaterial( ZnS, 66.7*perCent );


  // Polyethylene with boron at 10% - Has borated polyethylene any oxygen elements? FIXME
  G4Material* pol_bor_10pc = new G4Material("pol_bor_10pc", density=0.96*g/cm3, nComponents=3, kStateSolid, 296*kelvin);
  pol_bor_10pc->AddElement(elH,  13.374*perCent);
  pol_bor_10pc->AddElement(elC,  76.626*perCent);
  pol_bor_10pc->AddElement(elB,  10.00*perCent);


  //Polyethylene moderator
  G4Material*  polyethylene = new G4Material("polyethylene", density=0.94*g/cm3, nComponents=2,kStateSolid, 296*kelvin);
  polyethylene->AddElement(NatC, 1);
  polyethylene->AddElement(NatH, 2);

  //paraffin moderator
  G4Material* paraffin = new G4Material("paraffin", density=0.9*g/cm3, nComponents=2,kStateSolid, 296*kelvin);
  paraffin->AddElement(elH, 52);
  paraffin->AddElement(elC, 25);


  //Phenol-formaldehyde resin density = 1.3*g/cc
  //from https://www.sciencedirect.com/topics/chemical-engineering/phenolic-resins
  G4Material*  phenol_formaldehyde = new G4Material("phenol_formaldehyde", density=1.3*g/cm3, nComponents=3,kStateSolid, 296*kelvin);
  phenol_formaldehyde->AddElement(NatC, 8);
  phenol_formaldehyde->AddElement(NatH, 6);
  phenol_formaldehyde->AddElement(elO, 2);


  G4Material*  water = new G4Material("water", density=1*g/cm3, nComponents=2,kStateLiquid, 296*kelvin);
  water->AddElement(elO, 1);
  water->AddElement(NatH_Water, 2);


  // Assuming PMMA -- see
  //	http://en.wikipedia.org/wiki/Poly(methyl_methacrylate)
  G4Material*  acrylic = new G4Material("acrylic", density= 1.17 * g/cm3, nComponents=3 ,kStateSolid, 296*kelvin);
  acrylic->AddElement(NatC, 5);
  acrylic->AddElement(elO, 2);
  acrylic->AddElement(NatH, 8);


  // Stainless steel (Medical Physics, Vol 25, No 10, Oct 1998)
  //https://apc.u-paris.fr/~franco/g4doxy4.10/html/class_brachy_material.html
  G4Material* matsteel = new G4Material("matsteel",density=8.02*g/cm3,nComponents=5);
  matsteel->AddElement(elMn, 0.02);
  matsteel->AddElement(elSi, 0.01);
  matsteel->AddElement(elCr, 0.19);
  matsteel->AddElement(elNi, 0.10);
  matsteel->AddElement(elFe, 0.68);


  //concrete
  G4Material* concrete = new G4Material("concrete",density= 2.3*g/cm3,nComponents=10);
  concrete->AddElement(elH,0.01);
  concrete->AddElement(elC,0.001);
  concrete->AddElement(elO,0.529107);
  concrete->AddElement(elNa,0.016);
  concrete->AddElement(elMg,0.002);
  concrete->AddElement(elAl,0.033872);
  concrete->AddElement(elSi,0.337021);
  concrete->AddElement(elK,0.013);
  concrete->AddElement(elCa,0.044);
  concrete->AddElement(elFe,0.014);

  //soil
  G4Material* soil = new G4Material("soil",density= 1.50*g/cm3,nComponents=8);
  soil->AddElement(elH,0.021);
  soil->AddElement(elC,0.016);
  soil->AddElement(elO,0.577);
  soil->AddElement(elAl,0.050);
  soil->AddElement(elSi,0.271);
  soil->AddElement(elK,0.013);
  soil->AddElement(elCa,0.041);
  soil->AddElement(elFe,0.011);



  // Germanium  -------------------------------------------------------------
  G4Isotope* Ge70 = new G4Isotope("Ge70", 32, 70, 69.9240*g/mole);
  G4Isotope* Ge72 = new G4Isotope("Ge72", 32, 72, 71.9216*g/mole);
  G4Isotope* Ge73 = new G4Isotope("Ge73", 32, 73, 72.9233*g/mole);
  G4Isotope* Ge74 = new G4Isotope("Ge74", 32, 74, 73.9210*g/mole);
  G4Isotope* Ge76 = new G4Isotope("Ge76", 32, 76, 75.9213*g/mole);

  G4Element* GeNat = new G4Element("Germanium naturel", "Ge",nComponents=5);
  GeNat->AddIsotope(Ge70,20.52*perCent);
  GeNat->AddIsotope(Ge72,27.43*perCent);
  GeNat->AddIsotope(Ge73,7.76*perCent);
  GeNat->AddIsotope(Ge74,36.54*perCent);
  GeNat->AddIsotope(Ge76,7.76*perCent);

  G4Material* germanium = new G4Material("germanium", density= 5.310*g/cm3,nComponents=1);
  germanium->AddElement(GeNat, 1);

  // Tin (natural) -------------------------------------------------------------

  G4Isotope* Sn112 = new G4Isotope("Sn112", 50, 112, 111.9048*g/mole);
  G4Isotope* Sn114 = new G4Isotope("Sn114", 50, 114, 113.9028*g/mole);
  G4Isotope* Sn115 = new G4Isotope("Sn115", 50, 115, 114.9033*g/mole);
  G4Isotope* Sn116 = new G4Isotope("Sn116", 50, 116, 115.9017*g/mole);
  G4Isotope* Sn117 = new G4Isotope("Sn117", 50, 117, 116.9029*g/mole);
  G4Isotope* Sn118 = new G4Isotope("Sn118", 50, 118, 117.9016*g/mole);
  G4Isotope* Sn119 = new G4Isotope("Sn119", 50, 119, 118.9033*g/mole);
  G4Isotope* Sn120 = new G4Isotope("Sn120", 50, 120, 119.9022*g/mole);
  G4Isotope* Sn122 = new G4Isotope("Sn122", 50, 122, 121.9034*g/mole);
  G4Isotope* Sn124 = new G4Isotope("Sn124", 50, 124, 123.9053*g/mole);

  // Natural tin element
  G4Element* SnNat = new G4Element("Tin naturel", "Sn", nComponents=10);

  SnNat->AddIsotope(Sn112, 0.97*perCent);
  SnNat->AddIsotope(Sn114, 0.66*perCent);
  SnNat->AddIsotope(Sn115, 0.34*perCent);
  SnNat->AddIsotope(Sn116, 14.54*perCent);
  SnNat->AddIsotope(Sn117, 7.68*perCent);
  SnNat->AddIsotope(Sn118, 24.22*perCent);
  SnNat->AddIsotope(Sn119, 8.59*perCent);
  SnNat->AddIsotope(Sn120, 32.58*perCent);
  SnNat->AddIsotope(Sn122, 4.63*perCent);
  SnNat->AddIsotope(Sn124, 5.79*perCent);

  // Material
  G4Material* tin = new G4Material("tin", density = 7.31*g/cm3, nComponents=1);
  tin->AddElement(SnNat, 1);


  // Zinc  -------------------------------------------------------------
  G4Isotope* Zn64 = new G4Isotope("Zn64", 30, 64, 63.929*g/mole);
  G4Isotope* Zn66 = new G4Isotope("Zn66", 30, 66, 65.926*g/mole);
  G4Isotope* Zn67 = new G4Isotope("Zn67", 30, 67, 66.927*g/mole);
  G4Isotope* Zn68 = new G4Isotope("Zn68", 30, 68, 67.924*g/mole);
  G4Isotope* Zn70 = new G4Isotope("Zn70", 30, 70, 69.925*g/mole);

  G4Element* ZnNat = new G4Element("Zinc naturel", "Zn",nComponents=5);
  ZnNat->AddIsotope(Zn64,49.2*perCent);
  ZnNat->AddIsotope(Zn66,27.7*perCent);
  ZnNat->AddIsotope(Zn67,4.0*perCent);
  ZnNat->AddIsotope(Zn68,18.5*perCent);
  ZnNat->AddIsotope(Zn70,0.6*perCent);

  G4Material* zinc = new G4Material("zinc", density= 7.13*g/cm3,nComponents=1);
  zinc->AddElement(ZnNat, 1);


  // Print materials
  //G4cout <<"Is hydrogen declared in the scintillator a Thermal Hydrogen"  <<G4NeutronHPThermalScatteringNames::IsThisThermalElement(TS_H_of_Polyethylene)<< G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* IronFilterDetectorConstruction::DefineVolumes()
{

  // Get materials
  G4Material* Vacuum = G4Material::GetMaterial("galactic");
  G4Material* Titanium = G4Material::GetMaterial("titanium");
  G4Material* Aluminum = G4Material::GetMaterial("NatAluminum");
  G4Material* Lead = G4Material::GetMaterial("NatLead");
  G4Material* Silicon = G4Material::GetMaterial("silicon");
  G4Material* EJ2545pc = G4Material::GetMaterial("ej_254_5pc");
  G4Material* PolBor10pc = G4Material::GetMaterial("pol_bor_10pc");
  G4Material* EJ230 = G4Material::GetMaterial("ej_230");
  G4Material* EJ4265HD = G4Material::GetMaterial("ej_426_HD");
  G4Material* LithiumIodide = G4Material::GetMaterial("Li6I");
  G4Material* Polyethylene = G4Material::GetMaterial("polyethylene");
  G4Material* Water = G4Material::GetMaterial("water");
  G4Material* Acrylic = G4Material::GetMaterial("acrylic");
  G4Material* Phenol_formaldehyde= G4Material::GetMaterial("phenol_formaldehyde");
  G4Material* Concrete = G4Material::GetMaterial("concrete");
  G4Material* Soil = G4Material::GetMaterial("soil");
  G4Material* Paraffin = G4Material::GetMaterial("paraffin");
  G4Material* StainlessSteel = G4Material::GetMaterial("matsteel");
  G4Material* Germanium = G4Material::GetMaterial("germanium");
  G4Material* Tin = G4Material::GetMaterial("tin");
  G4Material* Zinc = G4Material::GetMaterial("zinc");


  if ( ! Vacuum ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("IronFilterDetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }



//
//  Filter Sizes
//
 //Useful for Scintillator Studies
 //G4double TitaniumThickness = 3.0*cm;//3.0*cm
 //G4double AluminumThickness = 3*mm; //3*mm;lets assume this as new EJ426 layer
 //G4double ScintillatorHeight = 4.0*cm;//7.5*cm//4.0*cm;
 //G4double ScintillatorRadius = 2.5*cm;//2.5*cm; 6*cm;
 //G4double moderatorRadius = ScintillatorRadius+AluminumThickness+TitaniumThickness; //15
 //G4double SiPMSide = 1.5*cm;
 //G4double SiPMthickness = 2.5*mm;



  //G4double Fe_Height= (20.0)*cm; //20
  //G4double FeRadius= (5.0)*cm; //20
  //G4double Al_Height = 27.0*cm;//20
  //G4double AlRadius = 20.0*cm;//20
  //G4double Fe_Height_2 =  30.0*cm;//15



  G4double DD_Height = 20.0*cm;
  G4double DD_Extra_Height= 60.0*cm;
  G4double shieldthickness = 40.0*cm; //20.0*cm; //20
  G4double leadshieldthickness = 20.0*cm;
  G4double Polyshieldthickness = 40.0*cm;
  G4double SourceRadius = 1.7*cm;
  G4double delta= 1.0*cm;// 1.0cm parameter of catchment area




  G4double zeroRadius = 0.*cm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;
  //G4double shieldHeight = 400.*cm;

  //G4double moderatorRadius = 15.0*cm; //15
  G4double Front_Moderator_Thickness=1.5*cm;//(5.0/4.0)*2.54*cm; //changes this
  G4double Back_Moderator_Thickness=1.5*cm;//(5.0/4.0)*2.54*cm;
  //G4double Inner_Radius =30.0*cm;
  G4double Inner_Radius =20.0*cm;//30.0*cm;
  G4double Radial_thickness=10.0*cm;//10.0*cm;
  G4double Mid_Acrylic_thickness=2.5*cm;//(3.0/2.0)*2.54*cm;
  G4double EJ426_thickness=0.25*2*mm;
  G4double BoratedPoly_thickness = 5.0*cm; //15

  G4double Water_tank_Diameter = 11.5*2.54*cm; //15
  G4double Water_tank_Height = 9*2.54*cm; //I had 10 inch of water intially but than we drained an inch
  G4double Support_ring_Height = 1.5*2.54*cm;
  //G4double shieldCapHeight= 15.0*cm;//5

  G4double Table_X_dimension = 381*cm; //15
  G4double Table_Y_dimension = 152.4*cm; //I had 10 inch of water intially but than we drained an inch
  G4double Table_Z_dimension = 1*2.54*cm;


  //coordinates if the center of the water tank with respect to the door entrance corner
  G4double WaterTank_COM_X=81*2.54*cm;
  G4double WaterTank_COM_Y=17.5*2.54*cm;

  //coordinates if the center of the table with respect to the center of the water tank
  G4double Center_Table_X=Table_X_dimension/2.0-WaterTank_COM_X;
  G4double Center_Table_Y=Table_Y_dimension/2.0-WaterTank_COM_Y;




  //G4double FeCapHeight= 20.0*cm;//20
  //G4double Source_radius = (3.4/2)*cm;
  //G4double Pb_radius = Source_radius + 5.0*cm ;
  //G4double Fe2_Height = shieldCapHeight + FeCapHeight;
  ///G4double shieldHeight = Fe_Height+Fe2_Height+Fe_Height_2+Al_Height+delta;
  //G4double shieldHeight = Fe_Height+shieldCapHeight+DD_Height+Al_Height;
  G4double shieldHeight =  Front_Moderator_Thickness+Mid_Acrylic_thickness+Back_Moderator_Thickness;
  //G4double shieldRadius = UrRadius+PbRadius+AlRadius+FeRadius+delta;

  //G4double Room_Height = 100.0*cm;
  //G4double LiF_Height = 0.25*cm;
  //G4double Cd_Height = 0.25*cm;
  //G4double shieldHeight = Room_Height+LiF_Height+Cd_Height+delta;
  //G4double shieldHeight = Room_Height+delta;


  //for Polycone Photon Relfecting layer made of Aluminum
  //G4int nbEdges = 6;
  //G4double z[6]    = {(ScintillatorHeight+2*AluminumThickness)/2.0, (ScintillatorHeight)/2.0,(ScintillatorHeight)/2.0,
  //                           -(ScintillatorHeight)/2.0,-(ScintillatorHeight)/2.0, -(ScintillatorHeight+2*AluminumThickness)/2.0 };

  //G4double rIn[6]  = { zeroRadius , zeroRadius , ScintillatorRadius,  ScintillatorRadius,  zeroRadius, zeroRadius};
  //G4double rOut[6] = { ScintillatorRadius+AluminumThickness,  ScintillatorRadius+AluminumThickness, ScintillatorRadius+AluminumThickness,ScintillatorRadius+AluminumThickness, ScintillatorRadius+AluminumThickness, ScintillatorRadius+AluminumThickness};

  //for Polycone Neutron Relfecting layer made of Titanium or lead
  //G4int nbEdges1 = 4;
  //G4double z1[4]    = {-(ScintillatorHeight+2*AluminumThickness)/2.0-TitaniumThickness, -(ScintillatorHeight+2*AluminumThickness)/2.0 ,-(ScintillatorHeight+2*AluminumThickness)/2.0
  //                          , (ScintillatorHeight+2*AluminumThickness)/2.0 };
  //G4double rIn1[4]  = { zeroRadius ,zeroRadius ,ScintillatorRadius+AluminumThickness,  ScintillatorRadius+AluminumThickness};
  //G4double rOut1[4] = { ScintillatorRadius+AluminumThickness+TitaniumThickness,  ScintillatorRadius+AluminumThickness+TitaniumThickness,
  //                       ScintillatorRadius+AluminumThickness+TitaniumThickness,ScintillatorRadius+AluminumThickness+TitaniumThickness};


  //for Polycone surounding the DT made up of Poly
  //G4int nbEdges = 6;
  //G4double z[6]    = {-Polyshieldthickness-DD_Extra_Height, -DD_Extra_Height,-DD_Extra_Height,
                            // DD_Height,DD_Height, DD_Height+Polyshieldthickness };

  //G4double rIn[6]  = { zeroRadius , zeroRadius , SourceRadius,  SourceRadius,  zeroRadius, zeroRadius};
  //G4double rOut[6] = { Polyshieldthickness,  Polyshieldthickness, Polyshieldthickness,Polyshieldthickness, Polyshieldthickness, Polyshieldthickness};

  //for Polycone surounding the DT made up of Lead
  G4int nbEdges2 = 6;
  G4double z2[6]    = {-Polyshieldthickness-leadshieldthickness-DD_Extra_Height, -DD_Extra_Height-Polyshieldthickness,-DD_Extra_Height-Polyshieldthickness,
                             DD_Height+Polyshieldthickness,DD_Height+Polyshieldthickness, DD_Height+Polyshieldthickness+leadshieldthickness };

  G4double rIn2[6]  = { zeroRadius , zeroRadius , Polyshieldthickness, Polyshieldthickness,  zeroRadius, zeroRadius};
  G4double rOut2[6] = { leadshieldthickness+Polyshieldthickness,  leadshieldthickness+Polyshieldthickness, leadshieldthickness+Polyshieldthickness,
                        leadshieldthickness+Polyshieldthickness, leadshieldthickness+Polyshieldthickness, leadshieldthickness+Polyshieldthickness};


  //for Polycone suurounding the poly to see the number of particles leaving the shielding
  G4int nbEdges1 = 4;
  G4double z1[4]    = {-Polyshieldthickness-leadshieldthickness-DD_Extra_Height-delta, -Polyshieldthickness-leadshieldthickness-DD_Extra_Height,
                          -Polyshieldthickness-leadshieldthickness-DD_Extra_Height  , DD_Height+leadshieldthickness+Polyshieldthickness };
  G4double rIn1[4]  = { zeroRadius ,zeroRadius ,Polyshieldthickness+leadshieldthickness,  Polyshieldthickness+leadshieldthickness};
  G4double rOut1[4] = { Polyshieldthickness+leadshieldthickness+delta,  Polyshieldthickness+leadshieldthickness+delta,
                         Polyshieldthickness+leadshieldthickness+delta,Polyshieldthickness+leadshieldthickness+delta};


//
// Rotations
//

  G4RotationMatrix* NO_ROT = new G4RotationMatrix;
  G4RotationMatrix* xRot7 = new G4RotationMatrix;
  G4RotationMatrix* xRot8 = new G4RotationMatrix;
  xRot7 -> rotateX(-pi/2.*rad);
  xRot8 -> rotateX(pi/2.*rad);
//
// GEOMETRY
//


  //G4VSolid* vacuum_solid = new G4Tubs("vacuum_solid", zeroRadius,Inner_Radius+ Radial_thickness+Table_X_dimension, Table_X_dimension, startAngle, spanningAngle);
  G4VSolid* vacuum_solid = new G4Tubs("vacuum_solid",zeroRadius,Inner_Radius+Radial_thickness+(20*9*2.54)*cm, Table_X_dimension, startAngle, spanningAngle);
  //G4VSolid* vacuum_solid = new G4Sphere("vacuum_solid", zeroRadius, 50*cm, startAngle, spanningAngle, startAngle, spanningAngle);
  //G4VSolid* vacuum_solid = new G4Box("vacuum_solid", CapturerLength/2.0, CapturerLength/2.0, (shieldHeight)/2.0);
  G4LogicalVolume* vacuum_solid_LV = new G4LogicalVolume(vacuum_solid, Vacuum, "vacuum_solid");
  G4VPhysicalVolume* vacuum_solid_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(), vacuum_solid_LV, "Vacuum_solid", 0, false, 0, fCheckOverlaps);




G4double Steel_Thickness= (0.1)*2.54*cm;
G4double Box_Diameter = 24*2.54*cm;
G4double Box_Height= 24*2.54*cm;
G4double Port_Diameter = 1.5*2.54*cm;
G4double Port_Height= 12.1*2.54*cm;
G4double zasymetry_parafffin= 0*2.54*cm;
G4double Paraffin_Height= Box_Height- 2*Steel_Thickness - zasymetry_parafffin;
G4double Paraffin_Thickness= Box_Diameter- 2*Steel_Thickness;
//G4double distance_detector_box = 53*2.54*cm;
G4double distance_detector_box = 12*9*2.54*cm;
G4double Source_stand_height = 4.2*2.54*cm;
G4double Ge_crystal_x = 25.44*mm;
G4double Ge_crystal_y = 25.44*mm;
G4double Ge_crystal_z = 10.44*mm;





G4int nbEdges = 6;
G4double z[6]    = {-Box_Height/2.0, -Box_Height/2.0 + Steel_Thickness, -Box_Height/2.0 + Steel_Thickness,
                            Box_Height/2.0 - Steel_Thickness,   Box_Height/2.0 - Steel_Thickness, Box_Height/2.0};
G4double rIn[6]  = { zeroRadius , zeroRadius ,Box_Diameter/2.0-Steel_Thickness,
                    Box_Diameter/2.0-Steel_Thickness,  Box_Diameter/2.0-Steel_Thickness, zeroRadius };
G4double rOut[6] = { Box_Diameter/2.0,Box_Diameter/2.0, Box_Diameter/2.0, Box_Diameter/2.0, Box_Diameter/2.0, Box_Diameter/2.0};





//Front Polyethylene layer, front is in -ve z axis
G4VSolid* shielding_lead_S = new G4Tubs("shielding_lead", Inner_Radius, Inner_Radius+ Radial_thickness,(Front_Moderator_Thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume* shielding_lead_LV = new G4LogicalVolume(shielding_lead_S, Polyethylene, "shielding_lead_solid");
//shielding_lead_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(shieldHeight-Front_Moderator_Thickness+Mid_Acrylic_thickness)/2.0), shielding_lead_LV, "Titanium_Reflector", vacuum_solid_LV, false, 0, fCheckOverlaps);

//shielding_lead_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(shieldHeight-Front_Moderator_Thickness)/2.0), shielding_lead_LV, "Back_Poly", room_solid_LV, false, 0, fCheckOverlaps);


//Back Polyethylene layer, back is in +ve z axis
G4VSolid* Iron_solid_S = new G4Tubs("Iron_solid", Inner_Radius, Inner_Radius+ Radial_thickness,(Back_Moderator_Thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume *Iron_solid_LV = new G4LogicalVolume(Iron_solid_S, Polyethylene,"Iron_solid" );
//Iron_solid_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(shieldHeight-Back_Moderator_Thickness)/2.0), Iron_solid_LV, "Front_Poly",room_solid_LV,false, 0, fCheckOverlaps);


//Acrylic in the middle
G4VSolid* DT_solid_S = new G4Tubs("DT_solid", Inner_Radius, Inner_Radius+ Radial_thickness,(Mid_Acrylic_thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume *DT_solid_LV = new G4LogicalVolume(DT_solid_S, Acrylic,"DT_solid" );
//DT_solid_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0), DT_solid_LV, "Acrylic",  room_solid_LV, false, 0, fCheckOverlaps);

//Front EJ426, placed in Acrylic as its Mother Volume, Front is -ve z axis
G4VSolid* filter_aluminum_S = new G4Tubs("filter_aluminum_solid", Inner_Radius, Inner_Radius+ Radial_thickness-5.0*mm,(EJ426_thickness/2.0), startAngle+12*deg, spanningAngle-12*deg);
G4LogicalVolume* filter_aluminum_LV = new G4LogicalVolume(filter_aluminum_S, EJ4265HD , "filter_aluminum_solid");
//filter_aluminum_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV, "Lead_layer", DT_solid_LV, false, 0, fCheckOverlaps);


//Back EJ426, placed in Acrylic as its Mother Volume, Back is +ve z axis
G4VSolid* shield_cap_iron_S = new G4Tubs("Shield_cap_iron", Inner_Radius, Inner_Radius+ Radial_thickness-5.0*mm,(EJ426_thickness/2.0), startAngle+12*deg, spanningAngle-12*deg);
G4LogicalVolume *shield_cap_iron_LV = new G4LogicalVolume(shield_cap_iron_S, EJ4265HD,"shield_cap" );
//shield_cap_iron_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV, "Fe_Cap", DT_solid_LV, false, 0, fCheckOverlaps );

//Lead inner Shield (Design B)
G4VSolid* inner_shield_S = new G4Box("inner_shield", Box_Diameter/2.0, Box_Diameter/2.0,delta);
G4LogicalVolume *inner_shield_LV = new G4LogicalVolume(inner_shield_S, Vacuum,"Pb_inner_shield" );
//inner_shield_PV = new G4PVPlacement( xRot8, G4ThreeVector(0,(Box_Diameter+delta)/2.0+distance_detector_box/2.0,0), inner_shield_LV, "Pb_inner_shield", vacuum_solid_LV, false, 0, fCheckOverlaps);


//G4Polycone steelcase arounf the neutron box
G4Polycone* SteelCase_S = new G4Polycone("SteelCase", startAngle, spanningAngle, nbEdges, z, rIn, rOut);
G4LogicalVolume* SteelCase_LV = new G4LogicalVolume(SteelCase_S, StainlessSteel, "SteelCase_solid");
//SteelCase_PV = new G4PVPlacement(xRot8, G4ThreeVector(0.,0.,0.), SteelCase_LV, "Stainless_Case", vacuum_solid_LV, false, 0, fCheckOverlaps);
SteelCase_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0.,0.,Source_stand_height), SteelCase_LV, "Stainless_Case", vacuum_solid_LV, false, 0, fCheckOverlaps);


//Paraffin  Iron_solid_S
G4VSolid* first_S = new G4Tubs("first_solid", zeroRadius, Box_Diameter/2.0-Steel_Thickness,(Paraffin_Height/2.0), startAngle, spanningAngle);
G4VSolid* second_S = new G4Tubs("second_solid", zeroRadius, Port_Diameter/2.0,(Port_Height/2.0), startAngle, spanningAngle);
G4SubtractionSolid * moderator_iron_S =  new G4SubtractionSolid ("moderator_iron_solid", first_S, second_S, xRot8, G4ThreeVector(0,Port_Height/2, zasymetry_parafffin));
//G4VSolid* moderator_iron_S= new G4Tubs("moderator_iron_solid", zeroRadius, Box_Diameter/2.0-Steel_Thickness,(Paraffin_Height/2.0), startAngle, spanningAngle);
G4LogicalVolume *moderator_iron_LV = new G4LogicalVolume(moderator_iron_S, Paraffin,"Paraffin_cylinder" );
moderator_iron_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,-zasymetry_parafffin+Source_stand_height),moderator_iron_LV, "Paraffin_cylinder",vacuum_solid_LV,false, 0, fCheckOverlaps);

G4VSolid* room_solid_S = new G4Box("room_solid_iron", Ge_crystal_x/2.0, Ge_crystal_y/2.0, Ge_crystal_z/2.0);
//G4LogicalVolume *room_solid_LV = new G4LogicalVolume(room_solid_S, Germanium,"room_solid" );
G4LogicalVolume *room_solid_LV = new G4LogicalVolume(room_solid_S, Tin,"room_solid" );
room_solid_PV = new G4PVPlacement( xRot8, G4ThreeVector(0,Port_Height/2.0,-zasymetry_parafffin+Source_stand_height), room_solid_LV, "Ge Crystal", vacuum_solid_LV,false, 0, fCheckOverlaps );
//room_solid_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,.0,-zasymetry_parafffin+Source_stand_height+ Paraffin_Height/2.0+Steel_Thickness+Ge_crystal_z/2.0), room_solid_LV, "Ge Crystal", vacuum_solid_LV,false, 0, fCheckOverlaps );
//NO_ROT


//Lab donot include ceiling
G4double soil_width=25*cm;
//G4VSolid* LabFloorExtended_solid_S=  new G4Box("LabFloorExtended_solid", 25.0*m, 25.0*m , 15.0*m);
G4VSolid* LabFloorExtended_solid_S=  new G4Box("LabFloorExtended_solid", 2.0*m, 4.0*m , soil_width/2.0);
//G4SubtractionSolid* Main_2a_S= new G4SubtractionSolid("Main_2a_solid", Main_2_S, hole_2_S, NO_ROT, G4ThreeVector(0.,0., 0.));
G4LogicalVolume* LabFloorExtended_solid_LV = new G4LogicalVolume(LabFloorExtended_solid_S, Soil, "LabFloorExtended_solid");
LabFloorExtended_solid_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0,0, -(Inner_Radius+ Radial_thickness)-soil_width/2.0), LabFloorExtended_solid_LV, "LabFloor_extended", vacuum_solid_LV, false, 0, fCheckOverlaps);
////LabFloorExtended_solid_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(Center_Table_X,Center_Table_Y, -(shieldHeight+Support_ring_Height+ soil_width)/2.0), LabFloorExtended_solid_LV, "LabFloor_extended", vacuum_solid_LV, false, 0, fCheckOverlaps);


//Lab donot include ceiling
G4double concrete_width=25*cm;
//G4VSolid* LabFloorExtended_solid_S=  new G4Box("LabFloorExtended_solid", 25.0*m, 25.0*m , 15.0*m);
G4VSolid* LabFloor_solid_S=  new G4Box("LabFloor_solid", 2.0*m, 2.0*m , concrete_width/2.0);
//G4SubtractionSolid* Main_2a_S= new G4SubtractionSolid("Main_2a_solid", Main_2_S, hole_2_S, NO_ROT, G4ThreeVector(0.,0., 0.));
G4LogicalVolume* LabFloor_solid_LV = new G4LogicalVolume(LabFloor_solid_S, Soil, "LabFloor_solid");
//LabFloor_solid_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., soil_width/2.0-concrete_width/2.0), LabFloor_solid_LV, "LabFloor", LabFloorExtended_solid_LV, false, 0, fCheckOverlaps);




//
// Visualization attributes
//


  vacuum_solid_LV->SetVisAttributes(G4VisAttributes::GetInvisible());
  //vacuum_solid_LV->SetVisAttributes(G4Colour(0.0,1.0,0.0,0.5));
  //inner_shield_LV->SetVisAttributes(G4VisAttributes::Invisible);

  G4VisAttributes* test_vis = new G4VisAttributes(G4Colour(0.0,1.0,0.0,0.5));  //used in verification of the geometry
  //G4VisAttributes* iron_vis = new G4VisAttributes(G4Colour(1.0,0.0,0.0,0.5));
  G4VisAttributes* aluminum_vis = new G4VisAttributes(G4Colour(1.0,0.0,0.0,0.5));


  //G4VisAttributes* lead_vis = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5));
  G4VisAttributes* lead_vis = new G4VisAttributes(G4Colour(1.0,0.0,0.0,0.5));
  G4VisAttributes* silicon_vis = new G4VisAttributes(G4Colour(0.0,1.0,0.0,0.5));
  G4VisAttributes* ej_254_5pc_vis = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5));
  G4VisAttributes* LithiumIodide_vis = new G4VisAttributes(G4Colour(0.6,0.5,1.0,0.5));
  G4VisAttributes* air_vis = new G4VisAttributes(G4Colour(1.0,0.5,0.5,0.5));
  G4VisAttributes* EJ230_vis = new G4VisAttributes(G4Colour(0.0,1.0,1.0,0.5));
  G4VisAttributes* EJ4265HD_vis = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5));


  //airlayer_solid_LV->SetVisAttributes(G4VisAttributes::Invisible);
  //airlayer_solid_LV->SetVisAttributes(aluminum_vis);
  SteelCase_LV->SetVisAttributes(air_vis);
  shielding_lead_LV->SetVisAttributes(lead_vis);
  //shielding_lead_LV->SetVisAttributes(lead_vis);

  //moderator_iron_LV->SetVisAttributes(LithiumIodide_vis);

  Iron_solid_LV->SetVisAttributes(lead_vis);

  DT_solid_LV->SetVisAttributes(silicon_vis);

  //DT_solid_LV_1->SetVisAttributes(silicon_vis);

  filter_aluminum_LV->SetVisAttributes(EJ4265HD_vis);
  shield_cap_iron_LV->SetVisAttributes(EJ4265HD_vis);//Design A
  //LabFloorExtended_solid_LV->SetVisAttributes(lead_vis);
  //LabFloor_solid_LV->SetVisAttributes(silicon_vis);
  //shielding_lead_LV->SetVisAttributes(G4VisAttributes::Invisible);


  /////shielding_lead_LV->SetVisAttributes(lead_vis);//Design D
  ///////shielding_lead_LV->SetVisAttributes(lead_vis);//Design E

  moderator_iron_LV->SetVisAttributes(LithiumIodide_vis);

  //shield_cap_iron_LV->SetVisAttributes(lead_vis); //Design B
  //shield_cap_iron_LV->SetVisAttributes(lif_vis); //Design C
  //shield_cap_iron_LV->SetVisAttributes(cadmium_vis); //Design D
  //inner_shield_LV->SetVisAttributes(lead_vis);// Design A
  inner_shield_LV->SetVisAttributes(G4VisAttributes::GetInvisible());
  room_solid_LV->SetVisAttributes(EJ4265HD_vis);
  LabFloorExtended_solid_LV->SetVisAttributes(lead_vis);
  LabFloor_solid_LV->SetVisAttributes(silicon_vis);

  //Iron_solid_LV->SetVisAttributes(silicon_vis);

  //
  // Always return the physical World
  //
  return vacuum_solid_PV;
}
