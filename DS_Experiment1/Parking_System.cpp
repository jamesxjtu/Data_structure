//
// Created by James Wang on 24-11-29.
//
#include<iostream>
#include<fstream>
using namespace std;
#define MAX_PARK 5;
#define MAX_PAVE 100;
class car {
    public:
    char *license;
    char state;

    car(char *_license,char _state):
    license(_license),
    state(_state){}
};

class parkinglot {
    public:
    car *stops[MAX_PARK];
    int top;
    parkinglot():stops(nullptr),top(0){}

    void status() {
        for(int i=0;i<top;i++) {
            cout<<"The car "<<stops[top]->license<< "is in the stop "<< i+1 <<endl;
        }
    }
    bool isEmpty() {
        if(top == -1)
            return true;
        return false;
    }

    bool isFull() {
        if(top == max) {
            cout<<"Error in stack is full"<<endl;
            return true;
        }
        return false;
    }

    void stack_push(car * d) {
        if(isFull()) {
            cout<<"Error in stack is full"<<endl;
            exit(0);
        }
        stops[++top] = d;
    }
    car* stack_pop() {
        if(isEmpty()) {
            cout<<"Error in stack is empty"<<endl;
            exit(0);
        }
        return stops[top--];
    }


};

class pave {
    public:
    car *car_pave[MAX_PAVE];
    int front;
    int rear;
    pave():front(0),rear(0) {
        for (int i = 0; i < max; i++) {
            car_pave[i] = nullptr;
        }
    }
    void enqueue(car *d) {
            car_pave[++rear] = d;
        }
        car* dequeue() {
            car* temp = car_pave[++front];
            return temp;
        }
};

class buffer {
    public:
    car *car_buffer[MAX_PARK];
    int top;
    buffer():car_buffer(nullptr),top(0){}

    void status() {
        for(int i=0;i<top;i++) {
            cout<<"The car "<<car_buffer[top]->license<< "is in the stop "<< i+1 <<endl;
        }
    }
    bool isEmpty() {
        if(top == -1)
            return true;
        return false;
    }

    bool isFull() {
        if(top == max) {
            cout<<"Error in stack is full"<<endl;
            return true;
        }
        return false;
    }

    void stack_push(car * d) {
        if(isFull()) {
            cout<<"Error in stack is full"<<endl;
            exit(0);
        }
        car_buffer[++top] = d;
    }
    car* stack_pop() {
        if(isEmpty()) {
            cout<<"Error in stack is empty"<<endl;
            exit(0);
        }
        return car_buffer[top--];
    }
};



int main() {
    void welcome();
    void menu();
    void come();
    void leave();


}