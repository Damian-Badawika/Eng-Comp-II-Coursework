/* PROJECT 3 - proj_3.cpp

    Damian Badawika
    tuo69407@temple.edu
    10/29/2023

    Implements a system that models reading data asynchronously from the cloud,
    storing it temporarily in a buffer, and then placing it into a hash table.

    Compile:
        make all
    Compile for debug:
        make debug
    Run:
        ./proj_3 [OPT]
        where [OPT] is 1, 2, or 3 depending on which test case you are running.

*/
#include<iostream>
#include<thread>
#include<fstream>
#include<vector>
#include<chrono>
#include<mutex>
#include<ctype.h>
#include<iomanip>

using namespace std;
using namespace std::chrono;

//Student data structure
struct student{

    //Class data for each student
    string first;
    string last;
    double id;
    int gpa;
    string major;

    //Student constructor with empty default values
    student(string f = "", string l = "", double i = 0, int g = 0, string m = ""){
        first = f;
        last = l;
        id = i;
        gpa = g;
        major = m;
    }

    //Function to check if the student's data isn't populated
    bool is_empty(){
        return ((first=="") & (last=="") & (gpa==0) & (id == 0) & (major==""));
    }
};

//Hash table class
class hashTable{

    protected:
    //Declare data for a table size and a count of the students in the hash table
    const static int BUFFLEN = 50000;
    int n_students;

    //Create the buffer for the students to sit in
    student* buffer[BUFFLEN];

    public:

    //Default constructor for the hash tab;e
    hashTable(){
        
        //Start with no students
        n_students = 0;

        //Array elements point to no students
        for(int i = 0 ; i < BUFFLEN ; i++){
            buffer[i] = new student();
        }
    }

    //Function to assign a key to each studetn based on their ID number
    int hash_function(student* s){

        //Take the student ID as input for the hash function
        int id = s->id;

        //Convert to id to a string to get the ASCII values
        string sid = to_string(id);
        //Create a variable to store the hash key
        int key = 0;
        
        //Sum the ASCII values of each digit of the id
        for(int i = 0 ; i < 9 ; i++){
            key += sid[i];
        }

        //Map the key to the buffer size
        return key % BUFFLEN;
    } 

    //Function to search for a student by their ID number
    student* search(int i){
        //Create a student pointer for the student we are looking for
        student* tmp = new student("", "", i, 0, "");

        //Compute the hash value fro that ID, and redeclare the temp variable
        int target_index = hash_function(tmp);
        tmp = new student();

        //Index through the list
        while(target_index < BUFFLEN){

            //Check if the student at the index exists, and check if the ID matches the target
            if(!buffer[target_index]->is_empty() && buffer[target_index]->id == i){

                //Assign tmp to the student we found and end the loop
                tmp = buffer[target_index];
                break;
            }
            else{
                //Increment the index
                target_index += 1;
            }
        }

        //Display the student we found, display a message if that student doesn't exist
        if(!tmp->is_empty()){
            cout << "Student found. Name: " << tmp->first << " " << tmp->last << ", ID: " << fixed << setprecision(0) << tmp->id << ", GPA: " << tmp->gpa << ", Major: " << tmp->major << endl;
        }
        else{
            cout << "Student " << i << " not found" << endl;
        }

        return tmp;
    }

    //Function to hash a student's ID and insert them into the list
    void insert(student* s){

        //Compute the hash key for the student we want to insert
        int key = hash_function(s);

        //Go through the list to insert the student
        while(key < BUFFLEN){

            //Check of the current spot is empty
            if(buffer[key]->is_empty()){

                //Insert the student in the empty spot and increment the student counter
                delete buffer[key]; //delete the placeholder pointer
                buffer[key] = s;
                n_students++;
                break; //stop the loop
            }
            else{
                //go to the next spot if this one is taken
                key++;
            }
        }
        return;
    }

    //Function to display each student in the hash table
    void display(){

        //Index through the buffer
        for (int i = 0 ; i < BUFFLEN ; i++){
            //cout << i << ": ";

            //Check each element to see if it is empty
            if(!buffer[i]->is_empty()){

                //Print the student and their data
                cout << i << ": " << "Name: " << buffer[i]->first << " " << buffer[i]->last << ", ID: " << fixed << setprecision(0) << buffer[i]->id << ", GPA: " << buffer[i]->gpa << ", Major: " << buffer[i]->major << endl;
            }
        }
    }
};

//The queue class for the students to go in
class queue{

    protected:

    //vector for the student queue
    vector<student*> q;

    public:

    //Function to insert a student into the queue
    void insert(student* s){
        q.push_back(s);
        return;
    }

    //Function to retrieve a student from the queue
    student* retrieve(){

        //Allocate memory for a student
        student* tmp = new student();

        //Take the last student to be added
        tmp = q.back();

        //Pop that student off of the list
        q.pop_back();
        return tmp;
    }

    //Checks if the queue is empty
    bool is_empty(){
        return q.empty();
    }
};

// You will need these global variables
queue waiting_list;
hashTable student_db;
mutex queue_mutex;

// this controls the input timing. do not edit
bool stop_thread = false;
steady_clock::time_point t1 = steady_clock::now();
float t_elapsed(){
    return duration_cast<seconds>(steady_clock::now() - t1).count();
}


void process_input_data(){
    student* p_student;

    while (!stop_thread){
        queue_mutex.lock();

        // YOUR CODE HERE
        // Checking the queue
        // If there's data, remove it from the queue and
        // add it to the hash table

        //Check if the list is empty
        if(!waiting_list.is_empty()){

            //Retrieve and remove the first student from the queue
            p_student = waiting_list.retrieve();

            //Insert that student to the hash table
            student_db.insert(p_student);
        }


        queue_mutex.unlock();
    }
}

void load_data(string filename){
    string shared_path = "/data/courses/ece_3822/current/project_3/";
    string filename_complete = shared_path + filename;

    // create local variables to stash the data for each person as it's
    // read from the file
    float arrival_time,gpa;
    string first,last,major;
    int id;

    ifstream f_id;
    f_id.open(filename_complete,ios_base::in);

    // start the thread that will wait for input data to arrive
    thread thr(process_input_data);

    clock_t t_start = clock();
    while (f_id >> arrival_time){
        // read data for the next person in the file
        f_id >> first;
        f_id >> last;
        f_id >> gpa;
        f_id >> id;
        f_id >> major;

        // wait until their data packet has 'arrived'
        while ( t_elapsed() < arrival_time){
            ;
        }

        // YOUR CODE HERE
        // [1] create a new student
        student* s = new student(first, last, id, gpa, major);

        queue_mutex.lock();

        // YOUR CODE HERE
        // [2] add the new student to the wait queue
        waiting_list.insert(s);

        queue_mutex.unlock();

    }

    f_id.close();                       // close the data file
    
    while (!waiting_list.is_empty()){   // wait for the waiting_list queue
        ;                               // to empty out before stopping the 
    }                                   // process_input_data thread

    stop_thread = true;                 // send a signal to the thread to stop running
    thr.join();                         // wait for the thread to finish up
}

int main(int argc, char** argv){
    string filename;

    if (argc !=2 ){
        cout << "ERROR: include a command line arguement of 0, 1, or 2" << endl;
        return -1;
    }

    switch (stoi(argv[1])){
        case 0: filename = "student_data_short.txt"; break;
        case 1: filename = "student_data_medium.txt"; break;
        case 2: filename = "student_data.txt"; break;
    }

    load_data(filename);

    // now that the data has been stored in the hash table, lets test hashtable lookup
    // if the student is found, print all their info
    // if not, print <student name> "not found"

    // YOUR CODE HERE FOR TESTING THE SEARCH/LOOKUP capability

    student_db.display();
    student_db.search(111111111);

    //Declare a new hash table
    hashTable table;
    // cout << "Created table" <<endl;
    student* a = new student("Lebron", "James", 427980112, 4.0, "Engineering");
    student* b = new student("Andrea", "Pirlo", 258399712, 2.3, "Italian");
    student* c = new student("Charles", "Oliveira", 948140115, 3.1, "MIS");

    // cout << "Created students" <<endl;

    table.insert(a);
    table.insert(b);
    table.insert(c);

    // cout << "inserted students" <<endl;

    // table.search(427980112);
    // table.search(258399712);
    // table.search(948140115);

    // cout << "found students" <<endl;

    // table.display();
    // search for the following student IDs
    // 427980112
    // 258399712
    // 948140115

    return 0;
}