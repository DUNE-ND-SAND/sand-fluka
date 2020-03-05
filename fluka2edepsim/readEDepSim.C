// TEST MACRO FOR USE WITH OLDER ROOT6.  DOESN"T WORK WHEN CLING KNOWS ABOUT
// THE VARIOUS CLASSES.
#include <TFile.h>
#include <TTree.h>

#include <iostream>

#include "readEDepSim.h"

TTree* gEDepSimTree = NULL;
TG4Event* gEDepSimEvent = NULL;
bool flukafile=true; //put true to read Provadep.root
bool traj=false;      //put true to read trajectories
bool segm=false;      //put true to read segment	

void readEDepSim() {
	std::cout<<"STARTING READ execution "<<std::endl;

	if(flukafile==true){
		TFile *ffile=new TFile("build/Provadep.root", "READ");
		gEDepSimTree = (TTree*) ffile->Get("EDepSimEvents");
	}else	gEDepSimTree = (TTree*) gFile->Get("EDepSimEvents");

	if (!gEDepSimTree) {
		std::cout << "Missing the event tree" << std::endl;
		return;
	}

	gEDepSimTree->SetBranchAddress("Event",&gEDepSimEvent);

	int N=gEDepSimTree->GetEntries();
	std::cout<<"number of entries "<<N<<std::endl;

	for (int i=0; i<2; i++){

		gEDepSimTree->GetEntry(i);
		EDepSimDumpEvent();
		//gEDepSimTree->Print();
	}
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

	std::cout << " event " << event->EventId;
	std::cout << " primaries " << event->Primaries.size();
	std::cout << " trajectories " << event->Trajectories.size();
	std::cout << std::endl;
	std::cout << "Analyzing PRIMARIES "<<std::endl;

	for (std::vector<TG4PrimaryVertex>::iterator
			v = event->Primaries.begin();
			v != event->Primaries.end(); ++v) {
		std::cout << "   Position " << v->Position.X()
			<< " " << v->Position.Y()
			<< " " << v->Position.Z()
			<< " Time " << v->Position.T();
		std::cout <<" Nbr of particles " << v->Particles.size();
		for (std::vector<TG4PrimaryParticle>::iterator
				p = v->Particles.begin();
				p != v->Particles.end(); ++p) {
			std::cout << " PDGcode " << p->PDGCode;
			std::cout << " Name " << p->Name;
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
			std::cout << " TRAJ POINTS:    ";

			for (std::vector<TG4TrajectoryPoint>::iterator
					p = t->Points.begin();
					p != t->Points.end();
					++p) {
				std::cout << " Time: " << p->Position.T();
				std::cout << " Process: " << p->Process;
				std::cout << " Subprocess: " << p->Subprocess;
				std::cout << std::endl;
				if (--count < 1) break;
			}
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
			for (std::vector<TG4HitSegment>::iterator
					h = d->second.begin();
					h != d->second.end();
					++h) {
				std::cout << "      ";
				std::cout << " PrimaryId: " << h->PrimaryId;
				std::cout << " EnergyDeposit: " << h->EnergyDeposit;
				//std::cout << " S: " << h->SecondaryDeposit;
				std::cout << " Contrib: " << h->Contrib.size();
				std::cout << " Track Length: " << h->TrackLength;
				std::cout << std::endl;
				if ((--count) < 1) break;
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
