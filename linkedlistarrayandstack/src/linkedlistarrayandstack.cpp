#include "Linked_List.h"
#include "dynamic_array.h"
#include <iostream>

int main()
{    
    /*WhoLeb::Linked_List<int>* my_list = new WhoLeb::Linked_List<int>(5);
    my_list->print_list();
    my_list->create_nodes(3, 3);
    my_list->print_list();
    my_list->change_node(2, 0);
    my_list->remove_nodes(2, 4);
    my_list->print_list();*/

    WhoLeb::dynamic_array<int> my_array(5);
    my_array.print_array();
    my_array.push_back(4);
    my_array.add_elements(2, 4);
    my_array.remove_elements(1, 3);
    my_array.print_array();

    system("pause");
}
