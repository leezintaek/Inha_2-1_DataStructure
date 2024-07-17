#include<iostream>
using namespace std;

class Node{
friend class LinkedList;
private:
    int element;
    Node* next;
public:
    Node();
    Node(int element);
};

class LinkedList{
private:
    Node* head;
    Node* tail;
    int sizeL{0};
public:
    LinkedList();
    bool empty();
    void Print();
    void Append(int value);
    void Delete(int index);
    void AfterMax(int index);
    void Sum();
};

Node::Node(){
    element = 0;
    next = nullptr;
}

Node::Node(int element){
    this->element = element;
    next = nullptr;
}

LinkedList::LinkedList(){
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->next = nullptr;
}

bool LinkedList::empty(){
    return (head->next==tail);
}

void LinkedList::Print(){
    if(empty()){
        cout << "empty" << endl;
        return;
    }
    Node* curNode = head->next;
    while(curNode!=tail){
        cout << curNode->element << " ";
        curNode = curNode->next;
    }
}

void LinkedList::Append(int value){
    Node* newNode = new Node{value};
    Node* curNode = head;
    while(curNode->next!= tail){
        curNode = curNode->next;
    }
    curNode->next = newNode;
    newNode->next = tail;
    Print();
    sizeL++;
}

void LinkedList::Delete(int index){
    if(empty()||(sizeL<=index)){
        cout << -1 << endl;
        return;
    }
    Node* delNode = head->next;
    for(int a{0}; a<index; a++){
        delNode = delNode->next;
    }
    Node* curNode = head;
    while(curNode->next!=delNode){
        curNode = curNode->next;
    }
    int delNum = delNode->element;
    curNode->next = delNode->next;
    delete delNode;
    sizeL--;

    cout << delNum << endl;
}

void LinkedList::AfterMax(int index){
    if(empty()||(sizeL<=index)){
        cout << "error" << endl;
        return;
    }
    Node* curNode = head->next;
    for(int a{0}; a<index; a++){
        curNode = curNode->next;
    }
    int maxNum = curNode->element;
    while(curNode!=tail){
        if(maxNum<curNode->element){
            maxNum = curNode->element;
        }
        curNode = curNode->next;
    }
    cout << maxNum << endl;
}

void LinkedList::Sum(){
    if(empty()){
        cout << 0 << endl;
        return;
    }
    Node* curNode = head->next;
    int sumNum{0};
    while(curNode!=tail){
        sumNum += curNode->element;
        curNode = curNode->next;
    }
    cout << sumNum << endl;
}

/////////////////
int main(){
    int order; cin >> order;
    LinkedList list;
    for(int a{0}; a<order; a++){
        string input; cin >> input;
        if(input=="Print"){
            list.Print();
        }
        else if(input=="Append"){
            int value; cin >> value;
            list.Append(value);
        }
        else if(input=="Delete"){
            int index; cin >> index;
            list.Delete(index);
        }
        else if(input=="AfterMax"){
            int index; cin >> index;
            list.AfterMax(index);
        }
        else{
            list.Sum();
        }
    }
}