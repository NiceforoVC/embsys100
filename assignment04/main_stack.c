#include <assert.h>
#include "stack.h"

int main()
{
    int result1;
    int result2;
    int testInt;
    
    // *******************************************************************
    // Test1: Retrieve item from an empty stack
    // *******************************************************************
    // Arrange:
    result1 = 42;
    result2 = 42;
    testInt = 100;
    stack_init();
    
    // Act:
    result1 = stack_pop(&testInt);
    result2 = stack_isEmpty();
      
    // Assert:
    assert(-1 == result1);
    assert(1 == result2);
    assert(100 == testInt);
    
    
    // *******************************************************************
    // Test2: Successfully retrieve an item from the stack
    // *******************************************************************
    // Arrange:
    result1 = 42;
    result2 = 42;
    testInt = 100;
    stack_init();
    
    // Act:
    result1 = stack_push(50);
    result2 = stack_pop(&testInt);
    
    // Assert:
    assert(0 == result1);
    assert(0 == result2);
    assert(50 == testInt);
    
    
    // *******************************************************************
    // Test3: Fill stack, then get all items.
    // *******************************************************************
    // Arrange:
    result1 = 42;
    testInt = 100;
    stack_init();
    
    // Act:
    stack_push(10);
    stack_push(20);
    stack_push(30);  
    result1 = stack_isFull();
    
    // Assert:
    assert(1 == result1);
    
    assert(0 == stack_pop(&testInt));
    assert(30 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(20 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(10 == testInt);

    
    // *******************************************************************
    // Test4: Fill stack, then put one more item, should fail
    // *******************************************************************
    // Arrange:
    testInt = 100;
    stack_init();
    
    // Act:
    stack_push(10);
    stack_push(20);
    stack_push(30);
    
    // Assert:
    assert(0 == stack_isEmpty());
    assert(1 == stack_isFull());
    
    assert(-1 == stack_push(40));    

    assert(0 == stack_pop(&testInt));
    assert(30 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(20 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(10 == testInt);
    
    assert(1 == stack_isEmpty());
    assert(0 == stack_isFull());


    // ***********************************************************************
    // Test5: Fill stack, retrieve one item, then add item, then retrieve all
    // ***********************************************************************
    // Arrange:
    testInt = 100;
    stack_init();
    
    // Act:
    stack_push(10);
    stack_push(20);
    stack_push(30);
    
    // Assert:
    assert(0 == stack_pop(&testInt));
    assert(30 == testInt);

    assert(0 == stack_push(40));

    assert(0 == stack_pop(&testInt));
    assert(40 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(20 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(10 == testInt);

    
    // ***********************************************************************
    // Test6: Fill stack and retrieve all items twice
    // ***********************************************************************
    // Arrange:
    testInt = 100;
    stack_init();
    
    // Act:
    stack_push(10);
    stack_push(20);
    stack_push(30);
    
    // Assert:
    assert(0 == stack_pop(&testInt));
    assert(30 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(20 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(10 == testInt);

    assert(0 == stack_push(40));
    assert(0 == stack_push(50));
    assert(0 == stack_push(60));
    
    assert(-1 == stack_push(70));

    assert(0 == stack_pop(&testInt));
    assert(60 == testInt);
   
    assert(0 == stack_pop(&testInt));
    assert(50 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(40 == testInt);

    return 0;
}
