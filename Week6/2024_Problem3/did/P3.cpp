#include <iostream>
#include <vector>
using namespace std;

class Node{
friend class Tree;
private:
    int element;
    Node* parent;
    vector<Node*> childList;
public:
    Node(int value, Node* parent);
};

class Tree{
private:
    Node* root;
    vector<Node*> nodeList;

    int findIndex(int data, vector<Node*>& list);
public:
    Tree();
    void insertNode(int parentNode, int childNode);
    void deleteNode(int node);
    void printParent(int node);
    void printChild(int node);
    void minChild(int node);
};

Node::Node(int value, Node* parent){
    this->element = value;
    this->parent = parent;
}

int Tree::findIndex(int data, vector<Node*>& list){
    for(int a{0}; a<list.size(); a++){
        if(list[a]->element==data)
            return a;
    }
    return -1;
}

Tree::Tree(){
    root = new Node(1, nullptr);
    nodeList.push_back(root);
}

void Tree::insertNode(int parentNode, int childNode){
    int parentIndex = findIndex(parentNode, nodeList);
    int check = findIndex(childNode, nodeList);
    if((parentIndex==-1)||(check!=-1)){
        cout << -1 << endl;
        return;
    }
    Node* parNode = nodeList[parentIndex];
    Node* newNode = new Node{childNode, parNode};
    parNode->childList.push_back(newNode);
    nodeList.push_back(newNode);
}

void Tree::deleteNode(int node){
    int index = findIndex(node, nodeList);
    if(index==-1){ //노드가 존재하지 않을 때
        cout << -1 << endl;
        return;
    }
    // if(node==1){ //루트 노드를 지우려 할 때
    //     return;
    // }
    Node* delNode = nodeList[index]; //지우려는 노드
    Node* parDel = delNode->parent; //지우려는 노드의 부모
    vector<Node*>& child = parDel->childList;
    for(int a{0}; a<delNode->childList.size(); a++){
        child.push_back(delNode->childList[a]);
        delNode->childList[a]->parent = parDel;
    }
    child.erase(child.begin()+findIndex(node, child));
    delete nodeList[index];
    nodeList.erase(nodeList.begin()+index);
}

void Tree::printParent(int node){
    int index = findIndex(node, nodeList);
    if(index==-1){
        cout << -1 << endl;
        return;
    }
    Node* childNode = nodeList[index];
    cout << childNode->parent->element << endl;
}

void Tree::printChild(int node){
    int index = findIndex(node, nodeList);
    if((index==-1)||(nodeList[index]->childList.size()==0)){
        cout << -1 << endl;
        return;
    }
    Node* parNode = nodeList[index];
    for(Node* list : parNode->childList){
        cout << list->element << " ";
    }
    cout << endl;
}

void Tree::minChild(int node){
    int index = findIndex(node, nodeList);
    if((index==-1)||(nodeList[index]->childList.size()==0)){
        cout << -1 << endl;
        return;
    }
    Node* parNode = nodeList[index];
    int min = parNode->childList[0]->element;
    int max = parNode->childList[0]->element;
    for(Node* check : parNode->childList){
        if(check->element<min){
            min = check->element;
        }
    }
    for(Node* check : parNode->childList){
        if(check->element>max){
            max = check->element;
        }
    }
    if(min==max){
        cout << min << endl;
    }
    else{
        cout << max - min << endl;
    }
}

int main(){
    int fre; cin >> fre;
    Tree list;
    while(fre--){
        string input; cin >> input;
        if(input=="insert"){
            int x, y; cin >> x >> y;
            list.insertNode(x, y);
        }
        else if(input=="delete"){
            int x; cin >> x;
            list.deleteNode(x);
        }
        else if(input=="parent"){
            int x; cin >> x;
            list.printParent(x);
        }
        else if(input=="child"){
            int x; cin >> x;
            list.printChild(x);
        }
        else{
            int x; cin >> x;
            list.minChild(x);
        }
    }
}