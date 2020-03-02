#include "TG4Event.h"
#include "FillPrimaries.h"
//#include "FillTrajectories.h"
#include <iostream>
#include "TTree.h"
#include "TFile.h"

int main() {
	// check to see if the event class is in the dictionary
	// if it is not load the definition in libEvent.so

	//if (!TClassTable::GetDict("Event")) {
	//cout<<"carico la libreria"<<endl;
	//gSystem->Load("libEvent.so");
	//cout<<"ho caricato la libreria"<<endl;
	// }
	std::cout<<"Inizio del programma"<<std::endl;
	
	/// The ROOT output file that events are saved into.
	TFile *fOutput;

	/// The event tree that contains the output events.
	TTree *fEventTree;

	/// The number of events saved to the output file since the last write.
	//int fEventsNotSaved;


	//Opening FLUKA FILE
	
	TFile *fInput = new TFile("/eos/user/s/salap/DUNE-IT/sand/sand_numu001_Out.root");
    	TTree *HeaderTree  = (TTree*)fInput->Get("HeaderTree");
    	//TTree *HitsTree = (TTree*)f->Get("HitsTree");
	
	//Opening EDEPSIM OUTPUT FILE	
	fOutput = TFile::Open("Provadep.root", "RECREATE", "EDepSim Root Output");
	fOutput->cd();

	fEventTree = new TTree("EDepSimEvents",
			"Energy Deposition for Simulated Events");

	TG4Event *pEvent=new TG4Event();
	fEventTree->Branch("Event","TG4Event",&pEvent);

	int NEVENT=HeaderTree->GetEntries();
	std::cout<<"Number of event to rewrite: "<<NEVENT<<std::endl;
	
	//scrivo dentro EDEPSIM
	for(int i=0; i<10; i++){  
		pEvent->RunId = 0;
		pEvent->EventId = i;
		std::cout<<"Event for run " << pEvent->RunId	<< " event " << pEvent->EventId<<std::endl;

		// Summarize the trajectories first so that fTrackIdMap is filled.
		//MarkTrajectories(event);
		
		FillPrimaries(pEvent->Primaries, HeaderTree, i);
		std::cout<<"   Primaries " << pEvent->Primaries.size()<<std::endl;

	//	FillTrajectories(pEvent->Trajectories,FlukaTree);
		std::cout<<"   Trajectories " << pEvent->Trajectories.size()<<std::endl;

		//FillSegmentDetectors(fEventSummary.SegmentDetectors, event);
		//cout<"   Segment Detectors "	<< pEvent.SegmentDetectors.size()<<endl;
	fEventTree->Fill();
	}
	fOutput->Write();            // Write the file header
	fEventTree->Print();           // Print the tree contents
        fOutput->Close();
}


