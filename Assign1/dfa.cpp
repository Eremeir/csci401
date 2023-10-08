/*
    Assignment #1
    AUTHOR:  Matt Borek
*/

#include <iostream>
#include <vector>
#include <string>

/**
 * @brief Main function to test DFA Simulator
 * 
 * Process standard input to simualte a DFA and test words to check if they exist in the language of the DFA.
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

    std::vector<std::vector<int>> transitionTable(nstates, std::vector<int>(2));
    for(int i = 0; i < nstates; ++i)
    {
        std::cin >> transitionTable[i][0] >> transitionTable[i][1]; //Parse input for a state transition for A and B.
    }

    std::cout << "    |  a  b" << std::endl;
    std::cout << "----+------" << std::endl;
    for(int i = 0; i < nstates; ++i) //
    {
        std::cout << ((naccepting > 0 && i == acceptingStates[0] ) ? "*" : " ") //If there is at least 1 accepting state and the state number is an accepting state, prefix '*', else ' '.
        << " " << i << " |  " << transitionTable[i][0] << "  " << transitionTable[i][1] << std::endl; //Print A/B transition paths for state i.
    }

    int nwords = 0; //Number of words to check.
    std::cin >> nwords; //Take input for number of words.

    for(int i = 0; i < nwords; ++i) //simulate pathing through DFA.
    {
        std::string word; //Temp string for word input.
        std::cin >> word; //Take input for test word.

        int currentState = 0;
        for(char character : word) //For each character in the word.
        {
            if (character == 'a')
            {
                currentState = transitionTable[currentState][0]; //Lookup transition table from current state for a input and follows to new state.
            } 
            else if (character == 'b')
            {
                currentState = transitionTable[currentState][1]; //Lookup transition table from current state for b input and follows to new state.
            }
        }

        bool accepted = false;
        for(int state : acceptingStates) //For each state in the accepting states vector.
        {
            if (currentState == state) //If current state is accepting.
            {
                accepted = true; //Word is in the language.
                break;
            }
        }

        std::cout << word << " " << (accepted ? "accepted" : "rejected") << std::endl; //Print accepted or rejected based on accept bool.
    }

    return 0;
}