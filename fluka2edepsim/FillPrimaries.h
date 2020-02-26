void FillPrimaries(std::vector<TG4PrimaryVertex>& dest, TTree *HeaderTree) {
	dest.clear();

	int nentries=HeaderTree->GetEntries();  
	cout<<"Ho letto le entries "<<nentries<<endl;
		
	for(int i=0; i<nentries; i++){
		TG4PrimaryVertex vtx;

		vtx.Position.SetX(0.*i);
		vtx.Position.SetY(1.*i);
		vtx.Position.SetZ(2.*i);
		vtx.Position.SetT(3.*i);
                double E = 0.0;
		// Add the particles associated with the vertex to the summary.
		for (int j=0; j< i; ++j) {
			TG4PrimaryParticle prim;
			prim.PDGCode = j; 
			prim.TrackId = j;
			prim.Momentum.SetX(2.22);
			prim.Momentum.SetY(2.22);
			prim.Momentum.SetZ(2.22);
			E += pow(prim.Momentum.P(),2); //è giusto??..era così
			if (E>0) E = std::sqrt(E);
			else E = 0;
			prim.Momentum.SetE(E);
			vtx.Particles.push_back(prim);
		}

		//vtx.Reaction = char(222);
		dest.push_back(vtx);
	}
}
