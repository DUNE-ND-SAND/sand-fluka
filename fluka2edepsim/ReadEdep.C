// TEST MACRO FOR USE WITH OLDER ROOT6.  DOESN"T WORK WHEN CLING KNOWS ABOUT
// THE VARIOUS CLASSES.
#include <TFile.h>
#include <TTree.h>
#include "TG4Event.h"
#include <iostream>


void DumpEvent() {
	TFile *ffile=new TFile("/eos/user/l/ldinoto/ECALSTT_FHC_Horn1Y_r1_001_5e16.200102.edep.root", "READ");
	TTree *gEDepTree =  (TTree*) ffile->Get("EDepSimEvents");
	if (!gEDepTree) {
		std::cout << "Missing the Levent tree" << std::endl;
		return;
	}
	TG4Event* Levent;
	gEDepTree->SetBranchAddress("Event",&Levent);

	if (!Levent) {
		std::cout << "Event not available" << std::endl;
	}

	int nentries= gEDepTree->GetEntries();
	cout<<"numero di entries "<<nentries<<endl;
	for(int i=0; i<2; i++)
		gEDepTree->GetEntry(i);
		std::cout << " Levent " << Levent->EventId;
		std::cout << " primaries " << Levent->Primaries.size();
		std::cout << " trajectories " << Levent->Trajectories.size();
		std::cout << std::endl;
		for (std::vector<TG4PrimaryVertex>::iterator
				v = Levent->Primaries.begin();
				v != Levent->Primaries.end(); ++v) {
			std::cout << "   Position " << v->Position.Z()
				<< " " << v->Position.Y()
				<< " " << v->Position.Z()
				<< " " << v->Position.T();
			std::cout << "  particles " << v->Particles.size();
			for (std::vector<TG4PrimaryParticle>::iterator
					p = v->Particles.begin();
					p != v->Particles.end(); ++p) {
				std::cout << " " << p->Name;
			}
			std::cout << endl;
		}
		for (std::vector<TG4Trajectory>::iterator
				t = Levent->Trajectories.begin();
				t != Levent->Trajectories.end(); ++t) {
			std::cout << "   Traj " << t->TrackId;
			std::cout << " " << t->ParentId;
			std::cout << " " << t->Name;
			std::cout << " " << t->Points.size();
			int count = 3;
			std::cout << " Up to " << count << " points";
			std::cout << std::endl;
			for (std::vector<TG4TrajectoryPoint>::iterator
					p = t->Points.begin();
					p != t->Points.end();
					++p) {
				std::cout << "      ";
				std::cout << " Time: " << p->Position.T();
				std::cout << " Process: " << p->Process;
				std::cout << " Subprocess: " << p->Subprocess;
				std::cout << std::endl;
				if (--count < 1) break;
			}
		}
		for (auto d = Levent->SegmentDetectors.begin();
				d != Levent->SegmentDetectors.end(); ++d) {
			std::cout << "   det " << d->first;
			std::cout << " " << d->second.size();
			int count = 10;
			std::cout << " up to " << count << " segments";
			std::cout << std::endl;
			for (std::vector<TG4HitSegment>::iterator
					h = d->second.begin();
					h != d->second.end();
					++h) {
				std::cout << "      ";
				std::cout << " P: " << h->PrimaryId;
				std::cout << " E: " << h->EnergyDeposit;
				std::cout << " S: " << h->SecondaryDeposit;
				std::cout << " C: " << h->Contrib.size();
				std::cout << " L: " << h->TrackLength;
				std::cout << std::endl;
				if ((--count) < 1) break;
			}
		}
	}
}
