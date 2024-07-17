#include <iostream>
#include <vector>
using namespace std;

class Node{
friend class Tree;
private:
    Node* parent;
    vector<Node*> childList;
    int element;
public:
    Node(int element, Node* parent);
};

class Tree{
private:
    Node* root;
    vector<Node*> nodeList;

    int findIndex(int value, vector<Node*>& list);
public:
    Tree();
    void insertNode(int parV, int childV);
    void deleteNode(int curV);
};

Node::Node(int element, Node* parent){
    this->element = element;
    this->parent = parent;
}

int Tree::findIndex(int value, vector<Node*>& list){
    for(int a{0}; a<list.size(); a++){
        if(list[a]->element==value){
            return a;
        }
    }
    return -1;
}

Tree::Tree(){
    root = new Node{1, nullptr};
    nodeList.push_back(root);
}

void Tree::insertNode(int parV, int childV){
    int parIndex = findIndex(parV, nodeList);
    if(parIndex==-1){
        cout << -1 << endl;
        return;
    }

    Node* parNode = nodeList[parIndex];
    Node* newNode = new Node{childV, parNode};
    parNode->childList.push_back(newNode);
    nodeList.push_back(newNode);
}

void Tree::deleteNode(int curV){
    int curIndex = findIndex(curV, nodeList);
    if(curV==-1){
        cout << -1 << endl;
        return;
    }

    Node* curNode = nodeList[curIndex];
    Node* parNode = curNode->parent;
    for(int a{0}; parNode->childList.size(); a++){
        parNode->childList.push_back(curNode->childList[a]);
        curNode->childList[a]->parent = parNode;
        parNode->childList.erase(parNode->childList.begin()+a);
    }
    nodeList.erase(nodeList.begin()+curIndex);
    delete curNode;
}

int 