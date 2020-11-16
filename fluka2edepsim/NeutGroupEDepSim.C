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
#include "Grouped_Barrel_Time.h"
#include "Grouped_Endcap_Time.h"


TTree* gEDepSimTree = NULL;
TG4Event* gEDepSimEvent = NULL;
bool flukafile=true; //put true to read Provadep.root
bool segm=false;
float Mn=939.565378;
const float sogliabarrel=0.0001;  //100 keV in MeV
const float sogliastt=250e-6;  //250 eV in MeV
const float barreltimecut=30e-9;  //30 ns
const float timecutcell=10;  // in ns 

int NTOTNeut=0;

TH2F* PosCalZY;
TH2F* PosCalXY;
TH1F* PosCalX;


 TH2D *isto_Edepgbarrel; 
 TH2D *isto_Edepgendcap; 



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

Float_t PosHitX;
Float_t PosHitY;
Float_t PosHitZ;
Float_t PosHitXreco;
Float_t PosHitYreco;
Float_t PosHitZreco;
Float_t timegbarrel; 
Float_t timegendcap;
Float_t timestt;
Float_t TimeHit; 



Int_t vistostt;
Int_t visto;
Int_t vistogbarrel;
Int_t vistogendcap;

Int_t   endcap=0;



void NeutGroupEDepSim() {
	std::cout<<"STARTING NEUT execution "<<std::endl;

	PosCalZY = new TH2F("PosCalZY","PosCalZY",1000,0.,0.,1000,0.,0.); //-5000.0,0.0,1000,21500.0,26500.0);
	PosCalXY = new TH2F("PosCalXY","PosCalXY",1000,0,0,1000,0,0); //-5000.0,0.0,1000,21500.0,26500.0);

	isto_Edepgbarrel=new TH2D("isto_Edepgbarrel","isto_Edepgbarrel",1000,0.0,0.0,100,0.0,0.3e-3);
 	isto_Edepgendcap=new TH2D("isto_Edepgendcap","isto_Edepgendcap",1000,0.0,0.0,100,0.0,0.3e-3);

	char basic[]="../data/sand2020_nocube_sttonly_anumu001_Out.fluka2edep";
	//char basic[]="../data/STT_RHC_CC_001_1e18.4321.edep";
	char nome [150];
	char nome_out [150];

	sprintf (nome, "%s.root",basic);

	sprintf (nome_out, "%s.NeutGroupEDepSim.root",basic);
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
	
	outputTree->Branch("visto",&visto,"visto/I");
	outputTree->Branch("vistostt",&vistostt,"vistostt/I");
	outputTree->Branch("vistogbarrel",&vistogbarrel,"vistogbarrel/I");
    	outputTree->Branch("vistogendcap",&vistogendcap,"vistogendcap/I");

	outputTree->Branch("PosHitX",&PosHitX,"PosHitX/F");
    	outputTree->Branch("PosHitY",&PosHitY,"PosHitY/F");
    	outputTree->Branch("PosHitZ",&PosHitZ,"PosHitZ/F");
	outputTree->Branch("PosHitXreco",&PosHitXreco,"PosHitXreco/F");
    	outputTree->Branch("PosHitYreco",&PosHitYreco,"PosHitYreco/F");
    	outputTree->Branch("PosHitZreco",&PosHitZreco,"PosHitZreco/F");
	outputTree->Branch("timegbarrel",&timegbarrel,"timegbarrel/F");
   	outputTree->Branch("timegendcap",&timegendcap,"timegendcap/F");
   	outputTree->Branch("timestt",&timestt,"timestt/F");
   	outputTree->Branch("TimeHit",&TimeHit,"TimeHit/F");
	outputTree->Branch("endcap",&endcap,"endcap/I");

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

		}else	gEDepSimTree = (TTree*) gFile->Get("EDepSimEvents");

		if (!gEDepSimTree) {
			std::cout << "Missing the event tree" << std::endl;
			return;
		}

		gEDepSimTree->SetBranchAddress("Event",&gEDepSimEvent);




		int N=gEDepSimTree->GetEntries();
		std::cout<<"number of entries "<<N<<std::endl;
		N=10; //FIXME
		for(int i=0; i<N; i++){

			gEDepSimTree->GetEntry(i);
			EDepSimDumpEvent();
		}

	}
	std::cout<<"Sono fuori "<<std::endl;
	outf->cd();		
	isto_Edepgbarrel->Write();
	isto_Edepgendcap->Write();
	PosCalZY->Write();
	PosCalXY->Write();
	outputTree->Write();
	std::cout<<"Ho scritto "<<std::endl;
	delete PosCalZY;
	delete PosCalXY;
	delete isto_Edepgbarrel;
	delete isto_Edepgendcap;

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

	int evento=event->EventId;
	std::cout<<"-----------------------------------------------------------------------------------"<<std::endl;
	std::cout << " " << event->EventId;
	std::cout << " event " << event->EventId<<std::endl;
/*
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
	int Nlost=0;

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
		std::cout<<"Nell'evento ci sono "<<NNneut<<" neutroni "<<std::endl;


		int NTR=-10;
		NumNev=0;
		int NNcount=0; //conta i neutroni in TRAJ
		std::cout << "Analyzing TRAJECTORY "<<std::endl;
		for (std::vector<TG4Trajectory>::iterator
				t = event->Trajectories.begin();
				t != event->Trajectories.end(); ++t) {

			if(t->TrackId<NPrimari) std::cout<<t->TrackId<<std::endl;
		}		



		for (std::vector<TG4Trajectory>::iterator
				t = event->Trajectories.begin();
				t != event->Trajectories.end(); ++t) {

			if(t->ParentId<0 && t->TrackId>NPrimari) std::cout<<"ERROR nella variabile ParentId!!! Track "<<t->TrackId<<"non può essere primario"<<std::endl;
	
			if(t->TrackId>NPrimari) continue;
		//	std::cout<<"Ciclo sulle tracce "<<std::endl;
		
			std::cout << " TrackId " << t->TrackId;
			std::cout << " ParentId " << t->ParentId<<std::endl;
		//	std::cout << " Name " << t->Name<<std::endl;
			
			//int count = t->Points.size();
			//std::cout << " Up to " << count << " points";
			//			std::cout << std::endl;
			int NP=0;
			int ii=0;
			
			if(t->ParentId<0 && (t->TrackId<NPrimari || t->TrackId==NPrimari) && t->PDGCode==2112){
				std::cout<<"NEUTRONE TROVATO "<<std::endl;
				NTR=t->TrackId;
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
					//	std::cout << " TrackId " << p->TrackId<<std::endl;
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

		//cerco i depositi che questo neutrone ha lasciato nel rivelatore
		//
		float Edepgbarrel=9999;
		timegbarrel=9999;
		vistogbarrel=999;
		vistogendcap=999;
	
		//costruisco i vettori di fluka
		//
		int NStt=100000;
		float PosInStt[NStt][3];
		float PosOuStt[NStt][3];
		float EdqStt[NStt];
		int IdStt[NStt];
		int IdParStt[NStt];
		float TimeStt[NStt];

                timestt=9999.9;
                int indicebarrel=9999;
                int indicestt=9999;

                //salvo il primo tempo degli stt e l'indicestt

                float edepgbarrel=9999;
                float xb=9999;
                float yb=9999;
                float zb=9999;
                int indexbarrel=-1;

                float edepgendcap=9999;
                timegendcap=9999;
                float xec=9999;
                float yec=9999;
                float zec=9999;
                int indexendcap=-1;

		vistostt=0;
		float vistostt_time=999;
		float vistostt_energy=999;
		float vistostt_x=999;
		float vistostt_y=999;
		float vistostt_z=999;
		


		int k=0;	
		NP=0;

	
		for (auto d = event->SegmentDetectors.begin();
				d != event->SegmentDetectors.end(); ++d) {
			std::cout << "   det " << d->first;
			int count = d->second.size();
			std::cout << " up to " << count << " segments";
			std::cout << std::endl;

			if(d->first=="EMCalSci"){// "EMCalSci"){  ECAL
				std::cout<<"analizzo ecal "<<std::endl;
				for (std::vector<TG4HitSegment>::iterator
						h = d->second.begin();
						h != d->second.end();
						++h) {
						
						if(h->PrimaryId==NTR){   //cerco gli hit del neutrone o dei figli
							//std::cout<<"primary "<<h->PrimaryId;
							h->Contrib.size();			
							
							IdParStt[k]=h->PrimaryId;
											
							EdqStt[k]=h->EnergyDeposit/1000;
							
							TLorentzVector h_new=GlobalToLocalCoordinates(h->Start);
							TimeStt[k]=h_new.T();
							PosInStt[k][0]=h_new.X();
							PosInStt[k][1]=h_new.Y();
							PosInStt[k][2]=h_new.Z();
							
							TLorentzVector h2_new=GlobalToLocalCoordinates(h->Stop);
							
							PosOuStt[k][0]=h2_new.X();
							PosOuStt[k][1]=h2_new.Y();
							PosOuStt[k][2]=h2_new.Z();
							
							//std::cout<<"contrib[0]"<<h->Contrib[0]<<std::endl;			
							//std::cout<<"energy dep "<<h->EnergyDeposit<<std::endl;
							//std::cout<<"time start "<<h->Start.T()<<std::endl;
							k++;
							if(k>NStt) std:cout<<"ERROR k max >"<<NStt<<std::endl; 	
						}
						if(h->Contrib.size()!=1) std::cout<<"size > 1"<<std::endl; 		

					}//chiude il for di TG4HitSegm
				
			
				NP=k-1;
				std::cout<<"Ci sono "<<NP<<" hit nel calorimetro "<<std::endl;

				if(NP>0){	
		 			Grouped_Barrel_Time(NP, NTR, PosInStt, PosOuStt, IdStt, EdqStt,IdParStt,TimeStt,edepgbarrel, timegbarrel, vistogbarrel, isto_Edepgbarrel, xb, yb, zb, indexbarrel);

                			Grouped_Endcap_Time(NP, NTR, PosInStt, PosOuStt, IdStt, EdqStt,IdParStt,TimeStt,edepgendcap, timegendcap, vistogendcap, isto_Edepgendcap, xec, yec, zec, indexendcap);
				}
			
			std::cout<<"vistogbarrel "<<vistogbarrel<<std::endl;
			std::cout<<"vistogendcap "<<vistogendcap<<std::endl;
		}//chiude if nel calo
				
		if(d->first=="Straw"){ //Straw
				std::cout<<"analizzo straw "<<std::endl;
	
				for (std::vector<TG4HitSegment>::iterator
						h = d->second.begin();
						h != d->second.end();
						++h) {
						if(evento==42) std::cout<<"part in stt "<<h->Contrib.size()<<" "<<h->PrimaryId<<std::endl;	
						if(h->Contrib.size()!=1) std::cout<<"size > 1"<<std::endl; 		
					
						if(h->PrimaryId==NTR){
							//std::cout<<"neutrone trovato con PrimaryId "<<h->PrimaryId<<std::endl;
							std::cout<<"energia dep "<<h->EnergyDeposit<<std::endl;	
							std::cout<<"contrib  "<<h->Contrib[0]<<std::endl;		
									if(h->Contrib.size()>1) std::cout<<" size > 1 !!!!!!!!!!!!!"<<endl;			
							if(h->EnergyDeposit>sogliastt){  //in Mev
								std::cout<<"neutrone visto negli stt "<<std::endl;
								vistostt=1;
								if(vistostt_time>h->Start.T()){
									vistostt_time=h->Start.T();
									vistostt_x=h->Start.X();	
									vistostt_y=h->Start.Y();	
									vistostt_z=h->Start.Z();
									vistostt_energy=h->EnergyDeposit;
																	}
							
							}
						}
					}
					std::cout<<"stt analisi "<<std::endl;
					std::cout<<"visto stt "<<vistostt<<std::endl;
					std::cout<<"timestt "<<vistostt_time<<std::endl;			
					std::cout<<"energy dep "<<vistostt_energy<<std::endl;
					std::cout<<"pos "<<vistostt_x<<" "<<vistostt_y<<" "<<vistostt_z<<std::endl;
					TLorentzVector point(vistostt_x, vistostt_y, vistostt_z, vistostt_time);
					TLorentzVector h_fluka_coord=GlobalToLocalCoordinates(point);
					
					vistostt_time=h_fluka_coord.T();
					vistostt_x=h_fluka_coord.X();	
					vistostt_y=h_fluka_coord.Y();	
					vistostt_z=h_fluka_coord.Z();
		
					std::cout<<"Dopo trasformazione------------ "<<std::endl;
					std::cout<<"visto stt "<<vistostt<<std::endl;
					std::cout<<"timestt "<<vistostt_time<<std::endl;			
					std::cout<<"energy dep "<<vistostt_energy<<std::endl;
					std::cout<<"pos "<<vistostt_x<<" "<<vistostt_y<<" "<<vistostt_z<<std::endl;
						

					
					}//chiude if in stt

			} //chiude il for su  Segm Det


		/////Salvo le variabili confrontando i risultati da ecal e stt	
		timestt=vistostt_time;
		int vistog3dst=0;
		float timeg3dst=1e12;
		int index=9999;
                float tm=999;
                if(vistogbarrel==1 && vistostt==1){
                    if(timegbarrel<timestt ) {tm=timegbarrel; visto=2;index=indexbarrel; }   // il primo hit è nel barrel
                    else if(timestt<timegbarrel) {tm=timestt; visto=1; index=indicestt; }  // il primo hit è negli stt
                } else if (vistogbarrel==1) {tm=timegbarrel; visto=2; index=indexbarrel; }
                else if (vistostt==1) {tm=timestt; visto=1; index=indicestt; }

                if(visto==0 && vistostt==1 && vistogbarrel==1) {tm=timestt; visto=1; index=indicestt; } //succede se i tempi sono uguali
                //considero anche i 3dst
                //
                if(visto==0 && vistog3dst==1) {tm=timeg3dst; visto=4; }
                else if(vistog3dst==1 && tm>timeg3dst) {tm=timeg3dst; visto=4;}

                if(visto==0 && vistogendcap==1) {tm=timegendcap; visto=3; }
                else if(vistogendcap==1 && tm>timegendcap) {tm=timegendcap; visto=3;}

                //cout<<"visto finale e tempo finale "<<visto<<" "<<tm<<endl;
                //uso il grouped
                if(vistostt==0 && vistogbarrel==0 && vistog3dst==0 && vistogendcap==0) {
                    //  cout<<"Neutrone perso "<<endl;
                    visto=0;
                    Nlost++;
                }

		if(visto==3){  //Neutrone visto per primo dal calo
                    PosHitX=xec;//PosCell[indice3dst][0]; //=x;
                    PosHitY=yec; //PosCell[indice3dst][1]; //=y;
                    PosHitZ=zec; //PosCell[indice3dst][2]; //=z;

                    //cout<<"posizioni barrel "<<xb<<" "<<yb<<" "<<zb<<endl;
                    PosHitXreco=PosHitX;
                    PosHitYreco=PosHitY;
                    PosHitZreco=PosHitZ;
                    //if(t_res==1) tm=tm+gaussian_random->Gaus(0,54e-12/(sqrt(edepgbarrel))+50e-12);
                    TimeHit=tm;
                    if(zec>300 || abs(zb)<1e-3 ) {cout<<"ERROR "<<xb<<" "<<yb<<" "<<zb<<endl; return;}

                }else if(visto==2){  //Neutrone visto per primo dal calo
                    PosHitX=xb;//PosCell[indice3dst][0]; //=x;
                    PosHitY=yb; //PosCell[indice3dst][1]; //=y;
                    PosHitZ=zb; //PosCell[indice3dst][2]; //=z;

                    if((PosHitX<-169 || PosHitX>169) && sqrt(PosHitY*PosHitY+PosHitZ*PosHitZ)<200) endcap=1;
                    //cout<<"posizioni barrel "<<xb<<" "<<yb<<" "<<zb<<endl;
                    PosHitXreco=PosHitX;
                    PosHitYreco=PosHitY;
                    PosHitZreco=PosHitZ;
                    //if(t_res==1) tm=tm+gaussian_random->Gaus(0,54e-12/(sqrt(edepgbarrel))+50e-12);
                    TimeHit=tm;
                    if(zb>300 || abs(zb)<1e-3 ) {cout<<"ERROR "<<xb<<" "<<yb<<" "<<zb<<endl; return;}

                }else if(visto==1){ //neutrone visto da stt
                    PosHitX=vistostt_x;
                    PosHitY=vistostt_y;
                    PosHitZ=vistostt_z;

                    PosHitXreco=PosHitX;
		    PosHitYreco=PosHitY;
                    PosHitZreco=PosHitZ;
                    //if(t_res==1) tm=tm+gaussian_random->Gaus(0,2e-9);
                    TimeHit=tm;

                }

		std::cout<<"timestt prima del fill "<<timestt<<std::endl;
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
