/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;
using std::string;
using std::tuple;
/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) 
        {
            string without_first_letter, without_second_letter;
            //substring without the first letter
            without_first_letter = word.substr(1);
            //substring without the second letter
            //if the word's length is less than 2, we just want the first letter
            //else we want the first letter + everything but the second letter
            (word.length() < 2) ? (without_second_letter = word.substr(0, 1)) : (without_second_letter = word[0] + word.substr(2));
            
            //make sure all three words are homophones
            if(d.homophones(word, without_first_letter) && d.homophones(word, without_second_letter))
            {
                //creates a tuple of the homophone
                tuple<string, string, string> cartalk_homophones
                    = tuple<string, string, string>(word, without_first_letter, without_second_letter);
                //pushes it to "ret" vector
                ret.push_back(cartalk_homophones);
            }
        }
    }
    /* Your code goes here! */
    return ret;
}
