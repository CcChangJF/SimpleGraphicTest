#include <iostream>
#include "GraphicColoring.h"
#include <vector>
#include <ctime>

using std::vector;

bool EquiprobabilitySelect(float probability);
void CompareAndChoose(int delt, int &count, int i, int k, int &bestNode, int &bestColor, int &bestDeltObj);

GraphicColoring::GraphicColoring(Graphic g, int k):graph(g),sol(g.n, 0),adjacentTable(g.n, vector<int>(k,0)),tabuTable(g.n, vector<int>(k,0))
{
	bestObjVal = 0;
	objVal = 0;
	numOfColor = k;
}

void GraphicColoring::Solve()
{
	int testobj;

	srand(int(time(0)));
	InitialSolution();
	InitialAdjacentTable();
	bestObjVal = objVal = GetObjVal();
	int bestNodeNonTabu,bestColorNonTabu,bestDeltObjNonTabu;
	int bestNodeTabu, bestColorTabu,bestDeltObjTabu;
	int bestNode,bestColor,bestDeltObj;
	int iteration = 0;
	while(!IsAcceptanceCriterionSatisfied())
	{
		++iteration;
		//output every 10000 iterations.
		if(iteration % 10000 == 0)
		{
			std::cout << "iter : " << iteration << ", con = " << objVal << std::endl;
		}
		//end output.

		/////
		////
		////should carefully check this part code case the tabu never occurs.
		////
		////

		GetBestMove(iteration, bestNodeNonTabu,bestColorNonTabu,bestDeltObjNonTabu,bestNodeTabu,bestColorTabu,bestDeltObjTabu);
		//if tabu better than  the history
		if( bestDeltObjTabu < bestDeltObjNonTabu  && objVal + bestDeltObjTabu < bestObjVal)
		{
			bestNode = bestNodeTabu;
			bestColor = bestColorTabu;
			bestDeltObj = bestDeltObjTabu;
			std::cout << "tabu at: " << iteration << std::endl;

		}
		// else if
		else
		{
			bestNode = bestNodeNonTabu;
			bestColor = bestColorNonTabu;
			bestDeltObj = bestDeltObjNonTabu;
		}
		//do the change
		UpdateAdjacentTable(bestNode,bestColor);
		UpdateTabuTable(bestNode,iteration);
		UpdateSolution(bestNode,bestColor,bestDeltObj);
		if(bestObjVal > objVal)
		{
			bestObjVal = objVal;
		}
		testobj = GetObjVal();
		if(testobj != objVal)
		{
			std::cout << "wrong at: " << iteration << std::endl;
		}
	}
	return ;
}

void GraphicColoring::InitialSolution()
{
	for(int i = 1; i < graph.n; ++i)
	{
		sol[i] = rand()%numOfColor;
	}
	return;
}

void GraphicColoring::InitialAdjacentTable()
{
	for(int i = 1; i < graph.n; ++i)
	{
		for(int k = 0; k < numOfColor; ++k)
		{
			for(int j = 1; j < graph.n; ++j)
			{
				if(graph.graphMatrix[i][j] == 1 && k == sol[j])
				{
					++adjacentTable[i][k];
				}
			}
		}
	}
	return;
}

bool GraphicColoring::IsNodeConflict(int node)
{
	if(adjacentTable[node][sol[node]] > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int GraphicColoring::GetObjVal()
{
	int obj = 0;
	for(int i = 1; i < graph.n; ++i)
	{
		obj += adjacentTable[i][sol[i]];
	}
	return obj/2;
}

bool GraphicColoring::IsAcceptanceCriterionSatisfied()
{
	if(objVal > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void GraphicColoring::GetBestMove(int iter, int &bestNodeNonTabu, int &bestColorNonTabu, int &bestDeltObjNonTabu, int &bestNodeTabu, int &bestColorTabu, int &bestDeltObjTabu)
{
	int delt;
	bestDeltObjNonTabu = bestDeltObjTabu = INT_MAX;
	int countNonTabu = 0, countTabu = 0;
	for(int i = 1; i < graph.n; ++i)
	{
		if(IsNodeConflict(i))
		{
			for(int k = 0; k < numOfColor; ++k)
			{
				if(sol[i] != k)
				{
					// tabu
					if( tabuTable[i][k] > iter)
					{
						delt =  adjacentTable[i][k] - adjacentTable[i][sol[i]];
						CompareAndChoose(delt,countTabu,i,k,bestNodeTabu,bestColorTabu,bestDeltObjTabu);
					}
					//non tabu
					else
					{
						delt =  adjacentTable[i][k] - adjacentTable[i][sol[i]];
						CompareAndChoose(delt,countNonTabu,i,k,bestNodeNonTabu,bestColorNonTabu,bestDeltObjNonTabu);
					}
				}

			}
		}
	}
	return;
}

//void CompareAndChoose(int delt, int count, int i, int k, int &bestNodeNonTabu, int &bestColorNonTabu, int &bestDeltObjNonTabu, int &bestNodeTabu, int &bestColorTabu, int &bestDletObjTabu)
//void CompareAndChoose(int delt, int count, int i, int k, int &bestNodeNonTabu, int &bestColorNonTabu, int &bestDeltObjNonTabu, int &bestNodeTabu, int &bestColorTabu, int &bestDletObjTabu)
//{
//
//	if(bestDeltObjNonTabu > delt)
//	{
//		count = 1;
//		bestNodeNonTabu = i;
//		bestColorNonTabu = k;
//		bestDeltObjNonTabu = delt;
//	}
//	else if( bestDeltObjNonTabu == delt )
//	{
//		++count;
//		if(EquiprobabilitySelect(1.0/count))
//		{
//			bestNodeNonTabu = i;
//			bestColorNonTabu = k;
//			bestDeltObjNonTabu = delt;
//		}
//	}
//	return;
//}

bool EquiprobabilitySelect(double probability)
{
	if(1.0*rand()/RAND_MAX < probability)
	{
		return true;
	} 
	else
	{
		return false;
	}
}

void CompareAndChoose(int delt, int &count, int i, int k, int &bestNode, int &bestColor, int &bestDeltObj)
{
	if(bestDeltObj > delt)
	{
		count = 1;
		bestNode = i;
		bestColor = k;
		bestDeltObj = delt;
	}
	else if( bestDeltObj == delt )
	{
		++count;
		if(EquiprobabilitySelect(1.0/count))
		{
			bestNode = i;
			bestColor = k;
			bestDeltObj = delt;
		}
	}
	return;
}

void GraphicColoring::UpdateAdjacentTable(int node, int color)
{
	for(int i = 1; i < graph.n; ++i)
	{
		if(graph.graphMatrix[node][i] == 1)
		{
			++adjacentTable[i][color];
			--adjacentTable[i][sol[node]];
		}
	}
	return;
}

void GraphicColoring::UpdateSolution(int node, int col, int delt)
{
	sol[node] = col;
	objVal = objVal + delt;
	return;
}

void GraphicColoring::UpdateTabuTable(int node, int iter)
{
	tabuTable[node][sol[node]] = iter + rand()%5 + objVal;
	return;
}


