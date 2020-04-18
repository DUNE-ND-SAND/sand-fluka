#include <map>
#include "TFile.h"
#include "TH1F.h"
#include "TG4Event.h"
#include "TNamed.h"
#include "TDatabasePDG.h"
#include "THashList.h"
#include "utils.h"

//#include "TParticlePDG.h"
//#include "FillPrimaries.h"
//#include "FillTrajectories.h"

const int MaxNhit   = 100000; //Max Number of hits
const int MaxN   = 1000; //Max Number of hits
//const int MaxNHad   = 10000; //Max Number of hits
//const int MaxNHeavy = 10000; //Max Number of hits
//const int MaxNPhot  = 10000; //Max Number of hits
//const int MaxNTr    = 10000; //Max Number of hits
//Global variables
//Int_t  IdTrack, NumTracks, IdTrck[MaxNTr], NumLep, IdLep[MaxNLep], TrLep[MaxNLep], NumHad, IdHad[MaxNHad], TrHad[MaxNHad], NumHeavy, IdHeavy[MaxNHeavy], TrHeavy[MaxNHeavy], NumPhot, IdPhot[MaxNPhot], TrPhot[MaxNPhot];
//Float_t P_Lep[MaxNLep]  , P_Had[MaxNHad], P_Heavy[MaxNHeavy], P_Phot[MaxNPhot];
//Int_t   RunNum, EveNum  , NIncHits, IdTrack , IdInc[MaxNhit], IdParInc[MaxNhit], TrInc[MaxNhit], LatStt[MaxNhit];
//Float_t PInc[MaxNhit][5], TimeInc[MaxNhit];
//Float_t PosInc[MaxNhit][3];
Int_t NIncHits, NStt, NSttHits;
Int_t   TrInc[MaxNhit], TrStt[MaxNhit];
#include "FillPrimaries.h"
#include "FillTrajectories.h"
#include "FillSegmentDetectors.h"
#include "Check.h"

int  main() {
	/// The ROOT output file that events are saved into.
	TFile *fOutput;

	/// The event tree that contains the output events.
	TTree *fEventTree;

	//Opening FLUKA FILE
	
	//TFile *fInput = new TFile("/eos/user/s/salap/DUNE-IT/sand/sand_nocube_tr_numu_001_Out.root");
 	TFile *fInput = new TFile("/eos/user/s/salap/DUNE-IT/sand/sand_testflags001_Out.root");
	//TFile *fInput = new TFile("/home/NEUTRINO/leadinotodune/MASTER/sand-fluka/fluka2edepsim/sand_testflags001_Out.root");
    	
	TTree *HeaderTree  = (TTree*)fInput->Get("HeaderTree");
    	TTree *HitsTree = (TTree*)fInput->Get("HitsTree");
        TTree *SttTree = (TTree*)fInput->Get("SttTree");
	TTree *CellTree = (TTree*)fInput->Get("CellTree");
    	
	//*************************************************

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
	for(int i=0; i<NEVENT; i++){  
		pEvent->RunId = 0;
		pEvent->EventId = i;

		std::cout<<"Run " << pEvent->RunId	<< " Event " << pEvent->EventId<<std::endl;
//                Check();
		
		FillPrimaries(pEvent->Primaries, HeaderTree, i);
		std::cout<<"   Primaries " << pEvent->Primaries.size()<<std::endl;

		FillTrajectories(pEvent->Trajectories, HitsTree, i);
		std::cout<<"   Trajectories " << pEvent->Trajectories.size()<<std::endl;

		FillSegmentDetectors(pEvent->SegmentDetectors, SttTree, CellTree, i);
		std::cout<<"   Segment Detectors "	<< pEvent->SegmentDetectors.size()<<std::endl;
                
        Check();

		fEventTree->Fill();
		//break;
	}
	fOutput->Write();            // Write the file header
	//fEventTree->Print();           // Print the tree contents
        fOutput->Close();
}


