#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct vertex;
struct edge;
struct edgeNode;
class vertexList;

class edgeList{
public:
    edgeList();
    void insertEdge(edge* newEdge);
    void eraseEdge(edgeNode* delEdge);
    edgeNode* header;
    edgeNode* trailer;
};

struct vertex{
    int vertexId;
    int degree;
    vertex* prev;
    vertex* next;
    edgeList incidentEdge;

    bool visit = false;

    vertex(){
        vertexId = -1;
        degree = 0;
        prev = next = NULL;
    }
    vertex(int vertexId){
        this->vertexId = vertexId;
        degree = 0;
        prev = next = NULL;
    }
};

struct edge{
    vertex* srcVertex;
    vertex* dstVertex;
    edgeNode* srcIncidentEdgeNode;
    edgeNode* dstIncidentEdgeNode;
    edgeNode* totalEdgeNode;
    edge(){
        srcVertex = dstVertex = NULL;
    }
    edge(vertex* src, vertex* dst){
        this->srcVertex = src;
        this->dstVertex = dst;
    }
};

struct edgeNode{
    edge* edgeInfo;
    edgeNode* prev;
    edgeNode* next;
    edgeNode(){
        edgeInfo = NULL;
        prev = next = NULL;
    }
    edgeNode(edge* edgeInfo){
        this->edgeInfo = edgeInfo;
        prev = next = NULL;
    }
};

class vertexList{
public:
    vertexList();
    void insertVertex(vertex* newVertex);
    void eraseVertex(vertex* delVertex);
    vertex* findVertex(int vertexId);
// private:
    vertex* header;
    vertex* trailer;
};

vertexList::vertexList(){
    header = new vertex();
    trailer = new vertex();
    header->next = trailer;
    trailer->prev = header;
}

void vertexList::insertVertex(vertex* newVertex){
    newVertex->prev = trailer->prev;
    newVertex->next = trailer;
    trailer->prev->next = newVertex;
    trailer->prev = newVertex;
}

void vertexList::eraseVertex(vertex* delVertex){
    delVertex->prev->next = delVertex->next;
    delVertex->next->prev = delVertex->prev;
    delete delVertex;
}

vertex* vertexList::findVertex(int vertexId){
    for(vertex* curVertex = header->next; curVertex != trailer; curVertex = curVertex->next){
        if(curVertex->vertexId == vertexId){
            return curVertex;
        }
    }
    return NULL;
}

// class edgeList{
// public:
//     edgeList();
//     void insertEdge(edge* newEdge);
//     void eraseEdge(edgeNode* delEdge);
//     edgeNode* header;
//     edgeNode* trailer;
// };

edgeList::edgeList(){
    header = new edgeNode();
    trailer = new edgeNode();
    header->next = trailer;
    trailer->prev = header;
}

void edgeList::insertEdge(edge* newEdge){
    edgeNode* newEdgeNode = new edgeNode(newEdge);
    newEdgeNode->prev = trailer->prev;
    newEdgeNode->next = trailer;
    trailer->prev->next = newEdgeNode;
    trailer->prev = newEdgeNode;
}

void edgeList::eraseEdge(edgeNode* delEdge){
    delEdge->prev->next = delEdge->next;
    delEdge->next->prev = delEdge->prev;
    delete delEdge;
}

class graph{
public:
    edge* findEdge(vertex* srcVertex, vertex* dstVertex);
    void insertVertex(int vertexId);
    void eraseVertex(int vertexId);
    void insertEdge(int srcVertexId, int delVertexId);
    void eraseEdge(int srvVertexId, int dstVertexId);

    void BFS(int vertexId, int& num);
    void DFS(vertex* curVertex, int& num);
    void DFScheck();

    vertexList vList;
    edgeList eList;
};

edge* graph::findEdge(vertex* srcVertex, vertex* dstVertex){
    if(srcVertex->degree < dstVertex->degree){
        for(edgeNode* curEdge = srcVertex->incidentEdge.header->next; curEdge != srcVertex->incidentEdge.trailer; curEdge = curEdge->next){
            if(curEdge->edgeInfo->dstVertex == dstVertex){
                return curEdge->edgeInfo;
            }
        }
    }
    else{
        for(edgeNode* curEdge = dstVertex->incidentEdge.header->next; curEdge != dstVertex->incidentEdge.trailer; curEdge = curEdge->next){
            if(curEdge->edgeInfo->dstVertex == srcVertex){
                return curEdge->edgeInfo;
            }
        }
    }
    return NULL;
}

void graph::insertVertex(int vertexId){
    if(vList.findVertex(vertexId) != NULL){
        return;
    }

    vertex* newVertex = new vertex(vertexId);
    vList.insertVertex(newVertex);
}

void graph::eraseVertex(int vertexId){
    vertex* delVertex = vList.findVertex(vertexId);
    if(delVertex == NULL){
        return;
    }

    for(edgeNode* curEdge = delVertex->incidentEdge.header->next; curEdge != delVertex->incidentEdge.trailer; curEdge = curEdge->next){
        eList.eraseEdge(curEdge->edgeInfo->totalEdgeNode);
        if(curEdge == curEdge->edgeInfo->srcIncidentEdgeNode){
            curEdge->edgeInfo->dstVertex->incidentEdge.eraseEdge(curEdge->edgeInfo->dstIncidentEdgeNode);
        }
        else{
            curEdge->edgeInfo->srcVertex->incidentEdge.eraseEdge(curEdge->edgeInfo->srcIncidentEdgeNode);
        }
        delete curEdge->edgeInfo;
    }
    vList.eraseVertex(delVertex);
}

void graph::insertEdge(int srcVertexId, int dstVertexId){
    vertex* srcVertex = vList.findVertex(srcVertexId);
    vertex* dstVertex = vList.findVertex(dstVertexId);
    if(srcVertex == NULL || dstVertex == NULL){
        return;
    }
    if(findEdge(srcVertex, dstVertex) != NULL){
        return;
    }

    edge* newEdge = new edge(srcVertex, dstVertex);

    srcVertex->incidentEdge.insertEdge(newEdge);
    dstVertex->incidentEdge.insertEdge(newEdge);
    eList.insertEdge(newEdge);
    newEdge->srcIncidentEdgeNode = srcVertex->incidentEdge.trailer->prev;
    newEdge->dstIncidentEdgeNode = dstVertex->incidentEdge.trailer->prev;
    newEdge->totalEdgeNode = eList.trailer->prev;
    srcVertex->degree++;
    dstVertex->degree++;
}

void graph::eraseEdge(int srcVertexId, int dstVertexId){
    vertex* srcVertex = vList.findVertex(srcVertexId);
    vertex* dstVertex = vList.findVertex(dstVertexId);
    if(srcVertex == NULL || dstVertex == NULL){
        return;
    }

    edge* delEdge = findEdge(srcVertex, dstVertex);

    if(delEdge == NULL){
        return;
    }

    srcVertex->incidentEdge.eraseEdge(delEdge->srcIncidentEdgeNode);
    dstVertex->incidentEdge.eraseEdge(delEdge->dstIncidentEdgeNode);
    eList.eraseEdge(delEdge->totalEdgeNode);
    srcVertex->degree--;
    dstVertex->degree--;
    delete delEdge;
}
void graph::BFS(int vertexId, int& num){
        vertex* v = vList.findVertex(vertexId);
        queue<vertex*> que;
        que.push(v);
        while(!que.empty()){
            vertex* curVertex = que.front();
            que.pop();
            for(edgeNode* e = curVertex->incidentEdge.header->next; e != curVertex->incidentEdge.trailer; e = e->next){
                if(curVertex == e->edgeInfo->srcVertex){
                    if(e->edgeInfo->dstVertex->visit != true){
                        que.push(e->edgeInfo->dstVertex);
                        e->edgeInfo->dstVertex->visit = true;
                        num++;
                    }
                }
                else{
                    if(e->edgeInfo->srcVertex->visit != true){
                        que.push(e->edgeInfo->srcVertex);
                        e->edgeInfo->srcVertex->visit = true;
                        num++;
                    }
                }
            }
        }
    }

void graph::DFS(vertex* curVertex, int& num){
    curVertex->visit = true;
    num++;
    for(edgeNode* e = curVertex->incidentEdge.header->next; e != curVertex->incidentEdge.trailer; e = e->next){
        if(curVertex == e->edgeInfo->srcVertex){
            if(e->edgeInfo->dstVertex->visit != true){
                DFS(e->edgeInfo->dstVertex, num);
            }
        }
        else{
            if(e->edgeInfo->srcVertex->visit != true){
                DFS(e->edgeInfo->srcVertex, num);
            }
        }
    }
}

void graph::DFScheck(){
    vertex* check = vList.header->next;
    while(check!=vList.trailer){
        check->visit = false;
        check = check->next;
    }
}
///
int main(){
    graph g;
    int N, M, Q; cin >> N >> M >> Q;
    for(int i=1; i<=N; i++){
        g.insertVertex(i);
    }
    while(M--){
        int a, b; cin >> a >> b;
        g.insertEdge(a, b);
    }
    while(Q--){
        int check = 0;
        int a; cin >> a;
        g.DFS(g.vList.findVertex(a), check);
        cout << check << endl;
        g.DFScheck();
    }
}