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
    void findPost(int curV);
    int findDepth(int curV);
    void findMin(Node* curNode);
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

void Tree::findPost(int curV){
    int curIndex = findIndex(curV, nodeList);
    Node* curNode = nodeList[curIndex];
    if(curNode->childList.size()!=0){ //자식 노드 존재
        for(int a{0}; a<curNode->childList.size(); a++){
            findPost(curNode->childList[a]->element);
        }
    }
    else{ //자식 없을 때
        cout << findDepth(curV) << " ";
        return;
    }
    findMin(curNode);
}

int Tree::findDepth(int curV){
    int curIndex = findIndex(curV, nodeList);
    Node* curNode = nodeList[curIndex];
    if(curNode==root){
        return 0;
    }
    else{
        return 1 + findDepth(curNode->parent->element);
    }
}

void Tree::findMin(Node* curNode){
    int minNum{curNode->childList[0]->element};
    for(int a{0}; a<curNode->childList.size(); a++){
        if(minNum>curNode->childList[a]->element){
            minNum = curNode->childList[a]->element;
        }
    }
    cout << minNum << " ";
}

int main(){
    int fre; cin >> fre;
    for(int a{0}; a<fre; a++){
        Tree t;
        int num; cin >> num;
        for(int b{1}; b<num; b++){
            int par, child; cin >> par >> child;
            t.insertNode(par, child);
        }
        t.findPost(1);
        cout << endl;
    }
}