#include <iostream>
#include <string>
using namespace std;

class Node{
friend class List;
private:
    Node* next{nullptr};
    Node* prev{nullptr};
    string element;
public:
    Node();
    Node(string element);
};

class List{
private:
    Node* head;
    Node* tail;
    Node* pos;
    int sizeL{0};
public:
    List();
    void appendF(string value);
    void setPos(int p);
    void up(int X);
    void down(int X);
    void cut();
    void append(string name);
    void printAll();
};

Node::Node(){
    element = " ";
}

Node::Node(string element){
    this->element = element;
}

List::List(){
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

void List::appendF(string value){
    Node* newNode = new Node{value};
    tail->prev->next = newNode;
    newNode->prev = tail->prev;
    tail->prev = newNode;
    newNode->next = tail;
    sizeL++;
}

void List::setPos(int p){
    pos = head->next;
    for(int a{0}; a<p; a++){
        pos = pos->next;
    }
}

void List::up(int X){
    if(head->next==tail){
        return;
    }

    for(int a{0}; a<X; a++){
        pos = pos->prev;
        if(pos==head){
            pos = head->next;
            break;
        }
    }
}

void List::down(int X){
    if(head->next==tail){
        return;
    }

    for(int a{0}; a<X; a++){
        pos = pos->next;
        if(pos==tail){
            pos = tail->prev;
            break;
        }
    }
}

void List::cut(){
    if(head->next==tail){
        return;
    }

    Node* useNode = pos->prev;
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    pos = useNode;
    if(pos==head){
        pos = head->next;
    }
}

void List::append(string name){
    Node* newNode = new Node{name};
    if(head->next==tail){
        head->next = newNode;
        newNode->prev = head;
        tail->prev = newNode;
        newNode->next = tail;
        pos = newNode;
        return;
    }

    pos->next->prev = newNode;
    newNode->next = pos->next;
    pos->next = newNode;
    newNode->prev = pos;
}

void List::printAll(){
    if(head->next==tail){
        cout << "And Then There Were None" << endl;
        return;
    }

    Node* useNode = head->next;
    while(useNode!=tail){
        cout << useNode->element << " ";
        useNode = useNode->next;
    }
    cout << endl;
}

int main(){
    int freq; cin >> freq;
    while(freq--){
        int num, order, pick; cin >> num >> order >> pick;
        List list;
        for(int a{0}; a<num; a++){
            string input; cin >> input;
            list.appendF(input);
        }
        list.setPos(pick);
        for(int a{0}; a<order; a++){
            string input; cin >> input;
            if(input=="up"){
                int X; cin >> X;
                list.up(X);
            }
            else if(input=="down"){
                int X; cin >> X;
                list.down(X);
            }
            else if(input=="cut"){
                list.cut();
            }
            else{
                string name; cin >> name;
                list.append(name);
            }
        }
        list.printAll();
    }
}
