#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "TVector3.h"
#include <string>

using namespace std;

class MapGeometry {

private:
    MapGeometry();
    static MapGeometry* me;

    vector<pair<int,TVector3>> fMap;  
    int fN;


public:
    virtual ~MapGeometry();
    static MapGeometry* Get();
    void ClearMap();

    void AddPointToMap(int, TVector3);
    vector<pair<int,TVector3>> GetMap (){return fMap;}

    int GetN() const {return fN;}


};
#endif
                                                                
