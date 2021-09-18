#pragma once
#include <iostream>
namespace WhoLeb
{
    template<class T>
    class Linked_List
    {
    public:
        Linked_List(T& arr);
        Linked_List(const unsigned int size);
        Linked_List(Linked_List* Head) : head(Head) {}
        Linked_List() : head(nullptr) {}
        ~Linked_List() = default;
        
        void print_list();
        void create_nodes(const unsigned int count, const unsigned int place);
        void change_node(unsigned const int place, T new_val);
        void remove_nodes(const int count, const int place);
        Linked_List<T>* find_el(const int pos);
        unsigned int get_length();

    private:
        Linked_List* head;
        Linked_List* next_node;
        T element;
    };

    template<class T> Linked_List<T>::Linked_List(const unsigned int size)
    {
        Linked_List<T>* current = new Linked_List<T>;
        if (!head) head = current;
        Linked_List<T>* list = 0;
        for (unsigned int i = 0; i < size; i++)
        {
            if (i == 0) list = current;
            std::cout << "Enter the value: ";
            std::cin >> current->element;
            if (std::cin.fail())
            {
                std::cout << "Wrong input!\n";
                break;
            }

            if (i < size)
            {
                current->next_node = new Linked_List<T>(head);
                current = current->next_node;
            }
            else current->next_node = nullptr;
        }
    }

    template<class T> Linked_List<T>::Linked_List(T& arr)
    {
        int size = sizeof(arr) / sizeof(T);
        Linked_List<T>* current = new Linked_List<T>;
        if (!head) head = current;
        Linked_List<T>* list = nullptr;
        for (int i = 0; i < size; i++)
        {
            if (i == 0) list = current;
            current->element = arr[i];
            if (std::cin.fail)
            {
                std::cout << "Wrong input!\n";
                break;
            }

            if (i < size)
            {
                current->next_node = new Linked_List<T>(head);
                current = current->next_node;
            }
            else current->next_node = nullptr;
        }
    }

    template<class T> void Linked_List<T>::change_node(unsigned const int place, T new_val)
    {
        auto current = find_el(place - 1);
        std::cin >> new_val;
        current->element = new_val;
    }

    template<class T> void Linked_List<T>::create_nodes(const unsigned int count, const unsigned int place)
    {
        if (count < 1 || place < 1)
        {
            std::cout << "Wrong input, creating unacceptable amout at unacceptable place\n";
            return;
        }
        Linked_List<T>* templ1 = find_el(place);
        Linked_List<T>* list2 = new Linked_List<T>(count);
        if (place == 1)
        {
            list2->find_el(count - 1)->next_node = head;
            head = list2->head;
        }
        else
        {
            find_el(place - 1)->next_node = list2->head;
            list2->find_el(count - 1)->next_node = templ1;
        }
    }

    template<class T> void Linked_List<T>::remove_nodes(const int count, const int place)
    {
        if (place == 1)
        {
            for (int i = 0; i < count; i++)
            {
                Linked_List* templ = head->next_node;
                delete head;
                head = templ;
            }
        }
        else
        {
            Linked_List* templ_1 = find_el(place);
            for (int i = 0; i < count; i++)
            {
                Linked_List* templ_2 = templ_1->next_node;
                delete templ_1;
                templ_1 = templ_2;
            }
            find_el(place - 1)->next_node = templ_1;
        }
    }

    template<class T> Linked_List<T>* Linked_List<T>::find_el(const int pos)
    {
        Linked_List<T>* tmp = head;
        for (int i = 0; i < pos; i++)
            tmp = tmp->next_node;
        return tmp;
    }

    template<class T> unsigned int WhoLeb::Linked_List<T>::get_length()
    {
        int k = 1;
        auto tmp = head;
        while (tmp->next_node)
        {
            k++;
            tmp = tmp->next_node;
        }
        return k;
    }

    template<class T> void Linked_List<T>::print_list()
    {
        Linked_List<T>* tmp = head;
        while (tmp->next_node)
        {
            std::cout << tmp->element << " ";
            tmp = tmp->next_node;
        }
        std::cout << std::endl;
    }

}

