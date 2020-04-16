#ifndef test2
#define test2
void  Check(){
	bool check;
	int  counter = 0;
	std::vector<Int_t> st;
	//std::cout<< "Nhits From hitstree and Stttree: "<< NIncHits<< " , "<< NStt <<std::endl;
        
	std::cout<<"Warning! The Following TrackId are missing in SttTree : "<<std::endl;
	for (int i=0; i< NStt; i++){
		check = false;
		for(unsigned int j=0; j< st.size(); j++){
			if (st[j] == TrStt[i]){
				check = true;
			}
		}
		if (!check)
			st.push_back(TrStt[i]);
		else  continue;
		check = false;
		for(int j=0; j< NIncHits; j++){
			if (TrInc[j] == TrStt[i]){
				check = true;
			}
		}
                //std::cout<< "Track Id of Stt, Check : "<< TrStt[i]<< " , "<< check << std::endl;
		if (!check){
			counter ++;
			std::cout<<" - - - - - -  :  "<<TrStt[i]<<std::endl;
		}
		//else std::cout<<" Warning, Track Id is not consistent "<<std::endl;
	}
	std::cout<<" Total Number of Track ID Missing : "<< counter<<std::endl;
}
#endif
