#ifndef _TEAM_
#define _TEAM_

#include "player.cpp"

class team{
    private:

        //Class data, values for name, array of player pointers, score value, 
        string name;
        vector<player*> members;
        int score; 
        bool captain;

    public:

    //Team class constructor
    team(string x){
        cout << "Creating team named: " << x << endl;
        name = x;
    }

    // Getter for score
    int get_score(){
        return score;
    }

    //Checks if the team already has a captain
    bool has_captain(){
        
        //Index through team members
        //
        for( int i = 0 ; i < members.size() ; i++){
        
            if (members[i]->get_cap() == true){
                return true;
            }
        }
        return false;
    }
    
    //Function to add a player to the team
    void add_player(player* p, bool cap){

        //Sets the player's captain status and checks if the team already has a captian
        if(has_captain() == true){

            //First player set as the captain is always the captain
            p->set_cap(0);
        }

        else{
            p->set_cap(cap);
        }
        //Adds the player to the team
        members.push_back(p);
        return;
    }
    
    //Getter for team name
    string get_name(){
        return name;
    }

    //Function for a team to play a turn
    void play_turn(){

        //Index through the members of the team
        for(int i = 0 ; i < members.size() ; i++){

            //Check if each member is the captain
            if(members[i]->get_cap() == true){

                //Play a turn twice if the player is a captain
                members[i]->set_score(generate_score(members[i]->get_ability()));
                members[i]->set_score(generate_score(members[i]->get_ability()));
            }
            else{

                //Play one turn if the player is not a captain
                members[i]->set_score(generate_score(members[i]->get_ability()));
            }

            //Add the generated values to the score of the team
            score += members[i]->get_score();
        }
        return;
    }

};

#endif