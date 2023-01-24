#include "sensitiveDetectorConstruction.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}
MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    //G4ThreeVector posPhoton = preStepPoint->GetPosition();

    G4ThreeVector momPhoton = preStepPoint->GetMomentum()/CLHEP::eV;

    G4cout<<"photonMomentum: "<<momPhoton<<G4endl;

    /*const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNO = touchable->GetCopyNumber();

    G4VPhysicalVolume *physVol = touchable->GetVolume();*/
    G4ThreeVector posDetector = preStepPoint->GetPosition()/CLHEP::m;
    //G4cout<<"photonPosition: "<<posDetector<<G4endl;

    //G4cout<<"detector position: "<<posDetector<<G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, posDetector[0]);
    man->FillNtupleDColumn(2, posDetector[1]);
    man->FillNtupleDColumn(3, posDetector[2]);
    man->FillNtupleDColumn(4, momPhoton[0]);
    man->FillNtupleDColumn(5, momPhoton[1]);
    man->FillNtupleDColumn(6, momPhoton[2]);
    man->AddNtupleRow(0);





    return true;
}
