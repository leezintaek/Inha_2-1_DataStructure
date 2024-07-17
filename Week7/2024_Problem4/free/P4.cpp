#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node{
friend class Tree;
private:
    int element;
    Node* parent;
    vector<Node*> childList;
public:
    Node(int element, Node* parent);
};

class Tree{
private:
    Node* root;
    vector<Node*> nodeList;

    int findIndex(int value, vector<Node*> list);
public:
    Tree();
    void insertNode(int parV, int childV);
    void printSum(int curV, int& sumNum);
};

Node::Node(int element, Node* parent){
    this->element = element;
    this->parent = parent;
}

int Tree::findIndex(int value, vector<Node*> list){
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
    if(parIndex==-1){ //부모 노드가 존재하지 않을 시
        return;
    }

    Node* parNode = nodeList[parIndex];
    Node* newNode = new Node{childV, parNode};
    nodeList.push_back(newNode);
    parNode->childList.push_back(newNode);
}

void Tree::printSum(int curV, int& sumNum){
    int curIndex = findIndex(curV, nodeList);
    Node* curNode = nodeList[curIndex];
    if(curNode->childList.size()==0){
        cout << "D" << " ";
    }
    else{
        cout << "F" << " ";
    }
    curNode = curNode->parent;
    while(curNode){
        sumNum += curNode->element;
        curNode = curNode->parent;
    }
    cout << sumNum << endl;
}

int main(){
    int num, inp; cin >> num >> inp;
    Tree t;
    for(int a{1}; a<num; a++){
        int par, child; cin >> par >> child;
        t.insertNode(par, child);
    }

    for(int a{0}; a<inp; a++){
        int number; cin >> number;
        int re{0};
        t.printSum(number, re);
    }
}