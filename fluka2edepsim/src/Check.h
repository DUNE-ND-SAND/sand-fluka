#ifndef test2
#define test2
void  Check(){
	bool check;
	std::cout<< "Nhits From hitstree and Stttree: "<< NIncHits<< " , "<< NStt <<std::endl;
	for (int i=0; i< NStt; i++){
		check = false;
		for(int j=0; j< NIncHits; j++){
			if (TrInc[j] == TrStt[i]) check = true;;
		}
		if (check != true) std::cout<<" Track Id is not consistent"<<std::endl;
		//else std::cout<<" Warning, Track Id is not consistent "<<std::endl;
	}
}
#endif
