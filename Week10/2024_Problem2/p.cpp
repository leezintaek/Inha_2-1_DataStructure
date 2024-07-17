#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare{
    bool operator()(int& e1, int& e2){
        if(e2%2==1){
            if(e1%2==1){
                return (e1<e2);
            }
            else{
                return true;
            }
        }
        else{
            if(e1%2==1){
                return false;
            }
            else{
                return (e1>e2);
            }
        }
    }
};

class Heap{
public:
    Heap();
    int size();
    bool empty();
    void insert(int num);
    int pop();
    void print();
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

void Heap::insert(int num){
    heap.push_back(num);
    upHeap(size());
}

int Heap::pop(){
    if(empty()){
        return -1;
    }

    int num = heap[1];
    swap(1, size());
    heap.pop_back();
    downHeap(1);
    return num;
}

void Heap::print(){
    while(!empty()){
        cout << pop() << " ";
    }
    cout << endl;
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
    int T; cin >> T;
    while(T--){
        Heap heap;
        int N; cin >> N;
        for(int a=0; a<N; a++){
            int num; cin >> num;
            heap.insert(num);
        }
        heap.print();
    }
}