#ifndef RUN_HH_INCLUDED
#define RUN_HH_INCLUDED

#include "G4UserRunAction.hh"
//#include "g4root.hh"
#include "G4AnalysisManager.hh"

class MyRunAction : public G4UserRunAction
{
public:

    MyRunAction();
    ~MyRunAction();

    virtual void BeginOfRunAction(const G4Run*) override;
    virtual void EndOfRunAction(const G4Run*);
};


#endif // RUN_HH_INCLUDED
