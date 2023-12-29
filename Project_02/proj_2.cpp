#include<iostream>
#include<fstream>
#include "linked_list.h"
using namespace std;

#define DEFAULT_DIRECTORY "/data/courses/ece_3822/current/project_2/"
#define DEFAULT_FILENAME "dataFile1.txt"

// do not edit
string get_filename(int argc, char** argv){
    string filename = DEFAULT_DIRECTORY;
    
    // no command line inputs: use default
    if (argc == 1)
        filename += DEFAULT_FILENAME;

    // command line filename given
    else
        filename += (string) argv[1];
    
    return filename;
}

class linked_list_movies : public linked_list<int>{
    public:
        
    //Display movies
    void display(){
        //assign a temporary pointer to the head of the list
        node* temp = head;

        while (temp != nullptr){

            //Print that pointer's data and move to the next one
            cout << temp->data << ", ";
            temp = temp->next;
        }
        cout<< "\n";
    }

    //Checks if a customer has viewed a specific movie, returns boolean, takes id as an argument
    bool check(int id){
        //assign a temporary pointer to the head of the list
        node* temp = head;

        while (temp != nullptr){

            //If the current customer has viewed the movie, return true
            if(temp->data == id){
                return true;
            }

            //Go to the next node
            temp = temp->next;
        }
        //Returns false if the movie is not in the customer's list
        return false;
    }
};

class customer{
    public:

    int customer_id;
    linked_list_movies movie_ids;    

    //Displays all the movies a specified customer has watched, no arguments, no return
    void display(){

        //Print each customer ID and their watched movies
        cout << "Customer " << customer_id << " watched: ";
        movie_ids.display();
    }

};

// note this a linked list of POINTERS to customers...
// that way you only every make one copy of each customer
// and simply place a pointer to that customer in the linked list

class linked_list_customers : public linked_list<customer*>{

    public:

    void print_customer(int customer_id){

        //assign a temporary pointer to the head of the list
        node* temp = head;

        while (temp != nullptr){

            //Traverse the list to find the specified customer
            if(temp->data->customer_id == customer_id){
                //Display their data
                temp->data->display();
                return;
            }
            //Go to the next node
            temp = temp->next;
        }
    }

    void print_all(){
        //assign a temporary pointer to the head of the list
        node* temp = head;

        while (temp != nullptr){

            //Print that pointer's data and move to the next one
            temp->data->display();
            temp = temp->next;
        }    
    }

    void print_views(int movie_id){
        //declare counter and temproray node variables
        int n = 0;
        node* temp = head;

        //Traverse the linked list
        while(temp != nullptr){

            //Check if the current customer watched the movie, incrment the counter if so
            if(temp->data->movie_ids.check(movie_id)==true){
                n++;
            }

            //Go to the next element
            temp = temp->next;
        }

        //Print the amount of views
        cout << movie_id << " was watched " << n << " times" << endl;
    }

    //Function to load customers from a file, string is an argument, returns void
    void load_customers(string filename){

        //Declare variables for the filename and lines
        ifstream file_id(filename);
        string line;

        //Declare variables for customer info
        int cust_id;
        int movie;
        int n;
        
        //Index through the file line by line
        while(getline(file_id, line)){

            //Creste a new customer poitner
            customer* temp = new customer;

            //Read and assign that cutomer their id
            cust_id = stoi(line);
            temp->customer_id = cust_id;

            //Get the number of movies
            getline(file_id, line);
            n = stoi(line);

            //Index through the next n values and add them to that customer's views
            for(int i = 0 ; i < n ; i++){

                getline(file_id,line);
                movie = stoi(line);
                temp->movie_ids.insert(movie);
            }
            //Insert the new customer to the linked list
            insert(temp);
        }
        
        
    }

};


int main(int argc, char** argv){

    string filename;
    filename = get_filename(argc,argv);

    linked_list_customers clients;
    clients.load_customers(filename);

    clients.print_all();
    clients.print_customer(724);
    clients.print_views(109); 

    return 0;
}