#ifndef _PLAYER_
#define _PLAYER_

/* this include gives you access to 
    int generate_score(int)
which takes ability (0,1,2) as input and returns a valid 
score according to the project instructions */
#include "ece_3822.h"
#include <vector>
using namespace std;

class player{
    private:
    
    //Initialize class data
    //
    string name;
    int lvl;
    bool cap;
    int score;

    public:

    //Class constructor
    //
    player(string n, int level=0, bool captain = false, int val = 0){
        lvl = level;    //Values for level, captains status, score, and name
        cap = captain; 
        score = val;
        name = n;
        cout << "Creating player: " << name << endl;
    }

    //Function to set the name of the player
    void set_name(string n){
        name = n;   //Player name is the input of the function
        return;
    }

    //Setter for ability level
    void set_ability(int level){
        lvl = level;
        return;
    }

    //Getter for ability level
    int get_ability(){
        return lvl;
    }

    //Setter for captain status
    void set_cap(bool in){
        cap = in;
        return;
    }

    //Function to reset a player's score to 0
    void reset_score(){
        score = 0;
        return;
    }

    //Getter for player score
    int get_score(){
        return score;
    }

    //Setter for player score
    void set_score(int n){
        score = n;
        return;
    }

    //Getter for captain status
    bool get_cap(){
        return cap;
    }

    //Cleass display function
    void display(){

        //Print name, level, and score
        //
        cout << "Player name: " << name << endl;
        cout << "Player ability level: " << lvl << endl;
        cout << "Player score: " << score << endl;

        return;
    }
    
    //Functionto generate player score for a turn
    void play_turn(){
        score += generate_score(lvl);
        return;
    }

};

#endif