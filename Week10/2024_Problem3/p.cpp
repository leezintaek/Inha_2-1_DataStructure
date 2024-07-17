#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Heap{
public:
    Heap();
    int size();
    bool empty();
    void insert(int num);
    int pop();
    int top();
    void second_top();
    void print();
private:
    vector<int> heap;

    void swap(int idx1, int idx2);
    void upHeap(int idx);
    void downHeap(int idx);
};

void Heap::print(){
    int size1 = size();
    for(int a=1; a<=size1; a++){
        cout << heap[a] << " ";
    }
    cout << endl;
}

Heap::Heap(){
    heap.push_back(0);
}

int Heap::size(){
    return (heap.size()-1);
}

bool Heap::empty(){
    return (size()==0);
}

void Heap::insert(int num){
    heap.push_back(num);
    upHeap(size());
}

int Heap::pop(){
    if(empty()){
        return -1;
    }
    int maxNum = heap[1];
    swap(1, size());
    heap.pop_back();
    downHeap(1);

    return maxNum;
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

    int child;
    if(size()==2){
        child = 2;
    }
    else{
        if(heap[2]>heap[3]){
            child = 2;
        }
        else{
            child = 3;
        }
    }

    cout << heap[child] << endl;
}
//
void Heap::swap(int idx1, int idx2){
    heap[0] = heap[idx1];
    heap[idx1] = heap[idx2];
    heap[idx2] = heap[0];
}

void Heap::upHeap(int idx){
    if(idx==1){
        return;
    }

    int parent = idx/2;
    if(heap[parent]<heap[idx]){ //최소 힙
        swap(parent, idx);
        upHeap(parent);
    }
}

void Heap::downHeap(int idx){
    int left = idx*2;
    int right = idx*2+1;
    int child;

    if(left>size()){
        return;
    }
    else if(left==size()){
        child = left;
    }
    else{
        if(heap[left]>heap[right]){
            child = left;
        }
        else{
            child = right;
        }
    }

    if(heap[idx]<heap[child]){
        swap(idx, child);
        downHeap(child);
    }
}

int main(){
    Heap heap;
    int T; cin >> T;
    while(T--){
        string input; cin >> input;
        if(input=="size"){
            cout << heap.size() << endl;
        }
        if(input=="empty"){
            cout << heap.empty() << endl;
        }
        if(input=="push"){
            int num; cin >> num;
            heap.insert(num);
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