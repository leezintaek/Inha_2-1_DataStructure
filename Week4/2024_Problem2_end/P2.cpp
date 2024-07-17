#include <iostream>
#include <string>
using namespace std;

class Node{
friend class List;
private:
    Node* next{nullptr};
    Node* prev{nullptr};
    int element;
public:
    Node();
    Node(int element);
};

class List{
private:
    Node* head;
    Node* tail;
    int sizeList{0};
public:
    List();
    void append(int value);
    int sizeL();
    int score(int index);
};

Node::Node(){
    element = 0;
}

Node::Node(int element){
    this->element = element;
}

List::List(){
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

void List::append(int value){
    Node* newNode = new Node{value};
    Node* useNode = head;
    while(useNode->next!=tail){
        useNode = useNode->next;
    }
    useNode->next->prev =newNode;
    newNode->next = useNode->next;
    useNode->next = newNode;
    newNode->prev = useNode;
    sizeList++;
}

int List::sizeL(){
    return sizeList;
}

int List::score(int index){
    Node* useNode = head->next;
    for(int a{0}; a<index; a++){
        useNode = useNode->next;
    }
    return useNode->element;
}

void run(List& l1, List& l2);

int main(){
    int T; cin >> T;
    while(T--){
        int N; cin >> N; //카드의 개수
        List l1;
        for(int a{0}; a<N; a++){
            int V; cin >> V; //체력
            l1.append(V);
        }
        List l2;
        for(int a{0}; a<N; a++){
            int V; cin >> V;
            l2.append(V);
        }
        run(l1, l2);
    }
}

void run(List& l1, List& l2){
    int point1{0};
    int point2{0};
    int rP{0};
    int winner{0};
    for(int a{1}; a<=l1.sizeL(); a++){
        int P1 = l1.score(a-1);
        int P2 = l2.score(a-1);
        cout << "Round" << a << " ";
        if(winner==1){
            P1 += rP;
        }
        if(winner==2){
            P2 += rP;
        }
        //
        if(P1==P2){
            winner = 0;
            rP = 0;
            cout << P1 << "=" << P2 << " " << point1 << ":" << point2 << endl;
            continue;
        }
        if(P1>P2){
            winner = 1;
            // point1++;
            rP = P1 - P2;
            cout << P1 << ">" << P2 << " " << ++point1 << ":" << point2 << endl;
        }
        if(P1<P2){
            winner = 2;
            // point2++;
            rP = P2 - P1;
            cout << P1 << "<" << P2 << " " << point1 << ":" << ++point2 << endl;
        }
    }
    if(point1>point2){
        cout << "Winner P1" << endl;
    }
    if(point1<point2){
        cout << "Winner P2" << endl;
    }
    if(point1==point2){
        if(winner==0){
            cout << "Draw" << endl;
        }
        else if(winner==1){
            cout << "Winner P1" << endl;
        }
        else if(winner==2){
            cout << "Winner P2" << endl;
        }
    }
}