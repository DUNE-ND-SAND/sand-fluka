#ifndef MAP_TREE_H
#define MAP_TREE_H

#include "TTree.h"
#include <iostream>
#include "MapGeometry.h"
#include <vector>
#include <string>
#include "TVector3.h"

class MapTree
{

public:

                static MapTree* Get();

                ~MapTree();

                //int Init(std::string);
                //int Exit();
                //int WriteOnFile(std::string);
                void InitTree(); 

                void FillTree(int ,float );
                void Fill_MapTree(vector<pair<int,TVector3>>, int);

        private:

                static MapTree* me;
                MapTree();

		TTree* fTTreeMap;

                Int_t fEvtNum;

                Int_t fNHits;
		Int_t fDetType[5000000];
                Float_t fxHits[5000000];
                Float_t fyHits[5000000];
                Float_t fzHits[5000000];
                                                       
};
#endif









