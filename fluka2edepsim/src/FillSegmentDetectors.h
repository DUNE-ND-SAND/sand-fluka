#include "TTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "utils.h"
#include "MapGeometry.h"
#include "TVector3.h"

void SummarizeHitSegments(TG4HitSegmentContainer& dest, TTree *DetHits, int iev, int entries, int idet) {

	dest.clear();

	Int_t NCells,IdCell[NCellMax],IdParCell[NCellMax];
	Float_t hitPosX,hitPosY,hitPosZ;
	//std::cout<<"  ... in SummarizeHitSegments ... iev: "<<iev<<" ... Idet: "<<idet<<std::endl;

	if (idet < 3) {
		DetHits->SetBranchAddress("NStt",&NStt);
		DetHits->SetBranchAddress("IdStt",&IdStt);
		DetHits->SetBranchAddress("IdParStt",&IdParStt);
		DetHits->SetBranchAddress("TrStt",&TrStt);
		DetHits->SetBranchAddress("IntParStt",&IntParStt);
		DetHits->SetBranchAddress("PrimTrStt",&PrimTrStt);
		DetHits->SetBranchAddress("RegStt",&RegStt);
		DetHits->SetBranchAddress("PosInStt",&PosInStt);
		DetHits->SetBranchAddress("PStt",&PStt);
		DetHits->SetBranchAddress("TimeStt",&TimeStt);
		DetHits->SetBranchAddress("EdepStt",&EdepStt);
		DetHits->SetBranchAddress("EdqStt",&EdqStt);
		DetHits->SetBranchAddress("PosOuStt",&PosOuStt);
		DetHits->SetBranchAddress("DirStt",&DirStt); // (=0 NO Straw, =1 Straw along X, =2 Straw along Y)

		DetHits->GetEntry(iev); // AS

		//if (entries>100) entries = 100;  // for debug
		int det_str = 99;

		if (idet==1) {
			NSttHits = 0;
			for(int j=0; j<NStt; j++){
				float rad2 = pow(PosOuStt[j][1],2) + pow(PosOuStt[j][2],2);
				// STT:
				if (rad2 < 40000. && std::abs(PosOuStt[j][0])<169.) {

					TG4HitSegment hit;
					TG4HitSegment::Contributors Contrib;

					//hit.PrimaryId = IdParStt[j];
					//if (IntParStt[j] == 102 || IntParStt[j] == 110) hit.PrimaryId = TrStt[j];
					hit.PrimaryId = PrimTrStt[j];
					hit.EnergyDeposit = EdepStt[j];
					hit.SecondaryDeposit = 0.0;  //non ce lo abbiamo
					float segLen = sqrt(pow((PosOuStt[j][0]-PosInStt[j][0]),2) + pow((PosOuStt[j][1]-PosInStt[j][1]),2) + pow((PosOuStt[j][2]-PosInStt[j][2]),2));
					hit.TrackLength = segLen;

					(hit.Contrib).push_back(TrStt[j]);

					TLorentzVector pos_in(PosInStt[j][0],PosInStt[j][1],PosInStt[j][2],TimeStt[j]);
					TLorentzVector pos_out(PosOuStt[j][0],PosOuStt[j][1],PosOuStt[j][2],TimeStt[j]);

					hit.Start=GlobalCoordinates(pos_in);
					hit.Stop=GlobalCoordinates(pos_out);

					hitPosX = 0.5*(hit.Start.X()+hit.Stop.X());
					hitPosY = 0.5*(hit.Start.Y()+hit.Stop.Y());
					hitPosZ = 0.5*(hit.Start.Z()+hit.Stop.Z());
					TVector3 hitPos(hitPosX,hitPosY,hitPosZ);

					if (DirStt[j] == 1) det_str =1; // "stt_horizontal";
					else if (DirStt[j] == 2) det_str =2; // "stt_vertical";
					else {
						std::cout<<" ERROR not found DirStt!= da 1 e da 2 : "<<DirStt[j]<<std::endl;
						det_str= 10; // "not_found";
					}
					MapGeometry::Get()->AddPointToMap(det_str, hitPos);			

					NSttHits++;
					/*
					   if (segLen == 0.0) {
					//std::cout<<" ... hit-Loop .. segLen: "<<segLen<<" ... j: "<<j<<std::endl;
					//	    std::cout<<" ... xin: "<<PosInStt[j][0]<<" yin: "<<PosInStt[j][1]<<" zin: "<<PosInStt[j][2]<<std::endl;
					//	    std::cout<<" ... xout: "<<PosOuStt[j][0]<<" yout: "<<PosOuStt[j][1]<<" zout: "<<PosOuStt[j][2]<<std::endl;
					}
					*/
					dest.push_back(hit);
				}
			}
			//std::cout<<" STT> NSttHits: "<<NSttHits<<std::endl;
		}
		else if (idet==2) {
			int NCalHits = 0;
			for(int j=0; j<NStt; j++){
				float rad2 = pow(PosOuStt[j][1],2) + pow(PosOuStt[j][2],2);
				// ECAL:
				if (((rad2>=40000.&&rad2<50625.) || (std::abs(PosOuStt[j][0])>=169.)) && std::abs(PosOuStt[j][0])<216.) {

					TG4HitSegment hit;
					TG4HitSegment::Contributors Contrib;

					//hit.PrimaryId = IdParStt[j];
					//if (IntParStt[j] == 102 || IntParStt[j] == 110) hit.PrimaryId = TrStt[j];
					hit.PrimaryId = PrimTrStt[j];
					hit.EnergyDeposit = EdepStt[j];
					hit.SecondaryDeposit = 0.0;  //non ce lo abbiamo
					float segLen = sqrt(pow((PosOuStt[j][0]-PosInStt[j][0]),2) + pow((PosOuStt[j][1]-PosInStt[j][1]),2) + pow((PosOuStt[j][2]-PosInStt[j][2]),2));
					hit.TrackLength = segLen;

					(hit.Contrib).push_back(TrStt[j]);

					TLorentzVector pos_in(PosInStt[j][0],PosInStt[j][1],PosInStt[j][2],TimeStt[j]);
					TLorentzVector pos_out(PosOuStt[j][0],PosOuStt[j][1],PosOuStt[j][2],TimeStt[j]);

					hit.Start=GlobalCoordinates(pos_in);
					hit.Stop=GlobalCoordinates(pos_out);

					hitPosX = 0.5*(hit.Start.X()+hit.Stop.X());
					hitPosY = 0.5*(hit.Start.Y()+hit.Stop.Y());
					hitPosZ = 0.5*(hit.Start.Z()+hit.Stop.Z());
					TVector3 hitPos(hitPosX,hitPosY,hitPosZ);

					if (DirStt[j] == 0) det_str = 0; //"ecal";
					else { std::cout<<" NOT FOunD ... ??? det_str ???: "<<DirStt[j]<<std::endl; det_str=9;}
					MapGeometry::Get()->AddPointToMap(det_str, hitPos);			

					NCalHits++;
					/*
					   if (segLen == 0.0) {
					//std::cout<<" ... hit-Loop .. segLen: "<<segLen<<" ... j: "<<j<<std::endl;
					//	    std::cout<<" ... xin: "<<PosInStt[j][0]<<" yin: "<<PosInStt[j][1]<<" zin: "<<PosInStt[j][2]<<std::endl;
					//	    std::cout<<" ... xout: "<<PosOuStt[j][0]<<" yout: "<<PosOuStt[j][1]<<" zout: "<<PosOuStt[j][2]<<std::endl;
					}
					*/
					dest.push_back(hit);
				}
			}
			// std::cout<<" ECAL> NCalHits: "<<NCalHits<<std::endl;
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

			//hit.PrimaryId = IdCell[j];
			hit.PrimaryId = IdParCell[j];

			hit.EnergyDeposit = EdepCell[j];
			hit.SecondaryDeposit = 0.0;  //non ce lo abbiamo
			float segLen = 0.0;
			hit.TrackLength = segLen;

			(hit.Contrib).push_back(IdParCell[j]);

			TLorentzVector pos_in(PosCell[j][0],PosCell[j][1],PosCell[j][2],TimeStt[j]);
			TLorentzVector pos_out(PosCell[j][0],PosCell[j][1],PosCell[j][2],TimeStt[j]);

			hit.Start=GlobalCoordinates(pos_in);
			hit.Stop=GlobalCoordinates(pos_out);

			hitPosX = 0.5*(hit.Start.X()+hit.Stop.X());
			hitPosY = 0.5*(hit.Start.Y()+hit.Stop.Y());
			hitPosZ = 0.5*(hit.Start.Z()+hit.Stop.Z());
			TVector3 hitPos(hitPosX,hitPosY,hitPosZ);
			int det_str=3;
			MapGeometry::Get()->AddPointToMap(det_str, hitPos);			

			NDetHits++;
			dest.push_back(hit);
		}
		//std::cout<<" 3DST> NDetHits: "<<NDetHits<<std::endl;
		//
	}
	//
}

void FillSegmentDetectors(std::map<std::string, std::vector<TG4HitSegment> >& dest, TTree *SttHits, TTree *ScdHits,int ientry) {

	dest.clear();

	std::string det = "Straw";
	int iflag = 1;
	int entries_stt = 0;
	SummarizeHitSegments(dest[det], SttHits, ientry, entries_stt, iflag);

	//
	det = "EMCalSci";
	iflag = 2;
	int entries_ecal = 0;
	SummarizeHitSegments(dest[det], SttHits, ientry, entries_ecal, iflag);


	det = "3DST";
	iflag = 3;
	int entries_3dst = 0;
	SummarizeHitSegments(dest[det], ScdHits, ientry, entries_3dst, iflag);

}
