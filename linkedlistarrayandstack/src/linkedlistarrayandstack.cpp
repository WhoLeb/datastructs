#include "Linked_List.h"
#include "dynamic_array.h"
#include "Stack.h"
#include <string>
#include <iostream>
#include <random>

std::string ifix2pfix(std::string& string);

int main()
{

    
    std::string string;
    std::getline(std::cin >> std::ws, string);

    std::string res = ifix2pfix(string);
   
    std::cout << res << std::endl;
    
    system("pause");
}


std::string ifix2pfix(std::string& string)
{
    std::string nums = "0123456789";
    std::string funcs = "sincos";
    std::string operators = "+-*/^";
    std::string braces = "()";
    std::string res = "";
    WhoLeb::stack<std::string> my_stack;
    WhoLeb::dynamic_array<std::string> tokens;

    while (!string.empty())
    {
        if (string.find_first_of(" ") == -1)
        {
            tokens.add_element(tokens.size(), string.substr(0, string.size()));
            string.replace(string.begin(), string.end(), "");
            break;
        }
        tokens.add_element(tokens.size(), string.substr(0, string.find_first_of(" ")));
        string.replace(0, string.find_first_of(" ") + 1, "");
    }

    for (int tok = 0; tok < tokens.size(); tok++)
    {
        if (nums.find_first_of(tokens[tok]) != -1)
        {
            res += tokens[tok] + " ";
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
            while (
                !my_stack.empty() &&
                operators.find_first_of(my_stack.top()) / 2 >= t / 2 &&
                operators.find_first_of(my_stack.top()) != -1
                )
            {
                res += my_stack.top() + " ";
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
                res += my_stack.top() + " ";
                my_stack.pop();
                if (my_stack.empty())
                {
                    std::cout << "\nMissed an opening bracket\n";
                    break;
                }
            }
            my_stack.pop();
            if (
                !my_stack.empty() &&
                funcs.find_first_of(my_stack.top()) != -1
                )
            {
                res += my_stack.top() + " ";
                my_stack.pop();
            }
            continue;
        }

    }

    while (!my_stack.empty())
    {
        res += my_stack.top() + " ";
        my_stack.pop();
    }

    return res;
}