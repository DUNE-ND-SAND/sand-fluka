#include "TTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

void SummarizeHitSegments(TG4HitSegmentContainer& dest, TTree *DetHits, int iev, int entries, int idet) {

	dest.clear();

	const int NhitMax=50000, NCellMax=50000;
	Int_t NStt;
	Int_t IdStt[NhitMax];
	Int_t IdParStt[NhitMax];
	Int_t TrStt[NhitMax];
	Int_t IntParStt[NhitMax];
	Int_t RegStt[NhitMax];
	Int_t TrHitContrib[100];
	Float_t PosInStt[NhitMax][3];
	Float_t PosOuStt[NhitMax][3];
	Float_t PStt[NhitMax][5];
	Float_t TimeStt[NhitMax];
	Float_t EdepStt[NhitMax];
	Float_t EdqStt[NhitMax];
//
	Int_t NCells,IdCell[NCellMax],IdParCell[NCellMax];
	Float_t PosCell[NCellMax][3],EdepCell[NCellMax],EdepQCell[NCellMax],TimeCell[NCellMax];
//
    std::cout<<"  ... in SummarizeHitSegments ... iev: "<<iev<<" ... Idet: "<<idet<<std::endl;
		
    if (idet < 3) {
	DetHits->SetBranchAddress("NStt",&NStt);
	DetHits->SetBranchAddress("IdStt",&IdStt);
	DetHits->SetBranchAddress("IdParStt",&IdParStt);
	DetHits->SetBranchAddress("TrStt",&TrStt);
	DetHits->SetBranchAddress("IntParStt",&IntParStt);
	DetHits->SetBranchAddress("RegStt",&RegStt);
	DetHits->SetBranchAddress("PosInStt",&PosInStt);
	DetHits->SetBranchAddress("PStt",&PStt);
	DetHits->SetBranchAddress("TimeStt",&TimeStt);
	DetHits->SetBranchAddress("EdepStt",&EdepStt);
	DetHits->SetBranchAddress("EdqStt",&EdqStt);
	DetHits->SetBranchAddress("PosOuStt",&PosOuStt);

	DetHits->GetEntry(iev); // AS

        //if (entries>100) entries = 100;  // for debug

	if (idet==1) {
	    int NSttHits = 0;
	    for(int j=0; j<NStt; j++){
		float rad2 = pow(PosOuStt[j][1],2) + pow(PosOuStt[j][2],2);
// STT:
		if (rad2 < 40000. && std::abs(PosOuStt[j][0])<169.) {

			TG4HitSegment hit;
			TG4HitSegment::Contributors Contrib;
		
			hit.PrimaryId = IdStt[j];
			hit.EnergyDeposit = EdepStt[j];
			hit.SecondaryDeposit = 0.0;  //non ce lo abbiamo
			float segLen = sqrt(pow((PosOuStt[j][0]-PosInStt[j][0]),2) + pow((PosOuStt[j][1]-PosInStt[j][1]),2) + pow((PosOuStt[j][2]-PosInStt[j][2]),2));

			TrHitContrib[0] = TrStt[j];
			   //Contrib.push_back(contrib);

			//hit.Contrib(TrHitContrib);

			hit.TrackLength = segLen;
			hit.Start.SetXYZT(PosInStt[j][0],
					PosInStt[j][1] -238.473,
					PosInStt[j][2] +2391.0,
					TimeStt[j]);
        		hit.Stop.SetXYZT(PosOuStt[j][0],
					PosOuStt[j][1] -238.473,
					PosOuStt[j][2] +2391.0,
					TimeStt[j]);
			NSttHits++;
//
                	if (segLen == 0.0) {
	         	  std::cout<<" ... hit-Loop .. segLen: "<<segLen<<" ... j: "<<j<<std::endl;
		 	  std::cout<<" ... xin: "<<PosInStt[j][0]<<" yin: "<<PosInStt[j][1]<<" zin: "<<PosInStt[j][2]<<std::endl;
		 	  std::cout<<" ... xout: "<<PosOuStt[j][0]<<" yout: "<<PosOuStt[j][1]<<" zout: "<<PosOuStt[j][2]<<std::endl;
	        	}
//
			dest.push_back(hit);
		}
	    }
	    std::cout<<" STT> NSttHits: "<<NSttHits<<std::endl;
	}
	else if (idet==2) {
	    int NCalHits = 0;
	    for(int j=0; j<NStt; j++){
		float rad2 = pow(PosOuStt[j][1],2) + pow(PosOuStt[j][2],2);
// ECAL:
		if ((rad2>=40000.&&rad2<50200.) || (std::abs(PosOuStt[j][0])>=169. && std::abs(PosOuStt[j][0])<205.)) {

			TG4HitSegment hit;
			TG4HitSegment::Contributors Contrib;
		
			hit.PrimaryId = IdStt[j];
			hit.EnergyDeposit = EdepStt[j];
			hit.SecondaryDeposit = 0.0;  //non ce lo abbiamo
			float segLen = sqrt(pow((PosOuStt[j][0]-PosInStt[j][0]),2) + pow((PosOuStt[j][1]-PosInStt[j][1]),2) + pow((PosOuStt[j][2]-PosInStt[j][2]),2));

			TrHitContrib[0] = TrStt[j];
			//hit.Contrib(TrHitContrib);

			hit.TrackLength = segLen;
			hit.Start.SetXYZT(PosInStt[j][0],
					PosInStt[j][1] -238.473,
					PosInStt[j][2] +2391.0,
					TimeStt[j]);
        		hit.Stop.SetXYZT(PosOuStt[j][0],
					PosOuStt[j][1] -238.473,
					PosOuStt[j][2] +2391.0,
					TimeStt[j]);
			NCalHits++;
//
                	if (segLen == 0.0) {
	          	  std::cout<<" ... hit-Loop .. segLen: "<<segLen<<" ... j: "<<j<<std::endl;
		  	  std::cout<<" ... xin: "<<PosInStt[j][0]<<" yin: "<<PosInStt[j][1]<<" zin: "<<PosInStt[j][2]<<std::endl;
		  	  std::cout<<" ... xout: "<<PosOuStt[j][0]<<" yout: "<<PosOuStt[j][1]<<" zout: "<<PosOuStt[j][2]<<std::endl;
	        	}
//
			dest.push_back(hit);
		}
	    }
	    std::cout<<" ECAL> NCalHits: "<<NCalHits<<std::endl;
	}
    }
    else if (idet==3) {

// 3DST:

	DetHits->SetBranchAddress("NCells",&NCells);
	DetHits->SetBranchAddress("PosCell",&PosCell);
	DetHits->SetBranchAddress("EdepCell",&EdepCell);
	DetHits->SetBranchAddress("EdepQCell",&EdepQCell);
	DetHits->SetBranchAddress("TimeCell",&TimeCell);
	DetHits->SetBranchAddress("IdCell",&IdCell);
	DetHits->SetBranchAddress("IdParCell",&IdParCell);

	DetHits->GetEntry(iev); // AS
	entries = NCells;

	int NDetHits = 0;
	for(int j=0; j<NCells; j++){
		TG4HitSegment hit;
		TG4HitSegment::Contributors Contrib;
		
		hit.PrimaryId = IdCell[j];
		hit.EnergyDeposit = EdepCell[j];
		hit.SecondaryDeposit = 0.0;  //non ce lo abbiamo
		//float segLen = 0.0;

		TrHitContrib[0] = IdParCell[j];
		//Contrib.push_back(contrib);

		//hit.Contrib(TrHitContrib);

		hit.TrackLength = 0.0;
		hit.Start.SetXYZT(PosCell[j][0],
				PosCell[j][1] -238.473,
				PosCell[j][2] +2391.0,
				TimeCell[j]);
        	hit.Stop.SetXYZT(PosCell[j][0],
				PosCell[j][1] -238.473,
				PosCell[j][2] +2391.0,
				TimeCell[j]);
		NDetHits++;
		dest.push_back(hit);
	}
	std::cout<<" 3DST> NDetHits: "<<NDetHits<<std::endl;
//
    }
//
}


void FillSegmentDetectors(std::map<std::string, std::vector<TG4HitSegment> >& dest, TTree *SttHits, TTree *ScdHits,int ientry) {

	dest.clear();

	std::string det = "STT";
	int iflag = 1;
	int entries_stt = 0;
	SummarizeHitSegments(dest[det], SttHits, ientry, entries_stt, iflag);
//
	det = "ECAL";
	iflag = 2;
	int entries_ecal = 0;
	SummarizeHitSegments(dest[det], SttHits, ientry, entries_ecal, iflag);
//
	det = "3DST";
	iflag = 3;
	int entries_3dst = 0;
	SummarizeHitSegments(dest[det], ScdHits, ientry, entries_3dst, iflag);
//
}