#include <iostream>
using namespace std;

// some constants
const int null = 0x0000;

/** function declaration begin **/
int abs(int a)
{
  return a>0?a:-a;
}
/** function declaration end **/

/** new data type begin **/
// linked list
template <class T>
class Node
{
    public:
        T data;
        Node<T> *next;
        Node(){}
        Node(T e)
        {
            // be careful, we need to override the operator= to be deep-copy
            // otherwise, data access will be illegal since its pointing
            // memory has already been marked as free and maybe modified by
            // other newly born variables.
            data = e;
            next = null;
        }
    ~Node()
    {
        delete next;
    }
};

template <class T>
class List
{
    protected:
        Node<T> *head, *tail, *cursor;
        int length;
    public:
        int getLength()
        {
            return length;
        }
        List()
        {
            head = tail = cursor = null;
            length = 0;
        }
    
        int add(T e)
        {
            Node<T> *t = new Node<T>(e);
            if(head==null)
            {
                tail = cursor = head = t;
            }
            else {
                tail->next = t;
                tail = tail->next;
            }
         
            ++length;
            return 0;
        }
    
        int rewind()
        {
            cursor = head;
            return 0;
        }
        bool hasNext()
        {
            if(cursor==null)
            {
                return false;
            }
            else {
                return true;
            }
        }
        T next()
        {
            if(cursor==null)
            {
                throw("iterator exceed size!\n");
                cerr<<"Error in Running Time"<<endl;
            }
            Node<T>* t;
            t = cursor;
            cursor = cursor->next;
            return t->data;
        }
        // deep copy but share same memory of base data
        List<T> operator=(List lst)
        {
            head = lst.head;
            tail = lst.tail;
            cursor = lst.cursor;
            length = lst.length;
            return *this;
        }
    ~List()
    {
        delete head;
        head = tail = cursor = null;
    }
};


// single Number
class N
{
    private:
        int data;
    // 1 stand for negative, 0 for positive
        bool sign;
    public:
        N()
        {
            data = 0;
            sign = 0;
        }
        N(int a)
        {
            int aa=abs(a);
            if(aa<10)
            {
                data = aa;
                sign = abs(a)<a?1:0;
            }
            else {
                cout<<"\nRuntime Error:Initial N type object failed, illegal argument!\n";
            }
        }
        int getData()
        {
            return data;
        }
        int getSign()
        {
            return sign;
        }
        // deep copy
        N operator=(N b)
        {
            data = b.getData();
            sign = b.getSign();
            return *this;
        }
        // print
        int print()
        {
            if(sign){cout<<"+";}
            else{cout<<"-";}
            cout<<data;
            return 0;
        }
};

// build rules to give result of mulitipy 2 number
// 2 look-up tables for fundamental + & * operators
class Dict
{
    private:
        N MUL[10][10][2];
        N ADD[10][10][2];
        int initialed;
    public:
        Dict(){initialed=0;}
        Dict initial()
        {
            initialed = 1;
            int i=0,j=0;
            for(;i<10;i++)
            {
                for(;j<10;j++)
                {
                    ADD[i][j][0]=N((i+j)%10);
                    ADD[i][j][1]=N((i+j)/10);
                    MUL[i][j][0]=N((i*j)%10);
                    MUL[i][j][1]=N((i*j)/10);
                }
            }
            return *this;
        }
        N* add(N i,N j)
        {
            if(!initialed)
            {
                initial();
            }
            return ADD[i.getData()][j.getData()];
        }
        N* mul(N i,N j)
        {
            if(!initialed)
            {
                initial();
            }
            return MUL[i.getData()][j.getData()];
        }
};

// multi-number
class M
{
    protected:
        List<N> data;
        int length;
    public:
        int getLength()
        {
            return length;
        }
        List<N> getData()
        {
            return data;
        }
        M(){}
        M(int a)
        {
            int r=a;
            data = List<N>();
            N tmp;
            while(r>=10)
            {
                tmp = N(r%10);
                data.add(tmp);
                r=r/10;
            }
            tmp = N(r);
            data.add(tmp);
            length = data.getLength();
        }
        // another way to construct a M type number
        M setData(List<N> dt)
        {
            data = dt;
            return *this;
        }
        //print
        int print()
        {
            data.rewind();
            while(data.hasNext())
            {
                data.next().print();
            }
            return 0;
        }
        
        M operator=(M a)
        {
            data = a.getData();
            length = a.getLength();
            return *this;
        }
        M operator+(M a)
        {
            List<N> lst;
            List<N> pri;
            List<N> adv;
            Dict dic;
            int max=a.getLength()>length?a.getLength():length;
            int dif=abs(a.getLength()-length);
            // reset cursor
            data.rewind();
            // advanced bits have residue one
            adv.add(N(0));
            
            while(max>dif)
            {
                max--;
                N* tmp = dic.add(data.next(),a.getData().next());
                pri.add(tmp[0]);
                adv.add(tmp[1]);
            }
            while(max>0)
            {
                max--;
                N p = a.getLength()>length?a.getData().next():data.next();
                pri.add(p);
                N a = N(0);
                adv.add(a);
            }
            pri.add(N(0));
            // add together of primary and advanced bits
            while(pri.hasNext())
            {
                N* tmp = dic.add(pri.next(),adv.next());
                lst.add(tmp[0]);
            }
            M all(0);
            all.setData(lst);
            return all;
        }
};


int main(int argc, const char** argv)
{
    M m1(3);
    M m2(5);
    M m3 = m1 + m2;
    m3.print();
    
    return 0;
}
