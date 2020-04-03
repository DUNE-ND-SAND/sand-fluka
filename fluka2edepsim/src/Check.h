#ifndef test2
#define test2
void  Check(){
	bool check;
        std::cout<< "Nhits From hitstree and Stttree: "<< NIncHits<< " , "<< NStt <<std::endl;
	for(int j=0; j< NIncHits; j++){
		check = false;
		for (int i=0; i< NStt; i++){
			if (TrInc[j] == TrStt[i]) check = true;;
		}
		if (check != true) std::cout<<" Track Id is not consistent"<<std::endl;
		//else std::cout<<" Warning, Track Id is not consistent "<<std::endl;
	}
}
#endif






