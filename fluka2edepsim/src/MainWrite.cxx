#include <map>
#include "TFile.h"
#include "TH1F.h"
#include "TG4Event.h"
#include "TNamed.h"
#include "TDatabasePDG.h"
#include "THashList.h"
//#include "TParticlePDG.h"
//#include "FillPrimaries.h"
//#include "FillTrajectories.h"

const int MaxNhit   = 10000; //Max Number of hits
const int MaxNLep   = 10000; //Max Number of hits
const int MaxNHad   = 10000; //Max Number of hits
const int MaxNHeavy = 10000; //Max Number of hits
const int MaxNPhot  = 10000; //Max Number of hits
const int MaxNTr    = 10000; //Max Number of hits
//Global variables
Int_t  IdTrack, NumTracks, IdTrck[MaxNTr], NumLep, IdLep[MaxNLep], TrLep[MaxNLep], NumHad, IdHad[MaxNHad], TrHad[MaxNHad], NumHeavy, IdHeavy[MaxNHeavy], TrHeavy[MaxNHeavy], NumPhot, IdPhot[MaxNPhot], TrPhot[MaxNPhot];
Float_t P_Lep[MaxNLep]  , P_Had[MaxNHad], P_Heavy[MaxNHeavy], P_Phot[MaxNPhot];
//Int_t   RunNum, EveNum  , NIncHits, IdTrack , IdInc[MaxNhit], IdParInc[MaxNhit], TrInc[MaxNhit], LatStt[MaxNhit];
//Float_t PInc[MaxNhit][5], TimeInc[MaxNhit];
//Float_t PosInc[MaxNhit][3];

TH1F* PosX;
#include "FillPrimaries.h"
#include "FillTrajectories.h"

int  main() {
	// check to see if the event class is in the dictionary
	// if it is not load the definition in libEvent.so

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
        

	//Opening FLUKA FILE
	
	TFile *fInput = new TFile("/eos/user/s/salap/DUNE-IT/sand/sand_nocube_tr_numu_001_Out.root");
    	TTree *HeaderTree  = (TTree*)fInput->Get("HeaderTree");
    	TTree *HitsTree = (TTree*)fInput->Get("HitsTree");
    	TTree *SttTree = (TTree*)fInput->Get("SttTree");
        //HeaderTree Info
    	//**********************************************
        HeaderTree->SetBranchAddress("NumTracks",&NumTracks);
        HeaderTree->SetBranchAddress("IdTrck",&IdTrack);
        //Lept Info
        HeaderTree->SetBranchAddress("NumLep",&NumLep);
        HeaderTree->SetBranchAddress("IdLep",&IdLep);
        HeaderTree->SetBranchAddress("TrLep",&TrLep);
        HeaderTree->SetBranchAddress("P_Lep",&P_Lep);
        //Had Info
        HeaderTree->SetBranchAddress("NumHad",&NumHad);
        HeaderTree->SetBranchAddress("IdHad",&IdHad);
        HeaderTree->SetBranchAddress("TrHad",&TrHad);
        HeaderTree->SetBranchAddress("P_Had",&P_Had);
        //Heavy Particle Info
        HeaderTree->SetBranchAddress("NumHeavy",&NumHeavy);
        HeaderTree->SetBranchAddress("IdHeavy",&IdHeavy);
        HeaderTree->SetBranchAddress("TrHeavy",&TrHeavy);
        HeaderTree->SetBranchAddress("P_Heavy",&P_Heavy);
        //Photon Info
        HeaderTree->SetBranchAddress("NumPhot",&NumPhot);
        HeaderTree->SetBranchAddress("IdPhot",&IdPhot);
        HeaderTree->SetBranchAddress("TrPhot",&TrPhot);
        HeaderTree->SetBranchAddress("P_Phot",&P_Phot);
    	//*************************************************
                          
        /*
	Int_t fRun,fEvent;
    	Float_t fx,fy,fz;
    	T->SetBranchAddress("Run",&Run);
    	T->SetBranchAddress("Event",&Event);
    	T->SetBranchAddress("x",&x);
    	T->SetBranchAddress("y",&y);
    	T->SetBranchAddress("z",&z);
    	TF->SetBranchAddress("Run",&fRun);
    	TF->SetBranchAddress("Event",&fEvent);
    	TF->SetBranchAddress("x",&fx);
    	TF->SetBranchAddress("y",&fy);
    	TF->SetBranchAddress("z",&fz);
    	T->AddFriend(TF);
	*/


	
	//Opening EDEPSIM OUTPUT FILE	
	fOutput = TFile::Open("Provadep.root", "RECREATE", "EDepSim Root Output");
	fOutput->cd();

        PosX = new TH1F("PosX","PosX",100,-250,250);
	fEventTree = new TTree("EDepSimEvents",
			"Energy Deposition for Simulated Events");

	TG4Event *pEvent=new TG4Event();
	fEventTree->Branch("Event","TG4Event",&pEvent);

	fEventsNotSaved = 0;

	int NEVENT=HeaderTree->GetEntries();
	std::cout<<"Number of event to rewrite: "<<NEVENT<<std::endl;
	
	//scrivo dentro EDEPSIM
	for(int i=0; i<NEVENT; i++){  
		pEvent->RunId = 0;
		pEvent->EventId = i;
		HeaderTree->GetEntry(i);

		// Summarize the trajectories first so that fTrackIdMap is filled.
		//MarkTrajectories(event);
		
		//FillPrimaries(pEvent->Primaries, HeaderTree);
		//std::cout<<"   Primaries " << pEvent->Primaries.size()<<endl;

		FillTrajectories(pEvent->Trajectories,HitsTree, SttTree, i);
		std::cout<<"   Trajectories " << pEvent->Trajectories.size()<<std::endl;

		//FillSegmentDetectors(fEventSummary.SegmentDetectors, event);
		//cout<"   Segment Detectors "	<< pEvent.SegmentDetectors.size()<<endl;
		fEventTree->Fill();
		//break;
	}
	fOutput->Write();            // Write the file header
	//fEventTree->Print();           // Print the tree contents
        fOutput->Close();
}


