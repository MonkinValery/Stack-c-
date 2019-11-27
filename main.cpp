//#define NOSECURE
#include "stack.h"
#include <stdio.h>

int main()
{
    /// Creating stack:
    printf("Creating stack\n");
    Stack_T<int> Stack;
    Stack.Construct();
    Stack.Push(10, Stack);
    Stack.Push(9, Stack);
    Stack.Push(8, Stack);
    Stack.Push(7, Stack);
    Stack.Push(6, Stack);
    Stack.Push(5, Stack);
    Stack.Push(4, Stack);
    Stack.Push(3, Stack);
    Stack.Push(2, Stack);
    Stack.Push(1, Stack);
    Stack.Push(0, Stack);
    Stack.Push(100, Stack);
    Stack.Print_Stack();
    Stack.Pop();
    Stack.Push(-1, Stack);
    Stack.Print_Stack();
    Stack.Destruct();
}