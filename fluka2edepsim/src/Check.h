#ifndef test2
#define test2
void  Check(){
	bool check;
	int  counter = 0;
	std::vector<Int_t> st;  //salvo quelli visti
	//std::cout<< "Nhits From hitstree and Stttree: "<< NIncHits<< " , "<< NStt <<std::endl;
//	std::cout<< "Nhits From hitstree and Stttree: "<< NIncHits<< " , "<< NSttHits <<std::endl;
        
	for (int i=0; i< NSttHits; i++){
		check = false;
		if(TrStt[i]<=NPrimari) continue;   // i primari ci sono sicuramente (altrimenti dovrei fari i loop su NumLep, NumHad...) (non serve il check)
		if(st.size()!=0){   //controllo di non averlo già visto
		for(unsigned int j=0; j< st.size(); j++){
			
			if (st[j] == TrStt[i]){
				check = true;
			}
		}
			if (!check) st.push_back(TrStt[i]);
		
		}

		if(check==true) continue; 
		check = false;
		for(int j=0; j< NIncHits; j++){
			if (TrInc[j] == TrStt[i]){
				check = true;
			}
		}
		if (check==true) continue;
		for(int j=0; j< NIneHits; j++){
			if (TrIne[j] == TrStt[i]){
				check = true;
			}
		}
		if(check==true) continue;
		int k=0;
		for(int j=0; j< NIneHits; j++){
			for(int ii=k; ii<k+NSecIne[j]; ii++){
				if(TrSecIne[ii]==TrStt[i]) check=true;	
			}
			k+=NSecIne[j];
		
		}

                //std::cout<< "Track Id of Stt, Check : "<< TrStt[i]<< " , "<< check << std::endl;
		if (!check){
			counter ++;
			std::cout<<" Missed track numb- - - - - -  :  "<<TrStt[i]<<std::endl;
		}
		//else std::cout<<" Warning, Track Id is not consistent "<<std::endl;
	}
	std::cout<<" Total Number of Track ID Missing : "<< counter<<std::endl;

}
#endif
