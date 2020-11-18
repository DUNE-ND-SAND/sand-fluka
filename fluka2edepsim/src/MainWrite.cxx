#include <map>
#include "TFile.h"
#include "TH1F.h"
#include "TG4Event.h"
#include "TNamed.h"
#include "TDatabasePDG.h"
#include "THashList.h"
#include "utils.h"
#include <string>
//#include "TParticlePDG.h"

const int MaxNhit   = 1000000; //Max Number of hits
const int MaxN   = 10000; //Max Number of hits

//Global variables
Int_t NIncHits, NStt, NSttHits, NCalHits, NCatchHits, NIneHits, NTIneSec;
Int_t TrInc[MaxNhit], TrStt[MaxNhit], TrSttHits[MaxNhit], TrCalHits[MaxNhit], TrCatchHits[MaxNhit];

// From FillTrajectories.h:
Int_t IdInc[MaxNhit], ParTrInc[MaxNhit], IdIne[MaxNhit], TypeIne[MaxNhit], IdParIne[MaxNhit], TrIne[MaxNhit], NSecIne[MaxNhit], IdSecIne[MaxNhit];
Float_t PInc[MaxNhit][5], TimeInc[MaxNhit], PosInc[MaxNhit][3], PosIne[MaxNhit][3], PIne[MaxNhit][3], TimeIne[MaxNhit], PSec[MaxNhit][5];

// From FillSegmentDetectors.h:
const int NhitMax = MaxNhit;
const int NCellMax = MaxNhit;
Int_t IdStt[NhitMax], IdParStt[NhitMax], IntParStt[NhitMax], PrimTrStt[NhitMax], RegStt[NhitMax], DirStt[NhitMax], FirstSec[NhitMax], TrSecIne[NhitMax] ;
Float_t PosInStt[NhitMax][3], PosOuStt[NhitMax][3], PStt[NhitMax][5], TimeStt[NhitMax], EdepStt[NhitMax], EdqStt[NhitMax];
//
Int_t IdCell[NCellMax],IdParCell[NCellMax];
Float_t PosCell[NCellMax][3],EdepCell[NCellMax],EdepQCell[NCellMax],TimeCell[NCellMax];


//
#include "FillPrimaries.h"
#include "FillTrajectories.h"
#include "FillSegmentDetectors.h"
//#include "Fillrootracker.h"
#include "Check.h"
#include "MapGeometry.h"
#include "MapTree.h"
	

int main(int argc, char* argv[])
{
//  TO BE USED FOR INPUT FROM CALL and OUTPUT with the name INPUT.fluka2edepsim.root

	if(argc != 2){
		std::cout<<"./Fluka2Edepsim <inputfile>"<<std::endl;
	}
	const char* finname=argv[1];
	std::cout<<"Input file : "<<finname<<std::endl;

	/// The ROOT output file that events are saved into.
	TFile *fOutput;

	/// The event tree that contains the output events.
	TTree *fEventTree;

	//Opening FLUKA FILE

	//TFile *fInput = new TFile("/eos/user/s/salap/DUNE-IT/sand/sand_nocube_tr_numu_001_Out.root");
	//TFile *fInput = new TFile("/eos/user/s/salap/DUNE-IT/sand/sand_testflags001_Out.root");
	//TFile *fInput = new TFile("/data/scratch/numu_1000.0.edepsim.root");  //FIXME to be deleted for general inputfile
	//TFile *fInput = new TFile("/home/NEUTRINO/leadinotodune/DATA_mio/sand_testflags001_Out.root");  //FIXME to be deleted for general inputfile
	
//        TFile *fInput = new TFile("/eos/user/s/salap/DUNE-IT/sand/sand2020_numu001_Out.root");

	//*************************************************
//  TO BE USED FOR INPUT FROM CALL and OUTPUT with the name INPUT.fluka2edepsim.root
	TFile *fInput = new TFile(finname);
	char* name2=argv[1];
	std::string namei=name2;

	std::cout<<"Nome iniziale "<<namei<<std::endl;

	int s=0;
	
	std::size_t found = namei.find("..");
  	
	while (found!=std::string::npos){	
	
		namei.erase(0,3); //elimino ../	
		std::cout<<"Nome ora "<<namei<<std::endl;
		s++;
		found=namei.find("..");
		}
	strtok(name2, ".");
	std::string name3=namei;
	std::string nameout=name3+ ".fluka2edep.root";
	
	for(int i=0; i<s; i++){
		nameout="../"+nameout;
		
	}
	
	const char*foutname=nameout.c_str();

	std::cout<<"Output file in "<<foutname<<std::endl;
	
	TTree *HeaderTree  = (TTree*)fInput->Get("HeaderTree");
	TTree *HitsTree = (TTree*)fInput->Get("HitsTree");
	TTree *SttTree = (TTree*)fInput->Get("SttTree");
	TTree *CellTree = (TTree*)fInput->Get("CellTree");

	Int_t Run, Evnum;
	HeaderTree->SetBranchAddress("RunNum",&Run);
	HeaderTree->SetBranchAddress("EveNum",&Evnum);
	

	//Opening EDEPSIM OUTPUT FILE	
	fOutput = TFile::Open(foutname, "RECREATE", "EDepSim Root Output");  
	//fOutput = TFile::Open("Prova.fluka2edep.root", "RECREATE", "EDepSim Root Output");  //FIXME to be deleted for output = input.fluka2edep.root

	fOutput->cd();

	fEventTree = new TTree("EDepSimEvents",
			"Energy Deposition for Simulated Events");

	TG4Event *pEvent=new TG4Event();
	fEventTree->Branch("Event","TG4Event",&pEvent);

/*
	TTree *MapTree;
	MapTree = new TTree("MapTree", "MapTree");

        MapTree->Branch("EvtNum"    ,0, "EvtNum/I");
	MapTree->Branch("NhitT"   ,0, "NhitT/I");
	MapTree->Branch("Position"   ,0, "Position[NhitT][3]/D");
*/

	MapTree::Get()->InitTree();

       
        TTree *rootracker;
	rootracker = new TTree("gRooTracker", "Genie Rootracker");
	rootracker->Branch("EvtNum"    ,0, "EvtNum/I");
	rootracker->Branch("StdHepN"   ,0, "StdHepN/I");
	rootracker->Branch("StdHepPdg"     ,0,  "StdHepPdg[StdHepN]/I");
	rootracker->Branch("StdHepP4"   ,0, "StdHepP4[StdHepN][4]/D");




	int NEVENT=HeaderTree->GetEntries();
	HeaderTree->GetEntry(0);
	int run=Run;
	int iev=Evnum;
	std::cout<<"Number of event to rewrite: "<<NEVENT<<std::endl;

	//scrivo dentro EDEPSIM
	for(int i=0; i<NEVENT; i++){  

		std::cout<<"entry ---------------------------------------"<<i<<std::endl;	
		//MapGeometry::Get()->ClearMap();
	
		pEvent->RunId = run;
		pEvent->EventId = iev+i;

		std::cout<<"Run " << pEvent->RunId	<< " Event " << pEvent->EventId<<std::endl;

		FillPrimaries(pEvent->Primaries, rootracker, HeaderTree, i);
	//	std::cout<<"   Primaries " << pEvent->Primaries.size()<<std::endl;


		FillTrajectories(pEvent->Trajectories, HitsTree, i);
		std::cout<<"   Trajectories " << pEvent->Trajectories.size()<<std::endl;

		


		FillSegmentDetectors(pEvent->SegmentDetectors, SttTree, CellTree, i);
		std::cout<<"   Segment Detectors "	<< pEvent->SegmentDetectors.size()<<std::endl;

                //Check();
	 	fEventTree->Fill();

	//	MapTree::Get()->Fill_MapTree(MapGeometry::Get()->GetMap(), i);
	
	/*	
		std::cout<<"Ok"<<std::endl;
		vector<pair<string,TVector3>> map=MapGeometry::Get()->GetMap();

        	std::cout<<"La mappa dei punti ha "<<map.size()<<" elementi "<<std::endl;
        	Evt=i;
        	int ihit=0;

        	NhitT=map.size();
		std::cout<<"NhitT "<<NhitT<<std::endl;
	
		for(int j=0; j<NhitT; j++){

			Postrei[j]=j;
		}

        	for (auto j = map.begin(); j != map.end(); ++j){
			std::cout<<"inizio "<<std::endl;
			
                       // pair<string, TVector3> val=(*j);

//                      detpos[ihit]=val.first;
                       // std::cout<<"detector "<<val.first<<std::endl;
                //	std::cout<<"position "<<val.second(0)<<std::endl;
                   
		    	Pos[ihit]=(*j).second(0);
                       
			
			//Pos[ihit][0]=val.second(0);
                        //Pos[ihit][1]=val.second(1);
                        //Pos[ihit][2]=val.second(2);
                        std::cout<<"ihit"<<ihit<<std::endl;
			if(ihit==NhitT) {std::cout<<"ERROR on total number of hits"<<std::endl; break;}
			ihit++;
	        }
		std::cout<<"fuori dalla lettura della mappa ihit "<<ihit<<std::endl;
        	if(ihit!=NhitT) {std::cout<<"ERROR on number of hits"<<std::endl; exit(1); }
*/  
	

	}
	fOutput->Write();            // Write the file header
	
        //vector<pair<string,TVector3>> map=MapGeometry::Get()->GetMap();

	//fOutput->WriteObjectAny(&map, "vector<pair<string,TVector3>>","myGeometryMap");

	//fEventTree->Print();           // Print the tree contents
	fOutput->Close();
	std::cout<<"DONE!!: Output file in "<<foutname<<std::endl;
	

}


