#include <iostream>
#include <vector>
using namespace std;

#define FRIEND 1
#define STRANGER 0

struct Vertex{
    int vertexId;
    int matrixId;
    Vertex* next;
    Vertex* prev;
    Vertex* connect;

    bool check = false;

    Vertex(){
        vertexId = matrixId = -1;
        next = prev = nullptr;
        connect = nullptr;
    }
    Vertex(int vertexId){
        this->vertexId = vertexId;
        matrixId = -1;
        next = prev = nullptr;
        connect = nullptr;
    }
};

struct Edge{
    Vertex* src;
    Vertex* dst;
    Edge* next;
    Edge* prev;

    int state;

    Edge(){
        src = dst = nullptr;
        next = prev = nullptr;
        state = STRANGER;
    }
    Edge(Vertex* src, Vertex* dst){
        this->src = src;
        this->dst = dst;
        next = prev = nullptr;
        state = STRANGER;
    }
};

class VertexList{
private:
    Vertex* head;
    Vertex* tail;

public:
    VertexList();
    void insertVertex(Vertex* newVertex);
    Vertex* findVertex(int vertexId);
};

VertexList::VertexList(){
    head = new Vertex;
    tail = new Vertex;
    head->next = tail;
    tail->prev = head;

    head->matrixId = -1;
}

void VertexList::insertVertex(Vertex* newVertex){
    newVertex->matrixId = tail->prev->matrixId + 1;
    //matrixId를 tail이전의 노드보다 +1
    newVertex->prev = tail->prev;
    newVertex->next = tail;
    tail->prev->next = newVertex;
    tail->prev = newVertex;
}

Vertex* VertexList::findVertex(int vertexId){
    for(Vertex* curVertex = head->next; curVertex != tail; curVertex = curVertex->next){
        if(curVertex->vertexId==vertexId){
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

class Graph{
private:
    vector<vector<Edge*> > edgeMatrix;
    VertexList vertexList;
    EdgeList edgeList;
public:
    void insertVertex(int vertexId);
    void insertEdge(int srcVertexId, int dstVertexId, int state);
    void connectVertex(int vertexId1);
    void findFriend(int vertexId1, int distance);
    bool checkNone(vector<int> checkList, int checkNum);
};

void Graph::insertVertex(int vertexId){
    if(vertexList.findVertex(vertexId))
        return;

    Vertex* newVertex = new Vertex(vertexId);
    for(int firstFriend=0; firstFriend<edgeMatrix.size(); firstFriend++){
        edgeMatrix[firstFriend].push_back(nullptr);
    }
    edgeMatrix.push_back(vector<Edge*> (edgeMatrix.size()+1, nullptr));
    vertexList.insertVertex(newVertex);
}

void Graph::insertEdge(int srcVertexId, int dstVertexId, int state){
    Vertex* srcVertex = vertexList.findVertex(srcVertexId);
    Vertex* dstVertex = vertexList.findVertex(dstVertexId);
    if(!srcVertex || !dstVertex)
        return;

    int srcMatrixId = srcVertex->matrixId;
    int dstMatrixId = dstVertex->matrixId;
    if(edgeMatrix[srcMatrixId][dstMatrixId] || edgeMatrix[dstMatrixId][srcMatrixId])
        return;

    Edge* newEdge = new Edge(srcVertex, dstVertex);
    newEdge->state = state;
    edgeMatrix[srcMatrixId][dstMatrixId] = edgeMatrix[dstMatrixId][srcMatrixId] = newEdge;
    edgeList.insertEdge(newEdge);
}

void Graph::connectVertex(int vertexId1){
    Vertex* curVertex = vertexList.findVertex(vertexId1);
    curVertex->check = true;
}

void Graph::findFriend(int vertexId, int distance){
    int point = 0;
    int miss = 0;
    Vertex* curVertex = vertexList.findVertex(vertexId);
    int matrixId = curVertex->matrixId;
    if(!curVertex)
        return;
    vector<int> friendList;
    ///
    int sizeF = edgeMatrix.size();
    for(int fir=0; fir<sizeF; fir++){
        if(fir!=matrixId){
            if((edgeMatrix[matrixId][fir]) && (edgeMatrix[matrixId][fir]->state==FRIEND)){
                Vertex* useVertex = (edgeMatrix[matrixId][fir]->src->vertexId==vertexId) ? edgeMatrix[matrixId][fir]->dst : edgeMatrix[matrixId][fir]->src;
                if(!useVertex->check){
                    point += 2;
                    miss--;
                }
                friendList.push_back(useVertex->vertexId);
                miss++;
            }
        }
    }
    ///1번 친구는 모드 찾아놓음(연동, 본인 예외처리)
    if(distance==2){
        int sizeE = edgeMatrix.size();
        for(int fir=0; fir<sizeE; fir++){ //뒤 노드
            for(int sec=0; sec<friendList.size(); sec++){
                Vertex* useVertex = (edgeMatrix[(friendList[sec]-1)][fir]->src->vertexId==vertexId) ? edgeMatrix[friendList[sec]-1][fir]->dst : edgeMatrix[friendList[sec]-1][fir]->src;
                if(!checkNone(friendList, useVertex->vertexId) || useVertex==curVertex || edgeMatrix[(friendList[sec]-1)][fir]->state!=FRIEND)
                    continue;
                if(!useVertex->check){
                    point += 1;
                    miss--;
                }
                friendList.push_back(useVertex->vertexId);
                miss++;
            }
        } //#1 2 #3(4, 5) 6  //+4 +
    }
    ///2번 친구 모두 찾아놓음(이미 존재, 본인, 연동 예외처리)

    if(friendList.size()==0){
        cout << -1;
        return;
    }
    cout << friendList.size()-miss << " " << point;
} // 1 2 / 5 12

bool Graph::checkNone(vector<int> checkList, int checkNum){
    int checkSize = checkList.size();
    for(int a=0; a<checkSize; a++){
        if(checkList[a]==checkNum){
            return false;
        }
    }
    return true;
}

///
int main(){
    Graph graph;
    int N, M, D; cin >> N >> M >> D;
    for(int firstFriend=1; firstFriend<=N; firstFriend++){
        graph.insertVertex(firstFriend);
    }
    while(D--){
        int vertex1; cin >> vertex1;
        graph.connectVertex(vertex1);
    }

    for(int a=1; a<=N; a++){
        for(int b=1; b<=N; b++){
            int state; cin >> state;
            graph.insertEdge(a, b, state);
        }
    }

    while(M--){
        int user, distance; cin >> user >> distance;
        graph.findFriend(user, distance);
        cout << endl;
    }
}