#include <iostream>
#include <string>
using namespace std;

class Stack{
private:
    int* stack;
    int capacity;
    int sizeS;
public:
    Stack(int t);
    int size();
    bool empty();
    void top();
    void push(int value);
    void popsum(int num);
};

Stack::Stack(int t){
    capacity = t;
    stack = new int[t];
    sizeS = 0;
}

int main(){
    int t, N; cin >> t >> N;
    Stack st{t};
    for(int a{0}; a<N; a++){
        string input; cin >> input;
        if(input=="size"){

        }
        else if(input=="empty"){

        }
        else if(input=="top"){

        }
        else if(input=="push"){

        }
        else{

        }
    }
}