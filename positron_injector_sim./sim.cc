#include<iostream>
#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4VisManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4Types.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "action.hh"
int main(int argc, char** argv)
{

    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager = new G4MTRunManager();
    #else
        G4RunManager *runManager = new G4RunManager();

    #endif



	runManager ->SetUserInitialization(new DetectorConstruction());
	runManager ->SetUserInitialization(new PhysicsList());
	runManager ->SetUserInitialization(new ActionInitialization());

	G4UIExecutive *ui = nullptr;

	if( argc ==1)
	{
        ui = new G4UIExecutive(argc, argv);

        runManager->SetNumberOfThreads(4);
        runManager->Initialize();
	}



	G4VisManager *visManager = new G4VisExecutive();
	visManager ->Initialize();

	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	if(!ui)
	{
        G4String command ="/control/execute ";

        G4String fileName = argv[1];

        UImanager->ApplyCommand(command+fileName);
    }
    else
    {



        UImanager ->ApplyCommand("/vis/open OGL");
        UImanager ->ApplyCommand("/vis/drawVolume");
        UImanager ->ApplyCommand("/vis/scene/add/trajectories smooth");
        UImanager ->ApplyCommand("/vis/viewer/set/autoRefresh true");

        ui->SessionStart();
        delete ui;

    }

	return 0;
}
