#include "GraphicColoring.h"
#include <iostream>
#include <fstream>
using namespace std;

Graphic ReadInputGraph(char *fileName);

void GetNumPAndEdge(char *str, int &n, int &edge);

int main()
{
	char filePath[7][80] = {"D:\\Study\\Research\\GraphicColor\\DSJC125.1.col",
		"D:\\Study\\Research\\GraphicColor\\DSJC125.5.col",
		"D:\\Study\\Research\\GraphicColor\\DSJC125.9.col",
		"D:\\Study\\Research\\GraphicColor\\DSJC250.1.col",
		"D:\\Study\\Research\\GraphicColor\\DSJC250.5.col",
		"D:\\Study\\Research\\GraphicColor\\DSJC250.9.col",
		"D:\\Study\\Research\\GraphicColor\\DSJC500.1.col"
	};
	int k[9] = {5,17,44,8,28,72,12};
	for(int i = 0; i < 7; ++i)
	{
		cout << "the instance: " << i << endl;
		Graphic g = ReadInputGraph(filePath[i]);
		GraphicColoring gc(g, k[i]);
		gc.Solve();
		cout << "con : " << gc.bestObjVal << endl;
	}

	return 0;
}

Graphic ReadInputGraph(char *fileName)
{
	vector<Edge> edgeVec;
	int n,edge;
	fstream pf(fileName,ios::in);
	char str[100];
	pf.getline(str,100);
	while(str[0] == 'c')
	{
		pf.getline(str,100);
	}
	GetNumPAndEdge(str, n, edge);
	char cTemp;
	int startNode,endNode;
	while (pf >> cTemp >> startNode >> endNode)
	{
		Edge newEdge(startNode, endNode);
		edgeVec.push_back(newEdge);
	}
	pf.close();
	//start with 1,
	++n;
	Graphic g(n,edgeVec);
	return g;
}

void GetNumPAndEdge(char *str, int &n, int &edge)
{
	int numN = 0, numEdge = 0;
	int i = 0;
	/*for(i = 0; i < len; ++i)
	{
	if(str[i] >= '0' && str[i] <= '9')
	{
	break;
	}
	}*/
	while (!(str[i] >= '0' && str[i] <= '9'))
	{
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		numN = numN*10 + str[i] - '0';
		++i;
	}
	while (!(str[i] >= '0' && str[i] <= '9'))
	{
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		numEdge = numEdge*10 + str[i] - '0';
		++i;
	}
	n = numN;
	edge = numEdge;
	return;
}