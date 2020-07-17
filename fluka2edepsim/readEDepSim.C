// TEST MACRO FOR USE WITH OLDER ROOT6.  DOESN"T WORK WHEN CLING KNOWS ABOUT
// THE VARIOUS CLASSES.
#include <TFile.h>
#include <TTree.h>
#include <TH2F.h>

#include <iostream>
#include <string>
#include "TVector3.h"
#include "readEDepSim.h"

TTree* gEDepSimTree = NULL;
TG4Event* gEDepSimEvent = NULL;
bool flukafile=true; //put true to read Provadep.root
bool traj=true;      //put true to read trajectories
bool segm=false;      //put true to read segment	
TH2F* PosCalZY;
TH2F* PosCalXY;
TH1F* PosCalX;

void readEDepSim() {
	std::cout<<"STARTING READ execution "<<std::endl;

	PosCalZY = new TH2F("PosCalZY","PosCalZY",1000,21500,26500,1000,-5000,0); //-5000.0,0.0,1000,21500.0,26500.0);
	PosCalXY = new TH2F("PosCalXY","PosCalXY",1000,-2500,2500,1000,-5000,0); //-5000.0,0.0,1000,21500.0,26500.0);
	if(flukafile==true){
	//	TFile *ffile=new TFile("/home/NEUTRINO/leadinotodune/MASTER/sand-fluka/fluka2edepsim/build/Prova.fluka2edep.root", "READ");
		TFile *ffile=new TFile("/home/NEUTRINO/leadinotodune/MASTER/sand-fluka/fluka2edepsim/sand_testflags001_Out.fluka2edep.root", "READ");
		gEDepSimTree = (TTree*) ffile->Get("EDepSimEvents");
		
		/*
		vector<pair<string,TVector3>>* MapGeo= NULL;
		ffile->GetObject("myGeometryMap",MapGeo);     //build by  WriteObjectAny(&map, "vector<pair<string,TVector3>>","myGeometryMap");

		std::cout<<"Map Geo element"<<MapGeo->size()<<std::endl;

		if(MapGeo->size()<1) {std::cout<<"Map Geo Empty"<<std::endl; }


		for (auto i = MapGeo->begin(); i != MapGeo->end(); ++i){

			pair<string, TVector3> val=(*i);

//			std::cout<<"det "<<val.first<<std::endl;
//			std::cout<<"point "<<val.second(0)<<" "<<val.second(1)<<" "<<val.second(2)<<std::endl;
		}
*/
	}else	gEDepSimTree = (TTree*) gFile->Get("EDepSimEvents");

	if (!gEDepSimTree) {
		std::cout << "Missing the event tree" << std::endl;
		return;
	}



	gEDepSimTree->SetBranchAddress("Event",&gEDepSimEvent);

	int N=gEDepSimTree->GetEntries();
	std::cout<<"number of entries "<<N<<std::endl;
	N=321;
	for (int i=0; i<N; i++){

		gEDepSimTree->GetEntry(i);
		EDepSimDumpEvent();
		//gEDepSimTree->Print();
	}
//	TFile *outf=new TFile ("drawCalZY.root", "RECREATE");	
//	PosCalZY->Write();
//	PosCalX->Write();
}
TTree* EDepSimTree() {
	return gEDepSimTree;
}

TG4Event* EDepSimEvent() {
	return gEDepSimEvent;
}


void EDepSimDumpEvent() {
	TG4Event* event = EDepSimEvent();
	if (!event) {
		std::cout << "Event not available" << std::endl;
	}

	const char* prova="ppp";
	std::cout<<prova<<std::endl;
	std::cout << " " << event->EventId;
	std::cout << " >event " << event->EventId;
	std::cout << " primaries " << event->Primaries.size();
	std::cout << " trajectories " << event->Trajectories.size();
	std::cout << " segment-detectors " << event->SegmentDetectors.size();
	std::cout << std::endl;
	std::cout << "Analyzing PRIMARIES "<<std::endl;

	for (std::vector<TG4PrimaryVertex>::iterator
			v = event->Primaries.begin();
			v != event->Primaries.end(); ++v) {
		std::cout << "   Position " << v->Position.X()
			<< " " << v->Position.Y()
			<< " " << v->Position.Z()
			<< " Time " << v->Position.T()
		        << " ReacType "<<v->Reaction;
		std::cout <<" Nbr of particles " << v->Particles.size()<<std::endl;
		for (std::vector<TG4PrimaryParticle>::iterator
				p = v->Particles.begin();
				p != v->Particles.end(); ++p) {
			std::cout << " TrackId " << p->TrackId;
			std::cout << " PDGcode " << p->PDGCode;
			std::cout << " Name " << p->Name<<std::endl;
		}
		std::cout << endl;
	}

	if(traj==true){
		std::cout << "Analyzing TRAJECTORY "<<std::endl;
		for (std::vector<TG4Trajectory>::iterator
				t = event->Trajectories.begin();
				t != event->Trajectories.end(); ++t) {
			std::cout << " TrackId " << t->TrackId;
			std::cout << " ParentId " << t->ParentId;
			std::cout << " Name " << t->Name;
			int count = t->Points.size();
			std::cout << " Up to " << count << " points";
			std::cout << std::endl;
	/*	
			   std::cout << " TRAJ POINTS:    ";
			   for (std::vector<TG4TrajectoryPoint>::iterator
			   p = t->Points.begin();
			   p != t->Points.end();
			   ++p) {
			   std::cout << " Time: " << p->Position.T();
			   std::cout << " Process: " << p->Process;
			//PosX->Fill(p->Position.X());
			std::cout << " Subprocess: " << p->Subprocess;
			std::cout << std::endl;
			if (--count < 1) break;
			}
*/	
		}
	}
	if(segm==true){	
		std::cout << "Analyzing SEGMENT DETECTORS "<<std::endl;
		for (auto d = event->SegmentDetectors.begin();
				d != event->SegmentDetectors.end(); ++d) {
			std::cout << "   det " << d->first;
			int count = d->second.size();
			std::cout << " up to " << count << " segments";
			std::cout << std::endl;

			if(d->first=="EMCalSci"){
				int oldcontrib=0;
				for (std::vector<TG4HitSegment>::iterator
						h = d->second.begin();
						h != d->second.end();
						++h) {
					//			std::cout << "      ";
					//			std::cout << " Coordinates: " << h->Start.X()<<" "<<h->Start.Y()<<" "<<h->Start.Z()<<std::endl;
					PosCalZY->Fill(h->Start.Z(), h->Start.Y());
					PosCalX->Fill(h->Start.X(), h->Start.Y());
					int contrib=h->Contrib[0];
					if(contrib!= oldcontrib){
						std::cout << " PrimaryId: " << h->PrimaryId;
					//			std::cout << " EnergyDeposit: " << h->EnergyDeposit;
					//std::cout << " S: " << h->SecondaryDeposit;
						std::cout << " Contrib: " << h->Contrib.size()<<" ["<<h->Contrib[0]<<"] ";
					//			std::cout << " Track Length: " << h->TrackLength;
								std::cout << std::endl;
						}
					oldcontrib=contrib;
					if ((--count) < 1) break;
				}
			}
		}
	}
}

TG4Event* EDepSimEvent(int i) {
	if (!gEDepSimTree) {
		std::cout << "Missing the event tree" << std::endl;
		return NULL;
	}
	gEDepSimTree->GetEntry(i);
	std::cout << "entry " << i;
	std::cout << " event " << gEDepSimEvent->EventId;
	std::cout << std::endl;
	return gEDepSimEvent;
}    
