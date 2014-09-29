# ifndef _GRAPHIC_H_
#define _GRAPHIC_H_
#include <iostream>
#include <vector>
using std::vector;
//typedef float disType;

//class Point{
//	int node;
//	disType dis; 
//	Point();
//	Point(int n, disType d);
//};

class Edge{
public:
	int startPoint;
	int endPoint;

	Edge();
	Edge(int s, int e);
};

class Graphic{
public:
	int n;
	std::vector<std::vector<int> > graphMatrix;
	/*std::vector<std::vector<int> > Nwk;
	std::vector<std::vector<Point> > DFTable;*/

	//void Floyd();
	//void Dijstra();

	Graphic(int nodes, std::vector<Edge> inputEdge);
};

#endif