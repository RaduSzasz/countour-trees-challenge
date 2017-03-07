#include "Mesh.h"

#include <iostream>
#include <parallel/algorithm>

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


size_t* Mesh::createGraph() 
{
	size_t *order = new size_t[data.totalSize];
	
	for (uint i = 0; i < data.totalSize; i++) 
		order[i] = i;
	
	__gnu_parallel::sort( order, order + data.totalSize, AscendingOrder(data) );
	return order;
}

size_t Mesh::getNeighbors(size_t i, size_t *n) 
{
	size_t curr_idx = 0;
	uint x,y,z;
	data.convertIndex( i, x, y, z );
	x--;
	if (x < data.size[0]) {
		n[curr_idx++] = data.convertIndex(x, y, z); 
	}
	x += 2;
	if (x < data.size[0]) {
		n[curr_idx++] = data.convertIndex(x, y, z);
	}
	x--;

	y--;
	if (y < data.size[1]) {
		n[curr_idx++] = data.convertIndex(x, y, z);
	}
	y += 2;
	if (y < data.size[1]) {
		n[curr_idx++] = data.convertIndex(x, y, z);
	}
	y--;

	z--;
	if (z < data.size[2]) {
		n[curr_idx++] = data.convertIndex(x, y, z);
	}
	z += 2;
	if (z < data.size[2]) {
		n[curr_idx++] = data.convertIndex(x, y, z);
	}
	z--;
	if ( ((x+y+z) & 1) != ODD_TET_PARITY ) {
		find18Neighbors(x, y, z, n, curr_idx);
	}
	return curr_idx;
}

void Mesh::find18Neighbors( uint x, uint y, uint z, size_t* neighbors, size_t &curr_idx) 
{
	x--;
	if (x < data.size[0]) {
		y--;
		if (y < data.size[1]) {
			neighbors[curr_idx++] = data.convertIndex(x, y, z);
		}
		y += 2;
		if (y < data.size[1]) {
			neighbors[curr_idx++] = data.convertIndex(x, y, z);
		}
		y--;

		z--;
		if (z < data.size[2]) {
			neighbors[curr_idx++] = data.convertIndex(x, y, z);
		}
		z += 2;
		if (z < data.size[2]) {
			neighbors[curr_idx++] = data.convertIndex(x, y, z);
		}
		z--;
	}

	x += 2; 
	if (x < data.size[0]) {
		y--;
		if (y < data.size[1]) {
			neighbors[curr_idx++] = data.convertIndex(x, y, z);
		}
		y += 2;
		if (y < data.size[1]) {
			neighbors[curr_idx++] = data.convertIndex(x, y, z);
		}
		y--;

		z--;
		if (z < data.size[2]) {
			neighbors[curr_idx++] = data.convertIndex(x, y, z);
		}
		z += 2;
		if (z < data.size[2]) {
			neighbors[curr_idx++] = data.convertIndex(x, y, z);
		}
		z--;
	}
	x--;

	y--;
	if (y < data.size[1]) {
		z--;
		if (z < data.size[2]) {
			neighbors[curr_idx++] = data.convertIndex(x, y, z);
		}
		z += 2;
		if (z < data.size[2]) {
			neighbors[curr_idx++] = data.convertIndex(x, y, z);
		}
		z--;
	}
	
	y += 2;
	if (y < data.size[1]) {
		z--;
		if (z < data.size[2]) {
			neighbors[curr_idx++] = data.convertIndex(x, y, z);
		}
		z += 2;
		if (z < data.size[2]) {
			neighbors[curr_idx++] = data.convertIndex(x, y, z);
		}
		z--;
	}
}
