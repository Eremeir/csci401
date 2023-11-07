/*
    Assignment #2
    AUTHOR:  Matt Borek
*/

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <unordered_set>

/**
 * @brief Build Epsilon Closure
 * 
 * Build set of states reachable through epsilon moves from the initial set of reachable states.
 * 
 * @param transitionTable 2D vector representing sets of transition pathways by holding states and input symbols.
 * @param currentStates Set of current reachable states to use for building epsilon closure.
 * @param epsilonStates Set to populate with the epsilon closure.
 */
void epsilonClosure(const std::vector<std::vector<std::set<int>>>& transitionTable, const std::set<int>& currentStates, std::set<int>& epsilonStates)
{
    std::unordered_set<int> visitedStates; //Set of visited states to avoid infinite looping.
    std::vector<int> unvisitedStates(currentStates.begin(), currentStates.end()); //States that need to be visited.

    while(!unvisitedStates.empty()) //While still states to visit.
    {
        int currentState = unvisitedStates.back();
        unvisitedStates.pop_back();

        if(visitedStates.count(currentState) == 0) //If unvisited, mark as visited and register with state set.
        {
            visitedStates.insert(currentState);
            epsilonStates.insert(currentState);

            for(int epsilonState : transitionTable[currentState][2]) //Follow through transition paths.
            {
                unvisitedStates.push_back(epsilonState);
            }
        }
    }
}

/**
 * @brief Main function to test NFA with e-moves Simulator
 * 
 * Process standard input to simualte a NFA with e-moves and test words to check if they exist in the language of the NFA.
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

    std::vector<std::vector<std::set<int>>> transitionTable(nstates, std::vector<std::set<int>>(3));
    for(int i = 0; i < nstates; ++i) //Parse input for a state transition for A and B.
    {
        int ntransitionsA = 0, //Number of outgoing transitions for A.
            ntransitionsB = 0, //Number of outgoing transitions for B.
            ntransitionsE = 0; //Number of outgoing epsilon moves.

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

        std::cin >> ntransitionsE; //Take input for number of outgoing epsilon movess.
        for(int j = 0; j < ntransitionsE; ++j) //Insert each epsilon move into the table.
        {
            int nextState = 0;
            std::cin >> nextState;
            transitionTable[i][2].insert(nextState); //Insert into epsilon moves set.
        }
    }

    std::cout << "    | a b e" << std::endl;
    std::cout << "----+------" << std::endl;
    for(int i = 0; i < nstates; ++i) //If there is at least 1 accepting state and the state number is an accepting state, prefix '*', else ' '.
    {
        std::cout << ((naccepting > 0 && std::find(acceptingStates.begin(), acceptingStates.end(), i) != acceptingStates.end()) ? "* " : "  ") << i << " |";
        for(int j = 0; j < 3; ++j) //Print A/B transition paths and epsilon moves for state i.
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

    for(int i = 0; i < nwords; ++i) //Simulate pathing through NFA with E-Moves.
    {
        std::string word; //Temp string for word input.
        std::cin >> word; //Take input for test word.

        std::set<int> currentStates = {0}; //Current reachable states
        std::set<int> epsilonStates; //Current reachable states with E-Moves.

        epsilonClosure(transitionTable, currentStates, epsilonStates); //Build epsilon closure states set.

        for(char character : word) //For each character in the word.
        {
            std::set<int> nextStates; //Reachable states after next read.
            for(int state : epsilonStates)
            {
                for(int nextState : transitionTable[state][character - 'a']) //Convert char to int.
                {
                    nextStates.insert(nextState); //Add state to process.
                }
            }

            epsilonStates.clear(); //Reset epsilon closure for new character.
            epsilonClosure(transitionTable, nextStates, epsilonStates); //Build epsilon closure states set.
            currentStates = nextStates; //Update the current reachable states.
        }

        bool accepted = false;
        for(int state : currentStates)
        {
            if(std::find(acceptingStates.begin(), acceptingStates.end(), state) != acceptingStates.end()) //If current state is an accepting state.
            {
                accepted = true;
                break;
            }
        }

        if(!accepted)
        {
            for(int epsilonState : epsilonStates)
            {
                if(std::find(acceptingStates.begin(), acceptingStates.end(), epsilonState) != acceptingStates.end()) //If an accepting state can be reached from epsilon move.
                {
                    accepted = true;
                    break;
                }
            }
        }

        std::cout << word << " " << (accepted ? "accepted" : "rejected") << std::endl; //Print accepted or rejected based on accept bool.
    }

    return 0;
}
