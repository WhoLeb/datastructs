#include "Linked_List.h"
#include "dynamic_array.h"
#include "Stack.h"
#include <iostream>

int main()
{    

    
    WhoLeb::stack<int> my_stack;

    my_stack.push(5);
    my_stack.push(7);
    std::cout << my_stack.top();
    
    system("pause");
}

