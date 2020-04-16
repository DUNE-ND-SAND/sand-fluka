#include "TTree.h"
#include "utils.h"

void Fillrootracker(TTree *rootracker, TTree *HeaderTree, int entry){
//EvtNum(int),  EvtFlags (TBits*), EvtCode (TObjString*), EvtXSec (double),EvtDXSec (double), EvtWght (double), EvtProb (double), EvtVtx (double[4]), StdHepN (int), StdHepPdg (int), StdHepStatus (int), StdHepRescat (int ), StdHepX4 (double [kNPmax][4]);
//StdHepP4 (double [kNPmax][4]), StdHepPolz (double [kNPmax][3]), StdHepFd (int [kNPmax]), StdHepLd (int [kNPmax]), StdHepFm (int [kNPmax]), StdHepLm (int [kNPmax]);
        constexpr int MaxN = 1000;
	int RunNum;
	int EveNum;

	int IntType;
	int ReacType;

	int   Primary;
	float Vertex[3];
	float P_Primary[5];
	int   NumTracks=0;
	int   IdTrack[1000]; 	

	int NumLep=0;
	int NumPhot=0;
	int NumHad=0;
	int NumHeavy=0;

	int IdLep[100000];
	int TrLep[1000];
	float P_Lep[1000][5];

	int IdHad[100000];
	int TrHad[1000];
	float P_Had[1000][5];

	int IdHeavy[1000];
	int TrHeavy[1000];
	float P_Heavy[1000][5];

	int IdPhot[1000];
	int TrPhot[1000];
	float  P_Phot[1000][5];
        //Genie Tree output variables
        int    StdHepPdg[MaxN];
        double StdHepP4[MaxN][4];
        int    StdHepN;
        int    EvtNum;
        //TObjString *EvtCode = 0;

	//int TargZ=0;
	//int TargA=0;

	HeaderTree->SetBranchAddress("RunNum",&RunNum);
	HeaderTree->SetBranchAddress("EveNum",&EveNum);

	HeaderTree->SetBranchAddress("IntType",&IntType);
	HeaderTree->SetBranchAddress("ReacType",&ReacType);
	HeaderTree->SetBranchAddress("Primary",&Primary);
	HeaderTree->SetBranchAddress("P_Primary",&P_Primary);

	HeaderTree->SetBranchAddress("Vertex",Vertex);
	HeaderTree->SetBranchAddress("P_Primary",P_Primary);
	HeaderTree->SetBranchAddress("NumTracks",&NumTracks);
	HeaderTree->SetBranchAddress("IdTrack",IdTrack);

	HeaderTree->SetBranchAddress("NumLep",&NumLep);
	HeaderTree->SetBranchAddress("NumPhot",&NumPhot);
	HeaderTree->SetBranchAddress("NumHeavy",&NumHeavy);
	HeaderTree->SetBranchAddress("NumHad",&NumHad);

	HeaderTree->SetBranchAddress("IdHad",IdHad);
	HeaderTree->SetBranchAddress("TrHad",TrHad);
	HeaderTree->SetBranchAddress("P_Had",P_Had);

	HeaderTree->SetBranchAddress("IdLep",IdLep);
	HeaderTree->SetBranchAddress("TrLep",TrLep);
	HeaderTree->SetBranchAddress("P_Lep",P_Lep);

	HeaderTree->SetBranchAddress("IdPhot",IdPhot);
	HeaderTree->SetBranchAddress("TrPhot",TrPhot);
	HeaderTree->SetBranchAddress("P_Phot",P_Phot);

	HeaderTree->SetBranchAddress("IdHeavy",IdHeavy);
	HeaderTree->SetBranchAddress("TrHeavy",TrHeavy);
	HeaderTree->SetBranchAddress("P_Heavy",P_Heavy);

        std::cout<< "**************SHOOOOOOOOOOOOOOOOOOOOOT******************"<<std::endl;
	HeaderTree->GetEntry(entry);
        std::cout<< "**************PASSSSSSSSSSSSSSSSSSSSS******************"<<std::endl;
	//HeaderTree->SetBranchAddress("TargZ",&TargZ);
	//HeaderTree->SetBranchAddress("TargA",&TargA);
        EvtNum = EveNum;
	//TTree *rootracker;
	//rootracker = new TTree("rootracker", "Genie Rootracker");
        
	rootracker->SetBranchAddress("EvtNum"   ,&EvtNum);
	//rootracker->SetBranchAddress("EvtFlags" ,&EvtFlags);
	//*rootracker->SetBranchAddress("EvtCode"  ,&EvtCode);
	//rootracker->SetBranchAddress("EvtXSec"  ,&EvtXSec, "EvtXSec/D");
	//rootracker->SetBranchAddress("EvtDXSec" ,&EvtDXSec,"EvtDXSec/D");
	//rootracker->SetBranchAddress("EvtWgt"   ,&EvtWgt,  "EvtWgt/D");
	//rootracker->SetBranchAddress("EvtProb"  ,&EvtProb, "EvtProb/D");
	//rootracker->SetBranchAddress("EvtProb"  ,&EvtProb, "EvtProb/D");
	//rootracker->SetBranchAddress("EvtVx[4]" ,&EvtVx,   "EvtVx[4]/D");
	rootracker->SetBranchAddress("StdHepN"  ,&StdHepN);
	rootracker->SetBranchAddress("StdHepPdg",&StdHepPdg);
	//rootracker->SetBranchAddress("StdHepStatus[StdHepN]",&StdHepStatus, "StdHepStatus[StdHepN]/I");
	//rootracker->SetBranchAddress("StdHepRescat[StdHepN]",&StdHepRescat, "StdHepRescat[StdHepN]/I");
	//rootracker->SetBranchAddress("StdHepX4[StdHepN][4]" ,&StdHepX4, "StdHepX4[StdHepN][4]/D");
	rootracker->SetBranchAddress("StdHepP4" ,&StdHepP4);
	//rootracker->SetBranchAddress("StdHepPolz[StdHepN][3]",&StdHepPolz, "StdHepPolz[StdHepN][3]/D");
	//rootracker->SetBranchAddress("StdHepFd[StdHepN]",&StdHepFd, "StdHepFd[StdHepN]/D");
	//rootracker->SetBranchAddress("StdHepLd[StdHepN]",&StdHepLd, "StdHepLd[StdHepN]/D");
	//rootracker->SetBranchAddress("StdHepFm[StdHepN]",&StdHepFm, "StdHepFm[StdHepN]/D");
	//rootracker->SetBranchAddress("StdHepLm[StdHepN]",&StdHepLm, "StdHepLm[StdHepN]/D");
//**************************************************************************************************

        //EvtCode     = new TObjString(ReacType);
        //EvtCode  = ReacType;
        //EvtCode  = IntType;
 
        int nPart= 0;

	StdHepPdg[nPart] = Primary; 
        //Adding the Neutrino
	StdHepP4[nPart][0]=P_Primary[0];
	StdHepP4[nPart][1]=P_Primary[1];
	StdHepP4[nPart][2]=P_Primary[2];
	StdHepP4[nPart][3]=P_Primary[3];
        nPart ++;
 
	for(int k=0; k<NumLep; k++){
                StdHepPdg[nPart] = IdLep[k]; 
		//prim.TrackId = TrLep[k];
		StdHepP4[nPart][0]=P_Lep[0][k];
		StdHepP4[nPart][1]=P_Lep[1][k];
		StdHepP4[nPart][2]=P_Lep[2][k];
		StdHepP4[nPart][3]=P_Lep[3][k];
                nPart ++;
	}

	for(int k=0; k<NumHad; k++){
                StdHepPdg[nPart] = IdHad[k]; 
		//prim.TrackId = TrHad[k];
		StdHepP4[nPart][0]=P_Had[0][k];
		StdHepP4[nPart][1]=P_Had[1][k];
		StdHepP4[nPart][2]=P_Had[2][k];
		StdHepP4[nPart][3]=P_Had[3][k];
                nPart ++;
	}

	for(int k=0; k<NumPhot; k++){
                StdHepPdg[nPart] = IdPhot[k]; 
		//prim.TrackId = TrPhot[k];;
		StdHepP4[nPart][0]=P_Phot[0][k];
		StdHepP4[nPart][1]=P_Phot[1][k];
		StdHepP4[nPart][2]=P_Phot[2][k];
		StdHepP4[nPart][3]=P_Phot[3][k];
                nPart ++;
	}

	for(int k=0; k<NumHeavy; k++){
                StdHepPdg[nPart] = IdHeavy[k]; 
		//prim.TrackId = TrHeavy[k];;
		StdHepP4[nPart][0]=P_Heavy[0][k];
		StdHepP4[nPart][1]=P_Heavy[1][k];
		StdHepP4[nPart][2]=P_Heavy[2][k];
		StdHepP4[nPart][3]=P_Heavy[3][k];
                nPart ++;
	}
        StdHepN = nPart;
        rootracker->Print();
	rootracker->Fill();
}
