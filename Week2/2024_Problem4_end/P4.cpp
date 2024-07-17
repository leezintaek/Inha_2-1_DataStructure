#include <iostream>
using namespace std;

class Node{
friend class List;
public:
    Node* next{nullptr};
    int element;
private:
    Node();
    Node(int element);
};

class List{
private:
    Node* head;
public:
    List();
    List(List& l1, List& l2);
    void append(int value);
    void print();
    void deletion(int value);
    void findIndex(int value);
};

Node::Node(){
    element = 0;
}

Node::Node(int element){
    this->element = element;
}

List::List(){
    head = new Node;
}

List::List(List& l1, List& l2){
    head = new Node;
    head->next = l1.head->next;

    Node* useNode = l1.head;
    while(useNode->next!=nullptr){
        useNode = useNode->next;
    }
    useNode->next = l2.head->next;
}

void List::append(int value){
    Node* newNode = new Node{value};
    Node* useNode = head;
    while(useNode->next!=nullptr){
        useNode = useNode->next;
    }
    useNode->next = newNode;
}

void List::print(){
    Node* useNode = head->next;
    while(useNode){
        cout << useNode->element << " ";
        useNode = useNode->next;
    }
    cout << endl;
}

void List::deletion(int value){
    Node* delNode = head;
    while(delNode->element!=value){
        delNode = delNode->next;
    }
    Node* useNode = head;
    while(useNode->next!=delNode){
        useNode = useNode->next;
    }
    useNode->next = delNode->next;
    print();
}

void List::findIndex(int value){
    Node* useNode = head->next;
    int index{0};
    while(true){
        if(useNode->element==value){
            cout << index << endl;
            break;
        }
        useNode = useNode->next;
        index++;
    }
}

int main(){
    int freq; cin >> freq;
    while(freq--){
        int N1; cin >> N1;
        List list1;
        for(int a{0}; a<N1; a++){
            int inp; cin >> inp;
            list1.append(inp);
        }
        // list1.print();
        int N2; cin >> N2;
        List list2;
        for(int a{0}; a<N2; a++){
            int inp; cin >> inp;
            list2.append(inp);
        }
        // list2.print();
        List mergeList(list1, list2);
        mergeList.print();

        int v; cin >> v;
        mergeList.deletion(v);
        int k; cin >> k;
        mergeList.findIndex(k);
    }
}