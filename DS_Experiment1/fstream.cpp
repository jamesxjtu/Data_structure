//
// Created by James Wang on 24-11-20.
//
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
/*
int main() {
    // 创建和写入文件
    ofstream outFile("journal.txt", ios::out);
    if (!outFile) {  // 检查文件是否成功打开
        cout << "Error: Unable to open file for writing." << endl;
        return 1;
    }

    // 写入内容到文件
    outFile << "Hello, world!" << endl;
    outFile << "This is a test file." << endl;
    outFile << "File input and output in C++ is fun!" << endl;

    // 关闭文件
    outFile.close();

    cout << "File written successfully!" << endl;

    // 读取文件
    ifstream inFile("example.txt", ios::in);
    if (!inFile) {  // 检查文件是否成功打开
        cout << "Error: Unable to open file for reading." << endl;
        return 1;
    }

    // 逐行读取文件内容
    string line;
    cout << "\nFile content:" << endl;
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    // 关闭文件
    inFile.close();

    return 0;
}*/