// TEST MACRO FOR USE WITH OLDER ROOT6.  DOESN"T WORK WHEN CLING KNOWS ABOUT
// THE VARIOUS CLASSES.
#include <TFile.h>
#include <TTree.h>
#include <TH2F.h>

#include <iostream>
#include <string>
#include "TVector3.h"
#include "readEDepSim.h"
#include "transf.h"

TTree* gEDepSimTree = NULL;
TG4Event* gEDepSimEvent = NULL;
bool flukafile=true; //put true to read Provadep.root
bool segm=false;
float Mn=939.565378;

int NTOTNeut=0;

TH2F* PosCalZY;
TH2F* PosCalXY;
TH1F* PosCalX;

TFile *outf;
TFile *ffile;
TTree *outputTree;

Float_t Vertex_x;
Float_t Vertex_y;
Float_t Vertex_z;

Int_t Nfile;
Int_t Evnum;
Int_t NumNev;
Int_t TypeNIne;
Int_t NNHits;
Int_t out;
Float_t Pneut_vertex; 
Float_t NKinetic; 
Float_t PosNXlast;
Float_t PosNYlast;
Float_t PosNZlast;
Float_t TimeNlast;
Float_t NKineticNlast;
Float_t dist;


void NeutEDepSim() {
	std::cout<<"STARTING NEUT execution "<<std::endl;

	PosCalZY = new TH2F("PosCalZY","PosCalZY",1000,0.,0.,1000,0.,0.); //-5000.0,0.0,1000,21500.0,26500.0);
	PosCalXY = new TH2F("PosCalXY","PosCalXY",1000,0,0,1000,0,0); //-5000.0,0.0,1000,21500.0,26500.0);

	char basic[]="../data/sand2020_nocube_sttonly_anumu003_Out.fluka2edep";
	//char basic[]="../data/STT_RHC_CC_002_1e18.4321.edep";
	char nome [150];
	char nome_out [150];

	sprintf (nome, "%s.root",basic);

	sprintf (nome_out, "%s.NeutEDepSim.root",basic);
	std::cout<<"nome file output "<<nome_out<<std::endl;

	outf=new TFile (nome_out, "RECREATE");	
	outputTree=new TTree("mioTreeTraj","mioTreeTraj");
	//        outputTree->Branch("FoundinHits",&FoundinHits,"FoundinHits/I");
	//      outputTree->Branch("FoundinIne",&FoundinIne,"FoundinIne/I");
	outputTree->Branch("Nfile",&Nfile,"Nfile/I");
	outputTree->Branch("Evnum",&Evnum,"Evnum/I");
	outputTree->Branch("NumNev",&NumNev,"NumNev/I");
	outputTree->Branch("Pneut_vertex",&Pneut_vertex,"Pneut_vertex/F");
	outputTree->Branch("NKinetic",&NKinetic,"NKinetic/F");
	//  outputTree->Branch("NNHits",&NNHits,"NNHits/I");
	outputTree->Branch("TypeNIne",&TypeNIne,"TypeNIne/I");
	//  outputTree->Branch("NNIne",&NNIne,"NNIne/I");
	outputTree->Branch("Vertex_x",&Vertex_x,"Vertex_x/F");
	outputTree->Branch("Vertex_y",&Vertex_y,"Vertex_y/F");
	outputTree->Branch("Vertex_z",&Vertex_z,"Vertex_z/F");

	outputTree->Branch("PosNXlast",&PosNXlast,"PosNXlast/F");
	outputTree->Branch("PosNYlast",&PosNYlast,"PosNYlast/F");
	outputTree->Branch("PosNZlast",&PosNZlast,"PosNZlast/F");
	outputTree->Branch("TimeNlast",&TimeNlast,"TimeNlast/F");
	outputTree->Branch("NKineticNlast",&NKineticNlast,"NKineticNlast/F");
	outputTree->Branch("dist",&dist,"dist/F");
	outputTree->Branch("NNHits",&NNHits,"NNHits/I");
	outputTree->Branch("out",&out,"out/I");


	Nfile=0;
	for(int l=0; l<1; l++){
		if(flukafile==true){
			//TFile *ffile=new TFile("/eos/user/l/ldinoto/Edepsim_file/ECALSTT_FHC_Horn1Y_r1_001_5e16.200102.edep.root","READ");
			// /home/NEUTRINO/leadinotodune/MASTER/sand-fluka/fluka2edepsim/build/Prova.fluka2edep.root", "READ");

			//per i tanti file su cnaf ----modifica l!
			//sprintf (nome, "/data/genie_prod_1/edep-sim/numu_internal_10k.%d.gtrac.edepsim.root",l);
			//ffile=new TFile(nome,"READ");
			//Nfile=l;

			//per un solo file------modifica l!!
			//sprintf (nome, "data/sand2020_nocube_sttonly_anumu001_Out.fluka2edep.root");
			if(l==0) ffile=new TFile(nome, "READ");
			//if(l==1) ffile=new TFile("/data/genie_prod_1/edep-sim/numu_internal_10k.1.gtrac.edepsim.root", "READ");

			gEDepSimTree = (TTree*) ffile->Get("EDepSimEvents");
			std::cout<<"Leggo "<<nome<<std::endl;
		}else	gEDepSimTree = (TTree*) gFile->Get("EDepSimEvents");

		if (!gEDepSimTree) {
			std::cout << "Missing the event tree" << std::endl;
			return;
		}

		gEDepSimTree->SetBranchAddress("Event",&gEDepSimEvent);




		int N=gEDepSimTree->GetEntries();
		std::cout<<"number of entries "<<N<<std::endl;
		for(int i=0; i<N; i++){

			gEDepSimTree->GetEntry(i);
			EDepSimDumpEvent();
		}

	}
	std::cout<<"Sono fuori "<<std::endl;
	outf->cd();		
	PosCalZY->Write();
	PosCalXY->Write();
	outputTree->Write();
	std::cout<<"Ho scritto "<<std::endl;
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

	PosNXlast=99999;
	PosNYlast=99999;
	PosNZlast=99999;
	TimeNlast=99999; 
	TypeNIne=99999; 
	NKineticNlast=99999; 
	dist=99999; 


/*
	std::cout<<"-----------------------------------------------------------------------------------"<<std::endl;
	std::cout << " " << event->EventId;
	std::cout << " event " << event->EventId;
	std::cout << " primaries " << event->Primaries.size();
	std::cout << " trajectories " << event->Trajectories.size();
	std::cout << " segment-detectors " << event->SegmentDetectors.size();
	std::cout << std::endl;
	std::cout << "Analyzing PRIMARIES "<<std::endl;
*/
	Evnum=event->EventId;

	int NNneut=0;
	float T0=0;
	bool evok=false;
	int NPrimari=-1;	

	for (std::vector<TG4PrimaryVertex>::iterator
			v = event->Primaries.begin();
			v != event->Primaries.end(); ++v) {
//		std::cout << "   Position " << v->Position.X()
//			<< " " << v->Position.Y()
//			<< " " << v->Position.Z()
//			<< " Time " << v->Position.T()
//			<< " ReacType "<<v->Reaction;
//		std::cout <<" Nbr of particles " << v->Particles.size()<<std::endl;
		NPrimari=v->Particles.size();

		TLorentzVector vv=GlobalToLocalCoordinates(v->Position);
		Vertex_x=vv.X();
		Vertex_y=vv.Y();
		Vertex_z=vv.Z();
		T0=v->Position.T();
		
		PosCalXY->Fill(Vertex_x, Vertex_y);
		PosCalZY->Fill(Vertex_y,Vertex_z);
		//FV cut
		float RV=sqrt(Vertex_y*Vertex_y+Vertex_z*Vertex_z);
		if(RV>180 || abs(Vertex_x)>149) continue;
		evok=true;	

		for (std::vector<TG4PrimaryParticle>::iterator
				p = v->Particles.begin();
				p != v->Particles.end(); ++p) {
			//std::cout << " TrackId " << p->TrackId;
			//std::cout << " PDGcode " << p->PDGCode;
			//std::cout << " Name " << p->Name<<std::endl;
			if(p->PDGCode==2112){ //  Name=="neutron"){
				//			std::cout<<"neutrone"<<std::endl;
				//			std::cout<<"Mom E "<<p->Momentum.T()<<std::endl;
//				std::cout<<"Modulo del Momentum Mag "<<p->Momentum.Mag()<<std::endl;  //è un tetravettore
//				std::cout<<"Modulo del momento sqrt "<<sqrt(p->Momentum.X()*p->Momentum.X()+p->Momentum.Y()*p->Momentum.Y()+p->Momentum.Z()*p->Momentum.Z())<<std::endl;
//				std::cout << " TrackId " << p->TrackId<<std::endl;
				NNneut++;
				//			std::cout<<"Mom X "<<p->Momentum.X()<<std::endl;
				//			std::cout<<"Mom Y "<<p->Momentum.Y()<<std::endl;
				//			std::cout<<"Mom Z "<<p->Momentum.Z()<<std::endl;
				//			std::cout<<"Vert X "<<Vertex_x<<std::endl;
				//			std::cout<<"Vert Y "<<Vertex_y<<std::endl;
				//			std::cout<<"Vert Z"<<Vertex_z<<std::endl;

				}
			}
			//	std::cout << endl;
		}
		if(evok==false) {
		//	std::cout<<"Evento scartato "<<std::endl; 
			return;
		}
		//std::cout<<"Nell'evento ci sono "<<NNneut<<" neutroni "<<std::endl;


		NumNev=0;
		int NNcount=0; //conta i neutroni in TRAJ
		std::cout << "Analyzing TRAJECTORY "<<std::endl;
		std::cout<<"NPrimari "<<NPrimari<<std::endl;
		std::cout<<"leggo i trajectory dei primari"<<std::endl;	
		for (std::vector<TG4Trajectory>::iterator
				t = event->Trajectories.begin();
				t != event->Trajectories.end(); ++t) {

			if(t->TrackId<NPrimari) std::cout<<t->TrackId<<std::endl;
		}		



		std::cout<<"inizio il ciclo vero "<<std::endl;
		for (std::vector<TG4Trajectory>::iterator
				t = event->Trajectories.begin();
				t != event->Trajectories.end(); ++t) {

			if(t->ParentId<0 && t->TrackId>NPrimari) std::cout<<"ERROR nella variabile ParentId!!! Track "<<t->TrackId<<"non può essere primario"<<std::endl;
			if(t->TrackId>NPrimari) continue;
			std::cout<<"Ciclo sulle tracce "<<std::endl;
			std::cout << " TrackId " << t->TrackId;
			std::cout << " ParentId " << t->ParentId;
			std::cout << " Name " << t->Name<<std::endl;
			
			//int count = t->Points.size();
			//std::cout << " Up to " << count << " points";
			//			std::cout << std::endl;
			int NP=0;
			int ii=0;
			if(t->ParentId<0 && (t->TrackId<NPrimari || t->TrackId==NPrimari) && t->PDGCode==2112){
				std::cout<<"NEUTRONE TROVATO "<<std::endl;
				int NTR=t->TrackId;
				NP=t->Points.size();  //punti del neutrone
				std::cout << " TrackId " << t->TrackId<<" "<<NTR<<std::endl;
				
				NNcount++;
				out=0;
				
				//salvo dal vertice l'info del momento del neutrone
				for (std::vector<TG4PrimaryVertex>::iterator
					v = event->Primaries.begin();
					v != event->Primaries.end(); ++v) {
					v->Particles.size();

					for (std::vector<TG4PrimaryParticle>::iterator
						p = v->Particles.begin();
						p != v->Particles.end(); ++p) {
						std::cout << " TrackId " << p->TrackId<<std::endl;
						if(p->TrackId==NTR){ 
							Pneut_vertex=sqrt(p->Momentum.X()*p->Momentum.X()+p->Momentum.Y()*p->Momentum.Y()+p->Momentum.Z()*p->Momentum.Z());		
							
							std::cout<<"Pneut "<<Pneut_vertex<<std::endl;
							std::cout<<"Modulo del momento sqrt "<<sqrt(p->Momentum.X()*p->Momentum.X()+p->Momentum.Y()*p->Momentum.Y()+p->Momentum.Z()*p->Momentum.Z())<<std::endl;
							break;
						}
					}
				}		
				
				//		std::cout<<"Traiettoria neutrone: numero di punti "<<NP<<" NumNev "<<NumNev<<std::endl;
				for (std::vector<TG4TrajectoryPoint>::iterator
						p = t->Points.begin();
						p != t->Points.end();
						++p) {

					//std::cout << " NP "<<NP<<" count: " << count;
					//std::cout << " ii "<<ii<<" Time: " << p->Position.T();
					//std::cout << " Process: " << p->Process;
					//std::cout << " Position " <<p->Position.X()<<" "<<p->Position.Y()<<" "<<p->Position.Z();
					
					TLorentzVector pp=GlobalToLocalCoordinates(p->Position);
					
		//	std::cout << " Position in local" <<pp.X()<<" "<<pp.Y()<<" "<<pp.Z();
					//std::cout << " Momentum" <<p->Momentum.X()<<" "<<p->Momentum.Y()<<" "<<p->Momentum.Z()<<" "<<p->Momentum.Mag();
					//std::cout<<"modulo momento "<<sqrt((p->Momentum.X()*p->Momentum.X())+(p->Momentum.Y()*p->Momentum.Y())+(p->Momentum.Z()*p->Momentum.Z()));
					//std::cout << " Subprocess: " << p->Subprocess;
					//std::cout << std::endl;
					//PosCalZY->Fill(pp.Z(),pp.Y());
					
					if(abs(pp.X())>205 || sqrt(pp.Y()*pp.Y()+pp.Z()*pp.Z())>223) {
						out=1; 
						break;
					}  //salvo l'ultimo punto dentro
					
					PosNXlast=pp.X();
					PosNYlast=pp.Y();
					PosNZlast=pp.Z();
					TimeNlast= (p->Position.T()-T0)/1e9; // converto in secondi
				//	cout<<"time "<<TimeNlast<<" pos "<<PosNXlast<<" "<<PosNYlast<<" "<<PosNZlast<<endl;

					TypeNIne=p->Process;
					float Plast=p->Momentum.Mag()/1000;
					NKineticNlast=sqrt(Plast*Plast+Mn/1000*Mn/1000)-Mn/1000;
					dist=sqrt((PosNXlast-Vertex_x)*(PosNXlast-Vertex_x)+(PosNYlast-Vertex_y)*(PosNYlast-Vertex_y)+(PosNZlast-Vertex_z)*(PosNZlast-Vertex_z));

				} //chiude per ogni punto

			ii++;
			//if (--count < 1) break;
		NNHits=NP;   //NHits numero di punti del neutrone oltre al vertice
		if(TimeNlast<0) {
				if(ii==1) {
					TimeNlast=0;  //dentro al detector c'è solo il vertice}
			}else  {
				std::cout<<"ERROR "<<T0<<" "<<TimeNlast<<std::endl; std::exit(0);
			}
		}
		//	std::cout<<"PosNXlast PosNYlast PosNZlast "<< PosNXlast<<" "<<PosNYlast<<" "<<PosNZlast<<" "<<TimeNlast<<std::endl;
		//std::cout<<"EvNum NumNev "<<Evnum<<" "<<NumNev<<std::endl;
		outputTree->Fill();
		NumNev++;
	
		if(TimeNlast>100) cout<<" ERROR out time "<<out<<" "<<TimeNlast<<" pos "<<PosNXlast<<" "<<PosNYlast<<" "<<PosNZlast<<endl;
		}//chiude se è un neutrone

	} //chiude per ogni traccia
	
	std::cout<<"Ho letto tutte le tracce dell'evento "<<std::endl;
	if(NNneut!=NNcount) {std::cout<<"ERROR on Neut in TRAJ: nel vertice "<<NNneut<<" in Traj "<<NNcount<<std::endl; exit(0);}
	NTOTNeut+=NNneut;


	std::cout<<"Numero totale di neutroni "<<NTOTNeut<<std::endl;

}//chiude la funzione

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
