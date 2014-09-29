#include <iostream>
#include "Graphic.h"

//Point::Point()
//{
//	node = 0;
//	dis = 0;
//}
//
//Point::Point(int n, disType d)
//{
//	node = n;
//	dis = d;
//}

Edge::Edge()
{
	startPoint = 0;
	endPoint = 0;
}

Edge::Edge(int s, int e)
{
	startPoint = s;
	endPoint = e;
}

Graphic::Graphic(int nodes, std::vector<Edge> inputEdge):n(nodes),graphMatrix(nodes, std::vector<int>(nodes, 0))
{
	int i = 0;
	for(std::vector<Edge>::iterator iter = inputEdge.begin(); iter != inputEdge.end(); ++iter)
	{
		++i;
		graphMatrix[(*iter).startPoint][(*iter).endPoint] = 1;
		graphMatrix[(*iter).endPoint][(*iter).startPoint] = 1;
	}

}
