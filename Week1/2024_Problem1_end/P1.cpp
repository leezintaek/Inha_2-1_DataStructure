#include <iostream>
#include <string>
using namespace std;

class Array{
private:
    int* arr;
    int capacity;
public:
    Array(int sizeN);
    void at(int index);
    void add(int index, int value);
    void remove(int index);
    void set(int index, int value);
    void count(int value);
    void print();
};

Array::Array(int sizeN){
    arr = new int[sizeN]{};
    capacity = sizeN;
    for(int a{0}; a<sizeN; a++){
        arr[a] = 0;
    }
}

void Array::at(int index){
    cout << arr[index] << endl;
}

void Array::add(int index, int value){
    for(int a{capacity-2}; index<=a; a--){
        arr[a+1] = arr[a];
    }
    arr[index] = value;
}
 // 0 1 2 3 4
void Array::remove(int index){
    if(index==capacity-1){
        arr[capacity-1] = 0;
        return;
    }
    for(int a{index+1}; a<capacity; a++){
        arr[a-1] = arr[a];
    }
    arr[capacity-1] = 0;
}

void Array::set(int index, int value){
    arr[index] = value;
}

void Array::count(int value){
    int num{0};
    for(int a{0}; a<capacity; a++){
        if(arr[a]==value){
            num++;
        }
    }
    cout << num << endl;
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
        if(input=="at"){
            int index; cin >> index;
            arr.at(index);
        }
        else if(input=="add"){
            int index, value; cin >> index >> value;
            arr.add(index, value);
        }
        else if(input=="remove"){
            int index; cin >> index;
            arr.remove(index);
        }
        else if(input=="set"){
            int index, value; cin >> index >> value;
            arr.set(index, value);
        }
        else if(input=="count"){
            int num; cin >> num;
            arr.count(num);
        }
        else{
            arr.print();
        }
    }
}