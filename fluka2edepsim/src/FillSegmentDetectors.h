void FillSegmentDetectors(std::vector<TG4HitSegment>& dest, TTree *SttTree, int ientry) {

	dest.clear();

    const int NhitMax=50000;
    Int_t IdStt[NhitMax];
	Int_t IdParStt[NhitMax];
	Int_t TrStt[NhitMax];
	Int_t IntParStt[NhitMax];
	Int_t RegStt[NhitMax];
    Float_t PosInStt[NhitMax][3];
	Float_t PosOuStt[NhitMax][3];
	Float_t PStt[NhitMax][5];
	Float_t TimeStt[NhitMax];
	Float_t EdepStt[NhitMax];
	Float_t EdqStt[NhitMax];

	int Nstt=SttTree->GetEvent(i); // AS
		
	for(int j=0; j<Nstt; j++){
		TG4HitSegment hit;
	
		hit.PrimaryId = IdStt[j];
        hit.EnergyDeposit = EdepStt[j];
        hit.SecondaryDeposit = 0.0;  //non ce lo abbiamo
		float segLen = sqrt(TMath::Power((PosOuStt[j][0]-PosInStt[j][0]),2) + TMath::Power((PosOuStt[j][1]-PosInStt[j][1]),2) + TMath::Power((PosOuStt[j][2]-PosInStt[j][2]),2));
       	hit.TrackLength = segLen;
      	hit.Start.SetXYZT(PosInStt[j][0],
					  	  PosInStt[j][1],
					 	  PosInStt[j][2],
						  TimeStt[j]);
        hit.Stop.SetXYZT(PosOuStt[j][0],
						 PosOuStt[j][1],
						 PosOuStt[j][2],
						 TimeStt[j]);
    
	    dest.push_back(hit);
	}
}
