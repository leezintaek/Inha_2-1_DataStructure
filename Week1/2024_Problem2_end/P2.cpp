#include <iostream>
#include <string>
using namespace std;

class Array{
private:
    int* arr;
    int capacity;
public:
    Array(int N);
    void shift(int iIndex, int jIndex);
    void swap(int iIndex, int jIndex);
    void print();
};

Array::Array(int N){
    capacity = N;
    arr = new int[N];

    for(int a{0}; a<capacity; a++){
        arr[a] = a;
    }
}

void Array::shift(int iIndex, int jIndex){
    int tmp = arr[jIndex];
    for(int a{jIndex-1}; a>=iIndex; a--){
        arr[a+1] = arr[a];
    }
    arr[iIndex] = tmp;
}

void Array::swap(int iIndex, int jIndex){
    int tmp = arr[jIndex];
    arr[jIndex] = arr[iIndex];
    arr[iIndex] = tmp;
}

void Array::print(){
    for(int a{0}; a<capacity; a++){
        cout << arr[a] << " ";
    }
    cout << endl;
}

int main(){
    int order, N; cin >> order >> N;
    Array arr{N};
    for(int a{0}; a<order; a++){
        string input; cin >> input;
        if(input=="shift"){
            int i, j; cin >> i >> j;
            arr.shift(i, j);
        }
        else if(input=="swap"){
            int i, j; cin >> i >> j;
            arr.swap(i, j);
        }
        else{
            arr.print();
        }
    }
}