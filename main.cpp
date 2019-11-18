#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    /// Creating stack:
    printf("Creating stack\n");
    Stack_T<int> Stack;
    Stack.Construct();
    Stack.Push(10);
    Stack.Push(9);
    Stack.Push(8);
    Stack.Push(7);
    Stack.Push(6);
    Stack.Push(5);
    Stack.Push(4);
    Stack.Push(3);
    Stack.Push(2);
    Stack.Push(1);
    Stack.Push(0);
    Stack.Push(100);
    Stack.Print_Stack();
    Stack.Pop();
    Stack.Push(-1);
    Stack.Print_Stack();
    Stack.Destruct();
}