#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct compare{
    bool operator()(int& e1, int& e2){
        return (e1<e2);
    }
};

class Q{
private:
    vector<int> q;
public:
    void insert(int& num);
    void print();
    int delPri();
};

void Q::insert(int& num){
    q.push_back(num);
}

void Q::print(){
    int sizeQ = q.size();
    cout << "PQ : ";
    for(int a{0}; a<sizeQ; a++){
        cout << q[a] << " ";
    }
    cout << endl;
}

int Q::delPri(){
    compare c;
    int checkV = q[0];
    int checkIdx = 0;
    int sizeQ = q.size();
    for(int a{0}; a<sizeQ; a++){
        if(c(checkV, q[a])){
            checkV = q[a];
            checkIdx = a;
        }
    }

    q.erase(q.begin()+checkIdx);
    return checkV;
}

int main(){
    int T; cin >> T;
    for(int a{0}; a<T; a++){
        vector<int> seq;
        Q q;

        int Num; cin >> Num;
        for(int b{0}; b<Num; b++){
            int num; cin >> num;
            seq.push_back(num);
        } //수열에 수 모두 삽입 완료

        int key; cin >> key;
        int lev = 0;

        for(int b{0}; b<Num; b++){
            q.insert(seq.front());
            seq.erase(seq.begin());
            lev++;

            if(key==lev){
                break;
            }
        }

        if(key==lev){
            cout << "S : ";
            int sizeS = seq.size();
            for(int c{0}; c<sizeS; c++){
                cout << seq[c] << " ";
            }
            cout << endl;
            q.print();
        }
        else{
            for(int c{0}; c<Num; c++){
                seq.push_back(q.delPri());
                lev++;

                if(key==lev){
                    break;
                }
            }
            if(key==lev){
                cout << "S : ";
                int sizeS = seq.size();
                for(int c{0}; c<sizeS; c++){
                    cout << seq[c] << " ";
                }
                cout << endl;
                q.print();
            }
        }
    }
}