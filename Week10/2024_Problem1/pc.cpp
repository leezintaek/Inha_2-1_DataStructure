#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare{
    bool operator()(int& e1, int& e2){
        return (e1>e2);
    }
};

class Heap{
public:
    Heap();
    int size();
    bool empty();
    void push(int num);
    int pop();
    int top();
    void second_top();
private:
    vector<int> heap;

    void swap(int idx1, int idx2);
    void upHeap(int idx);
    void downHeap(int idx);
};

Heap::Heap(){
    heap.push_back(0);
}

int Heap::size(){
    return (heap.size()-1);
}

bool Heap::empty(){
    return (size()==0);
}

void Heap::push(int num){
    heap.push_back(num);
    upHeap(size());
}

int Heap::pop(){
    if(empty()){
        return -1;
    }

    int min = heap[1];
    swap(1, size());
    heap.pop_back();
    downHeap(1);
    return min;
}

int Heap::top(){
    if(empty()){
        return -1;
    }

    return heap[1];
}


void Heap::second_top(){
    if(size()<2){
        cout << "Error" << endl;
        return;
    }

    compare c;
    int left = 2;
    int right = 3;
    int child;
    if(size()==2){
        child = left;
    }
    else{
        if(c(heap[left], heap[right])){
            child = right;
        }
        else{
            child = left;
        }
    }

    cout << heap[child] << endl;
}

void Heap::swap(int idx1, int idx2){
    heap[0] = heap[idx1];
    heap[idx1] = heap[idx2];
    heap[idx2] = heap[0];
}

void Heap::upHeap(int idx){
    if(idx==1){
        return;
    }

    compare c;
    int parent = idx/2;
    if(c(heap[parent], heap[idx])){
        swap(parent, idx);
        upHeap(parent);
    }
}

void Heap::downHeap(int idx){
    int left = idx*2;
    int right = idx*2+1;
    int child;
    compare c;

    if(left>size()){
        return;
    }
    else if(left==size()){
        child = left;
    }
    else{
        if(c(heap[left], heap[right])){
            child = right;
        }
        else{
            child = left;
        }
    }

    if(c(heap[idx], heap[child])){
        swap(idx, child);
        downHeap(child);
    }
}

int main(){
    Heap heap;
    int N; cin >> N;
    while(N--){
        string input; cin >> input;
        if(input=="size"){
            cout << heap.size() << endl;
        }
        if(input=="empty"){
            cout << heap.empty() << endl;
        }
        if(input=="push"){
            int num; cin >> num;
            heap.push(num);
        }
        if(input=="pop"){
            cout << heap.pop() << endl;
        }
        if(input=="top"){
            cout << heap.top() << endl;
        }
        if(input=="second_top"){
            heap.second_top();
        }
    }
}