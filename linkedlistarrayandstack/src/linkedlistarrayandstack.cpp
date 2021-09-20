#include "Linked_List.h"
#include "dynamic_array.h"
#include <iostream>

int main()
{    
    WhoLeb::Linked_List<int> my_list(2, 1, 2);
    my_list.create_node(1, 3);
    for (int i = 0; i < my_list.get_length(); i++)
        std::cout << my_list[i]->value << " ";
    my_list.remove_node(0);
    for(int i = 0; i < my_list.get_length(); i++)
        std::cout << my_list[i]->value << " ";
    std::cout << std::endl;

    WhoLeb::dynamic_array<int> my_array(5);
    my_array.print_array();
    my_array.push_back(4);
    my_array.add_elements(2, 4);
    my_array.remove_elements(1, 3);
    my_array.print_array();

    system("pause");
}
