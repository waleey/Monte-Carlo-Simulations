#ifndef SENSITIVEDETECTORCONSTRUCTION_HH_INCLUDED
#define SENSITIVEDETECTORCONSTRUCTION_HH_INCLUDED

#include "G4VSensitiveDetector.hh"
//#include "g4root.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

class MySensitiveDetector : public G4VSensitiveDetector{
public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();
private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};


#endif // SENSITIVEDETECTORCONSTRUCTION_HH_INCLUDED
