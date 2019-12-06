#include"Ideal2RealCal.cpp"
#include"Grouped_3DST.h"
#include"Grouped_Barrel_Time.h"
#include"Grouped_Barrel_Time_Ecal.h"
#include"Grouped_Barrel.h"
#include<TFile.h>
#include<TCanvas.h>
#include<iostream>
#include"TTree.h"
#include<TArc.h>
#include<TLegend.h>
#include <TGraph2D.h>
#include <TMath.h>
#include <cmath>
#include <vector>
#include <cmath>
#include <vector>
#include <math.h>
#include <fstream> 
#include <TRandom3.h>
#include <TChain.h>

using namespace std;
/*
   const double PI  =3.141592653589793238463;
   */
const float Mn=0.9395654133;
const float sogliabarrel=0.0001;
const float soglia3dst=0.0005;
const float barreltimecut=30e-9; //cut hit che arrivano nella cella
const float timecutcell=30e-9;

////////////////////////////////////////////////////////////////////////////

void visto_nei_det(int NStt, int Ntr, int IdParStt[NStt], float PosInStt[NStt][3], float EdqStt[NStt], float TimeStt[NStt], int &vistostt, int &vistobarrel, float &edepbarrel, float &edepstt, float &timebarrel, float &timestt,int &indicebarrel, int &indicestt, TH1D* isto_Edepbarrel, TH1D* isto_Edepstt){

	//prendo sempre edep del primo hit visto nel calo e nell'stt
	//edep è edepositata da tutti i neutroni o figli nel rivelatore

	bool stt=false;
	bool calo=false;

	float EdepMAXbarrel=0;
	float EdepMAXstt=0; 

	vistobarrel=0;
	vistostt=0;

	edepbarrel=0;
	edepstt=0;

	for(int i=0; i<NStt; i++){
		if(IdParStt[i]==Ntr){
			float R=sqrt(PosInStt[i][1]*PosInStt[i][1]+PosInStt[i][2]*PosInStt[i][2]);
			if(R>200 && R<225){
				if(EdepMAXbarrel<EdqStt[i]) EdepMAXbarrel=EdqStt[i];
				edepbarrel+=EdqStt[i];

				isto_Edepbarrel->Fill(EdqStt[i]);					
				if(EdqStt[i]>sogliabarrel) {
					vistobarrel=1; 
					//isto_Edepbarrel->Fill(EdqStt[i]);
					if(calo==false) {//edepbarrel=EdqStt[i]; 
						timebarrel=TimeStt[i]; indicebarrel=i; calo=true;
					}
				}	
			}else if(R<200 && PosInStt[i][0]> -169 && PosInStt[i][0]< 169){
				//isto_Edepstt->Fill(EdqStt[i]);
				if(EdepMAXstt<EdqStt[i]) EdepMAXstt=EdqStt[i];
				edepstt+=EdqStt[i];				
				//if(EdqStt[i]>0.000000250 ) {
					vistostt=1; 
					if(stt==false){ //edepstt=EdqStt[i]; 
						timestt=TimeStt[i]; indicestt=i; stt=true;  //prendo il primo hit che ha tempo minimo
						isto_Edepstt->Fill(timestt);	
					} 
					//isto_Edepstt->Fill(EdqStt[i]);
					//if(calo==true && stt==true) break; 
				//}
			}
		}
	}

	//	 isto_Edepbarrel->Fill(EdepMAXbarrel);
	//	 isto_Edepstt->Fill(EdepMAXstt);


}


void visto_3dst(int NCells, int Ntr, int* IdParCell, float PosCell[100000][3], float *EdepQCell, float *TimeCell, int &visto3dst, float &time3dst, float &edep3dst, int &indice3dst, TH1D *isto_Edep3dst){

	bool bool3dst=false;
	edep3dst=0;
	for(int i=0; i<NCells; i++){
		if(IdParCell[i]==Ntr){
			// cout<<"Coordinate "<<PosCell[i][0]<<" "<<PosCell[i][1]<<" "<<PosCell[i][2]<<endl;
			isto_Edep3dst->Fill(EdepQCell[i]);
			edep3dst+=EdepQCell[i];
			if(bool3dst==false && EdepQCell[i]>soglia3dst) {  //soglia 0.5 MeV
				time3dst=TimeCell[i];
				visto3dst=1;
				//	edep3dst=EdepQCell[i];
				indice3dst=i;
				bool3dst=true;
			}
		}
	}

}


double Phi_function(double yloc, double xloc){

	double fi;
	if(yloc==0 && xloc==0) fi=0;
	else if(xloc==0 && yloc>0) fi=M_PI/2;
	else if(xloc==0 && yloc<0) fi=3*M_PI/2;
	else {fi=atan(yloc/xloc);
		if(fi>0 && yloc<0) fi=fi+M_PI;
		if(fi<0 && yloc>0) fi=fi+M_PI;
		if(fi<0 && yloc<0) fi=fi+2*M_PI;
		if(fi==0 && xloc<0) fi=M_PI;
	}

	if(fi>2*M_PI) std::cout<<"ERROR on phi: yloc "<<yloc<<" "<<xloc<<std::endl;
	return fi;
}





//int main(){
void Neutron_3DST(){
	cout<<"INIZIO "<<endl;


	TRandom3 *gaussian_random = new TRandom3();
	TRandom3 *uniform_random = new TRandom3();
	TRandom3 *uniformt_random = new TRandom3();


	Float_t betaavg_cell;
	Float_t betatmin_cell=3;
	Float_t betabest_cell=3;
	Float_t betastt_cell=3;

	Float_t betafigli_cal_reco;
	Float_t betaN_vertex;
	Float_t betaN_cal_true=3;
	Float_t beta_reco; 
	Float_t beta_stt;


	Float_t Edepfigli_stt;
	Float_t EdepN_calo;
	Float_t EdepN_stt;
	Float_t Edepfigli_calo;

	Float_t Pneut_vertex;
	Float_t Eneut_vertex;
	Float_t Phit_neut;
	Float_t PosHitX;
	Float_t PosHitY;
	Float_t PosHitZ;
	Float_t PosHitXreco;
	Float_t PosHitYreco;
	Float_t PosHitZreco;

	Float_t Time_tof_cal;
	Float_t Time_tof_stt;
	Float_t Time_neut_hit; 
	Float_t dist_tof_cal;
	Float_t dist_tof_stt;
	Float_t dist_neut_hit;
	Float_t ENcell;
	Float_t Eothercell;
	Float_t angle_reco;
	Float_t angle_true;
	Float_t angle_reco_nudir;
	Float_t angle_true_nudir;
	Float_t NKinetic;
	Float_t P_reco;  
	Float_t Eneutrino_reco;
	Float_t Pmu;

	Float_t Eneutrino_true;

	Float_t Vertex_x;
	Float_t Vertex_y;
	Float_t Vertex_z;




	Float_t Vertex_xreco;
	Float_t Vertex_yreco;
	Float_t Vertex_zreco;

	Bool_t endcap;
	Bool_t onlyneutcal;
	Bool_t onlyfiglical;
	Bool_t neut_e_figli_cal;

	Int_t Ncell=0;
	Int_t Nneut_stt;
	Int_t Nfigli_stt;

	Int_t cstt;
	Int_t Nneut_cal;
	Int_t Ncell_soprasoglia=0;

	Int_t NhitCalT;
	Int_t Evnum;
	Int_t PlanT;
	Int_t Nfigli_cal;
	Int_t interazione;

	Int_t Id_tof_tmin;
	Int_t Id_tof_best;
	Int_t I_cella_best=9999;
	Int_t I_cella_tmin=9999;
	Int_t Nok;
	Int_t ncellg3dst=9999;

	Float_t barx3dst=9999.9;
	Float_t bary3dst=9999.9;
	Float_t barz3dst=9999.9;

	Bool_t figlical_int;
	Bool_t Ncal_int;
	Bool_t figlicalbordo_int;
	Bool_t interazionecal;

	Bool_t primohitcal;
	Bool_t primohitN;

	Int_t visto;  //vale 0 se non è visto, vale 1 se visto nell'STT, vale 2 se visto nel calo, vale 3 se visto nel catcher
	Int_t Nadroni;
	Bool_t Figlio;
	Int_t inttype;
	Int_t ncellgbarrel=999;

	Float_t barxbarrel=9999.9;
	Float_t barybarrel=9999.9;
	Float_t barzbarrel=9999.9;
	Float_t sigbarrel=9999.9;

	Int_t vistostt;
	Int_t vistobarrel;
	Int_t visto3dst;
	Int_t vistog3dst;
	Int_t vistogbarrel;

	Float_t Ereco_neutrino_from_angle;
	Float_t angle_reco_muon_neutrino;  
	Float_t EKneut_from_angle;
	Float_t EKneut_reco;
	Float_t E_neutrino;
	Float_t E_neutrone;

	Float_t edepbarrel=9999;
	Float_t edep3dst=9999;
	Float_t edepstt=9999;
	Float_t dist;
	Float_t Timeg3dst=9999;
	Float_t edepg3dst=99999; 
	Float_t sig3dst=9999.9;
	Float_t timegbarrel=9999;
	Float_t timestt=9999;


	TTree *outputTree=new TTree("mioTree","mioTree");
	/*
	   outputTree->Branch("Nneut_stt",&Nneut_stt,"Nneut_stt/I");
	   outputTree->Branch("Nneut_cal",&Nneut_cal,"Nneut_cal/I");
	   outputTree->Branch("Nfigli_stt",&Nfigli_stt,"Nfigli_stt/I");
	   outputTree->Branch("Nfigli_cal",&Nfigli_cal,"Nfigli_cal/I");
	   outputTree->Branch("EdepN_calo",&EdepN_calo,"EdepN_calo/F");
	   outputTree->Branch("EdepN_stt",&EdepN_stt,"EdepN_stt/F");
	   outputTree->Branch("Edepfigli_calo",&Edepfigli_calo,"Edepfigli_calo/F");
	   outputTree->Branch("Edepfigli_stt",&Edepfigli_stt,"Edepfigli_stt/F");

	   outputTree->Branch("primohitcal",&primohitcal,"primohitcal/B");
	   outputTree->Branch("primohitN",&primohitN,"primohitN/B");
	   */
	outputTree->Branch("Evnum",&Evnum,"Evnum/I");
	outputTree->Branch("Pneut_vertex",&Pneut_vertex,"Pneut_vertex/F");
	outputTree->Branch("NKinetic",&NKinetic,"NKinetic/F");

	outputTree->Branch("betaN_vertex",&betaN_vertex,"betaN_vertex/F");
	outputTree->Branch("beta_reco",&beta_reco,"beta_reco/F");
	
	outputTree->Branch("angle_reco",&angle_reco,"angle_reco/F");
	outputTree->Branch("visto",&visto,"visto/I");
	outputTree->Branch("vistostt",&vistostt,"vistostt/I");
	outputTree->Branch("vistobarrel",&vistobarrel,"vistobarrel/I");
	outputTree->Branch("visto3dst",&visto3dst,"visto3dst/I");
	outputTree->Branch("vistog3dst",&vistog3dst,"vistog3dst/I");
	outputTree->Branch("vistogbarrel",&vistogbarrel,"vistogbarrel/I");
	outputTree->Branch("ncellg3dst",&ncellg3dst,"ncellg3dstl/I");
	outputTree->Branch("barx3dst",&barx3dst,"barx3dst/F");
	outputTree->Branch("bary3dst",&bary3dst,"bary3dst/F");
	outputTree->Branch("barz3dst",&barz3dst,"barz3dst/F");

	outputTree->Branch("ncellgbarrel",&ncellgbarrel,"ncellg3barrel/I");
	outputTree->Branch("barxbarrel",&barxbarrel,"barxbarrel/F");
	outputTree->Branch("barybarrel",&barybarrel,"barybarrel/F");
	outputTree->Branch("barzbarrel",&barzbarrel,"barzbarrel/F");

	outputTree->Branch("inttype",&inttype,"inttype/I");
	outputTree->Branch("Figlio",&Figlio,"Figlio/b");
	//  outputTree->Branch("angle_reco_nudir",&angle_reco_nudir,"angle_reco_nudir/F");
	//  outputTree->Branch("angle_reco_muon_neutrino",&angle_reco_muon_neutrino,"angle_reco_muon_neutrino/F");

	outputTree->Branch("angle_true",&angle_true,"angle_true/F");
	outputTree->Branch("edep3dst",&edep3dst,"edep3dst/F");
	outputTree->Branch("edepg3dst",&edepg3dst,"edepg3dst/F");
	outputTree->Branch("edepbarrel",&edepbarrel,"edepbarrel/F");
	outputTree->Branch("edepstt",&edepstt,"edepstt/F");
	outputTree->Branch("dist",&dist,"dist/F");
	outputTree->Branch("sig3dst",&sig3dst,"sig3dst/F");

	outputTree->Branch("PosHitX",&PosHitX,"PosHitX/F");
	outputTree->Branch("PosHitY",&PosHitY,"PosHitY/F");
	outputTree->Branch("PosHitZ",&PosHitZ,"PosHitZ/F");

	outputTree->Branch("PosHitXreco",&PosHitXreco,"PosHitXreco/F");
	outputTree->Branch("PosHitYreco",&PosHitYreco,"PosHitYreco/F");
	outputTree->Branch("PosHitZreco",&PosHitZreco,"PosHitZreco/F");

	outputTree->Branch("Vertex_x",&Vertex_x,"Vertex_x/F");
	outputTree->Branch("Vertex_y",&Vertex_y,"Vertex_y/F");
	outputTree->Branch("Vertex_z",&Vertex_z,"Vertex_z/F");

	outputTree->Branch("Vertex_xreco",&Vertex_xreco,"Vertex_xreco/F");
	outputTree->Branch("Vertex_yreco",&Vertex_yreco,"Vertex_yreco/F");
	outputTree->Branch("Vertex_zreco",&Vertex_zreco,"Vertex_zreco/F");
	outputTree->Branch("timegbarrel",&timegbarrel,"timegbarrel/F");
	outputTree->Branch("timestt",&timestt,"timestt/F");


	outputTree->Branch("E_neutrino",&E_neutrino,"E_neutrino/F");
	outputTree->Branch("E_neutrone",&E_neutrone,"E_neutrone/F");

	/*	   outputTree->Branch("Eothercell",&Eothercell,"Eothercell/F");

		   outputTree->Branch("Phit_neut",&Phit_neut,"Phit_neut/F");
		   outputTree->Branch("Time_tof_cal",&Time_tof_cal,"Time_tof_cal/F");
		   outputTree->Branch("Time_tof_stt",&Time_tof_stt,"Time_tof_stt/F");
		   outputTree->Branch("Time_neut_hit",&Time_neut_hit,"Time_neut_hit/F");

		   outputTree->Branch("Nok",&Nok,"Nok/I");
		   outputTree->Branch("betaavg_cell",&betaavg_cell,"betaavg_cell/F");

		   outputTree->Branch("Id_tof_best",&Id_tof_best,"Id_tof_best/I");
		   outputTree->Branch("Id_tof_tmin",&Id_tof_tmin,"Id_tof_tmin/I");

		   outputTree->Branch("dist_tof_cal",&dist_tof_cal,"dist_tof_cal/F");
		   outputTree->Branch("dist_tof_stt",&dist_tof_stt,"dist_tof_stt/F");
		   outputTree->Branch("dist_neut_hit",&dist_neut_hit,"dist_neut_hit/F");

*/
	/*
	   outputTree->Branch("Ereco",&Ereco,"Ereco/F");
	   outputTree->Branch("Etrue",&Etrue,"Etrue/F");
	   outputTree=new TTree("mioTree","mioTree");

	   outputTree->Branch("Ncell",&Ncell,"Ncell/I");
	   outputTree->Branch("EveNumT",&EveNumT,"EveNumT/I");
	   */
	// outputTree->Branch("PlanT",&PlanT,"PlanT/I");
	// outputTree->Branch("ZT",&ZT,"ZT/F");

	TH1D *isto_Edepstt=new TH1D("isto_Edepstt","isto_Edepstt",1000,0,0.);
	TH1D *isto_Edep3dst=new TH1D("isto_Edep3dst","isto_Edep3dst",400,0,0.02);
	TH1D *isto_Edepbarrel=new TH1D("isto_Edepbarrel","isto_Edepbarrel",400,0,0.02);
	TH1D *isto_Edepg3dst=new TH1D("isto_Edepg3dst","isto_Edepg3dst",400,0.,0.);
	TH2D *isto_Edepgbarrel=new TH2D("isto_Edepgbarrel","isto_Edepgbarrel",100,0,100e-9,100,0.00008,0.01);
	//	TH1D *isto_Edepgbarrel=new TH1D("isto_Edepgbarrel","isto_Edepgbarrel",1000,0,0.);
	// TH1F* isto_N_Yposition=new TH1F("isto_N_Yposition","isto_N_Yposition",100,-1,1);
	//TH1F* isto_Yhits=new TH1F("isto_hits","isto_Yhits",500,-250,250);
	TH1D *isto_p=new TH1D("isto_p","isto_p",10000,0,3);
	TH1D *isto_pq=new TH1D("isto_pq","isto_pq",10000,0,3);
	//  TH2D *istobetaneut=new TH2D("Istobetaneut","istobetaneut",100,0,1,100,0,1);
	//  TH2D *istobetacalo=new TH2D("Istobetacalo","istobetacalo",100,0,1,100,0,1);
	TH2D *isto_ris_stt=new TH2D("isto_res_stt","isto_res_stt",30,0.5,1.5,50,-1.5,1.5);
	TH2D *isto_ris_calbarrel=new TH2D("isto_res_calbarrel","isto_res_calbarrel",30,0.5,1.5,50,-1.5,1.5);
	TH2D *isto_ris_calendcap=new TH2D("isto_res_calendcap","isto_res_calendcap",30,0.5,1.5,50,-1.5,1.5);


	int NneutTot=0;
	int Ncount=0;
	int Ncal=0;
	int Nstt=0;
	int neutcal=0;
	int neutfigli=0;
	int Nneut_e_figli_cal=0;
	int neutendcap=0;
	int cal=0;
	int csoprasoglia=0;  


	//leggo il file list e ciclo su ogni file

	char prova[100];
	char basic_name[1000]; 
	char *basic_name0;

	//ifstream myfile("Fede.list");	//interazioni in LAr meniscus sono 63 
	//ifstream myfile("Paola_cubes.list"); //sono 5
	//ifstream myfile("Paola_stt_RH_forC.list");//sono 51	
	ifstream myfile("Paola_stt_RH_All.list");//sono 40 o 71 per H
	string g, g2;

	float Xv, Yv, Zv;
	float* hitz;
	float* hity;
	int npunti_idpar=0;
	int Neventi=0;
	int Neventi_visti=0;


	for(int l=0; l<40; l++){ 
		myfile>>g;
		cout<<"Leggo il file "<<l<<" "<<g<<endl;
		const char *run_name=g.c_str();
		// sprintf(run_name,"%s",run);
		TChain *mytree=new TChain("HeaderTree");
		TChain *CellTree=new TChain("CellTree");
		TChain *SttTree=new TChain("SttTree");

		mytree->Add(run_name);
		SttTree->Add(run_name);
		CellTree->Add(run_name);

		//abilito le Branch che mi servono
		//---Branch di HeaderTree
		int NLep=0;
		// int NPhot=0;
		int NHad=0;
		int NTracks=0;  
		int IdLep[100000];
		int IdHad[100000];
		float Vertex[3];
		int TrHad[1000];
		int TrLep[1000];
		float P_Had[1000][5];
		// int NHeavy=0;
		// float P_Heavy[1000][5];
		float P_Lep[1000][5];
		// float P_Phot[1000][5];
		float P_Primary[5];
		int TargZ=0;
		int TargA=0;
		int IntType;
		int evnum;

		mytree->SetBranchAddress("NumLep",&NLep);
		mytree->SetBranchAddress("EveNum",&evnum);
		//mytree->SetBranchAddress("NumPhot",&NPhot);
		//mytree->SetBranchAddress("NumHeavy",&NHeavy);
		mytree->SetBranchAddress("NumHad",&NHad);
		mytree->SetBranchAddress("IdHad",IdHad);
		mytree->SetBranchAddress("TrHad",TrHad);
		mytree->SetBranchAddress("IdLep",IdLep);
		mytree->SetBranchAddress("NumTracks",&NTracks);
		mytree->SetBranchAddress("Vertex",Vertex);
		mytree->SetBranchAddress("TrLep",TrLep);
		mytree->SetBranchAddress("P_Had",P_Had);
		mytree->SetBranchAddress("P_Lep",P_Lep);
		//mytree->SetBranchAddress("P_Phot",P_Phot);
		//mytree->SetBranchAddress("P_Heavy",P_Heavy);
		mytree->SetBranchAddress("P_Primary",P_Primary);
		mytree->SetBranchAddress("TargZ",&TargZ);
		mytree->SetBranchAddress("TargA",&TargA);
		mytree->SetBranchAddress("IntType",&IntType);



		//-----aBranch di SttTree-----------
		int NStt=0;  
		int NSTTMAX=100000;
		float PosInStt[100000][3];
		float PosOuStt[100000][3];
		float TimeStt[100000];
		float PStt[100000][5];

		int RegStt[100000]; //è lungo come NStt e può assumere tanti valori
		int TrStt[100000];
		int IdStt[100000];
		int IdParStt[100000];
		float EdepStt[100000];
		float EdqStt[100000];

		mytree->SetBranchAddress("NStt",&NStt);

		mytree->SetBranchAddress("PosInStt",PosInStt);
		mytree->SetBranchAddress("PosOuStt",PosOuStt);
		mytree->SetBranchAddress("TimeStt",TimeStt);

		mytree->SetBranchAddress("RegStt",RegStt);
		mytree->SetBranchAddress("TrStt",TrStt);
		mytree->SetBranchAddress("IdStt",IdStt);
		mytree->SetBranchAddress("IdParStt",IdParStt);
		mytree->SetBranchAddress("EdepStt",EdepStt);
		mytree->SetBranchAddress("EdqStt",EdqStt);
		mytree->SetBranchAddress("PStt",PStt);

		/*	
		//------Branch di CalTree
		int NCal=0;  
		float PosCal[500][3];
		float TimeCal[500][3];
		float EdepCal[500][2];

		mytree->SetBranchAddress("NCal",&NCal);
		mytree->SetBranchAddress("PosCal",PosCal);
		mytree->SetBranchAddress("TimeCal",TimeCal);
		mytree->SetBranchAddress("EdepCal",EdepCal);
		*/

		int NCells=0;  
		float PosCell[10000][3];
		float TimeCell[10000];
		float EdepQCell[10000];
		int IdParCell[10000];

		mytree->SetBranchAddress("NCells",&NCells);
		mytree->SetBranchAddress("PosCell",PosCell);
		mytree->SetBranchAddress("TimeCell",TimeCell);
		mytree->SetBranchAddress("EdepQCell",EdepQCell);
		mytree->SetBranchAddress("IdParCell",IdParCell);


		//-------------------------------------------------
		int N=mytree->GetEntries();
		//cout<<"N Entries: "<<N<<endl;

		//CONSIDERO SOLO l'evento EV
		for(int K=0; K<N; K++){ 
			//cout<<"K "<<K<<endl;
			mytree->GetEntry(K);

			//cout<<"--------- INFO GENERALI--------  "<<endl;
			cout<<"Numero Evento            : "<<evnum<<endl;
			Evnum=evnum;
			// cout<<"Numero di Leptoni        : "<<NLep<<endl;
			// cout<<"Numero di Adroni         : "<<NHad<<endl;
			// cout<<"Numero di Fotoni         : "<<NPhot<<endl;

			//if(TargZ!=1 || TargA!=1 ) continue;  //seleziono solo le interazioni su Idrogeno per Petti
			//if(TargZ!=6 || TargA!=12 ) continue;  //seleziono solo le interazioni su Carbonio per Petti

			/*
			   for(int i=0; i<NStt; i++){
			   isto_pq->Fill(EdqStt[i]);
			   isto_p->Fill(EdepStt[i]);
			   }
			   */
			E_neutrino=P_Primary[3];
			int Nneut=0;
			for(int kk=0; kk<NHad; kk++){
				if(IdHad[kk]==2112) Nneut++;
			} 


			int Ntr=0;
			int ii=0;
			int IdParNeut=0; //salvo IdParStt del neutrone padre
			bool found=false;
			float Pn[3];


			for(int jj=0; jj<Nneut; jj++){  // apro il ciclo su tutti i neutroni dell'evento
				while(ii<NHad && found==false){
					//        cout<<ii<<endl;
					if(IdHad[ii]==2112){  // cerco il neutrone
						Ntr=TrHad[ii];
						Eneut_vertex=P_Had[ii][3];
						Pneut_vertex=P_Had[ii][4];
						NKinetic=Eneut_vertex-Mn;
						betaN_vertex=Pneut_vertex/Eneut_vertex;
						found=true;
						//        cout<<"i preso "<<ii<<endl;
						//Pn[0]=P_Had[0][0];
						//Pn[1]=P_Had[0][1];
						//Pn[2]=P_Had[0][2];
						E_neutrone=P_Had[ii][3];
					}
					ii++;
				} 
				found=false;
				//cout<<"Devo considerare la traccia "<<Ntr<<endl;


				//if(IdHad[0]!=2112 && IdLep[0]!=-13) continue;
				visto=0; //di default non viene visto
				vistostt=0;
				vistobarrel=0;
				visto3dst=0;
				vistog3dst=0;
				edepstt=9999;
				edepbarrel=9999;
				edep3dst=9999;

				inttype=IntType;
				//  cout<<"NUOVO EVENTO su H :-------------------------------------------------- "<<endl; 
				//  cout<<"EveNum : "<<evnum<<"--------------------------------------------------"<<endl;


				/*
				   float Energy_neutron=0;
				   float P_neutron=0;


				//salvo la traccia del neutrone in Ntr
				int Ntr=0;
				int ii=0;
				int IdParNeut=0; //salvo IdParStt del neutrone padre
				float PxN;
				float PyN;
				float PzN;

				float Pl[5];


				Ntr=TrHad[0];
				Eneut_vertex=P_Had[0][3];
				Pneut_vertex=P_Had[0][4];

				Pn[0]=P_Had[0][0];
				Pn[1]=P_Had[0][1];
				Pn[2]=P_Had[0][2];

				betaN_vertex=Pneut_vertex/Eneut_vertex; 
				NKinetic=Eneut_vertex-0.9395654;


				int Ntr_Lep=0;
				Ntr_Lep=TrLep[0];
				Pl[0]=P_Lep[0][0];
				Pl[1]=P_Lep[0][1];
				Pl[2]=P_Lep[0][2];
				Pl[3]=P_Lep[0][3];
				Pl[4]=P_Lep[0][4];
				*/
				//cout<<"Traccia del muone+ "<<Ntr_Lep<<endl;
				//cout<<"Traccia del neutrone "<<Ntr<<endl;


				//vertice
				float sigma=(7.21/sqrt(12))/10; //in cm
				float dz=gaussian_random->Gaus(0,sigma);

				Xv=Vertex[0];
				Yv=Vertex[1];
				Zv=Vertex[2]+dz;

				//inizializzo le variabili del tree
				beta_reco=3;
				betatmin_cell=3;
				beta_stt=3;

				betastt_cell=3;
				PosHitX=999;
				PosHitY=999; 
				PosHitZ=999;
				I_cella_tmin=999;
				I_cella_best=999;
				Ncell_soprasoglia=0;
				Ncell=0;        
				P_reco=9999;
				angle_reco=9999;
				angle_reco_nudir=9999;
				npunti_idpar=0;

				bool endcap=false;
				//se ho hit del neutrone o dei figli nell'endcap passo all'evento successivo 
				for(int i=0; i<NStt; i++){
					if(IdParStt[i]==Ntr) npunti_idpar++;
					double Rad=sqrt(PosInStt[i][1]*PosInStt[i][1]+PosInStt[i][2]*PosInStt[i][2]);
					if((PosInStt[i][0]< -169 || PosInStt[i][0]> 169)  && IdParStt[i]==Ntr){  //endcap punti del neutrone o dei figli nell'endcap
						endcap=true;
					}
				}
				if(endcap==1){
					//cout<<"--ENDCAP CUT-----------------"<<endl;
					//visto=5;
					//outputTree->Fill();
					continue; 
				}
				/////////////////////////////////////////////////////////////////////
				//check casino in lettura di EdqStt
				bool errorvar=false;
				for(int i=0; i<NStt; i++){
					if(IdParStt[i]==Ntr) {
						if(EdqStt[i]>1) {cout<<"ERROR VISTO PRIMA------------------------------------------------: "<<EdqStt[i]<<" "<<EdepStt[i]<<" "<<i<<endl; errorvar=true; }

					}
				}

				if(errorvar==true) continue; //casino
				//////////////////////////////////////////////////////////////////
				Neventi++;

				float timebarrel=9999.9;
				timestt=9999.9;
				int indicebarrel=9999;
				int indicestt=9999;

				//salvo il primo tempo degli stt e l'indicestt
				visto_nei_det(NStt, Ntr, IdParStt, PosInStt, EdqStt, TimeStt, vistostt, vistobarrel, edepbarrel, edepstt, timebarrel, timestt, indicebarrel, indicestt, isto_Edepbarrel, isto_Edepstt); 

				if(timestt>timecutcell) {vistostt=0; timestt=9999.9;}                               

                          //      cout<<"timestt "<<timestt<<" pos "<<PosInStt[indicestt][0]<<" "<<PosInStt[indicestt][1]<<" "<<PosInStt[indicestt][2]<<endl;
				//if(index==-99 && (vistobarrel==1 || vistostt==1)) {cout<<"ERRORE SU VISTO vistostt, vistobarrel" <<vistostt<<" "<<vistobarrel<<endl; return;}

				//cout<<"vistobarrel "<<vistobarrel<<endl;
				//cout<<"time "<<timebarrel<<" "<<timestt<<endl;

				float edepgbarrel=9999;
				timegbarrel=9999;
				float xb=9999;
				float yb=9999;
				float zb=9999;

				//Grouped_Barrel_Time(NStt, Ntr, PosInStt, PosOuStt, IdStt, EdqStt,IdParStt, TimeStt, edepgbarrel, timegbarrel, vistogbarrel, isto_Edepgbarrel, xb, yb, zb, ncellgbarrel, barxbarrel, barybarrel, barzbarrel, sigbarrel);
				//	Grouped_Barrel(NStt, Ntr, PosInStt, PosOuStt, IdStt, EdqStt,IdParStt, TimeStt,edepgbarrel, timegbarrel, vistogbarrel, isto_Edepgbarrel, xb, yb, zb);
				Grouped_Barrel_Time(NStt, Ntr, PosInStt, PosOuStt, IdStt, EdqStt,IdParStt, TimeStt,edepgbarrel, timegbarrel, vistogbarrel, isto_Edepgbarrel, xb, yb, zb);
				
			//	cout<<"timegbarrel "<<timegbarrel<<" pos "<<xb<<" "<<yb<<" "<<zb<<endl;
				
				//salvo il primo tempo del barrel in timegbarrel e la posizione del primo hit
				//Grouped_Barrel_Time_Ecal(NStt, Ntr, PosInStt, PosOuStt, IdStt, EdqStt,IdParStt, TimeStt,edepgbarrel, timegbarrel, vistogbarrel, isto_Edepgbarrel, xb, yb, zb);


				float time3dst=9999;
				int indice3dst=9999; 
				visto_3dst(NCells,Ntr, IdParCell,PosCell,EdepQCell,TimeCell,visto3dst, time3dst, edep3dst, indice3dst, isto_Edep3dst);
				//cout<<"edep3dst "<<edep3dst<<" "<<visto3dst<<endl;

				float timeg3dst=9999;
				float x=9999;
				float y=9999;
				float z=9999;

				//salvo il primo tempo del 3DST timeg3dst e le coordinate del primo hit
				Grouped_3DST(NCells, Ntr, IdParCell, PosCell, EdepQCell, TimeCell, edepg3dst, timeg3dst, vistog3dst, isto_Edepg3dst ,x,y,z, ncellg3dst, barx3dst, bary3dst, barz3dst,sig3dst ); 
				//cout<<"edepg3dst "<<edepg3dst<<" "<<vistog3dst<<endl;	

				//uso il grouped			
				if(vistostt==0 && vistogbarrel==0) {   //non considero i 3dst
					//cout<<"Neutrone perso "<<endl;
					visto=0;
					outputTree->Fill();
					continue;
				}
				//cout<<"Neutrone visto 3dst, stt, barrel "<<vistog3dst<<" "<<vistostt<<" "<<vistogbarrel<<endl;
				Neventi_visti++;

				int index=9999;
				float tm=999;
				if(vistogbarrel==1 && vistostt==1){
					if(timegbarrel<timestt ) {tm=timegbarrel; visto=2;}   // il primo hit è nel barrel
					else if(timestt<timegbarrel) {tm=timestt; visto=1; index=indicestt;}  // il primo hit è negli stt
				} else if (vistogbarrel==1) {tm=timegbarrel; visto=2;}
				else if (vistostt==1) {tm=timegbarrel; visto=1;}

				if(visto==0 && vistostt==1 && vistobarrel==1) {tm=timestt; visto=1; index=indicestt;} //succede se i tempi sono uguali
				//qui visto è 2 o 1
			if(vistog3dst==1 && (timeg3dst<tm || (vistostt==0 && vistogbarrel==0))) {tm=timeg3dst; visto=3;} //il primo hit è nei 3DST
			//cout<<"visto in "<<visto<<endl;			

			if(visto==3) {  //neutrone visto per primo da 3dst 
				PosHitX=x;//PosCell[indice3dst][0]; //=x;
				PosHitY=y; //PosCell[indice3dst][1]; //=y;
				PosHitZ=z; //PosCell[indice3dst][2]; //=z;

				PosHitXreco=PosHitX;
				PosHitYreco=PosHitY;
				PosHitZreco=PosHitZ;

				//	Figlio=1;
				//	if(TrStt[indice3dst]==Ntr) Figlio=0; 

			}else if(visto==2){  //Neutrone visto per primo dal calo
				PosHitX=xb;//PosCell[indice3dst][0]; //=x;
				PosHitY=yb; //PosCell[indice3dst][1]; //=y;
				PosHitZ=zb; //PosCell[indice3dst][2]; //=z;

				//cout<<"posizioni barrel "<<xb<<" "<<yb<<" "<<zb<<endl;
				PosHitXreco=PosHitX;
				PosHitYreco=PosHitY;
				PosHitZreco=PosHitZ;
				if(zb>300 || abs(zb)<1e-3 ) {cout<<"Errori "<<xb<<" "<<yb<<" "<<zb<<endl; return;}

			}else if(visto==1){ //neutrone visto da stt
				PosHitX=PosInStt[index][0];
				PosHitY=PosInStt[index][1];
				PosHitZ=PosInStt[index][2];

				PosHitXreco=PosHitX;
				PosHitYreco=PosHitY;
				PosHitZreco=PosHitZ;
				//	Figlio=1;
				//	if(TrStt[index]==Ntr) Figlio=0; 

			}
			if(visto3dst==1 && vistog3dst==0){ cout<<"ERROR ON VISTO "<<endl; return; }

			//distanza interazione vertice punto di rivelazione (non inclusa la risoluzione)
			dist=sqrt((PosHitX-Xv)*(PosHitX-Xv)+(PosHitY-Yv)*(PosHitY-Yv)+(PosHitZ-Zv)*(PosHitZ-Zv));

			beta_reco=dist/100./(tm)/3e8;			

/*
			if(visto==2){  //applico lo smearing nella ricostruz per evento nel calorimetro nel barrel
				float dR1=uniform_random->Uniform(0,4)-2; //in cm //tra -2 e +2 cm
				float dR2=uniform_random->Uniform(0,4)-2; //in cm //tra -2 e +2 cm
				float dt=uniformt_random->Uniform(0,2*M_PI/288)-M_PI/288; //angolo dei settori di KLOE (288=24*12)

				float RR=sqrt(PosHitY*PosHitY+PosHitZ*PosHitZ);
				float alpha=Phi_function(PosHitY,PosHitZ); //calcolo angolo rispetto all'orizzontale

				float cosa=TMath::Cos(alpha);
				float sina=TMath::Sin(alpha);

				PosHitXreco=PosInStt[index][0];
				PosHitYreco=PosInStt[index][1]+dR1;//*cosa-RR*dt*sina;
				PosHitZreco=PosInStt[index][2]+dR2;//*sina+RR*dt*cosa; //-RR*dt*sina;
			}
*/
			//if(visto==3){  //smearing in x se sono negli endcap

			//PosHitXreco=PosInStt[index][0]+uniform_random->Uniform(0,4)-2;
			//PosHitYreco=PosInStt[index][1];
			//PosHitZreco=PosInStt[index][2]; 
			//}

			float ModN=sqrt((PosHitXreco-Xv)*(PosHitXreco-Xv)+(PosHitYreco-Yv)*(PosHitYreco-Yv)+(PosHitZreco-Zv)*(PosHitZreco-Zv));
			//angolo rispetto all'orizzontale
			angle_reco=acos(((PosHitXreco-Xv)*0+(PosHitYreco-Yv)*0+(PosHitZreco-Zv)*1)/(ModN));
			/*if((PosHitYreco-Yv)<0) { if(angle_reco<5*2*M_PI/360)  angle_reco_nudir=-angle_reco+5*2*M_PI/360;
			  else angle_reco_nudir=angle_reco-5*2*M_PI/360;
			  }
			  else angle_reco_nudir=angle_reco+5*2*M_PI/360;
			  */
			

			float ModPHad=sqrt(Pn[0]*Pn[0]+Pn[1]*Pn[1]+Pn[2]*Pn[2]);
			angle_true=acos(Pn[0]*0+Pn[1]*0+Pn[2]*1/(ModPHad));
			/*if(Pn[2]<0) {if(angle_reco<5*2*M_PI/360) angle_true_nudir=-angle_true+5*2*M_PI/360;
			  else angle_reco_nudir=angle_true-5*2*M_PI/360;
			  }
			  else angle_true_nudir=angle_true+5*2*M_PI/360;
			  */
			// cout<<"Pn: "<<Pn[0]<<" "<<Pn[1]<<" "<<Pn[2]<<endl;
			// cout<<"Salvato come evento nel stt: "<<stthit<<endl;
			// cout<<"Angle reco in gradi "<<angle_reco*360/(2*M_PI)<<endl;
			// cout<<"Angle true in gradi "<<angle_true*360/(2*M_PI)<<endl;
			// break;
			
			Vertex_xreco=Xv;
			Vertex_yreco=Yv;
			Vertex_zreco=Zv;

			Vertex_x=Vertex[0];
			Vertex_y=Vertex[1];
			Vertex_z=Vertex[2];
/*
			double ris=(angle_reco-angle_true)/angle_true;

			if(visto==1) isto_ris_stt->Fill(angle_true, ris);
			if(visto==2) isto_ris_calbarrel->Fill(angle_true,ris);
			if(visto==3) isto_ris_calendcap->Fill(angle_true,ris);

			if(vistogbarrel==1 && timegbarrel>10) {cout<<"ERROR "<<vistogbarrel<<" "<< timegbarrel<<endl; return;}
*/
			outputTree->Fill();

		} //chiude per ogni neutrone
	}//chiude il ciclo per ogni evento

} //chiude il ciclo per ogni file
myfile.close();

float HitZ[1]={PosHitZ};
float HitY[1]={PosHitY};

float vZ[1]={Zv};
float vY[1]={Yv};

/*
   TGraph *hitplot=new TGraph(npunti_idpar,hitz,hity);
   TGraph *vplot=new TGraph(1,vZ,vY);
   TGraph *Hplot=new TGraph(1,HitZ,HitY);

   TCanvas *c=new TCanvas("plot","plot",400,400);

   TEllipse* el1=new TEllipse(0.,0.,200.,200.);
   TEllipse* el=new TEllipse(0.,0.,220.,220.);

   el1->SetFillStyle(0);
   el->SetFillStyle(0);
   hitplot->GetXaxis()->SetLimits(-230,230);
   hitplot->GetYaxis()->SetRangeUser(-230,230);
   hitplot->Draw("AP");

   el1->Draw("SAME");
   el->Draw("SAME");

   vplot->SetMarkerColor(2);
   Hplot->SetMarkerColor(2);
   vplot->SetMarkerSize(20);
   Hplot->SetMarkerSize(20);

   vplot->Draw("SAMEP");
   Hplot->Draw("SAMEP");
   */

TFile *output=new TFile("OUT/Neutron_3DST_grouped_time_prova.root","RECREATE");
// output->cd();
outputTree->Write();
isto_ris_stt->Write();
isto_ris_calbarrel->Write();
isto_ris_calendcap->Write();
isto_Edepstt->Write();
isto_Edepbarrel->Write();
isto_Edep3dst->Write();
isto_Edepg3dst->Write();
isto_Edepgbarrel->Write();
//isto_p->Write();
//isto_pq->Write();
cout<<"Eventi visti "<<Neventi_visti<<endl;
cout<<"Eventi totali "<<Neventi<<endl;
cout<<"FATTO "<<endl;

}
