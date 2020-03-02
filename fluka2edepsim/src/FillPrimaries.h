#include "TTree.h"
#include <iostream>

void FillPrimaries(std::vector<TG4PrimaryVertex>& dest, TTree *mytree, int entry) {
	dest.clear();

	//int nentries=mytree->GetEntries();  
	//std::cout<<"Ho letto le entries "<<nentries<<std::endl;

	//---Branch of HeaderTree

	int RunNum;
	int EveNum;

	int IntType;
	int ReacType;

	//int Primary=0;
	float Vertex[3];
	float P_Primary[5];
	int NumTracks=0;
	int IdTrack[1000]; 	

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
	float P_Phot[1000][5];

	//int TargZ=0;
	//int TargA=0;

	mytree->SetBranchAddress("RunNum",&RunNum);
	mytree->SetBranchAddress("EveNum",&EveNum);

	mytree->SetBranchAddress("IntType",&IntType);
	mytree->SetBranchAddress("ReacType",&ReacType);
	//mytree->SetBranchAddress("Primary",&Primary);

	mytree->SetBranchAddress("Vertex",Vertex);
	mytree->SetBranchAddress("P_Primary",P_Primary);
	mytree->SetBranchAddress("NumTracks",&NumTracks);
	mytree->SetBranchAddress("IdTrack",IdTrack);

	mytree->SetBranchAddress("NumLep",&NumLep);
	mytree->SetBranchAddress("NumPhot",&NumPhot);
	mytree->SetBranchAddress("NumHeavy",&NumHeavy);
	mytree->SetBranchAddress("NumHad",&NumHad);

	mytree->SetBranchAddress("IdHad",IdHad);
	mytree->SetBranchAddress("TrHad",TrHad);
	mytree->SetBranchAddress("P_Had",P_Had);

	mytree->SetBranchAddress("IdLep",IdLep);
	mytree->SetBranchAddress("TrLep",TrLep);
	mytree->SetBranchAddress("P_Lep",P_Lep);

	mytree->SetBranchAddress("IdPhot",IdPhot);
	mytree->SetBranchAddress("TrPhot",TrPhot);
	mytree->SetBranchAddress("P_Phot",P_Phot);

	mytree->SetBranchAddress("IdHeavy",IdHeavy);
	mytree->SetBranchAddress("TrHeavy",TrHeavy);
	mytree->SetBranchAddress("P_Heavy",P_Heavy);

	//mytree->SetBranchAddress("TargZ",&TargZ);
	//mytree->SetBranchAddress("TargA",&TargA);

	//for(int i=0; i<nentries; i++){
	mytree->GetEntry(entry);
	TG4PrimaryVertex vtx;

	vtx.Position.SetX(Vertex[0]);
	vtx.Position.SetY(Vertex[1]);
	vtx.Position.SetZ(Vertex[2]);
	vtx.Position.SetT(0);             //in fluka all events are at T=0

	int NParticle=NumLep+NumPhot+NumHeavy+NumHad;

	std::cout<<"Number of particle in vertex "<<NParticle<<std::endl;
	// Add the particles associated with the vertex to the summary.
	for (int j=0; j<NParticle ; ++j) {
		TG4PrimaryParticle prim;

		for(int k=0; k<NumLep; k++){
			prim.PDGCode = IdLep[k] ; 	
			prim.TrackId = TrLep[k];;
			prim.Momentum.SetX(P_Lep[0][k]);
			prim.Momentum.SetY(P_Lep[1][k]);
			prim.Momentum.SetZ(P_Lep[2][k]);
			prim.Momentum.SetE(P_Lep[3][k]);
			vtx.Particles.push_back(prim);
		}

		for(int k=0; k<NumHad; k++){
			prim.PDGCode = IdHad[k] ; 	
			prim.TrackId = TrHad[k];;
			prim.Momentum.SetX(P_Had[0][k]);
			prim.Momentum.SetY(P_Had[1][k]);
			prim.Momentum.SetZ(P_Had[2][k]);
			prim.Momentum.SetE(P_Had[3][k]);
			vtx.Particles.push_back(prim);
		}

		for(int k=0; k<NumPhot; k++){
			prim.PDGCode = IdPhot[k] ; 	
			prim.TrackId = TrPhot[k];;
			prim.Momentum.SetX(P_Phot[0][k]);
			prim.Momentum.SetY(P_Phot[1][k]);
			prim.Momentum.SetZ(P_Phot[2][k]);
			prim.Momentum.SetE(P_Phot[3][k]);
			vtx.Particles.push_back(prim);
		}

		for(int k=0; k<NumHeavy; k++){
			prim.PDGCode = IdHeavy[k] ; 	
			prim.TrackId = TrHeavy[k];;
			prim.Momentum.SetX(P_Heavy[0][k]);
			prim.Momentum.SetY(P_Heavy[1][k]);
			prim.Momentum.SetZ(P_Heavy[2][k]);
			prim.Momentum.SetE(P_Heavy[3][k]);
			vtx.Particles.push_back(prim);
		}

		//vtx.Reaction = char(222);   //FIXME
		dest.push_back(vtx);
	}
}
