#include <iostream>
#include <vector>
using namespace std;

class Node{
friend class LinkedList;
private:
    Node* parent{nullptr};
    vector<Node*> childList;
    int element;
public:
    Node(int value, Node* parent);
};

class LinkedList{
private:
    Node* root;
    vector<Node*> nodeList;

    int findIndex(int data, vector<Node*>& list);
public:
    LinkedList();
    void append(int parent, int child);
    int findDepth(int node);
};

Node::Node(int value, Node* parent){
    this->element = value;
    this->parent = parent;
}

int LinkedList::findIndex(int data, vector<Node*>& list){
    for(int a{0}; a<list.size(); a++){
        if(list[a]->element==data){
            return a; //존재하면 그 인덱스를 리턴
        }
    }
    return -1; //존재하지 않을 시 -1 리턴
}

LinkedList::LinkedList(){
    root = new Node{1, nullptr};
    nodeList.push_back(root); //루트노드를 만들고 노드리스트에 넣음
}

void LinkedList::append(int parent, int child){
    int parIndex = findIndex(parent, nodeList);
    if(parIndex==-1){
        cout << -1 << endl;
        return;
    }
    int childIndex = findIndex(child, nodeList);
    if(childIndex!=-1){
        cout << -1 << endl;
        return;
    }

    Node* parNode = nodeList[parIndex];
    Node* newNode = new Node{child, parNode};
    parNode->childList.push_back(newNode);
    nodeList.push_back(newNode);
}

int LinkedList::findDepth(int node){
    int nodeIndex = findIndex(node, nodeList);
    if(nodeIndex==-1){
        return -1;
    }
    Node* curNode = nodeList[nodeIndex];
    if(curNode->element==1){
        return 0;
    }
    else{
        return 1 + findDepth(curNode->parent->element);
    }
}

int main(){
    LinkedList list;
    int number, fre; cin >> number >> fre;
    for(int a{0}; a<number; a++){
        int parNum, childNum; cin >> parNum >> childNum;
        list.append(parNum, childNum);
    }
    for(int a{0}; a<fre; a++){
        int findNum1; cin >> findNum1;
        int findNum2; cin >> findNum2;
        int check1 = list.findDepth(findNum1);
        int check2 = list.findDepth(findNum2);
        if((check1==-1)||(check2==-1)){
            cout << "error" << endl;
        }
        else{
            cout << check1 << " " << check2 << " " << check1 + check2 << endl;
        }
    }
}