#include "DetectorConstruction.hh"


DetectorConstruction::DetectorConstruction()
{

}
DetectorConstruction::~DetectorConstruction()
{

}

G4VPhysicalVolume *DetectorConstruction::Construct()
{

	//creating ice
	G4int z, nelements;
	G4double a, density;
    G4Element* H = new G4Element("Hydrogen", "H", z = 1, a = 1.01 * g / mole);
    G4Element* O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * g / mole);
    G4Material* water = new G4Material("Water", density = 0.9 * g / cm3, nelements = 2);
    water->AddElement(H, 2);
    water->AddElement(O, 1);

    //ice mother volume
    G4double cubeSideLength = 40.*m;

	G4Box *solidWorld = new G4Box("solidWrold", cubeSideLength/2, cubeSideLength/2, cubeSideLength/2);

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, water, "logicWorld");

	G4VPhysicalVolume *physWorld= new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

	//ice constants

	//depth assumed = 2.2km (AMANDA paper on ice properties)

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

    std::vector<G4double> absorptionIce = {7.03629708*m,   8.36689315*m,   9.98274229*m,  11.94478757*m,
        14.39402874*m,  17.36628222*m,  20.95485603*m,  25.36783598*m,
        30.61283538*m,  36.90086998*m,  44.29355318*m,  52.57766647*m,
        61.92773677*m,  71.83499252*m,  81.79740721*m,  91.22301808*m,
        99.67083403*m, 106.62134011*m, 111.71059737*m, 115.04461736*m,
       116.68976654*m, 116.92767716*m, 116.06537544*m, 114.37225939*m,
       112.11117543*m, 109.45694983*m, 106.52909421*m, 103.46747888*m,
       100.29364595*m,  97.09408084*m,  93.85717571*m,  74.22426142*m};

    std::vector<G4double> mieIce = {37.53124578*m, 36.9754402*m , 36.42113608*m, 35.86898834*m, 35.30500261*m,
       34.74529902*m, 34.190358*m  , 33.62744044*m, 33.07101785*m, 32.50913684*m,
       31.94338501*m, 31.38663422*m, 30.81708121*m, 30.24783821*m, 29.6800959*m ,
       29.11494555*m, 28.54405993*m, 27.96949574*m, 27.40170574*m, 26.82497909*m,
       26.24984859*m, 25.6703163*m , 25.09582815*m, 24.51398788*m, 23.93418458*m,
       23.35205411*m, 22.76429571*m, 22.17953092*m, 21.58936027*m, 21.00209473*m,
       20.41077326*m, 16.78011981*m};

    G4double mieConst[3] = { 0.99, 0.99, 0.8 };


	G4MaterialPropertiesTable *mptIce = new G4MaterialPropertiesTable();

	mptIce->AddProperty("RINDEX", energy, rIndexIce, numEntries);
    mptIce->AddProperty("ABSLENGTH", energy, absorptionIce,numEntries);
    mptIce->AddProperty("MIEHG", energy, mieIce,numEntries);
    mptIce->AddConstProperty("MIEHG_FORWARD", mieConst[0]);
	mptIce->AddConstProperty("MIEHG_BACKWARD", mieConst[1]);
	mptIce->AddConstProperty("MIEHG_FORWARD_RATIO", mieConst[2]);

	water->SetMaterialPropertiesTable(mptIce);

	//sensitive detector construction
	G4double outerRadi = 1.0 *m;
	G4double innerRadi = 0.9 *m;
	G4Sphere *solidDetector = new G4Sphere("solidDetector", innerRadi, outerRadi, 0, 2*CLHEP::pi, 0, CLHEP::pi);
    logicDetector = new G4LogicalVolume(solidDetector, water, "logicDetector");
    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicDetector, "physDetector", logicWorld, false, 0, true);

    //setting max step limit
    G4double maxStep = 10.*cm;
    maxStepLimit = new G4UserLimits(maxStep);
    logicWorld -> SetUserLimits(maxStepLimit);



	return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
}

void DetectorConstruction :: SetMaxStep(G4double maxStep)
{

    if((maxStepLimit)&&(maxStep>0.))
        maxStepLimit->SetMaxAllowedStep(maxStep);

}
