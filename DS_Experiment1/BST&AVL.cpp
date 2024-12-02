#include<iostream>
#include<fstream>
#include<cmath>
#include<sstream>
#include<vector>
using namespace std;
#define max 1000
class Node {
    public:int data;
    Node* left;
    Node* right;
    Node(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    };
};
int my_max(int a,int b) {
    return (a>b)?a:b;
}
class My_queue {
    public:
    int front;
    int rear;
    Node *queue1[max];
    My_queue() {
        rear = 0;
        front = 0;

        for (int i = 0; i < max; i++) {
            queue1[i] = nullptr;
        }
    }
    void enqueue(Node *d) {
        queue1[++rear] = d;
    }
    Node* dequeue() {
        Node* temp = queue1[++front];
        return temp;
    }
};


class Node_stack {
    public:
    int top;            // 栈顶索引
    Node* base[max];    // 存储Node指针的数组
    Node_stack()
    {   top=-1;
        for (int i = 0; i < max; ++i) {
            base[i] = nullptr; // 初始化数组元素为空
        }
    };

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

    void stack_push(Node * d) {
        if(isFull()) {
            cout<<"Error in stack is full"<<endl;
            exit(0);
        }
        base[++top] = d;
    }

    Node* stack_pop() {
        if(isEmpty()) {
            cout<<"Error in stack is empty"<<endl;
            exit(0);
        }
        return base[top--];
    }

    Node* stack_top() {
        if(isEmpty()) {
            cout<<"Error in stack is empty"<<endl;
            exit(0);
        }
        return base[top];
    }
};

class array_BST {
public:
    int Max_size;
    int *array;
    int size = 0;
    array_BST(int d) {
        Max_size = d;
        array = new int[Max_size];
        memset(array, -1, Max_size * sizeof(int));
    }
    ~array_BST() {
        delete[] array;
    }
    void insert(int d) {
        if(size == Max_size) {
            cout<<"ERROR: the array is full"<<endl;
            exit(0);
        }
        if (size == 0) {
            array[0] = d;
            size++;
        } else {
            int index = 0; // 从根节点开始
            while (index < Max_size) {
                if (array[index] == -1) {
                    array[index] = d;
                    size++;
                    return;
                }
                if (d < array[index]) {
                    index = 2 * index + 1; // 右子节点
                }
                else {
                    index = 2 * index + 2; // 左子节点
                }
            }
        }
    }
    string inorder() {
        stringstream ss;
        inorderREC(array,0,size,ss);
        return ss.str();
    }

    void inorderREC(int *array, int index, int size,stringstream &ss) {
        if(index >= Max_size || array[index] == -1) {
            return;
        }
        inorderREC(array, 2*index+1,size,ss);
        ss<<array[index]<<" ";
        inorderREC(array, 2*index+2,size,ss);
    }
    int search(int d) {
        int index = 0;
        while (index < Max_size) {
            if (array[index] == -1) {
                return -1;
            }
            if (array[index] == d) {
                return index;
            }
            if (d < array[index]) {
                index = 2 * index + 1;
            }
            else {
                index = 2 * index + 2;
            }
        }
        return -1;
    }
    int search_length(int d) {
        int index = 0;
        int length = 0;
        while (index < Max_size) {
            if (array[index] == d) {
                length++;
                return length;

            }
            if (d > array[index]) {
                index = 2 * index + 2;
                length++;
            }
            else {
                index = 2 * index + 1;
                length++;
            }
        }
    }

    string my_delete(int d) {
        int index = search(d);
        int index1 = index;
        if(array[index*2+1] == d) {
            my_delete(array[index*2+1]);
        }
        if(index == -1){
            return "error";
        }

            if(array[index*2+1] == -1 && array[index*2+2] == -1) {
                array[index]=-1;
            }
            else if(array[index*2+1] != -1 && array[index*2+2]==-1) {
                index =index*2+1;
                while(array[index*2+2] != -1) {
                    index=index*2+2;
                }
                array[index1] = array[index];
                array[index] = -1;
                leftup(index,index*2+1);
            }
            else {
                index = index*2+2;
                while(array[index*2+1] != -1) {
                    index=index*2+1;
                }
                array[index1] = array[index];
                array[index] = -1;
                rightup(index,index*2+2);
            }
        string str = inorder();
        return str;
        }
    void rightup(int index1, int index2)
    {
        int index_left = index2*2+1;
        int index_right = index2*2+2;
        if(index_right > Max_size || index_left > Max_size) {
            return;
        }
        if(array[index2]!=-1 || array[index1]!=-1) {
            array[index1] = array[index2];
            rightup(index2,index_right);
            rightup(index1*2+1,index_left);
        }
    }

    void leftup(int index1, int index2) {
        int index_left = index2*2+1;
        int index_right = index2*2+2;
        if(index_right > Max_size || index_left > Max_size) {
            return;
        }
        if(array[index2]!=-1 || array[index1]!=-1) {
            array[index1] = array[index2];
            leftup(index2,index_left);
            leftup(index1*2+2,index_right);
        }
    }


};

class BST {
    public:
    Node* root;
    BST(Node* root) {
        this->root = root;
    }
    void insert(int data)
    /*
     *二叉排序树允许重复元素 重复元素插入时放在已有元素右子树位置
     *
     *1.如果无根节点 以data为值创建根节点
     *2.若有根节点 以data为值创建新节点s 申请指针p q均指向根节点
     *3.若p非空 q=p 判断若q->data>s-data  p=p->left 否则  p=p->right
     *4.若p空，若q空 return 否则 判断q->data>s->data q->left=s
     *5.否则 q->right=s
     */
    {
        if (root == nullptr) {
            root = new Node(data);
        }
        else {
            Node *s = new Node(data) ;
            Node *p = root;
            Node *q = nullptr;

            q = search(data);//借用q来存储找到的结点
            if (q != nullptr) {
                if(q->right == nullptr) {
                    q->right = s;
                }
                else {
                    s->right = q->right;
                    q->right = s;
                }
            }
            else {
                while (p != nullptr) {
                    q = p;
                    if (p->data > s->data) p = p->left;
                    else if (p->data < s->data) p = p->right;
                }
                if(q==nullptr) {
                    return;
                }
                if(q->data > s->data) q->left = s;
                else q->right = s;

            }
        }
    }

    void Print_data(Node *p) {
        if (p == nullptr) return;
        cout << p->data << " ";
    }

    string inorder() {
        stringstream ss;
        inorderREC(root,ss);
        return ss.str();
    }
    void inorderREC(Node *root,stringstream &ss) {
        if (root == nullptr) return;
        inorderREC(root->left,ss);
        ss<<root->data<<" ";
        inorderREC(root->right,ss);
    }

    string inorder2() {
        stringstream ss;
        inorder2REC(root,ss);
        return ss.str();
    }


    void inorder2REC(Node *root,stringstream &ss)
    /*申请指针p指向root 创建堆栈stack
     *当p或stack非空时，将p入栈 并将p指向其左孩子结点
     *此过程中若p为空 则pop一个元素出栈并赋值给p 输出p 并将p指向右孩子
     *重复
     */
    {
        if (root == nullptr) return;
        Node *p = root;
        Node_stack stack1;
        while(p||!stack1.isEmpty()) {
            if(p) {
                stack1.stack_push(p);
                p = p->left;
            }
            else {
                p = stack1.stack_top();
                stack1.stack_pop();
                ss<<p->data<<" ";
                p = p->right;
            }
        }
    }

    Node* search(int p)
/*
 * 若根为空 返回
 * 申请q指向根节点
 * 当q非空时 判断q->data和p大小 若> q指向自己的左子树 否则反之
 *
 */
    {
        if (root == nullptr) return nullptr;
        Node *q = root;
        while(q!=nullptr) {
            if (p > q->data) {
                q = q->right;
            }
            else if (p < q->data) {
                q = q->left;
            }
            else if (p == q->data) {
                return q;
            }
        }
        return nullptr;
    }

    int searchlength(int p)
/*
* 若根为空 返回
* 申请q指向根节点
* 当q非空时 判断q->data和p大小 若> q指向自己的左子树 否则反之
*
*/
   {
        int length = 0;
        if (root == nullptr) return 0;
        Node *q = root;
        while(q!=nullptr) {
            if (p > q->data) {
                q = q->right;
                length++;
            }
            else if (p < q->data) {
                q = q->left;
                length++;
            }
            else if (p == q->data) {
                length++;
                q=nullptr;
            }
        }
        return length;
   }
    Node* Parent_search(Node *p)
    {
        if (root == nullptr) return nullptr;
        Node *q = root;
        Node *s = root;
        if (p == root) return nullptr;
        while(q!=nullptr) {
            if (p->data > q->data) {
                s = q;
                q = q->right;
            }
            else if (p->data < q->data) {
                s = q;
                q = q->left;
            }
            else if (p->data == q->data && (s->left == p || s->right == p)){
                return s;
            }
            else {
                s=q;
                q = q->right;
            }
        }
        return nullptr;
    }

    string Node_delete(int x) {
        Node *p = search(x);
        Node *parent = Parent_search(p);
        if(p == nullptr) {
            cout<<"There is no x in this tree"<<endl;
        }
        else {
            /*
             * 分三种情况
             * 1.要删除的结点为叶子结点
             * 2.有左（右）子树
             * 3.有左右子树
             * 此外 因为二叉排序树允许有重复值的结点，要都删除掉
             */
            while( p != nullptr ) {
                Node *q = p;
                Node *child;
                if(p->right != nullptr && p->left != nullptr) {
                    parent = p;
                    p = p->right;
                    while(p->left) {
                        parent = p;
                        p = p->left;
                    }

                }

                child = (p->left)?p->left:p->right;
                if(!parent) root = child;
                else {
                    if(parent->left == p) {
                        parent->left = child;
                    }
                    else parent->right = child;
                }
                if (q!=p) q->data = p->data;
                p = search(x);
            }

        }
        string str =inorder2();
        return str;
    }

};


class AVL : public BST {
    public:
    void insert(int data)
    /*
     *二叉排序树允许重复元素 重复元素插入时放在已有元素右子树位置
     *
     *1.如果无根节点 以data为值创建根节点
     *2.若有根节点 以data为值创建新节点s 申请指针p q均指向根节点
     *3.若p非空 q=p 判断若q->data>s-data  p=p->left 否则  p=p->right
     *4.若p空，若q空 return 否则 判断q->data>s->data q->left=s
     *5.否则 q->right=s
     *
     *
     *AVL需要在插入后判断tree是否还是AVL 所以需要加入平衡因子BF的判断
     */
    {


        if (root == nullptr) {
            root = new Node(data);
        }
        else {
            Node *s = new Node(data) ;
            Node *p = root;
            Node *q = nullptr;
            My_queue my_queue;
            q = search(data);//借用q来存储找到的结点
            if (q != nullptr) {  //处理相同元素
                if(q->right == nullptr) {
                    q->right = s;
                }
                else {
                    s->right = q->right;
                    q->right = s;
                }
            }
            else {
                while (p != nullptr) {
                    q = p;
                    if (p->data > s->data) p = p->left;
                    else if (p->data < s->data) p = p->right;
                }
                if(q==nullptr) {
                    return;
                }
                if(q->data > s->data) q->left = s;
                else q->right = s;
            }//插入结束 开始判断is_AVL?
            if(get_bf(root)>1) {
                while(get_bf(s) <= 1){
                    Node *father = Parent_search(s);
                    my_queue.enqueue(s);
                    if (abs(my_queue.front-my_queue.rear) > 2) {
                        my_queue.dequeue();
                    }
                    s = father;
                }
                my_queue.enqueue(s);
                Node * node1 = my_queue.dequeue();
                Node * node2 = my_queue.dequeue();
                Node * node3 = my_queue.dequeue();
                balance(node1, node2, node3);
            }
        }
    }

    void balance(Node *node1, Node *node2, Node *node3) {
        if (node3->left == node2) {
            if (node2->left == node1) {
                LL(node1, node2, node3);
            } else {
                LR(node1, node2, node3);
            }
        } else {
            if (node2->left == node1) {
                RL(node1, node2, node3);
            } else {
                RR(node1, node2, node3);
            }
        }
    }

    void LL(Node *node1,Node *node2,Node *node3) {
            Node *parent = Parent_search(node3);
            node3->left = node2->right;
            node2->right = node3;
        if (parent == nullptr) {root = node2;}
        else parent->left == node3 ? parent->left = node2 : parent->right = node2;
    }

    void LR(Node *node1,Node *node2,Node *node3) {
        Node *parent = Parent_search(node3);
        node2->right = node1->left;
        node3->left = node1->right;
        node1->right = node3;
        node1->left = node2;
        if (parent == nullptr) {root = node1;}
        else parent->left == node3 ? parent->left = node1 : parent->right = node1;
    }

    void RL(Node *node1,Node *node2,Node *node3) {
        Node *parent = Parent_search(node3);
        node3->right = node1->left;
        node2->left = node1->right;
        node1->right = node2;
        node1->left = node3;
        if (parent == nullptr) {root = node1;}
        else parent->left == node3 ? parent->left = node1 : parent->right = node1;
    }

    void RR(Node *node1,Node *node2,Node *node3) {
        Node *parent = Parent_search(node3);
        node3->right = node2->left;
        node2->left = node3;
        if (parent == nullptr) {root = node2;}
        else parent->right == node3 ? parent->right = node2 : parent->left = node2;
    }

    int get_Height(Node *p) {
        if (p == nullptr) return 0;
        return (1+my_max(get_Height(p->left), get_Height(p->right)));
    }
    int get_bf(Node *p) {
        if (p == nullptr) return 0;
        int BF = abs(get_Height(p->left) - get_Height(p->right));
        return BF;
    }
};







int main() {


    ifstream inFile("input.txt", ios::in);
    if (!inFile) {  // 检查文件是否成功打开
        cout << "Error: Unable to open file for reading." << endl;
        return 1;
    }
    ofstream outFile("output.txt", ios::out);
    if (!outFile) {  // 检查文件是否成功打开
        cout << "Error: Unable to open file for writing." << endl;
        return 1;
    }
    BST tree(nullptr);
    AVL avlt(nullptr);
    array_BST array_bst1(55000);


    // 逐行读取文件内容
    string line;
    cout << "\nFile content:" << endl;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    stringstream ss(line);  // 使用字符串流解析输入
    vector<int> numbers;     // 存储分割后的整型数组
    int number;
    // 使用字符串流和 >> 操作符将字符串分割并转为整数
    while (ss >> number) {
        numbers.push_back(number);
    }
    // 插入数据到二叉树
    for (int value : numbers) {
        tree.insert(value);
        avlt.insert(value);
        array_bst1.insert(value);
    }
    // 测试BST递归中序遍历
    outFile << "Inorder traversal of BST (recursive): "<<tree.inorder()<<endl;
    // 测试AVL非递归中序遍历
    outFile << "Inorder traversal of AVL (non-recursive): " << avlt.inorder2()<<endl;
    // 测试ARRAY_BST递归中序遍历
    outFile << "Inorder traversal of array_BST (recursive): " << array_bst1.inorder() <<endl;


    float search_length_bst = 0,counter = 0,search_length_avl = 0,search_length_arr = 0;
    for(int value :numbers) {
        search_length_bst+=tree.searchlength(value);
        search_length_avl+=avlt.searchlength(value);
        search_length_arr+=array_bst1.search_length(value);
        counter+=1;
    }
    outFile << "ASL of BST = " << search_length_bst<<"/"<<counter << endl;
    outFile << "ASL of AVL = " << search_length_avl<<"/"<<counter << endl;
    outFile << "ASL of ARR_BST = " << search_length_arr<<"/"<<counter << endl;

    //测试BST删除
    outFile << "Delete one node in the BST: " <<tree.Node_delete(40)<<endl;
    //测试ARRAY_BST删除
    outFile << "Delete one node in the array_BST: "<< avlt.Node_delete(1)<<endl;


    // 关闭文件
    inFile.close();
    // 关闭文件
    outFile.close();
    cout << "File written successfully!" << endl;
    return 0;
}
