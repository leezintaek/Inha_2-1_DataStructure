#include <iostream>
#include <string>
using namespace std;

class Q{
private:
    int* arr;
    int capacity;
    int sizeQ{0};
public:
    Q(int N);
    void size();
    bool isEmpty();
    bool full();
    void front();
    void rearNsum(int num);
    void enqueue(int value);
    void dequeue();
};

Q::Q(int N){
    capacity = N;
    arr = new int[N];
}

void Q::size(){
    cout << sizeQ << endl;
}

bool Q::isEmpty(){
    if(sizeQ==0){
        return true;
    }
    return false;
}

bool Q::full(){
    return capacity==sizeQ;
}

void Q::front(){
    if(isEmpty()){
        cout << "Empty" << endl;
        return;
    }

    cout << arr[0] << endl;
}

void Q::rearNsum(int num){
    if(isEmpty()){
        cout << "Empty" << endl;
        return;
    }
    if(num>sizeQ){
        cout << "error" << endl;
        return;
    }

    int sum{0};
    for(int a{sizeQ-num}; a<capacity; a++){
        sum += arr[a];
    }
    cout << sum << endl;
}

void Q::enqueue(int value){
    if(full()){
        cout << "Full" << endl;
        return;
    }

    arr[sizeQ] = value;
    sizeQ++;
}

void Q::dequeue(){
    if(isEmpty()){
        cout << "Empty" << endl;
        return;
    }

    cout << arr[0] << endl;
    for(int a{1}; a<sizeQ; a++){
        arr[a-1] = arr[a];
    }
    sizeQ--;
}

int main(){
    int N, T; cin >> N >> T;
    Q q{N};
    while(T--){
        string input; cin >> input;
        if(input=="size"){
            q.size();
        }
        else if(input=="isEmpty"){
            if(q.isEmpty()){
                cout << "true" << endl;
            }
            else{
                cout << "false" << endl;
            }
        }
        else if(input=="full"){
            if(q.full()){
                cout << "true" << endl;
            }
            else{
                cout << "false" << endl;
            }
        }
        else if(input=="front"){
            q.front();
        }
        else if(input=="rearNsum"){
            int num; cin >> num;
            q.rearNsum(num);
        }
        else if(input=="enqueue"){
            int value; cin >> value;
            q.enqueue(value);
        }
        else{
            q.dequeue();
        }
    }
}