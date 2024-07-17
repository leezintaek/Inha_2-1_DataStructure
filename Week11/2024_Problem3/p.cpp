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
    BST();
    Node* search(Node* curNode, int key);
    void insert(int key);
    void remove(int key);

    int height(){
        return heightRec(root);
    }

    int findKthLargest(int k){
        int count = 0;
        int result = -1;
        findKthLargest(root, k, count, result);
        return result;
    }

private:
    Node* root;

    int heightRec(Node* node){
        if(node==nullptr){
            return -1;
        }

        int leftHeight = heightRec(node->left);
        int rightHeight = heightRec(node->right);

        return max(leftHeight, rightHeight) + 1;
    }

    void findKthLargest(Node* node, int k, int& count, int& result){
        if(!node||count>=k)
            return;

        findKthLargest(node->left, k, count, result);

        count++;

        if(count==k){
            result = node->key;
            return;
        }

        findKthLargest(node->right, k, count, result);
    }
};

BST::BST(){
    root = nullptr;
}

Node* BST::search(Node* curNode, int key){
    if(curNode==nullptr)
        return nullptr;

    if(curNode->key==key)
        return curNode;
    else if(curNode->key<key)
        return search(curNode->right, key);
    else
        return search(curNode->left, key);
}

void BST::insert(int key){
    if(search(root, key)!=nullptr)
        return;

    Node* newNode = new Node(key);
    if(root==nullptr){
        root = newNode;
        return;
    }

    Node* curNode = root;
    Node* parNode = nullptr;

    while(curNode!=nullptr){
        parNode = curNode;
        if(curNode->key<key)
            curNode = curNode->right;
        else
            curNode = curNode->left;
    }

    newNode->parent = parNode;
    if(parNode->key<key)
        parNode->right = newNode;
    else
        parNode->left = newNode;
}

void BST::remove(int key){
    Node* delNode = search(root, key);
    if(delNode==nullptr)
        return;

    Node* parNode = delNode->parent;
    Node* childNode;

    if((delNode->left==nullptr)&&(delNode->right==nullptr))
        childNode = nullptr;
    else if((delNode->left==nullptr)&&(delNode->right!=nullptr))
        childNode = delNode->right;
    else if((delNode->left!=nullptr)&&(delNode->right==nullptr))
        childNode = delNode->left;
    else{
        childNode = delNode->right;
        while(childNode->left!=nullptr){
            childNode = childNode->left;
        }
        delNode->key = childNode->key;
        delNode = childNode;
        parNode = delNode->parent;
        childNode = delNode->right;
    }

    if(parNode==nullptr){
        root = childNode;
        if(childNode!=nullptr)
            root->parent = nullptr;
    }
    else if(delNode==parNode->left){
        parNode->left = childNode;
        if(childNode !=nullptr)
            childNode->parent = parNode;
    }
    else{
        parNode->right = childNode;
        if(childNode!=nullptr)
            childNode->parent = parNode;
    }

    delete delNode;
}
///

int main(){
    int T; cin >> T;
    while(T--){
        int N; cin >> N;
        BST tree;
        while(N--){
            string input; cin >> input;
            if(input=="insert"){
                int x; cin >> x;
                tree.insert(x);
            }
            if(input=="delete"){
                int x; cin >> x;
                tree.remove(x);
            }
            if(input=="min"){
                int k; cin >> k;
                cout << tree.findKthLargest(k) << endl;
            }
        }
    }
}