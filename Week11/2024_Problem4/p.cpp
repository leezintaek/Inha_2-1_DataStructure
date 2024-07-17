#include <iostream>
#include <string>
using namespace std;

struct Node{
    int key;
    Node* parent;
    Node* left;
    Node* right;
    Node(int key){
        this->key = key;
        parent = left = right = nullptr;
    }
};

class BST{
public:
    Node* search(Node* curNode, int key, int& count);
    void insert(int key);
    Node* root = nullptr;

    void checkN(int x, int& count){
        if(root==nullptr){
            cout << "empty" << endl;
            return;
        }
        Node* curNode = search(root, x, count);
        if(curNode==nullptr){
            cout << count << endl;
            return;
        }
        cout << count << endl;
    }

    void parent(int x){
        int gar = 0;
        Node* curNode = search(root, x, gar);
        if(curNode==nullptr){
            cout << -1 << endl;
            return;
        }
        if(curNode->parent==nullptr){
            cout << -2 << endl;
            return;
        }

        cout << curNode->parent->key << endl;
    }

    void child(int x){
        int gar = 0;
        Node* curNode = search(root, x, gar);
        if(curNode==nullptr){
            cout << -1 << endl;
            return;
        }
        if(curNode->right==nullptr){
            cout << -2 << endl;
            return;
        }
        cout << curNode->right->key << endl;
    }
};

Node* BST::search(Node* curNode, int key, int& count){
    if(curNode==nullptr)
        return nullptr;

    if(curNode->key==key){
        count++;
        return curNode;
    }
    else if(curNode->key<key){
        count++;
        return search(curNode->right, key, count);
    }
    else{
        count++;
        return search(curNode->left, key, count);
    }
}

void BST::insert(int key){
    int gar = 0;

    Node* newNode = new Node(key);
    if(root==nullptr){
        root = newNode;
        cout << 0 << endl;
        return;
    }

    Node* curNode = root;
    Node* parNode = nullptr;
    int count1 = 0;

    while(curNode!=nullptr){
        parNode = curNode;
        if(curNode->key<key){
            curNode = curNode->right;
            count1++;
        }
        else{
            curNode = curNode->left;
            count1++;
        }
    }

    newNode->parent = parNode;
    if(parNode->key<key)
        parNode->right = newNode;
    else
        parNode->left = newNode;
    cout << count1 << endl;
}

int main(){
    int T; cin >> T;
    while(T--){
        BST tree;
        int N; cin >> N;
        while(N--){
            string input; cin >> input;
            if(input=="insert"){
                int x; cin >> x;
                tree.insert(x);
            }
            if(input=="search"){
                int cou = 0;
                int x; cin >> x;
                tree.checkN(x, cou);
            }
            if(input=="parent"){
                int x; cin >> x;
                tree.parent(x);
            }
            if(input=="child"){
                int x; cin >> x;
                tree.child(x);
            }
        }
    }
}