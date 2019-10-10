#pragma once

#include<iostream>
#include<string>
#include<cmath>
#include<ctype.h>
#include<algorithm>
#include<map>
#include<set>
#include<list>
#include<vector>
#include<stack>
#include<queue>
#include<strstream>
#include<fstream>
const int N = 9999999;
using namespace std;
//bool assign_flag = 1;
enum Data_type { INT, CHAR };
struct Data
{
    Data_type datatag;
    union
    {
        int num;
        char c;
    };
};
struct binarynode
{
    Data element;
    binarynode* lchild, * rchild;
    binarynode()
    {
        lchild = rchild = nullptr;
    }
    binarynode(const Data& e)
    {
        element = e;
        lchild = rchild = nullptr;
    }
    binarynode(const Data& e, binarynode* l, binarynode* r)
    {
        element = e;
        lchild = l;
        rchild = r;
    }
};
class binarytree//为了递归调用is_all_assigned,inborder,preorder都需要传入参数
{
private:
    bool assign_flag = 1;
    binarynode* root;
    int size;
    bool isoperator(char op)
    {
        if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^')
            return true;
        else
            return false;
    }
    bool pricmp(char a, char b)//true:a>b  false:b>a
    {
        if (isoperator(a) && isoperator(b))
        {
            if (a == '^')
            {
                if (b == '^') return true;
                else return false;
            }
            else if (a == '*' || a == '/')
            {
                if (b == '*' || b == '/' || b == '^')return false;
                else return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    void maketree(const Data& e, binarytree& l, binarytree& r)
    {
        root = new binarynode(e, l.root, r.root);
        size = l.size + r.size;
        l.root = r.root = nullptr;
        l.size = r.size = 0;
    }
    bool judge_type(/*binarynode p,*/char c)//数字返回1，字母返回0
    {
        if (isdigit(c))
        {
            root->element.datatag = INT;
            root->element.num = c - '0';
            return 1;
        }
        else
        {
            root->element.datatag = CHAR;
            root->element.c = c;
            return 0;
        }
    }
    void is_all_assigned(binarynode* r)//检查表达式中的变量是否全部赋值
    {
        if (r != nullptr && r->element.datatag == CHAR)
        {
            //cout << r->element.c << " ";
            //isalpha(r->element.c)
            if (r->element.c!='+'&& r->element.c != '-'&&r->element.c != '*'&& r->element.c != '/'&& r->element.c != '^')
            {
                cout << "变量" << r->element.c << "未赋值" << endl;
                assign_flag = 0;
                return;
            }
            is_all_assigned(r->lchild);
            is_all_assigned(r->rchild);
        }
    }
    int calculate(int a, char op, int b)
    {
        if (op == '+')
            return a + b;
        else if (op == '-')
            return a - b;
        else if (op == '*')
            return a * b;
        else if (op == '/')
        {
            if (b == 0)
            {
                cout << "除数不能为0！" << endl;
                return N;
            }
            else
                return a / b;
        }
        else if (op == '^')
            return pow(a, b);
    }
public:
    void preorder_output()
    {
        //cout << "前缀表达式：" << endl;
        preorder(root);
        cout << endl;
    }
    void preorder(binarynode* r)

    {
        ofstream out("preorder.txt");

        if (r != nullptr)
        {
            if (r->element.datatag == INT)
                out << r->element.num;
            else
                out << r->element.c;
            preorder(r->lchild);
            preorder(r->rchild);
        }
    }
    void inorderbacket_output()
    {
        cout << "完全括号化的中缀表达式：";
        inorder_allbacket(root);
        cout << endl;
    }
    void inorder_allbacket(binarynode* r)
    {
        if (r != nullptr)
        {
            cout << "(";
            inorder_allbacket(r->lchild);
            if (r->element.datatag == INT)
                cout << r->element.num;
            else
                cout << r->element.c;
            inorder_allbacket(r->rchild);
            cout << ")";
        }
    }
    void WriteExpr()
    {
//        cout << "带括号的中缀表达式：";
        writeexpr(root);
//        cout << endl;
    }
    void writeexpr(binarynode* r)
    {
        ofstream out("inorder.txt");

        if (r != nullptr)
        {
            if (r->lchild && r->lchild->element.datatag == CHAR)
            {
                if (pricmp(r->element.c, r->lchild->element.c))//当前节点优先级高于左孩子
                {
                    out << "(";
                    writeexpr(r->lchild);
                    out << ")";
                }
                else
                    writeexpr(r->lchild);
            }
            else
                writeexpr(r->lchild);

            if (r->element.datatag == INT)
                out << r->element.num;
            else
                out << r->element.c;

            if (r->rchild && r->rchild->element.datatag == CHAR)
            {
                if (pricmp(r->element.c, r->rchild->element.c))
                {
                    out << "(";
                    writeexpr(r->rchild);
                    out << ")";
                }
                else
                    writeexpr(r->rchild);
            }
            else
                writeexpr(r->rchild);
        }
    }
    bool ReadExptr(string str)
    {
        stack<binarynode*> s;
        //stack<int> nums;
        binarynode p, q;
        int len = str.length();
        root = new binarynode;//****************
        root->lchild = root->rchild = nullptr;
        if (len == 1)
        {
            if (isdigit(str[0]))
            {
                root->element.datatag = INT;
                root->element.num = str[0] - '0';
                return true;
            }
            else if (isalpha(str[0]))
            {
                root->element.datatag = CHAR;
                root->element.c = str[0];
                return true;
            }
            else
            {
                cout << "非法输入！" << endl;
                return false;
            }
        }
        else
        {
            for (int i = len - 1; i >= 0; i--)
            {
                binarynode* pnode = new binarynode;
                if (isdigit(str[i]))
                {
                    pnode->element.datatag = INT;
                    pnode->element.num = str[i] - '0';
                }
                else
                {
                    //cout << str[i] << " ";
                    pnode->element.datatag = CHAR;
                    pnode->element.c = str[i];
                }
                pnode->lchild = nullptr; pnode->rchild = nullptr;

                /*if (isdigit(str[i]))
                    nums.push(str[i] - '0');*/
                if (isoperator(str[i]))
                {
                    pnode->lchild = s.top(); s.pop();
                    pnode->rchild = s.top(); s.pop();
                }
                s.push(pnode);
            }
            root = s.top();
            s.pop();//弹出最终的结果表达式
            if (s.empty())//若s中为空，则构造成功
                return true;
            else//若s中还有东西，则构造失败
            {
                cout << "ERROR!!!" << endl;
                return false;
            }
        }
    }
    void assign(binarynode* r, char v, int& num)
    {
        if (r != nullptr)
        {
            if (r->element.datatag == CHAR && r->element.c == v)
            {
                //cout << r->element.c << "=" << v << "=" << num;
                r->element.datatag = INT;
                r->element.num = num;

                //错误输入处理：修改num值为N，之后用来 判断是否成功赋值。
                num = N;
            }
            assign(r->lchild, v, num);
            assign(r->rchild, v, num);
        }
    }
    void Assign(char v, int num)
    {
        assign(root, v, num);
        if (num != N)
            cout << "本次未成功赋值，请勿输入表达式中不存在的变量。" << endl;
    }
    int Value(binarynode* r)
    {
        if (r != nullptr)
        {
            if (r->lchild == nullptr && r->rchild == nullptr && r->element.datatag == INT)//到达底层
                return r->element.num;
            return calculate(Value(r->lchild), r->element.c, Value(r->rchild));
        }
    }
    void Value_output()
    {
        //cout <<"assign="<< assign_flag << endl;
        is_all_assigned(root);
        //cout<<"assign=" << assign_flag << endl;
        if (assign_flag)//全赋值
        {
            writeexpr(root); cout << "=";
            cout << Value(root) << endl;
        }
        else
        {
            cout << "含有未赋值的变量，无法计算表达式的值！" << endl;
            assign_flag = 1;
        }
    }
    void CompoundExpr(char p, binarytree a, binarytree b)
    {
        root = new binarynode;
        root->element.datatag = CHAR;
        root->element.c = p;
        root->lchild = a.root;
        root->rchild = b.root;
        cout << "复合表达式：";
        writeexpr(root);
        cout << endl;
    }
    void mergeconst(binarynode* r)
    {
        if (r->lchild != nullptr && r->rchild != nullptr)
        {
            if (r->lchild->element.datatag == INT && r->rchild->element.datatag == INT)
            {
                int ans = calculate(r->lchild->element.num, r->element.c, r->rchild->element.num);
                r->element.datatag = INT;
                r->element.num = ans;
                delete r->lchild;
                delete r->rchild;
                r->lchild = r->rchild = nullptr;
            }
            else
            {
                mergeconst(r->lchild);
                mergeconst(r->rchild);
            }
        }
    }
    void MergeConst()
    {
        mergeconst(root);
        writeexpr(root);
        cout << endl;
    }
};
