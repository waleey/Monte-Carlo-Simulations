#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"

class ActionInitialization : public G4VUserActionInitialization
{
	public:
		ActionInitialization();
		~ActionInitialization();

		virtual void Build() const;
		virtual void BuildForMaster() const;
};



#endif
