#include<iostream>
#include<fstream>
#include<cmath>
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
                if (d > array[index]) {
                    index = 2 * index + 2; // 右子节点
                }
                else {
                    index = 2 * index + 1; // 左子节点
                }
            }
        }
    }
    void inorder(int *array, int index, int size) {
        if(index >= Max_size || array[index] == -1) {
            return;
        }
        inorder(array, 2*index+1,size);
        cout<<array[index]<<" ";
        inorder(array, 2*index+2,size);
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
                return index;
            }
            if (d > array[index]) {
                index = 2 * index + 1;
                length++;
            }
            else {
                index = 2 * index + 2;
                length++;
            }
        }
    }
    void my_delete1(int d) {
        int index = search(d); // 搜索目标节点的索引
        if (index == -1) {
            cout << "ERROR: Value " << d << " not found in the tree." << endl;
            return;
        }

        // 处理叶子节点
        if (array[2 * index + 1] == -1 && array[2 * index + 2] == -1) {
            array[index] = -1; // 直接将叶子节点置为空
        }
        // 处理只有左子树的节点
        else if (array[2 * index + 1] != -1 && array[2 * index + 2] == -1) {
            int replacementIndex = 2 * index + 1; // 左子树
            // 找到左子树的最右节点
            while (array[2 * replacementIndex + 2] != -1) {
                replacementIndex = 2 * replacementIndex + 2;
            }
            array[index] = array[replacementIndex]; // 用最右节点的值替换目标节点
            array[replacementIndex] = -1;          // 删除最右节点
        }
        // 处理只有右子树的节点
        else if (array[2 * index + 1] == -1 && array[2 * index + 2] != -1) {
            int replacementIndex = 2 * index + 2; // 右子树
            // 找到右子树的最左节点
            while (array[2 * replacementIndex + 1] != -1) {
                replacementIndex = 2 * replacementIndex + 1;
            }
            array[index] = array[replacementIndex]; // 用最左节点的值替换目标节点
            array[replacementIndex] = -1;          // 删除最左节点
        }
        // 处理同时有左右子树的节点
        else {
            int replacementIndex = 2 * index + 2; // 默认用右子树的最左节点
            // 找到右子树的最左节点
            while (array[2 * replacementIndex + 1] != -1) {
                replacementIndex = 2 * replacementIndex + 1;
            }
            array[index] = array[replacementIndex]; // 用最左节点的值替换目标节点
            array[replacementIndex] = -1;          // 删除最左节点
        }

        cout << "Deleted " << d << " successfully." << endl;

        // 调用中序遍历打印结果
        cout << "Inorder Traversal after Deletion: ";
        inorder(array, 0, Max_size);
        cout << endl;
    }
    void my_delete(int d) {
        int index = search(d);
        int index1 = index;
        if(index == -1){
            return;
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
            inorder(array,0,size);
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

    void inorder(Node *root) {
        if (root == nullptr) return;
        inorder(root->left);
        Print_data(root);
        inorder(root->right);
    }

    void inorder2(Node *root)
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
                Print_data(p);
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
        Node *s = nullptr;
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

    void Node_delete(int x) {
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
    // 创建根节点为空的BST
    BST tree(nullptr);
    AVL avlt(nullptr);
    array_BST array_bst1(55000);
    // 插入数据到二叉树
    int values1[] = {1,2,3};
    int values[] = {50,1,1, 30, 70, 20, 40, 60, 80,19,231,32,435,35,2,3,4,5,6,7,8,9,10};
    for (int value : values) {
        tree.insert(value);
        avlt.insert(value);
        array_bst1.insert(value);
    }
    // 测试递归中序遍历
    cout << "Inorder traversal (recursive): ";
    tree.inorder(tree.root);
    cout << endl;

    // 测试非递归中序遍历
    cout << "Inorder traversal (non-recursive): ";
    tree.inorder2(tree.root);
    cout << endl;

    cout << "Inorder traversal (recursive): ";
    array_bst1.inorder(array_bst1.array,0,array_bst1.size);
    cout << endl;
    array_bst1.my_delete(50);
    cout<<endl;

    float search_length_bst = 0,counter = 0,search_length_avl = 0,search_length_arr = 0;
    for(int value :values) {
        search_length_bst+=tree.searchlength(value);
        search_length_avl+=avlt.searchlength(value);
        search_length_arr+=array_bst1.search_length(value);
        counter+=1;
    }
    cout << "ASL of BST = " << search_length_bst<<"/"<<counter << endl;
    cout << "ASL of AVL = " << search_length_avl<<"/"<<counter << endl;
    cout << "ASL of ARR_BST = " << search_length_arr<<"/"<<counter << endl;
    return 0;
}
