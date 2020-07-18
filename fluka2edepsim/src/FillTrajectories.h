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


void FillTrajectories(std::vector<TG4Trajectory>& dest, TTree *HitsTree, int iEntry) {
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
	   	


	dest.clear();

	HitsTree->GetEntry(iEntry);
	Double_t PrTrInc = -1;

	// Making another container to appened the unordered Info
	std::map<Int_t,Float_t> TrInDest;
	TG4Trajectory *tx = 0;



	//mettere come funzione...sono 4 volte uguali!!...
	//loop on NIncHits the hit on the boudary


	for (int j=0; j< NIncHits; j++) {
		//std::cout<< " TrInc : "<<j <<" "<< TrInc[j] <<std::endl;	
		if(TrInc[j] != PrTrInc){

			TLorentzVector pos = GlobalCoordinates(TLorentzVector(PosInc[j][0], PosInc[j][1], PosInc[j][2], TimeInc[j]));
			TVector3 mom(PInc[j][0], PInc[j][1], PInc[j][2]); 

			//If it doesnt find it --> add
			if(tx != 0 && TrInDest.find(PrTrInc)==TrInDest.end()){
				//if(tx != 0){
				TrInDest.insert(std::make_pair(PrTrInc,dest.size()));
				dest.push_back(*tx);
				std::cout<<TrInc[j-1]<<" inserted!!"<<std::endl; 
				//std::cout<<" ************* Track is not there ***********"<<std::endl;
				//std::cout<<dest.size()<<std::endl;
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
			TLorentzVector pos = GlobalCoordinates(TLorentzVector(PosInc[j][0], PosInc[j][1], PosInc[j][2], TimeInc[j]));

			point.Position.SetXYZT(pos.X(), pos.Y(), pos.Z(), pos.T());
			point.Momentum.SetXYZ (PInc[j][0], PInc[j][1], PInc[j][2]);
			//point.Process = edepPoint->GetProcessType();
			//point.Subprocess = edepPoint->GetProcessSubType();
			tx->Points.push_back(point);
			if(tx != 0 && j == NIncHits - 1 && TrInDest.find(PrTrInc)==TrInDest.end())  dest.push_back(*tx);
		}		


		//loop on the NIneHits
		//

		Double_t PrTrIne=-1;
		Double_t PrSecTrIne=-1;
		int k=0;

		for (int j=0; j< NIneHits; j++) {
			//std::cout<< " TrIne : "<<j <<" "<< TrIne[j] <<std::endl;	
			if(TrIne[j] != PrTrIne){
				//If it doesnt find it --> add
				if(tx != 0 && TrInDest.find(PrTrIne)==TrInDest.end()){
					TrInDest.insert(std::make_pair(PrTrIne,dest.size()));
					dest.push_back(*tx);
					std::cout<<TrIne[j-1]<<" inserted in Ine!!"<<std::endl; 
				///       std::cout<<" ************* Track is not there ***********"<<std::endl;
					//std::cout<<dest.size()<<std::endl;
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
					std::cout<<"NTIneSec "<<NTIneSec<<std::endl;		
					int tr_fath=FindFather(TrIne[j], NTIneSec);
					tx->ParentId = tr_fath;
					tx->PDGCode  = IdIne[j];
					std::cout<<"TrIne father "<<TrIne[j]<<" "<<tr_fath<<std::endl;
					if (TDatabasePDG::Instance()->GetParticle(IdIne[j])){
						tx->Name     = TDatabasePDG::Instance()->GetParticle(IdIne[j])->GetName();
					}
					else {tx->Name = "Ion";}
				}
			}

			// Add the particles associated with the vertex to the summary.
			// Make sure they are ordered...etc ...see code /src/EDepSimPersistencyManager.cc at line 437
			TG4TrajectoryPoint point;
			TLorentzVector pos = GlobalCoordinates(TLorentzVector(PosIne[j][0], PosIne[j][1], PosIne[j][2], TimeIne[j]));
			point.Position.SetXYZT(pos.X(), pos.Y(), pos.Z(), pos.T());
			point.Momentum.SetXYZ (PIne[j][0], PIne[j][1], PIne[j][2]);
			//point.Process = edepPoint->GetProcessType();
			//point.Subprocess = edepPoint->GetProcessSubType();
			tx->Points.push_back(point);
			if(tx != 0 && j == NIneHits - 1 && TrInDest.find(PrTrIne)==TrInDest.end())  dest.push_back(*tx);


			bool newp=false;

			
			//costruisco già tutti i figli
			for(int i=k; i<k+NSecIne[j]; i++){
				//gli indici di questa interazione vanno da k a k+NSecIne[i]
				std::cout<< " TrSecIne : "<<i <<" "<< TrSecIne[i] <<std::endl;	
				//If it doesnt find it --> add

				//       std::cout<<" ************* Track is not there ***********"<<std::endl;
				//std::cout<<dest.size()<<std::endl;

				//If it finds it let it be
				if(TrInDest.find(TrSecIne[i])!=TrInDest.end()){
					tx = &(dest[TrInDest[TrSecIne[i]]]);
					std::cout<<" ************* Track is there ***********"<<std::endl;
					//If it doesnt exist make it
				}else{
					std::cout<<" ************* New Track ***********"<<std::endl;
					newp= true;	
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
				TLorentzVector pos = GlobalCoordinates(TLorentzVector(PosIne[i][0], PosIne[i][1], PosIne[i][2], TimeIne[i]));

				point.Position.SetXYZT(pos.X(), pos.Y(), pos.Z(), pos.T());
				point.Momentum.SetXYZ (PSec[i][0], PSec[i][1], PSec[i][2]);
				//point.Process = edepPoint->GetProcessType();
				//point.Subprocess = edepPoint->GetProcessSubType();
				tx->Points.push_back(point);

				PrSecTrIne=TrSecIne[i];
				TrInDest.insert(std::make_pair(PrSecTrIne,dest.size()));
				if(newp==true){ 
					dest.push_back(*tx);
					std::cout<<TrSecIne[i]<<" point inserted in new track as TrSecIne "<<std::endl;
					}
				else{std::cout<<TrSecIne[i]<<" point inserted as TrSecIne "<<std::endl;}
			//sono tutti punti diversi!!..quindi chiudo subito la traccia
			}
			k+=NSecIne[j]; //in modo che al giro dopo mi trovo all'indice giusto
		}


//controllo che i punti ci siano tutti:
//

std::cout<<"FINE....ecco tutte le traiettorie "<<std::endl;

for (std::vector<TG4Trajectory>::iterator
				t = dest.begin();
				t != dest.end(); ++t) {
			std::cout << " TrackId " << t->TrackId;
			std::cout << " ParentId " << t->ParentId;
			int count = t->Points.size();
			std::cout << " Up to " << count << " points";
			std::cout << std::endl;

	}
}
