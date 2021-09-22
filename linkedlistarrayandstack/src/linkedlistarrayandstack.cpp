#include "Linked_List.h"
#include "dynamic_array.h"
#include "Stack.h"
#include <string>
#include <iostream>
#include <random>

int main()
{

    WhoLeb::dynamic_array<std::string> nums(10, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" );
    WhoLeb::dynamic_array<std::string> funcs(2, "sin", "cos" );
    WhoLeb::dynamic_array<std::string> operators(5, "+", "-", "*", "/", "^" );
    WhoLeb::dynamic_array<std::string> braces(2, "(", ")" );

    WhoLeb::stack<std::string> my_stack;

    std::string string = "5 + 7 * 9";
    WhoLeb::dynamic_array<std::string> tokens;
    std::string res = "";
    while (string.find(" "))
    {
        tokens.add_element(tokens.size(), string.substr(0, string.find(" ")));
        string.replace(0, string.find(" "), "");
    }
    for (int tok = 0; tok < tokens.size(); tok++)
    {
        if (nums.find_first_of(tokens[tok]) != -1)
        {
            res += tokens[tok];
            continue;
        }
        if (funcs.find_first_of(tokens[tok]) != -1) 
        {
            my_stack.push(tokens[tok]);
            continue;
        }
        int t = operators.find_first_of(tokens[tok]);
        if (t != -1)
        {
            while (operators.find_first_of(my_stack.top()) > t)
            {
                res += my_stack.top();
                my_stack.pop();
            }
            my_stack.push(tokens[tok]);
            continue;
        }
        if (braces.find_first_of(tokens[tok]) == 0)
        {
            my_stack.push(tokens[tok]);
            continue;
        }
        if (braces.find_first_of(tokens[tok]) == 1)
        {
            while (my_stack.top() != "(")
            {
                res += my_stack.top();
                if (my_stack.empty())
                {
                    std::cout << "\nMissed an opening bracket\n";
                    break;
                }
            }
            my_stack.pop();
            if (funcs.find_first_of(my_stack.top()) != 1)
            {
                res += my_stack.top();
                my_stack.pop();
            }
            continue;
        }

    }

    while (!my_stack.empty())
    {
        res += my_stack.top();
        my_stack.pop();
    }

    std::cout << std::endl << res << std::endl;
    
    system("pause");
}

