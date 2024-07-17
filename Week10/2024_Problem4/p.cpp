#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare{
    bool operator()(int num1, int num2){
        if(num2%2==0){ //2가 짝수
            if(num1%2==1){ //2가 짝수 1이 홀수
                return true;
            }
            else{ //2가 짝수 1이 짝수
                if(num1>num2){ //뒤 우선순위 클때
                    return true;
                }
                else{ //앞 우선순위 클때
                    return false;
                }
            }
        }
        else{ //2가 홀수
            if(num1%2==0){ //2가 홀수 1이 짝수
                return false;
            }
            else{ //2가 홀수 1이 짝수
                if(num1<num2){ // 뒤 우선순위 클때
                    return true;
                }
                else{ //앞 우선순위 클때
                    return false;
                }
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
    void print();
    int pop();
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

void Heap::print(){
    int sizeH = size();
    for(int a=0; a<sizeH; a++){
        cout << pop() << " ";
    }
    cout << endl;
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
    if(c(heap[parent], heap[idx])){ //최소 힙
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
        if(c(heap[right], heap[left])){
            child = left;
        }
        else{
            child = right;
        }
    }

    if(c(heap[idx], heap[child])){
        swap(idx, child);
        downHeap(child);
    }
}

///
int main(){
    int T; cin >> T;
    while(T--){
        Heap heap;
        int N; cin >> N;
        while(N--){
            int n; cin >> n;
            heap.insert(n);
        }

        heap.print();
    }
}
