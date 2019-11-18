//
// Created by valer on 06.11.2019.
//


#include <iomanip>
#include <iostream>
#include <cassert>
#include <string>
using namespace std;


template <typename T>
class Stack_T
{
private:
    #ifndef NOSECURE
        long long Can1_;
    #endif
    int top_;
    T *stackPtr_;
    unsigned int size_ ;
    int error_;
    #ifndef  NOSECURE
        unsigned long hash_;
        long long Can2_;
        unsigned long Solve_hash();
        long long Solve_Can1();
        long long Solve_Can2();
    #endif

    void Assert_Stack(string);
    void Assert_ptr(string);
    bool StackOk();
    void StackDump();
public:
    bool Construct(int = 9);        //Create Stack
    bool Copy(const Stack_T<T> &);        //Copy Stack
    bool Destruct();         //Delete stack

    bool Push(const T &);         //Add new element to Stack
    T Pop();         //Delete last element of Stack
    void Print_Stack();  //Print one element of Stack
    void Print_Element(int);    //Print hole Stack
    const T &Peek(int) const;           //N element from the top of Stack
    int get_Stack_Size () const;         //Get size of Stack
    T *get_Ptr() const;          //Get pointer
    int get_Top() const;         //Get number of top element
};

template <typename T> //Stack construct
bool Stack_T<T>::Construct(int maxSize)
{
    stackPtr_ = new T[maxSize];  //Get memory for stack
    size_=maxSize;
    top_ = 0;
    #ifndef NOSECURE
        Can1_ = Solve_Can1();
    #endif
    string name="Construct";
    Assert_ptr(name);
    #ifndef NOSECURE
        hash_=Solve_hash();
        Can2_ = Solve_Can2();
    #endif
    return true;
}

template <typename T> //Copy stack
bool Stack_T<T>::Copy(const Stack_T & Other_Stack)
{
    string name="Copy";
    stackPtr_ = new T[size_];   //Get memory for new stack
    top_ = Other_Stack.get_Top();
    for (int ix=0; ix < top_; ix++)   //Copy stack
        stackPtr_[ix]=Other_Stack.get_Ptr()[ix];
    return true;
}

template <typename T> //Delete stack
bool Stack_T<T>::Destruct()
{
    string name="Destruct";
    delete [] stackPtr_;    //Deleting stack
    return true;
}

template <typename T> //Add element to stack
bool Stack_T<T>::Push(const T &value)
{
    string name="Push1";
    Assert_Stack(name);
    if (top_ == size_)
    {
        size_ += 10;
        stackPtr_ = (T*)realloc(stackPtr_,size_);
        #ifndef NOSECURE
            Can1_ = Solve_Can1();
            hash_=Solve_hash();
            Can2_ = Solve_Can2();
        #endif
    }
    stackPtr_[top_++] = value;
    #ifndef NOSECURE
        Can1_ = Solve_Can1();
        hash_=Solve_hash();
        Can2_ = Solve_Can2();
    #endif
    name="Push2";
    Assert_Stack(name);
    return true;
}

template <typename T> //Delete element from stack
T Stack_T<T>::Pop()
{
    string name="Pop";
    Assert_Stack(name);
    stackPtr_[top_--];
    #ifndef NOSECURE
        hash_=Solve_hash();
        Can1_ = Solve_Can1();
        Can2_ = Solve_Can2();
    #endif
    Assert_Stack(name);
    return 0;
}

template <typename T> //Return N element from top
const T &Stack_T<T>::Peek(int nom) const
{
    string name="Peek";
    return stackPtr_[top_ - nom];
}

template <typename T>
void Stack_T<T>::Print_Stack()
{
    string name="Print_Stack";
    printf("Elements of stack:\n");
    for (int ix = top_-1; ix >= 0; ix--)
    {
        Print_Element(ix);
    }
}

template <typename T>
void Stack_T<T>::Print_Element(int ix)
{
    string name="Print_Element";
    cout << "|" << setw(4) << stackPtr_[ix] << endl;
}

template <typename T>
int Stack_T<T>::get_Stack_Size() const
{
    string name="get_Stack_Size";
    return size_;
}

template <typename T>
T * Stack_T<T>::get_Ptr() const
{
    string name="get_Ptr";
    return stackPtr_;
}

template <typename T>
int Stack_T<T>::get_Top() const
{
    string name="get_Top";
    return top_;
}

template <typename T>
void Stack_T<T>::Assert_Stack(string name)
{
    if (!StackOk())
    {
        printf("Dump from %s\n", name.c_str());
        StackDump();
        abort();
    }
}

template <typename T>
void Stack_T<T>::Assert_ptr(string name)
{
    if (stackPtr_ == nullptr)
    {
        printf("ASSERT:%s /n:  pointer is NULL", name.c_str() );
        abort();
    }
}

enum ERRORS
{
        PTR_ERR = 1,
        SIZE_ERR = 2,
        NUMBER_ERR = 3,
        HASH_ERR = 4,
        CANARY_ERR1 = 5,
        CANARY_ERR2 = 6,
};



template <typename T>
 bool Stack_T<T>::StackOk()
{
    Assert_ptr("StackOk");

    if (stackPtr_ == nullptr)
    {
        error_ = PTR_ERR;
        return false;
    }
    if (&Can1_ == nullptr)
    {
        error_ = PTR_ERR;
        return false;
    }
    if (&Can2_ == nullptr)
    {
        error_ = PTR_ERR;
        return false;
    }
    if (Can1_ != Solve_Can1())
    {
        error_ = CANARY_ERR1;
        return false;
    }
    if (Can2_ != Solve_Can2())
    {
        error_ = CANARY_ERR2;
        return false;
    }
    if (top_ < 0)
    {
        error_ = NUMBER_ERR;
        return false;
    }
    if (top_ > size_)
    {
        error_ = SIZE_ERR;
        return false;
    }
    if (size_ < 1)
    {
        error_ = SIZE_ERR;
        return false;
    }
    if (hash_ != Solve_hash())
    {
        error_ = HASH_ERR;
        return false;
    }
    return true;
}

template <typename T>
void Stack_T<T>::StackDump()
{
    printf("\n\t\tDUMP\n");
    printf("ERROR:\t\t%d\n", error_);
    printf("Pointer of stack:");
    printf("\t\t%p\n", stackPtr_);
    printf("Capacity of stack:");
    printf("\t\t%d\n",size_);
    printf("Number of elements in stack:");
    printf("\t\t%d\n", top_);
    printf("Hash:");
    printf("\t\t\t%d\n", hash_);
    printf("First canary:");
    printf("\t\t%d\n",Can1_);
    printf("Second canary:");
    printf("\t\t%d\n",Can2_);
    Print_Stack();
}

template <typename T>
unsigned long Stack_T<T>::Solve_hash()
{
    return (((9804657-5460983564)*top_+top_*843756-size_/9083-1)/28796+6745/6473920);
}

template <typename T>
long long Stack_T<T>::Solve_Can1()
{
    return (97898740+size_*8236754-top_*8943756/25463);
}

template <typename T>
long long Stack_T<T>::Solve_Can2()
{
    return (7862345+Can1_*(29873642/235468-62354)-top_/76243+size_/2);
}