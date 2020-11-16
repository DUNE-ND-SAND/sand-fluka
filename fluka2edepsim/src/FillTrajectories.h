int FindFather(int tr, int NT){

	int indexsec=-1;

	for(int i=0; i<NT; i++){
		if(TrSecIne[i]==tr) {
			indexsec=i; break;
		}
	}

	int tr_father=-1;

	if(indexsec>-1){
		for(int i=0; i<NIneHits; i++){
			if(FirstSec[i]<=indexsec && FirstSec[i]+NSecIne[i]>indexsec) {tr_father=TrIne[i]; break;}
		}
	}
	return tr_father;
}

bool my_IsBigger(TG4TrajectoryPoint i,TG4TrajectoryPoint j) { 
	return (i.Position.T()<j.Position.T());
 }


void FillTrajectories(std::vector<TG4Trajectory>& destfin, TTree *HitsTree, int iEntry) {
	//Variables
	Int_t   RunNum, EveNum;

	//HitTree Info
	HitsTree->SetBranchAddress("RunNum",&RunNum);
	HitsTree->SetBranchAddress("EveNum",&EveNum);
	HitsTree->SetBranchAddress("NIncHits",&NIncHits);   //Number of hits for each particles , Mc hit
	HitsTree->SetBranchAddress("IdInc",&IdInc);         //particle ID                       , Mc hit
	//HitsTree->SetBranchAddress("IdParInc",&IdParInc);   //Parent ID                       , MC hit
	HitsTree->SetBranchAddress("ParTrInc",&ParTrInc);   //Parent ID                         , MC hit
	HitsTree->SetBranchAddress("TrInc",&TrInc);         //Track Num                         , MC hit
	HitsTree->SetBranchAddress("PosInc",&PosInc);       //Position[3]   (x,y,z)             , Mc hit
	HitsTree->SetBranchAddress("PInc",&PInc);           //Energy-Mom[5] (px,py,pz,E,P)      , Mc hit
	HitsTree->SetBranchAddress("TimeInc",&TimeInc);     //Time                              , Mc hit
	//*************************************************

	HitsTree->SetBranchAddress("NIneHits",&NIneHits);   //Number of inelastic interactions  , Mc hit
	HitsTree->SetBranchAddress("IdIne",&IdIne);         //particle ID                       , Mc hit
	HitsTree->SetBranchAddress("TypeIne",&TypeIne);     //Type of interaction               , Mc hit
	HitsTree->SetBranchAddress("IdParIne",&IdParIne);   //Parent ID                        , MC hit
	HitsTree->SetBranchAddress("TrIne",&TrIne);         //Track Num                         , MC hit
	HitsTree->SetBranchAddress("PosIne",&PosIne);       //Position[3]   (x,y,z)             , Mc hit
	HitsTree->SetBranchAddress("PIne",&PIne);           //Energy-Mom[5] (px,py,pz,E,P)      , Mc hit
	HitsTree->SetBranchAddress("TimeIne",&TimeIne);     //Time                              , Mc hit
	//*************************************************
	
	   HitsTree->SetBranchAddress("NSecIne",&NSecIne);   //Number of secondary in the inelastic interactions  , Mc hit
	   HitsTree->SetBranchAddress("FirstSec",&FirstSec);   //index of the first secondary particle in the NTIneSec collection  , Mc hit
	   HitsTree->SetBranchAddress("NTIneSec",&NTIneSec);   //Number of total secondaries in all the inelastic interactions  , Mc hit
	   HitsTree->SetBranchAddress("TrSecIne",&TrSecIne);   //Number of the track of secondary in the inelastic interactions  , Mc hit
	   HitsTree->SetBranchAddress("IdSecIne",&IdSecIne);         //particle ID                       , Mc hit
	   HitsTree->SetBranchAddress("PSec",&PSec);         //Initial momentum of interaction daugthers                       , Mc hit
	   	

	std::vector<TG4Trajectory> dest; 
	dest.clear();
	destfin.clear();


	HitsTree->GetEntry(iEntry);
	Double_t PrTrInc = -1;

	// Making another container to appened the unordered Info
	std::map<int,int> TrInDest;
	TrInDest.clear();
	
	TG4Trajectory *tx = 0;	



	//loop on NIncHits the hit on the boudary


	for (int j=0; j< NIncHits; j++) {
		//std::cout<< " TrInc : "<<j <<" "<< TrInc[j] <<std::endl;	
		if(TrInc[j] != PrTrInc){

			TLorentzVector pos = GlobalCoordinates(TLorentzVector(PosInc[j][0], PosInc[j][1], PosInc[j][2], TimeInc[j]*1e9));

			//If it doesnt find it --> add
			if(tx != 0 && TrInDest.find(PrTrInc)==TrInDest.end()){
				//if(tx != 0){
				TrInDest.insert(std::make_pair(PrTrInc,dest.size()));
				dest.push_back(*tx);
				
			}
			PrTrInc = TrInc[j];
			//If it finds it let it be
			if(TrInDest.find(TrInc[j])!=TrInDest.end()){
				tx = &(dest[TrInDest[TrInc[j]]]);
				//       std::cout<<" ************* Track is there ***********"<<std::endl;
				//If it doesnt exist make it
			}else{
				tx           = new TG4Trajectory;
				tx->TrackId  = TrInc[j];
				tx->ParentId = ParTrInc[j];
				tx->PDGCode  = IdInc[j];
				//std::cout<<"TrInc ParTr "<<TrInc[j]<<" "<<ParTrInc[j]<<std::endl;
				if (TDatabasePDG::Instance()->GetParticle(IdInc[j])){
					tx->Name     = TDatabasePDG::Instance()->GetParticle(IdInc[j])->GetName();

				}
				else {
					tx->Name = "Ion";
				}
			}
		}
		// Add the particles associated with the vertex to the summary.
		// Make sure they are ordered...etc ...see code /src/EDepSimPersistencyManager.cc at line 437
		TG4TrajectoryPoint point;
		TLorentzVector pos = GlobalCoordinates(TLorentzVector(PosInc[j][0], PosInc[j][1], PosInc[j][2], TimeInc[j]*1e9));

		point.Position.SetXYZT(pos.X(), pos.Y(), pos.Z(), pos.T());
		point.Momentum.SetXYZ (PInc[j][0]*1000, PInc[j][1]*1000, PInc[j][2]*1000);
		//point.Process = edepPoint->GetProcessType();
		//point.Subprocess = edepPoint->GetProcessSubType();
	
///		std::cout<<"Inserisco il punto INC "<<point.Position.X()<<" "<<point.Position.Y()<<" "<<point.Position.Z()<<" "<<point.Position.T()<<std::endl;	


		tx->Points.push_back(point);
		if(tx != 0 && j == NIncHits - 1 && TrInDest.find(PrTrInc)==TrInDest.end())  {
			TrInDest.insert(std::make_pair(PrTrInc,dest.size()));
			dest.push_back(*tx);
			}		
	}

		//loop on the NIneHits
		//

	Double_t PrTrIne=-1;
	Double_t PrSecTrIne=-1;
	int k=0;
        tx=0;

	for (int j=0; j< NIneHits; j++) {
//		std::cout<< " TrIne : "<<j <<" "<< TrIne[j] <<std::endl;	
		if(TrIne[j] != PrTrIne){
			//If it doesnt find it --> add
			if(tx != 0 && TrInDest.find(PrTrIne)==TrInDest.end()){
				TrInDest.insert(std::make_pair(PrTrIne,dest.size()));
				dest.push_back(*tx);

			///       std::cout<<" ************* Track is not there ***********"<<std::endl;
			}

			PrTrIne = TrIne[j];
			//If it finds it let it be
			if(TrInDest.find(TrIne[j])!=TrInDest.end()){
				tx = &(dest[TrInDest[TrIne[j]]]);
					//        std::cout<<" ************* Track is there ***********"<<std::endl;
					//If it doesnt exist make it
			}else{
				
				tx           = new TG4Trajectory;
				tx->TrackId  = TrIne[j];
				//std::cout<<"NTIneSec "<<NTIneSec<<std::endl;		
				int tr_fath=FindFather(TrIne[j], NTIneSec);
				tx->ParentId = tr_fath;
				tx->PDGCode  = IdIne[j];
				//std::cout<<"TrIne father "<<TrIne[j]<<" "<<tr_fath<<std::endl;
				if (TDatabasePDG::Instance()->GetParticle(IdIne[j])){
					tx->Name     = TDatabasePDG::Instance()->GetParticle(IdIne[j])->GetName();
				}
				else {tx->Name = "Ion";}
			}
		}

		// Add the particles associated with the vertex to the summary.
		// Make sure they are ordered...etc ...see code /src/EDepSimPersistencyManager.cc at line 437
		TG4TrajectoryPoint point;
		TLorentzVector pos = GlobalCoordinates(TLorentzVector(PosIne[j][0], PosIne[j][1], PosIne[j][2], TimeIne[j]*1e9));
	

		point.Position.SetXYZT(pos.X(), pos.Y(), pos.Z(), pos.T());
		point.Momentum.SetXYZ (PIne[j][0]*1000, PIne[j][1]*1000, PIne[j][2]*1000);
		//point.Process = edepPoint->GetProcessType();
		//point.Subprocess = edepPoint->GetProcessSubType();

		tx->Points.push_back(point);
		if(tx != 0 && j == NIneHits - 1 && TrInDest.find(PrTrIne)==TrInDest.end()){
				TrInDest.insert(std::make_pair(PrTrIne,dest.size()));
				dest.push_back(*tx);
		}
	}	

	
	for (int j=0; j< NIneHits; j++) {
		
		//std::cout<<" j TrIne[j] FirstSec NSec"<<j<<" "<<TrIne[j]<<" "<<FirstSec[j]<<" "<<NSecIne[j]<<std::endl;

		//costruisco tutti i figli
		for(int i=k; i<k+NSecIne[j]; i++){
				//if(PrSecTrIne==TrSecIne[i]) std::cout<<"ERROR...stesso numero a particelle diverse???"<<std::endl;

				//gli indici di questa interazione vanno da k a k+NSecIne[i]
		//		std::cout<< "i TrSecIne : "<<" "<<TrSecIne[i] <<" IdSecIne "<<IdSecIne[i]<<std::endl;	

				if(TrInDest.find(TrSecIne[i])!=TrInDest.end()){
					tx = &(dest[TrInDest[TrSecIne[i]]]);
					//If it doesnt exist make it
				}else{
					//std::cout<<" ************* New Track ***********"<<std::endl;
					tx           = new TG4Trajectory;
					tx->TrackId  = TrSecIne[i];
					tx->ParentId = TrIne[j]; // sono tutti figli dello stesso padre
					tx->PDGCode  = IdSecIne[i];
					if (TDatabasePDG::Instance()->GetParticle(IdSecIne[i])){
						tx->Name     = TDatabasePDG::Instance()->GetParticle(IdSecIne[i])->GetName();
					}
					else {tx->Name = "Ion";}
				}
				// Add the particles associated with the vertex to the summary.
				// Make sure they are ordered...etc ...see code /src/EDepSimPersistencyManager.cc at line 437
				TG4TrajectoryPoint point;
				TLorentzVector pos = GlobalCoordinates(TLorentzVector(PosIne[j][0], PosIne[j][1], PosIne[j][2], TimeIne[j]*1e9));
				point.Position.SetXYZT(pos.X(), pos.Y(), pos.Z(), pos.T());
				point.Momentum.SetXYZ (PSec[i][0]*1000, PSec[i][1]*1000, PSec[i][2]*1000);
				//point.Process = edepPoint->GetProcessType();
				//point.Subprocess = edepPoint->GetProcessSubType();
	
				bool newp=true;
				//std::cout<<"numero di punti su cui controllo "<<tx->Points.size()<<std::endl;
				float timelast=-1;
				for (std::vector<TG4TrajectoryPoint>::iterator
	                           p = tx->Points.begin();
        	                   p != tx->Points.end();
                		           ++p) {
                           		timelast=p->Position.T();
					if(abs(point.Position.X()-p->Position.X())<0.1 && abs(point.Position.Y()-p->Position.Y())<0.1 && abs(point.Position.Z()-p->Position.Z())<0.1 && abs(point.Position.T()-p->Position.T())<1e-11) {
				//		std::cout<<"ERROR ho trovato un punto uguale "<<std::endl;
						newp=false;
						break;
					}
				}
				
				if(newp==true) {
				//std::cout<<"tempo dell'ultimo punto "<<tx->Points.back().Position.T()<<std::endl;
				if(timelast>point.Position.T()){ 
				
				 //std::cout<<"ERROR on time: l'ultimo punto è precedente!!  nuovo punto e timelast "<<point.Position.T()<<" "<<timelast<<std::endl;	
				}
			//	std::cout<<"Inserisco il punto SEC"<<point.Position.X()<<" "<<point.Position.Y()<<" "<<point.Position.Z()<<" "<<point.Position.T()<<std::endl;	


				tx->Points.push_back(point);
				}							
				//std::cout<<"numero di punti a fine giro "<<tx->Points.size()<<std::endl;
				
				PrSecTrIne=TrSecIne[i];
				
				TrInDest.insert(std::make_pair(PrSecTrIne,dest.size()));
				dest.push_back(*tx);		
								//}
				//sono tutti punti diversi!!..quindi chiudo subito la traccia
			}
			k+=NSecIne[j]; //in modo che al giro dopo mi trovo all'indice giusto
		}
	
//	delete tx;	

//riordino le tracce con TrackId in ordine crescente
 for (std::map<int,int>::iterator i = TrInDest.begin();
         i != TrInDest.end(); ++i) {
        destfin.push_back(dest[i->second]);
    }


//riordino i Points con i tempi crescenti


for (std::vector<TG4Trajectory>::iterator
				t = destfin.begin();
				t != destfin.end(); ++t) {
			std::sort (t->Points.begin(), t->Points.end(), my_IsBigger); 
 					
	}



/*
std::cout<<"FINE....ecco tutte le traiettorie "<<std::endl;

for (std::vector<TG4Trajectory>::iterator
				t = destfin.begin();
				t != destfin.end(); ++t) {
			std::cout << " TrackId " << t->TrackId;
		//	std::cout << " ParentId " << t->ParentId;
			int count = t->Points.size();
			std::cout << " Up to " << count << " points";
			std::cout << std::endl;
			std::sort (t->Points.begin(), t->Points.end(), my_IsBigger); 
 					
			float last=-1;	
                       for (std::vector<TG4TrajectoryPoint>::iterator
		 		   p = t->Points.begin();
				   p != t->Points.end();
			   		++p) {
			if(p->Position.T()<last) std::cout<<"ERRORRRRRR"<<std::endl;
			last=p->Position.T();
			std::cout << " Time: " << p->Position.T();
			   std::cout << " Position: " << p->Position.X()<<" "<< p->Position.Y()<<" "<< p->Position.Z();
			//PosX->Fill(p->Position.X());
			//std::cout << " Subprocess: " << p->Subprocess;
			std::cout << std::endl;
			if (--count < 1) break;
			}

	}
std::cout << "Tempo del'ultimo punto "<<((destfin.back()).Points.back()).Position.X()<<std::endl;
*/

}
