void FillTrajectories(std::vector<TG4Trajectory>& dest, TTree *HitsTree, int iEntry) {
       //Variables
       Int_t   RunNum, EveNum  , IdInc[MaxNhit], ParTrInc[MaxNhit];
       //Int_t   TrInc[MaxNhit];
       Float_t PInc[MaxNhit][5], TimeInc[MaxNhit];
       Float_t PosInc[MaxNhit][3];
       //Int_t IdParInc[MaxNhit], IdTrack;
       
	//HitTree Info
        HitsTree->SetBranchAddress("RunNum",&RunNum);
        HitsTree->SetBranchAddress("EveNum",&EveNum);
        HitsTree->SetBranchAddress("NIncHits",&NIncHits);   //Number of hits for each particles , Mc hit
        HitsTree->SetBranchAddress("IdInc",&IdInc);         //particle ID                       , Mc hit
        //HitsTree->SetBranchAddress("IdParInc",&IdParInc);   //Parent ID                         , MC hit
        HitsTree->SetBranchAddress("ParTrInc",&ParTrInc);   //Parent ID                         , MC hit
        HitsTree->SetBranchAddress("TrInc",&TrInc);         //Track Num                         , MC hit
        HitsTree->SetBranchAddress("PosInc",&PosInc);       //Position[3]   (x,y,z)             , Mc hit
        HitsTree->SetBranchAddress("PInc",&PInc);           //Energy-Mom[5] (px,py,pz,E,P)      , Mc hit
        HitsTree->SetBranchAddress("TimeInc",&TimeInc);     //Time                              , Mc hit
    	//*************************************************
        
        dest.clear();
        
	HitsTree->GetEntry(iEntry);
	Double_t PrTrInc = -1;
        
	// Making another container to appened the unordered Info
        std::map<Int_t,Float_t> TrInDest;
	TG4Trajectory *tx = 0;

	for (int j=0; j< NIncHits; j++) {
                //std::cout<< " TrInc : "<<j <<" "<< TrInc[j] <<std::endl;	
		if(TrInc[j] != PrTrInc){
                        //If it doesnt find it --> add
                        if(tx != 0 && TrInDest.find(PrTrInc)==TrInDest.end()){
                        //if(tx != 0){
                                TrInDest.insert(std::make_pair(PrTrInc,dest.size()));
				dest.push_back(*tx);
                                //std::cout<<" ************* Track is not there ***********"<<std::endl;
                                //std::cout<<dest.size()<<std::endl;
				//break;
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
				std::cout<<"TrInc ParTr "<<TrInc[j]<<" "<<ParTrInc[j]<<std::endl;
				if (TDatabasePDG::Instance()->GetParticle(IdInc[j])){
                                    tx->Name     = TDatabasePDG::Instance()->GetParticle(IdInc[j])->GetName();
                                }
                                else {tx->Name = "Ion";}
                                //TDatabasePDG::Instance()->GetParticle(IdInc[j])->GetName();
                                //std::cout<< " Number of entries in partcile list : "<< TDatabasePDG::Instance()->GetParticle(IdInc[j])->GetName()<<std::endl;
                                //std::cout<< " ********** Name      ************ "<< Name.GetParticle(tx->PDGCode)->GetName() <<std::endl;
                                //std::cout<< " ********** Track Id  ***********"<< tx->TrackId<<std::endl;
                                //std::cout<< " ********** PDG Code  ***********"<< tx->PDGCode<<std::endl;
                                //std::cout<< " ********** Parent Id ***********"<< tx->ParentId<<std::endl;
				//tx->Name = "prova";
				//tx->PDGCode= 10;

				// tx ->InitialMomentum.SetXYZM(0.9, 0.9, 0.9, 100);
				// traj.InitialMomentum.SetXYZM(ndTraj->GetInitialMomentum().x(),
				// ndTraj->GetInitialMomentum().y(),
				// ndTraj->GetInitialMomentum().z(),
				// part->GetPDGMass();
			}
		}
		// Add the particles associated with the vertex to the summary.
		// Make sure they are ordered...etc ...see code /src/EDepSimPersistencyManager.cc at line 437
		TG4TrajectoryPoint point;
                TLorentzVector pos = GlobalCoordinates(TLorentzVector(PosInc[j][0], PosInc[j][1], PosInc[j][2], TimeInc[j]));

		point.Position.SetXYZT(pos.X(), pos.Y(), pos.Z(), pos.T());
		point.Momentum.SetXYZ (PInc[j][0], PInc[j][1], PInc[j][2]);
	        //std::cout<< " Pos(x) , Pos(y) , Pos(z) , Time : "<< PosInc[j][0]<<" , "<< PosInc[j][1] <<" , "<<PosInc[j][2]<<" , "<< TimeInc[j]<<std::endl; 
                //std::cout<< " Px  , Py , Pz : "<< PInc[j][0] <<" , "<< PInc[j][1] <<" , "<< PInc[j][2] <<std::endl;	
		//point.Position.SetXYZT(edepPoint->GetPosition().x(),
		//		edepPoint->GetPosition().y(),
		//		edepPoint->GetPosition().z(),
		//		edepPoint->GetTime());
		//point.Momentum.SetXYZ(edepPoint->GetMomentum().x(),
		//		edepPoint->GetMomentum().y(),
		//		edepPoint->GetMomentum().z());
		//point.Process = edepPoint->GetProcessType();
		//point.Subprocess = edepPoint->GetProcessSubType();
		tx->Points.push_back(point);
		if(tx != 0 && j == NIncHits - 1 && TrInDest.find(PrTrInc)==TrInDest.end())
			dest.push_back(*tx);

       }
}
