//
// Created by James Wang on 24-12-1.
//

#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
class Node {
    public:
    int code;
    int number;
    Node* next;
    Node(int _code, int _number):
    code(_code),number(_number)
    {
        next = nullptr;
    }
};

class Josephus {
    public:
    int size;
    Node* root;
    Node* current;
    Josephus(int _size):
    size(_size)
    {
        current = nullptr;
        root = nullptr;
    }
    void insert(vector<int>& code) {
        if (code.empty()) return; // 如果 vector 为空，直接返回
        root = new Node(code[0], 1);
        current = root;
        for (int i = 1; i < size; i++) {
            current->next = new Node(code[i], i + 1);
            current = current->next;
        }
        current->next = root;  // 闭合循环链表
        current = root;
    }

    int Node_del() {
        if (current == nullptr) exit(0);
        Node *temp = current->next;
        size--;
        if (temp == current) { // 只剩最后一个节点
            int code = temp->code;
            delete temp;
            current = nullptr;
            return code;
        }
        current->next = temp->next;
        current = temp->next;
        int code = temp->code;
        delete temp;
        return code;
    }

    void count(int d) {
        for(int i = 1; i<d-1 ;i++) {
            current = current->next;
        }
    }

    void display(int init) {
        int i = init;
        current = root;
        while(size>0) {
            count(i);
            cout << current->next->number << " " ;
            i = Node_del();
        }
    }
};

int main() {
    ifstream inFile;
    ofstream outFile;

    inFile.open("/Users/jameswang/CLionProjects/Data_structure/DS_Experiment1/cmake-build-debug/Testing/Josephus/input.txt",ios::in);
    outFile.open("/Users/jameswang/CLionProjects/Data_structure/DS_Experiment1/cmake-build-debug/Testing/Josephus/output.txt",ios::out);


    int N;
    if (inFile >> N) {
        cout << "Step count from file: " << N << endl;
    }

    string line;
    cout << "File content:" << endl;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    stringstream ss(line);  // 使用字符串流解析输入
    vector<int> numbers;     // 存储分割后的整型数组
    int num;
    while (ss >> num) {
        numbers.push_back(num);
    }

    int n = numbers.size();

    Josephus j(n);
    j.insert(numbers);
    cout.rdbuf(outFile.rdbuf());
    j.display(N);

    inFile.close();
    outFile.close();
}


