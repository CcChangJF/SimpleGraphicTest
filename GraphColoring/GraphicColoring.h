# ifndef _GRAPHICCOLORING_H_
# define _GRAPHICCOLORING_H_

#include "Graphic.h"

using std::vector;

class GraphicColoring{
public:
	Graphic graph;
	int numOfColor;
	vector<int> sol;
	vector<vector<int> > adjacentTable;
	vector<vector<int> > tabuTable;
	int bestObjVal;
	int objVal;

	void Solve();
	void PrintResult();

	GraphicColoring(Graphic g, int k);

private:
	vector<Edge> ReadInputGraph();
	int GetObjVal();
	bool IsAcceptanceCriterionSatisfied();
	void GetBestMove(int iter, int &bestNodeNonTabu, int &bestColorNonTabu, int &bestDeltObjNonTabu, int &bestNodeTabu, int &bestColorTabu, int &bestDletObjTabu);
	void UpdateAdjacentTable(int node, int color);
	void UpdateSolution(int node, int col, int delt);
	void UpdateTabuTable(int node, int iter);
	void InitialAdjacentTable();
	bool IsNodeConflict(int node);
	void InitialSolution();
};

#endif