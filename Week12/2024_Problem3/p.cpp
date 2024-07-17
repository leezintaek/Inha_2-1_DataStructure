#include <iostream>
#include <string>
using namespace std;

#define NOITEM 0
#define ISITEM 1
#define AVALIABLE 2

struct Entry{
int key;
string value;
int valid;
Entry(){
    key = 0;
    value = "";
    valid = NOITEM;
}
Entry(int key, string value){
    this->key = key;
    this->value = value;
    valid = ISITEM;
}
void erase(){
    valid = AVALIABLE;
}
};

class Hash{
private:
    Entry* table;
    int capacity;
    int hashFnc(int key);
public:
    Hash(int N);
    void put(int key, string value);
    void erase(int key);
    void find(int key);
    int vacant();
};

Hash::Hash(int N){
    capacity = N;
    table = new Entry[capacity];
}

int Hash::hashFnc(int key){
    return key % capacity;
}

void Hash::put(int key, string value){
    int index = hashFnc(key);
    int probe = 1;

    while(table[index].valid==ISITEM && probe<=capacity){
        index = hashFnc(index+1);
        probe++;
    }

    if(probe>capacity){
        cout << hashFnc(key) << " " << -1 << endl;
        return;
    }

    table[index] = Entry(key, value);
    cout << hashFnc(key) << " " << index << endl;
    return;
}

void Hash::erase(int key){
    int index = hashFnc(key);
    int probe = 1;

    while(table[index].valid!=NOITEM && probe<=capacity){
        if(table[index].valid==ISITEM && table[index].key==key){
            cout << table[index].value << endl;
            table[index].erase();
            return;
        }

        index = hashFnc(index+1);
        probe++;
    }
    cout << "None" << endl;
}

void Hash::find(int key){
    int index = hashFnc(key);
    int probe = 1;

    while(table[index].valid!=NOITEM && probe<=capacity){
        if(table[index].valid==ISITEM && table[index].key==key){
            cout << table[index].value << endl;
            return;
        }

        index = hashFnc(index+1);
        probe++;
    }
    cout << "None" << endl;
}

int Hash::vacant(){
    int n = 0;
    for(int a=0; a<capacity; a++){
        if(table[a].valid==ISITEM){
            n++;
        }
    }
    return capacity - n;
}

int main(){
    int T, N; cin >> T >> N;
    Hash hash(N);
    while(T--){
        string input; cin >> input;
        if(input=="put"){
            int k;
            string s;
            cin >> k >> s;
            hash.put(k, s);
        }
        if(input=="erase"){
            int k; cin >> k;
            hash.erase(k);
        }
        if(input=="find"){
            int k; cin >> k;
            hash.find(k);
        }
        if(input=="vacant"){
            cout << hash.vacant() << endl;
        }
    }
}