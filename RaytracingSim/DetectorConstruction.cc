#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
{}
DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();

	//creating vacum
	G4double A, Z;
    G4double density, massfraction;
    G4int natoms, nel;
    G4Element* elN = new G4Element("Nitrogen","N", Z=7., A= 14.00674*g/mole);
    G4Element* elO = new G4Element("Oxygen", "O", Z=8., A= 15.9994*g/mole);
    density = 1.e-25*g/cm3;
    G4Material* Vacuum = new G4Material("Vacuum", density, nel=2);
    Vacuum-> AddElement(elN, .23);
    Vacuum-> AddElement(elO, .1);

    //vacuum volume
	G4Box *solidWorld = new G4Box("solidWrold", 0.5*m, 0.5*m, 0.5*m);

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, Vacuum, "logicWorld");

	G4VPhysicalVolume *physWorld= new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

	//Adding material properties for vacuum
    G4int numEntries = 2;
    G4double energy[2] =  {1.239841939*eV/0.2, 1.239841939*eV/0.9};
    G4double rIndexVacuum[2]={1.0,1.0};
	G4double absorptionVacuum[2]={200*m, 200*m};
	G4double mieVacuum[2]={500*m,500*m};
	G4double mie_const[3]={0.99,0.2,0.99};

	G4MaterialPropertiesTable *mptVacuum= new G4MaterialPropertiesTable();

	mptVacuum->AddProperty("RINDEX", energy, rIndexVacuum, numEntries);
	mptVacuum->AddProperty("ABSLENGTH", energy, absorptionVacuum, numEntries);
	mptVacuum->AddProperty("MIEHG", energy, mieVacuum, numEntries);
	mptVacuum->AddConstProperty("MIEHG_FORWARD", mie_const[0]);
	mptVacuum->AddConstProperty("MIEHG_BACKWARD", mie_const[1]);
	mptVacuum->AddConstProperty("MIEHG_FORWARD_RATIO", mie_const[2]);

	Vacuum->SetMaterialPropertiesTable(mptVacuum);


	//Glass Slab Construction

	G4Material *glass = nist->FindOrBuildMaterial("G4_GLASS_PLATE");

	G4Box *glassSlab = new G4Box("glassSalb", 0.5*m, 0.5*m, 0.1*m);

	G4LogicalVolume *logicGlass = new G4LogicalVolume(glassSlab, glass, "logicGLass");

	G4VPhysicalVolume *physGlass = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicGlass, "physGlass", logicWorld, false, 0, true);

	//Adding Material Properties for glass

    G4double rIndexGlass[2] = {1.5,1.5};
    G4double absorption[2] =  {.5*m, .5*m}; //value assumed, empirical values yet to be used
    G4double mie_glass[2] = {.05*m, .05*m}; //value assumed, empirical values yet to be used


	G4MaterialPropertiesTable *mptGlass = new G4MaterialPropertiesTable();
  	mptGlass->AddProperty("RINDEX", energy, rIndexGlass, numEntries);

	mptGlass->AddProperty("ABSLENGTH", energy, absorption, numEntries);
	mptGlass->AddProperty("MIEHG", energy, mie_glass, numEntries);
	mptGlass->AddConstProperty("MIEHG_FORWARD", mie_const[0]);
	mptGlass->AddConstProperty("MIEHG_BACKWARD", mie_const[1]);
	mptGlass->AddConstProperty("MIEHG_FORWARD_RATIO", mie_const[2]);


	glass->SetMaterialPropertiesTable(mptGlass);

	//air slab construction
	G4Material *air = nist->FindOrBuildMaterial("G4_AIR");
	G4Box *airSlab = new G4Box("airSlab", 0.5*m, 0.5*m, 0.19*m);
	G4LogicalVolume *logicAir = new G4LogicalVolume(airSlab, air, "logicAir");
	G4VPhysicalVolume *physAir = new G4PVPlacement(0, G4ThreeVector(0,0,0.29*m), logicAir, "physAir", logicWorld, false, 0, true);

	//Adding Material Properties for Air
	G4double rIndexAir[2]={1.0,1.0};
	G4double absorptionAir[2]={0.2*m, 0.2*m};
	G4double mieAir[2]={0.2*m,0.2*m};

	G4MaterialPropertiesTable *mptAir= new G4MaterialPropertiesTable();

	mptAir->AddProperty("RINDEX", energy, rIndexAir, numEntries);
	mptAir->AddProperty("ABSLENGTH", energy, absorptionAir, numEntries);
	mptAir->AddProperty("MIEHG", energy, mieAir, numEntries);
	mptAir->AddConstProperty("MIEHG_FORWARD", mie_const[0]);
	mptAir->AddConstProperty("MIEHG_BACKWARD", mie_const[1]);
	mptAir->AddConstProperty("MIEHG_FORWARD_RATIO", mie_const[2]);

	air->SetMaterialPropertiesTable(mptAir);

	//sensitive detector construction
	G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);
    logicDetector = new G4LogicalVolume(solidDetector, air, "logicDetector");

    for(G4int i=0; i<100; i++){
        for(G4int j=0; j<100; j++){
            G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/100,-0.5*m+(j+0.5)*m/100, 0.49*m ), logicDetector, "physDetector", logicWorld, false, 100*i+j, true);
        }
    }




	return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
}
