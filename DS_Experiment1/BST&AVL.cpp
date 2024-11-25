#include<iostream>
#include<fstream>
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
    Node* Parent_search(int p)
    {
        if (root == nullptr) return nullptr;
        Node *q = root;
        Node *s = nullptr;
        while(q!=nullptr) {
            if (p > q->data) {
                s = q;
                q = q->right;
            }
            else if (p < q->data) {
                s = q;
                q = q->left;
            }
            else if (p == q->data) {
                return s;
            }
        }
        return nullptr;
    }

    void Node_delete(int x) {
        Node *p = search(x);
        Node *parent = Parent_search(x);
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








int main() {
    // 创建根节点为空的BST
    BST tree(nullptr);

    // 插入数据到二叉树
    int values[] = {50,1,1, 30, 70, 20, 40, 60, 80,19,231,32,435,35,2,3,4,5,6,7,8,9,10};
    for (int value : values) {
        tree.insert(value);
    }
    tree.Node_delete(1);
    // 测试递归中序遍历
    cout << "Inorder traversal (recursive): ";
    tree.inorder(tree.root);
    cout << endl;

    // 测试非递归中序遍历
    cout << "Inorder traversal (non-recursive): ";
    tree.inorder2(tree.root);
    cout << endl;

    int search_length = 0,counter = 0;
    for(int value :values) {
        search_length+=tree.searchlength(value);
        counter+=1;
    }
    cout << "ASL = " << search_length/counter << endl;
    return 0;
}
