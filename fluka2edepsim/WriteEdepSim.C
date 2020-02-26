#include "TG4Event.h"
#include "FillPrimaries.h"
#include "FillTrajectories.h"

void WriteEdepSim() {
	// check to see if the event class is in the dictionary
	// if it is not load the definition in libEvent.so
	cout<<"inizio "<<endl;

	//if (!TClassTable::GetDict("Event")) {
	//cout<<"carico la libreria"<<endl;
	//gSystem->Load("libEvent.so");
	//cout<<"ho caricato la libreria"<<endl;
	// }

	//da mettere nel .h
	/// The ROOT output file that events are saved into.
	TFile *fOutput;

	/// The event tree that contains the output events.
	TTree *fEventTree;

	/// The number of events saved to the output file since the last write.
	int fEventsNotSaved;
	//FINE .hh


	//APRO IL FILE E CREO IL TREE	
	fOutput = TFile::Open("Provadep.root", "RECREATE", "EDepSim Root Output");
	fOutput->cd();

	fEventTree = new TTree("EDepSimEvents",
			"Energy Deposition for Simulated Events");

	//static TG4Event *pEvent = &fEventSummary;
	TG4Event *pEvent=new TG4Event();
	fEventTree->Branch("Event","TG4Event",&pEvent);

	fEventsNotSaved = 0;


	//apro il file di FLUKA
	TTree *HeaderTree;
	TTree *HitsTree;	

	//scrivo dentro EDEPSIM
	for(int i=0; i<30; i++){  //FIXME
		pEvent->RunId = 0;
		pEvent->EventId = i;
		cout<<"Event for run " << pEvent->RunId	<< " event " << pEvent->EventId<<endl;

		// Summarize the trajectories first so that fTrackIdMap is filled.
		//MarkTrajectories(event);
		
		FillPrimaries(pEvent->Primaries, HeaderTree);
		cout<<"   Primaries " << pEvent->Primaries.size()<<endl;

		FillTrajectories(pEvent->Trajectories,HitsTree);
		cout<<"   Trajectories " << pEvent->Trajectories.size()<<endl;

		//FillSegmentDetectors(fEventSummary.SegmentDetectors, event);
		//cout<"   Segment Detectors "	<< pEvent.SegmentDetectors.size()<<endl;
	fEventTree->Fill();
	}
	fOutput->Write();            // Write the file header
	fEventTree->Print();           // Print the tree contents
}


