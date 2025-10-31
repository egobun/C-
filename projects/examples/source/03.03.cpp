//////////////////////////////////////////////////
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>

//////////////////////////////////////////////////

// class Entity
// {
// public :

// 	Entity()
//     {
//         std::cout << "Entity:: Entity (1)\n";
//     }

// //  ----------------------------------------------

//     Entity(int x, int y) : m_x(x), m_y(y)
//     {
//         std::cout << "Entity:: Entity (2)\n";

//     //	m_y = y; // error
//     }

// //  ----------------------------------------------

// //	Entity(int x, int y) : m_y(y), m_x(x) // error
// //  {
// //      std::cout << "Entity:: Entity (3)\n";
// //  }

// //  ----------------------------------------------

// 	Entity(int x) : Entity(x, 0)
// 	{
//         std::cout << "Entity:: Entity (4)\n";
// 	}

// //  ----------------------------------------------

//    ~Entity()
//     {
//         std::cout << "Entity::~Entity\n";
//     }

// private :

//     int       m_x = 0;
          
//     int const m_y = 0; //!!!не может быть изменено после инициализации-вызова конструктора
// };

//////////////////////////////////////////////////

class List{

private:

    struct Node
    {
        int data = 0;
        Node* next_node = nullptr;
        Node(int data) : data(data), next_node(nullptr) {};
    };

    Node* tail = nullptr;
    Node* head = nullptr;
public:
    // struct Node;
    // List(Node* node) {
    //     this->head = node;
    // }


    bool empty () const
    {
        return head == nullptr;
    }

    void push_back (int data)
    {
        Node* new_node = new Node(data);
        
        if(this->empty())
        {
            tail = new_node;
            head = new_node;
        } else {
            tail->next_node = new_node;
            tail = new_node;
        }
    }

    void push_front (int data)
    {
        Node* new_node = new Node(data);
        
        if(this->empty())
        {
            head = tail = new_node;
        } else {
            new_node->next_node = head;
            head = new_node;
        }
    }

    void pop_back()
    {
        if(empty())
        {
            return;
        } else if (head == tail) {
            delete tail;
            head = nullptr;
            tail = nullptr;
        } else {
            Node* node = head;
            while(node->next_node != tail)
            {
                node = node->next_node;
            }
            delete tail;
            tail = node;
            tail->next_node = nullptr;
        }
    }

    void pop_front()
    {
        if(empty()) return;

        Node* node = head;
        head = node->next_node;
        if(head == nullptr)
        {
            tail = nullptr;
        }
        delete node;
        
    }


    void show () const
    {   
        if(empty())
        {
            std::cout << "List is empty" << std::endl;
        } else {
            Node* current_node = head;
            while(current_node != nullptr)
            {
                std::cout << current_node->data << " || ";
                current_node = current_node->next_node;
            }
            
        }
        std::cout << std::endl;
    }

    Node* get () const
    {
        if(empty())
        {
            throw std::runtime_error("List is empty");

        } else {

            Node* fast = head;
            Node* slow = head;

            while(fast && fast->next_node)
            {
                fast = fast->next_node->next_node;
                slow = slow->next_node;
            }
            return slow;
        }
    }

    ~List()
    {
        while(head != nullptr){
            Node* del_node = head;
            head = head->next_node;
            delete del_node;
        }
        tail = nullptr;
    }


    
};

int main()
{
    List list;

    for(int i = 0; i < 10; i++)
    {
        list.push_back(i);
    }

    for(int i = -1; i > -5; i--)
    {
        list.push_front(i);
    }

    list.show();

    std::cout << list.get()->data << std::endl;

    list.pop_back();
    list.pop_front();

    list.show();

//     Entity entity_1;

// //	Entity entity_2(); // error

// 	Entity entity_3(3, 3);
	
// 	Entity entity_4(4);

//  -----------------------------------

//	assert(entity_1.m_x == 0); // error
}

//////////////////////////////////////////////////