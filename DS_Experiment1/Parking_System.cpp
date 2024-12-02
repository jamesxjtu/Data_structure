//
// Created by James Wang on 24-11-29.
//
#include<iostream>
#include<fstream>
using namespace std;
#define MAX_PARK 5
#define MAX_PAVE 100
#define max1 100
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
    parkinglot():stops(nullptr),top(-1){}


    int search(char *id) {
            for(int i=0;i<=top;i++) {
                if(strcmp(stops[i]->license,id)==0) {
                    return i;
                }
            }
            return -1;
    }

    void status() {
        int flag = 0;
        cout<<"Parking lot: "<<endl;
        for(int i=0;i<=top;i++) {
            if(stops[i] != nullptr) {
                cout<<"Position"<< i+1 <<" -> "<<stops[i]->license<< endl;
                flag =1;
            }
        }
        if(!flag) {
            cout<<"No car in Parking lot"<<endl;
        }
        cout<<"==================="<<endl;

    }
    bool isEmpty() {
        if(top == -1)
            return true;
        return false;
    }

    bool isFull() {
        if(top == MAX_PARK -1 ) {
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


}PARKINGLOT;

class pave {
    public:
    car *car_pave[MAX_PAVE];
    int front;
    int rear;
    pave():front(0),rear(0) {
        for (int i = 0; i < MAX_PAVE; i++) {
            car_pave[i] = nullptr;
        }
    }
    int search(char *id) {
        for(int i=front;i<rear;i++) {
            if(strcmp(car_pave[i]->license,id)==0) {
                return i;
            }
        }
        return -1;
    }
    bool isEmpty() {
        if (front == rear) {
            return true;
        }
        return false;
    }
    bool isFull() {
        if(rear == MAX_PAVE) {
            return true;
        }
        return false;
    }
    void enqueue(car *d) {
            car_pave[++rear] = d;
        }
    car* dequeue() {
        if(isEmpty()) {
            cout<<"Error in stack is empty"<<endl;
            return nullptr;
        }
            car* temp = car_pave[++front];
            return temp;
        }
    void status() {
        int flag = 0;
        cout<<"Pave: "<<endl;
        for (int i = front+1; i <= rear; i++) {
            if(car_pave[i] != nullptr) {
                cout << car_pave[i]->license<<" is waiting" <<endl;
                flag = 1;
            }
        }
        if(!flag) {
            cout << "No car at the pave" << endl;
        }
        cout<<"==================="<<endl;

    }
}PAVE;

class buffer {
    public:
    car *car_buffer[MAX_PARK];
    int top;
    buffer():top(-1) {
        for (auto & i : car_buffer) {
            i = nullptr;
        }
    }

    int search(char *id) {
        for(int i=0;i<=top;i++) {
            if(strcmp(car_buffer[i]->license,id)==0) {
                return i;
            }
        }
        return -1;
    }

    void status() {
        int flag = 0;
        cout<<"Buffer: "<<endl;
        for(int i=0;i<=top;i++) {
            if( car_buffer[i] != nullptr ) {
                cout<<"Position"<< i+1 <<" -> "<<car_buffer[i]->license<< endl;
                flag = 1;
            }
        }
        if(!flag) {
            cout<<"No car in buffer"<< endl;
        }
        cout<<"==================="<<endl;
    }
    bool isEmpty() {
        if(top == -1)
            return true;
        return false;
    }

    bool isFull() {
        if(top == MAX_PARK) {
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
}BUFFER;
//查看停车场状态
void Check_Status() {
    PARKINGLOT.status();
    BUFFER.status();
    PAVE.status();
}

//CAR stop->buffer
void stop2buffer() {
    if(PARKINGLOT.isEmpty() || BUFFER.isFull()) {
        cout<<"Error: Parking lot is empty or the buffer is full"<<endl;
    }
    else {
        cout << PARKINGLOT.stops[PARKINGLOT.top]->license<<" goes to the buffer"<<endl;
        BUFFER.stack_push(PARKINGLOT.stack_pop());

    }
}
//CAR buffer->stop
void buffer2stop() {
    if(PARKINGLOT.isFull() || BUFFER.isEmpty()) {
        cout<<"Error: Parking lot is full or the buffer is empty"<<endl;
    }
    else {
        cout << BUFFER.car_buffer[BUFFER.top]->license<<" goes to the parking lot"<<endl;
        PARKINGLOT.stack_push(BUFFER.stack_pop());
    }
}
//CAR stop->pave
void stop2pave() {
    if(PARKINGLOT.isEmpty() || PAVE.isFull()) {
        cout<<"Error: Parking lot is empty or the pave is full"<<endl;
    }
    else {
        PARKINGLOT.stops[PARKINGLOT.top]->state = 'p';
        PAVE.enqueue(PARKINGLOT.stack_pop());
    }
}
//CAR pave->stop
void pave2stop() {
    if(PARKINGLOT.isFull() || PAVE.isEmpty()) {
        cout<<"Error: Parking lot is full or the pave is empty"<<endl;
    }
    else {
        PAVE.car_pave[PAVE.front+1]->state = 's';
        PARKINGLOT.stack_push(PAVE.dequeue());
    }
}
//CAR IN
void CAR_IN() {
    if (PARKINGLOT.isFull()) {
        cout<<"Error: Parking lot is full"<<endl;
    }
    else {
        pave2stop();
        cout << PARKINGLOT.stops[PARKINGLOT.top]->license << " goes in to the parking lot" << endl;
    }
}
//CAR OUT DONE
void CAR_OUT(char *id) {
    int position = 0;
    int numbers = 0;
    position = PARKINGLOT.search(id);
    if(position == -1) {
        cout<<"No such car"<<endl;
    }
    else {
        for (int i = PARKINGLOT.top; i > position; i--) {
            stop2buffer();  // 依次将后面的车挪到 BUFFER 中
            numbers++;
        }
        cout<< PARKINGLOT.stops[position]->license <<" left"<< endl;
        PARKINGLOT.stack_pop();
        for(int i = 0; i < numbers;i++ ) {
            buffer2stop();
        }
    }
    while(PARKINGLOT.top <= MAX_PARK && !PAVE.isEmpty()) {
        pave2stop();
        cout << PAVE.car_pave[PAVE.front]->license << " goes in the the parking lot "<< endl;
    }
}

void CAR_IN_OPERATE() {
    char str[7];
    cout << " Please enter the license : "<<endl;
    cin >> str;
    char *license = new char[7];
    strcpy(license, str);
    car *new_car = new car(license,'i');
    PAVE.enqueue(new_car);
    if(PARKINGLOT.isFull()) {
        cout<<"Error: Parking lot is full"<<endl;
    }
    else {
        if(strcmp(license,PAVE.car_pave[PAVE.front+1]->license) == 0) {
            CAR_IN();
            PAVE.car_pave[PAVE.rear]->state = 'p';
        }
        else {
            cout << "Please wait in line"<<endl;
        }
    }
}

void CAR_OUT_OPERATE() {
    char str[7];
    cout << " Please enter the license : "<<endl;
    cin >> str;
    CAR_OUT(str);
}

void printmenu() {
    cout<<endl;
    cout<<"1. Check the parking lot status"<<endl;
    cout<<"2. Car in"<<endl;
    cout<<"3. Car out"<<endl;
}

int getUserOperation() {
    int userOperate;
    cout<<"Type 1-3"<<endl;
    cin>>userOperate;
    cout<<"==================="<<endl;
    cout<<"You chose:"<<userOperate<<endl;
    cout<<"==================="<<endl;
    return userOperate;
}

void processUserOperation(int userOperation) {
    if(cin.fail() ) {
        cin.clear();
        cout<< "Please enter a valid choice"<<endl;
        cin.ignore(1000, '\n');  // 丢弃缓冲区中的错误输入
    }
    else {
        if(userOperation == 1) {
            Check_Status();
        }
        else if(userOperation == 2) {
            CAR_IN_OPERATE();
        }
        else if(userOperation == 3) {
            CAR_OUT_OPERATE();
        }
        else
            cout<<"Please enter a valid choice"<<endl;
    }

}
void welcome() {
    cout<<"Welcome to Parking System"<<endl;
    while(true) {
        printmenu();
        int UserOption = getUserOperation();
        processUserOperation(UserOption);
    }
}
void carset() {

}



int main() {
    carset();
    welcome();
}