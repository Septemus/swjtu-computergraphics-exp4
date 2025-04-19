#include "pch.h"
#include "EdgeTable.h"
EdgeTable::EdgeTable(int scanBottom, int scanTop):scanBottom(scanBottom),scanTop(scanTop) {
	initScanlineMap(scanBottom, scanTop);
}

void EdgeTable::initScanlineMap(int scanBottom, int scanTop) {
	for (int i = scanBottom;i <= scanTop;++i) {
		edgeItemsOfEveryScanline.insert(
			{
				i,
				new MyList<EdgeItem>()
			}
		);
	}
}

EdgeTable::~EdgeTable() {
	for (int i = scanBottom;i < scanTop;++i) {
		delete edgeItemsOfEveryScanline.at(i);
	}
}



MyList<EdgeItem>* EdgeTable::getEdgeItemsOfScanline(int y) {
	return edgeItemsOfEveryScanline.at(y);
}
void EdgeTable::insertEdgeItemToScanline(int y,EdgeItem ei) {
	MyList<EdgeItem>* mylist=edgeItemsOfEveryScanline.at(y);
	ListItem<EdgeItem>* ptr = mylist->head;
	boolean found = false;
	while (ptr->next) {
		ListItem<EdgeItem>* ptrNxt = ptr->next;
		if (ei.x < ptrNxt->value.x || ei.x == ptrNxt->value.x && ei.deltax < ptrNxt->value.deltax) {
			ptr->next = new ListItem<EdgeItem>(ei);
			ptr->next->next = ptrNxt;
			found = true;
			break;
		}
		ptr = ptr->next;
	}
	if (!found) {
		ptr->next = new ListItem<EdgeItem>(ei);
	}
}

void EdgeTable::setEdgeItemsOfScanline(int y,MyList<EdgeItem>* assignment) {
	ListItem<EdgeItem>* ptr = assignment->head;
	while (ptr->next) {
		ListItem<EdgeItem>* target = ptr->next;
		insertEdgeItemToScanline(y, target->value);
		ptr = ptr->next;
	}
	
}

EdgeTable* EdgeTable::buildEffectiveTable() {
	EdgeTable* effectiveTable = new EdgeTable(scanBottom, scanTop);
	MyList<EdgeItem>* lastScanline = NULL;
	MyList<EdgeItem>* curScanline = NULL;
	for (map<int, MyList<EdgeItem>* >::iterator i = edgeItemsOfEveryScanline.begin();i != edgeItemsOfEveryScanline.end();++i) {
		curScanline = (*i).second->fork();
		int curY = (*i).first;
		if (lastScanline) {
			ListItem<EdgeItem>* ptr = lastScanline->head;
			while (ptr->next) {
				ListItem<EdgeItem>* target = ptr->next;
				if (curY <= ptr->next->value.ymax) {
					curScanline->push(*new EdgeItem(target->value.ymax, target->value.x + target->value.deltax, target->value.deltax));
				}
				ptr = ptr->next;
			}
		}
		effectiveTable->setEdgeItemsOfScanline(curY, curScanline);
		lastScanline = curScanline;
	}
	effectiveTable->print();
	return effectiveTable;
}

EdgeTable::EdgeTable(vector<Cordinate<int>*>* const cordinatesOfVertices) {
	int ymax = 0, ymin = INT32_MAX;
	Cordinate<int>* last = NULL;
	Cordinate<int>* first = NULL;
	vector<pair<int,EdgeItem>>* vec = new vector<pair<int, EdgeItem>>();
	for (vector<Cordinate<int>*>::iterator i = cordinatesOfVertices->begin();i != cordinatesOfVertices->end();++i) {
		
		Cordinate<int>* current = (*i);
		ymin = min(ymin, current->getY());
		ymax = max(ymax, current->getY());
		if (last) {
			EdgeItem tmp = *new EdgeItem(last, current);
			vec->push_back({ min((int)(last->getY()+0.5),(int)(current->getY()+0.5)),tmp});
		}
		else {
			first = current;
		}
		last = current;
	}
	vec->push_back({ min((int)(last->getY() + 0.5),(int)(first->getY() + 0.5)),*new EdgeItem(last,first)});
	scanBottom = ymin;
	scanTop = ymax;
	initScanlineMap(ymin, ymax);
	for (vector<pair<int, EdgeItem>>::iterator i = vec->begin();i != vec->end();++i) {
		insertEdgeItemToScanline((*i).first, (*i).second);
	}
	delete vec;
}

EdgeItem::EdgeItem(Cordinate<int>* a, Cordinate<int>* b) {
	ymax = max(a->getY(), b->getY());
	x = a->getY() < b->getY() ? a->getX() : b->getX();
	if (a->getY() != b->getY()&&a->getX()!=b->getX()) {
		deltax = a->getX() < b->getX() ? 1 / ((float)(b->getY() - a->getY()) / (b->getX() - a->getX())) : 1 / ((float)(a->getY() - b->getY()) / (a->getX() - b->getX()));
	}
	else {
		deltax = 0;
	}
}
	

vector<Cordinate<int>*>* EdgeTable::getFillPoints(EdgeTable* effectiveTable) {
	vector<Cordinate<int>*>* ret = new vector<Cordinate<int>*>();
	for (map<int, MyList<EdgeItem>* >::iterator i = effectiveTable->edgeItemsOfEveryScanline.begin();i != effectiveTable->edgeItemsOfEveryScanline.end();++i) {
		int curIntersection = 0;
		
		ListItem<EdgeItem>* last = NULL;
		ListItem<EdgeItem>* ptr = (*i).second->head;
		int curY = (*i).first;
		while (ptr->next) {
			ListItem<EdgeItem>* cur = ptr->next;
			if (last) {
				if (fabs(last->value.x - cur->value.x) < 1e-2) {
					if (curY == cur->value.ymax && curY == last->value.ymax) {
						curIntersection += 1;
					}
					else if (curY < cur->value.ymax && curY < last->value.ymax) {
						curIntersection += 1;
					}
					else {
						curIntersection+=2;
					}
				}
				else {
					curIntersection += 1;
				}
				if (curIntersection % 2) {
					for (int i = (int)(last->value.x + 0.5);i <= (int)(cur->value.x + 0.5);++i) {
						ret->push_back(new Cordinate<int>(i, curY));
					}
				}
				
			}
			last = cur;
			ptr = ptr->next;
		}
	}
	return ret;
}
void EdgeTable::print() {
	CString msg = _T("");
	char buffer[4000];
	for (map<int, MyList<EdgeItem>* >::iterator i = edgeItemsOfEveryScanline.begin();i != edgeItemsOfEveryScanline.end();++i) {

		sprintf_s(buffer,"y:%d: ", (*i).first);
		ListItem<EdgeItem>* ptr = (*i).second->head;
		while (ptr->next) {
			sprintf_s(buffer,"%s |%d|%f|%f| -> ",buffer, ptr->next->value.ymax, ptr->next->value.x, ptr->next->value.deltax);
			ptr = ptr->next;
		}
		sprintf_s(buffer,"%s \n",buffer);
		TRACE("%s", buffer);
	}
}