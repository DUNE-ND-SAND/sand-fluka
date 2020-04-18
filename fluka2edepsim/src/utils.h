#ifndef test
#define test

TLorentzVector GlobalCoordinates(TLorentzVector pos){
	TLorentzVector finalpos;
	finalpos.SetXYZT(pos.X()*10,
			pos.Y()*10 -2384.73,
			pos.Z()*10 +23910,
			pos.T());
	return finalpos;
}
#endif
