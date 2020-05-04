#include "TTree.h"
#include <iostream>
#include "MapTree.h"

MapTree* MapTree::me = 0;

MapTree* MapTree::Get() {
        if (!me) me=new MapTree();
        return me;
}



MapTree::MapTree()
{

        fEvtNum=0;


}

MapTree::~MapTree()
{
        delete fTTreeMap;
}


void MapTree::InitTree(){

	fTTreeMap=new TTree("MapTree","MapTree");
	fTTreeMap->Branch("EvtNum",&fEvtNum,"EvtNum/I");
	fTTreeMap->Branch("NHits",&fNHits,"NHits/I");
	fTTreeMap->Branch("xHits",&fxHits,"xHits[NHits]/F");
	fTTreeMap->Branch("yHits",&fyHits,"yHits[NHits]/F");
	fTTreeMap->Branch("zHits",&fzHits,"zHits[NHits]/F");
	fTTreeMap->Branch("DetType",&fDetType, "DetType[NHits]/I");

}


void MapTree::FillTree(int j,float k){
	fEvtNum=j;
	fNHits=j;
	for(int l=0; l<fNHits; l++){
		fxHits[l]=k;
		fyHits[l]=k;
		fzHits[l]=k;
	//	fDetType[l]="prova";
	}
	fTTreeMap->Fill();
}

void MapTree::Fill_MapTree(vector<pair<int,TVector3>> map, int  entry){
	fEvtNum=entry;
	fNHits=map.size();

	int ihit=0;	
           for (auto j = map.begin(); j != map.end(); ++j){

                       // pair<string, TVector3> val=(*j);

//                      detpos[ihit]=val.first;
                       // std::cout<<"detector "<<val.first<<std::endl;
                //      std::cout<<"position "<<val.second(0)<<std::endl;
                        fDetType[ihit]=(*j).first;
			fxHits[ihit]=(*j).second(0);
	                fyHits[ihit]=(*j).second(1);
        	        fzHits[ihit]=(*j).second(2);

                        if(ihit==fNHits) {std::cout<<"ERROR on total number of hits"<<std::endl; break;}
                        ihit++;
                }
                if(ihit!=fNHits) {std::cout<<"ERROR on number of hits"<<std::endl; exit(1); }
	
	fTTreeMap->Fill();

}
