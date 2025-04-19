#pragma once
#include <map>
#include <vector>
#include "Cordinate.h"
#include "CMyList.h"
using namespace std;



class EdgeItem {
public:
	int ymax;
	float x;
	float deltax;
	EdgeItem(int ymax, float x, float deltax) : ymax(ymax), x(x), deltax(deltax) {}
	EdgeItem() :ymax(0), x(0), deltax(0) {}
	EdgeItem(Cordinate<int>* a, Cordinate<int>* b);
};

class EdgeTable
{
private:
	map<int, MyList<EdgeItem>* > edgeItemsOfEveryScanline;
	int scanBottom;
	int scanTop;
public:
	EdgeTable(int scanBottom, int scanTop);
	EdgeTable(vector<Cordinate<int>*>* const cordinatesOfVertices);
	~EdgeTable();
	void initScanlineMap(int scanBottom, int scanTop);
	void print();
	MyList<EdgeItem>* getEdgeItemsOfScanline(int y);
	void insertEdgeItemToScanline(int y,EdgeItem ei);
	void setEdgeItemsOfScanline(int y,MyList<EdgeItem>* assignment);
	EdgeTable* buildEffectiveTable();
	static vector<Cordinate<int>*>* getFillPoints(EdgeTable* effectiveTable);
};


