#ifndef MESH_H
#define MESH_H

#include <vector>

#include "Global.h"
#include "Data.h"

//abstract mesh class
class Mesh 
{
	public:
	
	Data & data;
	Mesh(Data & d) : data(d) {}
	
	size_t getNeighbors(size_t i, size_t* n);
	size_t* createGraph();
	uint numVerts();
	
	private:
	void find18Neighbors( uint x, uint y, uint z, size_t *neighbors, size_t &curr_idx);
	
};

#endif
