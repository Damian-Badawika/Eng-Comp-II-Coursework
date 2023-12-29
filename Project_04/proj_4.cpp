#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cctype>

using namespace std;

// Function to load data from a file and display band names and song titles
void sample_load_function() {
    string filename_complete = "/data/courses/ece_3822/current/project_4/songlist.txt";

    ifstream f_id;
    f_id.open(filename_complete, ios_base::in);

    string line;
    string band_name;
    string song_title;

    int i_split;

    while (getline(f_id, line)) {
        // "line" is one complete line from the text file

        // find the comma, which separates band name from song
        i_split = line.find(',');

        // extract bandname and songname
        band_name = line.substr(0, i_split);         // band name is everything up till the comma
        line.erase(0, i_split + 2);                  // erase band name plus comma, plus space
        song_title = line.substr(0, line.size() - 1); // erase the carriage return at the end

        // check to make sure it worked
        cout << band_name << " <<- " << song_title << endl;
        cout << song_title << " <<- " << band_name << endl;
    }
    f_id.close();
}

class hashTable {
protected:
    // Declare data for a table size and a count of the songs in the hash table
    const static int BUFFLEN = 7000;
    int n_songs;

    // Create the buffer for the songs to sit in
    vector<string> buff;

public:
    // Default constructor for the hash table
    hashTable() {
        // Start with no songs
        n_songs = 0;
        buff.reserve(BUFFLEN);
    }

    // Function to assign a key to each song based on its name
    int hash_function(string s) {
        // Create a variable to store the hash key
        int key = 0;

        // Sum the ASCII values of each digit of the id
        for (int i = 0; i < 9; i++) {
            key += s[i];
        }

        // Cool hash function
        key = floor(BUFFLEN * ((int)(key * 0.61803) % 1));

        // Map the key to the buffer size
        return key;
    }

    // Function to search for a song by its name
    string search(string s) {
        // Traversal count to find complexity
        int trav = 0;
        // Create a song pointer for the song we are looking for
        string tmp;

        // Compute the hash value for that ID and redeclare the temp variable
        int target_index = hash_function(s);

        // Index through the list
        while (target_index < BUFFLEN) {
            // Check if the song at the index exists, and check if the ID matches the target
            if (buff.at(target_index) == s) {
                // Assign tmp to the song we found and end the loop
                tmp = buff.at(target_index);
                break;
            } else {
                // Increment the index
                target_index += 1;
                trav++;
            }
        }

        // Display the song we found, display a message if that song doesn't exist
        if (!tmp.empty()) {
            cout << "Song found. Name: " << s << endl;
            cout << "This search took " << trav << " traversals! Wow!!!!" << endl;
        } else {
            cout << "Song " << s << " not found" << endl;
        }

        return tmp;
    }

    // Function to hash a song's ID and insert them into the list
    void insert(string s) {
        // Compute the hash key for the song we want to insert
        int key = hash_function(s);

        buff.insert(buff.begin() + key, s);
        return;
    }

    // Function to display each song in the hash table
    void display() {
        // Index through the buffer
        for (int i = 0; i < BUFFLEN; i++) {
            // Check each element to see if it is empty
            if (!buff.at(i).empty()) {
                // Print the song and its index
                cout << i << buff.at(i) << endl;
            }
        }
    }

    void load_data() {
        string filename_complete = "/data/courses/ece_3822/current/project_4/songlist.txt";
        ifstream f_id;
        f_id.open(filename_complete, ios_base::in);

        string line;
        string band_name;
        string song_title;

        int i_split;

        while (getline(f_id, line)) {
            // "line" is one complete line from the text file

            // find the comma, which separates band name from song
            i_split = line.find(',');

            // extract bandname and songname
            band_name = line.substr(0, i_split);         // band name is everything up till the comma
            line.erase(0, i_split + 2);                  // erase band name plus comma, plus space
            song_title = line.substr(0, line.size() - 1); // erase the carriage return at the end

            // check to make sure it worked
            // cout << band_name << " <<- " << song_title << endl;
            // cout << song_title << " <<- " << band_name << endl;

            insert(song_title);
        }
        f_id.close();
    }
};

class tree {
protected:
    class node {
    public:
        int data;
        string name;
        node *left, *right, *up;
        node(int d, string n) {
            data = d;
            name = n;
            left = nullptr;
            right = nullptr;
            up = nullptr;
        }
    }; // end class node

    node *root;
    int nNodes;

public:
    // Traversal count
    int trav = 0;
    // constructor - no parameters
    tree() {
        root = nullptr;
        nNodes = 0;
    }

    node *get_root() {
        return root;
    }

    int hash_function(string s) {
        // Create a variable to store the hash key
        int key = 0;

        // Sum the ASCII values of each digit of the id
        for (int i = 0; i < 9; i++) {
            key += s[i];
        }

        // Cool hash function
        key = floor(((int)(key * 0.61803) % 1));

        // Map the key to the buffer size
        return key;
    }

    void insert(string s) {
        int d = hash_function(s);
        node *newNode = new node(d, s);
        node *currPtr = root;
        node *parentPtr = nullptr;

        int LR;

        // special case if tree is empty
        if (nNodes == 0)
            root = newNode;
        else {

            // find which node should be parent to newNode
            while (currPtr) {
                parentPtr = currPtr;
                if (d < currPtr->data) {
                    currPtr = currPtr->left;
                    LR = 0;
                } else {
                    currPtr = currPtr->right;
                    LR = 1;
                }
            }

            // connect newNode to parent
            newNode->up = parentPtr;
            if (LR == 0)
                parentPtr->left = newNode;
            else
                parentPtr->right = newNode;
        }

        // increment number of nodes
        nNodes++;
    }

    int search(node *root, string s, int trav) {
        // Base case: If the current node is null
        if (root == nullptr) {
            cout << "Song not found" << endl;
            return trav; // Not found
        }

        // Compute the target key
        int target = hash_function(s);

        // Start searching from the root
        node *currptr = root;

        while (currptr != nullptr) {
            if (target == currptr->data) {
                cout << "Song found!" << endl;
                cout << "This search took " << trav << " traversals!" << endl;
                return trav; // Found
            } else if (target < currptr->data) {
                // Search in the left subtree
                currptr = currptr->left;
                trav++;
            } else {
                // Search in the right subtree
                currptr = currptr->right;
                trav++;
            }
            trav++;
        }

        cout << "Song not found" << endl;
        return trav;
    }

    void print_all(node *currNode) {
        if (currNode) {
            print_all(currNode->left);
            cout << currNode->data << endl;
            print_all(currNode->right);
        }
    }

    // search function
    // print all
    void load_data() {
        string filename_complete = "/data/courses/ece_3822/current/project_4/songlist.txt";

        ifstream f_id;
        f_id.open(filename_complete, ios_base::in);

        string line;
        string band_name;
        string song_title;

        int i_split;

        while (getline(f_id, line)) {
            // "line" is one complete line from the text file

            // find the comma, which separates band name from song
            i_split = line.find(',');

            // extract bandname and songname
            band_name = line.substr(0, i_split);         // band name is everything up till the comma
            line.erase(0, i_split + 2);                  // erase band name plus comma, plus space
            song_title = line.substr(0, line.size() - 1); // erase the carriage return at the end

            // check to make sure it worked
            // cout << band_name << " <<- " << song_title << endl;
            // cout << song_title << " <<- " << band_name << endl;
            insert(song_title);
        }

        f_id.close();
    }
}; // end class tree

int main() {
    string to_search = "Cheap Thrills";
    hashTable songs_hash;
    tree songs_tree;
    // traversal count for tree
    int trav = 0;

    songs_hash.load_data();
    songs_tree.load_data();
    songs_hash.search(to_search);
    songs_tree.search(songs_tree.get_root(), to_search, trav);
    // sample_load_function();

    return 0;
}
