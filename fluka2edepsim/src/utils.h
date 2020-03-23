
TLorentzVector GeneralCoordinates(TLorentzVector pos){
	TLorentzVector finalpos;
	finalpos.SetXYZT(pos.X(),
			pos.Y() -238.473,
			pos.Z() +2391.0,
			pos.T());
	return finalpos;
}
