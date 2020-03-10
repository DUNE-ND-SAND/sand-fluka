void FillTrajectories(std::vector<TG4Trajectory>& dest, TTree *HitsTree) {
	dest.clear();
	
	Double_t PrTrInc = -1;
        // Making another container to appened the unordered Info
        std::map<Int_t,Float_t> TrInDest;
	TG4Trajectory *tx = 0;
        

	for (int j=0; j< NIncHits; j++) {
                std::cout<< " TrInc : "<<j <<" "<< TrInc[j] <<std::endl;	
		if(TrInc[j] != PrTrInc){
                        //------- New
                        //If it doesnt find it --> add
                        if(tx != 0 && TrInDest.find(PrTrInc)==TrInDest.end()){
                        //if(tx != 0){
                                TrInDest.insert(std::make_pair(PrTrInc,dest.size()));
				dest.push_back(*tx);
                                std::cout<<" ************* Track is not there ***********"<<std::endl;
                                std::cout<<dest.size()<<std::endl;
				//break;
                        }
			PrTrInc = TrInc[j];
                        //------- New
                        //If it finds it let it be
			if(TrInDest.find(TrInc[j])!=TrInDest.end()){
				tx = &(dest[TrInDest[TrInc[j]]]);
                                std::cout<<" ************* Track is there ***********"<<std::endl;
                        //If it doesnt exist make it
			}else{
				tx           = new TG4Trajectory;
				tx->TrackId  = TrInc[j];
				tx->ParentId = IdParInc[j];
                                std::cout<< " ********** Track Id ***********"<< tx->TrackId<<std::endl;
                                std::cout<< " ********** Parent Id ***********"<< tx->ParentId<<std::endl;
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
		PosX->Fill(PosInc[j][0]);

		point.Position.SetXYZT(PosInc[j][0], PInc[j][1], PInc[j][2], TimeInc[j]);
		point.Momentum.SetXYZ (PInc[j][0], PInc[j][1], PInc[j][2]);
	        std::cout<< " Pos(x) , Pos(y) , Pos(z) , Time : "<< PosInc[j][0]<<" , "<< PosInc[j][1] <<" , "<<PosInc[j][2]<<" , "<< TimeInc[j]<<std::endl; 
                std::cout<< " Px  , Py , Pz : "<< PInc[j][0] <<" , "<< PInc[j][1] <<" , "<< PInc[j][2] <<std::endl;	
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
