void FillTrajectories(std::vector<TG4Trajectory>& dest, TTree *HitsTree) {
	dest.clear();

	//I need number of tracks
	int ntracks=10; //HeaderTree->GetEntries();  FIXME

	for(int i=0; i<ntracks; i++){

		TG4Trajectory tx;

		tx.TrackId= 2;
		tx.ParentId = 2;
		tx.Name = "prova";
		tx.PDGCode= 10;

		tx.InitialMomentum.SetXYZM(0.9, 0.9, 0.9, 100);
		//traj.InitialMomentum.SetXYZM(ndTraj->GetInitialMomentum().x(),
		// ndTraj->GetInitialMomentum().y(),
		// ndTraj->GetInitialMomentum().z(),
		// part->GetPDGMass();

		int npoints;
		// Add the particles associated with the vertex to the summary.
		for (int j=0; j< npoints; j++) {

			//make sure they are ordered...etc ...see code /src/EDepSimPersistencyManager.cc at line 437
			TG4TrajectoryPoint point;
			point.Position.SetXYZT(11.0, 11.0, 11.0,11.0);
			point.Momentum.SetXYZ(12.0, 12.0, 12.0);
			
			//point.Position.SetXYZT(edepPoint->GetPosition().x(),
			//		edepPoint->GetPosition().y(),
			//		edepPoint->GetPosition().z(),
			//		edepPoint->GetTime());
			//point.Momentum.SetXYZ(edepPoint->GetMomentum().x(),
			//		edepPoint->GetMomentum().y(),
			//		edepPoint->GetMomentum().z());
			//point.Process = edepPoint->GetProcessType();
			//point.Subprocess = edepPoint->GetProcessSubType();
			tx.Points.push_back(point);
		}

		dest.push_back(tx);
	}
}
