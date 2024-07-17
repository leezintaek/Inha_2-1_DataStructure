#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare{
    bool operator()(int& e1, int e2){
        string str1 = to_string(e1);
        string str2 = to_string(e2);

        if(str1.size() > str2.size()){
            return true;
        }
        else if(str1.size() < str2.size()){
            return false;
        }
        else{
            return (e1 < e2);
        }
    }
};

class Q{
private:
    vector<int> seq;
public:
    void insert(int num);
    void print();
};

void Q::insert(int num){
    int sizeQ = seq.size();
    int idx{sizeQ};

    compare c;
    for(int i{0}; i<sizeQ; i++){
        if(c(num, seq[i])){
            idx = i;
            break;
        }
    }
    seq.insert(seq.begin() + idx, num);
}

void Q::print(){
    int sizeQ = seq.size();
    for(int a{0}; a<sizeQ; a++){
        cout << seq[a] << " ";
    }
    cout << endl;
}

int main(){
    int T; cin >> T;
    for(int a{1}; a<=T; a++){
        Q q;
        int N; cin >> N;
        for(int b{0}; b<N; b++){
            int n; cin >> n;
            q.insert(n);
        }
        cout << "Case #" << a << ".\n";
        q.print();
    }
}