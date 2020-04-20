#include "MapGeometry.h"
#include <iostream>
#include <string>

MapGeometry* MapGeometry::me = 0;

MapGeometry* MapGeometry::Get() {
	if (!me) me=new MapGeometry();
	return me;


}

MapGeometry::MapGeometry() {
	fN=0 ; 
	std::cout<<"SONO IN DUSTORAGE:::::::::::::::::::::"<<std::endl;
}

MapGeometry::~MapGeometry() {}

void MapGeometry::ClearMap() {
	fMap.clear();
}


void MapGeometry::AddPointToMap(string det_info, TVector3 pos){

	pair<string,TVector3> new_point;

	new_point.first=det_info;
	new_point.second=pos;

	fMap.push_back(new_point);
}
