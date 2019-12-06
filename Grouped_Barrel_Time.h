//This function analyses the barrel hits and using the digitization class (Ideal2RealCal), it groups in cell and fills an array with the information of the cells with hits
//then it calculates the weigthed time for each cell and the sum of the energy of hits arriving in the cell in the barreltimecut window respect the weighted time
//then it searches for cells over the threshold (sogliabarrel) and it saves the minimum weighted time in timegbarrel
//
extern const float sogliabarrel;
extern const float barreltimecut;
extern const float timecutcell;
//
void Grouped_Barrel_Time(int NStt, int Ntr, float PosInStt[NStt][3], float PosOuStt[NStt][3], int *IdStt, float EdqStt[NStt], int *IdParStt, float *TimeStt, float &Edepgbarrel, float &timegbarrel, int &vistogbarrel, TH2D *istogbarrel, float &xb, float &yb, float &zb){

	float PosCalCell[2000][3];
	float EnCalCell[2000];
	float TimeCalCell[2000];
	float TimeMaxCalCell[2000];
	float NhitCalCell[2000];
	float EnCutCalCell[2000];
	float TimeWeigCalCell[2000];

	for(int y=0; y<2000; y++){
		TimeWeigCalCell[y]=0;
	}

	//int IdCube[8000];
	int n_cell=0;
	int j=0;

	float PosCalX, PosCalY, PosCalZ, EdepCal, TimeCal;
	Ideal2RealCal *event1;

	int used_hit=0;

	for(int i=0; i<NStt; i++){
		//cerco il neutrone o i figli
		bool new_dato;
		if(IdParStt[i]==Ntr){
			float R=sqrt(PosInStt[i][1]*PosInStt[i][1]+PosInStt[i][2]*PosInStt[i][2]);
			if(R<200 || R>225 || abs(PosInStt[i][0])>169) continue; 
			new_dato=true;
			//cout<<"Radius "<<R<<endl;
			//cout<<"PosInStt "<<PosInStt[i][0]<<" "<<PosInStt[i][1]<<" "<<PosInStt[i][2]<<endl;

			event1 = new Ideal2RealCal(EdqStt[i], PosInStt[i], PosOuStt[i], IdStt[i], TimeStt[i]);

			PosCalX=event1->Get_Pos()[0];
			PosCalY=event1->Get_Pos()[1];
			PosCalZ=event1->Get_Pos()[2];
			//EdepCal=EdqStt[i];
			EdepCal=event1->Get_EnPmt()[0]+event1->Get_EnPmt()[1];
			
			TimeCal=TimeStt[i];
			delete event1;

//			if(EdepCal<0.00003) continue; //10 keV
//			cout<<"indice dell' hit "<<i<<endl;
			
			R=sqrt(PosCalY*PosCalY+PosCalZ*PosCalZ);
			if(R<200 || R>225){ cout<<"Error after Ideal2Real R !!"<<R<<" "<<PosCalX<<" "<<PosCalY<<" "<<PosCalZ<<endl; exit;} 


			if(n_cell>0){
				for(j=0; j<n_cell; j++){
					//in cm secondo la scelta di Federico
					if(abs(PosCalY-PosCalCell[j][1])<0.5 &&  abs(PosCalZ-PosCalCell[j][2])<0.5) {
						new_dato=false;
						break;
					}

				}
			}					
			used_hit++;
			if(new_dato==false) {
//				cout<<"indice della cella "<<j<<endl;
				EnCalCell[j]+=EdepCal;
				NhitCalCell[j]++;
				if(TimeCalCell[j]>TimeCal) { TimeCalCell[j]=TimeCal; }
				if(TimeMaxCalCell[j]<TimeCal) { TimeMaxCalCell[j]=TimeCal; }
				TimeWeigCalCell[j]+=EdepCal*TimeCal;
	//                  if (IdCube[i]!= IdCell[j]) IdCube[j]=-1000;
			}else { //nuova cella
//				cout<<"indice della nuova cella "<<n_cell<<endl;
				PosCalCell[n_cell][0]=PosCalX;
				PosCalCell[n_cell][1]=PosCalY;
				PosCalCell[n_cell][2]=PosCalZ;
				EnCalCell[n_cell]=EdepCal;
				TimeCalCell[n_cell]=TimeCal;
				TimeMaxCalCell[n_cell]=TimeCal;
				NhitCalCell[n_cell]=1;
				TimeWeigCalCell[n_cell]=EdepCal*TimeCal;
			//	IdCube[n_cell]=IdCell[i];
				n_cell++;
				if(n_cell>2000){
					cout<<"Aumentare n_cell oltre 2000!!"<<endl;
					return;
				}
			}  //cout<<"nuovo dato "<<ri<<" "<<R<<

		}


	}


	for(int y=0; y<n_cell; y++){
		TimeWeigCalCell[y]=TimeWeigCalCell[y]/EnCalCell[y];
	}




	//cout<<"Ho n_cell "<<n_cell<<endl;


	vistogbarrel=0;
	Edepgbarrel=9999;
	timegbarrel=9999;
	//Ottengo le info del barrel: quelli della cella con il tempo minimo


	//considero ora solo gli hit che arrivano entro 30 ns dal primo

	for(j=0; j<n_cell; j++){
		EnCutCalCell[j]=0;
	}	 

	int used_hit2=0;
	for(int i=0; i<NStt; i++){
		//cerco il neutrone o i figli
		if(IdParStt[i]==Ntr){
			float R=sqrt(PosInStt[i][1]*PosInStt[i][1]+PosInStt[i][2]*PosInStt[i][2]);
			float Ro=sqrt(PosOuStt[i][1]*PosOuStt[i][1]+PosOuStt[i][2]*PosOuStt[i][2]);

			if(R<200 || R>225 || abs(PosInStt[i][0])>169) continue; 
			//cout<<"Radius "<<R<<endl;
			//cout<<"PosInStt "<<PosInStt[i][0]<<" "<<PosInStt[i][1]<<" "<<PosInStt[i][2]<<endl;
			Ideal2RealCal *event1;

			event1 = new Ideal2RealCal(EdqStt[i], PosInStt[i], PosOuStt[i], IdStt[i], TimeStt[i]);

			PosCalX=event1->Get_Pos()[0];
			PosCalY=event1->Get_Pos()[1];
			PosCalZ=event1->Get_Pos()[2];
			//EdepCal=EdqStt[i];
			EdepCal=event1->Get_EnPmt()[0]+event1->Get_EnPmt()[1];

			TimeCal=TimeStt[i];
			delete event1;

//			if(EdepCal<0.000030) continue;
//			cout<<"indice dell' hit "<<i<<endl;
			
			if(n_cell>0){
				for(j=0; j<n_cell; j++){
					//in cm secondo la scelta di Federico
					if(abs(PosCalY-PosCalCell[j][1])<0.5 &&  abs(PosCalZ-PosCalCell[j][2])<0.5) {
						break;
					}
					// allora l'hit è della cella j

				}
			}	
			//istogbarrel->Fill(TimeCal-TimeCalCell[j],EdepCal);
//			cout<<"indice della cella "<<j<<endl;				
			//istogbarrel->Fill(TimeCal-TimeCalCell[j]);
			if((TimeWeigCalCell[j]+barreltimecut)>=TimeCal) {
				//istogbarrel->Fill(EdepCal);
				EnCutCalCell[j]+=EdepCal;
			
			}
			used_hit2++;	
		}
	}

	if(used_hit!=used_hit2) cout<<"ERROR "<<endl;
	//cout<<"used hit "<<used_hit<<endl;
	
	float EdepMAXgbarrel=0;	
	for(int k=0; k<n_cell; k++){
		//cout<<"PosCalCell "<<PosCalCell[k][0]<<" "<<PosCalCell[k][1]<<" "<<PosCalCell[k][2]<<" "<<EnCalCell[k]<<endl;
		if(EdepMAXgbarrel<EnCalCell[k]) EdepMAXgbarrel=EnCalCell[k];
		//istogbarrel->Fill(EnCalCell[k]);
		//if(EnCalCell[k]>sogliabarrel) { // && TimeCalCell[k]<300e-9){
		if(EnCutCalCell[k]>sogliabarrel && TimeWeigCalCell[k]<timecutcell) {
			vistogbarrel=1;
			istogbarrel->Fill(TimeWeigCalCell[k]-TimeCalCell[k],EnCalCell[k]);
			//istogbarrel->Fill(TimeCalCell[k]);
			Edepgbarrel+=EnCutCalCell[k];
			if(TimeWeigCalCell[k]<timegbarrel) {
				timegbarrel=TimeWeigCalCell[k];
				//Edepgbarrel=EnCalCell[k];
				xb=PosCalCell[k][0];
				yb=PosCalCell[k][1];
				zb=PosCalCell[k][2];
				//cout<<"xb "<<xb<<" "<<yb<<" "<<zb<<endl;
			}
		}

	}
	//istogbarrel->Fill(used_hit);
	//cout<<"Info barrelg: Edep "<<Edepgbarrel<<" "<<Timegbarrel<<" "<<vistogbarrel<<endl;
}
