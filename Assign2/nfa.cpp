/*
    Assignment #2
    AUTHOR:  Matt Borek
*/

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

/**
 * @brief Main function to test NFA Simulator
 * 
 * Process standard input to simualte a NFA and test words to check if they exist in the language of the NFA.
 * 
 * @return int indicating program's exit status.
 */
int main()
{
    int nstates = 0,      //Number of states
        naccepting = 0;   //Number of accepting states

    std::cin >> nstates >> naccepting; //Take input for num states and num accepting states.

    std::vector<int> acceptingStates; //Create a vector of accepting states.
    for(int i = 0; i < naccepting; ++i)
    {
        int state = 0;
        std::cin >> state; //Take next input for state.
        acceptingStates.push_back(state); //Add state to accepting vector.
    }

    std::vector<std::vector<std::set<int>>> transitionTable(nstates, std::vector<std::set<int>>(2));
    for(int i = 0; i < nstates; ++i) //Parse input for a state transition for A and B.
    {
        int ntransitionsA = 0, //Number of outgoing transitions for A.
            ntransitionsB = 0; //Number of outgoing transitions for B.

        std::cin >> ntransitionsA; //Take input for number of outgoing A transitions.
        for(int j = 0; j < ntransitionsA; ++j) //Insert each A transition into the table.
        {
            int nextState = 0;
            std::cin >> nextState;
            transitionTable[i][0].insert(nextState); //Insert into A transition set.
        }

        std::cin >> ntransitionsB; //Take input for number of outgoing B transitions.
        for(int j = 0; j < ntransitionsB; ++j) //Insert each B transition into the table.
        {
            int nextState = 0;
            std::cin >> nextState;
            transitionTable[i][1].insert(nextState); //Insert into B transition set.
        }
    }

    std::cout << "    | a b" << std::endl;
    std::cout << "----+----" << std::endl;
    for(int i = 0; i < nstates; ++i) //If there is at least 1 accepting state and the state number is an accepting state, prefix '*', else ' '.
    {
        std::cout << ((naccepting > 0 && std::find(acceptingStates.begin(), acceptingStates.end(), i) != acceptingStates.end()) ? "* " : "  ") << i << " |";
        for(int j = 0; j < 2; ++j) //Print A/B transition paths for state i.
        {
            std::cout << " {";
            for(int state : transitionTable[i][j])
            {
                if(state >= 0) //Handle empty sets.
                {
                    std::cout << " ";
                }
                std::cout << state;
            }

            std::cout << "}";
        }

        std::cout << " " << std::endl;
    }

    int nwords = 0; //Number of words to check.
    std::cin >> nwords; //Take input for number of words.

    for(int i = 0; i < nwords; ++i) //simulate pathing through DFA.
    {
        std::string word; //Temp string for word input.
        std::cin >> word; //Take input for test word.

        std::set<int> currentStates = {0};
        for(char character : word) //For each character in the word.
        {
            std::set<int> nextStates;
            for(int state : currentStates)
            {
                for(int nextState : transitionTable[state][character - 'a']) //Convert char to int.
                {
                    nextStates.insert(nextState);
                }
            }

            currentStates = nextStates;
        }

        bool accepted = false;
        for(int state : currentStates) //For each state in the accepting states vector.
        {
            if(std::find(acceptingStates.begin(), acceptingStates.end(), state) != acceptingStates.end()) //If current state is accepting. 
            {
                accepted = true; //Word is in the language.
                break;
            }
        }

        std::cout << word << " " << (accepted ? "accepted" : "rejected") << std::endl; //Print accepted or rejected based on accept bool.
    }

    return 0;
}