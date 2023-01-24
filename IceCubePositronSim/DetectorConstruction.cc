#include "DetectorConstruction.hh"


DetectorConstruction::DetectorConstruction()
{}
DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
	//G4NistManager *nist = G4NistManager::Instance();

	//creating ice
	G4int z, nelements;
	G4double a, density;
    G4Element* H = new G4Element("Hydrogen", "H", z = 1, a = 1.01 * g / mole);
    G4Element* O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * g / mole);
    G4Material* water = new G4Material("Water", density = 0.9 * g / cm3, nelements = 2);
    water->AddElement(H, 2);
    water->AddElement(O, 1);

    //ice mother volume
	G4Box *solidWorld = new G4Box("solidWrold", 0.5*m, 0.5*m, 0.5*m);

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, water, "logicWorld");

	G4VPhysicalVolume *physWorld= new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

	//Adding material properties for vacuum
    /*G4int numEntries = 2;
    G4double energy[2] =  {1.239841939*eV/0.2, 1.239841939*eV/0.9};
    G4double rIndexVacuum[2]={1.0,1.0};
	G4double absorptionVacuum[2]={200*m, 200*m};
	G4double mieVacuum[2]={500*m,500*m};
	G4double mie_const[3]={0.99,0.2,0.99};*/

	//ice constants

	G4int numEntries=32;
	std::vector<G4double> energy = {
    2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV,
    2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
    2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV,
    2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
    3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV,
    4.002 * eV, 4.9750 * eV
    };
    std::vector<G4double> rIndexIce = {
    1.3435, 1.344,  1.3445, 1.345,  1.3455, 1.346,  1.3465, 1.347,
    1.3475, 1.348,  1.3485, 1.3492, 1.35,   1.3505, 1.351,  1.3518,
    1.3522, 1.3530, 1.3535, 1.354,  1.3545, 1.355,  1.3555, 1.356,
    1.3568, 1.3572, 1.358,  1.3585, 1.359,  1.3595, 1.36,   1.3608
    };
	std::vector<G4double> absorptionIce = {
    3.448 * m,  4.082 * m,  6.329 * m,  9.174 * m,  12.346 * m, 13.889 * m,
    15.152 * m, 17.241 * m, 18.868 * m, 20.000 * m, 26.316 * m, 35.714 * m,
    45.455 * m, 47.619 * m, 52.632 * m, 52.632 * m, 55.556 * m, 52.632 * m,
    52.632 * m, 47.619 * m, 45.455 * m, 41.667 * m, 37.037 * m, 33.333 * m,
    30.000 * m, 28.500 * m, 27.000 * m, 24.500 * m, 22.000 * m, 19.500 * m,
    17.500 * m, 14.500 * m
    };
    std::vector<G4double> mieIce = {
    167024.4 * m, 158726.7 * m, 150742 * m,   143062.5 * m, 135680.2 * m,
    128587.4 * m, 121776.3 * m, 115239.5 * m, 108969.5 * m, 102958.8 * m,
    97200.35 * m, 91686.86 * m, 86411.33 * m, 81366.79 * m, 76546.42 * m,
    71943.46 * m, 67551.29 * m, 63363.36 * m, 59373.25 * m, 55574.61 * m,
    5730.429 * m, 5085.425 * m, 4496.467 * m, 3960.210 * m, 3473.413 * m,
    3032.937 * m, 1675.064 * m,
    1422.710 * m, 1200.004 * m, 1004.528 * m, 833.9666 * m, 686.1063 * m
    };
    G4double mieConst[3] = { 0.99, 0.99, 0.8 };

	/*G4MaterialPropertiesTable *mptVacuum= new G4MaterialPropertiesTable();

	mptVacuum->AddProperty("RINDEX", energy, rIndexVacuum, numEntries);
	mptVacuum->AddProperty("ABSLENGTH", energy, absorptionVacuum, numEntries);
	mptVacuum->AddProperty("MIEHG", energy, mieVacuum, numEntries);
	mptVacuum->AddConstProperty("MIEHG_FORWARD", mie_const[0]);
	mptVacuum->AddConstProperty("MIEHG_BACKWARD", mie_const[1]);
	mptVacuum->AddConstProperty("MIEHG_FORWARD_RATIO", mie_const[2]);

	Vacuum->SetMaterialPropertiesTable(mptVacuum);*/


	G4MaterialPropertiesTable *mptIce = new G4MaterialPropertiesTable();

	/*mptIce->AddProperty("RINDEX", energy, rIndexIce, numEntries);
	mptIce->AddProperty("ABSLENGTH", energy, absorptionIce, numEntries);
	mptIce->AddProperty("MIEHG", energy, mieIce, numEntries);
	mptIce->AddConstProperty("MIEHG_FORWARD", mieConst[0]);
	mptIce->AddConstProperty("MIEHG_BACKWARD", mieConst[1]);
	mptIce->AddConstProperty("MIEHG_FORWARD_RATIO", mieConst[2]);

	water->SetMaterialPropertiesTable(mptIce);
	*/

	mptIce->AddProperty("RINDEX", energy, rIndexIce, numEntries);

    /*for(size_t i = 1; i < energy.size(); ++i)
    {
        mptIce->AddEntry("RINDEX", energy[i], rIndexIce[i]);
    };*/
    mptIce->AddProperty("ABSLENGTH", energy, absorptionIce,numEntries);
    mptIce->AddProperty("MIEHG", energy, mieIce,numEntries);
    mptIce->AddConstProperty("MIEHG_FORWARD", mieConst[0]);
	mptIce->AddConstProperty("MIEHG_BACKWARD", mieConst[1]);
	mptIce->AddConstProperty("MIEHG_FORWARD_RATIO", mieConst[2]);

	water->SetMaterialPropertiesTable(mptIce);
	//water->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);


	/* //Glass Slab Construction

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

	air->SetMaterialPropertiesTable(mptAir); */

	//sensitive detector construction
	G4Sphere *solidDetector = new G4Sphere("solidDetector", 0.09*m, 0.1*m, 0, 2*CLHEP::pi, 0, CLHEP::pi);
	//G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);
    logicDetector = new G4LogicalVolume(solidDetector, water, "logicDetector");
    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicDetector, "physDetector", logicWorld, false, 0, true);


    /*for(G4int i=0; i<100; i++){
        for(G4int j=0; j<100; j++){
            G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/100,-0.5*m+(j+0.5)*m/100, 0.49*m ), logicDetector, "physDetector", logicWorld, false, 100*i+j, true);
        }
    }*/




	return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
}
