#include "TTree.h"
#include <iostream>
#include "utils.h"

void FillPrimaries(std::vector<TG4PrimaryVertex>& dest, TTree *mytree, int entry) {
	dest.clear();

	//---Branch of HeaderTree
    	//*************************************************
       
	Int_t RunNum;
	Int_t EveNum;

	Int_t IntType;
	Int_t ReacType;

	//int Primary=0;
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

	//int TargZ=0;
	//int TargA=0;

	mytree->SetBranchAddress("RunNum",&RunNum);
	mytree->SetBranchAddress("EveNum",&EveNum);

	mytree->SetBranchAddress("IntType",&IntType);
	mytree->SetBranchAddress("ReacType",&ReacType);
	//mytree->SetBranchAddress("Primary",&Primary);

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

	//mytree->SetBranchAddress("TargZ",&TargZ);
	//mytree->SetBranchAddress("TargA",&TargA);

	std::cout<<"Prima di getentry"<<entry<<std::endl;

	mytree->GetEntry(entry);
	std::cout<<"Dopo di getentry"<<std::endl;


	TG4PrimaryVertex vtx;


	std::cout<<"evenum "<<EveNum<<std::endl;
	//std::cout<<"Vertex coord "<<Vertex[0]<<" "<<Vertex[1]<<" "<<Vertex[2]<<std::endl;
	
	TLorentzVector vertex(Vertex[0],Vertex[1],Vertex[2],0.0);            //in fluka all events are at T=0

	vtx.Position=GlobalCoordinates(vertex); 

	int NParticle=NumLep+NumPhot+NumHeavy+NumHad;

	std::cout<<"NParticle "<<NParticle<<std::endl;
	if(NumLep>MaxN || NumPhot>MaxN ||NumHad>MaxN || NumHeavy>MaxN) {
		std::cout<<"ERROR on MAX number of MaxN10000"<<std::endl;
		exit;
	}

	//std::cout<<"Number of particle in vertex "<<NParticle<<std::endl;
	// Add the particles associated with the vertex to the summary.
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
//	std::cout<<"Ho riempito "<<dest.size()<<std::endl;

}
