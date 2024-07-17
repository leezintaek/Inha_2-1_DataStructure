#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Vertex{
    int vertexId;
    int matrixId;
    Vertex* next;
    Vertex* prev;

    Vertex(){
        vertexId = matrixId = -1;
        next = prev = nullptr;
    }

    Vertex(int vertexId){
        this->vertexId = vertexId;
        matrixId = -1;
        next = prev = nullptr;
    }
};

struct Edge{
    Vertex* src;
    Vertex* dst;
    Edge* next;
    Edge* prev;

    Edge(){
        src = dst = nullptr;
        next = prev = nullptr;
    }

    Edge(Vertex* src, Vertex* dst){
        this->src = src;
        this->dst = dst;
        next = prev = nullptr;
    }
};

class VertexList{
private:
    Vertex* head;
    Vertex* tail;
public:
    VertexList();
    void insertVertex(Vertex* newVertex);
    void eraseVertex(Vertex* delVertex);
    Vertex* findVertex(int findVertexId);
    Vertex* best(){
        Vertex* curVertex = head->next;
        Vertex* bestVertex = nullptr;
        int num = 0;
        for(; curVertex!= tail; curVertex = curVertex->next){
            if(curVertex->vertexId>num){
                bestVertex = curVertex;
                num = curVertex->vertexId;
            }
        }
        return bestVertex;
    }
};

VertexList::VertexList(){
    head = new Vertex;
    tail = new Vertex;
    head->next = tail;
    tail->prev = head;

    head->matrixId = -1;
}

void VertexList::insertVertex(Vertex* newVertex){
    newVertex->prev = tail->prev;
    newVertex->next = tail;

    newVertex->matrixId = tail->prev->matrixId + 1;

    tail->prev->next = newVertex;
    tail->prev = newVertex;
}

void VertexList::eraseVertex(Vertex* delVertex){
    for(Vertex* curVertex = delVertex; curVertex!=tail; curVertex = curVertex->next){
        curVertex->matrixId--;
    }

    delVertex->prev->next = delVertex->next;
    delVertex->next->prev = delVertex->prev;
    delete delVertex;
}

Vertex* VertexList::findVertex(int findVertexId){
    for(Vertex* curVertex = head->next; curVertex!=tail; curVertex = curVertex->next){
        if(curVertex->vertexId==findVertexId){
            return curVertex;
        }
    }
    return nullptr;
}

class EdgeList{
private:
    Edge* head;
    Edge* tail;
public:
    EdgeList();
    void insertEdge(Edge* newEdge);
    void eraseEdge(Edge* delEdge);
};

EdgeList::EdgeList(){
    head = new Edge;
    tail = new Edge;
    head->next = tail;
    tail->prev = head;
}

void EdgeList::insertEdge(Edge* newEdge){
    newEdge->prev = tail->prev;
    newEdge->next = tail;
    tail->prev->next = newEdge;
    tail->prev = newEdge;
}

void EdgeList::eraseEdge(Edge* delEdge){
    delEdge->prev->next = delEdge->next;
    delEdge->next->prev = delEdge->prev;
}

class Graph{
private:
    VertexList vertexList;
    EdgeList edgeList;
    vector<vector<Edge*> > edgeMatrix;
public:
    void insertVertex(int vertexId);
    void eraseVertex(int vertexId);
    void insertEdge(int srcVertexId, int dstVertexId);
    void eraseEdge(int srcVertexId, int dstVertexId);
    void isAdjacent(int vertexId1, int vertexId2);
    void maxVertexInfo();
};

void Graph::insertVertex(int vertexId){
    if(vertexList.findVertex(vertexId)){
        cout << "Exist" << endl;
        return;
    }

    Vertex* newVertex = new Vertex(vertexId);

    for(int i=0; i<edgeMatrix.size(); i++){
        edgeMatrix[i].push_back(nullptr);
    }
    edgeMatrix.push_back(vector<Edge*> (edgeMatrix.size()+1, nullptr));

    vertexList.insertVertex(newVertex);
}

void Graph::eraseVertex(int vertexId){
    Vertex* delVertex = vertexList.findVertex(vertexId);
    if(!delVertex){
        return;
    }

    int matrixId = delVertex->matrixId; // 지우려는 노드의 행렬 위치
    for(int i=0; i<edgeMatrix.size(); i++){
        if(i!=matrixId){
        // 지우려는 정점의 위치의 행은 제외 -> 따로 하나하나 edge를 제거해야 한다
            if(edgeMatrix[i][matrixId]){
                edgeList.eraseEdge(edgeMatrix[i][matrixId]);
            }
            edgeMatrix[i].erase(edgeMatrix[i].begin() + matrixId);
        }
    }
    int sizeF = edgeMatrix.size();
    for(int i=0; i<sizeF; i++){
        if(edgeMatrix[matrixId][i]!=nullptr){
            edgeList.eraseEdge(edgeMatrix[matrixId][i]);
        }
    }

    edgeMatrix.erase(edgeMatrix.begin() + matrixId);
    vertexList.eraseVertex(delVertex);
}

void Graph::insertEdge(int srcVertexId, int dstVertexId){
    Vertex* src = vertexList.findVertex(srcVertexId);
    Vertex* dst = vertexList.findVertex(dstVertexId);
    if(!src || !dst){
        return;
    }

    int srcMatrixId = src->matrixId;
    int dstMatrixId = dst->matrixId;

    if(edgeMatrix[srcMatrixId][dstMatrixId] || edgeMatrix[dstMatrixId][srcMatrixId]){
        cout << "Exist" << endl;
        return;
    }

    Edge* newEdge = new Edge(src, dst);
    edgeList.insertEdge(newEdge);
    edgeMatrix[srcMatrixId][dstMatrixId] = edgeMatrix[dstMatrixId][srcMatrixId] = newEdge;
}

void Graph::eraseEdge(int srcVertexId, int dstVertexId){
    Vertex* src = vertexList.findVertex(srcVertexId);
    Vertex* dst = vertexList.findVertex(dstVertexId);
    if(!src || !dst){
        return;
    }

    int srcMatrixId = src->matrixId;
    int dstMatrixId = dst->matrixId;

    if(!edgeMatrix[srcMatrixId][dstMatrixId] || !edgeMatrix[dstMatrixId][srcMatrixId]){
        cout << "None" << endl;
        return;
    }

    edgeList.eraseEdge(edgeMatrix[srcMatrixId][dstMatrixId]);
    edgeMatrix[srcMatrixId][dstMatrixId] = edgeMatrix[dstMatrixId][srcMatrixId] = nullptr;
}

void Graph::isAdjacent(int vertexId1, int vertexId2){
    Vertex* srcVertex = vertexList.findVertex(vertexId1);
    Vertex* dstVertex = vertexList.findVertex(vertexId2);
    if(!srcVertex || !dstVertex)
        return;
    int srcMatrixId = srcVertex->matrixId;
    int dstMatrixId = dstVertex->matrixId;

    if(edgeMatrix[srcMatrixId][dstMatrixId] || edgeMatrix[dstMatrixId][srcMatrixId]){
        cout << "True" << " ";
    }
    else{
        cout << "False" << " ";
    }

    int srcCount = 0;
    int dstCount = 0;
    for(int a=0; a<edgeMatrix.size(); a++){
        if(edgeMatrix[srcMatrixId][a]){
            srcCount++;
        }
        if(edgeMatrix[dstMatrixId][a]){
            dstCount++;
        }
    }
    if(srcCount>dstCount){
        cout << vertexId1 << endl;
    }
    else if(srcCount<dstCount){
        cout << vertexId2 << endl;
    }
    else{
        cout << max(vertexId1, vertexId2) << endl;
    }
}

void Graph::maxVertexInfo(){
    Vertex* curVertex = vertexList.best();
    if(!curVertex){
        cout << -1 << endl;
        return;
    }
    cout << curVertex->vertexId << " ";
    int matrixId = curVertex->matrixId;
    int count = 0;

    for(int a=0; a<edgeMatrix.size(); a++){
        if(edgeMatrix[matrixId][a]){
            count++;
        }
    }
    cout << count << endl;
}

///

int main(){
    Graph graph;
    int order;
    cin >> order;
    while(order--){
        string input; cin >> input;
        if(input=="insertVertex"){
            int S; cin >> S;
            graph.insertVertex(S);
        }
        if(input=="insertEdge"){
            int S, D; cin >> S >> D;
            graph.insertEdge(S, D);
        }
        if(input=="eraseVertex"){
            int S; cin >> S;
            graph.eraseVertex(S);
        }
        if(input=="eraseEdge"){
            int S, D; cin >> S >> D;
            graph.eraseEdge(S, D);
        }
        if(input=="isAdjacent"){
            int S, D; cin >> S >> D;
            graph.isAdjacent(S, D);
        }
        if(input=="maxVertexInfo"){
            graph.maxVertexInfo();
        }
    }
}