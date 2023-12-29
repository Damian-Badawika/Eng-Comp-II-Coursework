#ifndef _linked_list_h_
#define _linked_list_h_

namespace ll_node{
    // node for the linked list data
    // do not edit
    class node{
        
        private:
        int data;
        node* next;

        public:
        
        // constructor
        node(int d){
            data = d;
            next = nullptr;
        };

        // getter, data
        int get_data(){
            return data;
        }

        // setter, 'next' pointer
        void set_next(node *n){
            next = n;
        }

        // getter, 'next' pointer
        node* get_next(){
            return next;
        }
    };
}

class linked_list{

    // private class variables
    private:

    ll_node::node* head;
    int n_elements;

    // public class methods
    public:

    linked_list(){
        head = nullptr;
        n_elements = 0;
    }

    void insert(int d){
        ll_node::node *newNode = new ll_node::node(d);
        newNode->set_next(head);
        head = newNode;
        n_elements++;
    }

    int pop(){
        int ret_val = 0;
        if (n_elements > 0){
            ret_val = head->get_data();
            ll_node::node *tmpNode = head;
            head = head->get_next();
            delete tmpNode;
            n_elements --;
        }
        return ret_val;
    }

    //Function to clear the list, no arguments, returns void
    //
    void clear_list(){
        
        //Declare a temporary pointer for indexing
        ll_node::node* tmp;

        //Index through the linked list
        //
        while(head != nullptr){
            //Set temporary pointer equal to the head
            tmp = head;

            //Get the next element and delete the current one
            head = head->get_next();
            delete [] tmp;
        }

        //Set the element counter to zero
        n_elements = 0;

        return;
    }

    //Function to check if the linked list is empty or not, returns boolean, takes no argument
    //
    bool is_empty(){
        
        //Check if the head pointer is null, if yes, return true stating that the list is empty
        //
        if(head == nullptr){
            return true;
        }
        
        //If the head pointer points to any node, the list is not empty
        //
        else{
            return false;
        }
    }

    //Function to get the size of the linked list, no arguments, returns integer
    int size(){

        //return list size
        return n_elements;
    }
    
    //Function to sum the linked list, no arguments, returns integer
    int sum(){

        //Declare sum variable, index variable, and temporary node pointer
        int sum = 0;
        int i = 0;
        ll_node::node* tmp = head;

        //Index through the linked list
        while(i < n_elements){

            //Sum the data and go to the next element
            sum += tmp -> get_data();
            tmp = tmp->get_next();

            //Increment index variable
            i++;
        }

        //Return the summation of all data
        return sum;
    }
};

#endif