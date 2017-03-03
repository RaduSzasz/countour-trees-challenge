#include "Mesh.h"

#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::sort;





//functor for sorting
class AscendingOrder 
{
	Data & data;
	public:
	AscendingOrder( Data & d ) : data(d) {}
	bool operator()(const uint & a, const uint & b) const { 
		return data.less( a , b );
	}
};


void Mesh::createGraph(std::vector<size_t> & order) 
{
	order.resize( data.totalSize );
	
	for (uint i = 0; i < order.size(); i++) 
		order[i] = i;
	
	sort( order.begin() , order.end(), AscendingOrder(data) );
}

void Mesh::getNeighbors(size_t i, std::vector<size_t>& n) 
{
	uint x,y,z;
	data.convertIndex( i, x, y, z );
	if (x == 0xffffffff || y == 0xffffffff || z == 0xffffffff)
		return;
	x--;
	if (x < data.size[0]) {
		n.push_back( data.convertIndex(x, y, z) );
	}
	x += 2;
	if (x < data.size[0]) {
		n.push_back( data.convertIndex(x, y, z) );
	}
	x--;

	y--;
	if (y < data.size[1]) {
		n.push_back( data.convertIndex(x, y, z) );
	}
	y += 2;
	if (y < data.size[1]) {
		n.push_back( data.convertIndex(x, y, z) );
	}
	y--;

	z--;
	if (z < data.size[2]) {
		n.push_back( data.convertIndex(x, y, z) );
	}
	z += 2;
	if (z < data.size[2]) {
		n.push_back( data.convertIndex(x, y, z) );
	}
	z--;
	if ( ((x+y+z) & 1) != ODD_TET_PARITY ) {
		find18Neighbors(x,y,z,n);
	}
}

void Mesh::find18Neighbors( uint x, uint y, uint z, std::vector< size_t > & neighbors) 
{
	x--;
	if (x < data.size[0]) {
		y--;
		if (y < data.size[1]) {
			neighbors.push_back( data.convertIndex(x, y, z) );
		}
		y += 2;
		if (y < data.size[1]) {
			neighbors.push_back( data.convertIndex(x, y, z) );
		}
		y--;

		z--;
		if (z < data.size[2]) {
			neighbors.push_back( data.convertIndex(x, y, z) );
		}
		z += 2;
		if (z < data.size[2]) {
			neighbors.push_back( data.convertIndex(x, y, z) );
		}
		z--;
	}

	x += 2; 
	if (x < data.size[0]) {
		y--;
		if (y < data.size[1]) {
			neighbors.push_back( data.convertIndex(x, y, z) );
		}
		y += 2;
		if (y < data.size[1]) {
			neighbors.push_back( data.convertIndex(x, y, z) );
		}
		y--;

		z--;
		if (z < data.size[2]) {
			neighbors.push_back( data.convertIndex(x, y, z) );
		}
		z += 2;
		if (z < data.size[2]) {
			neighbors.push_back( data.convertIndex(x, y, z) );
		}
		z--;
	}
	x--;

	y--;
	if (y < data.size[1]) {
		z--;
		if (z < data.size[2]) {
			neighbors.push_back( data.convertIndex(x, y, z) );
		}
		z += 2;
		if (z < data.size[2]) {
			neighbors.push_back( data.convertIndex(x, y, z) );
		}
		z--;
	}
	
	y += 2;
	if (y < data.size[1]) {
		z--;
		if (z < data.size[2]) {
			neighbors.push_back( data.convertIndex(x, y, z) );
		}
		z += 2;
		if (z < data.size[2]) {
			neighbors.push_back( data.convertIndex(x, y, z) );
		}
		z--;
	}
}
