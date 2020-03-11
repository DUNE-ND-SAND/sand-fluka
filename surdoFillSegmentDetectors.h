void FillSegmentDetectors(std::vector<TG4HitSegment>& dest, TTree *SttTree) {

	dest.clear();

        int NhitSttMax=50000;
        int IdStt[NhitSttMax];
	int IdParStt[NhitSttMax];
	int TrStt[NhitSttMax];
	int IntParStt[NhitSttMax];
	int RegStt[NhitSttMax];
        float PosInStt[NhitSttMax][3];
	float PosOuStt[NhitSttMax][3];
	float PStt[NhitSttMax][5];
	float TimeStt[NhitSttMax];
	float EdepStt[NhitSttMax];
	float EdqStt[NhitSttMax];

	int nentries=SttTree->GetEntries();  
	cout<<"Ho letto le entries"<<nentries<<endl;
	
	for(int i=0; i<nentries; i++){
		int Nstt=SttTree->GetEvent(i); // AS
	
		...
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
}
