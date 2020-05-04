#include "TTree.h"
#include <iostream>
#include "utils.h"

void FillPrimaries(std::vector<TG4PrimaryVertex>& dest, TTree *rootracker, TTree *mytree, int entry) {
	dest.clear();

	//---Branch of HeaderTree
    	//*************************************************
       
	Int_t RunNum;
	Int_t EveNum;

	Int_t IntType;
	Int_t ReacType;

	Int_t Primary=0;
	Float_t Vertex[3];
	Float_t P_Primary[5];
	Int_t NumTracks;
	Int_t IdTrack[MaxN]; 	

	Int_t NumLep;
	Int_t NumPhot;
	Int_t NumHad;
	Int_t NumHeavy;

	Int_t IdLep[MaxN];
	Int_t TrLep[MaxN];
	Float_t P_Lep[MaxN][5];

	Int_t IdHad[MaxN];
	Int_t TrHad[MaxN];
	Float_t P_Had[MaxN][5];

	Int_t IdHeavy[MaxN];
	Int_t TrHeavy[MaxN];
	Float_t P_Heavy[MaxN][5];

	Int_t IdPhot[MaxN];
	Int_t TrPhot[MaxN];
	Float_t P_Phot[MaxN][5];
        //Genie
        Int_t    StdHepPdg[MaxN];
        Double_t StdHepP4[MaxN][4];
        Int_t    StdHepN;
	Int_t EvtNum;

	Int_t TargZ=0;
	Int_t TargA=0;

	mytree->SetBranchAddress("RunNum",&RunNum);
	mytree->SetBranchAddress("EveNum",&EveNum);

	mytree->SetBranchAddress("IntType",&IntType);
	mytree->SetBranchAddress("ReacType",&ReacType);
	mytree->SetBranchAddress("Primary",&Primary);

	mytree->SetBranchAddress("Vertex",&Vertex);
	mytree->SetBranchAddress("P_Primary",&P_Primary);
	mytree->SetBranchAddress("NumTracks",&NumTracks);
	mytree->SetBranchAddress("IdTrack",&IdTrack);

	mytree->SetBranchAddress("NumLep",&NumLep);
	mytree->SetBranchAddress("NumPhot",&NumPhot);
	mytree->SetBranchAddress("NumHeavy",&NumHeavy);
	mytree->SetBranchAddress("NumHad",&NumHad);

	mytree->SetBranchAddress("IdHad",&IdHad);
	mytree->SetBranchAddress("TrHad",&TrHad);
	mytree->SetBranchAddress("P_Had",&P_Had);

	mytree->SetBranchAddress("IdLep",&IdLep);
	mytree->SetBranchAddress("TrLep",&TrLep);
	mytree->SetBranchAddress("P_Lep",&P_Lep);

	mytree->SetBranchAddress("IdPhot",&IdPhot);
	mytree->SetBranchAddress("TrPhot",&TrPhot);
	mytree->SetBranchAddress("P_Phot",&P_Phot);

	mytree->SetBranchAddress("IdHeavy",&IdHeavy);
	mytree->SetBranchAddress("TrHeavy",&TrHeavy);
	mytree->SetBranchAddress("P_Heavy",&P_Heavy);

	mytree->SetBranchAddress("TargZ",&TargZ);
	mytree->SetBranchAddress("TargA",&TargA);
	
	EvtNum = EveNum;
	//-------------------------------------------------------------------------- RootrackerTree, some variables are still unknown
	
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
	//-------------------------------------------------------------------------- RootrackerTree

	mytree->GetEntry(entry);

	TG4PrimaryVertex vtx;

	std::cout<<"evenum "<<EveNum<<std::endl;
	//std::cout<<"Vertex coord "<<Vertex[0]<<" "<<Vertex[1]<<" "<<Vertex[2]<<std::endl;
	
	TLorentzVector vertex(Vertex[0],Vertex[1],Vertex[2],0.0);            //in fluka all events are at T=0

	vtx.Position=GlobalCoordinates(vertex); 

        vtx.GeneratorName="FLUKA";

	int NParticle=NumLep+NumPhot+NumHeavy+NumHad;

	std::cout<<"NParticle "<<NParticle<<std::endl;

	//std::cout<<"Number of particle in vertex "<<NParticle<<std::endl;
	// Add the particles associated with the vertex to the summary.
	TG4PrimaryParticle prim;
        //EvtCode     = new TObjString(ReacType);
        //EvtCode  = ReacType;      //which one is correct to be filled? it should be a string or int? in fluka it's int
        //EvtCode  = IntType;
 	StdHepN = NParticle+2;
 
	StdHepPdg[0] = Primary; 
        //Adding the Neutrino
	StdHepP4[0][0]=P_Primary[0];
	StdHepP4[0][1]=P_Primary[1];
	StdHepP4[0][2]=P_Primary[2];
	StdHepP4[0][3]=P_Primary[3];


	char Target_genie_code[100]; 

	char Anumber[3];

	if(TargA>99)  sprintf(Anumber,"%i",TargA);
	if(TargA<100) sprintf(Anumber,"0%i",TargA);
	if(TargA<10)  sprintf(Anumber,"00%i",TargA);
	
	char Znumber[3];
	if(TargZ>99)  sprintf(Znumber,"%i",TargZ);
	if(TargZ<100) sprintf(Znumber,"0%i",TargZ);
	if(TargZ<10)  sprintf(Znumber,"0%i",TargZ);
	
	sprintf(Target_genie_code,"100%s%s0",Znumber,Anumber);
	std::cout<<"Target_genie_code"<<Target_genie_code<<std::endl;
/*
ESEMPI di GENIE target CODES
	
		1000060120, #C12
             1000100200, #Ne20
             1000130270, #Al27
             1000140300, #Si30
	     1000180400, #Ar40
             1000260560, #Fe56
             1000822070, #Pb207  
*/


	 //Adding the target
	
	StdHepPdg[1] = atoi(Target_genie_code);

	StdHepP4[1][1]=0.0;
	StdHepP4[1][2]=0.0;
	StdHepP4[1][3]=0.0;


	int nPart=2;
		
	for(int k=0; k<NumLep; k++){
                StdHepPdg[nPart] = IdLep[k]; 
		StdHepP4[nPart][0]=P_Lep[0][k];
		StdHepP4[nPart][1]=P_Lep[1][k];
		StdHepP4[nPart][2]=P_Lep[2][k];
		StdHepP4[nPart][3]=P_Lep[3][k];
                nPart ++;

		prim.PDGCode = IdLep[k] ; 	
		prim.TrackId = TrLep[k];;
		prim.Momentum.SetX(P_Lep[0][k]);
		prim.Momentum.SetY(P_Lep[1][k]);
		prim.Momentum.SetZ(P_Lep[2][k]);
		prim.Momentum.SetE(P_Lep[3][k]);
		vtx.Particles.push_back(prim);
	}

	for(int k=0; k<NumHad; k++){
                StdHepPdg[nPart] = IdLep[k]; 
		StdHepP4[nPart][0]=P_Lep[0][k];
		StdHepP4[nPart][1]=P_Lep[1][k];
		StdHepP4[nPart][2]=P_Lep[2][k];
		StdHepP4[nPart][3]=P_Lep[3][k];
                nPart ++;

		prim.PDGCode = IdHad[k] ; 	
		prim.TrackId = TrHad[k];;
		prim.Momentum.SetX(P_Had[0][k]);
		prim.Momentum.SetY(P_Had[1][k]);
		prim.Momentum.SetZ(P_Had[2][k]);
		prim.Momentum.SetE(P_Had[3][k]);
		vtx.Particles.push_back(prim);
	}

	for(int k=0; k<NumPhot; k++){
                StdHepPdg[nPart] = IdPhot[k]; 
		StdHepP4[nPart][0]=P_Phot[0][k];
		StdHepP4[nPart][1]=P_Phot[1][k];
		StdHepP4[nPart][2]=P_Phot[2][k];
		StdHepP4[nPart][3]=P_Phot[3][k];
                nPart ++;

		prim.PDGCode = IdPhot[k] ; 	
		prim.TrackId = TrPhot[k];;
		prim.Momentum.SetX(P_Phot[0][k]);
		prim.Momentum.SetY(P_Phot[1][k]);
		prim.Momentum.SetZ(P_Phot[2][k]);
		prim.Momentum.SetE(P_Phot[3][k]);
		vtx.Particles.push_back(prim);
	}

	for(int k=0; k<NumHeavy; k++){
                StdHepPdg[nPart] = IdHeavy[k]; 
		StdHepP4[nPart][0]=P_Heavy[0][k];
		StdHepP4[nPart][1]=P_Heavy[1][k];
		StdHepP4[nPart][2]=P_Heavy[2][k];
		StdHepP4[nPart][3]=P_Heavy[3][k];
                nPart ++;

		prim.PDGCode = IdHeavy[k] ; 	
		prim.TrackId = TrHeavy[k];;
		prim.Momentum.SetX(P_Heavy[0][k]);
		prim.Momentum.SetY(P_Heavy[1][k]);
		prim.Momentum.SetZ(P_Heavy[2][k]);
		prim.Momentum.SetE(P_Heavy[3][k]);
		vtx.Particles.push_back(prim);
	}
       
	if(StdHepN!=nPart) std::cout<<"ERROR on number of particles in rootracker"<<std::endl;
       //rootracker->Print();
	rootracker->Fill();



/*
 // basic GENIE reaction types
      string genie_code = EvtCode->GetString().Data();
      bool is_cc    = (genie_code.find("Weak[CC]") != string::npos);
      bool is_nc    = (genie_code.find("Weak[NC]") != string::npos);
      bool is_charm = (genie_code.find("charm")    != string::npos);  //charm production
      bool is_qel   = (genie_code.find("QES")      != string::npos);
      bool is_dis   = (genie_code.find("DIS")      != string::npos);
      bool is_res   = (genie_code.find("RES")      != string::npos);
      bool is_cohpi = (genie_code.find("COH")      != string::npos);
      bool is_ve    = (genie_code.find("NuEEL")    != string::npos);
      bool is_imd   = (genie_code.find("IMD")      != string::npos);  //inverse muon decay
  */ 

 // nuclear target can be at slot 2 (for nuclear targets), slot 1 (for free nuc targets) or undefined (for ve-, IMD, coherent etc)
// bool nuclear_target = (target_code > 1000000000);


             //nu:14;tgt:1000822070;N:2112;proc:Weak[CC],QES;
        char* QES_RES_DIS=NULL;
        if(IntType==1) QES_RES_DIS=(char *)"QES"; 
        else if(IntType==2) QES_RES_DIS=(char *)"RES"; 
        else if(IntType==3) QES_RES_DIS=(char *)"DIS"; 
       	else{ std::cout<<"ERROR IntType type not found-- IntType : "<<IntType<<std::endl;}

        char* CC_NC=NULL;
	if(ReacType==1) CC_NC=(char *)"proc:Weak[CC]";
	else{ std::cout<<"ERROR Reaction type not found-- ReacType : "<<ReacType<<std::endl;}

	char* nu_type=NULL;
	if(Primary==12) nu_type=(char *)"nu_bar";
	if(Primary==14) nu_type=(char *)"nu";
	else{ std::cout<<"ERROR nu type not found-- Primary : "<<Primary<<std::endl;}

	//int Nboh=111111; //nucleone con cui ha interagito il neutrino non abbiamo questa info in FLUKA e quindi non la mettiamo

	char genie_format_reaction[100];
//	sprintf( genie_format_reaction, "%s:%i;tgt:%i;N:%i;%s;%s,%s",nu_type,Primary,Target_genie_code,Nboh,CC_NC,QES_RES_DIS);
	sprintf( genie_format_reaction, "%s:%i;tgt:%s;%s;%s",nu_type,Primary,Target_genie_code,CC_NC,QES_RES_DIS);


	vtx.Reaction = genie_format_reaction;   
	dest.push_back(vtx);
//	std::cout<<"Ho riempito "<<dest.size()<<std::endl;

}
