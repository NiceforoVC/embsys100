#include "stack.h"
#define STACK_SIZE 3

// Backing store
int StackStore[STACK_SIZE];

// Pointers to stack elements for adding and retrieving
int* topPtr;
int* bottomPtr;
int* currentPtr;

// LIFO Stack is Empty if currentPtr == 0;
// LIFO Stack is Full if currentPtr == topPtr (points to top element in the Stack);

// Initialize internals of the stack
void stack_init(void)
{
    topPtr = &StackStore[STACK_SIZE-1];
    bottomPtr = &StackStore[0];
    currentPtr = 0;
    for(int i=0; i<STACK_SIZE; i++)
    {
        StackStore[i] = '\0';
    }
}

// Add data to stack
// If stack is full return error
// Otherwise return success
int stack_push(int data)
{
    if (stack_isFull() == 1)
    {
        // stack is full
        return -1;
    }
    
    if (currentPtr == 0)
    {
        currentPtr = bottomPtr;
    }    
    else
    {
        currentPtr++;
    }
    
    *currentPtr = data;
    
    return 0;
}

// Get data from stack
// If stack is empty return error
// Otherwise return success
int stack_pop(int* data)
{   
    if (stack_isEmpty() == 1)
    {
        // stack is empty
        return -1;
    }

    *data = *currentPtr;
    
    if (currentPtr == bottomPtr)
    {        
        currentPtr = 0;
    }
    else 
    {
        currentPtr--;
    }

    return 0;
}

// Check if stack is empty
// If stack is empty return 1
// Otherwise return 0
int stack_isEmpty()
{
  if (currentPtr == 0)
    return 1;
  else
    return 0;
}

// Check if stack is full
// If stack is full return 1
// Otherwise return 0
int stack_isFull()
{
  if (currentPtr == topPtr)
    return 1;
  else
    return 0;
}
