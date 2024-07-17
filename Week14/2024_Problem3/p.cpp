#include <iostream>
#include <vector>

using namespace std;

class vertex {
public:
	int id;
	int degree;
	vector<int> edgeList;

	vertex(int i) {
		id = i;
		degree = 0;
	}

	bool insertEdge(int vId) {
		for (int i = 0; i < edgeList.size(); i++) {
			if (edgeList[i] == vId) {
				return false;
			}
		}
		degree++;
		edgeList.push_back(vId);
		return true;
	}

	bool eraseEdge(int vId) {
		for (int i = 0; i < edgeList.size(); i++) {
			if (edgeList[i] == vId) {
				edgeList.erase(edgeList.begin() + i);
				degree--;
				return true;
			}
		}
		return false;
	}
};


class Graph {
	int id;
	vector<vertex*> verList;

public:
	Graph(int i) {
		id = i;
	}

	vertex* findVertex(int id) {
		for (int i = 0; i < verList.size(); i++) {
			if (verList[i]->id == id) return verList[i];
		}

		return NULL;
	}

	void insertVertex(int id) {
		if (findVertex(id) != NULL) {
			cout << "ERRORCODE 01" << '\n';

			return;
		}

		vertex* newVer = new vertex(id);
		verList.push_back(newVer);
	}
	
	void eraseVertex(int id) {
		if (findVertex(id) == NULL) {
			cout << "ERRORCODE 03\n";

			return;
		}

		vertex* delV = findVertex(id);

		for (int i = 0; i < delV->edgeList.size(); i++) {
			vertex* cur = findVertex(delV->edgeList[i]);

			cur->eraseEdge(id);
		}

		for (int i = 0; i < verList.size(); i++) {
			if (verList[i]->id == delV->id) {
				verList.erase(verList.begin() + i);
			}
		}

		delete delV;
	}
	
	void insertEdge(int src, int dst) {
		vertex* srcV = findVertex(src);
		vertex* dstV = findVertex(dst);


		if (srcV == NULL || dstV == NULL) {
			cout << "ERRORCODE 03\n";
			return;
		}

		if (!srcV->insertEdge(dst)) {
			cout << "ERRORCODE 02\n";
			return;
		}
		
		dstV->insertEdge(src);
	}

	void eraseEdge(int src, int dst) {
		vertex* srcV = findVertex(src);
		vertex* dstV = findVertex(dst);

		if (srcV == NULL || dstV == NULL) {
			cout << "ERRORCODE 03\n";
			return;
		}

		if (!srcV->eraseEdge(dst)) {
			cout << "ERRORCODE 04\n";
			return;
		}

		dstV->eraseEdge(src);
	}

	void printAdjCount(int x) {
		vertex* cur = findVertex(x);

		if (cur == NULL) {
			cout << "ERRORCODE 03\n";
			return;
		}

		cout << cur->edgeList.size() << "\n";
	}

	void printAdjMinMax(int x) {
		vertex* cur = findVertex(x);

		if (cur == NULL) {
			cout << "ERRORCODE 03\n";
			return;
		}

		if (cur->edgeList.size() == 0) {
			cout << "-1" << '\n';
			return;
		}

		int min = 1000001;
		int max = 99999;

		for (int i = 0; i < cur->edgeList.size(); i++) {
			if (cur->edgeList[i] > max) max = cur->edgeList[i];
			if (cur->edgeList[i] < min) min = cur->edgeList[i];
		}

		cout << min << " " << max << '\n';
	}

	int getId() {
		return id;
	}
};

int main() {
	int n;

	cin >> n;

	vector<Graph> g;

	string cmd;
	int x, y, z;

	while (n--) {
		cin >> cmd;

		if (cmd == "Graph") {
			cin >> x;

			g.push_back(Graph(x));
		}
		else if (cmd == "InsertVertex") {
			cin >> x >> y;

			for (int i = 0; i < g.size(); i++) {
				if (g[i].getId() == x) {
					g[i].insertVertex(y);
				}
			}
		}
		else if (cmd == "InsertEdge") {
			cin >> x >> y >> z;
			
			for (int i = 0; i < g.size(); i++) {
				if (g[i].getId() == x) {
					g[i].insertEdge(y, z);
				}
			}
		}
		else if (cmd == "EraseVertex") {
			cin >> x >> y;

			for (int i = 0; i < g.size(); i++) {
				if (g[i].getId() == x) {
					g[i].eraseVertex(y);
				}
			}
		}
		else if (cmd == "EraseEdge") {
			cin >> x >> y >> z;

			for (int i = 0; i < g.size(); i++) {
				if (g[i].getId() == x) {
					g[i].eraseEdge(y, z);
				}
			}
		}
		else if (cmd == "PrintAdjCount") {
			cin >> x >> y;

			for (int i = 0; i < g.size(); i++) {
				if (g[i].getId() == x) {
					g[i].printAdjCount(y);
				}
			}
		}
		else if (cmd == "PrintAdjMinMax") {
			cin >> x >> y;

			for (int i = 0; i < g.size(); i++) {
				if (g[i].getId() == x) {
					g[i].printAdjMinMax(y);
				}
			}
		}

	}
}