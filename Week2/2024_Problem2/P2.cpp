#include <iostream>
using namespace std;

class Node{
friend class LinkedList;
private:
    int element;
    Node* next;
public:
    Node();
    Node(int value);
};

class LinkedList{
private:
    Node* head;
    Node* tail;
    int sizeL{0};
public:
    LinkedList();
    bool empty();
    void append(int value);
    LinkedList(const LinkedList& list1, const LinkedList& l2);
    void print();
    void insertNode(int findValue, int value);
};

Node::Node(){
    element = 0;
    next = nullptr;
}

Node::Node(int value){
    element = value;
    next = nullptr;
}

LinkedList::LinkedList(){
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->next = nullptr;
}

bool LinkedList::empty(){
    return (sizeL==0);
}

void LinkedList::append(int value){
    Node* newNode = new Node{value};
    Node* curNode = head;
    while(curNode->next!=tail){
        curNode = curNode->next;
    }
    curNode->next = newNode;
    newNode->next = tail;
    sizeL++;
}

LinkedList::LinkedList(const LinkedList& list1, const LinkedList& list2){
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->next = nullptr;
    Node* curNode = head;

    Node* useNode = list1.head->next;
    curNode->next = useNode;
    while(useNode->next!=list1.tail){
        useNode = useNode->next;
    }
    curNode = useNode;
    useNode->next = tail;

    useNode = list2.head->next;
    curNode->next = useNode;
    while(useNode->next!=list2.tail){
        useNode = useNode->next;
    }
    useNode->next = tail;
}

void LinkedList::print(){
    Node* curNode = head->next;
    while(curNode!=tail){
        cout << curNode->element << " ";
        curNode = curNode->next;
    }
    cout << endl;
}

void LinkedList::insertNode(int findValue, int value){
    Node* useNode = head->next;
    while(true){
        if(useNode->next->element==findValue){
            break;
        }
        useNode = useNode->next;
    }
    Node* newNode = new Node{value};
    newNode->next = useNode->next;
    useNode->next = newNode;
}

////
int main(){
    int freq; cin >> freq;
    for(int a{0}; a<freq; a++){
        LinkedList list1;
        int num; cin >> num;
        for(int a{0}; a<num; a++){
            int value; cin >> value;
            list1.append(value);
        }
        LinkedList list2;
        cin >> num;
        for(int a{0}; a<num; a++){
            int value; cin >> value;
            list2.append(value);
        }
        list1.print();

        LinkedList mergeList(list1, list2);
        mergeList.print();
        int e, v; cin >> e >> v;
        mergeList.insertNode(e, v);
        mergeList.print();
    }
}