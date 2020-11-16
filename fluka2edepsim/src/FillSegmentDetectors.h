#include "TTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "utils.h"
#include "MapGeometry.h"
#include "TVector3.h"
int point_counter;

/*
int where(Tree *SttTree, int iev){
int w=-1;
SttTree->SetBranchAddress("PosInStt",&PosInStt);
SttTree->GetEntry(iev);
float rad2 = pow(PosInStt[j][1],2) + pow(PosInStt[j][2],2);
		// STT:
 if (rad2 < 40000. && std::abs(PosInStt[j][0])<169.) w=1;
 if (((rad2>=40000.&&rad2<50625.) || (std::abs(PosInStt[j][0])>=169.)) && std::abs(PosInStt[j][0])<216.){
	if(w!=-1) std::cout<<"ERROR 1"<<std::endl 	
	 w=2;
	
	}
 if (rad2>50625. || std::abs(PosInStt[j][0])>216.) {
	if(w!=-1) std::cout<<"ERROR 2"<<std::endl 	
	w=3;
	}	
return w;
}
*/


void SummarizeHitSegments(TG4HitSegmentContainer& dest, TTree *DetHits, int iev, int entries, int idet) {

	dest.clear();

	Int_t NCells;
	Float_t hitPosX,hitPosY,hitPosZ;
	//
	//std::cout<<"  ... in SummarizeHitSegments ... iev: "<<iev<<" ... Idet: "<<idet<<std::endl;
	int det_str =99;  
	//0 se ecal, 
	//1 stt_orizontal 
	//2 stt_vertical
	//3 3dst 
	//4 catcher
	//

	if (idet < 4) {
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


/*
		// for debug
		int w=-1;
		for(int o=0; o<NStt; o++){
		w=-1;
		float rad2 = pow(PosInStt[o][1],2) + pow(PosInStt[o][2],2);
		// STT:
 		if (rad2 < 40000. && std::abs(PosInStt[o][0])<169.) w=1;   //STT
 		if ((rad2>=40000.&& rad2<50625. && std::abs(PosInStt[o][0])<216.) || (std::abs(PosInStt[o][0])>=169. && std::abs(PosInStt[o][0])<192. && rad2<40000.)){
			if(w!=-1) std::cout<<"ERROR 1"<<std::endl; 	
	 		w=2;
	
		}
 		if (rad2>50625. || std::abs(PosInStt[o][0])>=216.) {
			if(w!=-1) {
				std::cout<<"ERROR 2"<<std::endl; 	
				std::cout<<"Point "<<PosInStt[o][0]<<" "<<PosInStt[o][1]<<" "<<PosInStt[o][2]<<" w "<<w<<std::endl;
				}
				w=3;
				}	
		if(w==-1) std::cout<<"ERROR in nessuno"<<std::endl;

		}
*/
		if (idet==1) {
			NSttHits = 0;
			for(int j=0; j<NStt; j++){
				

				float rad2 = pow(PosInStt[j][1],2) + pow(PosInStt[j][2],2);
				// STT:
				if (rad2 < 40000. && std::abs(PosInStt[j][0])<169.) {

					TG4HitSegment hit;
					TG4HitSegment::Contributors Contrib;

					//hit.PrimaryId = IdParStt[j];
					//if (IntParStt[j] == 102 || IntParStt[j] == 110) hit.PrimaryId = TrStt[j];
					hit.PrimaryId = PrimTrStt[j];
					hit.EnergyDeposit = EdqStt[j]*1000;     
					hit.SecondaryDeposit = 0.0;  //non ce lo abbiamo
					float segLen = sqrt(pow((PosOuStt[j][0]-PosInStt[j][0]),2) + pow((PosOuStt[j][1]-PosInStt[j][1]),2) + pow((PosOuStt[j][2]-PosInStt[j][2]),2));
					hit.TrackLength = segLen;

					(hit.Contrib).push_back(TrStt[j]);

					TLorentzVector pos_in(PosInStt[j][0],PosInStt[j][1],PosInStt[j][2],TimeStt[j]*1e9);
					TLorentzVector pos_out(PosOuStt[j][0],PosOuStt[j][1],PosOuStt[j][2],TimeStt[j]*1e9);

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

					TrSttHits[NSttHits] = TrStt[j];
					NSttHits++;
					/*
					   if (segLen == 0.0) {
					//std::cout<<" ... hit-Loop .. segLen: "<<segLen<<" ... j: "<<j<<std::endl;
					//	    std::cout<<" ... xin: "<<PosInStt[j][0]<<" yin: "<<PosInStt[j][1]<<" zin: "<<PosInStt[j][2]<<std::endl;
					//	    std::cout<<" ... xout: "<<PosOuStt[j][0]<<" yout: "<<PosOuStt[j][1]<<" zout: "<<PosOuStt[j][2]<<std::endl;
					}
					*/
					point_counter++;
					dest.push_back(hit);
				}
			}
		}
		else if (idet==2) {
			//int NCalHits = 0;
			NCalHits = 0;
			for(int j=0; j<NStt; j++){
				float rad2 = pow(PosInStt[j][1],2) + pow(PosInStt[j][2],2);
				// ECAL:
		
				if ((rad2>=40000.&& rad2<50625. && std::abs(PosInStt[j][0])<215.) || (std::abs(PosInStt[j][0])>=169. && std::abs(PosInStt[j][0])<192. && rad2<40000.)){
	
					TG4HitSegment hit;
					TG4HitSegment::Contributors Contrib;

					//hit.PrimaryId = IdParStt[j];
					//if (IntParStt[j] == 102 || IntParStt[j] == 110) hit.PrimaryId = TrStt[j];
					hit.PrimaryId = PrimTrStt[j];
					hit.EnergyDeposit = EdqStt[j]*1000;
					hit.SecondaryDeposit = 0.0;  //non ce lo abbiamo
					float segLen = sqrt(pow((PosOuStt[j][0]-PosInStt[j][0]),2) + pow((PosOuStt[j][1]-PosInStt[j][1]),2) + pow((PosOuStt[j][2]-PosInStt[j][2]),2));
					hit.TrackLength = segLen;

					(hit.Contrib).push_back(TrStt[j]);

					TLorentzVector pos_in(PosInStt[j][0],PosInStt[j][1],PosInStt[j][2],TimeStt[j]*1e9);
					TLorentzVector pos_out(PosOuStt[j][0],PosOuStt[j][1],PosOuStt[j][2],TimeStt[j]*1e9);

					hit.Start=GlobalCoordinates(pos_in);
					hit.Stop=GlobalCoordinates(pos_out);

					hitPosX = 0.5*(hit.Start.X()+hit.Stop.X());
					hitPosY = 0.5*(hit.Start.Y()+hit.Stop.Y());
					hitPosZ = 0.5*(hit.Start.Z()+hit.Stop.Z());
					TVector3 hitPos(hitPosX,hitPosY,hitPosZ);

					if (DirStt[j] == 0) det_str = 0; //"ecal";
					else { std::cout<<" NOT FOunD ... ??? det_str ???: "<<DirStt[j]<<std::endl; det_str=9;}
					MapGeometry::Get()->AddPointToMap(det_str, hitPos);

					TrCalHits[NCalHits] = TrStt[j];
					NCalHits++;
					/*
					   if (segLen == 0.0) {
					//std::cout<<" ... hit-Loop .. segLen: "<<segLen<<" ... j: "<<j<<std::endl;
					//	    std::cout<<" ... xin: "<<PosInStt[j][0]<<" yin: "<<PosInStt[j][1]<<" zin: "<<PosInStt[j][2]<<std::endl;
					//	    std::cout<<" ... xout: "<<PosOuStt[j][0]<<" yout: "<<PosOuStt[j][1]<<" zout: "<<PosOuStt[j][2]<<std::endl;
					}
					*/
					point_counter++;
					dest.push_back(hit);
				}
			}
			// std::cout<<" ECAL> NCalHits: "<<NCalHits<<std::endl;
		}
		else if (idet==3) {
			NCatchHits = 0;
			for(int j=0; j<NStt; j++){
				float rad2 = pow(PosInStt[j][1],2) + pow(PosInStt[j][2],2);
				// Mu-Catcher:
				if (rad2>50625. || std::abs(PosInStt[j][0])>216.) {

					TG4HitSegment hit;
					TG4HitSegment::Contributors Contrib;

					hit.PrimaryId = PrimTrStt[j];
					hit.EnergyDeposit = EdqStt[j];
					hit.SecondaryDeposit = 0.0;  //non ce lo abbiamo
					float segLen = sqrt(pow((PosOuStt[j][0]-PosInStt[j][0]),2) + pow((PosOuStt[j][1]-PosInStt[j][1]),2) + pow((PosOuStt[j][2]-PosInStt[j][2]),2));
					hit.TrackLength = segLen;

					(hit.Contrib).push_back(TrStt[j]);

					TLorentzVector pos_in(PosInStt[j][0],PosInStt[j][1],PosInStt[j][2],TimeStt[j]*1e9);
					TLorentzVector pos_out(PosOuStt[j][0],PosOuStt[j][1],PosOuStt[j][2],TimeStt[j]*1e9);

					hit.Start=GlobalCoordinates(pos_in);
					hit.Stop=GlobalCoordinates(pos_out);

					hitPosX = 0.5*(hit.Start.X()+hit.Stop.X());
					hitPosY = 0.5*(hit.Start.Y()+hit.Stop.Y());
					hitPosZ = 0.5*(hit.Start.Z()+hit.Stop.Z());
					TVector3 hitPos(hitPosX,hitPosY,hitPosZ);

					if (DirStt[j] == 0) det_str = 4; //"catcher";
					else {
						std::cout<<" ... ??? det_str ???: "<<DirStt[j]<<std::endl;
						std::cout<<" ... x: "<<PosInStt[j][0]<<"  y: "<<PosInStt[j][1]<<"  z: "<<PosInStt[j][2]<<" , rad2: "<<rad2<<std::endl;
					}
					//cout<<" CAL-hit: "<<NCalHits<<" DirStt: "<<DirStt[j]<<"  det: "<<det_str<<std::endl;
					MapGeometry::Get()->AddPointToMap(det_str, hitPos);			

					TrCatchHits[NCatchHits] = TrStt[j];
					NCatchHits++;
					/*
					   if (segLen == 0.0) {
					//std::cout<<" ... hit-Loop .. segLen: "<<segLen<<" ... j: "<<j<<std::endl;
					//	    std::cout<<" ... xin: "<<PosInStt[j][0]<<" yin: "<<PosInStt[j][1]<<" zin: "<<PosInStt[j][2]<<std::endl;
					//	    std::cout<<" ... xout: "<<PosOuStt[j][0]<<" yout: "<<PosOuStt[j][1]<<" zout: "<<PosOuStt[j][2]<<std::endl;
					}
					*/
					dest.push_back(hit);
					point_counter++;
				}
			}
			// std::cout<<" CATCHER> NCatchHits: "<<NCatchHits<<std::endl;
		}
	}
	else if (idet==4) {

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

			TLorentzVector pos_in(PosCell[j][0],PosCell[j][1],PosCell[j][2],TimeStt[j]*1e9);
			TLorentzVector pos_out(PosCell[j][0],PosCell[j][1],PosCell[j][2],TimeStt[j]*1e9);

			hit.Start=GlobalCoordinates(pos_in);
			hit.Stop=GlobalCoordinates(pos_out);

			hitPosX = 0.5*(hit.Start.X()+hit.Stop.X());
			hitPosY = 0.5*(hit.Start.Y()+hit.Stop.Y());
			hitPosZ = 0.5*(hit.Start.Z()+hit.Stop.Z());
			TVector3 hitPos(hitPosX,hitPosY,hitPosZ);

			det_str=3;	
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
	point_counter=0;
	


	std::string det = "Straw";
	int iflag = 1;
	int entries_stt = 0;
	SummarizeHitSegments(dest[det], SttHits, ientry, entries_stt, iflag);
	//
	det = "EMCalSci";
	iflag = 2;
	int entries_ecal = 0;
	SummarizeHitSegments(dest[det], SttHits, ientry, entries_ecal, iflag);
	//
	det = "Catcher";
	iflag = 3;
	int entries_ecatch = 0;
	SummarizeHitSegments(dest[det], SttHits, ientry, entries_ecatch, iflag);
	//
	det = "3DST";
	iflag = 4;
	int entries_3dst = 0;
	SummarizeHitSegments(dest[det], ScdHits, ientry, entries_3dst, iflag);
	//
	std::cout<<"point counter "<<point_counter<<std::endl;	
	if(point_counter!=NStt) std::cout<<"ERROR on NUMBER OF POINT"<<std::endl;
}
