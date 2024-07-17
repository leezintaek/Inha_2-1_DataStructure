// #include <iostream>
// #include <string>
// using namespace std;

// #define NOITEM 0
// #define ISITEM 1
// #define AVALIABLE 2

// struct Entry{
//     string ID;
//     string PW;
//     bool login;
//     int valid;
//     Entry();
//     Entry(string ID, string PW);
// };

// Entry::Entry(){
//     ID = "";
//     PW = "";
//     login = false;
//     valid = NOITEM;
// }

// Entry::Entry(string ID, string PW){
//     this->PW = PW;
//     this->ID = ID;
//     login = false;
//     valid = ISITEM;
// }

// class Hash{
// private:
//     Entry* table;
//     int capacity;
//     int hashFnc(string key);
//     int hashFnc(int key);

//     int onlineS = 0;
// public:
//     Hash(int N);
//     void put(string id, string pw);
//     void login(string id, string pw);
//     void logout(string id);
//     int online();
// };

// Hash::Hash(int N){
//     capacity = N;
//     table = new Entry[capacity];
// }

// int Hash::hashFnc(string key){
//     long long idInt = 0;
//     for(int a=0; a<6; a++){
//         long long num = key[a]- 'a';
//         for(int b=0; b<a; b++){
//             num *= 26;
//         }
//         idInt += num;
//     }

//     return idInt % capacity;
// }

// int Hash::hashFnc(int key){
//     return key % capacity;
// }

// void Hash::put(string id, string pw){
//     int index = hashFnc(id);
//     int probe = 1;

//     while(table[index].valid==ISITEM && probe<=capacity){
//         if(table[index].ID==id){
//             cout << "Invalid" << endl;
//             return;
//         }
//         index = hashFnc(index + 1);
//         probe++;
//     }

//     if(probe>capacity){
//         cout << "Invalid" << endl;
//         return;
//     }
//     table[index] = Entry(id, pw);
//     cout << "Submit" << endl;
// }

// void Hash::login(string id, string pw){
//     int index = hashFnc(id);
//     int probe = 1;

//     while(table[index].valid==ISITEM && probe<=capacity){
//         if(table[index].ID==id && table[index].PW==pw){
//             if(table[index].login==true){
//                 cout << "Already" << endl;
//                 return;
//             }
//             else{
//                 cout << "Submit" << endl;
//                 table[index].login = true;
//                 onlineS++;
//                 return;
//             }
//         }
//         index = hashFnc(index+1);
//         probe++;
//     }
//     cout << "Invalid" << endl;
// }

// void Hash::logout(string id){
//     int index = hashFnc(id);
//     int probe = 1;

//     while(table[index].valid==ISITEM && probe<=capacity){
//         if(table[index].ID==id && table[index].login==true){
//             cout << "Submit" << endl;
//             table[index].login = false;
//             onlineS--;
//             return;
//         }

//         index = hashFnc(index + 1);
//         probe++;
//     }
// }

// int Hash::online(){
//     return onlineS;
// }

// int main(){
//     int T; cin >> T;
//     Hash hash(200000);
//     while(T--){
//         string input; cin >> input;
//         if(input=="signup"){
//             string id, pw; cin >> id >> pw;
//             hash.put(id, pw);
//         }
//         if(input=="login"){
//             string id, pw; cin >> id >> pw;
//             hash.login(id, pw);
//         }
//         if(input=="logout"){
//             string id; cin >> id;
//             hash.logout(id);
//         }
//         if(input=="online"){
//             cout << hash.online() << endl;
//         }
//     }
// }

#include <iostream>
#include <string>
using namespace std;

#define NOITEM 0
#define ISITEM 1
#define AVALIABLE 2

#define strSize 6
#define hashNum 26
#define on true
#define off false

struct Entry{
    string id;
    string pw;
    int valid;
    bool login;

    Entry(){
        id = "";
        pw = "";
        valid = NOITEM;
        login = off;
    }

    Entry(string id, string pw){
        this->id = id;
        this->pw = pw;
        valid = ISITEM;
        login = off;
    }

    void erase(){
        valid = AVALIABLE;
    }
};

class Hash{
private:
    Entry* table;
    int onlinePeople = 0;
    int capacity;

    int hashFnc(string id);
    int hashFnc(int num);
public:
    Hash();
    void signup(string id, string pw);
    void login(string id, string pw);
    void logout(string id);
    void online();
};

Hash::Hash(){
    capacity = 500000;
    table = new Entry[capacity];
}

int Hash::hashFnc(string id){
    long sum = 0;
    for(int index=0; index<strSize; index++){
        long num = id[index];
        for(int fre=0; fre<index; fre++){
            num *= hashNum;
        }
        sum += num;
    }
    return sum % capacity;
}

int Hash::hashFnc(int num){
    return num % capacity;
}

void Hash::signup(string id, string pw){
    int index = hashFnc(id);
    int probe = 1;

    while(table[index].valid==ISITEM && probe<capacity){
        if(table[index].id==id){
            cout << "Invalid" << endl;
            return;
        }
        index = hashFnc(index+1);
        probe++;
    }

    if(probe>=capacity){
        cout << "Invalid" << endl;
        return;
    }
    cout << "Submit" << endl;
    table[index] = Entry(id, pw);
}

void Hash::login(string id, string pw){
    int index = hashFnc(id);
    int probe = 1;

    while(table[index].valid!=NOITEM && probe<=capacity){ // this
        if(table[index].valid==ISITEM && table[index].id==id && table[index].pw==pw){
            if(table[index].login==on){
                cout << "Already" << endl;
                return;
            }
            else{
                cout << "Submit" << endl;
                table[index].login = true;
                onlinePeople++;
                return;
            }
        }

        index = hashFnc(index+1);
        probe++;
    }

    cout << "Invalid" << endl;
}

void Hash::logout(string id){
    int index = hashFnc(id);
    int probe = 1;

    while(table[index].valid!=NOITEM && probe<=capacity){ // this
        if(table[index].valid==ISITEM && table[index].id==id){
            if(table[index].login==on){
                cout << "Submit" << endl;
                table[index].login = off;
                onlinePeople--;
                return;
            }
            else{
                cout << table[index].id << endl;
                return;
            }
        }
        index = hashFnc(index+1);
        probe++;
    }
}

void Hash::online(){
    cout << onlinePeople << endl;
}

int main(){
    Hash hash;
    int T; cin >> T;
    while(T--){
        string input; cin >> input;
        if(input=="signup"){
            string id, pw; cin >> id >> pw;
            hash.signup(id, pw);
        }
        if(input=="login"){
            string id, pw; cin >> id >> pw;
            hash.login(id, pw);
        }
        if(input=="logout"){
            string id; cin >> id;
            hash.logout(id);
        }
        if(input=="online"){
            hash.online();
        }
    }
}